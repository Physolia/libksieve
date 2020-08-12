/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef SIEVETEXTEDITWIDGETTEST_H
#define SIEVETEXTEDITWIDGETTEST_H

#include <QObject>

class SieveTextEditWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit SieveTextEditWidgetTest(QObject *parent = nullptr);
    ~SieveTextEditWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // SIEVETEXTEDITWIDGETTEST_H
