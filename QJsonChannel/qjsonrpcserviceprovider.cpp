#include <QObjectCleanupHandler>
#include <QMetaObject>
#include <QMetaClassInfo>
#include <QDebug>

#include "qjsonrpcservice.h"
#include "qjsonrpcservice_p.h"
#include "qjsonrpcserviceprovider.h"

class QJsonRpcServiceProviderPrivate
{
public:
    //QByteArray serviceName(QJsonRpcService *service);

	QJsonObject servicesInfo() const;

    QHash<QByteArray, QJsonRpcService*> services;
    QObjectCleanupHandler cleanupHandler;
};




QJsonObject QJsonRpcServiceProviderPrivate::servicesInfo() const
{
	QJsonObject objectInfos;
	const auto end = services.constEnd();
	for (auto it = services.constBegin(); it != end; ++it) {
		const QJsonObject &info = it.value()->serviceInfo();
		objectInfos[it.key()] = info;
	}
	return objectInfos;
}

//QByteArray QJsonRpcServiceProviderPrivate::serviceName(QJsonRpcService *service)
//{
//	const QMetaObject *mo = service->metaObject();
//	for (int i = 0; i < mo->classInfoCount(); i++) {
//		const QMetaClassInfo mci = mo->classInfo(i);
//		if (mci.name() == QLatin1String("serviceName"))
//			return mci.value();
//	}
//
//	return QByteArray(mo->className()).toLower();
//}

QJsonRpcServiceProvider::QJsonRpcServiceProvider()
    : d(new QJsonRpcServiceProviderPrivate)
{
}

QJsonRpcServiceProvider::~QJsonRpcServiceProvider()
{
}


bool QJsonRpcServiceProvider::addService(QJsonRpcService *service)
{
    QByteArray serviceName = service->serviceName();
    if (serviceName.isEmpty()) {
        qJsonRpcDebug() << Q_FUNC_INFO << "service added without serviceName classinfo, aborting";
        return false;
    }

    if (d->services.contains(serviceName)) {
        qJsonRpcDebug() << Q_FUNC_INFO << "service with name " << serviceName << " already exist";
        return false;
    }

    service->d_func()->cacheInvokableInfo();
    d->services.insert(serviceName, service);
    if (!service->parent())
        d->cleanupHandler.add(service);
    return true;
}

bool QJsonRpcServiceProvider::removeService(QJsonRpcService *service)
{
	QByteArray serviceName = service->serviceName();
    if (!d->services.contains(serviceName)) {
        qJsonRpcDebug() << Q_FUNC_INFO << "can not find service with name " << serviceName;
        return false;
    }

    d->cleanupHandler.remove(d->services.value(serviceName));
    d->services.remove(serviceName);
    return true;
}

QJsonRpcMessage QJsonRpcServiceProvider::processMessage(const QJsonRpcMessage &message)
{
    switch (message.type()) {
		case QJsonRpcMessage::Init:
		{
			QJsonRpcMessage response = message.createResponse(d->servicesInfo());
			return response;
		}
        case QJsonRpcMessage::Request:
        case QJsonRpcMessage::Notification: {
            QByteArray serviceName = message.method().section(".", 0, -2).toLatin1();
            if (serviceName.isEmpty() || !d->services.contains(serviceName)) {
                if (message.type() == QJsonRpcMessage::Request) {
                    QJsonRpcMessage error =
                        message.createErrorResponse(QJsonRpc::MethodNotFound,
                            QString("service '%1' not found").arg(serviceName.constData()));
					return error;
                }
            } else {
                QJsonRpcService *service = d->services.value(serviceName);
                //service->d_func()->currentRequest = QJsonRpcServiceRequest(message, socket);
                //if (message.type() == QJsonRpcMessage::Request)
                //    QObject::connect(service, SIGNAL(result(QJsonRpcMessage)),
                //                      socket, SLOT(notify(QJsonRpcMessage)), Qt::UniqueConnection);
                QJsonRpcMessage response = service->dispatch(message);
				return response;
            }
        }
        break;

        case QJsonRpcMessage::Response:
            // we don't handle responses in the provider
			return QJsonRpcMessage();
            break;

        default: {
            QJsonRpcMessage error =
                message.createErrorResponse(QJsonRpc::InvalidRequest, QString("invalid request"));
			return error;
            break;
        }
    };
}
