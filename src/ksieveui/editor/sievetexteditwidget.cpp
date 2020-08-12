/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "sievetexteditwidget.h"
#include <QVBoxLayout>
#include "editor/sievetextedit.h"

#include <KPIMTextEdit/PlainTextEditFindBar>
#include <KPIMTextEdit/SlideContainer>
using namespace KSieveUi;

class KSieveUi::SieveTextEditWidgetPrivate
{
public:
    SieveTextEditWidgetPrivate()
    {
    }

    KSieveUi::SieveTextEdit *mTextEdit = nullptr;
    KPIMTextEdit::SlideContainer *mSliderContainer = nullptr;
    KPIMTextEdit::PlainTextEditFindBar *mFindBar = nullptr;
};

SieveTextEditWidget::SieveTextEditWidget(KSieveUi::SieveTextEdit *customTextEdit, QWidget *parent)
    : QWidget(parent)
    , d(new KSieveUi::SieveTextEditWidgetPrivate)
{
    initialize(customTextEdit);
}

SieveTextEditWidget::SieveTextEditWidget(QWidget *parent)
    : QWidget(parent)
    , d(new KSieveUi::SieveTextEditWidgetPrivate)
{
    initialize();
}

SieveTextEditWidget::~SieveTextEditWidget()
{
    delete d;
}

void SieveTextEditWidget::initialize(KSieveUi::SieveTextEdit *custom)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    if (custom) {
        d->mTextEdit = custom;
    } else {
        d->mTextEdit = new KSieveUi::SieveTextEdit;
    }
    d->mTextEdit->setObjectName(QStringLiteral("textedit"));
    d->mTextEdit->setShowHelpMenu(false);
    mainLayout->addWidget(d->mTextEdit);

    d->mSliderContainer = new KPIMTextEdit::SlideContainer(this);
    d->mSliderContainer->setObjectName(QStringLiteral("slidercontainer"));
    d->mFindBar = new KPIMTextEdit::PlainTextEditFindBar(d->mTextEdit, this);
    d->mFindBar->setObjectName(QStringLiteral("findbar"));
    d->mFindBar->setHideWhenClose(false);
    connect(d->mFindBar, &KPIMTextEdit::TextEditFindBarBase::hideFindBar, d->mSliderContainer, &KPIMTextEdit::SlideContainer::slideOut);
    d->mSliderContainer->setContent(d->mFindBar);
    mainLayout->addWidget(d->mSliderContainer);
    connect(d->mTextEdit, &SieveTextEdit::findText, this, &SieveTextEditWidget::slotFind);
    connect(d->mTextEdit, &SieveTextEdit::replaceText, this, &SieveTextEditWidget::slotReplace);
}

void SieveTextEditWidget::setReadOnly(bool readOnly)
{
    d->mTextEdit->setReadOnly(readOnly);
}

void SieveTextEditWidget::slotReplace()
{
    if (d->mTextEdit->textCursor().hasSelection()) {
        d->mFindBar->setText(d->mTextEdit->textCursor().selectedText());
    }
    d->mFindBar->showReplace();
    d->mSliderContainer->slideIn();
    d->mFindBar->focusAndSetCursor();
}

void SieveTextEditWidget::slotFind()
{
    if (d->mTextEdit->textCursor().hasSelection()) {
        d->mFindBar->setText(d->mTextEdit->textCursor().selectedText());
    }
    d->mTextEdit->moveCursor(QTextCursor::Start);
    d->mFindBar->showFind();
    d->mSliderContainer->slideIn();
    d->mFindBar->focusAndSetCursor();
}

SieveTextEdit *SieveTextEditWidget::textEdit() const
{
    return d->mTextEdit;
}
