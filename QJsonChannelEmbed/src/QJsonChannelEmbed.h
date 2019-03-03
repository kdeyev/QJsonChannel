#pragma once

#include <memory>

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
	QJsonChannelServiceProvider _serviceRepository;
private:
	QJsonChannelEmbedImpl* _impl;
};
