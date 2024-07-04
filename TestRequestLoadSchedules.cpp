#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestLoadSchedules.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestLoadSchedules: public QObject
{
    Q_OBJECT
private slots:
    void performRequest_current();
    void performRequest_next();
    void performRequest_period();
    void performRequest_previous();
};

void TestRequestLoadSchedules::performRequest_current()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    QString period = "";
    RequestLoadSchedules request(context, HourLoadCurrent, &period);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // config
    QStringList expectedConfigFieldNames;
    expectedConfigFieldNames << "BlnAllowDropReason" << "BlnCanDeleteDrop" << "BlnCanDeleteSwap" << "BlnCanMakeTimeOffRequest" << "BlnUseSegmentForRequestTemplate" << "IntAvailableShiftTypeDrop" << "IntAvailableShiftTypeNone" << "IntAvailableShiftTypeSwap" << "ObjTextInputDropReason";
    QJsonObject config;
    QVERIFY(request.getObjectFromArray(document, 0, config));
    AssertJsonObjectHasFields(config,expectedConfigFieldNames);
    AssertJsonChildObjectHasField(config, "ObjTextInputDropReason", "BlnIsRequired");

    // data
    QStringList expectedDataFieldNames;
    expectedDataFieldNames << "BlnCanMoveToNextPeriod" << "BlnCanMoveToPrevPeriod" << "BlnShouldDisplayWeekends" << "DatPeriodMaxDate" << "DatPeriodStartDate" << "ArrScheduleWeeks";
    QJsonObject data;
    QVERIFY(request.getObjectFromArray(document, 1, data));
    AssertJsonObjectHasFields(data,expectedDataFieldNames);

    // weeks
    JsonReader dataReader(data);
    QJsonArray weekArray;
    dataReader.jsonArray("ArrScheduleWeeks", weekArray);
    QVERIFY2(weekArray.count() > 0, "No schedule weeks");
    QStringList scheduleWeekExpectedFields;
    scheduleWeekExpectedFields << "StrFormattedWeekTitle" << "StrFormattedWeekSubTitle" << "ArrScheduleDays";
    QStringList scheduleDayExpectedFields;
    scheduleDayExpectedFields << "BlnCanAdd" << "BlnCanPasteSegment" << "BlnIsScheduleOverridden" << "BlnIsWeekend" << "DatDate" << "StrFormattedDate" << "StrFormattedTotal" << "ArrScheduleSegments";
    QStringList segmentExpectedFields;
    segmentExpectedFields << "BlnCanCopySegment" << "BlnCanDeleteSegment" << "BlnCanEditSegment" << "BlnIsFirstSegmentInShift" << "BlnIsLastSegmentInShift" << "BlnIsLeaveCode" << "BlnIsMiddleSegmentInShift" << "IntEmployeeRecordId" << "IntRecordId" << "StrBreakDescription" << "StrFormattedHours" << "StrFormattedTimeIn" << "StrFormattedTimeOut" << "StrJobCodeDescription" << "BlnIsDroppable" << "BlnIsSwappable" << "StrPendingAvailableShiftDescription" << "IntPendingAvailableShiftType";

    for (int q = 0; q < weekArray.count(); q++)
    {
        QJsonObject scheduleWeekObject = weekArray.at(q).toObject();
        AssertJsonObjectHasFields(scheduleWeekObject, scheduleWeekExpectedFields);

        // days
        JsonReader weekReader(scheduleWeekObject);
        QJsonArray dayArray;
        weekReader.jsonArray("ArrScheduleDays", dayArray);
        QVERIFY2(dayArray.count() > 0, "No schedule days");
        for (int dayIterator = 0; dayIterator < dayArray.count(); dayIterator++)
        {
            QJsonObject scheduleDayObject = dayArray.at(dayIterator).toObject();
            AssertJsonObjectHasFields(scheduleDayObject, scheduleDayExpectedFields);

            // segments
            JsonReader dayReader(scheduleWeekObject);
            QJsonArray segmentArray;
            dayReader.jsonArray("ArrScheduleSegments", segmentArray);
            for (int segmentIterator = 0; segmentIterator < segmentArray.count(); segmentIterator++)
            {
                QJsonObject segmentObject = dayArray.at(segmentIterator).toObject();
                AssertJsonObjectHasFields(segmentObject, segmentExpectedFields);
            }
        }
    }    
}

void TestRequestLoadSchedules::performRequest_next()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    QString period = "";
    RequestLoadSchedules initialRequest(context,HourLoadCurrent, &period);
    QVERIFY(initialRequest.performRequest());

    RequestLoadSchedules request(context, HourLoadNext, &period);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    // data
    QStringList expectedDataFieldNames;
    expectedDataFieldNames << "BlnCanMoveToNextPeriod" << "BlnCanMoveToPrevPeriod" << "BlnShouldDisplayWeekends" << "DatPeriodMaxDate" << "DatPeriodStartDate" << "ArrScheduleWeeks";
    AssertResponseHasFields(request.response,expectedDataFieldNames);
}

void TestRequestLoadSchedules::performRequest_period()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    QString period = "";
    RequestLoadSchedules initialRequest(context,HourLoadCurrent, &period);
    QVERIFY(initialRequest.performRequest());

    RequestLoadSchedules request(context, HourLoadPeriod, &period);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    // data
    QStringList expectedDataFieldNames;
    expectedDataFieldNames << "BlnCanMoveToNextPeriod" << "BlnCanMoveToPrevPeriod" << "BlnShouldDisplayWeekends" << "DatPeriodMaxDate" << "DatPeriodStartDate" << "ArrScheduleWeeks";
    AssertResponseHasFields(request.response,expectedDataFieldNames);
}


void TestRequestLoadSchedules::performRequest_previous()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    QString period = "";
    RequestLoadSchedules initialRequest(context,HourLoadCurrent, &period);
    QVERIFY(initialRequest.performRequest());

    RequestLoadSchedules request(context, HourLoadPrevious, &period);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    // data
    QStringList expectedDataFieldNames;
    expectedDataFieldNames << "BlnCanMoveToNextPeriod" << "BlnCanMoveToPrevPeriod" << "BlnShouldDisplayWeekends" << "DatPeriodMaxDate" << "DatPeriodStartDate" << "ArrScheduleWeeks";
    AssertResponseHasFields(request.response,expectedDataFieldNames);
}

QTTESTUTIL_REGISTER_TEST(TestRequestLoadSchedules);
#include "TestRequestLoadSchedules.moc"
