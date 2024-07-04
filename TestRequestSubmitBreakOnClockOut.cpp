#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestSubmitBreakOnClockOut.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestSubmitBreakOnClockOut: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestSubmitBreakOnClockOut::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    StartClockOperationAndConfirm(context, companyConfig, 20, Out);
    RequestSubmitBreakOnClockOut request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "StrQuestionOnClockOut";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - question on clock out
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERQUESTIONONCLOCKOUT));    
}

QTTESTUTIL_REGISTER_TEST(TestRequestSubmitBreakOnClockOut);
#include "TestRequestSubmitBreakOnClockOut.moc"
