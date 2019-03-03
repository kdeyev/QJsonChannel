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

* build QJsonChannelTufaoHttp library: 
    - cd QJsonChannelTufaoHttp
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
* for test-http-server:
    - run test_http_server
    - run one of:
        - chrome javascript/examples/http/index.html
        - chrome javascript/examples/rpc-http/index.html
        - python python/testqjsonrpc_http.py
        - python python/testqjsonrpc_requests.py

* for any qtWebChannel example need to require to place a list of resources near your executable file:
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

    
