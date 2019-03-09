#include "TestService.h"
#include <QJsonChannelBeast.h>
#include <QJsonChannelService.h>
#include <QtCore/QCoreApplication>

int main (int argc, char* argv[]) {
    QCoreApplication a (argc, argv);

    QJsonChannelBeast server (1);

    server._serviceRepository.addService (new QJsonChannelService ("agent", "1.0", "test service", new TestService));

    server.start (boost::asio::ip::tcp::endpoint{boost::asio::ip::tcp::v4 (), 5555});

    return a.exec ();
}
