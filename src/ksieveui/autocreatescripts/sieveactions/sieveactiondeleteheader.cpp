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
#include "sieveactiondeleteheader.h"
#include "autocreatescripts/autocreatescriptutil_p.h"
#include "autocreatescripts/commonwidgets/selectmatchtypecombobox.h"
#include "editor/sieveeditorutil.h"

#include <KLocalizedString>
#include <QLineEdit>

#include <QWidget>
#include <QLabel>
#include <QDomNode>
#include "libksieve_debug.h"
#include <QGridLayout>

using namespace KSieveUi;

SieveActionDeleteHeader::SieveActionDeleteHeader(SieveEditorGraphicalModeWidget *sieveGraphicalModeWidget, QObject *parent)
    : SieveActionAbstractEditHeader(sieveGraphicalModeWidget, QStringLiteral("deleteheader"), i18n("Delete header"), parent)
{
}

QWidget *SieveActionDeleteHeader::createParamWidget(QWidget *parent) const
{
    QWidget *w = new QWidget(parent);
    QGridLayout *grid = new QGridLayout;
    grid->setMargin(0);
    w->setLayout(grid);

    SelectMatchTypeComboBox *matchType = new SelectMatchTypeComboBox(mSieveGraphicalModeWidget);
    matchType->setObjectName(QStringLiteral("matchtype"));
    connect(matchType, &SelectMatchTypeComboBox::valueChanged, this, &SieveActionDeleteHeader::valueChanged);
    grid->addWidget(matchType, 0, 0);

    QLabel *lab = new QLabel(i18n("header:"));
    grid->addWidget(lab, 0, 1);

    QLineEdit *headerEdit = new QLineEdit;
    headerEdit->setObjectName(QStringLiteral("headeredit"));
    connect(headerEdit, &QLineEdit::textChanged, this, &SieveActionDeleteHeader::valueChanged);
    grid->addWidget(headerEdit, 0, 2);

    lab = new QLabel(i18n("value:"));
    grid->addWidget(lab, 1, 1);

    QLineEdit *valueEdit = new QLineEdit;
    valueEdit->setObjectName(QStringLiteral("valueedit"));
    connect(valueEdit, &QLineEdit::textChanged, this, &SieveActionDeleteHeader::valueChanged);
    grid->addWidget(valueEdit, 1, 2);
    return w;
}

bool SieveActionDeleteHeader::parseValue(const QDomElement &element, QWidget *w, QString &error, bool isNegative)
{
    int index = 0;
    QDomNode node = element.firstChild();
    while (!node.isNull()) {
        QDomElement e = node.toElement();
        if (!e.isNull()) {
            const QString tagName = e.tagName();
            if (tagName == QLatin1String("test")) {
                const QDomNode testNode = e.toElement();
                const QString nameValue = e.attribute(QStringLiteral("name"), QString());
                const bool isNegative = (nameValue == QLatin1String("not"));
                return parseValue(testNode.toElement(), w, error, isNegative);
            } else if (tagName == QLatin1String("tag")) {
                SelectMatchTypeComboBox *combo = w->findChild<SelectMatchTypeComboBox *>(QStringLiteral("matchtype"));
                combo->setCode(AutoCreateScriptUtil::tagValueWithCondition(e.text(), isNegative), name(), error);
            } else if (tagName == QLatin1String("str")) {
                if (index == 0) {
                    QLineEdit *edit = w->findChild<QLineEdit *>(QStringLiteral("headeredit"));
                    edit->setText(e.text());
                } else if (index == 1) {
                    QLineEdit *value = w->findChild<QLineEdit *>(QStringLiteral("valueedit"));
                    value->setText(e.text());
                } else {
                    tooManyArgument(tagName, index, 2, error);
                    qCDebug(LIBKSIEVE_LOG) << " SieveActionAddHeader::setParamWidgetValue too many argument :" << index;
                }
                ++index;
            } else if (tagName == QLatin1String("crlf")) {
                //nothing
            } else if (tagName == QLatin1String("comment")) {
                //implement in the future ?
            } else {
                unknownTag(tagName, error);
                qCDebug(LIBKSIEVE_LOG) << "SieveActionAddHeader::setParamWidgetValue unknown tag " << tagName;
            }
        }
        node = node.nextSibling();
    }
    return true;
}

bool SieveActionDeleteHeader::setParamWidgetValue(const QDomElement &element, QWidget *w, QString &error)
{
    return parseValue(element, w, error, false);
}

QString SieveActionDeleteHeader::code(QWidget *w) const
{
    const SelectMatchTypeComboBox *combo = w->findChild<SelectMatchTypeComboBox *>(QStringLiteral("matchtype"));
    bool isNegative = false;
    const QString matchTypeStr = combo->code(isNegative);

    const QLineEdit *edit = w->findChild<QLineEdit *>(QStringLiteral("headeredit"));
    const QString headerStr = edit->text();

    const QLineEdit *value = w->findChild<QLineEdit *>(QStringLiteral("valueedit"));
    const QString valueStr = value->text();

    return QStringLiteral("deleteheader %1 \"%2\" \"%3\";").arg((isNegative ? QLatin1String("not ") + matchTypeStr : matchTypeStr), headerStr, valueStr);
}

QString SieveActionDeleteHeader::help() const
{
    return i18n("By default, the deleteheader action deletes all occurrences of the named header field.");
}

QUrl SieveActionDeleteHeader::href() const
{
    return SieveEditorUtil::helpUrl(SieveEditorUtil::strToVariableName(name()));
}
