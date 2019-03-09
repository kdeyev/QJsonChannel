#pragma once

#include <QVariant>
#include <QPointer>

#include "QJsonChannelMessage.h"

class QJsonChannelServiceRepository;
class QJsonChannelServicePrivate;
class QJSONCHANNEL_EXPORT QJsonChannelService : public QObject {
    Q_OBJECT
public:
    // QJsonChannelService wrapper
    QJsonChannelService (const QByteArray& name, const QByteArray& version, const QByteArray& description, QObject* obj, QObject* parent = nullptr);

    //// for inheritance
    //explicit QJsonChannelService (QObject* parent = nullptr);

    ~QJsonChannelService ();

    QObject*           serviceObj ();
    const QByteArray&  serviceName () const;
    const QJsonObject& serviceInfo () const;

    const QMetaObject* serviceMetaObject () const;

private:
    QJsonChannelMessage dispatch (const QJsonChannelMessage& request);
    void                cacheInvokableInfo ();

    Q_DISABLE_COPY (QJsonChannelService)
    Q_DECLARE_PRIVATE (QJsonChannelService)
    friend class QJsonChannelServiceRepository;

#if !defined(USE_QT_PRIVATE_HEADERS)
    QScopedPointer<QJsonChannelServicePrivate> d_ptr;
#endif
};
