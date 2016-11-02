/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "sievenetworkmanager.h"
#include <QNetworkConfigurationManager>
using namespace KSieveUi;

Q_GLOBAL_STATIC(SieveNetworkManager, s_pSieveNetworkManagerSelf)

SieveNetworkManager::SieveNetworkManager(QObject *parent)
    : QObject(parent)
{
    mNetworkConfigureManager = new QNetworkConfigurationManager();
}

SieveNetworkManager::~SieveNetworkManager()
{
    delete mNetworkConfigureManager;
}

SieveNetworkManager *SieveNetworkManager::self()
{
    return s_pSieveNetworkManagerSelf();
}

QNetworkConfigurationManager *SieveNetworkManager::networkConfigureManager() const
{
    return mNetworkConfigureManager;
}
