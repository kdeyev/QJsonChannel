#include <QDebug>

#include <QJsonDocument>

#include "QJsonChannelMessage.h"

class QJsonChannelMessagePrivate : public QSharedData
{
public:
    QJsonChannelMessagePrivate();
    ~QJsonChannelMessagePrivate();
    QJsonChannelMessagePrivate(const QJsonChannelMessagePrivate &other);

    void initializeWithObject(const QJsonObject &message);
    static QJsonChannelMessage createBasicRequest(const QString &method, const QJsonArray &params);
    static QJsonChannelMessage createBasicRequest(const QString &method,
                                              const QJsonObject &namedParameters);

    QJsonChannelMessage::Type type;
    QScopedPointer<QJsonObject> object;

    static int uniqueRequestCounter;
};

int QJsonChannelMessagePrivate::uniqueRequestCounter = 0;

QJsonChannelMessagePrivate::QJsonChannelMessagePrivate()
    : type(QJsonChannelMessage::Invalid),
      object(0)
{
}

QJsonChannelMessagePrivate::QJsonChannelMessagePrivate(const QJsonChannelMessagePrivate &other)
    : QSharedData(other),
      type(other.type),
      object(other.object ? new QJsonObject(*other.object) : 0)
{
}

void QJsonChannelMessagePrivate::initializeWithObject(const QJsonObject &message)
{
    object.reset(new QJsonObject(message));
    if (message.contains(QLatin1String("id"))) {
        if (message.contains(QLatin1String("result")) ||
            message.contains(QLatin1String("error"))) {
            if (message.contains(QLatin1String("error")) &&
                !message.value(QLatin1String("error")).isNull())
                type = QJsonChannelMessage::Error;
            else
                type = QJsonChannelMessage::Response;
        } else if (message.contains(QLatin1String("method"))) {
			if (message.value(QLatin1String("method")) == "__init__") {
				type = QJsonChannelMessage::Init;
			} else {
				type = QJsonChannelMessage::Request;
			}
        }
    } else {
        if (message.contains(QLatin1String("method")))
            type = QJsonChannelMessage::Notification;
    }
}

QJsonChannelMessagePrivate::~QJsonChannelMessagePrivate()
{
}

QJsonChannelMessage::QJsonChannelMessage()
    : d(new QJsonChannelMessagePrivate)
{
    d->object.reset(new QJsonObject);
}

QJsonChannelMessage::QJsonChannelMessage(const QJsonChannelMessage &other)
    : d(other.d)
{
}

QJsonChannelMessage::~QJsonChannelMessage()
{
}

QJsonChannelMessage &QJsonChannelMessage::operator=(const QJsonChannelMessage &other)
{
    d = other.d;
    return *this;
}

bool QJsonChannelMessage::operator==(const QJsonChannelMessage &message) const
{
    if (message.d == d)
        return true;

    if (message.type() == type()) {
        if (message.type() == QJsonChannelMessage::Error) {
            return (message.errorCode() == errorCode() &&
                    message.errorMessage() == errorMessage() &&
                    message.errorData() == errorData());
        } else {
            if (message.type() == QJsonChannelMessage::Notification) {
                return (message.method() == method() &&
                        message.params() == params());
            } else {
                return (message.id() == id() &&
                        message.method() == method() &&
                        message.params() == params());
            }
        }
    }

    return false;
}

QJsonChannelMessage QJsonChannelMessage::fromJson(const QByteArray &message)
{
    QJsonChannelMessage result;
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(message, &error);
    if (error.error != QJsonParseError::NoError) {
        QJsonChannelDebug() << Q_FUNC_INFO << error.errorString();
        return result;
    }

    if (!document.isObject()) {
        QJsonChannelDebug() << Q_FUNC_INFO << "invalid message: " << message;
        return result;
    }

    result.d->initializeWithObject(document.object());
    return result;
}

QJsonChannelMessage QJsonChannelMessage::fromObject(const QJsonObject &message)
{
    QJsonChannelMessage result;
    result.d->initializeWithObject(message);
    return result;
}

QJsonObject QJsonChannelMessage::toObject() const
{
    if (d->object)
        return QJsonObject(*d->object);
    return QJsonObject();
}

