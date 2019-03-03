#pragma once

#include <QHash>
#include <QPointer>
#include <QVarLengthArray>
#include <QStringList>

#include "QJsonChannelService.h"

class QJsonChannelAbstractSocket;
class QJsonChannelServiceRequestPrivate : public QSharedData
{
public:
    QJsonChannelMessage request;
    QPointer<QJsonChannelAbstractSocket> socket;
};

class QJsonChannelService;

class QJsonChannelServicePrivate
{
public:
    QJsonChannelServicePrivate(QJsonChannelService *parent, const QByteArray& name, QObject* obj)
        : 
		//delayedResponse(false),
          q_ptr(parent),
		  serviceName(name),
		  serviceObj(obj)
    {
    }

	QJsonObject createServiceInfo() const;

    void cacheInvokableInfo();
    static int QJsonChannelMessageType;
    static int convertVariantTypeToJSType(int type);
    static QJsonValue convertReturnValue(QVariant &returnValue);

    struct ParameterInfo
    {
        ParameterInfo(const QString &name = QString(), int type = 0, bool out = false);

        int type;
        int jsType;
        QString name;
        bool out;
    };

    struct MethodInfo
    {
        MethodInfo();
        MethodInfo(const QMetaMethod &method);

        QVarLengthArray<ParameterInfo> parameters;
        int returnType;
        bool valid;
        bool hasOut;
		QString name;
    };

    QHash<int, MethodInfo > methodInfoHash;
    QHash<QByteArray, QList<int> > invokableMethodHash;

	QJsonObject serviceInfo;

    QJsonChannelService * const q_ptr;
	QObject* serviceObj = nullptr;
	QByteArray serviceName;
    Q_DECLARE_PUBLIC(QJsonChannelService)
};