#include <QVarLengthArray>
#include <QMetaMethod>
#include <QDebug>
#include <QHash>
#include <QPointer>
#include <QStringList>

#include "QJsonChannelService.h"

class QJsonChannelServiceRequestPrivate : public QSharedData {
public:
    QJsonChannelMessage request;
};

class QJsonChannelService;

class QJsonChannelServicePrivate {
public:
    QJsonChannelServicePrivate (QJsonChannelService* parent, const QByteArray& name, const QByteArray& version, const QByteArray& description, QObject* obj)
        : //delayedResponse(false),
          q_ptr (parent), serviceName (name), serviceVersion (version), serviceDescription (description), serviceObj (obj) {
    }

    QJsonObject createServiceInfo () const;

    void              cacheInvokableInfo ();
    static int        QJsonChannelMessageType;
    static int        convertVariantTypeToJSType (int type);
    static QJsonValue convertReturnValue (QVariant& returnValue);

    struct ParameterInfo {
        ParameterInfo (const QString& name = QString (), int type = 0, bool out = false);

        int     type;
        int     jsType;
        QString name;
        bool    out;
    };

    struct MethodInfo {
        MethodInfo ();
        MethodInfo (const QMetaMethod& method);

        QVarLengthArray<ParameterInfo> parameters;
        int                            returnType;
        bool                           valid;
        bool                           hasOut;
        QString                        name;
    };

    QHash<int, MethodInfo>        methodInfoHash;
    QHash<QByteArray, QList<int>> invokableMethodHash;

    QJsonObject serviceInfo;

    QJsonChannelService* const q_ptr;
    QObject*                   serviceObj = nullptr;
    QByteArray                 serviceName;
    QString                    serviceVersion;
    QString                    serviceDescription;
    Q_DECLARE_PUBLIC (QJsonChannelService)
};

QJsonChannelServicePrivate::ParameterInfo::ParameterInfo (const QString& n, int t, bool o)
    : type (t), jsType (convertVariantTypeToJSType (t)), name (n), out (o) {
}

QJsonChannelServicePrivate::MethodInfo::MethodInfo () : returnType (QMetaType::Void), valid (false), hasOut (false) {
}

QJsonChannelServicePrivate::MethodInfo::MethodInfo (const QMetaMethod& method) : returnType (QMetaType::Void), valid (true), hasOut (false) {
    name = method.name ();

    returnType = method.returnType ();
    if (returnType == QMetaType::UnknownType) {
        QJsonChannelDebug () << "QJsonChannelService: can't bind method's return type" << QString (method.name ());
        valid = false;
        return;
    }

    parameters.reserve (method.parameterCount ());

    const QList<QByteArray>& types = method.parameterTypes ();
    const QList<QByteArray>& names = method.parameterNames ();
    for (int i = 0; i < types.size (); ++i) {
        QByteArray        parameterType = types.at (i);
        const QByteArray& parameterName = names.at (i);
        bool              out           = parameterType.endsWith ('&');

        if (out) {
            hasOut = true;
            parameterType.resize (parameterType.size () - 1);
        }

        int type = QMetaType::type (parameterType);
        if (type == 0) {
            QJsonChannelDebug () << "QJsonChannelService: can't bind method's parameter" << QString (parameterType);
            valid = false;
            break;
        }

        parameters.append (ParameterInfo (parameterName, type, out));
    }
}

//QByteArray getClassInfo(QObject* obj, const char* field) {
//	const QMetaObject* mo = obj->metaObject();
//	for (int i = 0; i < mo->classInfoCount(); i++) {
//		const QMetaClassInfo mci = mo->classInfo(i);
//		if (mci.name() == QLatin1String(field))
//			return mci.value();
//	}
//
//	return QByteArray();
//}
//
//QByteArray getServiceName (QObject* obj) {
//	QByteArray serviceName = getClassInfo(obj, "serviceName");
//	if (serviceName.isEmpty()) {
//		const QMetaObject* mo = obj->metaObject();
//		serviceName = QByteArray(mo->className()).toLower();
//	}
//	return serviceName;
//}
//
//QByteArray getServiceDescription(QObject* obj) {
//	return getClassInfo(obj, "serviceDescription");
//}
//
//QByteArray getServiceVersion(QObject* obj) {
//	return getClassInfo(obj, "serviceVersion");
//}
//
//QJsonChannelService::QJsonChannelService (QObject* parent) : QObject (parent) {
//    d_ptr.reset (new QJsonChannelServicePrivate (this, getServiceName (this), getServiceVersion(this), getServiceDescription(this), this));
//}
//
//QJsonChannelService::QJsonChannelService (const QByteArray& name, QObject* serviceObj, const QByteArray& version, const QByteArray& description,
//                                          QObject* parent)
//    : QObject (parent) {
//    d_ptr.reset (new QJsonChannelServicePrivate (this, name, version, description, serviceObj));
//}

