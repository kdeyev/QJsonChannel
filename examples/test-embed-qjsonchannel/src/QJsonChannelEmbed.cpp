#include "QJsonChannelEmbed.h"

#include "QJsonChannelEmbedAdapter.h"

class QJsonChannelEmbedImpl {
public:
	QJsonChannelEmbedAdapter* _adapter;
};

QJsonChannelEmbed::QJsonChannelEmbed() {
	_impl = new QJsonChannelEmbedImpl();
	_impl->_adapter = new QJsonChannelEmbedAdapter(&_serviceRepository);

  _channel.registerObject("jsonRPC", _impl->_adapter);
}

QJsonChannelEmbed::~QJsonChannelEmbed() { 
	//_channel.deregisterObject(_impl->_adapter);
	delete _impl->_adapter;
	delete _impl;
}
