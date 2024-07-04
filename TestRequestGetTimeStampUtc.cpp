#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestGetTimeStampUtc.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestGetTimeStampUtc: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestGetTimeStampUtc::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    QDateTime dateTime;
    RequestGetTimeStampUtc request(context,dateTime);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());
}

QTTESTUTIL_REGISTER_TEST(TestRequestGetTimeStampUtc);
#include "TestRequestGetTimeStampUtc.moc"
