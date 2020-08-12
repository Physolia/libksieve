/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "sievetemplatewidget.h"
#include "sievetemplateeditdialog.h"
#include "sievedefaulttemplate.h"
#include <PimCommon/TemplateManager>
#include "autocreatescripts/sieveeditorgraphicalmodewidget.h"

#include <KLocalizedString>

#include <QPointer>
#include <QLabel>
#include <QVBoxLayout>
#include <QMimeData>

using namespace KSieveUi;
SieveTemplateListWidget::SieveTemplateListWidget(const QString &configName, QWidget *parent)
    : PimCommon::TemplateListWidget(configName, parent)
{
    setKNewStuffConfigFile(QStringLiteral("ksieve_script.knsrc"));
    loadTemplates();
    mTemplateManager = new PimCommon::TemplateManager(QStringLiteral("sieve/scripts"), this);
}

void SieveTemplateListWidget::setSieveCapabilities(const QStringList &capabilities)
{
    mCapabilities = capabilities;
}

QMimeData *SieveTemplateListWidget::mimeData(const QList<QListWidgetItem *> items) const
{
    if (items.isEmpty()) {
        return nullptr;
    }
    QMimeData *mimeData = new QMimeData();
    QListWidgetItem *item = items.first();
    QString templateStr = item->data(TemplateListWidget::Text).toString();
    if (!mCapabilities.contains(QLatin1String("imap4flags")) && templateStr.contains(QLatin1String("imap4flags"))) {
        templateStr.replace(QStringLiteral("imap4flags"), QStringLiteral("imapflags"));
    }
    mimeData->setText(templateStr);
    return mimeData;
}

SieveTemplateListWidget::~SieveTemplateListWidget()
{
}

QVector<PimCommon::defaultTemplate> SieveTemplateListWidget::defaultTemplates()
{
    return KSieveUi::SieveDefaultTemplate::defaultTemplates();
}

bool SieveTemplateListWidget::addNewTemplate(QString &templateName, QString &templateScript)
{
    QPointer<SieveTemplateEditDialog> dlg = new SieveTemplateEditDialog(this);
    dlg->setSieveCapabilities(mCapabilities);
    bool result = false;
    if (dlg->exec()) {
        templateName = dlg->templateName();
        templateScript = dlg->script();
        result = true;
    }
    delete dlg;
    return result;
}

bool SieveTemplateListWidget::modifyTemplate(QString &templateName, QString &templateScript, bool defaultTemplate)
{
    QPointer<SieveTemplateEditDialog> dlg = new SieveTemplateEditDialog(this, defaultTemplate);
    dlg->setTemplateName(templateName);
    dlg->setScript(templateScript);
    dlg->setSieveCapabilities(mCapabilities);
    bool result = false;
    if (dlg->exec()) {
        if (!defaultTemplate) {
            templateName = dlg->templateName();
            templateScript = dlg->script();
        }
        result = true;
    }
    delete dlg;
    return result;
}

SieveTemplateWidget::SieveTemplateWidget(const QString &title, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);
    QLabel *lab = new QLabel(title, this);
    lay->addWidget(lab);
    mListTemplate = new SieveTemplateListWidget(QStringLiteral("sievetemplaterc"), this);
    mListTemplate->setWhatsThis(i18n("You can drag and drop element on editor to import template"));
    connect(mListTemplate, &SieveTemplateListWidget::insertTemplate, this, &SieveTemplateWidget::insertTemplate);
    lay->addWidget(mListTemplate);
}

SieveTemplateWidget::~SieveTemplateWidget()
{
}

void SieveTemplateWidget::setSieveCapabilities(const QStringList &capabilities)
{
    mListTemplate->setSieveCapabilities(capabilities);
}
