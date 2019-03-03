#include "QJsonChannelEmbedAdapter.h"

#include <QJsonDocument>
#include "QJsonChannelMessage.h"

QByteArray QJsonChannelEmbedAdapter::invokeJsonRPC(const QByteArray &jsonRpc) {
	QJsonChannelMessage request = QJsonChannelMessage::fromObject(QJsonDocument::fromJson(jsonRpc).object());
	QJsonChannelMessage response = _serviceRepository->processMessage(request);
	return response.toJson();
}
