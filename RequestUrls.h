#ifndef REQUESTURL_H
#define REQUESTURL_H

/*****************************************************************************************************
                                        Clock Operations 
*****************************************************************************************************/

//#define REQUEST_EMPLOYEELOGON "/api/v0000/employeeSessions/0/ApplicationLogOn"

#define REQUEST_STARTOPERATION "/api/v0000/clockOperation/{data}/Start{operation}"

#define REQUEST_GATHERBREAKINFO "/api/v0000/clockOperation/0/GetGatherBreakInfo"

#define REQUEST_GETHEADERINFORMATION "/api/v0000/webClockHeader/0/GetHeaderInformation"

#define REQUEST_LOGOFF "/api/v0000/employeeSessions/{sessionid}/LogOff"

#define REQUEST_CANCEL "/api/v0000/clockOperation/0/Cancel"

#define REQUEST_PING "/api/v0000/employeeSessions/0/Ping"

#define REQUEST_GETLASTPUNCH "/api/v0000/viewLastPunch/0/GetViewLastPunchInformation"

#define REQUEST_LOADHOURS "/api/v0000/ViewHours/0/GetViewHoursInformation"
#define REQUEST_LOADHOURSNEXT  "/api/v0000/ViewHours/0/GetNextPeriod"
#define REQUEST_LOADHOURSPREVIOUS "/api/v0000/ViewHours/0/GetPreviousPeriod"
#define REQUEST_APPROVESEGMENT "/api/v0000/ViewHours/0/Approve"
#define REQUEST_CONFIRMAPPROVAL "/api/v0000/viewHours/0/ConfirmApprovalMessage"
#define REQUEST_CONFIRMAPPROVALTIMESHEET "/api/v0000/ManageTimesheets/0/ConfirmApprovalMessage"
#define REQUEST_GETEMPLOYEEPHOTO "/api/v0000/clockOperation/0/GetPhoto"
#define REQUEST_RETURNFROMBREAK "/api/v0000/clockOperation/0/ReturnFromBreak"

#define REQUEST_LOADMESSAGES "/api/v0000/ViewMessages/0/GetViewMessagesInformation"
#define REQUEST_MARKMESSAGESREAD "/api/v0000/viewMessages/0/MarkAsRead"

#define REQUEST_LOADACCRUALS "/api/v0000/ViewHours/0/GetViewAccrualsInformation"
#define REQUEST_UPDATEACCRUALS "/api/v0000/ViewHours/0/UpdateAccrualForecast?accrualForecastDate={date}"

#define REQUEST_GETCHANGEPININFO "/api/v0000/changePin/0/GetFeatureInfo"
#define REQUEST_UPDATEPIN "/api/v0000/changePin/0/Submit"
#define REQUEST_CONFIRMPINCHANGE "/api/v0000/changePin/0/Confirm"

#define REQUEST_LOADSCHEDULES "/api/v0000/viewSchedules/0/getFeatureInfo"
#define REQUEST_LOADSCHEDULESNEXT "/api/v0000/viewSchedules/0/getPeriod?isPrevious=false"
#define REQUEST_LOADSCHEDULESPREV "/api/v0000/viewSchedules/0/getPeriod?isPrevious=true"
#define REQUEST_DROPSCHEDULE "/api/v0000/viewSchedules/0/DropSchedule"
#define REQUEST_CANCELDROPSWAP "/api/v0000/viewSchedules/0/HandleManageMenuCommand?command=DeletePending"
#define REQUEST_GETSCHEDULESWAPINFO "/api/v0000/swapSchedules/0/GetSwapScheduleInformation?recordId={recordId}"
#define REQUEST_SWAPGETNEXTSTEP "/api/v0000/swapSchedules/0/GetNextStep"
#define REQUEST_FINISHSWAPSCHEDULE "/api/v000/swapSchedules/0/FinishSwapSchedule"
#define REQUEST_LOADSCHEDULEPERIOD "/api/v0000/viewSchedules/0/getSelectedPeriod?selectedDate={period}"
#define REQUEST_GETVIEWOPENSINFORMATION "/api/v0000/EmployeeViewOpens/0/GetViewOpensInformation"
#define REQUEST_GETVIEWOPENSDATA "/api/v0000/EmployeeViewOpens/0/GetViewOpensData"
#define REQUEST_HANDLEOPENCOMMAND "/api/v0000/EmployeeViewOpens/{recordId}/HandleOpenCommand?command={command}"
#define REQUEST_SWAPUPDATEPROGRESS "/api/v0000/swapSchedules/0/UpdateProgress"
#define REQUEST_SWAPFILTEREMPLOYEES "/api/v0000/swapSchedules/0/FilterEmployees"
#define REQUEST_GETVIEWSWAPSINFORMATION "/api/v0000/EmployeeViewSwaps/0/GetViewSwapsInformation"
#define REQUEST_GETVIEWSWAPSDATA "/api/v0000/EmployeeViewSwaps/0/GetViewSwapsData"
#define REQUEST_HANDLESWAPSCOMMAND "/api/v0000/EmployeeViewSwaps/0/HandleSwapCommand?command={command}"

