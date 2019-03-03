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
    this.__id__ = name;
    //webChannel.objects[name] = this;

    // Cache of all properties, updated when a notify signal is emitted
    this.__propertyCache__ = {};

    var object = this;

    // ----------------------------------------------------------------------

    /*
    this.unwrapJsonChannelObject = function(response)
    {
        if (response instanceof Array) {
            // support list of objects
            var ret = new Array(response.length);
            for (var i = 0; i < response.length; ++i) {
                ret[i] = object.unwrapJsonChannelObject(response[i]);
            }
            return ret;
        }
        //if (!response
        //    || !response["__JsonChannelObject*__"]
        //    || response.id === undefined) {
        //    return response;
        //}

        //var objectId = response.id;
        //if (webChannel.objects[objectId])
        //    return webChannel.objects[objectId];

        if (!response.data) {
            console.error("Cannot unwrap unknown JsonChannelObject " + objectId + " without data.");
            return;
        }

        var JsonChannelObject = new JsonChannelObject( objectId, response.data, webChannel );
        JsonChannelObject.destroyed.connect(function() {
            if (webChannel.objects[objectId] === JsonChannelObject) {
                delete webChannel.objects[objectId];
                // reset the now deleted JsonChannelObject to an empty {} object
                // just assigning {} though would not have the desired effect, but the
                // below also ensures all external references will see the empty map
                // NOTE: this detour is necessary to workaround QTBUG-40021
                var propertyNames = [];
                for (var propertyName in JsonChannelObject) {
                    propertyNames.push(propertyName);
                }
                for (var idx in propertyNames) {
                    delete JsonChannelObject[propertyNames[idx]];
                }
            }
        });
        // here we are already initialized, and thus must directly unwrap the properties
        JsonChannelObject.unwrapProperties();
        return JsonChannelObject;
    }

    this.unwrapProperties = function()
    {
        for (var propertyIdx in object.__propertyCache__) {
            object.__propertyCache__[propertyIdx] = object.unwrapJsonChannelObject(object.__propertyCache__[propertyIdx]);
        }
    }
    */

    function addMethod(methodName)
    {
        object[methodName] = function() {
            var args = [];
            //var callback;
            for (var i = 0; i < arguments.length; ++i) {
                //if (typeof arguments[i] === "function")
                //    callback = arguments[i];
                //else
                    args.push(arguments[i]);
            }
            
            let function_name = this.__id__ + '.' + methodName;
            
            // return the promise
            return jrpc.call(function_name, args);
        };
    }

    /*
    function bindGetterSetter(propertyInfo)
    {
        var propertyIndex = propertyInfo[0];
        var propertyName = propertyInfo[1];
        var notifySignalData = propertyInfo[2];
        // initialize property cache with current value
        // NOTE: if this is an object, it is not directly unwrapped as it might
        // reference other JsonChannelObject that we do not know yet
        object.__propertyCache__[propertyIndex] = propertyInfo[3];

        if (notifySignalData) {
            if (notifySignalData[0] === 1) {
                // signal name is optimized away, reconstruct the actual name
                notifySignalData[0] = propertyName + "Changed";
            }
            addSignal(notifySignalData, true);
        }

        Object.defineProperty(object, propertyName, {
            configurable: true,
            get: function () {
                var propertyValue = object.__propertyCache__[propertyIndex];
                if (propertyValue === undefined) {
                    // This shouldn't happen
                    console.warn("Undefined value in property cache for property \"" + propertyName + "\" in object " + object.__id__);
                }

                return propertyValue;
            },
            set: function(value) {
                if (value === undefined) {
                    console.warn("Property setter for " + propertyName + " called with undefined value!");
                    return;
                }
                object.__propertyCache__[propertyIndex] = value;
                webChannel.exec({
                    "type": QWebChannelMessageTypes.setProperty,
                    "object": object.__id__,
                    "property": propertyIndex,
                    "value": value
                });
            }
        });

    }
    */

    // ----------------------------------------------------------------------

    let methods = [];
    for (let key in data.methods) {
        methods.push(key);
    }
    methods.forEach(addMethod);

    //data.properties.forEach(bindGetterSetter);

    //data.signals.forEach(function(signal) { addSignal(signal, false); });

    /*for (var name in data.enums) {
        object[name] = data.enums[name];
    }*/
}