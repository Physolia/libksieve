/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

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

#ifndef SIEVESCRIPTDEBUGGERWIDGET_H
#define SIEVESCRIPTDEBUGGERWIDGET_H

#include <QWidget>
#include "ksieveui_export.h"
class QStackedWidget;
class QLabel;
namespace KSieveUi {
class SieveScriptDebuggerFrontEndWidget;
/**
 * @brief The SieveScriptDebuggerWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class KSIEVEUI_EXPORT SieveScriptDebuggerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SieveScriptDebuggerWidget(QWidget *parent = nullptr);
    ~SieveScriptDebuggerWidget();

    void setScript(const QString &script);
    Q_REQUIRED_RESULT QString script() const;

    bool canAccept() const;

    QList<int> splitterSizes() const;
    void setSplitterSizes(const QList<int> &sizes);

    Q_REQUIRED_RESULT bool haveDebugApps() const;

Q_SIGNALS:
    void scriptTextChanged();
    void debugScriptButtonClicked();
    void debugButtonEnabled(bool state);
    void sieveTestNotFound();

private:
    void checkSieveTestApplication();
    QStackedWidget *mStackedWidget = nullptr;
    SieveScriptDebuggerFrontEndWidget *mSieveScriptFrontEnd = nullptr;
    QLabel *mSieveNoExistingFrontEnd = nullptr;
    bool mHaveDebugApps = false;
};
}
#endif // SIEVESCRIPTDEBUGGERWIDGET_H
