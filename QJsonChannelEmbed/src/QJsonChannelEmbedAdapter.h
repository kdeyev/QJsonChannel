#pragma once

#include <QObject>
#include <QJsonChannelServiceProvider.h>
//#include "QJsonChannelTufao_export.h"


class QJsonChannelEmbed;
class QJsonChannelEmbedAdapter : public QObject {
	Q_OBJECT
		friend QJsonChannelEmbed;
private:
	QJsonChannelEmbedAdapter(QJsonChannelServiceProvider* serviceRepository) : _serviceRepository(serviceRepository) {}
	public Q_SLOTS :
		QByteArray invokeJsonRPC(const QByteArray& jsonRpc);
private:
	QJsonChannelServiceProvider* _serviceRepository = nullptr;
};
