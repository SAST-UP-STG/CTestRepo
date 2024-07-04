#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestConfirmMissedPunch.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestConfirmMissedPunch: public QObject
{
    Q_OBJECT
private slots:
    void performRequest_missedin();
    void performRequest_missedout();
};

void TestRequestConfirmMissedPunch::performRequest_missedin()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    StartClockOperationAndConfirm(context, companyConfig, 14, Out);
    RequestConfirmMissedPunch request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "BlnCanEditMissedIn" << "BlnCanEditMissedOut" << "DatMissedDateIn" << "DatMissedDateOut" << "StrMissedPunchConfirmationHelp" << "StrMissedPunchConfirmationMessage" << "TimMissedTimeIn" << "TimMissedTimeOut"; 
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - gather missed summary confirmation
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERMISSEDIN));
}

void TestRequestConfirmMissedPunch::performRequest_missedout()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    StartClockOperationAndConfirm(context, companyConfig, 15, In);
    RequestConfirmMissedPunch request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "BlnCanEditMissedIn" << "BlnCanEditMissedOut" << "DatMissedDateIn" << "DatMissedDateOut" << "TimMissedTimeIn" << "TimMissedTimeOut";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - gather missed summary confirmation
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERMISSEDOUT));
}

QTTESTUTIL_REGISTER_TEST(TestRequestConfirmMissedPunch);
#include "TestRequestConfirmMissedPunch.moc"
