/****************************************************************************

****************************************************************************/

"use strict";

var RpcWebChannel = function(jrpc, initCallback)
{
    this.services = {};
    let rpcChannel = this;
    
    jrpc.call("__init__").then(function (result) {
        //document.getElementsByClassName('paragraph')[0].innerHTML += '__init__ result: ' + JSON.stringify(result) + '<br>';
        for (let key in result) {
            let service = result[key];
            rpcChannel.services[key] = new JsonChannelObject(key, service, jrpc);
        }

        initCallback(rpcChannel.services);
    });
};

function JsonChannelObject(name, data, jrpc)
{
    this.__server_data__ = data
    this.__id__ = name;
    //webChannel.objects[name] = this;

    // Cache of all properties, updated when a notify signal is emitted
    this.__propertyCache__ = {};

    var object = this;

    function addMethod(methodName)
    {
        object[methodName] = function() {
            var args = [];
            for (var i = 0; i < arguments.length; ++i) {
                args.push(arguments[i]);
            }
            
            let function_name = this.__id__ + '.' + methodName;
            
            // return the promise
            return jrpc.call(function_name, args);
        };
    }

    // ----------------------------------------------------------------------

    let methods = [];
    for (let key in data.methods) {
        methods.push(key);
    }
    methods.forEach(addMethod);

}