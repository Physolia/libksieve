/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef VACATIONMANAGER_H
#define VACATIONMANAGER_H

#include <QObject>
#include "ksieveui_export.h"

class QWidget;
namespace KSieveUi {
class VacationManagerPrivate;
class SieveImapPasswordProvider;
/**
 * @brief The VacationManager class
 * @author Laurent Montel <montel@kde.org>
 */
class KSIEVEUI_EXPORT VacationManager : public QObject
{
    Q_OBJECT
public:
    explicit VacationManager(SieveImapPasswordProvider *passwordProvider, QWidget *parent);
    ~VacationManager() override;

    void checkVacation();

public Q_SLOTS:
    void slotEditVacation(const QString &serverName);

Q_SIGNALS:
    void updateVacationScriptStatus(bool active, const QString &serverName);

private:
    void slotDialogCanceled();
    void slotDialogOk();
    void slotUpdateVacationScriptStatus(bool active, const QString &serverName);

private:
    Q_DISABLE_COPY(VacationManager)
    VacationManagerPrivate *const d;
};
}

#endif // VACATIONMANAGER_H
