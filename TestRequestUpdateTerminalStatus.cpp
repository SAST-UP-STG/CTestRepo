#include <QtTest/QtTest>
#include <QTextStream>
#include "QtTestUtil/QtTestUtil.h"

#include "Externs.h"
#include "RequestUpdateTerminalStatus.h"
#include "TestBase.h"
#include "UserContext.h"

class TestRequestUpdateTerminalStatus: public QObject
{
    Q_OBJECT
private slots:
    void performRequest();
};

void TestRequestUpdateTerminalStatus::performRequest()
{
    // set-up
    Initialize();
    UserContext context(RDTG_COMPANYID, "");
    RegisterTerminal(context);
    RequestUpdateTerminalStatus request(context);

    // pre-conditions
    QVERIFY(context.sessionId.length() != 0);
    QCOMPARE(isDBorLater(7, 0, 60, 0), true);

    // exercise
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);

    QStringList expectedFieldNames;
    expectedFieldNames << "sh-reb" << "up-suc";
    AssertResponseHasFields(request.response, expectedFieldNames);
}

QTTESTUTIL_REGISTER_TEST(TestRequestUpdateTerminalStatus);
#include "TestRequestUpdateTerminalStatus.moc"