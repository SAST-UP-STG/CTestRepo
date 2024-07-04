#ifndef OPERATIONCONTEXT_H
#define OPERATIONCONTEXT_H

#include <QtCore>

#include "CurlRequest.h"
#include "ContextBase.h"
#include "BreakInfo.h"
#include "CompanyConfig.h"
#include "IStore.h"
#include "LastPunchInfo.h"
#include "OfflineRecord.h"

#define CLEAR(x) qDeleteAll(x);x.clear();

#include "EmployeeInfoItem.h"
#include "EmployeeHourItem.h"
#include "EmployeeAccrualItem.h"
#include "EmployeeMessageItem.h"
#include "EmployeeScheduleItem.h"
#include "EmployeePinItem.h"
#include "CostCodeItem.h"
#include "MissedPunchItem.h"
#include "TrackedFieldItem.h"
#include "CoveredEmployeeItem.h"
#include "RequestItem.h"
#include "JobCodeItem.h"
#include "TimesheetItem.h"
#include "OverrideInfo.h"
#include "User.h"
#include "Workflow.h"
#include "VerificationSpec.h"
#include "DatePeriod.h"
#include "CostCodeOptionInfo.h"
#include "ClockOperationDefines.h"

class BreakOnClockOutInfo;

class MenuCommand
{
 public:
  MenuCommand(QString command, QString menuText): command(command), menuText(menuText) {}

  QString command, menuText;
};

class OperationContext: public ContextBase
{
 public:
  OperationContext(CompanyConfig& companyConfig);
  virtual ~OperationContext();

  QMap<QString,QString>         language;

  Workflow                      workflow;
  bool                          shouldShowNote;
  bool                          shouldRequireNote;
  int                           noteMaxLength;

  QString                       clockOutQuestion;
  QString                       clockOutQuestionAcknowledgement;

  bool                          loadStringsFromObject(QJsonValue obj);
  bool                          loadStringsFromObject(QJsonObject& obj);
  bool                          loadStringFromObject(QString storeName, QJsonObject& obj, QString subObject, const char *field);
  void                          addLanguageKey(QString key, QString value);

  inline void                   setQPClockedIn(bool isIn) { _qpClockedIn = isIn; }
  inline bool                   isQPClockedIn() { return _qpClockedIn; }

  inline void                   setQuickPunchId(qint64 id) { _quickPunchId = id; }
  inline qint64                 quickPunchId() { return _quickPunchId; }

  inline void                   setStore(IStore *store) { this->_store = store; }
  inline IStore&                database() { return *_store; }
  virtual int                   terminalId() { return companyConfig().terminalId; }
  
  QString                       translateAction(ClockAction action);
  virtual bool                  allowOperation(ClockAction operation);
  virtual QString               workflowTitle() { return workflow.workflowTitle; }

  QString                       formatDate(QDateTime date) { return formatDate(date.date()); }
  QString                       formatTime(QDateTime time,bool includeSeconds = false) { return OperationContext::formatTime(companyConfig().timeFormat, time.time(), includeSeconds); }
  QString                       formatDate(const QDate date);
  QString                       formatTime(const QTime time, bool includeSeconds = false) { return OperationContext::formatTime(companyConfig().timeFormat, time, includeSeconds); }
  static QString                formatTime(int timeFormat, const QTime time, bool includeSeconds = false);

  void                          reset();
  int                           saveVerificationSpecTemplates();
  QString                       getPrompt(QString key, QString defaultText);                          

  bool                          isBiometricsEnabled();
  bool                          captureImage();

  QString                       actionDescription(ClockAction action) { Q_UNUSED(action);  return "FIX"; } //v7
  QString                       processText(QString text);

  inline void                   setEntryType(ClockEntryType entryType) { _entryType = entryType; }
  inline ClockEntryType         entryType() { return _entryType; }

  QDateTime                     timeNow(bool includeSeconds = false);

  bool                          isQuickPunch;


  void loadModules() { }
  void setBiometricVerification(bool bioVerified) { _bioVerified = bioVerified; }

  inline OfflineRecord&         offlineRecord() { return _offlineRecord; }

  inline void                   setDatePeriods(DatePeriods *periods) { delete _datePeriods; _datePeriods = periods; }
  inline DatePeriods *          datePeriods() { return _datePeriods; }

  inline void                   setVerificationSpec(VerificationSpec * spec) { delete _verificationSpec; _verificationSpec = spec; }
  VerificationSpec *            verificationSpec() { return _verificationSpec; }

  inline void setPinVerified(bool verified) { Q_UNUSED(verified); }
  inline CompanyConfig&         companyConfig() { return this->_companyConfig; }
  
  inline EmployeeInfoItem&        employeeInfo() { return this->_employeeInfo; }

  inline void                   setLastPunch(LastPunchInfo *lpInfo) { delete this->_lastPunch; _lastPunch = lpInfo; }
  inline LastPunchInfo *        lastPunch() { return _lastPunch; }

  inline void                   setCostCodeOptionInfo(CostCodeOptionInfo *cInfo) { delete this->_costOptionInfo; _costOptionInfo = cInfo; }
  inline CostCodeOptionInfo *   costCodeOptionInfo() { return _costOptionInfo; }

  void                   setBreakOnClockOut(BreakOnClockOutInfo *bInfo);
  BreakOnClockOutInfo *  breakOnClockOutInfo();

  inline void                   setHours(EmployeeHours *hourInfo) { delete this->_hours; _hours = hourInfo; }
  inline EmployeeHours *        hours() { return _hours; }

  inline void                   setSchedules(EmployeeSchedules *scdInfo) { delete this->_schedules; _schedules = scdInfo; }
  inline EmployeeSchedules *    schedules() { return _schedules; }

