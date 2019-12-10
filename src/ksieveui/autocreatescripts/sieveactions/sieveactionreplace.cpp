/*
   Copyright (C) 2013-2019 Laurent Montel <montel@kde.org>

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
#include "sieveactionreplace.h"
#include "editor/sieveeditorutil.h"
#include "widgets/multilineedit.h"
#include "autocreatescripts/autocreatescriptutil_p.h"

#include <KLocalizedString>
#include <QLineEdit>

#include <QLabel>
#include <QXmlStreamReader>
#include "libksieve_debug.h"
#include <QGridLayout>

#include <KSieveUi/AbstractSelectEmailLineEdit>

using namespace KSieveUi;
SieveActionReplace::SieveActionReplace(SieveEditorGraphicalModeWidget *sieveGraphicalModeWidget, QObject *parent)
    : SieveAction(sieveGraphicalModeWidget, QStringLiteral("replace"), i18n("Replace"), parent)
{
}

QWidget *SieveActionReplace::createParamWidget(QWidget *parent) const
{
    QWidget *w = new QWidget(parent);
    QGridLayout *grid = new QGridLayout;
    grid->setContentsMargins(0, 0, 0, 0);
    w->setLayout(grid);

    QLabel *lab = new QLabel(i18n("Subject:"));
    grid->addWidget(lab, 0, 0);

    QLineEdit *subject = new QLineEdit;
    subject->setObjectName(QStringLiteral("subject"));
    connect(subject, &QLineEdit::textChanged, this, &SieveActionReplace::valueChanged);
    grid->addWidget(subject, 0, 1);

    lab = new QLabel(i18n("from:"));
    grid->addWidget(lab, 1, 0);

    KSieveUi::AbstractSelectEmailLineEdit *headers = AutoCreateScriptUtil::createSelectEmailsWidget();
    headers->setObjectName(QStringLiteral("from"));
    connect(headers, &AbstractSelectEmailLineEdit::valueChanged, this, &SieveActionReplace::valueChanged);
    grid->addWidget(headers, 1, 1);

    lab = new QLabel(i18n("text:"));
    grid->addWidget(lab, 2, 0);

    MultiLineEdit *text = new MultiLineEdit;
    text->setObjectName(QStringLiteral("text"));
    connect(text, &MultiLineEdit::textChanged, this, &SieveActionReplace::valueChanged);
    grid->addWidget(text, 2, 1);

    return w;
}

bool SieveActionReplace::setParamWidgetValue(QXmlStreamReader &element, QWidget *w, QString &error)
{
    while (element.readNextStartElement()) {
        const QStringRef tagName = element.name();
        if (tagName == QLatin1String("str")) {
            MultiLineEdit *edit = w->findChild<MultiLineEdit *>(QStringLiteral("text"));
            edit->setPlainText(element.readElementText());
        } else if (tagName == QLatin1String("tag")) {
            const QString tagValue = element.readElementText();
            if (tagValue == QLatin1String("subject")) {
                const QString strValue = AutoCreateScriptUtil::strValue(element);
                if (!strValue.isEmpty()) {
                    QLineEdit *subject = w->findChild<QLineEdit *>(QStringLiteral("subject"));
                    subject->setText(strValue);
                }
            } else if (tagValue == QLatin1String("from")) {
                const QString strValue = AutoCreateScriptUtil::strValue(element);
                if (!strValue.isEmpty()) {
                    KSieveUi::AbstractSelectEmailLineEdit *headers = w->findChild<KSieveUi::AbstractSelectEmailLineEdit *>(QStringLiteral("from"));
                    headers->setText(strValue);
                }
            } else {
                unknownTagValue(tagValue, error);
                qCDebug(LIBKSIEVE_LOG) << " SieveActionReplace::setParamWidgetValue unknown tagValue " << tagValue;
            }
        } else if (tagName == QLatin1String("crlf")) {
            element.skipCurrentElement();
            //nothing
        } else if (tagName == QLatin1String("comment")) {
            element.skipCurrentElement();
            //implement in the future ?
        } else {
            unknownTag(tagName, error);
            qCDebug(LIBKSIEVE_LOG) << " SieveActionReplace::setParamWidgetValue unknown tagName " << tagName;
        }
    }

    return true;
}

QString SieveActionReplace::code(QWidget *w) const
{
    QString result = QStringLiteral("replace ");
    const QLineEdit *subject = w->findChild<QLineEdit *>(QStringLiteral("subject"));
    const QString subjectStr = subject->text();
    if (!subjectStr.isEmpty()) {
        result += QStringLiteral(":subject \"%1\" ").arg(subjectStr);
    }

    const KSieveUi::AbstractSelectEmailLineEdit *headers = w->findChild<KSieveUi::AbstractSelectEmailLineEdit *>(QStringLiteral("from"));
    const QString headersStr = headers->text();
    if (!headersStr.isEmpty()) {
        result += QStringLiteral(":from \"%1\" ").arg(headersStr);
    }

    const MultiLineEdit *edit = w->findChild<MultiLineEdit *>(QStringLiteral("text"));
    const QString text = edit->toPlainText();
    if (!text.isEmpty()) {
        result += QStringLiteral("text:%1").arg(AutoCreateScriptUtil::createMultiLine(text));
    }

    return result;
}

QStringList SieveActionReplace::needRequires(QWidget *) const
{
    return QStringList() << QStringLiteral("replace");
}

bool SieveActionReplace::needCheckIfServerHasCapability() const
{
    return true;
}

QString SieveActionReplace::serverNeedsCapability() const
{
    return QStringLiteral("replace");
}

QString SieveActionReplace::help() const
{
    return i18n("The \"replace\" command is defined to allow a MIME part to be replaced with the text supplied in the command.");
}

QUrl SieveActionReplace::href() const
{
    return SieveEditorUtil::helpUrl(SieveEditorUtil::strToVariableName(name()));
}
