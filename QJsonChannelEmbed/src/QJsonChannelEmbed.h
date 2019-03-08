#pragma once

#include <memory>

#include <QWebChannel>
#include <QJsonChannelServiceRepository.h>
#include "qjsonchannelembed_export.h"

class QJsonChannelEmbedImpl;

class QJSONCHANNELEMBED_EXPORT QJsonChannelEmbed 
{
public:
	QJsonChannelEmbed();
	~QJsonChannelEmbed();

	QWebChannel _channel; 
	QJsonChannelServiceRepository _serviceRepository;
private:
	QJsonChannelEmbedImpl* _impl;
};
