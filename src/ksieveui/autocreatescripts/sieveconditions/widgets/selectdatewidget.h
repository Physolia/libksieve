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
#ifndef SELECTDATEWIDGET_H
#define SELECTDATEWIDGET_H

#include <QWidget>
#include <QSpinBox>

class KComboBox;
class QLineEdit;
class QStackedWidget;
class QSpinBox;
class KDateComboBox;
class KTimeComboBox;
namespace KSieveUi {

class SelectDateWidget : public QWidget
{
    Q_OBJECT
public:
    enum DateType {
        Year = 0,
        Month,
        Day,
        Date,
        Julian,
        Hour,
        Minute,
        Second,
        Time,
        Iso8601,
        Std11,
        Zone,
        Weekday
    };
    explicit SelectDateWidget(QWidget *parent = nullptr);
    ~SelectDateWidget();

    QString code() const;
    void setCode(const QString &type, const QString &value);

Q_SIGNALS:
    void valueChanged();

private Q_SLOTS:
    void slotDateTypeActivated(int);

private:
    SelectDateWidget::DateType dateTypeFromString(const QString &str);
    void initialize();
    QString dateType(DateType type) const;
    QString dateValue(DateType type) const;
    KComboBox *mDateType;
    QLineEdit *mDateLineEdit;
    QSpinBox *mDateValue;
    KDateComboBox *mDateEdit;
    KTimeComboBox *mTimeEdit;
    QStackedWidget *mStackWidget;
};

class SieveDateSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit SieveDateSpinBox(QWidget *parent = nullptr);
    ~SieveDateSpinBox();
    void setType(SelectDateWidget::DateType type);
private:
    SelectDateWidget::DateType mType;
};

}

#endif // SELECTDATEWIDGET_H