QJsonChannelService::QJsonChannelService (const QByteArray& name, const QByteArray& version, const QByteArray& description, QObject* serviceObj,
                                          QObject* parent)
    : QObject (parent) {
    d_ptr.reset (new QJsonChannelServicePrivate (this, name, version, description, serviceObj));
}

QJsonChannelService::~QJsonChannelService () {
}

QObject* QJsonChannelService::serviceObj() {
	return d_ptr->serviceObj;
}

const QByteArray& QJsonChannelService::serviceName () const {
    return d_ptr->serviceName;
}

const QJsonObject& QJsonChannelService::serviceInfo () const {
    return d_ptr->serviceInfo;
}

const QMetaObject* QJsonChannelService::serviceMetaObject () const {
    return d_ptr->serviceObj->metaObject ();
}

QString convertToString (QJsonValue::Type t) {
    switch (t) {
    case QJsonValue::Null:
        return "null";
    case QJsonValue::Bool:
        return "boolean";
    case QJsonValue::Double:
        return "number";
    case QJsonValue::String:
        return "string";
    case QJsonValue::Array:
        return "array";
    case QJsonValue::Object:
        return "object";
    case QJsonValue::Undefined:
    default:
        return "undefined";
    }
}

QJsonObject createParameterDescription (const QString& desc, int type) {
    QJsonObject param;
    param["description"] = desc;
    param["type"]        = convertToString (QJsonValue::Type (type));
    //desc["default"] = type;
    return param;
}

QJsonObject QJsonChannelServicePrivate::createServiceInfo () const {
    QJsonObject data;
    data["jsonrpc"] = "2.0";

    QJsonObject info;
    info["title"]   = serviceDescription;
    info["version"] = serviceVersion;

    data["info"] = info;

    QJsonObject   qtMethods;
    QSet<QString> identifiers;

    for (auto iter = methodInfoHash.begin (); iter != methodInfoHash.end (); ++iter) {
        const MethodInfo& info = iter.value ();
        QString           name = info.name;

        if (identifiers.contains (name)) {
            continue;
        }
        identifiers << name;

        QJsonObject method_desc;
        method_desc["summary"]     = name;
        method_desc["description"] = name;

        QJsonObject properties;

        for (const auto& param : info.parameters) {
            properties[param.name] = createParameterDescription (param.name, param.jsType);
        }
        QJsonObject params;
        params["type"]       = "object";
        params["properties"] = properties;

        method_desc["params"] = params;
        method_desc["result"] = createParameterDescription ("return value", convertVariantTypeToJSType (info.returnType));
        qtMethods[name]       = method_desc;
    }

    data["methods"] = qtMethods;
    return data;
}

int QJsonChannelServicePrivate::convertVariantTypeToJSType (int type) {
    switch (type) {
    case QMetaType::Int:
    case QMetaType::UInt:
    case QMetaType::Double:
    case QMetaType::Long:
    case QMetaType::LongLong:
    case QMetaType::Short:
    case QMetaType::Char:
    case QMetaType::ULong:
    case QMetaType::ULongLong:
    case QMetaType::UShort:
    case QMetaType::UChar:
    case QMetaType::Float:
        return QJsonValue::Double; // all numeric types in js are doubles
    case QMetaType::QVariantList:
    case QMetaType::QStringList:
        return QJsonValue::Array;
    case QMetaType::QVariantMap:
        return QJsonValue::Object;
    case QMetaType::QString:
        return QJsonValue::String;
    case QMetaType::Bool:
        return QJsonValue::Bool;
    default:
        break;
    }

    return QJsonValue::Undefined;
}

