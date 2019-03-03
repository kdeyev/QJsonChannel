#pragma once

#include <HttpServer>
#include <QJsonChannelServiceProvider.h>
#include "QJsonChannelTufao_export.h"

class QJSONCHANNELTUFAO_EXPORT QJsonChannelTufao
{
public:
	QJsonChannelTufao();

	Tufao::HttpServer _httpServer;
	QJsonRpcServiceProvider _serviceRepository;
};
