/* Copyright (C) 2013-2018 Laurent Montel <montel@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef SIEVEEDITORTEXTMODEWIDGET_H
#define SIEVEEDITORTEXTMODEWIDGET_H

#include "sieveeditorabstractwidget.h"
#include "ksieveui_export.h"
class QSplitter;
namespace KPIMTextEdit {
class SlideContainer;
class TextGoToLineWidget;
class PlainTextEditFindBar;
class PlainTextEditor;
class PlainTextEditorWidget;
class TextToSpeechWidget;
}

namespace KSieveUi {
class SieveInfoWidget;
class SieveTextEdit;
class SieveEditorWarning;
class SieveEditorParsingMissingFeatureWarning;
class SieveEditorTabWidget;
class SieveTemplateWidget;
class KSIEVEUI_EXPORT SieveEditorTextModeWidget : public SieveEditorAbstractWidget
{
    Q_OBJECT
public:
    explicit SieveEditorTextModeWidget(QWidget *parent = nullptr);
    ~SieveEditorTextModeWidget() override;

    void setSieveCapabilities(const QStringList &capabilities);
    void setReadOnly(bool b);

    Q_REQUIRED_RESULT QString script() const;
    void setScript(const QString &script, bool clearUndoRedo = false);

    void setDebugScript(const QString &debug);

    Q_REQUIRED_RESULT QString currentscript() override;
    void setImportScript(const QString &script) override;

    void createRulesGraphically();
    void generateXml();

    void showEditorWarning();
    void hideEditorWarning();

    void showParsingEditorWarning();

    void setParsingEditorWarningError(const QString &script, const QString &error);
    void replace();
    void find();
    void undo();
    void redo();
    void paste();
    void cut();
    void copy();
    void checkSpelling();
    void comment();
    void uncomment();

    bool isUndoAvailable() const;
    bool isRedoAvailable() const;
    bool hasSelection() const;

    void selectAll();
    void upperCase();
    void lowerCase();
    void sentenceCase();
    void reverseCase();
    void zoomIn();
    void zoomOut();
    Q_REQUIRED_RESULT QString currentHelpTitle() const;
    Q_REQUIRED_RESULT QUrl currentHelpUrl() const;
    void openBookmarkUrl(const QUrl &url);
    void debugSieveScript();
    void zoomReset();
    void wordWrap(bool state);
    Q_REQUIRED_RESULT bool isWordWrap() const;
    void print();
    void printPreview();
    Q_REQUIRED_RESULT bool printSupportEnabled() const;
    Q_REQUIRED_RESULT bool isTextEditor() const;
    Q_REQUIRED_RESULT SieveEditorTabWidget *tabWidget() const;

    void setListOfIncludeFile(const QStringList &listOfIncludeFile);
Q_SIGNALS:
    void enableButtonOk(bool);
    void switchToGraphicalMode();
    void valueChanged();
    void undoAvailable(bool);
    void redoAvailable(bool);
    void copyAvailable(bool);
    void sieveEditorTabCurrentChanged();

public Q_SLOTS:
    void slotShowGoToLine();
private:
    void slotTextChanged();
    void slotFind();
    void slotReplace();
    void slotGoToLine(int line);
    void readConfig();
    void writeConfig();
    bool loadFromFile(const QString &filename);
    QString mOriginalScript;
    QStringList mSieveCapabilities;
    QStringList mListOfIncludeFile;
    SieveTextEdit *mTextEdit = nullptr;
    KPIMTextEdit::PlainTextEditorWidget *mDebugTextEdit = nullptr;
    KPIMTextEdit::PlainTextEditFindBar *mFindBar = nullptr;
    KPIMTextEdit::TextToSpeechWidget *mTextToSpeechWidget = nullptr;
    SieveInfoWidget *mSieveInfo = nullptr;
    QSplitter *mMainSplitter = nullptr;
    QSplitter *mExtraSplitter = nullptr;
    QSplitter *mTemplateSplitter = nullptr;
    SieveEditorWarning *mSieveEditorWarning = nullptr;
    SieveEditorParsingMissingFeatureWarning *mSieveParsingWarning = nullptr;
    SieveEditorTabWidget *mTabWidget = nullptr;
    KPIMTextEdit::TextGoToLineWidget *mGoToLine = nullptr;
    KPIMTextEdit::SlideContainer *mGotoLineSliderContainer = nullptr;
    KPIMTextEdit::SlideContainer *mSliderContainer = nullptr;
    SieveTemplateWidget *mSieveTemplateWidget = nullptr;
    QWidget *mEditorWidget = nullptr;
};
}

#endif // SIEVEEDITORTEXTMODEWIDGET_H
