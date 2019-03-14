#include <QDebug>

#include "TestService.h"

TestService::TestService (QObject* parent) : QObject (parent) {
}

void TestService::slot () {
    qDebug () << Q_FUNC_INFO << "called" << endl;
}

void TestService::slotWithParams (const QString& first, bool second, double third) {
    qDebug () << Q_FUNC_INFO << "called with parameters: " << endl
              << " first: " << first << endl
              << "second: " << second << endl
              << " third: " << third << endl;
}

void TestService::slotWithVariantParams (const QString& first, bool second, double third, const QVariant& fourth) {
    qDebug () << Q_FUNC_INFO << "called with variant parameters: " << endl
              << " first: " << first << endl
              << "second: " << second << endl
              << " third: " << third << endl
              << "fourth: " << fourth << endl;
}

QString TestService::slotWithParamsAndReturnValue (const QString& name) {
    return QString ("Hello %1").arg (name);
}

void TestService::slotWithDefaultParameter (const QString& first, const QString& second) {
    qDebug () << Q_FUNC_INFO << endl << "first: " << first << endl << (second.isEmpty () ? "not defined, default parameter" : second) << endl;
}


QString TestService::invokableGetter() {
	return invokable;
}

void TestService::invokableSetter(QString p) {
	invokable = p;
	qDebug() << Q_FUNC_INFO << "called " << endl;
}

float TestService::getReadOnlyProperty() {
	return readOnlyProperty;
}

int TestService::getPropertyWithGetterSetter() {
	return propertyWithGetterSetter;
}

void TestService::setPropertyWithGetterSetter(int p) {
	propertyWithGetterSetter = p;
}