#define REQUEST_CONFIRMEMPLOYEE "/api/v0000/clockOperation/0/ConfirmEmployee"
#define REQUEST_CONFIRMJOBCODE "/api/v0000/clockOperation/{recordid}/SubmitJobCode"
#define REQUEST_CONFIRMCOSTCODE "/api/v0000/clockOperation/{recordid}/SubmitCostCode"
#define REQUEST_CONFIRMTRACKEDFIELDS "/api/v0000/clockOperation/0/SubmitTrackedFields"
#define REQUEST_CONFIRMLABORSTANDARDS "/api/v0000/clockOperation/0/SubmitLaborStandards"
#define REQUEST_CONFIRMMISSEDPUNCH "/api/v0000/clockOperation/0/ConfirmMissedPunch"
#define REQUEST_CONFIRMMISSEDPUNCHSUMMARY "/api/v0000/clockOperation/0/ConfirmMissedPunchSummary"
#define REQUEST_SUBMITMISSEDDATEANDTIME "/api/v0000/clockOperation/0/SubmitMissedDateAndTime?formattedDate={date}&formattedTime={time}&note={note}"

#define REQUEST_GETVIEWREQUESTSINFO "/api/v0000/manageRequestsEmployee/0/GetViewRequestsInfo"
#define REQUEST_GETVIEWREQUESTSDATA "/api/v0000/manageRequestsEmployee/0/GetViewRequestsData"
#define REQUEST_DELETEREQUEST "/api/v0000/manageRequestsEmployee/0/DeleteRequests?confirmed={confirmed}"
#define REQUEST_GETADDEDITREQUESTINFORMATION "/api/v0000/manageRequestsEmployee/{recordId}/GetAddEditEmployeeRequestInformation?requestedDate={requestdate}"
#define REQUEST_SELECTEMPLOYEEREQUESTTEMPLATE "/api/v0000/manageRequestsEmployee/0/SelectEmployeeRequestTemplate?employeeRequestTemplateRecordId={templateid}"
#define REQUEST_SAVEEMPLOYEEREQUEST "/api/v0000/manageRequestsEmployee/0/SaveEmployeeRequest"

#define REQUEST_LOADCOMPANIES "/api/v0000/employeeLoginValues/0/GetValidSortedCompanies?companyNamespace={ns}"

#define REQUEST_SUBMITOVERRIDERESTRICTION "/api/v0000/clockOperation/0/SubmitOverrideRestriction?userRecordId={recordid}&password={password}&note={note}"
#define REQUEST_SUBMITOVERRIDERESTRICTIONWITHFINGERPRINT "/api/v0000/clockOperation/0/SubmitOverrideRestrictionWithFingerprint?userRecordId={recordid}&confirmationValue={confirmValue}&note={note}"

#define REQUEST_SUBMITMESSAGESREAD "/api/v0000/clockOperation/0/SubmitMessagesRead"
#define REQUEST_GETCOSTCODEDATAFORSELECTION "/api/v0000/clockOperation/0/GetGatherCostCodeDataForSelection"

#define REQUEST_SEARCHCOSTCODE "/api/v0000/clockOperation/0/SearchCostCode?level={level}"
#define REQUEST_FILTERCOSTCODES "/api/v0000/clockOperation/0/FilterCostCodes"
#define REQUEST_FILTERJOBCODES "/api/v0000/clockOperation/0/FilterJobCodes"

