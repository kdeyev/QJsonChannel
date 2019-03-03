/*
 * Copyright (C) 2012-2014 Matt Broadstone
 * Contact: http://bitbucket.org/devonit/QJsonChannel
 *
 * This file is part of the QJsonChannel Library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */
#ifndef QJsonChannelSERVICEPROVIDER_H
#define QJsonChannelSERVICEPROVIDER_H

#include "QJsonChannelGlobal.h"

class QJsonChannelMessage;
class QJsonChannelService;
class QJsonChannelAbstractSocket;
class QJsonChannelServiceProviderPrivate;
class QJSONCHANNEL_EXPORT QJsonChannelServiceProvider
{
public:
	QJsonChannelServiceProvider();
	~QJsonChannelServiceProvider();
    virtual bool addService(QJsonChannelService *service);
    virtual bool removeService(QJsonChannelService *service);

	QJsonChannelMessage processMessage(const QJsonChannelMessage &message);
protected:


private:
    QScopedPointer<QJsonChannelServiceProviderPrivate> d;

};

#endif // QJsonChannelSERVICEPROVIDER_H
