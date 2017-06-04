/*
   Copyright (C) 2013-2017 Laurent Montel <montel@kde.org>

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
#ifndef SieveActionEReject_H
#define SieveActionEReject_H

#include "sieveaction.h"
namespace KSieveUi {
class SieveActionEReject : public SieveAction
{
    Q_OBJECT
public:
    explicit SieveActionEReject(SieveEditorGraphicalModeWidget *sieveGraphicalModeWidget, QObject *parent = nullptr);

    QWidget *createParamWidget(QWidget *parent) const override;
    QString code(QWidget *) const override;
    QStringList needRequires(QWidget *parent) const override;
    bool setParamWidgetValue(const QDomElement &element, QWidget *parent, QString &error) override;

    bool needCheckIfServerHasCapability() const override;

    QString serverNeedsCapability() const override;
    QString help() const override;
    QUrl href() const override;
};
}

#endif // SieveActionEReject_H
