/*
  SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include "ksieveui_export.h"
#include <QObject>
#include <QUrl>
#include <memory>
namespace KManageSieve
{
class SieveJob;
}

namespace KSieveUi
{
class RenameScriptJobPrivate;
/**
 * @brief The RenameScriptJob class
 * @author Laurent Montel <montel@kde.org>
 */
class KSIEVEUI_EXPORT RenameScriptJob : public QObject
{
    Q_OBJECT
public:
    explicit RenameScriptJob(QObject *parent = nullptr);
    ~RenameScriptJob() override;

    void setOldUrl(const QUrl &url);
    void setIsActive(bool active);
    void setNewName(const QString &newName);

    Q_REQUIRED_RESULT bool canStart() const;

    void start();

Q_SIGNALS:
    void finished(const QUrl &oldUrl, const QUrl &newUrl, const QString &error, bool success);

private Q_SLOTS:
    KSIEVEUI_NO_EXPORT void slotDeleteResult(KManageSieve::SieveJob *job, bool success);
    KSIEVEUI_NO_EXPORT void slotPutScript(KManageSieve::SieveJob *job, bool success);
    KSIEVEUI_NO_EXPORT void slotGetResult(KManageSieve::SieveJob *job, bool success, const QString &script, bool isActive);

private:
    Q_DISABLE_COPY(RenameScriptJob)
    std::unique_ptr<RenameScriptJobPrivate> const d;
};
}
