#ifndef DEFINES70
#define DEFINES70

#define MENU_DASHBOARD     "Dashboard"
#define MENU_CLOCKIN       "ClockIn"
#define MENU_CLOCKOUT      "ClockOut"
#define MENU_BREAK         "Break"
#define MENU_CHANGEJOB     "ChangeJob"
#define MENU_CHANGECOST    "ChangeCost"
#define MENU_VIEWHOURS     "ViewHours"
#define MENU_VIEWLASTPUNCH "ViewLastPunch"
#define MENU_VIEWSCHEDULE  "ViewSchedules"
#define MENU_VIEWMESSAGES  "ViewMessages"
#define MENU_REQUESTS      "Requests"
#define MENU_CHANGEPIN     "ChangePin"
#define MENU_VIEWACCRUALS  "ViewAccruals"
#define MENU_TIMESHEET     "ManageTimesheet"


#define EXTYPE_PRESENTATION  0
#define EXTYPE_CONFIRMATION  20
#define EXTYPE_CONFIRMATIONDEACTIVATE 21
#define EXTYPE_CONFIRMATIONUNASSIGN  22
#define EXTYPE_CONFIRMATIONVARIANCE  23
#define EXTYPE_CURRENTWEEKSTALE  30
#define EXTYPE_INFORMATION  50
#define EXTYPE_INVALIDSESSION  55
#define EXTYPE_PERSISTENCE  60
#define EXTYPE_INVALIDHUB  65
#define EXTYPE_WORKFLOW  70
#define EXTYPE_UNEXPECTED  99
#define EXTYPE_UNABLETOREACHSERVER  100

#define BIOACTION_VERIFY         1
#define BIOACTION_ENROLL         2
#define BIOACTION_ADMINISTRATOR  3

#define DATEFORMAT_CULTURE  1
#define DATEFORMAT_MDY 2
#define DATEFORMAT DMY 3
#define DATEFORMAT_MD 4
#define DATEFORMAT_DM 5

#define RDT_HANDSCANNER    1
#define RDT_COGENTFP       2
#define RDT_DIGITALPERSONA 3

#define OFFLINE_TERMINALSPEC "terminalspec7.json"
#define OFFLINE_COMPANYLIST "companylist7.json"

// SHA1 authentication keys
#define MANUAL_KEY "7.0-manual_%1_auth"
#define SESSION_KEY "7.0-session_%1_auth"
#define TERMINAL_KEY "7.0-terminal_%1_auth"
#define STATUS_KEY "7.0-status_%1_auth"
#define ADDITION_AUTH "-terminal_%1_auth"

// Define this if biometric template download require an authenticated session
#define BIOREQUIRESAUTH

// Automaticalliy fall out of the get employee screen every 5 minutes to refresh the configuration if the screen saver is not active
#define CONFIGREFRESH (5 * 60)

// Resync the time with the server every 10 minutes
#define TIMESYNCINTERVAL (10 * 60)

// Update Validation files every 2 hours
#define OFFLINEUPDATEINTERVAL (60 * 120)

// Interval at which the clock status (ip, netmask, RX/TX etc. will be uploaded to the server)
#define STATEUPDATEINTERVAL (60 * 2)

// Interval at which the termnial will check to see if a firmware update is available
#define UPDATECHECKINTERVAL (4 * 60 * 60)

#define APPLICATIONID 105

#define FIREONPRESS true

#define SCREENSAVERTIMEOUT (3 * 60)
//#define SCREENSAVERTIMEOUT (20)

#define TRACKEDCOUNT 3

#define BREAKTYPES 5

#define RDT_LANG_KEY "ObjClockResources"

#endif
