#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"
 
#include "Externs.h"
#include "RequestLogOnFromTerminal.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestLogOnFromTerminal: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestLogOnFromTerminal::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    RegisterAndConfigureTerminal(&companyConfig);
    
    OperationContext context(companyConfig);
    context.id = "1";
    context.setCompanyId(RDTG_COMPANYID);
    ConfigureOperationContext(context);
    RequestLogOnFromTerminal request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());
    QJsonArray a = document.array();
    QCOMPARE(a.count(), 2);
}

QTTESTUTIL_REGISTER_TEST(TestRequestLogOnFromTerminal);
#include "TestRequestLogOnFromTerminal.moc"