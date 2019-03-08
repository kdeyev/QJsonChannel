#pragma once

#include <QScopedPointer>

#include "QJsonChannelGlobal.h"

class QJsonChannelMessage;
class QJsonChannelService;
class QJsonChannelServiceRepositoryPrivate;

/**
 * @brief The main entity of QJsonChannel represents service repository and provides API for a JSON-RPC method invokation.
 * 
 */
class QJSONCHANNEL_EXPORT QJsonChannelServiceRepository {
public:
    QJsonChannelServiceRepository ();
    ~QJsonChannelServiceRepository ();

    /**
     * @brief Adds service to the repository
     * 
     * @param service A service to attach to the repository
     * @return true in case the sevice was added
     * @return false in case of failure
     */
    bool addService (QJsonChannelService* service);

    /**
     * @brief Return service by name
     * 
     * @param serviceName a service name to search
     * @return QJsonChannelService* a found sevice 
     */
    QJsonChannelService* getService (const QByteArray& serviceName);

    /**
     * @brief Removes service from the repository
     * 
     * @param service A service to remove from the repository
     * @return true in case the sevice was removed
     * @return false in case of failure
     */
    bool removeService (QJsonChannelService* service);

    /**
     * @brief Removes service from the repository
     * 
     * @param serviceName A service name to remove from the repository
     * @return true in case the sevice was removed
     * @return false in case of failure
     */
    bool removeService (const QByteArray& serviceName);

    /**
     * @brief Process a JSON-RPC message. In general it means the invogation of a requested function of a requested service
     * 
     * @param message JSON-RPC message
     * @return QJsonChannelMessage JSON-RPC response message
     */
    QJsonChannelMessage processMessage (const QJsonChannelMessage& message);

private:
    QScopedPointer<QJsonChannelServiceRepositoryPrivate> d;
};
