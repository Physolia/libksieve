/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef SIEVETEXTEDITTEST_H
#define SIEVETEXTEDITTEST_H

#include <QObject>

class SieveTextEditTest : public QObject
{
    Q_OBJECT
public:
    explicit SieveTextEditTest(QObject *parent = nullptr);
    ~SieveTextEditTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void comment_data();
    void comment();

    void uncomment_data();
    void uncomment();
};

#endif // SIEVETEXTEDITTEST_H
