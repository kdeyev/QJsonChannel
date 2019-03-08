#pragma once

#include <QObject>
#include <QJsonChannelServiceRepository.h>
//#include "QJsonChannelTufao_export.h"


class QJsonChannelEmbedImpl;
class QJsonChannelEmbedAdapter : public QObject {
Q_OBJECT
	friend QJsonChannelEmbedImpl;
private:
	QJsonChannelEmbedAdapter(QJsonChannelServiceRepository* serviceRepository) : _serviceRepository(serviceRepository) {}
public Q_SLOTS :
	QByteArray invokeJsonRPC(const QByteArray& jsonRpc);
private:
	QJsonChannelServiceRepository* _serviceRepository = nullptr;
};
