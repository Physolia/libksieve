/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "sievecondition.h"

namespace KSieveUi
{
class SieveConditionFalse : public SieveCondition
{
    Q_OBJECT
public:
    explicit SieveConditionFalse(SieveEditorGraphicalModeWidget *sieveGraphicalModeWidget, QObject *parent = nullptr);
    [[nodiscard]] QWidget *createParamWidget(QWidget *parent) const override;

    [[nodiscard]] QString code(QWidget *w) const override;
    [[nodiscard]] QString help() const override;
    void setParamWidgetValue(QXmlStreamReader &element, QWidget *parent, bool notCondition, QString &error) override;
    [[nodiscard]] QUrl href() const override;
};
}
