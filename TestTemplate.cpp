#include <QtTest/QtTest>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "{TEMPLATE}.h"
#include "TestBase.h"
#include "UserContext.h"

class Test{TEMPLATE}: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void Test{TEMPLATE}::performRequest()
{
    // set-up
    CompanyConfig companyConfig;
    OperationContext context(companyConfig);
    SetupForEmployee(context, companyConfig);
    {TEMPLATE} request(context);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QJsonDocument document = QJsonDocument::fromJson(request.response.response());

    // config

    // data
}

QTTESTUTIL_REGISTER_TEST(Test{TEMPLATE});
#include "Test{TEMPLATE}.moc"
