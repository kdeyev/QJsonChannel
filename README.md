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
