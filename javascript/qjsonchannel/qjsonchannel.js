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

    function bindGetterSetter(propertyName, getterName, setterName)
    {
        Object.defineProperty(object, propertyName, {
            configurable: true,
            get:  function () {
                if (getterName === undefined) {
                    console.warn("Property getter for " + propertyName + " is undefined!");
                    
                }

                let function_name = this.__id__ + '.' + getterName;

                // wait for promise and return the result
                return jrpc.call(function_name, []);
            },
            set: function(value) {
                if (setterName === undefined) {
                    console.warn("Property setter for " + propertyName + " is undefined!");
                    return;   
                }
                if (value === undefined) {
                    console.warn("Property setter for " + propertyName + " called with undefined value!");
                    return;
                }

                let function_name = this.__id__ + '.' + setterName;

                // wait for promise
                return jrpc.call(function_name, [value]);
            }
        });
    }

    // ----------------------------------------------------------------------

    let methods = [];
    for (let key in data.methods) {
        methods.push(key);
    }
    methods.forEach(addMethod);

    let properties = {};
    // go over all methods
    for (let key in data.methods) {
        function deCapitalizeFirstLetter(string) {
            return string.charAt(0).toLowerCase() + string.slice(1);
        }

        // getter should start with 'get' and shouldn't have arguments
        let params = data.methods[key].params.properties;
        if (key.startsWith('get') && Object.keys(params).length === 0) {
            let property = deCapitalizeFirstLetter(key.substring(3));
            if (properties[property] === undefined) 
                properties[property] = {'getter':undefined, 'setter':undefined};
            properties[property]['getter'] = key;
        }

        // getter should start with 'get' and should have one arguments
        if (key.startsWith('set') && Object.keys(params).length === 1) {
            let property = deCapitalizeFirstLetter(key.substring(3));
            if (properties[property] === undefined) 
                properties[property] = {'getter':undefined, 'setter':undefined};
            properties[property]['setter'] = key;
        }
    }

    for (let key in properties) {
        let property = properties[key];
        bindGetterSetter(key, property['getter'], property['setter']);
    }

}