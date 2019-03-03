#pragma once

#include <QJsonChannelServiceProvider.h>
#include "QJsonChannelBeast_export.h"

#include <boost/asio/ip/tcp.hpp>

class QJsonChannelBeastImpl;
class QJSONCHANNELBEAST_EXPORT QJsonChannelBeast
{
public:
	QJsonChannelBeast(size_t threadCount);
	~QJsonChannelBeast();
	void start (const boost::asio::ip::tcp::endpoint& ep);

	QJsonChannelServiceProvider _serviceRepository;
private:
	QJsonChannelBeastImpl* _impl;
};
