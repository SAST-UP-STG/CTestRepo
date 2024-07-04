#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestUserLogOn.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestUserLogOn: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestUserLogOn::performRequest()
{
    UserContext context(RDTG_COMPANYID, "");
    context.companyNamespace = "PROD";
    strcpy(boardConfig.deviceId, "3a5197c3-2312-4943-89f0-e34782816098");
    context.baseUrl = GetBaseUrl();
    QString userId = "ADMIN";
    QString password = "";
    RequestUserLogOn request(context, userId, password);

    // pre-conditions
    QCOMPARE(boardConfig.deviceId, "3a5197c3-2312-4943-89f0-e34782816098");
    QCOMPARE(context.baseUrl, GetBaseUrl());
    QCOMPARE(context.sessionId, QString(""));
    QVERIFY(context.sessionId.length() == 0);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);
    QVERIFY(context.sessionId.length() != 0);
}

QTTESTUTIL_REGISTER_TEST(TestRequestUserLogOn);
#include "TestRequestUserLogOn.moc"
