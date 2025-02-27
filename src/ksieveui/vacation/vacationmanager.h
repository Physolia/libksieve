/*
  SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include "ksieveui_export.h"
#include <QObject>
#include <memory>
class QWidget;
namespace KSieveCore
{
class SieveImapPasswordProvider;
}
namespace KSieveUi
{
class VacationManagerPrivate;
/**
 * @brief The VacationManager class
 * @author Laurent Montel <montel@kde.org>
 */
class KSIEVEUI_EXPORT VacationManager : public QObject
{
    Q_OBJECT
public:
    explicit VacationManager(KSieveCore::SieveImapPasswordProvider *passwordProvider, QWidget *parent);
    ~VacationManager() override;

    void checkVacation();

public Q_SLOTS:
    void slotEditVacation(const QString &serverName);

Q_SIGNALS:
    void updateVacationScriptStatus(bool active, const QString &serverName);

private:
    KSIEVEUI_NO_EXPORT void slotDialogCanceled();
    KSIEVEUI_NO_EXPORT void slotDialogOk();
    KSIEVEUI_NO_EXPORT void slotUpdateVacationScriptStatus(bool active, const QString &serverName);

private:
    Q_DISABLE_COPY(VacationManager)
    std::unique_ptr<VacationManagerPrivate> const d;
};
}
