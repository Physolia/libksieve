/*******************************************************************************
**
** Filename   : util
** Created on : 03 April, 2005
** Copyright  : (c) 2005 Till Adam
** Email      : <adam@kde.org>
**
*******************************************************************************/

/*******************************************************************************
**
**   This program is free software; you can redistribute it and/or modify
**   it under the terms of the GNU General Public License as published by
**   the Free Software Foundation; either version 2 of the License, or
**   (at your option) any later version.
**
**   It is distributed in the hope that it will be useful, but
**   WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   General Public License for more details.
**
**   You should have received a copy of the GNU General Public License
**   along with this program; if not, write to the Free Software
**   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
**   In addition, as a special exception, the copyright holders give
**   permission to link the code of this program with any edition of
**   the Qt library by Trolltech AS, Norway (or with modified versions
**   of Qt that use the same license as Qt), and distribute linked
**   combinations including the two.  You must obey the GNU General
**   Public License in all respects for all of the code used other than
**   Qt.  If you modify this file, you may extend this exception to
**   your version of the file, but you are not obligated to do so.  If
**   you do not wish to do so, delete this exception statement from
**   your version.
**
*******************************************************************************/

#include "util.h"
#include <PimCommon/PimUtil>
#include "imapresourcesettings.h"
#include "sieve-vacation.h"
#include "sieveimapinstance/sieveimapinstanceinterfacemanager.h"
#include "sieveimapinstance/sieveimapinstance.h"

#include <kmime/kmime_message.h>
#include <mailtransport/transport.h>
#include <QUrlQuery>

using namespace KSieveUi;

KSieveUi::Util::AccountInfo KSieveUi::Util::fullAccountInfo(const QString &identifier, bool withVacationFileName)
{
    std::unique_ptr<OrgKdeAkonadiImapSettingsInterface> interface(PimCommon::Util::createImapSettingsInterface(identifier));
    KSieveUi::Util::AccountInfo accountInfo = KSieveUi::Util::findAccountInfo(identifier, withVacationFileName, interface);
    return accountInfo;
}

