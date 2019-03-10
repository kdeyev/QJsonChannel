# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`QJsonChannel`](#namespaceQJsonChannel) | 
`class `[`QJsonChannelMessage`](#classQJsonChannelMessage) | 
`class `[`QJsonChannelService`](#classQJsonChannelService) | 
`class `[`QJsonChannelServiceRepository`](#classQJsonChannelServiceRepository) | The main entity of [QJsonChannel](#namespaceQJsonChannel) represents service repository and provides API for a JSON-RPC method invokation.

# namespace `QJsonChannel` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`ErrorCode`](#namespaceQJsonChannel_1a039ecfbd0e447f40a72d508e476839fb)            | 

## Members

#### `enum `[`ErrorCode`](#namespaceQJsonChannel_1a039ecfbd0e447f40a72d508e476839fb) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
NoError            | 
ParseError            | 
InvalidRequest            | 
MethodNotFound            | 
InvalidParams            | 
InternalError            | 
ServerErrorBase            | 
UserError            | 
TimeoutError            | 

# class `QJsonChannelMessage` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`QJsonChannelMessage`](#classQJsonChannelMessage_1afaba5cef0007d1882835e4e607761235)`()` | 
`public  `[`QJsonChannelMessage`](#classQJsonChannelMessage_1ad165544c6207ed0d6368055180095718)`(const `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & other)` | 
`public `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & `[`operator=`](#classQJsonChannelMessage_1a0a93d1b6cd64ef88a4262cd754d05469)`(const `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & other)` | 
`public  `[`~QJsonChannelMessage`](#classQJsonChannelMessage_1afd038907e6ba3e90ef10e363ea993c2b)`()` | 
`public inline void `[`swap`](#classQJsonChannelMessage_1a3d17ab8e0f1e682eaf0feeff8c8d38d7)`(`[`QJsonChannelMessage`](#classQJsonChannelMessage)` & other)` | 
`public `[`QJsonChannelMessage`](#classQJsonChannelMessage)` `[`createResponse`](#classQJsonChannelMessage_1a7695850e38389ffec71e0f34256b1a02)`(const QJsonValue & result) const` | 
`public `[`QJsonChannelMessage`](#classQJsonChannelMessage)` `[`createErrorResponse`](#classQJsonChannelMessage_1a8443da0fda5551ca47935af48d0ab29f)`(`[`QJsonChannel::ErrorCode`](#namespaceQJsonChannel_1a039ecfbd0e447f40a72d508e476839fb)` code,const QString & message,const QJsonValue & data) const` | 
`public `[`QJsonChannelMessage::Type`](#classQJsonChannelMessage_1a809f5209124be94455f504dd95f4a6e1)` `[`type`](#classQJsonChannelMessage_1a795452b9ba6d337373472fedbb147a22)`() const` | 
`public bool `[`isValid`](#classQJsonChannelMessage_1a401f89272794f282842e7411a93833f0)`() const` | 
`public int `[`id`](#classQJsonChannelMessage_1a559c1081f53d6e65f4ed50f90260c6ae)`() const` | 
`public QString `[`serviceName`](#classQJsonChannelMessage_1ae390ad1a8a4f6e5863904597637efd3e)`() const` | 
`public QString `[`method`](#classQJsonChannelMessage_1aed02cd1ff8bcc36f50e3eae610becd73)`() const` | 
`public QJsonValue `[`params`](#classQJsonChannelMessage_1a9ac1a0144875407f76da4748cde0ff48)`() const` | 
`public QJsonValue `[`result`](#classQJsonChannelMessage_1a06a894f759d26cc8b11f2004d0a49b71)`() const` | 
`public int `[`errorCode`](#classQJsonChannelMessage_1a05107fc4b90bcb77b54cf26d4c22d9d5)`() const` | 
`public QString `[`errorMessage`](#classQJsonChannelMessage_1a5985b7723aa3d2dbec8cabeae8b24990)`() const` | 
`public QJsonValue `[`errorData`](#classQJsonChannelMessage_1a1034fe2f6e7616b91a267abe993570f6)`() const` | 
`public QJsonObject `[`toObject`](#classQJsonChannelMessage_1afec3b6172ea66f37ad43e4fa2b607744)`() const` | 
`public QByteArray `[`toJson`](#classQJsonChannelMessage_1aa7ab887e01ccfc1eee90e8e549dafbd8)`() const` | 
`public bool `[`operator==`](#classQJsonChannelMessage_1a34676e15e30aabed7864aa1b706fb7d4)`(const `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & message) const` | 
`public inline bool `[`operator!=`](#classQJsonChannelMessage_1a16a7aadc3a2effc4cb4e097ed5f32104)`(const `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & message) const` | 
`enum `[`Type`](#classQJsonChannelMessage_1a809f5209124be94455f504dd95f4a6e1) | 

## Members

#### `public  `[`QJsonChannelMessage`](#classQJsonChannelMessage_1afaba5cef0007d1882835e4e607761235)`()` 

#### `public  `[`QJsonChannelMessage`](#classQJsonChannelMessage_1ad165544c6207ed0d6368055180095718)`(const `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & other)` 

#### `public `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & `[`operator=`](#classQJsonChannelMessage_1a0a93d1b6cd64ef88a4262cd754d05469)`(const `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & other)` 

#### `public  `[`~QJsonChannelMessage`](#classQJsonChannelMessage_1afd038907e6ba3e90ef10e363ea993c2b)`()` 

#### `public inline void `[`swap`](#classQJsonChannelMessage_1a3d17ab8e0f1e682eaf0feeff8c8d38d7)`(`[`QJsonChannelMessage`](#classQJsonChannelMessage)` & other)` 

#### `public `[`QJsonChannelMessage`](#classQJsonChannelMessage)` `[`createResponse`](#classQJsonChannelMessage_1a7695850e38389ffec71e0f34256b1a02)`(const QJsonValue & result) const` 

#### `public `[`QJsonChannelMessage`](#classQJsonChannelMessage)` `[`createErrorResponse`](#classQJsonChannelMessage_1a8443da0fda5551ca47935af48d0ab29f)`(`[`QJsonChannel::ErrorCode`](#namespaceQJsonChannel_1a039ecfbd0e447f40a72d508e476839fb)` code,const QString & message,const QJsonValue & data) const` 

#### `public `[`QJsonChannelMessage::Type`](#classQJsonChannelMessage_1a809f5209124be94455f504dd95f4a6e1)` `[`type`](#classQJsonChannelMessage_1a795452b9ba6d337373472fedbb147a22)`() const` 

#### `public bool `[`isValid`](#classQJsonChannelMessage_1a401f89272794f282842e7411a93833f0)`() const` 

#### `public int `[`id`](#classQJsonChannelMessage_1a559c1081f53d6e65f4ed50f90260c6ae)`() const` 

#### `public QString `[`serviceName`](#classQJsonChannelMessage_1ae390ad1a8a4f6e5863904597637efd3e)`() const` 

#### `public QString `[`method`](#classQJsonChannelMessage_1aed02cd1ff8bcc36f50e3eae610becd73)`() const` 

#### `public QJsonValue `[`params`](#classQJsonChannelMessage_1a9ac1a0144875407f76da4748cde0ff48)`() const` 

#### `public QJsonValue `[`result`](#classQJsonChannelMessage_1a06a894f759d26cc8b11f2004d0a49b71)`() const` 

#### `public int `[`errorCode`](#classQJsonChannelMessage_1a05107fc4b90bcb77b54cf26d4c22d9d5)`() const` 

#### `public QString `[`errorMessage`](#classQJsonChannelMessage_1a5985b7723aa3d2dbec8cabeae8b24990)`() const` 

#### `public QJsonValue `[`errorData`](#classQJsonChannelMessage_1a1034fe2f6e7616b91a267abe993570f6)`() const` 

#### `public QJsonObject `[`toObject`](#classQJsonChannelMessage_1afec3b6172ea66f37ad43e4fa2b607744)`() const` 

#### `public QByteArray `[`toJson`](#classQJsonChannelMessage_1aa7ab887e01ccfc1eee90e8e549dafbd8)`() const` 

#### `public bool `[`operator==`](#classQJsonChannelMessage_1a34676e15e30aabed7864aa1b706fb7d4)`(const `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & message) const` 

#### `public inline bool `[`operator!=`](#classQJsonChannelMessage_1a16a7aadc3a2effc4cb4e097ed5f32104)`(const `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & message) const` 

#### `enum `[`Type`](#classQJsonChannelMessage_1a809f5209124be94455f504dd95f4a6e1) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
Invalid            | 
Request            | 
Response            | 
Notification            | 
Error            | 
Init            | 

# class `QJsonChannelService` 

```
class QJsonChannelService
  : public QObject
```  

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`QJsonChannelService`](#classQJsonChannelService_1a5855f4bcd39d17b3e1be46256b5d9c00)`(const QByteArray & name,const QByteArray & version,const QByteArray & description,QObject * obj,QObject * parent)` | 
`public  `[`~QJsonChannelService`](#classQJsonChannelService_1a90a97461c0044613d08eb568db0c604f)`()` | 
`public QObject * `[`serviceObj`](#classQJsonChannelService_1a967078206d6dc7dbc4a0dac6992854c6)`()` | 
`public const QByteArray & `[`serviceName`](#classQJsonChannelService_1a461d8371b37d072085c0ade326e78786)`() const` | 
`public const QJsonObject & `[`serviceInfo`](#classQJsonChannelService_1a75731fa78a2872c3195c4f6e95dcff7d)`() const` | 
`public const QMetaObject * `[`serviceMetaObject`](#classQJsonChannelService_1a854b96d489450e3db00775f60b9c62af)`() const` | 

## Members

#### `public  `[`QJsonChannelService`](#classQJsonChannelService_1a5855f4bcd39d17b3e1be46256b5d9c00)`(const QByteArray & name,const QByteArray & version,const QByteArray & description,QObject * obj,QObject * parent)` 

#### `public  `[`~QJsonChannelService`](#classQJsonChannelService_1a90a97461c0044613d08eb568db0c604f)`()` 

#### `public QObject * `[`serviceObj`](#classQJsonChannelService_1a967078206d6dc7dbc4a0dac6992854c6)`()` 

#### `public const QByteArray & `[`serviceName`](#classQJsonChannelService_1a461d8371b37d072085c0ade326e78786)`() const` 

#### `public const QJsonObject & `[`serviceInfo`](#classQJsonChannelService_1a75731fa78a2872c3195c4f6e95dcff7d)`() const` 

#### `public const QMetaObject * `[`serviceMetaObject`](#classQJsonChannelService_1a854b96d489450e3db00775f60b9c62af)`() const` 

# class `QJsonChannelServiceRepository` 

The main entity of [QJsonChannel](#namespaceQJsonChannel) represents service repository and provides API for a JSON-RPC method invokation.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`QJsonChannelServiceRepository`](#classQJsonChannelServiceRepository_1a88ec3fc771c85cbaa2b8381d0c5acc65)`()` | 
`public  `[`~QJsonChannelServiceRepository`](#classQJsonChannelServiceRepository_1ac9091f7c6a130a549de12c2032113006)`()` | 
`public bool `[`addService`](#classQJsonChannelServiceRepository_1a2b7daf30399fccdbc4accef337ece629)`(`[`QJsonChannelService`](#classQJsonChannelService)` * service)` | Adds service to the repository.
`public bool `[`addService`](#classQJsonChannelServiceRepository_1aa807e6e9c5569513c2256f9507f617a8)`(const QByteArray & name,const QByteArray & version,const QByteArray & description,QObject * obj)` | Adds service to the repository.
`public `[`QJsonChannelService`](#classQJsonChannelService)` * `[`getService`](#classQJsonChannelServiceRepository_1a8032e8abcf6be04257ddc7b3d0c85d8d)`(const QByteArray & serviceName)` | Return service by name.
`public QObject * `[`getServiceObject`](#classQJsonChannelServiceRepository_1ad0e0b49946b74d81a37bd013654e1e3e)`(const QByteArray & serviceName)` | Return service object by name.
`public bool `[`removeService`](#classQJsonChannelServiceRepository_1a9455c34f304ff44012d5c876c696cb81)`(`[`QJsonChannelService`](#classQJsonChannelService)` * service)` | Removes service from the repository.
`public bool `[`removeService`](#classQJsonChannelServiceRepository_1a9e5bf74cccf97dde1fe63245a1cc25c0)`(const QByteArray & serviceName)` | Removes service from the repository.
`public `[`QJsonChannelMessage`](#classQJsonChannelMessage)` `[`processMessage`](#classQJsonChannelServiceRepository_1a312e1ae42f822a12b1fcb5a0c585ed03)`(const `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & message)` | Process a JSON-RPC message. In general it means the invogation of a requested function of a requested service.

## Members

#### `public  `[`QJsonChannelServiceRepository`](#classQJsonChannelServiceRepository_1a88ec3fc771c85cbaa2b8381d0c5acc65)`()` 

#### `public  `[`~QJsonChannelServiceRepository`](#classQJsonChannelServiceRepository_1ac9091f7c6a130a549de12c2032113006)`()` 

#### `public bool `[`addService`](#classQJsonChannelServiceRepository_1a2b7daf30399fccdbc4accef337ece629)`(`[`QJsonChannelService`](#classQJsonChannelService)` * service)` 

Adds service to the repository.

#### Parameters
* `service` A service to attach to the repository 

#### Returns
true in case the sevice was added 

#### Returns
false in case of failure

#### `public bool `[`addService`](#classQJsonChannelServiceRepository_1aa807e6e9c5569513c2256f9507f617a8)`(const QByteArray & name,const QByteArray & version,const QByteArray & description,QObject * obj)` 

Adds service to the repository.

#### Parameters
* `name` Service name 

* `version` Service version 

* `description` Service description 

* `obj` Service object 

#### Returns
true In case the sevice was added 

#### Returns
false In case of failure

#### `public `[`QJsonChannelService`](#classQJsonChannelService)` * `[`getService`](#classQJsonChannelServiceRepository_1a8032e8abcf6be04257ddc7b3d0c85d8d)`(const QByteArray & serviceName)` 

Return service by name.

#### Parameters
* `serviceName` a service name to search 

#### Returns
QJsonChannelService* a found sevice

#### `public QObject * `[`getServiceObject`](#classQJsonChannelServiceRepository_1ad0e0b49946b74d81a37bd013654e1e3e)`(const QByteArray & serviceName)` 

Return service object by name.

#### Parameters
* `serviceName` a service name to search 

#### Returns
QJsonChannelService* a found sevice

#### `public bool `[`removeService`](#classQJsonChannelServiceRepository_1a9455c34f304ff44012d5c876c696cb81)`(`[`QJsonChannelService`](#classQJsonChannelService)` * service)` 

Removes service from the repository.

#### Parameters
* `service` A service to remove from the repository 

#### Returns
true in case the sevice was removed 

#### Returns
false in case of failure

#### `public bool `[`removeService`](#classQJsonChannelServiceRepository_1a9e5bf74cccf97dde1fe63245a1cc25c0)`(const QByteArray & serviceName)` 

Removes service from the repository.

#### Parameters
* `serviceName` A service name to remove from the repository 

#### Returns
true in case the sevice was removed 

#### Returns
false in case of failure

#### `public `[`QJsonChannelMessage`](#classQJsonChannelMessage)` `[`processMessage`](#classQJsonChannelServiceRepository_1a312e1ae42f822a12b1fcb5a0c585ed03)`(const `[`QJsonChannelMessage`](#classQJsonChannelMessage)` & message)` 

Process a JSON-RPC message. In general it means the invogation of a requested function of a requested service.

#### Parameters
* `message` JSON-RPC message 

#### Returns
[QJsonChannelMessage](#classQJsonChannelMessage) JSON-RPC response message

Generated by [Moxygen](https://sourcey.com/moxygen)