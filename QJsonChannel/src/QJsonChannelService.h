#pragma once

#include <QVariant>
#include <QPointer>

#include "QJsonChannelMessage.h"

class QJsonChannelServiceProvider;
class QJsonChannelServicePrivate;
class QJSONCHANNEL_EXPORT QJsonChannelService : public QObject
{
    Q_OBJECT
public:
	// QJsonChannelService wrapper
	QJsonChannelService(const QByteArray& name, QObject *obj, QObject *parent = nullptr); 

	// for inheritance
	explicit QJsonChannelService (QObject *parent = nullptr);
	
    ~QJsonChannelService();

	const QByteArray& serviceName() const;
	const QJsonObject& serviceInfo() const;

	const QMetaObject* serviceMetaObject() const;

protected Q_SLOTS:
    QJsonChannelMessage dispatch(const QJsonChannelMessage &request);

private:
    Q_DISABLE_COPY(QJsonChannelService)
    Q_DECLARE_PRIVATE(QJsonChannelService)
    friend class QJsonChannelServiceProvider;

#if !defined(USE_QT_PRIVATE_HEADERS)
    QScopedPointer<QJsonChannelServicePrivate> d_ptr;
#endif

};


