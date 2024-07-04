#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestConfirmMissedPunch.h"
#include "RequestConfirmMissedPunchSummary.h"
#include "RequestSubmitMissedDateAndTime.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestConfirmMissedPunchSummary: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestConfirmMissedPunchSummary::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    StartClockOperationAndConfirm(context, companyConfig, 14, Out);
    RequestConfirmMissedPunch confirmMissedPunchRequest(context);
    QVERIFY(confirmMissedPunchRequest.performRequest());
    RequestSubmitMissedDateAndTime submitMissedDateAndTimeRequest(context, QDateTime::currentDateTime(), "No");
    QVERIFY(submitMissedDateAndTimeRequest.performRequest());

    RequestConfirmMissedPunchSummary request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus"; 
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - gather missed summary confirmation
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(""));
}

QTTESTUTIL_REGISTER_TEST(TestRequestConfirmMissedPunchSummary);
#include "TestRequestConfirmMissedPunchSummary.moc"
