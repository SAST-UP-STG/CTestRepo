#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestRegisterTerminal.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestRegisterTerminal: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestRegisterTerminal::performRequest()
{
    // set-up
    UserContext context(RDTG_COMPANYID, "");
    UserLogOn(context);
    RequestRegisterTerminal request(context, "Test");

    // pre-conditions
    QVERIFY(context.sessionId.length() != 0);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);
}

QTTESTUTIL_REGISTER_TEST(TestRequestRegisterTerminal);
#include "TestRequestRegisterTerminal.moc"