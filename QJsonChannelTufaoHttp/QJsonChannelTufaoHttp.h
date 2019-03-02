#pragma once

#include <Tufao/HttpServer>
#include <QJsonChannel/QJsonChannelServiceProvider.h>
#include "qjsonchanneltufaohttp_export.h"

class QJSONCHANNELTUFAOHTTP_EXPORT QJsonChannelTufaoHttp
{
public:
	QJsonChannelTufaoHttp();

	Tufao::HttpServer _httpServer;
	QJsonRpcServiceProvider _serviceRepository;
};
