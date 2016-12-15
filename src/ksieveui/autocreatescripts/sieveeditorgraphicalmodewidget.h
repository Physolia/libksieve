/*
   Copyright (C) 2013-2016 Laurent Montel <montel@kde.org>

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

#ifndef SIEVEEDITORGRAPHICALMODEWIDGET_H
#define SIEVEEDITORGRAPHICALMODEWIDGET_H

#include "editor/sieveeditorabstractwidget.h"
#include "util/sieveimapaccountsettings.h"
class QSplitter;
class QStackedWidget;
class QDomDocument;

namespace KSieveUi
{
class SieveScriptPage;
class SieveScriptListBox;
class SieveEditorParsingMissingFeatureWarning;
class SieveEditorGraphicalModeWidget : public SieveEditorAbstractWidget
{
    Q_OBJECT
public:
    explicit SieveEditorGraphicalModeWidget(QWidget *parent = Q_NULLPTR);
    ~SieveEditorGraphicalModeWidget();

    QString script(QString &requires) const;

    void setSieveCapabilities(const QStringList &capabilities);
    QStringList sieveCapabilities();

    void setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &sieveAccount);
    KSieveUi::SieveImapAccountSettings sieveAccount() const;

    void loadScript(const QDomDocument &doc, QString &error);

    QString currentscript() Q_DECL_OVERRIDE;
    void setImportScript(const QString &) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void enableButtonOk(bool);
    void switchTextMode(const QString &script);
    void valueChanged();

private:
    void readConfig();
    void writeConfig();

private Q_SLOTS:
    void slotSwitchToTextMode();
    void slotAddScriptPage(KSieveUi::SieveScriptPage *page);
    void slotRemoveScriptPage(QWidget *page);
    void slotActivateScriptPage(QWidget *page);

private:
    KSieveUi::SieveImapAccountSettings mSieveImapAccountSettings;
    QStringList mCapabilities;
    SieveScriptListBox *mSieveScript;
    QStackedWidget *mStackWidget;
    QSplitter *mSplitter;
    SieveEditorParsingMissingFeatureWarning *mSieveParsingWarning;
};
}

#endif // SIEVEEDITORGRAPHICALMODEWIDGET_H
