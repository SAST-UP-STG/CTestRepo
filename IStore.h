#ifndef ISTORE_H
#define ISTORE_H

class OperationContext;
class User;
class CustomFieldDataList;
class CompanyInfo;
class EmployeeHoursItem;
class CompanyConfig;
class FPTemplate;
class FPTemplates;
class ScheduleSwapContext;
class EmployeeInfoItem;
class ScheduleOffersContext;
class ScheduleSwapsContext;

#include "EmployeeHourItem.h"
#include "ClockOperationDefines.h"
#include "RequestLoadHours.h"
#include "EmployeePinItem.h"
#include "RequestItem.h"
#include "CostCodeItem.h"
#include "CoveredEmployeeItem.h"
#include "JobCodeItem.h"
#include "SegmentNoteItem.h"
#include "TimesheetItem.h"
#include "OfflineRecord.h"

class IStore
{
  public:
  IStore() {}
  virtual ~IStore() {}

  virtual bool isOnline() { return false; }
  virtual bool gatherBreakInfo() { return false; }
  virtual bool getHeaderInformation() { return false; }
  virtual bool logOff() { return false; }
  virtual bool cancel() { return false; }
  virtual bool getLastPunch() { return false; }
  virtual bool getHours(HourLoadAction action) { return false; }
  virtual bool approveSegment(EmployeeHourDetail *detail) { return false; }
  virtual bool confirmApproval(EmployeeHourDetail *detail) { return false; }
  virtual bool getMessages() { return false; }
  virtual bool markMessagesRead(QList<int>& messageIds) { return false; }
  virtual bool getAccruals(QDate *forecastDate = NULL) { return false; }
  virtual bool getChangePinInfo() { return false; }
  virtual bool updatePin(NewPinInfo& info) {return false; }
  virtual bool confirmChangePin() { return false; }
  virtual bool loadSchedules(HourLoadAction action, QString *period = NULL) { return false; }
  virtual bool startOperation(ClockAction action,int data = 0, QString photoFile = QString("")) { return false; }
  virtual bool confirmEmployee() { return false; }
  virtual bool confirmJobCode(int recordId) { return false; }
  virtual bool confirmCostCode(int recordId) { return false; }
  virtual bool confirmTrackedFields(QList<double>& fields, bool isIn) { return false; }
  virtual bool confirmMissedPunch() { return false; }
  virtual bool confirmMissedPunchSummary() { return false; }
  virtual bool submitMissedTime(QDateTime time, QString note) { return false; }
  virtual bool getViewRequestsInfo() { return false; }
  virtual bool getViewRequestsData(RequestDataOptions& options) { return false; }
  virtual bool deleteRequest(int recordId, bool confirmed) { return false; }
  virtual bool getAddEditRequestInfo(RequestEditInfo& info, int recordId = 0)  { return false; }
  virtual bool selectRequestTemplate(RequestEditInfo& info, int recordId) { return false;}
  virtual bool saveEmployeeRequest(RequestEditInfo& info, QStringList& exceptions) { return false; }
  virtual bool submitOverrideRestriction(int userRecordId, QString password, QString note) { return false; }
  virtual bool submitOverrideRestrictionWithFingerprint(int userRecordId, QString confirmationValue, QString note) { return false; }
  virtual bool submitMessagesRead(QList<int>& messageIds) { return false; }
  virtual bool getCostCodeDataForSelection(CostCodeSelectionInfo& info, CostCodeList *list = 0) { return false; }
  virtual bool searchCostCode(CostCodeSelectionInfo& info) { return false; }
  virtual bool listModeFilterCostCodes(CostCodeFilterInfo& info) { return false; }
  virtual bool filterCoveredEmployees(CoveredEmployeeFilterInfo& info) { return false; }
  virtual bool submitCoveredEmployee(int recordId) { return false; }
  virtual bool filterJobCodes(JobCodeFilterInfo& info) { return false; }
  virtual bool toggleItemExpanded(int recordId) { return false; }
  virtual bool filterCostCodeTreeItems(CostCodeFilterInfo& info) { return false; }
  virtual bool saveNote(QString note) { return false; }
  virtual bool getSegmentNotes(int recordId, SegmentNotes& notes) { return false; }
  virtual bool getManageTimesheetInformation() { return false; }
  virtual bool addTimesheetSegment(QDate& date) { return false; }
  virtual bool acceptTimesheetChanges() { return false; }
  virtual bool rejectTimesheetChanges() { return false; }
  virtual bool editTimesheet(TimesheetEditData& editData) { return false; }
  virtual bool loadTimesheetEditContext(TimesheetEditData& editData) { return false; }
  virtual bool timesheetCostSearch(int jobRecordId, QString search, QList<TimesheetCostSearchItem*>& codes) { return false; }
  virtual bool saveTimesheet(TimesheetEditData& record) { return false; }
  virtual bool logOnFromTerminal() { return false; }
  virtual bool logOnAndStartFromTerminal() { return false; }
  virtual bool confirmEmployeeVerification() { return false; }
  virtual bool getEmployeePhoto(QByteArray& photo) { return false; }
  virtual bool getMatchingEmployee(QString badgeNumber, qint64 *resolvedId) { return false; }
  virtual bool submitDigitalOutputLog() { return false; }
  virtual bool approveTimesheetDay(QStringList& ids, bool approve) { return false; }
  virtual bool submitQuestionOnClockOut(bool response) { return false; }
  virtual bool submitQuestionOnClockOutAck() { return false; }
  virtual bool getAddSubRequirementInfo(RequestEditInfo& info) { return false; }
  virtual bool addRequestSubSegment(QDate date) { return false; }
  virtual bool getEditSubSegmentInfo(TimesheetEditData& editData) { return false; }
  virtual bool saveRequestSubSegmentInfo(TimesheetEditData& editData) { return false; }
  virtual bool reloadRequestSubData() { return false; }
  virtual bool addSubRequirement(bool confirmModification) { return false; }
  virtual bool clearSubRequestSegment(QString id) { return false; }
  virtual bool getEditSubRequirement(int recordId) { return false; }
  virtual bool submitBreakOnClockOut() { return false; }
  virtual bool filterCostCodeOptions(CostCodeFilterInfo &filter) { return false; }
  virtual bool submitCostCodeOption(QString option) { return false; }
  virtual bool dropSchedule(int recordId, QString reason) { return false; }
  virtual bool cancelDropSwap(int recordId) { return false; }
  virtual bool getScheduleSwapInfo(int recordId, ScheduleSwapContext& swapContext) { return false; }
  virtual bool swapGetNextStep(ScheduleSwapContext& swapContext) { return false; }
  virtual bool swapUpdateProgress(ScheduleSwapContext& swapContext) { return false; }
  virtual bool swapFilterEmployees(ScheduleSwapContext & swapContext) { return false; }
  virtual bool finishSwapSchedule() { return false; }
  virtual bool getOffers(ScheduleOffersContext& offerContext) { return false; }
  virtual bool getOffersData(ScheduleOffersContext& offerContext) { return false; }
  virtual bool handleOpenCommand(ScheduleOffersContext& offersContext, int recordId, int command) { return false; }
  virtual bool handleSwapCommand(ScheduleSwapsContext& swapsContext, int recordId, int command) { return false; }

