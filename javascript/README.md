# QJsonChannel JavaScript Client <img src="https://seeklogo.com/images/J/javascript-js-logo-2949701702-seeklogo.com.png" width="24" height="24">

QJsonChannel JavaScript mimics to [QtWebChannel JavaScript API](https://doc.qt.io/qt-5.12/qtwebchannel-javascript.html), but uses [JSON-RPC](http://jsonrpc.org/) protocol over uni-directional communication channel.
In general QJsonChannel JavaScript Client is the client API for QJsonChannel server, which builds client-side stubs based on [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html)

# Motivation
The regular JSON-RPC clien code:
~~~~~~
var jrpc = new simple_jsonrpc();

//set a communication function
jrpc.toStream = function(_msg){
    ...
};

//call
jrpc.call("agent.testMethod").then(function (result) {
    ...
});
~~~~~~
The QJsonChannel client:
~~~~~~
 var jrpc = new simple_jsonrpc();

jrpc.toStream = function(_msg){
    ...
};


new RpcWebChannel(jrpc, function(services) {
    services.agent.testMethod().then(function (result) {
        ...
    });
});

~~~~~~

# References
- [QtWebChannel](https://doc.qt.io/qt-5.12/qtwebchannel-javascript.html) enables peer-to-peer communication between a server (QML/C++ application) and a client (HTML/JavaScript or QML application)
- [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html) is simply a JSON Schema with the additional definition for methods.
- [simple-jsonrpc-js](https://github.com/jershell/simple-jsonrpc-js) - Simple JSON-RPC javascript library. Generate and parse json rpc messages