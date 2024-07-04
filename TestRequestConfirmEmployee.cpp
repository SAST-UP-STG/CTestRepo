#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestConfirmEmployee.h"
#include "RequestStartOperation.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestConfirmEmployee: public QObject
{
    Q_OBJECT
private slots:
    void performRequest_confirmMissedPunch();
    void performRequest_gatherCostCodeOptions();
    void performRequest_gatherCoveredEmployee();
    void performRequest_gatherBreakOnClockOut();
    void performRequest_gatherOverride();
    void performRequest_presentMessage();
    void performRequest_selectCostCode();
    void performRequest_selectJobCode();
    void performRequest_selectTracked();
    void performRequest_shouldComplete();
};

void TestRequestConfirmEmployee::performRequest_confirmMissedPunch()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 7);
    RequestStartOperation clockOutRequest(context, Out, 0, QString("no"));
    QVERIFY(clockOutRequest.performRequest());

    RequestConfirmEmployee request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "StrMissedPunchConfirmationHelp" << "StrMissedPunchConfirmationMessage";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - gather missed confirmation
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERMISSEDCONFIRMATION));
}

void TestRequestConfirmEmployee::performRequest_gatherBreakOnClockOut()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 10);
    RequestStartOperation clockOutRequest(context, Out, 0, QString("no"));
    QVERIFY(clockOutRequest.performRequest());

    RequestConfirmEmployee request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "ObjGatherBreakOnClockOutContext";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - gather question on clock out
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERBREAKONCLOCKOUT));

    // gatherBreakOnClockOutContext
    QStringList gatherBreakOnClockOutExpectedFields;
    gatherBreakOnClockOutExpectedFields << "ObjTimeInputStartTime" << "ObjTimeInputStopTime" << "ObjTextInputClockIn" << "ObjTextInputClockOut" << "BlnEnterBreak" << "BlnRequireBreak" << "DatDateIn" << "DatDateOut" << "TimTimeIn" << "TimTimeOut" << "ObjSelectInputDate" << "ObjTimeInputStartTime" << "ObjBooleanInputConfirmBreak" << "ObjSelectInputBreakType" << "ObjTimeInputStopTime";
    AssertJsonChildObjectHasFields(data, "ObjGatherBreakOnClockOutContext", gatherBreakOnClockOutExpectedFields);

    QJsonObject contextData = dataReader.getField("ObjGatherBreakOnClockOutContext").toObject();
    
    // ObjSelectInputBreakType
    QStringList selectInputBreakTypeExpectedFields;
    selectInputBreakTypeExpectedFields << "BlnIsDisabled" << "IntValue" << "ArrSelectItemOptions";
    AssertJsonChildObjectHasFields(contextData, "ObjSelectInputBreakType", selectInputBreakTypeExpectedFields);
    
    // ObjSelectInputBreakType - options
    QStringList selectItemOptionExpectedFields;
    selectItemOptionExpectedFields << "_IntValue" << "_StrText";
    JsonReader contextReader(contextData);
    QJsonObject selectInputBreakTypeObject = contextReader.getField("ObjSelectInputBreakType").toObject();
    JsonReader selectInputBreakTypeReader(selectInputBreakTypeObject);
    QJsonArray selectItemOptions;
    selectInputBreakTypeReader.jsonArray("ArrSelectItemOptions", selectItemOptions);
    QVERIFY2(selectItemOptions.count() > 0, "No select item options");
    for (int q = 0; q < selectItemOptions.count(); q++)
    {
        QJsonObject selectItemOptionObject = selectItemOptions.at(q).toObject();
        AssertJsonObjectHasFields(selectItemOptionObject, selectItemOptionExpectedFields);
    }

    // ObjTimeInputStartTime
    AssertJsonChildObjectHasField(contextData, "ObjTimeInputStartTime", "TimValue");
}

