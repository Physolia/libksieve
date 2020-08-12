/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef SELECTHEADERTYPECOMBOBOX_H
#define SELECTHEADERTYPECOMBOBOX_H

#include <QComboBox>
#include <QDialog>

#include <QListWidget>

class QLineEdit;
class QPushButton;
namespace KSieveUi {
class SelectHeadersWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit SelectHeadersWidget(QWidget *parent = nullptr);
    ~SelectHeadersWidget();

    Q_REQUIRED_RESULT QString headers() const;
    void setListHeaders(const QMap<QString, QString> &lst, const QStringList &selectedHeaders);
    void addNewHeader(const QString &header);
private:
    enum HeaderEnum {
        HeaderId = Qt::UserRole + 1
    };

    void init();
};

class SelectHeadersDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectHeadersDialog(QWidget *parent = nullptr);
    ~SelectHeadersDialog();

    Q_REQUIRED_RESULT QString headers() const;
    void setListHeaders(const QMap<QString, QString> &lst, const QStringList &selectedHeaders);

private:
    void slotNewHeaderTextChanged(const QString &text);
    void slotAddNewHeader();
    void readConfig();
    void writeConfig();
    SelectHeadersWidget *mListWidget = nullptr;
    QLineEdit *mNewHeader = nullptr;
    QPushButton *mAddNewHeader = nullptr;
};

class SelectHeaderTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SelectHeaderTypeComboBox(bool onlyEnvelopType = false, QWidget *parent = nullptr);
    ~SelectHeaderTypeComboBox();

    Q_REQUIRED_RESULT QString code() const;
    void setCode(const QString &code);

Q_SIGNALS:
    void valueChanged();

private Q_SLOTS:
    void slotSelectItem(const QString &str);

private:
    void initialize(bool onlyEnvelopType);
    void changeReadOnlyStatus();
    void headerMap(bool onlyEnvelopType);
    QMap<QString, QString> mHeaderMap;
    QString mCode;
};
}

#endif // SELECTHEADERTYPECOMBOBOX_H