  virtual bool getSwaps(ScheduleSwapsContext& swapsContext) { return false; }
  virtual bool getSwapsData(ScheduleSwapsContext& swapsContext) { return false; }
  virtual bool getInfo() { return false; }
};


class IUserStore
{
 public:
  IUserStore() {}
  virtual ~IUserStore() {}
  
  virtual bool ping(int *pingStatus = NULL) { return false; }
  virtual bool userAutoLogOn() { return false; }
  virtual bool userLogOnX(QString userId, QString password) { return false; }
  virtual bool userLogOnFromTerminal(QString userId, QString password) { return false; }

  virtual bool userLogOff() { return false; } 
  virtual bool confirmUserVerification();
  virtual bool registerTerminal(QString name) { return false; }
  virtual bool unregisterTerminal() { return false; }
  virtual bool getTerminalSpecification(CompanyConfig *config = NULL, QList<CompanyConfig*> *configs = NULL) { return false; }
  virtual bool getTerminalSpecifications(QList<CompanyConfig*>& companies) { return false; }
  virtual bool saveEmployeeBiometricTemplate(int module, qint64 employeeId, FPTemplate& data) {return false; }
  virtual bool saveUserBiometricTemplate(int module, QString userId, FPTemplate& data) {return false; }
  virtual bool getEmployeeBiometricTemplates(int module, qint64 employeeId, FPTemplates& templates) { return false; }
  virtual bool getUserBiometricTemplates(int module, QString userId, FPTemplates& templates) { return false; }
  virtual bool getPotentialBiometricUsers(int module, QList<User*>& users, int action) { return false; }
  virtual bool lookupEmployee(QString badgeNumber, EmployeeInfoItem& employee) { return false; }
  virtual bool getUsersFromTerminal(QList<User*>& users) { return false; }
  virtual bool updateTerminalStatus();
  virtual bool getEmployeeValidationFile(QList<EmployeeInfoItem*>& employees);
  virtual bool getCostCodeValidationFile(QList<CostCodeItem*>& codes);
  virtual bool submitOfflinePunches(QList<OfflineRecord*>& punches);
  virtual bool getUTCTime(QDateTime& utcTime);
  virtual bool selectEnrollBadgeEmployee(EmployeeInfoItem& info);
  virtual bool enrollEmployeeBadge(QString badge);
  
};

  
#endif  
