/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "sievescriptparsingerrordialog.h"
#include <PimCommon/PimUtil>
#include <TextCustomEditor/RichTextEditorWidget>

#include <KLocalizedString>
#include <KSharedConfig>

#include <KConfigGroup>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>
#include <cerrno>
using namespace KSieveUi;
namespace
{
static const char mySieveScriptParsingErrorDialogGroupName[] = "SieveScriptParsingErrorDialog";
}
SieveScriptParsingErrorDialog::SieveScriptParsingErrorDialog(QWidget *parent)
    : QDialog(parent)
    , mTextEdit(new TextCustomEditor::RichTextEditorWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Sieve Parsing Error"));
    auto mainLayout = new QVBoxLayout(this);

    mTextEdit->setReadOnly(true);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    auto user1Button = new QPushButton(this);
    buttonBox->addButton(user1Button, QDialogButtonBox::ActionRole);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SieveScriptParsingErrorDialog::reject);
    user1Button->setText(i18n("Save As..."));
    readConfig();
    connect(user1Button, &QPushButton::clicked, this, &SieveScriptParsingErrorDialog::slotSaveAs);
    mainLayout->addWidget(mTextEdit);
    mainLayout->addWidget(buttonBox);
}

SieveScriptParsingErrorDialog::~SieveScriptParsingErrorDialog()
{
    writeConfig();
}

void SieveScriptParsingErrorDialog::setError(QString script, QString error)
{
    QString str;
    str = QLatin1String("<b>") + i18n("Sieve script:") + QLatin1String("</b><br>");
    str += script.replace(QLatin1Char('\n'), QStringLiteral("<br>")) + QLatin1String("<br><br>");
    str += QLatin1String("<b>") + i18n("Errors reported:") + QLatin1String("</b><br>");
    str += error.replace(QLatin1Char('\n'), QStringLiteral("<br>")) + QLatin1String("<br>");
    mTextEdit->setHtml(str);
}

void SieveScriptParsingErrorDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(800, 600));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(mySieveScriptParsingErrorDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void SieveScriptParsingErrorDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1String(mySieveScriptParsingErrorDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
    group.sync();
}

void SieveScriptParsingErrorDialog::slotSaveAs()
{
    const QString filter = i18n("All Files (*)");
    PimCommon::Util::saveTextAs(mTextEdit->toPlainText(), filter, this, QUrl(), i18nc("@title:window", "Save Log To File"));
}

#include "moc_sievescriptparsingerrordialog.cpp"
