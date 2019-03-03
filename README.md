# QJsonChannel

## How to build:

* build QJsonChannel library: 
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
* test-tufao-server illustrates the access to JSON-RPC services using QJsonChannel and tufao HTTP server:
    - run test-tufao-server
    - run one of:
        - chrome javascript/examples/http/index.html
        - chrome javascript/examples/rpc-http/index.html
        - python python/testqjsonrpc_http.py
        - python python/testqjsonrpc_requests.py

* The test-embed-qtwebchannel illustrates the hybrid application build on top of QtWebChannel. 
    The test includes the logic of both sides frontend and backend. The communication is built using internal webchannel transport.

* The test-embed-qjsonchannel illustrates the same idea as test-embed-qtwebchannel but uses QJsonChannel "instead of" QtWebChannel.
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

    