#define REQUEST_FILTEREDDATA "/api/v0000/clockOperation/0/FilteredData"
#define REQUEST_SUBMITCOVEREDEMPLOYEE "/api/v0000/clockOperation/{employee}/SubmitCoveredEmployee"

#define REQUEST_FILTERCOSTCODETREEITEMS "/api/v0000/clockOperation/0/FilterCostCodeTreeItems"
#define REQUEST_TOGGLEITEMEXPANDED "/api/v0000/clockOperation/0/ToggleItemExpanded?id={recordId}"

#define REQUEST_SAVENOTE "/api/v0000/employeeManageWorkSegmentNotes/0/SaveNote"
#define REQUEST_GETSEGMENTNOTESINFO "/api/v0000/employeeManageWorkSegmentNotes/0/GetSegmentNotesInformation?workSegmentId={recordId}"

#define REQUEST_GETMANAGETIMESHEETINFORMATION "/api/v0000/ManageTimeSheets/0/GetManageTimesheetInformation"
#define REQUEST_ADDTIMESHEETSEGMENT "/api/v0000/ManageTimesheetHours/0/AddSegment?selectedDate={date}"
#define REQUEST_ACCEPTTIMESHEETCHANGES "/api/v0000/ManageTimesheets/0/AcceptChanges"
#define REQUEST_REJECTTIMESHEETCHANGES "/api/v0000/ManageTimesheets/0/RejectChanges"
#define REQUEST_MANAGETIMESHEETEDITHOURS "/api/v0000/ManageTimesheetEditHours/{uniqueId}/Manage"
#define REQUEST_LOADTIMESHEETEDITCONTEXT "/api/v0000/ManageTimesheetEditHours/{jobRecordId}/JobCode?costCodeFullName={costCode}"
#define REQUEST_SAVETIMESHEET "/api/v0000/ManageTimesheetEditHours/{uniqueId}/SaveWorkSegment"
#define REQUEST_TIMESHEETCOSTSEARCH "/api/v0000/ManageTimesheetEditHours/0/SearchCostCodes?searchQuery={search}&jobCodeRecordId={jobRecordId}"
#define REQUEST_APPROVETIMESHEETDAY "/api/v0000/ManageTimesheetHours/0/ApproveSegments?shouldApprove={approve}"

#define REQUEST_REGISTERTERMINAL "/api/v0000/terminalSpecifications/0/RegisterStandAloneTerminal?standAloneTerminalName={name}"
#define REQUEST_UNREGISTERTERMINAL "/api/v0000/terminalSpecifications/0/UnRegisterStandAloneTerminal"
#define REQUEST_GETUNAUTHENTICATEDSESSION "/api/v0000/terminalSpecifications/0/GetUnauthenticatedSessionId"
#define REQUEST_USERLOGIN "/api/v0000/userSessions/0/LogOn"
#define REQUEST_USERLOGOFF "/api/v0000/userSessions/{sessionId}/LogOff"
#define REQUEST_GETTERMINALSPECIFICATIONS "/api/v0000/terminalSpecifications/0/GetStandaloneSpecs?companyNamespace={ns}&previousServerTimestamp={timestamp}"

#define REQUEST_SAVEBIOMETRICTEMPLATECOGENT "/api/v0000/Biometric/0/SaveCogentFingerprintSpec?companyNamespace={ns}"
#define REQUEST_SAVEBIOMETRICTEMPLATEDP "/api/v0000/Biometric/0/SavePersonaFingerprintSpec?companyNamespace={ns}"
#define REQUEST_SAVEBIOMETRICTEMPLATEHS "/api/v0000/Biometric/0/SaveSchlageHandscanSpec?companyNamespace={ns}"

