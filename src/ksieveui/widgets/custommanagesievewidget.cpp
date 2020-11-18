/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "custommanagesievewidget.h"
#include "widgets/managesievetreeview.h"
#include "util/util_p.h"

#include <KLocalizedString>
#include <QIcon>
#include <QTreeWidgetItem>
#include <kmanagesieve/sievejob.h>
#include <widgets/sievetreewidgetitem.h>

using namespace KSieveUi;

CustomManageSieveWidget::CustomManageSieveWidget(SieveImapPasswordProvider *passwordProvider, QWidget *parent)
    : KSieveUi::ManageSieveWidget(parent)
    , mPasswordProvider(passwordProvider)
{
}

CustomManageSieveWidget::~CustomManageSieveWidget()
{
}

void CustomManageSieveWidget::updateSieveSettings()
{
    mSieveImapInstances = KSieveUi::Util::sieveImapInstances();
    Q_EMIT updateSieveSettingsDone();
}

bool CustomManageSieveWidget::refreshList()
{
    bool noImapFound = true;
    SieveTreeWidgetItem *last = nullptr;
    mLastSieveTreeWidgetItem = nullptr; //TODO
    mServerSieveInfos.clear();
    for (const KSieveUi::SieveImapInstance &type : mSieveImapInstances) {
        if (type.status() == KSieveUi::SieveImapInstance::Broken) {
            continue;
        }
        mServerSieveInfos.insert(type.name(), type.identifier());

        QString serverName = type.name();
        last = new SieveTreeWidgetItem(treeView(), last);
        last->setIcon(0, QIcon::fromTheme(QStringLiteral("network-server")));

        const KSieveUi::Util::AccountInfo info = KSieveUi::Util::fullAccountInfo(type.identifier(), mPasswordProvider, false);
        const QUrl u = info.sieveUrl;
        if (u.isEmpty()) {
            auto *item = new QTreeWidgetItem(last);
            item->setText(0, i18n("No Sieve URL configured"));
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
            treeView()->expandItem(last);
        } else {
            serverName += QStringLiteral(" (%1)").arg(u.userName());
            KManageSieve::SieveJob *job = KManageSieve::SieveJob::list(u);
            //qDebug() << " SETTINGS " << info;
            job->setProperty("sieveimapaccountsettings", QVariant::fromValue(info.sieveImapAccountSettings));
            connect(job, &KManageSieve::SieveJob::gotList, this, &CustomManageSieveWidget::slotGotList);
            mJobs.insert(job, last);
            mUrls.insert(last, u);
            last->startAnimation();
        }
        last->setText(0, serverName);
        noImapFound = false;
    }
    return noImapFound;
}

void CustomManageSieveWidget::searchSieveScript()
{
#if 0
    QString serverName = type.name();
    mLastSieveTreeWidgetItem = new SieveTreeWidgetItem(treeView(), mLastSieveTreeWidgetItem);
    mLastSieveTreeWidgetItem->setIcon(0, QIcon::fromTheme(QStringLiteral("network-server")));

    const KSieveUi::Util::AccountInfo info = KSieveUi::Util::fullAccountInfo(type.identifier(), mPasswordProvider, false);
    const QUrl u = info.sieveUrl;
    if (u.isEmpty()) {
        auto *item = new QTreeWidgetItem(mLastSieveTreeWidgetItem);
        item->setText(0, i18n("No Sieve URL configured"));
        item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        treeView()->expandItem(mLastSieveTreeWidgetItem);
    } else {
        serverName += QStringLiteral(" (%1)").arg(u.userName());
        KManageSieve::SieveJob *job = KManageSieve::SieveJob::list(u);
        //qDebug() << " SETTINGS " << info;
        job->setProperty("sieveimapaccountsettings", QVariant::fromValue(info.sieveImapAccountSettings));
        connect(job, &KManageSieve::SieveJob::gotList, this, &CustomManageSieveWidget::slotGotList);
        mJobs.insert(job, mLastSieveTreeWidgetItem);
        mUrls.insert(mLastSieveTreeWidgetItem, u);
        mLastSieveTreeWidgetItem->startAnimation();
    }
    mLastSieveTreeWidgetItem->setText(0, serverName);
#endif
}
