#include "UserStore.h"
#include "UserContext.h"
#include "EmployeeInfoItem.h"

#include "RequestRegisterTerminal.h"
#include "RequestUnregisterTerminal.h"
#include "RequestUserLogOn.h"
#include "RequestUserLogOff.h"
#include "RequestGetTerminalSpecifications.h"
#include "RequestSaveBiometricTemplate.h"
#include "RequestGetEmployeeBiometricTemplates.h"
#include "RequestGetUserBiometricTemplates.h"
#include "RequestGetPotentialBiometricUsers.h"
#include "RequestLookupEmployee.h"
#include "RequestUserLogOnFromTerminal.h"
#include "RequestConfirmUserVerification.h"
#include "RequestPing.h"
#include "RequestGetUsersFromTerminal.h"
#include "RequestUpdateTerminalStatus.h"
#include "RequestGetEmployeeValidationFile.h"
#include "RequestGetCostCodeValidationFile.h"
#include "RequestSubmitOfflinePunches.h"
#include "RequestGetTimeStampUtc.h"
#include "RequestSelectEnrollBadgeEmployee.h"
#include "RequestEnrollEmployeeBadge.h"


UserStore::UserStore(UserContext& context) : context(context)
{
}

UserStore::~UserStore()
{
}

bool UserStore::userAutoLogOn()
{
   RequestUserLogOnFromTerminal login(context, "ADMIN", "");

   if (login.performRequest())
   {
      context.setVerificationSpec(NULL); // Ignore the verification spec
      qDebug() << "AUTO LOGON STEP 1 OK - CONFIRMING";

      return confirmUserVerification();
   }
   else{ qDebug() << "AUTO LOGON STEP 1 FAILED"; }

   qDebug() << context.exception.strMessage;

   return false;
}

bool UserStore::userLogOnFromTerminal(QString userId, QString password)
{
   RequestUserLogOnFromTerminal login(context, userId, password);

   return login.performRequest();
}

bool UserStore::userLogOnX(QString userId, QString password)
{
   RequestUserLogOn login(context, userId, password);

   return login.performRequest();
}


bool UserStore::userLogOff()
{
   RequestUserLogOff logOff(context);

   return logOff.performRequest();
}

bool UserStore::confirmUserVerification()
{
   RequestConfirmUserVerification confirm(context);

   return confirm.performRequest();
}

bool UserStore::registerTerminal(QString name)
{
   RequestRegisterTerminal reg(context, name);

   return reg.performRequest();
}

bool UserStore::getTerminalSpecification(CompanyConfig *config, QList<CompanyConfig*> *configs)
{
   RequestGetTerminalSpecifications getSpec(context, config, configs);

   if (getSpec.performRequest())
   {
      if (!config && context.companyConfig()) { context.setTerminalId(context.companyConfig()->terminalId); }
      return true;
   }
   return false;
}

bool UserStore::getTerminalSpecifications(QList<CompanyConfig*>& companies)
{
   RequestGetTerminalSpecifications getSpec(context, NULL, &companies);

   return getSpec.performRequest();
}

bool UserStore::unregisterTerminal()
{
   RequestUnregisterTerminal unr(context);

   return unr.performRequest();
}

bool UserStore::saveEmployeeBiometricTemplate(int module, qint64 employeeId, FPTemplate& data)
{
   RequestSaveBiometricTemplate save(context, context.terminalId(), module, employeeId, data);

   return save.performRequest();
}

bool UserStore::saveUserBiometricTemplate(int module, QString userId, FPTemplate& data)
{
   RequestSaveBiometricTemplate save(context, context.terminalId(), module, userId, data);

   return save.performRequest();
}

bool UserStore::getEmployeeBiometricTemplates(int module, qint64 employeeId, FPTemplates& templates)
{
   RequestGetEmployeeBiometricTemplates getTemplates(context, module, employeeId, context.terminalId(), templates);

   return getTemplates.performRequest();
}

bool UserStore::getUserBiometricTemplates(int module, QString userId, FPTemplates& templates)
{
   RequestGetUserBiometricTemplates getTemplates(context, module, userId, context.terminalId(), templates);

   return getTemplates.performRequest();
}

bool UserStore::getPotentialBiometricUsers(int module, QList<User*>& users, int action)
{
   RequestGetPotentialBiometricUsers get(context, module, context.terminalId(), users, action);

   return get.performRequest();
}

bool UserStore::lookupEmployee(QString badgeNumber, EmployeeInfoItem& employee)
{
   RequestLookupEmployee lookup(context, context.terminalId(), badgeNumber, employee);

   return lookup.performRequest();
}

bool UserStore::ping(int *pingStatus)
{
   RequestPing ping(context);

   bool result = ping.performRequest();

   if (pingStatus) { *pingStatus = ping.httpStatusCode(); }
   return result;
}

bool UserStore::getUsersFromTerminal(QList<User*>& users)
{
   RequestGetUsersFromTerminal getUsers(context, users);

   return getUsers.performRequest();
}

bool UserStore::updateTerminalStatus()
{
   RequestUpdateTerminalStatus status(context);

   return status.performRequest();
}

bool UserStore::getEmployeeValidationFile(QList<EmployeeInfoItem*>& employees)
{
   RequestGetEmployeeValidationFile get(context, employees);

   return get.performRequest();
}

bool UserStore::getCostCodeValidationFile(QList<CostCodeItem*>& codes)
{
   RequestGetCostCodeValidationFile get(context, codes);

   return get.performRequest();
}

bool UserStore::submitOfflinePunches(QList<OfflineRecord*>& punches)
{
   RequestSubmitOfflinePunches submit(context, punches);

   return submit.performRequest();
}

bool UserStore::getUTCTime(QDateTime& utcTime)
{
   RequestGetTimeStampUtc request(context, utcTime);

   return request.performRequest();
}

bool UserStore::selectEnrollBadgeEmployee(EmployeeInfoItem& info)
{
   RequestSelectEnrollBadgeEmployee sel(context, info);

   return sel.performRequest();
}

bool UserStore::enrollEmployeeBadge(QString badge)
{
   RequestEnrollEmployeeBadge enroll(context, badge);

   return enroll.performRequest();
}
