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

#ifndef SIEVEINCLUDEWIDGET_H
#define SIEVEINCLUDEWIDGET_H

#include "sievewidgetpageabstract.h"
#include <Libkdepim/KWidgetLister>
#include <KComboBox>

class QPushButton;
class QGridLayout;
class QCheckBox;
class QXmlStreamReader;
namespace KSieveUi {
class SieveHelpButton;
class IncludeFileLineEdit;
class SieveIncludeLocation : public KComboBox
{
    Q_OBJECT
public:
    explicit SieveIncludeLocation(QWidget *parent = nullptr);
    ~SieveIncludeLocation();

    Q_REQUIRED_RESULT QString code() const;
    void setCode(const QString &code, QString &error);

Q_SIGNALS:
    void valueChanged();

private:
    void initialize();
};

class SieveIncludeActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SieveIncludeActionWidget(QWidget *parent = nullptr);
    ~SieveIncludeActionWidget();

    void generatedScript(QString &script);
    void updateAddRemoveButton(bool addButtonEnabled, bool removeButtonEnabled);
    void loadScript(QXmlStreamReader &element, QString &error);
    Q_REQUIRED_RESULT bool isInitialized() const;
    void clear();
    void setListOfIncludeFile(const QStringList &listOfIncludeFile);

private Q_SLOTS:
    void slotAddWidget();
    void slotRemoveWidget();

Q_SIGNALS:
    void addWidget(QWidget *w);
    void removeWidget(QWidget *w);
    void valueChanged();

private:
    void initWidget();
    QPushButton *mAdd = nullptr;
    QPushButton *mRemove = nullptr;
    QGridLayout *mLayout = nullptr;
    QCheckBox *mOptional = nullptr;
    QCheckBox *mOnce = nullptr;
    SieveIncludeLocation *mLocation = nullptr;
    IncludeFileLineEdit *mIncludeFileName = nullptr;
};

class SieveIncludeWidgetLister : public KPIM::KWidgetLister
{
    Q_OBJECT
public:
    explicit SieveIncludeWidgetLister(QWidget *parent = nullptr);
    ~SieveIncludeWidgetLister() override;

    void generatedScript(QString &script, QStringList &requires);
    void loadScript(QXmlStreamReader &element, QString &error);

    void setListOfIncludeFile(const QStringList &listOfIncludeFile);

Q_SIGNALS:
    void valueChanged();

public Q_SLOTS:
    void slotAddWidget(QWidget *w);
    void slotRemoveWidget(QWidget *w);

protected:
    void clearWidget(QWidget *aWidget) override;
    QWidget *createWidget(QWidget *parent) override;
private:
    void reconnectWidget(SieveIncludeActionWidget *w);
    void updateAddRemoveButton();
    QStringList mListOfIncludeFile;
};

class SieveIncludeWidget : public SieveWidgetPageAbstract
{
    Q_OBJECT
public:
    explicit SieveIncludeWidget(QWidget *parent = nullptr);
    ~SieveIncludeWidget();

    void generatedScript(QString &script, QStringList &requires, bool inForEveryPartLoop) override;

    void loadScript(QXmlStreamReader &element, QString &error);

    void setListOfIncludeFile(const QStringList &lst);
private Q_SLOTS:
    void slotHelp();

private:
    SieveIncludeWidgetLister *mIncludeLister = nullptr;
    SieveHelpButton *mHelpButton = nullptr;
};
}

#endif // SIEVEINCLUDEWIDGET_H
