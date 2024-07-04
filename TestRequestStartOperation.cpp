#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestStartOperation.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestStartOperation: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestStartOperation::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 2);
    RequestStartOperation request(context, In, 0, QString("no"));

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // config
    QJsonObject config;
    QStringList configExpectedFields;
    configExpectedFields << "ObjViewMessagesConfig" << "ObjGatherCostCodeConfig";
    request.getObjectFromArray(document, 0, config);
    AssertJsonObjectHasFields(config,configExpectedFields);

    // data
    QJsonObject data;
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus";
    request.getObjectFromArray(document, 1, data);
    AssertJsonObjectHasFields(data,dataExpectedFields);
    
    // validate response data - confirmation
    JsonReader rdr(data);
    QString workflowStepCommand = rdr.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_CONFIRMATION));
}

QTTESTUTIL_REGISTER_TEST(TestRequestStartOperation);
#include "TestRequestStartOperation.moc"