void TestRequestConfirmEmployee::performRequest_gatherCostCodeOptions()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 9);
    RequestStartOperation clockInRequest(context, In, 0, QString("no"));
    QVERIFY(clockInRequest.performRequest());

    RequestConfirmEmployee request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "ObjGatherCostCodeOptionContext";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - select cost code
    QStringList gatherCostCodeOptionsExpectedFields;
    gatherCostCodeOptionsExpectedFields << "ObjFilterData" << "ArrStringSelectItemSelections";
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERCOSTCODEOPTIONSELECTION));
    AssertJsonChildObjectHasFields(data, "ObjGatherCostCodeOptionContext", gatherCostCodeOptionsExpectedFields);

    QJsonObject gatherCostCodeData = dataReader.getField("ObjGatherCostCodeOptionContext").toObject();
    JsonReader gatherReader(gatherCostCodeData);
    QStringList costCodeExpectedFields;
    costCodeExpectedFields << "StrText";
    QJsonArray costCodeItems;
    gatherReader.jsonArray("ArrStringSelectItemSelections", costCodeItems);
    QVERIFY2(costCodeItems.count() > 0, "No cost codes");
    for (int q = 0; q < costCodeItems.count(); q++)
    {
        QJsonObject costCodeObject = costCodeItems.at(q).toObject();
        AssertJsonObjectHasFields(costCodeObject, costCodeExpectedFields);
    }

    // filter data
    QStringList filterDataExpectedFields;
    filterDataExpectedFields << "BlnActiveOnly" << "BlnSortDescending" << "IntFilterByType" << "ObjPagingData";
    AssertJsonChildObjectHasFields(gatherCostCodeData, "ObjFilterData", filterDataExpectedFields);

    // paging data
    QJsonObject filterData = gatherReader.getField("ObjFilterData").toObject();

    QStringList pagingDataExpectedFields;
    pagingDataExpectedFields << "IntCurrentPage" << "IntEntitiesPerPage" << "IntSelectedEntitiesOutOfPage" << "IntTotalEntities" << "IntTotalPages";
    AssertJsonChildObjectHasFields(filterData, "ObjPagingData", pagingDataExpectedFields);
}

void TestRequestConfirmEmployee::performRequest_gatherCoveredEmployee()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 12);
    RequestStartOperation clockInRequest(context, In, 0, QString("no"));
    QVERIFY(clockInRequest.performRequest());

    RequestConfirmEmployee request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "ObjSelectCoveredEmployeeData";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - gather covered employee
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERCOVEREDEMPLOYEE));

    // ObjSelectCoveredEmployeeData
    QStringList coveredEmployeeDataExpectedFields;
    coveredEmployeeDataExpectedFields << "ObjFilterData" << "StrEmployeeType" << "StrLocationName" << "ArrCoveredEmployees" << "ArrStringLocations" << "ArrStringEmployeeTypes";
    AssertJsonChildObjectHasFields(data, "ObjSelectCoveredEmployeeData",coveredEmployeeDataExpectedFields);
    
    // coveredEmployeeItem
    QStringList coveredEmployeeExpectedFields;
    coveredEmployeeExpectedFields << "IntRecordId" << "StrFirstName" << "StrLastName" << "StrFullName" << "StrLocationName" << "StrEmployeeType";
    
    QJsonObject selectCoveredEmployeeDataObject = dataReader.getField("ObjSelectCoveredEmployeeData").toObject();
    JsonReader selectCoveredReader(selectCoveredEmployeeDataObject);    
    QJsonArray coveredEmployeeItems;
    selectCoveredReader.jsonArray("ArrCoveredEmployees", coveredEmployeeItems);
    QVERIFY2(coveredEmployeeItems.count() > 0, "No coverable employees");
    for (int q = 0; q < coveredEmployeeItems.count(); q++)
    {
        QJsonObject coveredEmployeeObject = coveredEmployeeItems.at(q).toObject();
        AssertJsonObjectHasFields(coveredEmployeeObject, coveredEmployeeExpectedFields);
    }
}

