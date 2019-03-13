#pragma once

#include <QObject>

class TestService : public QObject {
	Q_OBJECT

public:
	TestService(QObject* parent = 0);

	Q_PROPERTY(int property1 MEMBER property1);
	Q_PROPERTY(float property2 READ getProperty2);
	Q_PROPERTY(QString property3 READ getProperty3 WRITE setProperty3);

	float getProperty2() {
		return property2;
	}

	QString getProperty3() {
		return property3;
	}

	void setProperty3(QString p) {
		property3 = p;
	}

	Q_INVOKABLE QString getInvokable();

	Q_INVOKABLE void setInvokable(QString p);

	public Q_SLOTS:
	void    testMethod();
	void    testMethodWithParams(const QString& first, bool second, double third);
	void    testMethodWithVariantParams(const QString& first, bool second, double third, const QVariant& fourth);
	QString testMethodWithParamsAndReturnValue(const QString& name);
	void    testMethodWithDefaultParameter(const QString& first, const QString& second = QString());

private:
	int property1 = 0;
	float property2 = 0;
	QString property3;
	QString invokable = QString("I'm getInvokable");
};
