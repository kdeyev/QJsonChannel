#!/usr/bin/python

import jsonrpc

rpc = jsonrpc.ServerProxy(jsonrpc.JsonRpc20(), jsonrpc.TransportHTTP(addr=("localhost", 5555)))
print (rpc.agent.testMethod())
print (rpc.agent.testMethodWithParams("one", False, 10))
print (rpc.agent.testMethodWithParamsAndReturnValue("kostya"))
