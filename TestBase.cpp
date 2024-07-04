#include <QtTest/QtTest>
#include "TestBase.h"

char *BaseUrl;

void AssertJsonChildObjectHasField(QJsonObject obj, QString childObjectName, QString fieldName)
{
    JsonReader mainReader(obj);
    QString childObjectMessage = (childObjectName + QString(" was not found"));
    QVERIFY2(mainReader.hasField(childObjectName), childObjectMessage.toStdString().c_str());

    QJsonValue childObjectValue = mainReader.getField(childObjectName);
    QJsonObject childObject = childObjectValue.toObject();
    AssertJsonObjectHasField(childObject, fieldName);
}

void AssertJsonChildObjectHasFields(QJsonObject obj, QString childObjectName, QStringList fieldNames)
{
    JsonReader mainReader(obj);
    QString childObjectMessage = (childObjectName + QString(" was not found"));
    QVERIFY2(mainReader.hasField(childObjectName), childObjectMessage.toStdString().c_str());

    QJsonValue childObjectValue = mainReader.getField(childObjectName);
    QJsonObject childObject = childObjectValue.toObject();
    AssertJsonObjectHasFields(childObject, fieldNames);
}

void AssertJsonObjectHasField(QJsonObject obj, QString fieldName)
{
    JsonReader rdr(obj);
    QString message = (fieldName + QString(" was not found"));
    QVERIFY2(rdr.hasField(fieldName), message.toStdString().c_str());
}

void AssertJsonObjectHasFields(QJsonObject obj, QStringList fieldNames)
{
    JsonReader rdr(obj);

    for (int i = 0; i < fieldNames.size(); i++)
    {
        QString fieldName = fieldNames.at(i);
        QString message = (fieldName + QString(" was not found"));
        QVERIFY2(rdr.hasField(fieldName), message.toStdString().c_str());
    }
}

void AssertResponseHasField(CurlResponse &response, QString fieldName)
{
    QJsonDocument document = QJsonDocument::fromJson(response.response());
    QJsonObject obj = document.object();
    AssertJsonObjectHasField(obj, fieldName);
}

void AssertResponseHasFields(CurlResponse &response, QStringList fieldNames)
{
    QJsonDocument document = QJsonDocument::fromJson(response.response());
    QJsonObject obj = document.object();
    AssertJsonObjectHasFields(obj, fieldNames);
}

void ConfigureTerminal(UserContext &context, CompanyConfig* companyConfigPtr)
{
    RequestGetTerminalSpecifications request(context, companyConfigPtr);
    bool result = request.performRequest();

    // configured successfully
    QCOMPARE(result, true); 
}

void ConfigureOperationContext(OperationContext &context)
{
    context.companyNamespace = "PROD";
    strcpy(boardConfig.deviceId, "3a5197c3-2312-4943-89f0-e34782816098");
    context.baseUrl = GetBaseUrl();
}

void Initialize()
{
    databaseVersion[0] = 7;
    databaseVersion[1] = 0;
    databaseVersion[2] = 63;
    databaseVersion[3] = 0;

    UserContext CommonUserContext(RDTG_COMPANYID, "");
}

void EmployeeLogOn(OperationContext &context)
{
    EmployeeLogOn(context, 1);
}

void EmployeeLogOn(OperationContext &context, int id)
{
    context.id = QString::number(id);;
    context.setCompanyId(RDTG_COMPANYID);
    ConfigureOperationContext(context);
    RequestLogOnFromTerminal request(context);

    // log on
    bool result = request.performRequest();

    // post-conditions
    QCOMPARE(result, true);
}

QString GetBaseUrl()
{
    if (BaseUrl == NULL)
    {
        return "http://192.168.6.32";
    }
    
    return QString(BaseUrl);
}

void RegisterTerminal()
{
    UserContext context(RDTG_COMPANYID, "");
    RegisterTerminal(context);
}

void RegisterTerminal(UserContext& context)
{
    UserLogOn(context);
    RequestRegisterTerminal request(context, "Test");

    bool result = request.performRequest();

    // registered successfully
    QCOMPARE(result, true); 
}

void RegisterAndConfigureTerminal(CompanyConfig* companyConfigPtr)
{
    UserContext context(RDTG_COMPANYID, "");
    RegisterTerminal(context);
    ConfigureTerminal(context, companyConfigPtr);
}

void RegisterAndConfigureTerminal(UserContext &context, CompanyConfig* companyConfigPtr)
{
    RegisterTerminal(context);
    ConfigureTerminal(context, companyConfigPtr);
}

void SetupForEmployee(OperationContext &context, CompanyConfig &companyConfig)
{
    SetupForEmployee(context, companyConfig, 1);
}

void SetupForEmployee(OperationContext &context, CompanyConfig &companyConfig, int id)
{
    RegisterAndConfigureTerminal(&companyConfig);
    EmployeeLogOn(context,id);
}

void StartClockOperationAndConfirm(OperationContext &context, CompanyConfig &companyConfig, int id, ClockAction action)
{
    SetupForEmployee(context, companyConfig, id);
    RequestStartOperation clockOperationRequest(context, action, 0, QString("no"));
    QVERIFY(clockOperationRequest.performRequest());
    RequestConfirmEmployee confirmEmployeeRequest(context);
    QVERIFY(confirmEmployeeRequest.performRequest());
}

void UserLogOn(UserContext& context)
{
    context.companyNamespace = "PROD";
    strcpy(boardConfig.deviceId, "3a5197c3-2312-4943-89f0-e34782816098");
    context.baseUrl = GetBaseUrl();
    QString userId = "ADMIN";
    QString password = "";
    RequestUserLogOn request(context, userId, password);
    bool result = request.performRequest();

    // could logon
    QCOMPARE(result, true);
}
