#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"
 
#include "Externs.h"
#include "RequestGetInfo.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestGetInfo: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestGetInfo::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    RegisterAndConfigureTerminal(&companyConfig);
    
    OperationContext context(companyConfig);
    ConfigureOperationContext(context);
    RequestGetInfo request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());
    QJsonObject obj;
    QVERIFY2(request.getObjectFromArray(document, 0, obj), "Missing first json argument");
    AssertJsonObjectHasField(obj, "StrLogOnToDashboard");

    QVERIFY2(request.getObjectFromArray(document, 2, obj), "Missing third json argument");
    AssertJsonObjectHasField(obj, "ArrCompanies");

    QJsonArray array;
    JsonReader rdr(obj);
    QVERIFY2(rdr.jsonArray(obj, "ArrCompanies", array), "Json array deserialization failed");
    QStringList expectedFieldNames;
    expectedFieldNames << "_IntCompanyId" << "StrPasswordEntryTitle" << "ObjCustomFieldControlModelLogOnId" << "ObjCustomFieldControlModelLogOnPassword";

    for (int q = 0; q < array.count(); q++)
    {
        QJsonObject obj2 = array.at(q).toObject();
        JsonReader rdr2(obj2);

        AssertJsonObjectHasFields(obj2, expectedFieldNames);

        QJsonObject obj3 = rdr2.getField("ObjCustomFieldControlModelLogOnId").toObject();
        AssertJsonObjectHasField(obj3, "StrText");

        obj3 = rdr2.getField("ObjCustomFieldControlModelLogOnPassword").toObject();
        AssertJsonObjectHasField(obj3, "StrText");
    }
}

QTTESTUTIL_REGISTER_TEST(TestRequestGetInfo);
#include "TestRequestGetInfo.moc"