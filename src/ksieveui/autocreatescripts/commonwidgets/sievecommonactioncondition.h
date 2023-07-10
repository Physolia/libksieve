/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>
namespace KSieveCore
{
class SieveImapAccountSettings;
}
namespace KSieveUi
{
class SieveEditorGraphicalModeWidget;
class SieveCommonActionCondition : public QObject
{
    Q_OBJECT
public:
    explicit SieveCommonActionCondition(SieveEditorGraphicalModeWidget *sieveGraphicalModeWidget,
                                        const QString &name,
                                        const QString &label,
                                        QObject *parent = nullptr);
    ~SieveCommonActionCondition() override;

    Q_REQUIRED_RESULT QString name() const;
    Q_REQUIRED_RESULT QString label() const;

    Q_REQUIRED_RESULT virtual QString code(QWidget *parent) const;

    Q_REQUIRED_RESULT virtual QStringList needRequires(QWidget *parent) const;

    Q_REQUIRED_RESULT virtual bool needCheckIfServerHasCapability() const;

    Q_REQUIRED_RESULT virtual QString serverNeedsCapability() const;

    Q_REQUIRED_RESULT virtual QString help() const;
    Q_REQUIRED_RESULT virtual QUrl href() const;

    virtual void unknownTagValue(const QString &tagValue, QString &error);
    virtual void unknownTag(const QStringView &tag, QString &error);
    virtual void tooManyArguments(const QStringView &tagName, int index, int maxValue, QString &error);
    virtual void serverDoesNotSupportFeatures(const QString &feature, QString &error);

    Q_REQUIRED_RESULT QString comment() const;

    void setComment(const QString &comment);

    virtual QWidget *createParamWidget(QWidget *parent) const;

protected:
    Q_REQUIRED_RESULT KSieveCore::SieveImapAccountSettings sieveImapAccountSettings() const;
    Q_REQUIRED_RESULT QStringList sieveCapabilities() const;
    SieveEditorGraphicalModeWidget *const mSieveGraphicalModeWidget;

Q_SIGNALS:
    void valueChanged();

private:
    Q_DISABLE_COPY(SieveCommonActionCondition)
    const QString mName;
    const QString mLabel;
    QString mComment;
};
}
