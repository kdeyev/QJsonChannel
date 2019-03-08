- [Overview](#overview)
- [Components](#components)
- [Build](#build)
  - [Build Tufao](#build-tufao)
  - [Build QJsonChannel](#build-qjsonchannel)
- [Examples](#examples)
  - [Server side](#server-side)
  - [Client side](#client-side)
    - [Client-side examples tips](#client-side-examples-tips)
  - [Hybrid (Server + Client)](#hybrid-server--client)
    - [Hybrid Examples Tips](#hybrid-examples-tips)
- [Requirements](#requirements)
- [References](#references)

# Overview

QJsonChannel is a Qt implementation of the JSON-RPC protocol, which mimics to the functionality provided by QtWebChannel.
Like QtWebChannel, QJsonChannel is leveraging Qt's meta-object system for method invocation. But unlike QtWebChannel is utilizing the idea of uni-directional communication. The project was started as a try to build an analog of QtWebChannel more suitable for stateless services.

|                           | QtWebChannel              | QJsonChannel                  |
|---                        |---                        |---                            |
| RPC protocol              | Internal JSON-based       | JSON-RPC 2.0                  |
| Communication protocol    | bi-directional            | uni-directional               |
| Stateless communication   | -                         |  +                            |
| Server->Client call       | +                         |  -                            |
| WebSocket support         | +                         |  +                            |
| HTTP support              | -                         |  +                            |
| Services list             | Internal representation   | JSON Schema Service Descriptor|

# Components

* QJsonChannel - RPC layer based on top of Qt meta objects invocation
* QJsonChannelEmbed - the library utilizes QtWebChannel internal transport for passing messages to QJsonChannel RPC layer
* QJsonChannelBeast - the library utilizes Boost.Beast library for WebSocket and HTTP transport over QJsonChannel RPC layer
* QJsonChannelTufao - the library utilizes Tufao library for WebSocket and HTTP transport over QJsonChannel RPC layer
* qjsonchannel.js - JavaScript layer over simple-jsonrpc-js which uses the JSON Schema Service Descriptor for building JS stubs on client side. 

# Build

## Build Tufao 
1. set BOOST_ROOT environment variable
2. cd QJsonChannel
3. mkdir build && cd mkdir
4. cmake -DCMAKE_INSTALL_PREFIX:PATH=../install -G "Visual Studio 15 2017 Win64" ..
5. cmake --build . --target install

## Build QJsonChannel
1. cd QJsonChannel
3. mkdir build && cd mkdir
2. cmake -G "Visual Studio 15 2017 Win64" ..
4. cmake --build . 
5. (for installation) cmake --build . --target install 
6. (for VS debugging) devenv Project.sln

# Examples

## Server side
- <img src="https://seeklogo.com/images/C/c-logo-43CE78FF9C-seeklogo.com.png" width="12" height="12"> [Tufao QJsonChannel Server](https://github.com/kdeyev/QJsonChannel/tree/master/examples/tufao-server) illustrates the building of JSON-RPC services using QJsonChannel and HTTP/WebSocket Tufao server. The QJsonChannel server supports [JSON-RPC](http://jsonrpc.org/)  calls and provides service descriptions by [JSON Schema Service Descriptor](https://jsonrpc.org/historical/).
- <img src="https://seeklogo.com/images/C/c-logo-43CE78FF9C-seeklogo.com.png" width="12" height="12"> [Boost.Beast QJsonChannel Server](https://github.com/kdeyev/QJsonChannel/tree/master/examples/beast-server) illustrates the building of JSON-RPC services using QJsonChannel and HTTP/WebSocket Boost.Beast server. The QJsonChannel server supports [JSON-RPC](http://jsonrpc.org/)  calls and provides service descriptions by [JSON Schema Service Descriptor](https://jsonrpc.org/historical/).
  
## Client side
- <img src="https://seeklogo.com/images/J/javascript-js-logo-2949701702-seeklogo.com.png" width="12" height="12"> [HTTP JSON-RPC Client](https://github.com/kdeyev/QJsonChannel/blob/master/javascript/examples/http-client/index.html) shows access to JSON-RPC server using HTTP transport 
- <img src="https://seeklogo.com/images/J/javascript-js-logo-2949701702-seeklogo.com.png" width="12" height="12"> [WebSocket JSON-RPC Client](https://github.com/kdeyev/QJsonChannel/blob/master/javascript/examples/ws-client/index.html) shows access to JSON-RPC server using WebSocket transport.
- <img src="https://seeklogo.com/images/J/javascript-js-logo-2949701702-seeklogo.com.png" width="12" height="12"> [WebSocket QJsonChannel Client](https://github.com/kdeyev/QJsonChannel/blob/master/javascript/examples/rpc-ws-client/index.html) shows access to QJsonChannel server using WebSocket transport and client-side stubs.
- <img src="https://seeklogo.com/images/J/javascript-js-logo-2949701702-seeklogo.com.png" width="12" height="12"> [HTTP QJsonChannel Client](https://github.com/kdeyev/QJsonChannel/blob/master/javascript/examples/rpc-http-client/index.html) shows access to JSON-RPC server using HTTP transport and client side stubs
- <img src="https://seeklogo.com/images/R/react-logo-7B3CE81517-seeklogo.com.png" width="12" height="12"> [Automatic UI Generation using React and QJsonChannel](https://github.com/kdeyev/QJsonChannel/tree/master/javascript/examples/react-froms-client) shows how to generate UI forms for RPC functions exposed by the QJsonChannel server. 
- <img src="https://seeklogo.com/images/P/python-logo-A32636CAA3-seeklogo.com.png" width="12" height="12"> [HTTP JSON-RPC Client](https://github.com/kdeyev/QJsonChannel/blob/master/python/http_jsonrpc_requests.py) shows access to JSON-RPC server using HTTP transport and client-side stubs using [jsonrpc-requests Python libary](https://pypi.org/project/jsonrpc-requests/)

### Client-side examples tips
All of these tests can work with with [Tufao QJsonChannel Server](https://github.com/kdeyev/QJsonChannel/tree/master/examples/tufao-server) or [Boost.Beast QJsonChannel Server](https://github.com/kdeyev/QJsonChannel/tree/master/examples/beast-server).

## Hybrid (Server + Client)
* <img src="https://seeklogo.com/images/C/c-logo-43CE78FF9C-seeklogo.com.png" width="12" height="12"> <img src="https://seeklogo.com/images/Q/qt-logo-1631E0218A-seeklogo.com.png" width="12" height="12"> <img src="https://seeklogo.com/images/J/javascript-js-logo-2949701702-seeklogo.com.png" width="12" height="12"> [QtWebChannel Hybrid Application](https://github.com/kdeyev/QJsonChannel/blob/master/examples/qtwebchannel-hybrid/src/main.cpp) illustrates a hybrid approach of application building. The example includes the logic of both frontend and backend and uses [QtWebChannel](https://doc.qt.io/qt-5.12/qtwebchannel-index.html) for the communication between JavaScript and C++.
* <img src="https://seeklogo.com/images/C/c-logo-43CE78FF9C-seeklogo.com.png" width="12" height="12"> <img src="https://seeklogo.com/images/Q/qt-logo-1631E0218A-seeklogo.com.png" width="12" height="12"> <img src="https://seeklogo.com/images/J/javascript-js-logo-2949701702-seeklogo.com.png" width="12" height="12"> [QJsonChannel Hybrid Application](https://github.com/kdeyev/QJsonChannel/blob/master/examples/qjsonchannel-hybrid/src/main.cpp) illustrates the same idea as [QtWebChannel Hybrid Application](https://github.com/kdeyev/QJsonChannel/blob/master/examples/qtwebchannel-hybrid/src/main.cpp) but uses QJsonChannel "instead of" QtWebChannel.
Actually I have difficulties with the internal web channel transport access.
So, currently I'm using the QtWebChannel for message passing, but the service invocation is done using QJsonChannel.
### Hybrid Examples Tips
1. For any QtWebChannel example may require [Deploying Qt WebEngine Applications](https://doc.qt.io/qt-5/qtwebengine-deploying.html).
2. Use Google Chrome <img src="https://seeklogo.com/images/G/google-chrome-logo-95B6A0B483-seeklogo.com.png" width="12" height="12"> http://localhost:9090 for debugging

Requirements
============
- Qt 5.5 or greater
- boost 1.67 or greater

References
==========
- [QJsonRpc](https://bitbucket.org/devonit/qjsonrpc)
- [Boost.Beast](https://github.com/boostorg/beast)
- [TUFÃO](http://vinipsmaker.github.io/tufao/)
- [simple-jsonrpc-js](https://github.com/jershell/simple-jsonrpc-js) - Simple JSON-RPC javascript library. Generate and parse json rpc messages
- [jsonrpc-requests](https://pypi.org/project/jsonrpc-requests/) - compact and simple JSON-RPC client implementation
- [JSON](http://www.json.org/) is a lightweight data interchange format.
- [JSON-RPC](http://jsonrpc.org/) is lightweight remote procedure call protocol similar to XML-RPC.
- [JSON Schema Service Descriptor](https://jsonrpc.org/historical/json-schema-service-descriptor.html)
- [React JSon Schema Form](https://github.com/mozilla-services/react-jsonschema-form) A React component for building Web forms from JSON Schema.