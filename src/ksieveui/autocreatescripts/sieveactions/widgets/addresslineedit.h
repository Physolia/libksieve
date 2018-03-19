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
#ifndef ADDRESSLINEEDIT_H
#define ADDRESSLINEEDIT_H

#include <QLineEdit>
#include <KSieveUi/AbstractSelectEmailLineEdit>
namespace KSieveUi {
class AddressLineEdit : public AbstractSelectEmailLineEdit
{
    Q_OBJECT
public:
    explicit AddressLineEdit(QWidget *parent = nullptr);
    ~AddressLineEdit() override;

    void setText(const QString &str) override;
    QString text() const override;

Q_SIGNALS:
    void valueChanged();

protected:
    void focusOutEvent(QFocusEvent *ev) override;

private:
    void slotTextChanged();
    void verifyAddress();
    QLineEdit *mLineEdit = nullptr;
    QString mNegativeBackground;
    bool mIncorrectEmail = false;
};
}

#endif // ADDRESSLINEEDIT_H
