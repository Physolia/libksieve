/*
  SPDX-FileCopyrightText: 2015-2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QObject>

class SieveEditorMenuBarTest : public QObject
{
    Q_OBJECT
public:
    explicit SieveEditorMenuBarTest(QObject *parent = nullptr);
    ~SieveEditorMenuBarTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldEmitSignals();
    void shouldDisableActions();
};
