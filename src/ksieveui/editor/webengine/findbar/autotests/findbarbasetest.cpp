/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "findbarbasetest.h"
#include "../findbarbase.h"

#include <PimCommon/LineEditWithCompleterNg>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QTest>
#include <QSignalSpy>

FindBarBaseTest::FindBarBaseTest(QObject *parent)
    : QObject(parent)
{
}

FindBarBaseTest::~FindBarBaseTest()
{
}

void FindBarBaseTest::shouldHaveDefaultValue()
{
    KSieveUi::FindBarBase bar;
    QLabel *status = bar.findChild<QLabel *>(QStringLiteral("status"));
    QVERIFY(status);
    QVERIFY(status->text().isEmpty());

    QPushButton *previous = bar.findChild<QPushButton *>(QStringLiteral("findprevious"));
    QVERIFY(previous);
    QVERIFY(!previous->isEnabled());

    QPushButton *next = bar.findChild<QPushButton *>(QStringLiteral("findnext"));
    QVERIFY(next);
    QVERIFY(!next->isEnabled());

    QToolButton *close = bar.findChild<QToolButton *>(QStringLiteral("close"));
    QVERIFY(close);

    PimCommon::LineEditWithCompleterNg *lineedit = bar.findChild<PimCommon::LineEditWithCompleterNg *>(QStringLiteral("searchline"));
    QVERIFY(lineedit);
    QVERIFY(lineedit->text().isEmpty());
}

void FindBarBaseTest::shouldClearLineWhenClose()
{
    KSieveUi::FindBarBase bar;
    bar.show();
    QSignalSpy spy(&bar, &KSieveUi::FindBarBase::hideFindBar);
    QVERIFY(QTest::qWaitForWindowExposed(&bar));
    QVERIFY(bar.isVisible());
    bar.focusAndSetCursor();
    PimCommon::LineEditWithCompleterNg *lineedit = bar.findChild<PimCommon::LineEditWithCompleterNg *>(QStringLiteral("searchline"));
    lineedit->setText(QStringLiteral("FOO"));
    QVERIFY(!lineedit->text().isEmpty());
    QVERIFY(lineedit->hasFocus());
    bar.closeBar();
    QVERIFY(lineedit->text().isEmpty());
    QVERIFY(!lineedit->hasFocus());
    QCOMPARE(spy.count(), 1);
}

void FindBarBaseTest::shouldEnableDisableNextPreviousButton()
{
    KSieveUi::FindBarBase bar;
    bar.show();
    QVERIFY(QTest::qWaitForWindowExposed(&bar));
    QPushButton *previous = bar.findChild<QPushButton *>(QStringLiteral("findprevious"));

    QPushButton *next = bar.findChild<QPushButton *>(QStringLiteral("findnext"));

    bar.autoSearch(QStringLiteral("FOO"));
    QVERIFY(next->isEnabled());
    QVERIFY(previous->isEnabled());

    bar.autoSearch(QString());
    QVERIFY(!next->isEnabled());
    QVERIFY(!previous->isEnabled());
}

void FindBarBaseTest::shouldClearAllWhenShowBar()
{
    KSieveUi::FindBarBase bar;
    bar.show();
    QVERIFY(QTest::qWaitForWindowExposed(&bar));
    QLabel *status = bar.findChild<QLabel *>(QStringLiteral("status"));
    status->setText(QStringLiteral("FOO"));
    bar.closeBar();

    bar.show();
    bar.focusAndSetCursor();
    PimCommon::LineEditWithCompleterNg *lineedit = bar.findChild<PimCommon::LineEditWithCompleterNg *>(QStringLiteral("searchline"));
    QVERIFY(lineedit->hasFocus());
    QVERIFY(status->text().isEmpty());
}

QTEST_MAIN(FindBarBaseTest)
