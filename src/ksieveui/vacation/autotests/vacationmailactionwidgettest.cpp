/*
   Copyright (C) 2017-2019 Laurent Montel <montel@kde.org>

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

#include "vacationmailactionwidgettest.h"
#include "../vacationmailactionwidget.h"
#include "kdepimtest_layout.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QStackedWidget>
#include <QTest>
#include <KSieveUi/AbstractMoveImapFolderWidget>
#include <ksieveui/abstractselectemaillineedit.h>

QTEST_MAIN(VacationMailActionWidgetTest)

VacationMailActionWidgetTest::VacationMailActionWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void VacationMailActionWidgetTest::shouldHaveDefaultValue()
{
    KSieveUi::VacationMailActionWidget w;

    QHBoxLayout *mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    KdepimTestLayout::checkContentsMargins(0, mainLayout);

    QStackedWidget *mStackedWidget = w.findChild<QStackedWidget *>(QStringLiteral("stackedWidget"));
    QVERIFY(mStackedWidget);

    QCOMPARE(mStackedWidget->count(), 3);
    QWidget *mMailActionRecipient = mStackedWidget->widget(0);
    QVERIFY(mMailActionRecipient);
    QCOMPARE(mMailActionRecipient->objectName(), QStringLiteral("mailActionRecipient"));
    QVERIFY(!mMailActionRecipient->isEnabled());

    QCOMPARE(mStackedWidget->currentIndex(), 0);

    QWidget *mMoveImapFolderWidget = mStackedWidget->widget(1);
    QVERIFY(mMoveImapFolderWidget);
    KSieveUi::AbstractMoveImapFolderWidget *abstractMoveImapFolderWidget = dynamic_cast<KSieveUi::AbstractMoveImapFolderWidget *>(mMoveImapFolderWidget);
    QVERIFY(abstractMoveImapFolderWidget);
    QCOMPARE(abstractMoveImapFolderWidget->objectName(), QStringLiteral("moveImapFolderWidget"));

    QWidget *mSelectEmailLineEdit = mStackedWidget->widget(2);
    QVERIFY(mSelectEmailLineEdit);

    KSieveUi::AbstractSelectEmailLineEdit *abstractSelectEmailWidget = dynamic_cast<KSieveUi::AbstractSelectEmailLineEdit *>(mSelectEmailLineEdit);
    QVERIFY(abstractSelectEmailWidget);
    QCOMPARE(abstractSelectEmailWidget->objectName(), QStringLiteral("selectEmailLineEdit"));

    bool ok;
    QVERIFY(w.mailActionRecipient(ok).isEmpty());
}

void VacationMailActionWidgetTest::shouldSwitchComponents()
{
    KSieveUi::VacationMailActionWidget w;
    QStackedWidget *mStackedWidget = w.findChild<QStackedWidget *>(QStringLiteral("stackedWidget"));

    w.mailActionChanged(KSieveUi::VacationUtils::Keep);
    QCOMPARE(mStackedWidget->currentIndex(), 0);
    bool ok;
    QVERIFY(w.mailActionRecipient(ok).isEmpty());
    QVERIFY(!w.isEnabled());

    w.mailActionChanged(KSieveUi::VacationUtils::CopyTo);
    QCOMPARE(mStackedWidget->currentIndex(), 1);
    QVERIFY(w.mailActionRecipient(ok).isEmpty());
    QVERIFY(w.isEnabled());

    w.mailActionChanged(KSieveUi::VacationUtils::Discard);
    QCOMPARE(mStackedWidget->currentIndex(), 0);
    QVERIFY(w.mailActionRecipient(ok).isEmpty());
    QVERIFY(!w.isEnabled());

    w.mailActionChanged(KSieveUi::VacationUtils::Sendto);
    QCOMPARE(mStackedWidget->currentIndex(), 2);
    QVERIFY(w.mailActionRecipient(ok).isEmpty());
    QVERIFY(w.isEnabled());
}