void TestRequestConfirmEmployee::performRequest_gatherOverride()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 11);
    RequestStartOperation clockInRequest(context, In, 0, QString("no"));
    QVERIFY(clockInRequest.performRequest());

    RequestConfirmEmployee request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "ArrOverrides" << "ArrSelectItemUsers";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - gather missed confirmation
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHEROVERRIDE));

    // selectItemUsers
    QStringList selectItemUserExpectedFields;
    selectItemUserExpectedFields << "_StrText" << "_StrSubText" << "_IntValue";
    QJsonArray selectItems;
    dataReader.jsonArray("ArrSelectItemUsers", selectItems);
    QVERIFY2(selectItems.count() > 0, "No user select items");
    for (int q = 0; q < selectItems.count(); q++)
    {
        QJsonObject selectItem = selectItems.at(q).toObject();
        AssertJsonObjectHasFields(selectItem, selectItemUserExpectedFields);
    }
}

void TestRequestConfirmEmployee::performRequest_presentMessage()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 8);
    RequestStartOperation clockInRequest(context, In, 0, QString("no"));
    QVERIFY(clockInRequest.performRequest());

    RequestConfirmEmployee request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "ObjViewMessagesData";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - present messages
    QStringList presentMessageExpectedFields;
    presentMessageExpectedFields << "ArrEmployeeMessages";
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_PRESENTMESSAGES));
    AssertJsonChildObjectHasFields(data, "ObjViewMessagesData", presentMessageExpectedFields);

    // message values
    QJsonObject messageData = dataReader.getField("ObjViewMessagesData").toObject();
    JsonReader gatherReader(messageData);
    QStringList messageExpectedFields;
    messageExpectedFields << "BlnCanDeleteMessage" << "BlnCanMarkAsRead" << "BlnIsRead" << "BlnStartMessage" << "BlnStopMessage" << "DatDateSent" << "IntMessageType" << "IntRecordId" << "StrFormattedMessageReadDateTime" << "StrFormattedMessageSentDate" << "StrMessage" << "StrSentByUserId";
    QJsonArray messageItems;
    gatherReader.jsonArray("ArrEmployeeMessages", messageItems);
    QVERIFY2(messageItems.count() > 0, "No messages");
    for (int q = 0; q < messageItems.count(); q++)
    {
        QJsonObject messageObject = messageItems.at(q).toObject();
        AssertJsonObjectHasFields(messageObject, messageExpectedFields);
    }
}

void TestRequestConfirmEmployee::performRequest_selectCostCode()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 5);
    RequestStartOperation clockInRequest(context, In, 0, QString("no"));
    QVERIFY(clockInRequest.performRequest());

    RequestConfirmEmployee request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "ObjGatherCostCodeData";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - select cost code
    QStringList gatherCostCodeDataExpectedFields;
    gatherCostCodeDataExpectedFields << "IntCostCodeControlType" << "IntSelectedCostCodeId" << "ObjFilterData" << "ArrCostCodes";
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERCOST));
    AssertJsonChildObjectHasFields(data, "ObjGatherCostCodeData", gatherCostCodeDataExpectedFields);

    QJsonObject gatherCostCodeData = dataReader.getField("ObjGatherCostCodeData").toObject();
    JsonReader gatherReader(gatherCostCodeData);
    QStringList costCodeExpectedFields;
    costCodeExpectedFields << "IntRecordId" << "StrFullCode" << "StrDescription";
    QJsonArray costCodeItems;
    gatherReader.jsonArray("ArrCostCodes", costCodeItems);
    QVERIFY2(costCodeItems.count() > 0, "No cost codes");
    for (int q = 0; q < costCodeItems.count(); q++)
    {
        QJsonObject costCodeObject = costCodeItems.at(q).toObject();
        AssertJsonObjectHasFields(costCodeObject, costCodeExpectedFields);
    }
}

