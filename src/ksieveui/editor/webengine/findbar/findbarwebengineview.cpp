/* SPDX-FileCopyrightText: 2016-2022 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "findbarwebengineview.h"
#include <PimCommon/LineEditWithCompleterNg>
#include <QAction>
#include <QWebEngineView>
using namespace KSieveUi;

class KSieveUi::FindBarWebEngineViewPrivate
{
public:
    FindBarWebEngineViewPrivate() = default;

    QWebEngineView *mView = nullptr;
};

FindBarWebEngineView::FindBarWebEngineView(QWebEngineView *view, QWidget *parent)
    : FindBarBase(parent)
    , d(new KSieveUi::FindBarWebEngineViewPrivate)
{
    d->mView = view;
}

FindBarWebEngineView::~FindBarWebEngineView() = default;

void FindBarWebEngineView::searchText(bool backward, bool isAutoSearch)
{
    QWebEnginePage::FindFlags searchOptions;

    if (backward) {
        searchOptions |= QWebEnginePage::FindBackward;
    }
    if (mCaseSensitiveAct->isChecked()) {
        searchOptions |= QWebEnginePage::FindCaseSensitively;
    }
    const QString searchWord(mSearch->text());
    if (!isAutoSearch && !mLastSearchStr.contains(searchWord, Qt::CaseSensitive)) {
        clearSelections();
    }
    d->mView->findText(QString()); // Clear an existing highlight
    mLastSearchStr = searchWord;
    d->mView->findText(mLastSearchStr, searchOptions, [this](bool found) {
        setFoundMatch(found);
    });
}

void FindBarWebEngineView::updateSensitivity(bool sensitivity)
{
    QWebEnginePage::FindFlags searchOptions;
    if (sensitivity) {
        searchOptions |= QWebEnginePage::FindCaseSensitively;
        d->mView->findText(QString()); // Clear an existing highligh
    }
    d->mView->findText(QString(), searchOptions, [this](bool found) {
        setFoundMatch(found);
    });
}

void FindBarWebEngineView::clearSelections()
{
    d->mView->findText(QString());
    mLastSearchStr.clear();
    FindBarBase::clearSelections();
}