QByteArray QJsonChannelMessage::toJson() const
{
    if (d->object) {
        QJsonDocument doc(*d->object);
        return doc.toJson();
    }

    return QByteArray();
}

bool QJsonChannelMessage::isValid() const
{
    return d->type != QJsonChannelMessage::Invalid;
}

QJsonChannelMessage::Type QJsonChannelMessage::type() const
{
    return d->type;
}

QJsonChannelMessage QJsonChannelMessagePrivate::createBasicRequest(const QString &method, const QJsonArray &params)
{
    QJsonChannelMessage request;
    request.d->object->insert(QLatin1String("jsonrpc"), QLatin1String("2.0"));
    request.d->object->insert(QLatin1String("method"), method);
    if (!params.isEmpty())
        request.d->object->insert(QLatin1String("params"), params);
    return request;
}

QJsonChannelMessage QJsonChannelMessagePrivate::createBasicRequest(const QString &method,
                                                           const QJsonObject &namedParameters)
{
    QJsonChannelMessage request;
    request.d->object->insert(QLatin1String("jsonrpc"), QLatin1String("2.0"));
    request.d->object->insert(QLatin1String("method"), method);
    if (!namedParameters.isEmpty())
        request.d->object->insert(QLatin1String("params"), namedParameters);
    return request;
}

QJsonChannelMessage QJsonChannelMessage::createRequest(const QString &method, const QJsonArray &params)
{
    QJsonChannelMessage request = QJsonChannelMessagePrivate::createBasicRequest(method, params);
    request.d->type = QJsonChannelMessage::Request;
    QJsonChannelMessagePrivate::uniqueRequestCounter++;
    request.d->object->insert(QLatin1String("id"), QJsonChannelMessagePrivate::uniqueRequestCounter);
    return request;
}

QJsonChannelMessage QJsonChannelMessage::createRequest(const QString &method, const QJsonValue &param)
{
    QJsonArray params;
    params.append(param);
    return createRequest(method, params);
}

QJsonChannelMessage QJsonChannelMessage::createRequest(const QString &method,
                                               const QJsonObject &namedParameters)
{
    QJsonChannelMessage request =
        QJsonChannelMessagePrivate::createBasicRequest(method, namedParameters);
    request.d->type = QJsonChannelMessage::Request;
    QJsonChannelMessagePrivate::uniqueRequestCounter++;
    request.d->object->insert(QLatin1String("id"), QJsonChannelMessagePrivate::uniqueRequestCounter);
    return request;
}

QJsonChannelMessage QJsonChannelMessage::createNotification(const QString &method, const QJsonArray &params)
{
    QJsonChannelMessage notification = QJsonChannelMessagePrivate::createBasicRequest(method, params);
    notification.d->type = QJsonChannelMessage::Notification;
    return notification;
}

QJsonChannelMessage QJsonChannelMessage::createNotification(const QString &method, const QJsonValue &param)
{
    QJsonArray params;
    params.append(param);
    return createNotification(method, params);
}

QJsonChannelMessage QJsonChannelMessage::createNotification(const QString &method,
                                                    const QJsonObject &namedParameters)
{
    QJsonChannelMessage notification =
        QJsonChannelMessagePrivate::createBasicRequest(method, namedParameters);
    notification.d->type = QJsonChannelMessage::Notification;
    return notification;
}

QJsonChannelMessage QJsonChannelMessage::createResponse(const QJsonValue &result) const
{
    QJsonChannelMessage response;
    if (d->object->contains(QLatin1String("id"))) {
        QJsonObject *object = response.d->object.data();
        object->insert(QLatin1String("jsonrpc"), QLatin1String("2.0"));
        object->insert(QLatin1String("id"), d->object->value(QLatin1String("id")));
        object->insert(QLatin1String("result"), result);
        response.d->type = QJsonChannelMessage::Response;
    }

    return response;
}

