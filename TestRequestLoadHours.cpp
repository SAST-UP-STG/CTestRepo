#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestLoadHours.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestLoadHours: public QObject
{
    Q_OBJECT
private slots:
    void performRequest_current();
    void performRequest_next();
    void performRequest_period();
    void performRequest_previous();
};

void TestRequestLoadHours::performRequest_current()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    RequestLoadHours request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());
    // config
    QJsonObject config;
    QStringList configExpectedFields;
    configExpectedFields << "BlnCanAddShiftNotes" << "BlnCanViewShiftNotes";
    request.getObjectFromArray(document, 0, config);
    AssertJsonObjectHasFields(config,configExpectedFields);

    // data
    QJsonObject data;
    QStringList dataExpectedFields;
    //TODO: MDS - add logic to manage the 'private' arrays
    dataExpectedFields << "BlnCanSplitSegment" << "BlnNavigateNextDisabled" << "BlnNavigatePrevDisabled" << "StrViewPeriod"
        << "ObjPeriodSummary" << "ObjGridOptions" << "_ArrWorkSegments";
    request.getObjectFromArray(document, 1, data);
    AssertJsonObjectHasFields(data,dataExpectedFields);

    QStringList periodSummaryExpectedFields;
    periodSummaryExpectedFields << "StrLeaveHours" << "StrOverallHours" << "StrOvertime1Hours" << "StrOvertime2Hours" << "StrRegularHours";
    AssertJsonChildObjectHasFields(data, "ObjPeriodSummary", periodSummaryExpectedFields);

    QStringList gridOptionsExpectedFields;
    periodSummaryExpectedFields << "BlnDisplayActualPunchTimes" << "BlnDisplayIndividualApproval" << "BlnDisplayTotalDayHours"
        << "BlnShowCostCode" << "BlnShowCostCodeDescription" << "BlnShowUserIdThatGrantedApproval";
    AssertJsonChildObjectHasFields(data, "ObjGridOptions", gridOptionsExpectedFields);

    JsonReader dataReader(data);
    QJsonArray array;
    dataReader.jsonArray("ArrWorkSegments", array);
    QVERIFY2(array.count() > 0, "No work segments");
    QStringList workSegmentExpectedFields;
    workSegmentExpectedFields << "BlnCanApproveEmployee" << "BlnCanSplitSegment" << "BlnHasNote" << "BlnIsApprovedByEmployee" << "BlnIsApprovedByManager" << "BlnIsApprovedByOther" << "BlnIsApprovedMissedIn" << "BlnIsApprovedMissedOut" << "BlnIsConflictingShift" << "BlnIsEdited" << "BlnIsEndOfWeek" << "BlnIsFirstSegmentInShift" << "BlnIsHistory" << "BlnIsLastSegmentInShift" << "BlnIsMiddleSegmentInShift" << "BlnIsMissedIn" << "BlnIsMissedOut" << "IntApprovedExceptionType" << "IntExceptionStatus" << "IntJobCodeRecordId" << "IntMenuExceptionType" << "IntRecordId" << "IntRequireApprovalExceptionType" << "IntToolTipExceptionType" << "StrColor" << "StrCostCodeDescription" << "StrFormattedActualDateTimeIn" << "StrFormattedActualDateTimeOut" << "StrFormattedBreakLength" << "StrFormattedBreakLengthDesc" << "StrFormattedDateTimeIn" << "StrFormattedDateTimeOut" << "StrFormattedDayTotal" << "StrFormattedSegmentTotal" << "StrFormattedShiftTotal" << "StrFormattedTimeSheetMinutes" << "StrFormattedWeekTotal" << "StrJobCodeDescription" << "StrTimeInColor" << "StrTimeOutColor" << "StrTrack1Value" << "StrTrack2Value" << "StrTrack3Value";
    // workSegmentExpectedFields << "BlnCanApproveEmployee" << "BlnCanSplitSegment" << "BlnHasNote" << "BlnIsApprovedByEmployee" << "BlnIsApprovedByManager" << "BlnIsApprovedByOther" << "BlnIsApprovedMissedIn" << "BlnIsApprovedMissedOut" << "BlnIsConflictingShift" << "BlnIsEdited" << "BlnIsEndOfWeek" << "BlnIsFirstSegmentInShift" << "BlnIsHistory" << "BlnIsLastSegmentInShift" << "BlnIsMiddleSegmentInShift" << "BlnIsMissedIn" << "BlnIsMissedOut" << "IntApprovedExceptionType" << "IntExceptionStatus" << "IntJobCodeRecordId" << "IntMenuExceptionType" << "IntRecordId" << "IntRequireApprovalExceptionType" << "IntToolTipExceptionType" << "StrApprovedByEmployeeId" << "StrApprovedByManagerId" << "StrApprovedByOtherId" << "StrColor" << "StrCostCodeDescription" << "StrFormattedActualDateTimeIn" << "StrFormattedActualDateTimeOut" << "StrFormattedBreakLength" << "StrFormattedBreakLengthDesc" << "StrFormattedDateTimeIn" << "StrFormattedDateTimeOut" << "StrFormattedDayTotal" << "StrFormattedRate" << "StrFormattedSegmentTotal" << "StrFormattedShiftTotal" << "StrFormattedTimeSheetMinutes" << "StrFormattedWeekTotal" << "StrJobCodeDescription" << "StrTimeInColor" << "StrTimeOutColor" << "StrTrack1Value" << "StrTrack2Value" << "StrTrack3Value";
    for (int q = 0; q < array.count(); q++)
    {
        QJsonObject workSegmentObject = array.at(q).toObject();
        AssertJsonObjectHasFields(workSegmentObject, workSegmentExpectedFields);
    }
}