int QJsonChannelServicePrivate::QJsonChannelMessageType = qRegisterMetaType<QJsonChannelMessage> ("QJsonChannelMessage");

void QJsonChannelServicePrivate::cacheInvokableInfo () {
    QObject*           q        = serviceObj;
    const QMetaObject* obj      = q->metaObject ();
    int                startIdx = q->staticMetaObject.methodCount (); // skip QObject slots
    for (int idx = startIdx; idx < obj->methodCount (); ++idx) {
        const QMetaMethod method = obj->method (idx);
        if ((method.methodType () == QMetaMethod::Slot && method.access () == QMetaMethod::Public) || method.methodType () == QMetaMethod::Signal) {
            QByteArray signature  = method.methodSignature ();
            QByteArray methodName = method.name ();

            MethodInfo info (method);
            if (!info.valid)
                continue;

            if (signature.contains ("QVariant"))
                invokableMethodHash[methodName].append (idx);
            else
                invokableMethodHash[methodName].prepend (idx);
            methodInfoHash[idx] = info;
        }
    }

    serviceInfo = createServiceInfo ();
}

static bool jsParameterCompare (const QJsonArray& parameters, const QJsonChannelServicePrivate::MethodInfo& info) {
    int j = 0;
    for (int i = 0; i < info.parameters.size () && j < parameters.size (); ++i) {
        int jsType = info.parameters.at (i).jsType;
        if (jsType != QJsonValue::Undefined && jsType != parameters.at (j).type ()) {
            if (!info.parameters.at (i).out)
                return false;
        } else {
            ++j;
        }
    }

    return (j == parameters.size ());
}

static bool jsParameterCompare (const QJsonObject& parameters, const QJsonChannelServicePrivate::MethodInfo& info) {
    for (int i = 0; i < info.parameters.size (); ++i) {
        int        jsType = info.parameters.at (i).jsType;
        QJsonValue value  = parameters.value (info.parameters.at (i).name);
        if (value == QJsonValue::Undefined) {
            if (!info.parameters.at (i).out)
                return false;
        } else if (jsType == QJsonValue::Undefined) {
            continue;
        } else if (jsType != value.type ()) {
            return false;
        }
    }

    return true;
}

static inline QVariant convertArgument (const QJsonValue& argument, const QJsonChannelServicePrivate::ParameterInfo& info) {
    if (argument.isUndefined ())
        return QVariant (info.type, Q_NULLPTR);

    if (info.type == QMetaType::QJsonValue || info.type == QMetaType::QVariant || info.type >= QMetaType::User) {
        if (info.type == QMetaType::QVariant)
            return argument.toVariant ();

        QVariant result (argument);
        if (info.type >= QMetaType::User && result.canConvert (info.type))
            result.convert (info.type);
        return result;
    }

    QVariant result = argument.toVariant ();
    if (result.userType () == info.type || info.type == QMetaType::QVariant) {
        return result;
    } else if (result.canConvert (info.type)) {
        result.convert (info.type);
        return result;
    } else if (info.type < QMetaType::User) {
        // already tried for >= user, this is the last resort
        QVariant result (argument);
        if (result.canConvert (info.type)) {
            result.convert (info.type);
            return result;
        }
    }

    return QVariant ();
}

QJsonValue QJsonChannelServicePrivate::convertReturnValue (QVariant& returnValue) {
    if (static_cast<int> (returnValue.type ()) == qMetaTypeId<QJsonObject> ())
        return QJsonValue (returnValue.toJsonObject ());
    else if (static_cast<int> (returnValue.type ()) == qMetaTypeId<QJsonArray> ())
        return QJsonValue (returnValue.toJsonArray ());

    switch (returnValue.type ()) {
    case QMetaType::Bool:
    case QMetaType::Int:
    case QMetaType::Double:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
    case QMetaType::UInt:
    case QMetaType::QString:
    case QMetaType::QStringList:
    case QMetaType::QVariantList:
    case QMetaType::QVariantMap:
        return QJsonValue::fromVariant (returnValue);
    default:
        // if a conversion operator was registered it will be used
        if (returnValue.convert (QMetaType::QJsonValue))
            return returnValue.toJsonValue ();
        else
            return QJsonValue ();
    }
}

