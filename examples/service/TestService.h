#pragma once

#include <QObject>

class TestService : public QObject {
	Q_OBJECT

public:
	TestService(QObject* parent = 0);

	Q_PROPERTY(QString property MEMBER property);
	Q_PROPERTY(float readOnlyProperty READ getReadOnlyProperty);
	Q_PROPERTY(int propertyWithGetterSetter READ getPropertyWithGetterSetter WRITE setPropertyWithGetterSetter);

	Q_INVOKABLE QString invokableGetter();
	Q_INVOKABLE void invokableSetter(QString p);

public Q_SLOTS:
	void    slot();
	void    slotWithParams(const QString& first, bool second, double third);
	QString slotWithParamsAndReturnValue(const QString& name);

	void    slotWithVariantParams(const QString& first, bool second, double third, const QVariant& fourth);
	void    slotWithDefaultParameter(const QString& first, const QString& second = QString());

private:
	QString property = 0;
	float readOnlyProperty = 42;
	int propertyWithGetterSetter = 0;
	QString invokable = QString("I'm getInvokable");

	float getReadOnlyProperty();
	int getPropertyWithGetterSetter();
	void setPropertyWithGetterSetter(int p);
};