QJsonChannelMessage QJsonChannelMessage::createErrorResponse(QJsonChannel::ErrorCode code,
                                                     const QString &message,
                                                     const QJsonValue &data) const
{
    QJsonChannelMessage response;
    QJsonObject error;
    error.insert(QLatin1String("code"), code);
    if (!message.isEmpty())
        error.insert(QLatin1String("message"), message);
    if (!data.isUndefined())
        error.insert(QLatin1String("data"), data);

    response.d->type = QJsonChannelMessage::Error;
    QJsonObject *object = response.d->object.data();
    object->insert(QLatin1String("jsonrpc"), QLatin1String("2.0"));
    if (d->object->contains(QLatin1String("id")))
        object->insert(QLatin1String("id"), d->object->value(QLatin1String("id")));
    else
        object->insert(QLatin1String("id"), 0);
    object->insert(QLatin1String("error"), error);
    return response;
}

int QJsonChannelMessage::id() const
{
    if (d->type == QJsonChannelMessage::Notification || !d->object)
        return -1;

    const QJsonValue &value = d->object->value(QLatin1String("id"));
    if (value.isString())
        return value.toString().toInt();
    return value.toInt();
}

QString QJsonChannelMessage::method() const
{
    if (d->type == QJsonChannelMessage::Response || !d->object)
        return QString();

    return d->object->value(QLatin1String("method")).toString();
}

QJsonValue QJsonChannelMessage::params() const
{
    if (d->type == QJsonChannelMessage::Response || d->type == QJsonChannelMessage::Error)
        return QJsonValue(QJsonValue::Undefined);
    if (!d->object)
        return QJsonValue(QJsonValue::Undefined);

    return d->object->value(QLatin1String("params"));
}

QJsonValue QJsonChannelMessage::result() const
{
    if (d->type != QJsonChannelMessage::Response || !d->object)
        return QJsonValue(QJsonValue::Undefined);

    return d->object->value(QLatin1String("result"));
}

int QJsonChannelMessage::errorCode() const
{
    if (d->type != QJsonChannelMessage::Error || !d->object)
        return 0;

    QJsonObject error =
        d->object->value(QLatin1String("error")).toObject();
    const QJsonValue &value = error.value(QLatin1String("code"));
    if (value.isString())
        return value.toString().toInt();
    return value.toInt();
}

QString QJsonChannelMessage::errorMessage() const
{
    if (d->type != QJsonChannelMessage::Error || !d->object)
        return QString();

    QJsonObject error =
        d->object->value(QLatin1String("error")).toObject();
    return error.value(QLatin1String("message")).toString();
}

QJsonValue QJsonChannelMessage::errorData() const
{
    if (d->type != QJsonChannelMessage::Error || !d->object)
        return QJsonValue(QJsonValue::Undefined);

    QJsonObject error =
        d->object->value(QLatin1String("error")).toObject();
    return error.value(QLatin1String("data"));
}

static QDebug operator<<(QDebug dbg, QJsonChannelMessage::Type type)
{
    switch (type) {
    case QJsonChannelMessage::Request:
        return dbg << "QJsonChannelMessage::Request";
    case QJsonChannelMessage::Response:
        return dbg << "QJsonChannelMessage::Response";
    case QJsonChannelMessage::Notification:
        return dbg << "QJsonChannelMessage::Notification";
    case QJsonChannelMessage::Error:
        return dbg << "QJsonChannelMessage::Error";
    default:
        return dbg << "QJsonChannelMessage::Invalid";
    }
}

QDebug operator<<(QDebug dbg, const QJsonChannelMessage &msg)
{
    dbg.nospace() << "QJsonChannelMessage(type=" << msg.type();
    if (msg.type() != QJsonChannelMessage::Notification) {
        dbg.nospace() << ", id=" << msg.id();
    }

    if (msg.type() == QJsonChannelMessage::Request ||
        msg.type() == QJsonChannelMessage::Notification) {
        dbg.nospace() << ", method=" << msg.method()
                      << ", params=" << msg.params();
    } else if (msg.type() == QJsonChannelMessage::Response) {
        dbg.nospace() << ", result=" << msg.result();
    } else if (msg.type() == QJsonChannelMessage::Error) {
        dbg.nospace() << ", code=" << msg.errorCode()
                      << ", message=" << msg.errorMessage()
                      << ", data=" << msg.errorData();
    }
    dbg.nospace() << ")";
    return dbg.space();
}
