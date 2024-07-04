#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestPing.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestPing: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestPing::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    RequestPing request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);
}

QTTESTUTIL_REGISTER_TEST(TestRequestPing);
#include "TestRequestPing.moc"