static inline QByteArray methodName (const QJsonChannelMessage& request) {
    const QString& methodPath (request.method ());
    return methodPath.midRef (methodPath.lastIndexOf ('.') + 1).toLatin1 ();
}

void QJsonChannelService::cacheInvokableInfo () {
    Q_D (QJsonChannelService);
    d->cacheInvokableInfo ();
}

QJsonChannelMessage QJsonChannelService::dispatch (const QJsonChannelMessage& request) {
    Q_D (QJsonChannelService);
    if (request.type () != QJsonChannelMessage::Request && request.type () != QJsonChannelMessage::Notification) {
        return request.createErrorResponse (QJsonChannel::InvalidRequest, "invalid request");
    }

    const QByteArray& method (methodName (request));
    if (!d->invokableMethodHash.contains (method)) {
        return request.createErrorResponse (QJsonChannel::MethodNotFound, "invalid method called");
    }

    int                        idx = -1;
    QVariantList               arguments;
    const QList<int>&          indexes = d->invokableMethodHash.value (method);
    const QJsonValue&          params  = request.params ();
    QVarLengthArray<void*, 10> parameters;
    QVariant                   returnValue;
    QMetaType::Type            returnType = QMetaType::Void;

    bool usingNamedParameters = params.isObject ();

    // iterate over candidates
    foreach (int methodIndex, indexes) {
        QJsonChannelServicePrivate::MethodInfo& info = d->methodInfoHash[methodIndex];
        bool methodMatch = usingNamedParameters ? jsParameterCompare (params.toObject (), info) : jsParameterCompare (params.toArray (), info);

        if (methodMatch) {
            idx = methodIndex;
            arguments.reserve (info.parameters.size ());
            returnType  = static_cast<QMetaType::Type> (info.returnType);
            returnValue = (returnType == QMetaType::Void) ? QVariant () : QVariant (returnType, Q_NULLPTR);
            if (returnType == QMetaType::QVariant)
                parameters.append (&returnValue);
            else
                parameters.append (returnValue.data ());

            for (int i = 0; i < info.parameters.size (); ++i) {
                const QJsonChannelServicePrivate::ParameterInfo& parameterInfo = info.parameters.at (i);
                QJsonValue incomingArgument = usingNamedParameters ? params.toObject ().value (parameterInfo.name) : params.toArray ().at (i);

                QVariant argument = convertArgument (incomingArgument, parameterInfo);
                if (!argument.isValid ()) {
                    QString message = incomingArgument.isUndefined () ? QString ("failed to construct default object for '%1'").arg (parameterInfo.name)
                                                                      : QString ("failed to convert from JSON for '%1'").arg (parameterInfo.name);
                    return request.createErrorResponse (QJsonChannel::InvalidParams, message);
                }

                arguments.push_back (argument);
                if (parameterInfo.type == QMetaType::QVariant)
                    parameters.append (static_cast<void*> (&arguments.last ()));
                else
                    parameters.append (const_cast<void*> (arguments.last ().constData ()));
            }

            // found a match
            break;
        }
    }

    if (idx == -1) {
        return request.createErrorResponse (QJsonChannel::InvalidParams, "invalid parameters");
    }

    QJsonChannelServicePrivate::MethodInfo& info = d->methodInfoHash[idx];

    QObject* serviceObj = d->serviceObj;
    bool     success    = serviceObj->qt_metacall (QMetaObject::InvokeMetaMethod, idx, parameters.data ()) < 0;
    if (!success) {
        QString message = QString ("dispatch for method '%1' failed").arg (method.constData ());
        return request.createErrorResponse (QJsonChannel::InvalidRequest, message);
    }

    if (info.hasOut) {
        QJsonArray ret;
        if (info.returnType != QMetaType::Void)
            ret.append (QJsonChannelServicePrivate::convertReturnValue (returnValue));
        for (int i = 0; i < info.parameters.size (); ++i)
            if (info.parameters.at (i).out)
                ret.append (QJsonChannelServicePrivate::convertReturnValue (arguments[i]));
        if (ret.size () > 1)
            return request.createResponse (ret);
        return request.createResponse (ret.first ());
    }

    return request.createResponse (QJsonChannelServicePrivate::convertReturnValue (returnValue));
}
