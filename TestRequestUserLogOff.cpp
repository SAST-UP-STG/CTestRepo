#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestUserLogOn.h"
#include "RequestUserLogOff.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestUserLogOff: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestUserLogOff::performRequest()
{
    // set-up
    UserContext context(RDTG_COMPANYID, "");
    UserLogOn(context);
    RequestUserLogOff request(context);

    // pre-conditions
    QVERIFY(context.sessionId.length() != 0);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);
}

QTTESTUTIL_REGISTER_TEST(TestRequestUserLogOff);
#include "TestRequestUserLogOff.moc"
