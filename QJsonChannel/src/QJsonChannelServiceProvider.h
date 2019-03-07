#pragma once

#include <QScopedPointer>

#include "QJsonChannelGlobal.h"

class QJsonChannelMessage;
class QJsonChannelService;
class QJsonChannelAbstractSocket;
class QJsonChannelServiceProviderPrivate;
class QJSONCHANNEL_EXPORT QJsonChannelServiceProvider
{
public:
	QJsonChannelServiceProvider();
	~QJsonChannelServiceProvider();
    virtual bool addService(QJsonChannelService *service);
    virtual bool removeService(QJsonChannelService *service);

	QJsonChannelMessage processMessage(const QJsonChannelMessage &message);
private:
    QScopedPointer<QJsonChannelServiceProviderPrivate> d;
};
