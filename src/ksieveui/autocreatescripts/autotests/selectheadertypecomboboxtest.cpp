/*
   Copyright (C) 2016 Laurent Montel <montel@kde.org>

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

#include "selectheadertypecomboboxtest.h"
#include "../sieveconditions/widgets/selectheadertypecombobox.h"

#include <QTest>

SelectHeaderTypeComboBoxTest::SelectHeaderTypeComboBoxTest(QObject *parent)
    : QObject(parent)
{

}

SelectHeaderTypeComboBoxTest::~SelectHeaderTypeComboBoxTest()
{

}

void SelectHeaderTypeComboBoxTest::shouldHaveDefaultValue()
{
    KSieveUi::SelectHeaderTypeComboBox combox;
    QVERIFY(combox.isEditable());
    QVERIFY(combox.count() > 0);

    KSieveUi::SelectHeaderTypeComboBox combox1(true); /*onlyEnvelopType*/
    QVERIFY(combox1.isEditable());
    QVERIFY(combox1.count() > 0);

}

QTEST_MAIN(SelectHeaderTypeComboBoxTest)
