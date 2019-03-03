#include <QObjectCleanupHandler>
#include <QMetaObject>
#include <QMetaClassInfo>
#include <QDebug>

#include "QJsonChannelService.h"
#include "QJsonChannelService_p.h"
#include "QJsonChannelServiceProvider.h"

class QJsonChannelServiceProviderPrivate
{
public:
    QJsonObject servicesInfo() const;

    QHash<QByteArray, QJsonChannelService*> services;
    QObjectCleanupHandler cleanupHandler;
};




QJsonObject QJsonChannelServiceProviderPrivate::servicesInfo() const
{
	QJsonObject objectInfos;
	const auto end = services.constEnd();
	for (auto it = services.constBegin(); it != end; ++it) {
		const QJsonObject &info = it.value()->serviceInfo();
		objectInfos[it.key()] = info;
	}
	return objectInfos;
}

QJsonChannelServiceProvider::QJsonChannelServiceProvider()
    : d(new QJsonChannelServiceProviderPrivate)
{
}

QJsonChannelServiceProvider::~QJsonChannelServiceProvider()
{
}


bool QJsonChannelServiceProvider::addService(QJsonChannelService *service)
{
    QByteArray serviceName = service->serviceName();
    if (serviceName.isEmpty()) {
        QJsonChannelDebug() << Q_FUNC_INFO << "service added without serviceName classinfo, aborting";
        return false;
    }

    if (d->services.contains(serviceName)) {
        QJsonChannelDebug() << Q_FUNC_INFO << "service with name " << serviceName << " already exist";
        return false;
    }

    service->d_func()->cacheInvokableInfo();
    d->services.insert(serviceName, service);
    if (!service->parent())
        d->cleanupHandler.add(service);
    return true;
}

bool QJsonChannelServiceProvider::removeService(QJsonChannelService *service)
{
	QByteArray serviceName = service->serviceName();
    if (!d->services.contains(serviceName)) {
        QJsonChannelDebug() << Q_FUNC_INFO << "can not find service with name " << serviceName;
        return false;
    }

    d->cleanupHandler.remove(d->services.value(serviceName));
    d->services.remove(serviceName);
    return true;
}

QJsonChannelMessage QJsonChannelServiceProvider::processMessage(const QJsonChannelMessage &message)
{
    switch (message.type()) {
		case QJsonChannelMessage::Init:
		{
			QJsonChannelMessage response = message.createResponse(d->servicesInfo());
			return response;
		}
        case QJsonChannelMessage::Request:
        case QJsonChannelMessage::Notification: {
            QByteArray serviceName = message.method().section(".", 0, -2).toLatin1();
            if (serviceName.isEmpty() || !d->services.contains(serviceName)) {
                if (message.type() == QJsonChannelMessage::Request) {
                    QJsonChannelMessage error =
                        message.createErrorResponse(QJsonChannel::MethodNotFound,
                            QString("service '%1' not found").arg(serviceName.constData()));
					return error;
                }
            } else {
                QJsonChannelService *service = d->services.value(serviceName);
                //service->d_func()->currentRequest = QJsonChannelServiceRequest(message, socket);
                //if (message.type() == QJsonChannelMessage::Request)
                //    QObject::connect(service, SIGNAL(result(QJsonChannelMessage)),
                //                      socket, SLOT(notify(QJsonChannelMessage)), Qt::UniqueConnection);
                QJsonChannelMessage response = service->dispatch(message);
				return response;
            }
        }
        break;

        case QJsonChannelMessage::Response:
            // we don't handle responses in the provider
			return QJsonChannelMessage();
            break;

        default: {
            QJsonChannelMessage error =
                message.createErrorResponse(QJsonChannel::InvalidRequest, QString("invalid request"));
			return error;
            break;
        }
    };

    return QJsonChannelMessage();
}
