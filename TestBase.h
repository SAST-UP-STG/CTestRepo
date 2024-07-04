#ifndef TESTBASE_H
#define TESTBASE_H

#include "Externs.h"
#include "JsonReader.h"
#include "OperationContext.h"
#include "RequestConfirmEmployee.h"
#include "RequestGetTerminalSpecifications.h"
#include "RequestLogOnFromTerminal.h"
#include "RequestRegisterTerminal.h"
#include "RequestStartOperation.h"
#include "RequestUserLogOn.h"
#include "UserContext.h"

// extern
extern char *BaseUrl;

// constants
const int RDTG_COMPANYID = 2700;

// free functions
void AssertJsonChildObjectHasField(QJsonObject obj, QString childObjectName, QString fieldName);
void AssertJsonChildObjectHasFields(QJsonObject obj, QString childObjectName, QStringList fieldNames);
void AssertJsonObjectHasField(QJsonObject obj, QString fieldName);
void AssertJsonObjectHasFields(QJsonObject obj, QStringList fieldNames);
void AssertResponseHasField(CurlResponse &response, QString fieldName);
void AssertResponseHasFields(CurlResponse &response, QStringList fieldNames);
void ConfigureOperationContext(OperationContext &context);
void ConfigureOperationContext(OperationContext &context);
void EmployeeLogOn(OperationContext &context);
void EmployeeLogOn(OperationContext &context, int id);
QString GetBaseUrl();
void Initialize();
void UserLogOn(UserContext& context);
void RegisterTerminal();
void RegisterTerminal(UserContext& context);
void RegisterAndConfigureTerminal(CompanyConfig* companyConfigPtr);
void RegisterAndConfigureTerminal(UserContext &context, CompanyConfig* companyConfigPtr);
void SetupForEmployee(CompanyConfig &companyConfig);
void SetupForEmployee(OperationContext &context, CompanyConfig &companyConfig);
void SetupForEmployee(OperationContext &context, CompanyConfig &companyConfig, int id);
void StartClockOperationAndConfirm(OperationContext &context, CompanyConfig &companyConfig, int id, ClockAction action);
void UserLogOn(UserContext& context);

#endif
