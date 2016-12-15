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

#include "moveimapfolderwidget.h"
#include <QLineEdit>
#include <QHBoxLayout>
using namespace KSieveUi;

MoveImapFolderWidget::MoveImapFolderWidget(QWidget *parent)
    : KSieveUi::AbstractMoveImapFolderWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);
    mLineEdit = new QLineEdit(this);
    mLineEdit->setObjectName(QStringLiteral("lineedit"));
    mainLayout->addWidget(mLineEdit);
    connect(mLineEdit, &QLineEdit::textChanged, this, &MoveImapFolderWidget::textChanged);
}

MoveImapFolderWidget::~MoveImapFolderWidget()
{

}

void MoveImapFolderWidget::setText(const QString &str)
{
    mLineEdit->setText(str);
}

QString MoveImapFolderWidget::text() const
{
    return mLineEdit->text();
}

void MoveImapFolderWidget::setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account)
{
    Q_UNUSED(account);
}

