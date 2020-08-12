/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef SELECTVARIABLEMODIFIERCOMBOBOX_H
#define SELECTVARIABLEMODIFIERCOMBOBOX_H

#include <QComboBox>

namespace KSieveUi {
class SelectVariableModifierComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SelectVariableModifierComboBox(QWidget *parent = nullptr);
    ~SelectVariableModifierComboBox();

    Q_REQUIRED_RESULT QString code() const;
    void setCode(const QString &code, const QString &name, QString &error);

Q_SIGNALS:
    void valueChanged();

private:
    void initialize();
};
}

#endif // SELECTVARIABLEMODIFIERCOMBOBOX_H
