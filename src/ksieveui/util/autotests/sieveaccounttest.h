/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SIEVEACCOUNTTEST_H
#define SIEVEACCOUNTTEST_H

#include <QObject>

class SieveAccountTest : public QObject
{
    Q_OBJECT
public:
    explicit SieveAccountTest(QObject *parent = nullptr);
    ~SieveAccountTest();

private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignValue();
    void shouldBeEqual();

    void shouldCreateIdentifier();
    void shouldCreateIdentifier_data();
};

#endif // SIEVEACCOUNTTEST_H
