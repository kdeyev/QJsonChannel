#pragma once

#include <QObject>

class TestService : public QObject
{
	Q_OBJECT
		//Q_CLASSINFO("serviceName", "agent")
public:
	TestService(QObject *parent = 0);

	public Q_SLOTS:
	void testMethod();
	void testMethodWithParams(const QString &first, bool second, double third);
	void testMethodWithVariantParams(const QString &first, bool second, double third, const QVariant &fourth);
	QString testMethodWithParamsAndReturnValue(const QString &name);
	void testMethodWithDefaultParameter(const QString &first, const QString &second = QString());

	QString immediateResponse();
	QString longTaskWithImmediateResponse();
};
