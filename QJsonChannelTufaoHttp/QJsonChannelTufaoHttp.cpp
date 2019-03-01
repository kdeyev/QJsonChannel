#include <QJsonChTufao/QJsonChannelTufaoHttp.h>

QJsonChannelTufaoHttp::QJsonChannelTufaoHttp() {
	QObject::connect(&_httpServer, &HttpServer::requestReady,
		[&](HttpServerRequest &req, HttpServerResponse &res) {

		if (req.method() == "POST") {
			QByteArray data = req.readBody();
			res.writeHead(Tufao::HttpResponseStatus::OK);
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
			res.writeHead(Tufao::HttpResponseStatus::OK);

			res.headers().insert("Access-Control-Allow-Origin", "*");
			res.headers().insert("Access-Control-Allow-Methods", "POST");
			res.headers().insert("Access-Control-Allow-Headers", "accept, content-type");

			res.headers().insert("Allow", "POST");
			res.end();
		}
		else {
			std::cout << req.method().toStdString();
		}
	});
}