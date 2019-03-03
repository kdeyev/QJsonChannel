#include <QApplication>
#include <QWebChannel>
#include <QWebEngineView>
#include "testservice.h"

int main(int argc, char *argv[])
{
    qputenv ("QTWEBENGINE_REMOTE_DEBUGGING", "9090");
    QApplication app(argc, argv);

    TestService service;
    QWebChannel channel;
    channel.registerObject(QStringLiteral("agent"), &service);

    QWebEngineView webView;
    webView.page ()->setWebChannel(&channel);
    webView.load (QUrl ("qrc:///resources/index.html"));
    webView.show();

    return app.exec();
}
