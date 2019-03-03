#pragma once

#include <QtGlobal>
#include <QMetaType>
#include "qjsonchannel_export.h"

// error codes defined by spec
namespace QJsonChannel {
    enum ErrorCode {
        NoError         = 0,
        ParseError      = -32700,           // Invalid JSON was received by the server.
                                            // An error occurred on the server while parsing the JSON text.
        InvalidRequest  = -32600,           // The JSON sent is not a valid Request object.
        MethodNotFound  = -32601,           // The method does not exist / is not available.
        InvalidParams   = -32602,           // Invalid method parameter(s).
        InternalError   = -32603,           // Internal JSON-RPC error.
        ServerErrorBase = -32000,           // Reserved for implementation-defined server-errors.
        UserError       = -32099,           // Anything after this is user defined
        TimeoutError    = -32100
    };
}
Q_DECLARE_METATYPE(QJsonChannel::ErrorCode)

#define QJsonChannelDebug if (qgetenv("QJsonChannel_DEBUG").isEmpty()); else qDebug