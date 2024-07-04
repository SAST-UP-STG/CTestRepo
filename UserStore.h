#ifndef USERSTORE_H
#define USERSTORE_H

#include <QtCore>

#include "IStore.h"

class UserContext;
class CompanyConfig;
class EmployeeInfoItem;

class UserStore: public IStore
{
 public:
  UserStore(UserContext& context);
  virtual ~UserStore();
 
  bool ping(int *pingStatus = NULL);
  bool userAutoLogOn();
  bool userLogOnX(QString userId, QString password);
  bool userLogOnFromTerminal(QString userId, QString password);
  bool userLogOff();
  bool confirmUserVerification();
  bool registerTerminal(QString name);
  bool unregisterTerminal();
  bool getTerminalSpecification(CompanyConfig *config = NULL, QList<CompanyConfig*> *configs = NULL);
  bool getTerminalSpecifications(QList<CompanyConfig*>& companies);
  bool saveEmployeeBiometricTemplate(int module, qint64 employeeId, FPTemplate& data);
  bool saveUserBiometricTemplate(int module, QString userId, FPTemplate& data);
  bool getEmployeeBiometricTemplates(int module, qint64 employeeId, FPTemplates& templates);
  bool getUserBiometricTemplates(int module, QString userId, FPTemplates& templates);
  bool getPotentialBiometricUsers(int module, QList<User*>& users, int action);
  bool lookupEmployee(QString badgeNumber, EmployeeInfoItem& employee);
  bool getUsersFromTerminal(QList<User*>& users);
  bool updateTerminalStatus();
  bool getEmployeeValidationFile(QList<EmployeeInfoItem*>& employees);
  bool getCostCodeValidationFile(QList<CostCodeItem*>& codes);
  bool submitOfflinePunches(QList<OfflineRecord*>& punches);
  bool getUTCTime(QDateTime& utcTime);
  bool selectEnrollBadgeEmployee(EmployeeInfoItem& info);
  bool enrollEmployeeBadge(QString badge);

 private:
  UserContext& context;
};

#endif
