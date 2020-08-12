/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef SELECTFLAGSWIDGET_H
#define SELECTFLAGSWIDGET_H

#include <QDialog>
#include <QListWidget>
class QLineEdit;

namespace KSieveUi {
class SelectFlagsListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit SelectFlagsListWidget(QWidget *parent = nullptr);
    ~SelectFlagsListWidget();

    void setFlags(const QStringList &list);
    Q_REQUIRED_RESULT QStringList flags() const;

private:
    enum Type {
        FlagsRealName = Qt::UserRole + 1
    };
    void init();
};

class SelectFlagsListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectFlagsListDialog(QWidget *parent = nullptr);
    ~SelectFlagsListDialog();

    void setFlags(const QStringList &list);
    Q_REQUIRED_RESULT QStringList flags() const;

private:
    void readConfig();
    void writeConfig();
    SelectFlagsListWidget *mListWidget = nullptr;
};

class SelectFlagsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectFlagsWidget(QWidget *parent = nullptr);
    ~SelectFlagsWidget();

    Q_REQUIRED_RESULT QString code() const;
    void setFlags(const QStringList &flags);

Q_SIGNALS:
    void valueChanged();

private:
    void slotSelectFlags();
    QLineEdit *mEdit = nullptr;
};
}

#endif // SELECTFLAGSWIDGET_H
