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

#include "autocreatescriptutil_p.h"

#include <KLocalizedString>

#include <KPluginLoader>
#include <KPluginFactory>
#include <QStringList>
#include <QRegularExpression>

#include "autocreatescripts/sieveconditions/widgets/regexpeditorlineedit.h"
using namespace KSieveUi;

QString AutoCreateScriptUtil::createMultiLine(const QString &str)
{
    const QString result = QStringLiteral("\n%1\n.\n;\n").arg(str);
    return result;
}

QString AutoCreateScriptUtil::createList(const QString &str, QChar separator, bool addEndSemiColon)
{
    const QStringList list = str.trimmed().split(separator);
    const int count = list.count();
    switch (count) {
    case 0:
        return QString();
    case 1:
        return QLatin1String("\"") + list.first() + QLatin1String("\"");
    default:
    {
        const QString result = createList(list, addEndSemiColon);
        return result;
    }
    }
}

QString AutoCreateScriptUtil::quoteStr(const QString &str, bool protectSlash)
{
    QString st = str;
    if (protectSlash) {
        st = AutoCreateScriptUtil::protectSlash(str);
    }
    return st.replace(QLatin1String("\""), QStringLiteral("\\\""));
}

QString AutoCreateScriptUtil::protectSlash(QString str)
{
    return str.replace(QLatin1Char('\\'), QStringLiteral("\\\\"));
}

QString AutoCreateScriptUtil::createList(const QStringList &lst, bool addSemiColon, bool protectSlash)
{
    QString result;
    result = QLatin1Char('[');
    bool wasFirst = true;
    for (QString str : lst) {
        if (protectSlash) {
            str = AutoCreateScriptUtil::protectSlash(str);
        }
        result += (wasFirst ? QString() : QStringLiteral(",")) + QStringLiteral(" \"%1\"").arg(quoteStr(str, false));
        wasFirst = false;
    }
    result += QLatin1String(" ]");
    if (addSemiColon) {
        result += QLatin1Char(';');
    }

    return result;
}

QStringList AutoCreateScriptUtil::createListFromString(QString str)
{
    QStringList lst;
    if (str.startsWith(QLatin1Char('[')) && str.endsWith(QLatin1String("];"))) {
        str.remove(0, 1);
        str.remove(str.length() - 2, 2);
    } else if (str.startsWith(QLatin1Char('[')) && str.endsWith(QLatin1String("]"))) {
        str.remove(0, 1);
        str.remove(str.length() - 1, 1);
    } else {
        return lst;
    }
    lst = str.split(QStringLiteral(", "));
    QStringList resultLst;
    resultLst.reserve(lst.count());
    for (QString s : qAsConst(lst)) {
        s.remove(QLatin1Char('"'));
        resultLst << s.trimmed();
    }
    lst = resultLst;
    return lst;
}

QString AutoCreateScriptUtil::createAddressList(const QString &str, bool addSemiColon)
{
    if (str.trimmed().startsWith(QLatin1Char('[')) && str.trimmed().endsWith(QLatin1Char(']'))) {
        return str;
    }
    return createList(str, QLatin1Char(';'), addSemiColon);
}

QString AutoCreateScriptUtil::negativeString(bool isNegative)
{
    return isNegative ? QStringLiteral("not ") : QString();
}

QString AutoCreateScriptUtil::tagValueWithCondition(const QString &tag, bool notCondition)
{
    return (notCondition ? QStringLiteral("[NOT]") : QString()) + QLatin1Char(':') + tag;
}

QString AutoCreateScriptUtil::tagValue(const QString &tag)
{
    return QLatin1Char(':') + tag;
}

QString AutoCreateScriptUtil::strValue(QXmlStreamReader &element)
{
    if (element.readNextStartElement()) {
        const QStringRef textElementTagName = element.name();
        if (textElementTagName == QLatin1String("str")) {
            return element.readElementText();
        } else {
            element.skipCurrentElement();
        }
    }
    return QString();
}

QString AutoCreateScriptUtil::listValueToStr(QXmlStreamReader &element)
{
    const QStringList lst = AutoCreateScriptUtil::listValue(element);
    //Don't add semicolon
    return createList(lst, false);
}

QStringList AutoCreateScriptUtil::listValue(QXmlStreamReader &element)
{
    QStringList lst;
    while (element.readNextStartElement()) {
        const QStringRef tagName = element.name();
        if (tagName == QLatin1String("str")) {
            lst << element.readElementText();
        } else {
            element.skipCurrentElement();
        }
    }
    return lst;
}

QString AutoCreateScriptUtil::fixListValue(QString valueStr)
{
    if (!(valueStr.startsWith(QLatin1Char('[')) && valueStr.endsWith(QLatin1Char(']')))) {
        valueStr = QStringLiteral("\"%1\"").arg(valueStr);
    } else if (valueStr.contains(QRegularExpression(QStringLiteral("^\\[\\s*\".*\"\\s*]$")))) {
    } else {
        valueStr = QStringLiteral("\"%1\"").arg(valueStr);
    }

    return valueStr;
}

void AutoCreateScriptUtil::comboboxItemNotFound(const QString &searchItem, const QString &name, QString &error)
{
    error += i18n("Cannot find item \"%1\" in widget \"%2\"", searchItem, name) + QLatin1Char('\n');
}

QString AutoCreateScriptUtil::createFullWhatsThis(const QString &help, const QString &href)
{
    if (href.isEmpty()) {
        return help;
    }
    const QString fullWhatsThis = QLatin1String("<qt>") + help + QStringLiteral("<br><a href=\'%1\'>%2</a></qt>").arg(href, i18n("More information"));
    return fullWhatsThis;
}

QString AutoCreateScriptUtil::indentation()
{
    return QStringLiteral("    ");
}

AbstractRegexpEditorLineEdit *AutoCreateScriptUtil::createRegexpEditorLineEdit(QWidget *parent)
{
    KSieveUi::AbstractRegexpEditorLineEdit *edit = nullptr;
    KPluginLoader loader(QStringLiteral("libksieve/regexpeditorlineeditplugin"));
    KPluginFactory *factory = loader.factory();
    if (factory) {
        edit = factory->create<KSieveUi::AbstractRegexpEditorLineEdit>(parent);
    } else {
        edit = new KSieveUi::RegexpEditorLineEdit(parent);
    }
    return edit;
}

QString AutoCreateScriptUtil::generateConditionComment(const QString &comment)
{
    QString strComment;
    if (!comment.trimmed().isEmpty()) {
        const QVector<QStringRef> commentList = comment.splitRef(QLatin1Char('\n'));

        for (const QStringRef &str : commentList) {
            if (str.isEmpty()) {
                strComment += QLatin1Char('\n');
            } else {
                if (!strComment.isEmpty()) {
                    strComment += QLatin1Char('\n');
                }
                strComment += QStringLiteral(" #") + str;
            }
        }
    }
    return strComment;
}

QString AutoCreateScriptUtil::loadConditionComment(QString originalComment, const QString &comment)
{
    if (originalComment.isEmpty()) {
        originalComment = comment;
    } else {
        originalComment += QLatin1Char('\n') + comment;
    }
    return originalComment;
}