void TestRequestLoadHours::performRequest_next()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    RequestLoadHours initialRequest(context);
    QVERIFY(initialRequest.performRequest());
    RequestLoadHours request(context, HourLoadNext);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    //TODO: MDS - add logic to manage the 'private' arrays
    dataExpectedFields << "BlnCanSplitSegment" << "BlnNavigateNextDisabled" << "BlnNavigatePrevDisabled" << "StrViewPeriod"
        << "ObjPeriodSummary" << "ObjGridOptions" << "_ArrWorkSegments";
    request.getObjectFromArray(document, 1, data);
    AssertJsonObjectHasFields(data,dataExpectedFields);

    QStringList periodSummaryExpectedFields;
    periodSummaryExpectedFields << "StrLeaveHours" << "StrOverallHours" << "StrOvertime1Hours" << "StrOvertime2Hours" << "StrRegularHours";
    AssertJsonChildObjectHasFields(data, "ObjPeriodSummary", periodSummaryExpectedFields);

    QStringList gridOptionsExpectedFields;
    periodSummaryExpectedFields << "BlnDisplayActualPunchTimes" << "BlnDisplayIndividualApproval" << "BlnDisplayTotalDayHours"
        << "BlnShowCostCode" << "BlnShowCostCodeDescription" << "BlnShowUserIdThatGrantedApproval";
    AssertJsonChildObjectHasFields(data, "ObjGridOptions", gridOptionsExpectedFields);
}

void TestRequestLoadHours::performRequest_period()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    RequestLoadHours initialRequest(context);
    QVERIFY(initialRequest.performRequest());
    RequestLoadHours request(context, HourLoadPeriod);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    //TODO: MDS - add logic to manage the 'private' arrays
    dataExpectedFields << "BlnCanSplitSegment" << "BlnNavigateNextDisabled" << "BlnNavigatePrevDisabled" << "StrViewPeriod"
        << "ObjPeriodSummary" << "ObjGridOptions" << "_ArrWorkSegments";
    request.getObjectFromArray(document, 1, data);
    AssertJsonObjectHasFields(data,dataExpectedFields);

    QStringList periodSummaryExpectedFields;
    periodSummaryExpectedFields << "StrLeaveHours" << "StrOverallHours" << "StrOvertime1Hours" << "StrOvertime2Hours" << "StrRegularHours";
    AssertJsonChildObjectHasFields(data, "ObjPeriodSummary", periodSummaryExpectedFields);

    QStringList gridOptionsExpectedFields;
    periodSummaryExpectedFields << "BlnDisplayActualPunchTimes" << "BlnDisplayIndividualApproval" << "BlnDisplayTotalDayHours"
        << "BlnShowCostCode" << "BlnShowCostCodeDescription" << "BlnShowUserIdThatGrantedApproval";
    AssertJsonChildObjectHasFields(data, "ObjGridOptions", gridOptionsExpectedFields);
}

void TestRequestLoadHours::performRequest_previous()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    RequestLoadHours initialRequest(context);
    QVERIFY(initialRequest.performRequest());
    RequestLoadHours request(context, HourLoadPrevious);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());
    QJsonObject data = document.object();
    QStringList dataExpectedFields;
    //TODO: MDS - add logic to manage the 'private' arrays
    dataExpectedFields << "BlnCanSplitSegment" << "BlnNavigateNextDisabled" << "BlnNavigatePrevDisabled" << "StrViewPeriod"
        << "ObjPeriodSummary" << "ObjGridOptions" << "_ArrWorkSegments";
    request.getObjectFromArray(document, 1, data);
    AssertJsonObjectHasFields(data,dataExpectedFields);

    QStringList periodSummaryExpectedFields;
    periodSummaryExpectedFields << "StrLeaveHours" << "StrOverallHours" << "StrOvertime1Hours" << "StrOvertime2Hours" << "StrRegularHours";
    AssertJsonChildObjectHasFields(data, "ObjPeriodSummary", periodSummaryExpectedFields);

    QStringList gridOptionsExpectedFields;
    periodSummaryExpectedFields << "BlnDisplayActualPunchTimes" << "BlnDisplayIndividualApproval" << "BlnDisplayTotalDayHours"
        << "BlnShowCostCode" << "BlnShowCostCodeDescription" << "BlnShowUserIdThatGrantedApproval";
    AssertJsonChildObjectHasFields(data, "ObjGridOptions", gridOptionsExpectedFields);
}

QTTESTUTIL_REGISTER_TEST(TestRequestLoadHours);
#include "TestRequestLoadHours.moc"