#define REQUEST_GETEMPLOYEEBIOMETRICTEMPLATESCOGENT "/api/v0000/Biometric/0/GetEmployeeCogentFingerprintSpecs?companyNamespace={ns}&employeeId={employeeId}&terminalId={terminalId}"
#define REQUEST_GETEMPLOYEEBIOMETRICTEMPLATESDP "/api/v0000/Biometric/0/GetEmployeePersonaFingerprintSpecs?companyNamespace={ns}&employeeId={employeeId}&terminalId={terminalId}"
#define REQUEST_GETEMPLOYEEBIOMETRICTEMPLATESHS "/api/v0000/Biometric/0/GetEmployeeSchlageHandscanSpec?companyNamespace={ns}&employeeId={employeeId}&terminalId={terminalId}"

#define REQUEST_GETUSERBIOMETRICTEMPLATESCOGENT "/api/v0000/Biometric/0/GetUserCogentFingerprintSpecs?companyNamespace={ns}&userId={userId}&terminalId={terminalId}"
#define REQUEST_GETUSERBIOMETRICTEMPLATESDP "/api/v0000/Biometric/0/GetUserPersonaFingerprintSpecs?companyNamespace={ns}&userId={userId}&terminalId={terminalId}"
#define REQUEST_GETUSERBIOMETRICTEMPLATESHS "/api/v0000/Biometric/0/GetUserSchlageHandscanSpec?companyNamespace={ns}&userId={userId}&terminalId={terminalId}"

#define REQUEST_GETPOTENTIALBIOMETRICUSERS "/api/v0000/Biometric/0/GetPotential{biotype}{action}Users?companyNamespace={ns}&terminalId={terminalId}"

#define REQUEST_LOOKUPEMPLOYEE "/api/v0000/Biometric/0/GetEmployee?companyNamespace={ns}&terminalId={terminalId}&badgeNumberOrEmployeeId={badge}"

#define REQUEST_CONFIRMEMPLOYEEVERIFICATION "/api/v0000/employeeSessions/{id}/TerminalConfirmVerification?confirmationValue={confirmation}"
#define REQUEST_CONFIRMUSERVERIFICATION "/api/v0000/userSessions/{id}/TerminalConfirmVerification?confirmationValue={confirmation}"

#define REQUEST_LOGONFROMTERMINAL "/api/v0000/employeeSessions/{id}/TerminalLogOn"
#define REQUEST_LOGONANDSTARTFROMTERMINAL "/api/v0000/employeeSessions/{id}/TerminalLogOnAndStart?clockOperationType={clockAction}&breakTypeRecordId={breakId}"

#define REQUEST_GETINFO "/api/v0000/employeeLoginValues/1/GetInfo?companyNamespace={ns}&applicationId={appId}"

//#define REQUEST_USERLOGONFROMTERMINAL "/api/v0000/userSessions/{id}/TerminalLogOn"
#define REQUEST_USERLOGONFROMTERMINAL "/api/v0000/userSessions/0/TerminalLogOn?id={id}"

#define REQUEST_GETUSERSFROMTERMINAL "/api/v0000/userSessions/0/GetUsersFromTerminal?companyNamespace={ns}&companyId={company}&confirmationValue={confirmationValue}"

#define REQUEST_GETMATCHINGEMPLOYEES "/api/v0000/employeeSessions/{id}/TerminalGetMatchingEmployeeIdAndStatus?companyNamespace={ns}&companyId={company}&badgeNumber={badge}"

#define REQUEST_UPDATETERMINALSTATUS "/api/v0000/terminalSpecifications/0/UpdateStandaloneTerminal?companyNamespace={ns}&encodedStatus={status}&confirmationValue={confirmationValue}"

#define REQUEST_GETEMPLOYEEINFORMATION "/api/v0000/EmployeeDashboard/0/GetInformation"

#define REQUEST_SUBMITDIGITALOUTPUTLOG "/api/v0000/DigitalOutputLog/0/SubmitDigitalOutputLog"

#define REQUEST_GETEMPLOYEEVALIDATIONFILE "/api/v0000/TerminalSpecifications/0/GetStandaloneFallbackEmployees?terminalId={id}"
#define REQUEST_GETCOSTCODEVALIDATIONFILE "/api/v0000/TerminalSpecifications/0/GetStandaloneFallbackCostCodes?terminalId={id}"

#define REQUEST_SUBMITOFFLINEPUNCHES "/api/v0000/OfflinePunches/0/AddOfflineStandaloneTerminalPunches?deviceId={id}"


