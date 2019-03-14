# RpcWebChannel JavaScript Client <img src="https://seeklogo.com/images/J/javascript-js-logo-2949701702-seeklogo.com.png" width="24" height="24">

RpcWebChannel JavaScript mimics to [QtWebChannel JavaScript API](https://doc.qt.io/qt-5.12/qtwebchannel-javascript.html), but uses [JSON-RPC](http://jsonrpc.org/) protocol over uni-directional communication channel.
In general RpcWebChannel JavaScript Client is the client API for RpcWebChannel server, which builds client-side stubs based on [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html)

# Motivation
The regular JSON-RPC clien code:
~~~~~~
var jrpc = new simple_jsonrpc();

//set a communication function
jrpc.toStream = function(_msg){
    ...
};

//call
jrpc.call("object.slot").then(function (result) {
    ...
});
~~~~~~
The RpcWebChannel client:
~~~~~~
var jrpc = new simple_jsonrpc();

jrpc.toStream = function(_msg){
    ...
};


new RpcWebChannel(jrpc, function(services) {
    services.object.slot().then(function (result) {
        ...
    });
});
~~~~~~
# Getters/Setters

RpcWebChannel allows the symplyfied access to getters and setter. The regular access looks like:
~~~~~~
 // Properties access 
object.setProperty("I'm setter").then(function (result) {
    document.getElementsByClassName('paragraph')[0].innerHTML += 'object.setProperty result: ' + result + '<br>';
    
    // call Getter as function call
    object.getProperty().then(function (result) {
        document.getElementsByClassName('paragraph')[0].innerHTML += 'object.getProperty    result: ' + result + '<br>';
    });
});
~~~~~~ 

And the symplified version:
~~~~~~
// Anonymous local async function call is nedded for further await
(async function() {
    // wait for setter finish
    await (object.propertyWithGetterSetter = 42);

    // wait for getter finish
    let property = await object.propertyWithGetterSetter;

    // synch access to property
    document.getElementsByClassName('paragraph')[0].innerHTML += 'propertyWithGetterSetter result: ' + property + '<br>';
}());
~~~~~~

# References
- [QtWebChannel](https://doc.qt.io/qt-5.12/qtwebchannel-javascript.html) enables peer-to-peer communication between a server (QML/C++ application) and a client (HTML/JavaScript or QML application)
- [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html) is simply a JSON Schema with the additional definition for methods.
- [simple-jsonrpc-js](https://github.com/jershell/simple-jsonrpc-js) - Simple JSON-RPC javascript library. Generate and parse json rpc messages