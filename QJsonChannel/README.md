# QJsonChannel Core Library <img src="https://seeklogo.com/images/C/c-logo-43CE78FF9C-seeklogo.com.png" width="24" height="24">

QJsonChannel utilises ideas and some implementation details of [QJsonRpc](https://bitbucket.org/devonit/qjsonrpc) implementation. QJsonRpc library has tight integration with communication transport and supports server-to-client messages. So QJsonChannel library development for resolving these QJsonRpc specialties. 
In addition, QJsonChannel supports [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html) for services and methods discovery.

The main component of QJsonChannel is QJsonChannelServiceRepositor. 

## Motivation:
~~~~~~
// Build a service repository
QJsonChannelServiceRepositor serviceRepository;

// Build a service object
QObject* testService = new TestService();

// Add the service to the repository
serviceRepository.addService ("agent", "1.0", "test service", testService);
~~~~~~

## Message processing
~~~~~~

// A JSON-RPC request
QJsonChannelMessage request;
request.fromJson(...);

QJsonChannelMessage response = serviceRepository.processMessage (request);

// Get a JSOON-RPC response
QByteArray ... = response.toJson();
~~~~~~

## References
- [QJsonRpc](https://bitbucket.org/devonit/qjsonrpc) is a Qt implementation of the JSON-RPC protocol.
- [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html) is simply a JSON Schema with the additional definition for methods.