KSieveUi::Util::AccountInfo KSieveUi::Util::findAccountInfo(const QString &identifier, bool withVacationFileName, std::unique_ptr<OrgKdeAkonadiImapSettingsInterface> &interface)
{

    KSieveUi::Util::AccountInfo accountInfo;
    if (!interface) {
        return accountInfo;
    }

    if (!interface->sieveSupport()) {
        return accountInfo;
    }

    if (interface->sieveReuseConfig()) {
        // assemble Sieve url from the settings of the account:
        QUrl u;
        u.setScheme(QStringLiteral("sieve"));
        QString server;
        QDBusReply<QString> reply = interface->imapServer();
        if (reply.isValid()) {
            server = reply;
            server = server.section(QLatin1Char(':'), 0, 0);
        } else {
            return accountInfo;
        }
        accountInfo.sieveImapAccountSettings.setServerName(server);
        accountInfo.sieveImapAccountSettings.setUserName(interface->userName());

        u.setHost(server);
        u.setUserName(interface->userName());

        QDBusInterface resourceSettings(QLatin1String("org.freedesktop.Akonadi.Resource.") + identifier, QStringLiteral("/Settings"), QStringLiteral("org.kde.Akonadi.Imap.Wallet"));

        QString pwd;
        QDBusReply<QString> replyPass = resourceSettings.call(QStringLiteral("password"));
        if (replyPass.isValid()) {
            pwd = replyPass;
        }
        u.setPassword(pwd);
        accountInfo.sieveImapAccountSettings.setPassword(pwd);
        accountInfo.sieveImapAccountSettings.setPort(interface->sievePort());
        u.setPort(interface->sievePort());
        QString authStr;
        accountInfo.sieveImapAccountSettings.setAuthenticationType(static_cast<SieveImapAccountSettings::AuthenticationMode>((int)interface->authentication()));
        switch (interface->authentication()) {
        case MailTransport::Transport::EnumAuthenticationType::CLEAR:
        case MailTransport::Transport::EnumAuthenticationType::PLAIN:
            authStr = QStringLiteral("PLAIN");
            break;
        case MailTransport::Transport::EnumAuthenticationType::LOGIN:
            authStr = QStringLiteral("LOGIN");
            break;
        case MailTransport::Transport::EnumAuthenticationType::CRAM_MD5:
            authStr = QStringLiteral("CRAM-MD5");
            break;
        case MailTransport::Transport::EnumAuthenticationType::DIGEST_MD5:
            authStr = QStringLiteral("DIGEST-MD5");
            break;
        case MailTransport::Transport::EnumAuthenticationType::GSSAPI:
            authStr = QStringLiteral("GSSAPI");
            break;
        case MailTransport::Transport::EnumAuthenticationType::ANONYMOUS:
            authStr = QStringLiteral("ANONYMOUS");
            break;
        default:
            authStr = QStringLiteral("PLAIN");
            break;
        }
        QUrlQuery query;
        query.addQueryItem(QStringLiteral("x-mech"), authStr);
        const QString resultSafety = interface->safety();
        if (resultSafety == QLatin1String("None")) {
            query.addQueryItem(QStringLiteral("x-allow-unencrypted"), QStringLiteral("true"));
            accountInfo.sieveImapAccountSettings.setEncryptionMode(SieveImapAccountSettings::Unencrypted);
        } else {
            //Verify it.
            accountInfo.sieveImapAccountSettings.setEncryptionMode(SieveImapAccountSettings::AnySslVersion);
        }
        u.setQuery(query);
        u = u.adjusted(QUrl::RemoveFilename);
        if (withVacationFileName) {
            u.setPath(u.path() + QLatin1Char('/') + QString(interface->sieveVacationFilename()));
        }
        accountInfo.sieveUrl = u;
        return accountInfo;
    } else {
        QUrl u;
        u.setHost(interface->sieveAlternateUrl());
        u.setScheme(QStringLiteral("sieve"));
        u.setPort(interface->sievePort());
        QString authStr;
        const QString resultSafety = interface->safety();
        switch (interface->alternateAuthentication()) {
        case MailTransport::Transport::EnumAuthenticationType::CLEAR:
        case MailTransport::Transport::EnumAuthenticationType::PLAIN:
            authStr = QStringLiteral("PLAIN");
            break;
        case MailTransport::Transport::EnumAuthenticationType::LOGIN:
            authStr = QStringLiteral("LOGIN");
            break;
        case MailTransport::Transport::EnumAuthenticationType::CRAM_MD5:
            authStr = QStringLiteral("CRAM-MD5");
            break;
        case MailTransport::Transport::EnumAuthenticationType::DIGEST_MD5:
            authStr = QStringLiteral("DIGEST-MD5");
            break;
        case MailTransport::Transport::EnumAuthenticationType::GSSAPI:
            authStr = QStringLiteral("GSSAPI");
            break;
        case MailTransport::Transport::EnumAuthenticationType::ANONYMOUS:
            authStr = QStringLiteral("ANONYMOUS");
            break;
        default:
            authStr = QStringLiteral("PLAIN");
            break;
        }
        QUrlQuery query;
        query.addQueryItem(QStringLiteral("x-mech"), authStr);
        if (resultSafety == QLatin1String("None")) {
            query.addQueryItem(QStringLiteral("x-allow-unencrypted"), QStringLiteral("true"));
        }
        u.setQuery(query);

        const QString resultCustomAuthentication = interface->sieveCustomAuthentification();
        if (resultCustomAuthentication == QLatin1String("ImapUserPassword")) {
            u.setUserName(interface->userName());
            QDBusInterface resourceSettings(QLatin1String("org.freedesktop.Akonadi.Resource.") + identifier, QStringLiteral("/Settings"), QStringLiteral("org.kde.Akonadi.Imap.Wallet"));
            QString pwd;
            QDBusReply<QString> replyPass = resourceSettings.call(QStringLiteral("password"));
            if (replyPass.isValid()) {
                pwd = replyPass;
            }
            u.setPassword(pwd);
        } else if (resultCustomAuthentication == QLatin1String("CustomUserPassword")) {
            QDBusInterface resourceSettings(QLatin1String("org.freedesktop.Akonadi.Resource.") + identifier, QStringLiteral("/Settings"), QStringLiteral("org.kde.Akonadi.Imap.Wallet"));
            QString pwd;
            QDBusReply<QString> replyPass = resourceSettings.call(QStringLiteral("sieveCustomPassword"));
            if (replyPass.isValid()) {
                pwd = replyPass;
            }
            u.setPassword(pwd);
            u.setUserName(interface->sieveCustomUsername());
        }
        u = u.adjusted(QUrl::RemoveFilename);
        if (withVacationFileName) {
            u.setPath(u.path() + QLatin1Char('/') + QString(interface->sieveVacationFilename()));
        }
        accountInfo.sieveUrl = u;
        return accountInfo;
    }
}

