/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "multiimapvacationmanager.h"
#include "vacationcheckjob.h"
#include <kmanagesieve/sievejob.h>
#include <ksievecore/util/util_p.h>
#include <managescriptsjob/checkkolabkep14supportjob.h>
#include <managescriptsjob/parseuserscriptjob.h>

#include "libksieveui_debug.h"
#include "searchserverwithvacationsupportjob.h"
#include <QVariant>

using namespace KSieveUi;
MultiImapVacationManager::MultiImapVacationManager(KSieveCore::SieveImapPasswordProvider *passwordProvider, QObject *parent)
    : QObject(parent)
    , mPasswordProvider(passwordProvider)
{
}

MultiImapVacationManager::~MultiImapVacationManager() = default;

void MultiImapVacationManager::checkVacation(const QString &serverName, const QUrl &url)
{
    ++mNumberOfJobs;
    if (!mKep14Support.contains(serverName)) {
        auto checkKep14Job = new KSieveCore::CheckKolabKep14SupportJob(this);
        checkKep14Job->setProperty("triggerScript", QVariant(true));
        checkKep14Job->setServerName(serverName);
        checkKep14Job->setServerUrl(url);
        connect(checkKep14Job, &KSieveCore::CheckKolabKep14SupportJob::result, this, &MultiImapVacationManager::slotCheckKep14Ended);
        checkKep14Job->start();
        return;
    }

    auto job = new VacationCheckJob(url, serverName, this);
    job->setKep14Support(mKep14Support[serverName]);
    connect(job, &VacationCheckJob::vacationScriptActive, this, &MultiImapVacationManager::slotScriptActive);
    job->start();
}

void MultiImapVacationManager::checkVacation()
{
    if (mCheckInProgress) {
        return;
    }
    mNumberOfJobs = 0;
    mCheckInProgress = true;

    auto job = new SearchServerWithVacationSupportJob(this);
    job->setPasswordProvider(passwordProvider());
    connect(job,
            &SearchServerWithVacationSupportJob::searchServerWithVacationSupportFinished,
            this,
            &MultiImapVacationManager::slotSearchServerWithVacationSupportFinished);
    job->start();
}

void MultiImapVacationManager::slotSearchServerWithVacationSupportFinished(const QMap<QString, KSieveCore::Util::AccountInfo> &list)
{
    QMapIterator<QString, KSieveCore::Util::AccountInfo> i(list);
    while (i.hasNext()) {
        i.next();
        checkVacation(i.key(), i.value().sieveUrl);
    }
}

void MultiImapVacationManager::slotScriptActive(VacationCheckJob *job, const QString &scriptName, bool active)
{
    --mNumberOfJobs;
    if (mNumberOfJobs == 0) {
        mCheckInProgress = false;
    }

    job->deleteLater();

    if (job->noScriptFound()) {
        Q_EMIT scriptActive(false, job->serverName());
        return;
    }
    Q_EMIT scriptActive(active, job->serverName());
    Q_EMIT scriptAvailable(job->serverName(), job->sieveCapabilities(), scriptName, job->script(), active);
}

void MultiImapVacationManager::slotCheckKep14Ended(KSieveCore::CheckKolabKep14SupportJob *job, bool success)
{
    job->deleteLater();
    if (!success) {
        --mNumberOfJobs;
        return;
    }

    mKep14Support.insert(job->serverName(), job->hasKep14Support());

    auto checkJob = new VacationCheckJob(job->serverUrl(), job->serverName(), this);
    checkJob->setKep14Support(job->hasKep14Support());
    connect(checkJob, &VacationCheckJob::vacationScriptActive, this, &MultiImapVacationManager::slotScriptActive);
    checkJob->start();
}

bool MultiImapVacationManager::kep14Support(const QString &serverName) const
{
    if (mKep14Support.contains(serverName)) {
        return mKep14Support[serverName];
    } else {
        qCWarning(LIBKSIEVE_LOG) << "We don't know the KEP:14 support for this server." << serverName;
    }
    return false;
}

KSieveCore::SieveImapPasswordProvider *MultiImapVacationManager::passwordProvider() const
{
    return mPasswordProvider;
}

#include "moc_multiimapvacationmanager.cpp"
