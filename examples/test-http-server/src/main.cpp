/*
  Copyright (c) 2013 Vinícius dos Santos Oliveira

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <iostream>
#include <QtCore/QCoreApplication>
#include <QtCore/QUrl>

#include <Tufao/HttpServer>
#include <Tufao/HttpServerRequest>
#include <Tufao/Headers>
#include <QJsonChannel/qjsonrpcserviceprovider.h>
#include <testservice.h>

using namespace Tufao;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HttpServer server;

	QJsonRpcServiceProvider sp;
	sp.addService(new QJsonRpcService("agent", new TestService));

    QObject::connect(&server, &HttpServer::requestReady,
                     [&](HttpServerRequest &req, HttpServerResponse &res) {
							
							if (req.method() == "POST") {
								QByteArray data = req.readBody();
								res.writeHead(Tufao::HttpResponseStatus::OK);
								res.headers().replace("Content-Type", "application/json");

								res.headers().insert("Access-Control-Allow-Origin", "*");
								res.headers().insert("Access-Control-Allow-Methods", "POST");
								res.headers().insert("Access-Control-Allow-Headers", "accept, content-type");

								QJsonRpcMessage request = QJsonRpcMessage::fromJson(data);
								QJsonRpcMessage response = sp.processMessage(request);
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
							} else {
								std::cout << req.method().toStdString();
							}
						});

    server.listen(QHostAddress::Any, 5555);

    return a.exec();
}
