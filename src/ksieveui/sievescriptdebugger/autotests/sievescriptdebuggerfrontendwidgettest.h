/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class SieveScriptDebuggerFrontEndWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit SieveScriptDebuggerFrontEndWidgetTest(QObject *parent = nullptr);
    ~SieveScriptDebuggerFrontEndWidgetTest() override;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldChangeButtonEnabledState();
    void shouldAddScript();
    void shouldNotAccept();
};