#define REQUEST_SUBMITQUESTION "/api/v0000/clockOperation/0/SubmitQuestionOnClockOut?response={response}"
#define REQUEST_QUESTIONONCLOCKOUTACK "/api/v0000/clockOperation/0/SubmitQuestionOnClockOutAcknowledgement"
#define REQUEST_SUBMITQUESTIONAUTOBREAK "/api/v0000/clockOperation/0/SubmitQuestionOnAutomaticBreak?response={response}"
#define REQUEST_SUBMITQUESTIONMEALBREAK "/api/v0000/clockOperation/0/SubmitQuestionOnMealBreak?response={response}"
#define REQUEST_SUBMITQUESTIONMISSEDBREAKENTRY "/api/v0000/clockOperation/0/SubmitMissedBreakQuestion?response={response}"

#define REQUEST_GETTIMESTAMPUTC "/api/v0000/TerminalSpecifications/0/GetTimeStampUtc?companyNamespace={ns}"

#define REQUEST_GETADDSUBREQUIREMENTINFO "/api/v0000/employeeAddSubRequirement/0/GetAddSubRequirementInformation"
#define REQUEST_ADDREQUESTSUBSEGMENT "/api/v0000/employeeAddSubRequirement/0/AddSegment?date={date}"
#define REQUEST_GETEDITSUBSEGMENTINFO "/api/v0000/employeeEditSubStaffingSegment/0/GetEditSubStaffingSegmentInformation?uniqueId={id}"
#define REQUEST_SAVEREQUESTSUBSEGMENT "/api/v0000/employeeEditSubStaffingSegment/0/SaveSegment"
#define REQUEST_RELOADREQUESTSUBDATA "/api/v0000/employeeAddSubRequirement/0/ReloadPeriod"
#define REQUEST_ADDSUBREQUIREMENT "/api/v0000/employeeAddSubRequirement/0/AddSubRequirement?confirmModification={confirm}"
#define REQUEST_CLEARSUBREQUESTSEGMENT "/api/v0000/employeeAddSubRequirement/0/ClearSegment?uniqueId={id}"
#define REQUEST_GETEDITSUBREQUIREMENT "/api/v0000/employeeAddSubRequirement/0/getEditSubRequirementInformation?employeeRequestRecordId={recordId}"

#define REQUEST_SUBMITBREAKONCLOCKOUT "/api/v0000/clockOperation/0/submitBreakOnClockOut"
#define REQUEST_SUBMITGATHERMISSEDBREAK "/api/v0000/clockOperation/0/SubmitGatherMissedBreak"
#define REQUEST_SUBMITSKIPMISSEDBREAK "/api/v0000/clockOperation/0/SkipMissedBreakEntry"

#define REQUEST_SUBMITCOSTCODEOPTION "/api/v0000/clockOperation/0/SubmitCostCodeOption"
#define REQUEST_FILTERCOSTCODEOPTIONS "/api/v0000/clockOperation/0/FilterCostCodeOptionSelections"

#define REQUEST_SELECTENROLLBADGEEMPLOYEE "/api/v0000/badgeEnrollment/0/SelectEmployee?individualId={id}"
#define REQUEST_ENROLLEMPLOYEEBADGE "/api/v0000/badgeEnrollment/0/EnrollEmployee?badgeNumber={badge}"

#define REQUEST_GETFEATUREINFORMATION "/api/v0000/EmployeeConfirmationAction/0/GetFeatureInformation"

#define REQUEST_GETUPDATESERVER "/api/v0000/TerminalSpecifications/0/GetRdtgUpdateServer"

#define REQUEST_GETOCCURRENCEINFO "/api/v0000/viewOccurrences/0/GetInfo"
#define REQUEST_FILTEROCCURRENCES "/api/v0000/employeeOccurrences/0/FilterOccurrences"

#define REQUEST_GETBIOENROLLMENTAGREEMENT "/api/v0000/Biometric/0/GetAttestationAgreement?terminalId={tid}&biometricPeripheralType={bioType}&employeeId={employee}"
#define REQUEST_SAVEATTESTATIONRESPONSE "/api/v0000/Biometric/0/SaveAttestationResponse?terminalId={tid}"


#endif










