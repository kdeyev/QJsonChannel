# QJsonChannel

Overview
=======

QJsonChannel is a Qt implementation of the JSON-RPC protocol, which mimics to the functionality provided by QtWebChannel.
Like QtWebChannel, QJsonChannel is leveraging Qt's meta-object system for method invocation. But unlike QtWebChannel is utilizing the idea of uni-directional communication. The project was started as a try to build an analog of QtWebChannel more suitable for stateless services.

|                           | QtWebChannel          | QJsonChannel          |
|---                        |---                    |---                    |
| RPC protocol              | Internal JSON-based   | JSON-RPC 2.0          |
| Communication protocol    | uni-directional       | bi-directional        |
| Stateless communication   | -                     |  +                    |
| Server->Client call       | +                     |  -                    |
| WebSocket support         | +                     |  +                    |
| HTTP support              | -                     |  +                    |
| Services list             | Internal representation | JSON Schema Service Descriptor |

Libraries
--------
* QJsonChannel - RPC layer based on top of Qt meta objects invocation
* QJsonChannelEmbed - the library utilizes QtWebChannel internal transport for passing messages to QJsonChannel RPC layer
* QJsonChannelTufao - the library utilizes Tufao library for WebSocket and HTTP transport over QJsonChannel RPC layer
* qjsonchannel.js - JavaScript layer over simple-jsonrpc-js which uses the JSON Schema Service Descriptor for building JS stubs on client side. 

Examples
--------
* 

References
==========
- [QJsonRpc](https://bitbucket.org/devonit/qjsonrpc)
- [TUFÃO](http://vinipsmaker.github.io/tufao/)
- [simple-jsonrpc-js](https://github.com/jershell/simple-jsonrpc-js) - Simple JSON-RPC javascript library. Generate and parse json rpc messages
- [jsonrpc.py])(https://www.simple-is-better.org/rpc/jsonrpc.py) - Simple Python JSON-RPC client supports client side stubs
- [JSON](http://www.json.org/) is a lightweight data interchange format.
- [JSON-RPC](http://jsonrpc.org/) is lightweight remote procedure call protocol similar to XML-RPC.
- [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html)

Requirements
============

- Qt 5.5 or greater

Features
========

- Support for JSON-RPC 2.0
- Easily create services using the Qt meta object system
- QtScript integration

Building
========

# QJsonChannel library: 
    - cd QJsonChannel
    - mkdir build
    - cd build
    - cmake -G "Visual Studio 15 2017 Win64" ..
    - cmake --build . --target install

* build tufao library: 
    - cd tufao
    - mkdir build
    - cd build
    - cmake -DCMAKE_INSTALL_PREFIX:PATH=../install -G "Visual Studio 15 2017 Win64" ..
    - cmake --build . --target install

* build QJsonChannelTufao library: 
    - cd QJsonChannelTufao
    - mkdir build
    - cd build
    - cmake -G "Visual Studio 15 2017 Win64" ..
    - cmake --build . --target install

* build QJsonChannelEmbed library: 
    - cd QJsonChannelEmbed
    - mkdir build
    - cd build
    - cmake -G "Visual Studio 15 2017 Win64" ..
    - cmake --build . --target install

* build examples library: 
    - cd examples
    - mkdir build
    - cd build
    - cmake -G "Visual Studio 15 2017 Win64" ..
    - cmake --build . --target install

## Examples

* (Javascript) [http](https://github.com/kdeyev/QJsonChannel/blob/master/javascript/examples/http/index.html) Example shows access to JSON-RPC server using HTTP transport
* (Javascript) [rpc-http](https://github.com/kdeyev/QJsonChannel/blob/master/javascript/examples/rpc-http/index.html) Example shows access to JSON-RPC server using HTTP transport and client side stubs
* (Javascript) [ws](https://github.com/kdeyev/QJsonChannel/blob/master/javascript/examples/ws/index.html) Example shows access to JSON-RPC server using WebSocket transport
* (Javascript) [rpc-ws](https://github.com/kdeyev/QJsonChannel/blob/master/javascript/examples/rpc-ws/index.html) Example shows access to JSON-RPC server using WebSocket transport and client side stubs
* (Python) [testqjsonrpc_http.py](https://github.com/kdeyev/QJsonChannel/blob/master/python/testqjsonrpc_http.py) Example shows access to JSON-RPC server using HTTP transport
* (Python) [testqjsonrpc_websocket.py](https://github.com/kdeyev/QJsonChannel/blob/master/python/testqjsonrpc_websocket.py) EExample shows access to JSON-RPC server using WebSocket transport
* (Python) [testqjsonrpc_requests.py](https://github.com/kdeyev/QJsonChannel/blob/master/python/testqjsonrpc_requests.py) Example shows access to JSON-RPC server using HTTP transport and client side stubs
* (C++) [test-tufao-server](https://github.com/kdeyev/QJsonChannel/blob/master/examples/test-tufao-server/src/main.cpp) illustrates the access to JSON-RPC services using QJsonChannel and tufao HTTP server:
    - run test-tufao-server
    - run one of:
        - chrome javascript/examples/http/index.html
        - chrome javascript/examples/rpc-http/index.html
        - python python/testqjsonrpc_http.py
        - python python/testqjsonrpc_requests.py
* (C++) [test-embed-qtwebchannel](https://github.com/kdeyev/QJsonChannel/blob/master/examples/test-embed-qtwebchannel/src/main.cpp) illustrates the hybrid application build on top of QtWebChannel. 
    The test includes the logic of both sides frontend and backend. The communication is built using internal webchannel transport.
* (C++) [test-embed-qjsonchannel](https://github.com/kdeyev/QJsonChannel/blob/master/examples/test-embed-qjsonchannel/src/main.cpp) illustrates the same idea as test-embed-qtwebchannel but uses QJsonChannel "instead of" QtWebChannel.
    Actually I have difficulties with the internal web channel transport access.
    So, currently I'm using the QtWebChannel for message passing, bot the service invocation is done using QSsonChannel.
    
* for any QtWebChannel example need to require to place a list of resources near your executable file:
    - qt.conf
    - QtWebEngineProcess
        - QtWebEngineProcess executable         from Qt/bin
        - icudtl.dat                            from Qt/resources
        - qtwebengine_devtools_resources.pak    from Qt/resources
        - qtwebengine_resources.pak             from Qt/resources
        - qtwebengine_resources_100p.pak        from Qt/resources
        - qtwebengine_resources_200p.pak        from Qt/resources
        - qtwebengine_locales                   from Qt/translations/qtwebengine_locales
            -   many files 

    use chrome http://localhost:9090 for debugging