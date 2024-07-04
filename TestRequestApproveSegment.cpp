#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestApproveSegment.h"
#include "RequestLoadHours.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestApproveSegment: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestApproveSegment::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 1);
    RequestLoadHours loadHoursRequest(context);

    // pre-conditions
    QVERIFY(loadHoursRequest.performRequest());
    QVERIFY(context.hours()->hours.count() > 0);

    RequestApproveSegment request(context, context.hours()->hours.first());

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);
}

QTTESTUTIL_REGISTER_TEST(TestRequestApproveSegment);
#include "TestRequestApproveSegment.moc"
