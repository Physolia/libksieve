/*
   Copyright (C) 2013-2018 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef VACATIONUTILS_H
#define VACATIONUTILS_H
#include <QString>
#include <kmime/kmime_header_parsing.h>

class QDate;

namespace KSieveUi {
namespace VacationUtils {
enum MailAction {
    Keep,
    Discard,
    Sendto,
    CopyTo,
};

QString defaultMessageText();
QString defaultSubject();
MailAction defaultMailAction();
int defaultNotificationInterval();
KMime::Types::AddrSpecList defaultMailAliases();
bool defaultSendForSpam();
QString defaultDomainName();
QDate defaultStartDate();
QDate defaultEndDate();

struct Vacation {
    Vacation()
        : notificationInterval(1)
        , mailAction(Keep)
        , valid(false)
        , active(false)
        , sendForSpam(true)
    {
    }

    bool isValid() const
    {
        return valid;
    }

    QString mailActionRecipient;
    QString messageText;
    QString subject;
    KMime::Types::AddrSpecList aliases;
    QString reactOndomainName;
    QDate startDate;
    QTime startTime;
    QDate endDate;
    QTime endTime;
    int notificationInterval;
    MailAction mailAction;
    bool valid;
    bool active;
    bool sendForSpam;
};

Q_REQUIRED_RESULT QString composeScript(const Vacation &vacation);

Q_REQUIRED_RESULT KSieveUi::VacationUtils::Vacation parseScript(const QString &script);

Q_REQUIRED_RESULT QString mergeRequireLine(const QString &script, const QString &scriptUpdate);

Q_REQUIRED_RESULT QString updateVacationBlock(const QString &oldScript, const QString &newScript);

Q_REQUIRED_RESULT QString mailAction(MailAction action);
}
}

#endif // VACATIONUTILS_H