QStringList KSieveUi::Util::sieveImapResourceNames()
{
    const QVector<KSieveUi::SieveImapInstance> lst = KSieveUi::Util::sieveImapInstances();
    QStringList resourceNames;
    resourceNames.reserve(lst.count());
    for (const KSieveUi::SieveImapInstance &type : lst) {
        resourceNames << type.identifier();
    }
    return resourceNames;
}

QVector<KSieveUi::SieveImapInstance> KSieveUi::Util::sieveImapInstances()
{
    const QVector<KSieveUi::SieveImapInstance> allInstances = KSieveUi::SieveImapInstanceInterfaceManager::self()->sieveImapInstanceList();
    QVector<KSieveUi::SieveImapInstance> relevantInstances;
    for (const KSieveUi::SieveImapInstance &instance : allInstances) {
        if (instance.mimeTypes().contains(KMime::Message::mimeType()) &&
                instance.capabilities().contains(QStringLiteral("Resource")) &&
                !instance.capabilities().contains(QStringLiteral("Virtual"))) {

            if (PimCommon::Util::isImapResource(instance.identifier())) {
                relevantInstances << instance;
            }
        }
    }
    return relevantInstances;
}

bool KSieveUi::Util::checkOutOfOfficeOnStartup()
{
    return VacationSettings::self()->checkOutOfOfficeOnStartup();
}

bool KSieveUi::Util::allowOutOfOfficeSettings()
{
    return VacationSettings::self()->allowOutOfOfficeSettings();
}

bool Util::hasKep14Support(const QStringList &sieveCapabilities, const QStringList &availableScripts, const QString &activeScript)
{
    const bool hasIncludeCapability = sieveCapabilities.contains(QStringLiteral("include"));
    if (!hasIncludeCapability) {
        return false;
    }

    bool masterIsActive = !activeScript.isEmpty();
    if (masterIsActive) {
        const QString scriptName = activeScript.split(QLatin1Char('.')).first().toLower();
        masterIsActive = (scriptName == QStringLiteral("master") || scriptName == QStringLiteral("user"));
    }
    if (!masterIsActive) {
        return false;
    }

    bool hasUserScript = false;
    for (const QString &script : availableScripts) {
        if (script.isEmpty()) {
            continue;
        }
        const QString name = script.split(QLatin1Char('.')).first().toLower();
        if (name == QStringLiteral("user")) {
            hasUserScript = true;
            break;
        }
    }

    return hasIncludeCapability && masterIsActive && hasUserScript;
}

bool Util::isKep14ProtectedName(const QString &name)
{
    const QString n = name.split(QLatin1Char('.')).first().toLower();
    if (n == QStringLiteral("master") ||
            n == QStringLiteral("user") ||
            n == QStringLiteral("management")) {
        return true;
    }
    return false;
}


QDebug Util::operator <<(QDebug d, const Util::AccountInfo &info)
{
    d << "sieveImapAccountSettings " << info.sieveImapAccountSettings;
    d << "url " << info.sieveUrl;
    return d;
}