void TestRequestConfirmEmployee::performRequest_selectJobCode()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 4);
    RequestStartOperation clockInRequest(context, In, 0, QString("no"));
    QVERIFY(clockInRequest.performRequest());

    RequestConfirmEmployee request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "ObjGatherJobCodeData";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - select job code
    QStringList gatherJobCodeDataExpectedFields;
    gatherJobCodeDataExpectedFields << "IntJobCodeRecordId" << "ObjFilterData" << "ArrEmployeeJobCodes";
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERJOB));
    AssertJsonChildObjectHasFields(data, "ObjGatherJobCodeData", gatherJobCodeDataExpectedFields);

    // jobCodeItem values
    QJsonObject gatherJobCodeData = dataReader.getField("ObjGatherJobCodeData").toObject();
    JsonReader gatherReader(gatherJobCodeData);
    QStringList employeeJobCodeExpectedFields;
    employeeJobCodeExpectedFields << "IntRecordId" << "LngJobCodeId" << "StrDescription" << "StrJobCodeGroup";
    QJsonArray jobCodeItems;
    gatherReader.jsonArray("ArrEmployeeJobCodes", jobCodeItems);
    QVERIFY2(jobCodeItems.count() > 0, "No job codes");
    for (int q = 0; q < jobCodeItems.count(); q++)
    {
        QJsonObject jobCodeObject = jobCodeItems.at(q).toObject();
        AssertJsonObjectHasFields(jobCodeObject, employeeJobCodeExpectedFields);
    }
}

void TestRequestConfirmEmployee::performRequest_selectTracked()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 6);
    RequestStartOperation clockInRequest(context, In, 0, QString("no"));
    QVERIFY(clockInRequest.performRequest());

    RequestConfirmEmployee request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "ObjTrackedFieldContext";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - select tracked
    QStringList gatherTrackedExpectedFields;
    gatherTrackedExpectedFields << "ObjTextInputTrack1" << "ObjTextInputTrack2" << "ObjTextInputTrack3";
    JsonReader dataReader(data);
    QString workflowStepCommand = dataReader.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(WORKFLOW_GATHERTRACKED));
    AssertJsonChildObjectHasFields(data, "ObjTrackedFieldContext", gatherTrackedExpectedFields);

    QJsonObject trackInputData = dataReader.getField("ObjTrackedFieldContext").toObject();
    JsonReader gatherReader(trackInputData);
    QStringList trackedInputExpectedFields;
    trackedInputExpectedFields << "StrText" << "BlnIsDisabled" << "StrMaxDecimalValue" << "StrValue";
    for (int q = 0; q < 3; q++)
    {
        QString field = QString("ObjTextInputTrack%1").arg(q + 1);
        QJsonObject trackedInputFieldObject = gatherReader.getField(field).toObject();
        AssertJsonObjectHasFields(trackedInputFieldObject, trackedInputExpectedFields);
    }
}

void TestRequestConfirmEmployee::performRequest_shouldComplete()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig, 3);
    RequestStartOperation clockInRequest(context, In, 0, QString("no"));
    QVERIFY(clockInRequest.performRequest());

    RequestConfirmEmployee request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // data
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    dataExpectedFields << "LngEmployeeId" << "StrWorkflowStepCommand" << "StrTitle" << "StrClockStatus" << "BlnShouldFinishWorkflow";
    AssertJsonObjectHasFields(data,dataExpectedFields);

    // validate response data - confirmation
    JsonReader rdr(data);
    QVERIFY(rdr.readBool("BlnShouldFinishWorkflow"));
    QString workflowStepCommand = rdr.readString("StrWorkflowStepCommand");
    QCOMPARE(workflowStepCommand, QString(""));
}

QTTESTUTIL_REGISTER_TEST(TestRequestConfirmEmployee);
#include "TestRequestConfirmEmployee.moc"
