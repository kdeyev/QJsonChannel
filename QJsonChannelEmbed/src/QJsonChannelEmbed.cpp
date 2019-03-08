#include "QJsonChannelEmbed.h"

#include "QJsonChannelEmbedAdapter.h"

class QJsonChannelEmbedImpl {
public:
 	QJsonChannelEmbedImpl(QJsonChannelServiceRepository* serviceRepository) 
	 : _adapter (new QJsonChannelEmbedAdapter(serviceRepository)) {
	 }
	std::unique_ptr<QJsonChannelEmbedAdapter> _adapter;
};

QJsonChannelEmbed::QJsonChannelEmbed() : _impl(new QJsonChannelEmbedImpl(&_serviceRepository)){
	_channel.registerObject("jsonRPC", _impl->_adapter.get());
}

QJsonChannelEmbed::~QJsonChannelEmbed() {
	delete _impl;
}