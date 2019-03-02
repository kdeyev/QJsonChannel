/*
 * Copyright (C) 2012-2014 Matt Broadstone
 * Copyright (C) 2013 Fargier Sylvain
 * Contact: http://bitbucket.org/devonit/qjsonrpc
 *
 * This file is part of the QJsonRpc Library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */
#include <QVarLengthArray>
#include <QMetaMethod>
#include <QEventLoop>
#include <QDebug>

#include "QJsonChannelService_p.h"
#include "QJsonChannelService.h"
//
//QJsonRpcServiceRequest::QJsonRpcServiceRequest()
//    : d(new QJsonRpcServiceRequestPrivate)
//{
//}
//
//QJsonRpcServiceRequest::QJsonRpcServiceRequest(const QJsonRpcServiceRequest &other)
//    : d (other.d)
//{
//}
//
//QJsonRpcServiceRequest::QJsonRpcServiceRequest(const QJsonRpcMessage &request,
//                                               QJsonRpcAbstractSocket *socket)
//    : d(new QJsonRpcServiceRequestPrivate)
//{
//    d->request = request;
//    d->socket = socket;
//}
//
//QJsonRpcServiceRequest &QJsonRpcServiceRequest::operator=(const QJsonRpcServiceRequest &other)
//{
//    d = other.d;
//    return *this;
//}
//
//QJsonRpcServiceRequest::~QJsonRpcServiceRequest()
//{
//}
//
//bool QJsonRpcServiceRequest::isValid() const
//{
//    return (d && d->request.isValid() && !d->socket.isNull());
//}
//
//QJsonRpcMessage QJsonRpcServiceRequest::request() const
//{
//    return d->request;
//}
//
//QJsonRpcAbstractSocket *QJsonRpcServiceRequest::socket() const
//{
//    return d->socket;
//}
//
//bool QJsonRpcServiceRequest::respond(QVariant returnValue)
//{
//    if (!d->socket) {
//        qJsonRpcDebug() << Q_FUNC_INFO << "socket was closed";
//        return false;
//    }
//
//    QJsonRpcMessage response =
//        d->request.createResponse(QJsonRpcServicePrivate::convertReturnValue(returnValue));
//    return respond(response);
//}
//
//bool QJsonRpcServiceRequest::respond(const QJsonRpcMessage &response)
//{
//    if (!d->socket) {
//        qJsonRpcDebug() << Q_FUNC_INFO << "socket was closed";
//        return false;
//    }
//
//    QMetaObject::invokeMethod(d->socket, "notify", Q_ARG(QJsonRpcMessage, response));
//    return true;
//}

QJsonRpcServicePrivate::ParameterInfo::ParameterInfo(const QString &n, int t, bool o)
    : type(t),
      jsType(convertVariantTypeToJSType(t)),
      name(n),
      out(o)
{
}

QJsonRpcServicePrivate::MethodInfo::MethodInfo()
    : returnType(QMetaType::Void),
      valid(false),
      hasOut(false)
{
}

QJsonRpcServicePrivate::MethodInfo::MethodInfo(const QMetaMethod &method)
    : returnType(QMetaType::Void),
      valid(true),
      hasOut(false)
{
	name = method.name();

    returnType = method.returnType();
    if (returnType == QMetaType::UnknownType) {
        qJsonRpcDebug() << "QJsonRpcService: can't bind method's return type"
                      << QString(method.name());
        valid = false;
        return;
    }

    parameters.reserve(method.parameterCount());

    const QList<QByteArray> &types = method.parameterTypes();
    const QList<QByteArray> &names = method.parameterNames();
    for (int i = 0; i < types.size(); ++i) {
        QByteArray parameterType = types.at(i);
        const QByteArray &parameterName = names.at(i);
        bool out = parameterType.endsWith('&');

        if (out) {
            hasOut = true;
            parameterType.resize(parameterType.size() - 1);
        }

        int type = QMetaType::type(parameterType);
        if (type == 0) {
            qJsonRpcDebug() << "QJsonRpcService: can't bind method's parameter"
                          << QString(parameterType);
            valid = false;
            break;
        }

        parameters.append(ParameterInfo(parameterName, type, out));
    }
}

QByteArray getServiceName(QObject *obj) {
	const QMetaObject *mo = obj->metaObject();
	for (int i = 0; i < mo->classInfoCount(); i++) {
		const QMetaClassInfo mci = mo->classInfo(i);
		if (mci.name() == QLatin1String("serviceName"))
			return mci.value();
	}

	return QByteArray(mo->className()).toLower();
}

