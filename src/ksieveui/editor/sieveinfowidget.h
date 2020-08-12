/*
  SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef SIEVEINFOWIDGET_H
#define SIEVEINFOWIDGET_H

#include <QWidget>
#include "ksieveui_export.h"
class QTextEdit;

namespace KSieveUi {
class KSIEVEUI_EXPORT SieveInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SieveInfoWidget(QWidget *parent = nullptr);
    ~SieveInfoWidget();

    void setServerInfo(QStringList info);

private:
    QTextEdit *mInfo = nullptr;
};
}

#endif // SIEVEINFOWIDGET_H
