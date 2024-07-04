#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestSubmitBreakOnClockOut.h"
#include "RequestSubmitQuestion.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestSubmitQuestion: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestSubmitQuestion::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    StartClockOperationAndConfirm(context, companyConfig, 20, Out);
    RequestSubmitBreakOnClockOut breakRequest(context);
    QVERIFY(breakRequest.performRequest());

    RequestSubmitQuestion request(context, true);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "StrQuestionOnClockOutAcknowledgement";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - question on clock out
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERQUESTIONONCLOCKOUTACK));
}

QTTESTUTIL_REGISTER_TEST(TestRequestSubmitQuestion);
#include "TestRequestSubmitQuestion.moc"