  inline void                   setCostCodes(CostCodeList *costList) { delete this->_costCodeList; this->_costCodeList = costList; }
  inline CostCodeList *         costCodes() { return _costCodeList; }

  inline void                   setChangePinInfo(ChangePinInfo *info) { delete this->_changePinInfo; _changePinInfo = info; }
  inline ChangePinInfo *        changePinInfo() { return _changePinInfo; }

  inline void                   setAccruals(EmployeeAccruals *accrualInfo) { delete this->_accruals; _accruals = accrualInfo; }
  inline EmployeeAccruals *     accruals() { return _accruals; }

  inline void                   setMessages(EmployeeMessages *messageInfo) { delete this->_messages; _messages = messageInfo; }
  inline EmployeeMessages *     messages() { return _messages; }

  inline void                   setTrackedInfo(TrackedInfo *info) { delete this->_trackedInfo; _trackedInfo = info; }
  inline TrackedInfo *          trackedInfo() { return _trackedInfo; }

  inline void                   setConfirmMissedInfo(ConfirmMissedInfo* info) { delete this->_confirmMissed; this->_confirmMissed = info; }
  inline ConfirmMissedInfo *    confirmMissedInfo() { return _confirmMissed; }

  inline void                   setConfirmMissedSummaryInfo(ConfirmMissedSummaryInfo* info) { delete this->_confirmMissedSummary; this->_confirmMissedSummary = info; }
  inline ConfirmMissedSummaryInfo * confirmMissedSummaryInfo() { return _confirmMissedSummary; }

  inline void                   setMissedTimeInfo(GatherMissedTimeInfo *info) { delete _missedTimeInfo; _missedTimeInfo = info; }
  inline GatherMissedTimeInfo * missedTimeInfo() { return _missedTimeInfo; }

  inline void                   setViewRequestsInfo(ViewRequestsInfo *info) { delete _viewRequestsInfo; _viewRequestsInfo = info; }
  inline ViewRequestsInfo *     viewRequestsInfo() { return _viewRequestsInfo; }

  inline void                   setAction(ClockAction action) { _action = action; }
  ClockAction                   action() { return _action; }
  
  inline void                   setEmployeeRequests(EmployeeRequests *requests) { delete _employeeRequests; _employeeRequests = requests; }
  inline EmployeeRequests *     employeeRequests() { return _employeeRequests; }

  inline void                   setOverrideInfo(OverrideInfo *info) { delete _overrideInfo; _overrideInfo = info; }
  inline OverrideInfo *         overrideInfo() { return _overrideInfo; }

  inline void                   setInWorkflow(bool inWorkflow) { _inWorkflow = inWorkflow; }
  inline bool                   inWorkflow() { return _inWorkflow; }
 
  inline void                   setCoveredEmployees(CoveredEmployees *coveredEmployees) { delete _coveredEmployees; _coveredEmployees = coveredEmployees; }
  inline CoveredEmployees *     coveredEmployees() { return _coveredEmployees; }
 
  inline void                   setJobCodes(JobCodes *jobCodes) { delete _jobCodes; _jobCodes=jobCodes;}
  inline JobCodes *             jobCodes() { return _jobCodes; }

  inline void                   setTimesheets(Timesheets *sheets) { delete _timesheets; _timesheets = sheets; }
  inline Timesheets *           timesheets() { return _timesheets; }

  inline void                   setBreakTypes(BreakTypes *types) { delete _breakTypes; _breakTypes = types; }
  inline BreakTypes *           breakTypes() { return _breakTypes; }

  inline EmployeeScheduleConfig&scheduleConfig() { return _scheduleConfig; }
  

ModuleConfigBase *                  moduleConfig(int moduleNumber) { Q_UNUSED(moduleNumber); return NULL; } //V7

  int                           formTimeout() { return _companyConfig.formTimeout; }

  QString                       id;
  QString                       pin;

  bool                          isOnBreak;
  QString                       clockStatus;
  QDateTime                     breakStartDateTime;

  QList<MenuCommand*>           menu;

 private:
  void                          clearLists();
  CompanyConfig&                _companyConfig;
  EmployeeInfoItem              _employeeInfo;
  ClockEntryType                _entryType;
  bool                          _bioVerified;
  IStore *                      _store;
  LastPunchInfo	*		_lastPunch;
  EmployeeHours *               _hours;
  EmployeeMessages *            _messages;
  EmployeeAccruals *            _accruals;
  EmployeeSchedules *           _schedules;
  ChangePinInfo *               _changePinInfo;
  CostCodeList *                _costCodeList;
  TrackedInfo *                 _trackedInfo;
  ConfirmMissedInfo *           _confirmMissed;
  ConfirmMissedSummaryInfo *    _confirmMissedSummary;
  GatherMissedTimeInfo *        _missedTimeInfo;
  ViewRequestsInfo *            _viewRequestsInfo;
  EmployeeRequests *            _employeeRequests;
  OverrideInfo *                _overrideInfo;
  CoveredEmployees *            _coveredEmployees;
  JobCodes *                    _jobCodes;
  BreakTypes *                  _breakTypes;
  BreakOnClockOutInfo *         _breakOnClockOutInfo;
  Timesheets *                  _timesheets;
  VerificationSpec *            _verificationSpec;
  bool                          _inWorkflow;
  ClockAction                   _action;
  bool                          _qpClockedIn;
  qint64                        _quickPunchId;
  DatePeriods*                  _datePeriods;
  OfflineRecord                 _offlineRecord;
  CostCodeOptionInfo *          _costOptionInfo;
  EmployeeScheduleConfig        _scheduleConfig;
  bool                          debugLanguage;
};

#endif
