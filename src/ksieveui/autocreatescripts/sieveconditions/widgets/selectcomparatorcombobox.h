/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SELECTCOMPARATORCOMBOBOX_H
#define SELECTCOMPARATORCOMBOBOX_H

#include <QComboBox>
namespace KSieveUi {
class SieveEditorGraphicalModeWidget;
class SelectComparatorComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SelectComparatorComboBox(KSieveUi::SieveEditorGraphicalModeWidget *sieveGraphicalModeWidget, QWidget *parent = nullptr);
    ~SelectComparatorComboBox();

    Q_REQUIRED_RESULT QString code() const;
    void setCode(const QString &code, const QString &name, QString &error);

    Q_REQUIRED_RESULT QString require() const;

Q_SIGNALS:
    void valueChanged();
private:
    void initialize(const QStringList &sieveCapabilities);
};
}
#endif // SELECTCOMPARATORCOMBOBOX_H
