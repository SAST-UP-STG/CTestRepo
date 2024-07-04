#ifndef CLOCKOPERATIONDEFINES_H 
#define CLOCKOPERATIONDEFINES_H 

#include <QtCore>

/// <summary>
 /// Represents the current action of the clock operation.  This information is passed to modules
 /// and to the running application to take specific action for certain operations.
 /// </summary>
 typedef enum tagClockAction
 {
  None = -1,
  In = 0,
  Out = 1,
  Break = 2,
  JobCode = 3,
  JobCost = 4,
  View = 5,
  Toggle = 6,
  Hours = 7,
  Schedule = 8,
  LastPunch = 9,
  Accruals = 10,
  TimesheetEntry = 11,
  ViewEmployeeMessages = 12,
  ChangePinNumber = 13,
  TimeOffRequest = 14,
  EndBreak = 15,
  ViewOffers = 16,
  ViewSwaps = 17,

  Invalid = 999,
 } ClockAction;


typedef enum tagClockEntryType
{
  ETApplicationCancel = -3,
  ETUserCancel = -2,
  ETTimeout = -1,
  ETNone = 0,
  ETBadge = 1,
  ETBiometrics = 2,
  ETManual = 3,
  ETNetworkId = 4,
  ETOther = 99,
} ClockEntryType;

typedef enum tagClockOperationStatus
{
 Ok = 0,
 UserCancel = 1,
 AppCancel = 2,
 Timeout = 3,
 AlreadyIn = 4,
 NotIn = 5,
 OutBeforeIn = 6,
 NoClockableCodes = 7,
 Suspended = 8,
 Terminated = 9,
 NotSetupForJobCost = 10,
 NotSetupForMultipleJobs = 11,
 ConflictingShift = 12,
 LogOpenFailure = 13,
 WriteFailure = 14,
 JobCodeNoCost = 15,
 EmployeeNotFound = 16,
 InUnderCode = 17,
 MustBeInForChangeJobOrCost = 18,
 BeforeCurrentWeek = 19,
 CannotAddMissedPunch = 20,
 NoTeachersConfigured = 21,
 DatabaseOpenError = 22,
 NoAccess = 23,
 UpdateFailure = 24,
 IdentityFailure = 25,
 FuturePunch = 26,
 TimesheetDisabled = 27,
 ExceedsMaxSegment = 28,
 ServerConnectionLost = 29,
 NoJobCodesAvailableForOperation = 30,
 NotOnBreak = 31,
} ClockOperationStatus;


#endif
