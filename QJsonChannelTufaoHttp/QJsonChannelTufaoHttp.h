#pragma once

#include <Tufao/HttpServer>
#include <QJsonChannel/qjsonrpcserviceprovider.h>
#include "qjsonchtufaohttp_export.h"

class QJSONCHTUFAOHTTP_EXPORT QJsonChannelTufaoHttp
{
public:
	QJsonChannelTufaoHttp();

	HttpServer _httpServer;
	qjsonrpcserviceprovider _serviceRepository;
};

#endif

