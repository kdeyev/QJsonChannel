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

#include <QApplication>
#include <QWebChannel>
#include <QWebEngineView>
//#include <QWebSocketServer>

//#include <QJsonChannelTufaoHttp.h>
#include "testservice.h"

//#include "websocketclientwrapper.h"
//#include "websockettransport.h"

int main(int argc, char *argv[])
{
    qputenv ("QTWEBENGINE_REMOTE_DEBUGGING", "9090");
    QApplication app(argc, argv);

    TestService service;
    QWebChannel channel;
    channel.registerObject(QStringLiteral("agent"), &service);
/*
    // setup the QWebSocketServer
    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"), QWebSocketServer::NonSecureMode);
    if (!server.listen(QHostAddress::LocalHost, 12345)) {
        qFatal("Failed to open web socket server.");
        return 1;
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper clientWrapper(&server);

    
    QJsonChannelTufaoHttp server;

    server._serviceRepository.addService(new QJsonRpcService("agent", new TestService));
      server._httpServer.listen(QHostAddress::Any, 5555);
*/


/*
    // setup the UI
    Dialog dialog;

    // setup the core and publish it to the QWebChannel
    Core core(&dialog);
    channel.registerObject(QStringLiteral("core"), &core);

    // open a browser window with the client HTML page
    QUrl url = QUrl::fromLocalFile(BUILD_DIR "/index.html");
    QDesktopServices::openUrl(url);

    dialog.displayMessage(Dialog::tr("Initialization complete, opening browser at %1.").arg(url.toDisplayString()));
    dialog.show();
*/

    QWebEngineView webView;
    webView.page ()->setWebChannel(&channel);
    webView.load (QUrl ("qrc:///web-ui-main/resources/index.html"));
    webView.show();

    return app.exec();
}
