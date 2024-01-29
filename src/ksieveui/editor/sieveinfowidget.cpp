/*
  SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "sieveinfowidget.h"

#include <KLocalizedString>

#include <QHBoxLayout>
#include <QTextEdit>

using namespace KSieveUi;
SieveInfoWidget::SieveInfoWidget(QWidget *parent)
    : QWidget(parent)
    , mInfo(new QTextEdit(this))
{
    auto lay = new QHBoxLayout(this);
    lay->setContentsMargins({});
    mInfo->setReadOnly(true);
    mInfo->setAcceptRichText(true);
    lay->addWidget(mInfo);
}

SieveInfoWidget::~SieveInfoWidget() = default;

void SieveInfoWidget::setServerInfo(QStringList serverInfos)
{
    serverInfos.sort();
    QString result = QLatin1StringView("<qt><b>") + i18n("Sieve server supports:") + QLatin1String("</b><ul>");
    for (const QString &info : std::as_const(serverInfos)) {
        result += QLatin1StringView("<li>") + info;
    }
    result += QLatin1StringView("</ul></qt>");
    mInfo->setHtml(result);
}

#include "moc_sieveinfowidget.cpp"
