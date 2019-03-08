#pragma once

#include <QSharedDataPointer>
#include <QMetaType>

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

#include "QJsonChannelGlobal.h"

class QJsonChannelMessagePrivate;
class QJSONCHANNEL_EXPORT QJsonChannelMessage {
public:
    QJsonChannelMessage ();
    QJsonChannelMessage (const QJsonChannelMessage& other);
    QJsonChannelMessage& operator= (const QJsonChannelMessage& other);
    ~QJsonChannelMessage ();

    inline void swap (QJsonChannelMessage& other) {
        qSwap (d, other.d);
    }

    enum Type { Invalid, Request, Response, Notification, Error, Init };

    static QJsonChannelMessage createRequest (const QString& method, const QJsonArray& params = QJsonArray ());
    static QJsonChannelMessage createRequest (const QString& method, const QJsonValue& param);
    static QJsonChannelMessage createRequest (const QString& method, const QJsonObject& namedParameters);

    static QJsonChannelMessage createNotification (const QString& method, const QJsonArray& params = QJsonArray ());
    static QJsonChannelMessage createNotification (const QString& method, const QJsonValue& param);
    static QJsonChannelMessage createNotification (const QString& method, const QJsonObject& namedParameters);

    QJsonChannelMessage createResponse (const QJsonValue& result) const;
    QJsonChannelMessage createErrorResponse (QJsonChannel::ErrorCode code, const QString& message = QString (), const QJsonValue& data = QJsonValue ()) const;

    QJsonChannelMessage::Type type () const;
    bool                      isValid () const;
    int                       id () const;

    // request
    QString    method () const;
    QJsonValue params () const;

    // response
    QJsonValue result () const;

    // error
    int        errorCode () const;
    QString    errorMessage () const;
    QJsonValue errorData () const;

    QJsonObject                toObject () const;
    static QJsonChannelMessage fromObject (const QJsonObject& object);

    QByteArray                 toJson () const;
    static QJsonChannelMessage fromJson (const QByteArray& data);

    bool        operator== (const QJsonChannelMessage& message) const;
    inline bool operator!= (const QJsonChannelMessage& message) const {
        return !(operator== (message));
    }

private:
    friend class QJsonChannelMessagePrivate;
    QSharedDataPointer<QJsonChannelMessagePrivate> d;
};

QJSONCHANNEL_EXPORT QDebug operator<< (QDebug, const QJsonChannelMessage&);
Q_DECLARE_METATYPE (QJsonChannelMessage)
Q_DECLARE_SHARED (QJsonChannelMessage)
