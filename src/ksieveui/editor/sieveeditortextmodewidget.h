/* Copyright (C) 2013-2017 Laurent Montel <montel@kde.org>
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
    ~SieveEditorTextModeWidget();

    void setSieveCapabilities(const QStringList &capabilities);
    void setReadOnly(bool b);

    QString script() const;
    void setScript(const QString &script, bool clearUndoRedo = false);

    void setDebugScript(const QString &debug);

    QString currentscript() override;
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
    QString currentHelpTitle() const;
    QUrl currentHelpUrl() const;
    void openBookmarkUrl(const QUrl &url);
    void debugSieveScript();
    void zoomReset();
    void wordWrap(bool state);
    bool isWordWrap() const;
    void print();
    void printPreview();
    bool printSupportEnabled() const;
    bool isTextEditor() const;
    SieveEditorTabWidget *tabWidget() const;

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
    SieveTextEdit *mTextEdit;
    KPIMTextEdit::PlainTextEditorWidget *mDebugTextEdit;
    KPIMTextEdit::PlainTextEditFindBar *mFindBar;
    KPIMTextEdit::TextToSpeechWidget *mTextToSpeechWidget;
    SieveInfoWidget *mSieveInfo;
    QSplitter *mMainSplitter;
    QSplitter *mExtraSplitter;
    QSplitter *mTemplateSplitter;
    SieveEditorWarning *mSieveEditorWarning;
    SieveEditorParsingMissingFeatureWarning *mSieveParsingWarning;
    SieveEditorTabWidget *mTabWidget;
    KPIMTextEdit::TextGoToLineWidget *mGoToLine;
    KPIMTextEdit::SlideContainer *mGotoLineSliderContainer;
    KPIMTextEdit::SlideContainer *mSliderContainer;
    SieveTemplateWidget *mSieveTemplateWidget;
    QWidget *mEditorWidget;
};
}

#endif // SIEVEEDITORTEXTMODEWIDGET_H
