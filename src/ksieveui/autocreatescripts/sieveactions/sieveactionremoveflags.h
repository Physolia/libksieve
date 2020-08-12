/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#ifndef SIEVEACTIONREMOVEFLAGS_H
#define SIEVEACTIONREMOVEFLAGS_H

#include "sieveactionabstractflags.h"

namespace KSieveUi {
class SieveActionRemoveFlags : public SieveActionAbstractFlags
{
    Q_OBJECT
public:
    explicit SieveActionRemoveFlags(SieveEditorGraphicalModeWidget *sieveGraphicalModeWidget, QObject *parent = nullptr);
    Q_REQUIRED_RESULT QString flagsCode() const override;
    Q_REQUIRED_RESULT QString help() const override;
    Q_REQUIRED_RESULT QUrl href() const override;
};
}
#endif // SIEVEACTIONREMOVEFLAGS_H
