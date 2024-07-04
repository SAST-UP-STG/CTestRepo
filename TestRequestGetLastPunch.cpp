#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestGetLastPunch.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestGetLastPunch: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestGetLastPunch::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    RequestGetLastPunch request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // config
    QStringList expectedConfigFieldNames;
    expectedConfigFieldNames << "BlnShowClockStatus" << "BlnShowDateTimeIn" << "BlnShowDateTimeOut" << "BlnShowName" << "StrClockedInAt" << "StrClockedOutAt" << "StrEmployeeName" << "StrLastPunch" << "StrTitle";
    //expectedConfigFieldNames << "BlnShowClockStatus" << "BlnShowCostCode" << "BlnShowDateTimeIn" << "BlnShowDateTimeOut" << "BlnShowName" << "BlnShowTrack1" << "BlnShowTrack2" << "BlnShowTrack3" << "StrClockedInAt" << "StrClockedOutAt" << "StrEmployeeName" << "StrLastPunch" << "StrTitle";
    QJsonObject config;
    QVERIFY(request.getObjectFromArray(document, 0, config));
    AssertJsonObjectHasFields(config,expectedConfigFieldNames);

    // data
    QStringList expectedDataFieldNames;
    expectedDataFieldNames << "StrCostCodeDescription" << "StrFormattedActualDateTimeIn" << "StrFormattedActualDateTimeOut" << "StrFormattedDateTimeIn" << "StrFormattedDateTimeOut" << "StrJobCodeDescription" << "StrCostCodeDescription";
    //expectedDataFieldNames << "StrCostCodeDescription" << "StrFormattedActualDateTimeIn" << "StrFormattedActualDateTimeOut" << "StrFormattedDateTimeIn" << "StrFormattedDateTimeOut" << "StrJobCodeDescription" << "StrCostCodeDescription";
    QJsonObject data;
    QVERIFY(request.getObjectFromArray(document, 1, data));
    AssertJsonObjectHasFields(data,expectedDataFieldNames);    
}

QTTESTUTIL_REGISTER_TEST(TestRequestGetLastPunch);
#include "TestRequestGetLastPunch.moc"
