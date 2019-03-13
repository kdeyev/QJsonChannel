#include <QApplication>
#include <QWebEngineView>

#include <QJsonChannelService.h>
#include <QJsonChannelEmbed.h>

#include "TestService.h"

int main (int argc, char* argv[]) {
    qputenv ("QTWEBENGINE_REMOTE_DEBUGGING", "9090");
    QApplication app (argc, argv);

    QJsonChannelEmbed channel;
    channel._serviceRepository.addService ("object", "1.0", "test service", QSharedPointer<QObject> (new TestService));

    QWebEngineView webView;
    webView.page ()->setWebChannel (&channel._channel);
    webView.load (QUrl ("qrc:///index.html"));
    webView.show ();

    return app.exec ();
}
