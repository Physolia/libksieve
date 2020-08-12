/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SIEVESCRIPTDEBUGGERFRONTENDWIDGETTEST_H
#define SIEVESCRIPTDEBUGGERFRONTENDWIDGETTEST_H

#include <QObject>

class SieveScriptDebuggerFrontEndWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit SieveScriptDebuggerFrontEndWidgetTest(QObject *parent = nullptr);
    ~SieveScriptDebuggerFrontEndWidgetTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldChangeButtonEnabledState();
    void shouldAddScript();
    void shouldNotAccept();
};

#endif // SIEVESCRIPTDEBUGGERFRONTENDWIDGETTEST_H
