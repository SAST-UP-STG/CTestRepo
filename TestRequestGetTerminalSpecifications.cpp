#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestGetTerminalSpecifications.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestGetTerminalSpecifications: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

// TODO: MDS - This test needs to be made more robust as it is the centerpiece for RDTg configuration
void TestRequestGetTerminalSpecifications::performRequest()
{
    // set-up
    UserContext context(RDTG_COMPANYID, "");
    RegisterTerminal(context);
    CompanyConfig companyConfig;
    RequestGetTerminalSpecifications request(context, &companyConfig);

    // pre-conditions
    QVERIFY(context.sessionId.length() != 0);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    // sanitize response
    QString resp = QString::fromUtf8(request.response.response());
    resp.replace("\\\"", "\"");
    resp.replace("\\\\", "\\");
    if (resp.length() > 2)
    {
        resp.remove(0, 1);
        resp.remove(resp.length() - 1, 1);
    }

    QJsonDocument document = QJsonDocument::fromJson(resp.toUtf8());
    QJsonObject main = document.object();
    
    QStringList expectedFieldNames;
    expectedFieldNames << "TerminalSpecifications" << "FormattedServerTimestampUtc";
    AssertJsonObjectHasFields(main, expectedFieldNames);
    QJsonArray specs = main["TerminalSpecifications"].toArray();
    
    QVERIFY2(specs.count() > 0, "No terminal specifications retrieved");

    for (int q = 0; q < specs.count(); q++)
    {
        QJsonObject specObj = specs.at(q).toObject();
        QStringList specificationExpectedFieldNames;
        specificationExpectedFieldNames << "CompanyId" << "Inactive" << "CompanyNamespace" << "TerminalId" << "OperationSuccessfulNumberOfBeeps" << "OperationFailedNumberOfBeeps"
            << "OperationSuccessfulBeepTone" << "OperationFailedBeepTone" << "WorkflowShowConfirmationOnManualEntry" << "WorkflowDisplaySuccessMessage"
            << "WorkflowShowConfirmationOnNonManualEntry" << "WorkflowAskForCostCodeOnJobChange" << "WorkflowAskForJobCodeOnCostChange"
            << "WorkflowForceBadgeUsageForOperations" << "AllowQuickPunchAction" << "IdleReleaseSeconds"
            << "CostCodeSelectionOption" << "AllowBreakAction" << "AllowClockInAction" << "AllowClockOutAction" << "AllowCostCodeAction"
            << "AllowJobCodeAction" << "AllowQuickPunchAction" << "AllowTimeOffRequest" << "AllowMessageViewingFromViewMenu"
            << "AllowViewAccruals" << "AllowViewHours" << "AllowViewSchedules" << "AllowChangePin" << "AllowViewLastPunch"
            << "AllowSetBlankPin" << "AllowViewOpens" << "AllowViewDrops" << "AllowViewSwaps" << "AllowTimeOffRequestRemoval"
            << "AllowTimeOffRequestUsingTemplatesOnly" << "DisplayDateFormat" << "DisplayTimeFormat" << "DisplayEmployeeFieldName"
            << "DisplayJobCodeFieldName" << "DisplayCostCodeFieldName" << "DisplayShowEmployeeId" << "TimeSheetEntryType";
        AssertJsonObjectHasFields(specObj, specificationExpectedFieldNames);
    }
}

QTTESTUTIL_REGISTER_TEST(TestRequestGetTerminalSpecifications);
#include "TestRequestGetTerminalSpecifications.moc"
