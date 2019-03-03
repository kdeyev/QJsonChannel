#include "QJsonChannelEmbedAdapter.h"

#include <QJsonDocument>
#include "QJsonChannelMessage.h"

QByteArray QJsonChannelEmbedAdapter::invokeJsonRPC(const QByteArray &jsonRpc) {
	QJsonRpcMessage request = QJsonRpcMessage::fromObject(QJsonDocument::fromJson(jsonRpc).object());
	QJsonRpcMessage response = _serviceRepository->processMessage(request);
	return response.toJson();
}
