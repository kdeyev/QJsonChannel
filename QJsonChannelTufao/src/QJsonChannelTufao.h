#pragma once

#include <HttpServer>
#include <QJsonChannelServiceRepository.h>
#include "QJsonChannelTufao_export.h"

class QJSONCHANNELTUFAO_EXPORT QJsonChannelTufao
{
public:
	QJsonChannelTufao();

	Tufao::HttpServer _httpServer;
	QJsonChannelServiceRepository _serviceRepository;
};
