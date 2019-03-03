#pragma once

#include <QWebChannel>
#include <QJsonChannelServiceProvider.h>
#include "qjsonchannelembed_export.h"

class QJsonChannelEmbedImpl;

class QJSONCHANNELEMBED_EXPORT QJsonChannelEmbed 
{
public:
	QJsonChannelEmbed();
	~QJsonChannelEmbed();

	QWebChannel _channel; 
	QJsonRpcServiceProvider _serviceRepository;
private:
	QJsonChannelEmbedImpl* _impl = nullptr;
};
