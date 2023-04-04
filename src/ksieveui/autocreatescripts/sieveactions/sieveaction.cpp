/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "sieveaction.h"
#include "libksieve_debug.h"

#include <KLocalizedString>

#include "autocreatescripts/sieveeditorgraphicalmodewidget.h"
#include <QWidget>
#include <QXmlStreamReader>

using namespace KSieveUi;

SieveAction::SieveAction(SieveEditorGraphicalModeWidget *sieveGraphicalModeWidget, const QString &name, const QString &label, QObject *parent)
    : SieveCommonActionCondition(sieveGraphicalModeWidget, name, label, parent)
{
}

SieveAction::~SieveAction() = default;

QStringList SieveAction::listOfIncludeFile() const
{
    if (mSieveGraphicalModeWidget) {
        return mSieveGraphicalModeWidget->listOfIncludeFile();
    }
    qCWarning(LIBKSIEVE_LOG) << "SieveAction::listOfIncludeFile Problem during initialize mSieveGraphicalModeWidget ";
    return {};
}

void SieveAction::setParamWidgetValue(QXmlStreamReader &n, QWidget *, QString &)
{
    n.skipCurrentElement();
}
void SieveAction::unknownTag(const QStringView &tag, QString &error)
{
    const QString result = tag.toString();
    error += i18n("An unknown tag \"%1\" was found during parsing action \"%2\".", result, name()) + QLatin1Char('\n');
}

void SieveAction::tooManyArguments(const QStringView &tagName, int index, int maxValue, QString &error)
{
    const QString result = tagName.toString();

    error += i18n("Too many arguments found for \"%1\", max value is %2, number of value found %3 for %4", name(), maxValue, index, result) + QLatin1Char('\n');
}

void SieveAction::unknownTagValue(const QString &tagValue, QString &error)
{
    error += i18n("An unknown tag value \"%1\" was found during parsing action \"%2\".", tagValue, name()) + QLatin1Char('\n');
}

void SieveAction::serverDoesNotSupportFeatures(const QString &feature, QString &error)
{
    error += i18n("A feature \"%1\" in condition \"%2\" is not supported by server", feature, name()) + QLatin1Char('\n');
}
