#include "QJsonChannelTufao.h"

#include <HttpServer>
#include <HttpServerRequest>
#include <Headers>
#include <WebSocket>
#include <AbstractMessageSocket>

#include "QJsonChannelMessage.h"

using namespace Tufao;

QJsonChannelTufao::QJsonChannelTufao() {
	QObject::connect(&_httpServer, &HttpServer::requestReady,
		[&](HttpServerRequest &req, HttpServerResponse &res) {

		if (req.method() == "POST") {
			QByteArray data = req.readBody();
			res.writeHead(HttpResponseStatus::OK);
			res.headers().replace("Content-Type", "application/json");

			res.headers().insert("Access-Control-Allow-Origin", "*");
			res.headers().insert("Access-Control-Allow-Methods", "POST");
			res.headers().insert("Access-Control-Allow-Headers", "accept, content-type");

			QJsonRpcMessage request = QJsonRpcMessage::fromJson(data);
			QJsonRpcMessage response = _serviceRepository.processMessage(request);
			data = response.toJson();
			res.end(data);
		}
		else if (req.method() == "OPTIONS") {
			res.writeHead(HttpResponseStatus::OK);

			res.headers().insert("Access-Control-Allow-Origin", "*");
			res.headers().insert("Access-Control-Allow-Methods", "POST");
			res.headers().insert("Access-Control-Allow-Headers", "accept, content-type");

			res.headers().insert("Allow", "POST");
			res.end();
		}
		else {
			res.writeHead(HttpResponseStatus::I_AM_A_TEAPOT);
		}
	});

	_httpServer.setUpgradeHandler([this](HttpServerRequest &request, const QByteArray &head) {
        WebSocket *socket = new WebSocket(&_httpServer);
        socket->startServerHandshake(request, head);
        socket->setMessagesType(WebSocketMessageType::TEXT_MESSAGE);

		QObject::connect(socket, &AbstractMessageSocket::disconnected, socket, &QObject::deleteLater);

		QObject::connect(socket, &AbstractMessageSocket::newMessage,
                [socket, this](const QByteArray& data){
					QJsonRpcMessage request = QJsonRpcMessage::fromJson(data);
					QJsonRpcMessage response = _serviceRepository.processMessage(request);
					socket->sendMessage (response.toJson());
				});
    });
}