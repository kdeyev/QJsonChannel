#include <QObjectCleanupHandler>
#include <QMetaObject>
#include <QMetaClassInfo>
#include <QDebug>

#include "QJsonChannelService.h"
#include "QJsonChannelServiceRepository.h"

class QJsonChannelServiceRepositoryPrivate {
public:
    QJsonObject servicesInfo () const;

    QHash<QByteArray, QJsonChannelService*> services;
    QObjectCleanupHandler                   cleanupHandler;
};

QJsonObject QJsonChannelServiceRepositoryPrivate::servicesInfo () const {
    QJsonObject objectInfos;
    const auto  end = services.constEnd ();
    for (auto it = services.constBegin (); it != end; ++it) {
        const QJsonObject& info = it.value ()->serviceInfo ();
        objectInfos[it.key ()]  = info;
    }
    return objectInfos;
}

QJsonChannelServiceRepository::QJsonChannelServiceRepository () : d (new QJsonChannelServiceRepositoryPrivate) {
}

QJsonChannelServiceRepository::~QJsonChannelServiceRepository () {
}

bool QJsonChannelServiceRepository::addService (const QByteArray& serviceName, const QByteArray& version, const QByteArray& description, QObject* obj) {
    QJsonChannelService* service = new QJsonChannelService(serviceName, version, description, obj);
	return addService (service);
}

bool QJsonChannelServiceRepository::addService (QJsonChannelService* service) {
    QByteArray serviceName = service->serviceName ();
    if (serviceName.isEmpty ()) {
        QJsonChannelDebug () << Q_FUNC_INFO << "service added without serviceName classinfo, aborting";
        return false;
    }

    if (d->services.contains (serviceName)) {
        QJsonChannelDebug () << Q_FUNC_INFO << "service with name " << serviceName << " already exist";
        return false;
    }

    service->cacheInvokableInfo ();
    d->services.insert (serviceName, service);
    if (!service->parent ()) {
        d->cleanupHandler.add (service);
    }
    return true;
}

bool QJsonChannelServiceRepository::removeService (QJsonChannelService* service) {
    QByteArray serviceName = service->serviceName ();
    return removeService (serviceName);
}

bool QJsonChannelServiceRepository::removeService (const QByteArray& serviceName) {
    if (!d->services.contains (serviceName)) {
        QJsonChannelDebug () << Q_FUNC_INFO << "can not find service with name " << serviceName;
        return false;
    }

    d->cleanupHandler.remove (d->services.value (serviceName));
    d->services.remove (serviceName);
    return true;
}

QJsonChannelService* QJsonChannelServiceRepository::getService (const QByteArray& serviceName) {
    if (!d->services.contains (serviceName)) {
        return nullptr;
    }

    return d->services.value (serviceName);
}

QObject* QJsonChannelServiceRepository::getServiceObject (const QByteArray& serviceName) {
    if (!d->services.contains (serviceName)) {
        return nullptr;
    }

    return d->services.value (serviceName)->serviceObj();
}

QJsonChannelMessage QJsonChannelServiceRepository::processMessage (const QJsonChannelMessage& message) {
    switch (message.type ()) {
    case QJsonChannelMessage::Init: {
        QJsonChannelMessage response = message.createResponse (d->servicesInfo ());
        return response;
    }
    case QJsonChannelMessage::Request:
    case QJsonChannelMessage::Notification: {
        QByteArray serviceName = message.method ().section (".", 0, -2).toLatin1 ();
        if (serviceName.isEmpty () || !d->services.contains (serviceName)) {
            if (message.type () == QJsonChannelMessage::Request) {
                QJsonChannelMessage error =
                    message.createErrorResponse (QJsonChannel::MethodNotFound, QString ("service '%1' not found").arg (serviceName.constData ()));
                return error;
            }
        } else {
            QJsonChannelService* service  = d->services.value (serviceName);
            QJsonChannelMessage  response = service->dispatch (message);
            return response;
        }
    } break;

    case QJsonChannelMessage::Response:
        // we don't handle responses in the provider
        return QJsonChannelMessage ();
        break;

    default: {
        QJsonChannelMessage error = message.createErrorResponse (QJsonChannel::InvalidRequest, QString ("invalid request"));
        return error;
        break;
    }
    };

    return QJsonChannelMessage ();
}
