/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SIEVEIMAPINSTANCEINTERFACEMANAGERTEST_H
#define SIEVEIMAPINSTANCEINTERFACEMANAGERTEST_H

#include <QObject>

class SieveImapInstanceInterfaceManagerTest : public QObject
{
    Q_OBJECT
public:
    explicit SieveImapInstanceInterfaceManagerTest(QObject *parent = nullptr);
    ~SieveImapInstanceInterfaceManagerTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignSieveImapInstanceInterface();
};

#endif // SIEVEIMAPINSTANCEINTERFACEMANAGERTEST_H
