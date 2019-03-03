#pragma once

#include <QWebChannel>
#include <QJsonChannelServiceProvider.h>
//#include "qjsonchanneltufaohttp_export.h"

class QJsonChannelEmbedImpl;

class /*QJSONCHANNELTUFAOHTTP_EXPORT*/ QJsonChannelEmbed 
{
public:
	QJsonChannelEmbed();
	~QJsonChannelEmbed();

	QWebChannel _channel; 
	QJsonRpcServiceProvider _serviceRepository;
private:
	QJsonChannelEmbedImpl* _impl = nullptr;
};
