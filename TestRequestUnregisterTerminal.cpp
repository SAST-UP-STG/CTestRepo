#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestUnregisterTerminal.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestUnregisterTerminal: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestUnregisterTerminal::performRequest()
{
    // set-up
    UserContext context(RDTG_COMPANYID, "");
    RegisterTerminal(context);
    RequestUnregisterTerminal request(context);

    // pre-conditions
    QVERIFY(context.sessionId.length() != 0);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);
}

QTTESTUTIL_REGISTER_TEST(TestRequestUnregisterTerminal);
#include "TestRequestUnregisterTerminal.moc"