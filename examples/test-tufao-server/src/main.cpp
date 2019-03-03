#include "TestService.h"
#include <QJsonChannelService.h>
#include <QJsonChannelTufao.h>
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  QJsonChannelTufao server;

  server._serviceRepository.addService(
      new QJsonChannelService("agent", new TestService));
  server._httpServer.listen(QHostAddress::Any, 5555);

  return a.exec();
}
