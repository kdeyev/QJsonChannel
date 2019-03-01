#!/usr/bin/python

from jsonrpc_requests import Server
rpc = Server('http://localhost:5555')
print (rpc.agent.testMethod())
print (rpc.agent.testMethodWithParams("one", False, 10))
print (rpc.agent.testMethodWithParamsAndReturnValue("kostya"))
