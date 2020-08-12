/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "sieveimapinstanceinterface.h"
#include "sieveimapinstance.h"
#include "libksieve_debug.h"

using namespace KSieveUi;
SieveImapInstanceInterface::SieveImapInstanceInterface()
{
}

SieveImapInstanceInterface::~SieveImapInstanceInterface()
{
}

QVector<KSieveUi::SieveImapInstance> SieveImapInstanceInterface::sieveImapInstances()
{
    qCWarning(LIBKSIEVE_LOG) << "Need to reimplement in subclass";
    return {};
}
