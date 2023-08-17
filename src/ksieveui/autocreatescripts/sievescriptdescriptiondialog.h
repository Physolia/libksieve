/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QDialog>

namespace TextCustomEditor
{
class PlainTextEditorWidget;
}
namespace KSieveUi
{
class SieveScriptDescriptionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SieveScriptDescriptionDialog(QWidget *parent = nullptr);
    ~SieveScriptDescriptionDialog() override;

    void setDescription(const QString &desc);
    Q_REQUIRED_RESULT QString description() const;

private:
    void readConfig();
    void writeConfig();

private:
    TextCustomEditor::PlainTextEditorWidget *mEdit = nullptr;
};
}
