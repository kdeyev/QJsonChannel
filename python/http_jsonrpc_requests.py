#!/usr/bin/python

from jsonrpc_requests import Server
rpc = Server('http://localhost:5555')
print (rpc.object.slot())
print (rpc.object.slotWithParams("one", False, 10))
print (rpc.object.slotWithParamsAndReturnValue("kostya"))