QJsonRpcService::QJsonRpcService(QObject *parent) : QObject(parent) {
	d_ptr.reset(new QJsonRpcServicePrivate(this, getServiceName(this), this));
}

QJsonRpcService::QJsonRpcService(const QByteArray& name, QObject *serviceObj, QObject *parent)
    : QObject(parent)
{
	d_ptr.reset(new QJsonRpcServicePrivate(this, name, serviceObj));
}

QJsonRpcService::~QJsonRpcService()
{
}

const QByteArray& QJsonRpcService::serviceName() const {
	return d_ptr->serviceName;
}

const QJsonObject& QJsonRpcService::serviceInfo() const {
	return d_ptr->serviceInfo;
}

const QMetaObject* QJsonRpcService::serviceMetaObject() const {
	return d_ptr->serviceObj->metaObject();
}

//QJsonRpcServiceRequest QJsonRpcService::currentRequest() const
//{
//    Q_D(const QJsonRpcService);
//    return d->currentRequest;
//}
//
//void QJsonRpcService::beginDelayedResponse()
//{
//    Q_D(QJsonRpcService);
//    d->delayedResponse = true;
//}


QString convertToString(QJsonValue::Type t) {
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

QJsonObject createParameterDescription(const QString& desc, int type) {
	QJsonObject param;
	param["description"] = desc;
	param["type"] = convertToString(QJsonValue::Type(type));
	//desc["default"] = type;
	return param;
}

QJsonObject QJsonRpcServicePrivate::createServiceInfo() const
{
	QJsonObject data;
	data["jsonrpc"] = "2.0";

	QJsonObject info;
	info["title"] = "Service";
	info["version"] = "1.0";

	data["info"] = info;


	//QJsonArray qtSignals;
	QJsonObject qtMethods;
	//QJsonArray qtProperties;
	//QJsonObject qtEnums;

	//const QMetaObject *metaObject = q_ptr->serviceMetaObject();
	//QSet<int> notifySignals;
	QSet<QString> identifiers;
	//for (int i = 0; i < metaObject->propertyCount(); ++i) {
	//	const QMetaProperty &prop = metaObject->property(i);
	//	const QString &propertyName = QString::fromLatin1(prop.name());
	//	QJsonArray propertyInfo;
	//	//propertyInfo.append(i);
	//	//propertyInfo.append(propertyName);
	//	//identifiers << propertyName;
	//	//QJsonArray signalInfo;
	//	//if (prop.hasNotifySignal()) {
	//	//	notifySignals << prop.notifySignalIndex();
	//	//	// optimize: compress the common propertyChanged notification names, just send a 1
	//	//	const QByteArray &notifySignal = prop.notifySignal().name();
	//	//	static const QByteArray changedSuffix = QByteArrayLiteral("Changed");
	//	//	if (notifySignal.length() == changedSuffix.length() + propertyName.length() &&
	//	//		notifySignal.endsWith(changedSuffix) && notifySignal.startsWith(prop.name()))
	//	//	{
	//	//		signalInfo.append(1);
	//	//	}
	//	//	else {
	//	//		signalInfo.append(QString::fromLatin1(notifySignal));
	//	//	}
	//	//	signalInfo.append(prop.notifySignalIndex());
	//	//}
	//	//else 
	//	if (!prop.isConstant()) {
	//		qWarning("Property '%s'' of object '%s' has no notify signal and is not constant, "
	//			"value updates in HTML will be broken!",
	//			prop.name(), q_ptr->serviceMetaObject()->className());
	//	}
	//	//propertyInfo.append(signalInfo);
	//	//propertyInfo.append(wrapResult(prop.read(object), transport));
	//	qtProperties.append(propertyInfo);
	//}
	for (auto iter = methodInfoHash.begin(); iter != methodInfoHash.end(); ++iter) {
		const MethodInfo& info = iter.value();
		QString name = info.name;
		
		if (identifiers.contains(name)) {
			continue;
		}
		identifiers << name;

		QJsonObject method_desc;
		method_desc["summary"] = name;
		method_desc["description"] = name;

		QJsonObject properties;

		for (const auto& param : info.parameters) {
			properties[param.name] = createParameterDescription(param.name, param.jsType);
		}
		QJsonObject params;
		params["type"] = "object";
		params["properties"] = properties;

		method_desc["params"] = params;
		method_desc["result"] = createParameterDescription("return value", convertVariantTypeToJSType(info.returnType));
		qtMethods[name] = method_desc;
	}
	//for (int i = 0; i < metaObject->enumeratorCount(); ++i) {
	//	QMetaEnum enumerator = metaObject->enumerator(i);
	//	QJsonObject values;
	//	for (int k = 0; k < enumerator.keyCount(); ++k) {
	//		values[QString::fromLatin1(enumerator.key(k))] = enumerator.value(k);
	//	}
	//	qtEnums[QString::fromLatin1(enumerator.name())] = values;
	//}
	//data[KEY_SIGNALS] = qtSignals;
	data["methods"] = qtMethods;
	//data["properties"] = qtProperties;
	//if (!qtEnums.isEmpty()) {
	//	data["enums"] = qtEnums;
	//}
	return data;
}

int QJsonRpcServicePrivate::convertVariantTypeToJSType(int type)
{
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
        return QJsonValue::Double;    // all numeric types in js are doubles
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

int QJsonRpcServicePrivate::qjsonRpcMessageType = qRegisterMetaType<QJsonRpcMessage>("QJsonRpcMessage");
void QJsonRpcServicePrivate::cacheInvokableInfo()
{
	QObject* q = serviceObj;
    const QMetaObject *obj = q->metaObject();
    int startIdx = q->staticMetaObject.methodCount(); // skip QObject slots
    for (int idx = startIdx; idx < obj->methodCount(); ++idx) {
        const QMetaMethod method = obj->method(idx);
        if ((method.methodType() == QMetaMethod::Slot &&
             method.access() == QMetaMethod::Public) ||
             method.methodType() == QMetaMethod::Signal) {

            QByteArray signature = method.methodSignature();
            QByteArray methodName = method.name();

            MethodInfo info(method);
            if (!info.valid)
                continue;

            if (signature.contains("QVariant"))
                invokableMethodHash[methodName].append(idx);
            else
                invokableMethodHash[methodName].prepend(idx);
            methodInfoHash[idx] = info;
        }
    }

	serviceInfo = createServiceInfo();
}

static bool jsParameterCompare(const QJsonArray &parameters,
                               const QJsonRpcServicePrivate::MethodInfo &info)
{
    int j = 0;
    for (int i = 0; i < info.parameters.size() && j < parameters.size(); ++i) {
        int jsType = info.parameters.at(i).jsType;
        if (jsType != QJsonValue::Undefined && jsType != parameters.at(j).type()) {
            if (!info.parameters.at(i).out)
                return false;
        } else {
            ++j;
        }
    }

    return (j == parameters.size());
}

static  bool jsParameterCompare(const QJsonObject &parameters,
                                const QJsonRpcServicePrivate::MethodInfo &info)
{
    for (int i = 0; i < info.parameters.size(); ++i) {
        int jsType = info.parameters.at(i).jsType;
        QJsonValue value = parameters.value(info.parameters.at(i).name);
        if (value == QJsonValue::Undefined) {
            if (!info.parameters.at(i).out)
                return false;
        } else if (jsType == QJsonValue::Undefined) {
            continue;
        } else if (jsType != value.type()) {
            return false;
        }
    }

    return true;
}

static inline QVariant convertArgument(const QJsonValue &argument,
                                       const QJsonRpcServicePrivate::ParameterInfo &info)
{
    if (argument.isUndefined())
        return QVariant(info.type, Q_NULLPTR);

    if (info.type == QMetaType::QJsonValue || info.type == QMetaType::QVariant ||
        info.type >= QMetaType::User) {

        if (info.type == QMetaType::QVariant)
            return argument.toVariant();

        QVariant result(argument);
        if (info.type >= QMetaType::User && result.canConvert(info.type))
            result.convert(info.type);
        return result;
    }

    QVariant result = argument.toVariant();
    if (result.userType() == info.type || info.type == QMetaType::QVariant) {
        return result;
    } else if (result.canConvert(info.type)) {
        result.convert(info.type);
        return result;
    } else if (info.type < QMetaType::User) {
        // already tried for >= user, this is the last resort
        QVariant result(argument);
        if (result.canConvert(info.type)) {
            result.convert(info.type);
            return result;
        }
    }

    return QVariant();
}

QJsonValue QJsonRpcServicePrivate::convertReturnValue(QVariant &returnValue)
{
    if (static_cast<int>(returnValue.type()) == qMetaTypeId<QJsonObject>())
        return QJsonValue(returnValue.toJsonObject());
    else if (static_cast<int>(returnValue.type()) == qMetaTypeId<QJsonArray>())
        return QJsonValue(returnValue.toJsonArray());

    switch (returnValue.type()) {
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
        return QJsonValue::fromVariant(returnValue);
    default:
        // if a conversion operator was registered it will be used
        if (returnValue.convert(QMetaType::QJsonValue))
            return returnValue.toJsonValue();
        else
            return QJsonValue();
    }
}

static inline QByteArray methodName(const QJsonRpcMessage &request)
{
    const QString &methodPath(request.method());
    return methodPath.midRef(methodPath.lastIndexOf('.') + 1).toLatin1();
}

QJsonRpcMessage QJsonRpcService::dispatch(const QJsonRpcMessage &request)
{
    Q_D(QJsonRpcService);
    if (request.type() != QJsonRpcMessage::Request &&
        request.type() != QJsonRpcMessage::Notification) {
        return request.createErrorResponse(QJsonRpc::InvalidRequest, "invalid request");
    }

    const QByteArray &method(methodName(request));
    if (!d->invokableMethodHash.contains(method)) {
        return request.createErrorResponse(QJsonRpc::MethodNotFound, "invalid method called");
    }

    int idx = -1;
    QVariantList arguments;
    const QList<int> &indexes = d->invokableMethodHash.value(method);
    const QJsonValue &params = request.params();
    QVarLengthArray<void *, 10> parameters;
    QVariant returnValue;
    QMetaType::Type returnType = QMetaType::Void;

    bool usingNamedParameters = params.isObject();
    foreach (int methodIndex, indexes) {
        QJsonRpcServicePrivate::MethodInfo &info = d->methodInfoHash[methodIndex];
        bool methodMatch = usingNamedParameters ?
            jsParameterCompare(params.toObject(), info) :
            jsParameterCompare(params.toArray(), info);

        if (methodMatch) {
            idx = methodIndex;
            arguments.reserve(info.parameters.size());
            returnType = static_cast<QMetaType::Type>(info.returnType);
            returnValue = (returnType == QMetaType::Void) ?
                QVariant() : QVariant(returnType, Q_NULLPTR);
            if (returnType == QMetaType::QVariant)
                parameters.append(&returnValue);
            else
                parameters.append(returnValue.data());

            for (int i = 0; i < info.parameters.size(); ++i) {
                const QJsonRpcServicePrivate::ParameterInfo &parameterInfo = info.parameters.at(i);
                QJsonValue incomingArgument = usingNamedParameters ?
                    params.toObject().value(parameterInfo.name) :
                    params.toArray().at(i);

                QVariant argument = convertArgument(incomingArgument, parameterInfo);
                if (!argument.isValid()) {
                    QString message = incomingArgument.isUndefined() ?
                        QString("failed to construct default object for '%1'").arg(parameterInfo.name) :
                        QString("failed to convert from JSON for '%1'").arg(parameterInfo.name);
                    return request.createErrorResponse(QJsonRpc::InvalidParams, message);
                }

                arguments.push_back(argument);
                if (parameterInfo.type == QMetaType::QVariant)
                    parameters.append(static_cast<void *>(&arguments.last()));
                else
                    parameters.append(const_cast<void *>(arguments.last().constData()));
            }

            // found a match
            break;
        }
    }

    if (idx == -1) {
        return request.createErrorResponse(QJsonRpc::InvalidParams, "invalid parameters");
    }

    QJsonRpcServicePrivate::MethodInfo &info = d->methodInfoHash[idx];

	QObject* serviceObj = d->serviceObj;
    bool success =
		serviceObj->qt_metacall(QMetaObject::InvokeMetaMethod, idx, parameters.data()) < 0;
    if (!success) {
        QString message = QString("dispatch for method '%1' failed").arg(method.constData());
        return request.createErrorResponse(QJsonRpc::InvalidRequest, message);
    }

    //if (d->delayedResponse) {
    //    d->delayedResponse = false;
    //    return QJsonRpcMessage();
    //}

    if (info.hasOut) {
        QJsonArray ret;
        if (info.returnType != QMetaType::Void)
            ret.append(QJsonRpcServicePrivate::convertReturnValue(returnValue));
        for (int i = 0; i < info.parameters.size(); ++i)
            if (info.parameters.at(i).out)
                ret.append(QJsonRpcServicePrivate::convertReturnValue(arguments[i]));
        if (ret.size() > 1)
            return request.createResponse(ret);
        return request.createResponse(ret.first());
    }

    return request.createResponse(QJsonRpcServicePrivate::convertReturnValue(returnValue));
}
