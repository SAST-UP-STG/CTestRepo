#include "OperationContext.h"
#include "70Defines.h"
#include "FilenameHelper.h"
#include "Externs.h"
#include "ImageConverter.h"
#include "BreakOnClockOutInfo.h"

OperationContext::OperationContext(CompanyConfig& companyConfig) : _companyConfig(companyConfig)
{
   _lastPunch = NULL;
   _hours = NULL;
   _messages = NULL;
   _accruals = NULL;
   _changePinInfo = NULL;
   _schedules = NULL;
   _costCodeList = NULL;
   _trackedInfo = NULL;
   _confirmMissed = NULL;
   _confirmMissedSummary = NULL;
   _missedTimeInfo = NULL;
   _viewRequestsInfo = NULL;
   _employeeRequests = NULL;
   _overrideInfo = NULL;
   _coveredEmployees = NULL;
   _jobCodes = NULL;
   _breakTypes = NULL;
   _timesheets = NULL;
   _verificationSpec = NULL;
   _datePeriods = NULL;
   _breakOnClockOutInfo = NULL;
   _costOptionInfo = NULL;

   debugLanguage = QFile::exists("TC_LANG");

   reset();

   init(companyConfig.companyId, "", companyConfig.terminalId);
}

OperationContext::~OperationContext()
{
   clearLists();

   delete _lastPunch;
   delete _hours;
   delete _messages;
   delete _accruals;
   delete _changePinInfo;
   delete _schedules;
   delete _costCodeList;
   delete _trackedInfo;
   delete _confirmMissed;
   delete _confirmMissedSummary;
   delete _missedTimeInfo;
   delete _viewRequestsInfo;
   delete _employeeRequests;
   delete _overrideInfo;
   delete _coveredEmployees;
   delete _jobCodes;
   delete _breakTypes;
   delete _verificationSpec;
   delete _datePeriods;
   delete _breakOnClockOutInfo;
   delete _costOptionInfo;
}

void OperationContext::reset()
{
   init(0, "", 0);
   setCompanyName("");

   _employeeInfo.reset();
   _action = None;

   _offlineRecord.reset();

   id = "";
   pin = "";

   qDeleteAll(menu);
   menu.clear();

   isOnBreak = false;
   isQuickPunch = false;

   _entryType = ETManual;
   _bioVerified = false;

   _inWorkflow = false;
   _qpClockedIn = false;

   _quickPunchId = 0;

   clearLists();
}

void OperationContext::clearLists()
{
   CLEAR(menu);
}

bool OperationContext::allowOperation(ClockAction action)
{
   switch (action)
   {
    case In: return companyConfig().allowClockInAction;
    case Out: return companyConfig().allowClockOutAction;
    case EndBreak:
    case Break: return companyConfig().allowBreakAction;
    case JobCode: return companyConfig().allowJobCodeAction;
    case JobCost: return companyConfig().allowCostCodeAction;
    case Hours: return companyConfig().allowViewHours;
    case Schedule: return companyConfig().allowViewSchedules;
    case TimeOffRequest: return companyConfig().allowTimeOffRequests;
    case Accruals: return companyConfig().allowViewAccruals;
    case ViewEmployeeMessages: return companyConfig().allowMessageViewingFromViewMenu;
    case ChangePinNumber: return companyConfig().allowChangePin;
    case LastPunch: return companyConfig().allowViewLastPunch;
    case TimesheetEntry: return companyConfig().timeSheetEntryType != 0;
    case ViewOffers: return companyConfig().allowViewOpens;
    case ViewSwaps: return companyConfig().allowViewSwaps;
    case View:
    case None:
    case Toggle:
    case Invalid:
       break;
   }

   qDebug() << "ERROR: Action " << action << "WAS NOT FOUND";
   return false;
}

QString OperationContext::translateAction(ClockAction action)
{
   switch (action)
   {
    case In: return MENU_CLOCKIN;
    case Out: return MENU_CLOCKOUT;
    case JobCode: return MENU_CHANGEJOB;
    case JobCost: return MENU_CHANGECOST;
    case ChangePinNumber: return MENU_CHANGEPIN;
    case Hours: return MENU_VIEWHOURS;
    case Schedule: return MENU_VIEWSCHEDULE;
    case LastPunch: return MENU_VIEWLASTPUNCH;
    case EndBreak: return MENU_BREAK;
    case Break: return MENU_BREAK;
    case ViewEmployeeMessages: return MENU_VIEWMESSAGES;
    case Accruals: return MENU_VIEWACCRUALS;
    case TimesheetEntry: return MENU_TIMESHEET;
    case TimeOffRequest: return MENU_REQUESTS;
    case Toggle: return "QuickPunch";
    case View:
    case None:
    case Invalid:
       break;
   }
   return "";
}

/*QString OperationContext::menuText(ClockAction action, QString defaultText)
   {
   QString menuCommand = translateAction(action);

   if (menuCommand.length() == 0) { return defaultText; }

   for (int q = 0; q < menu.count(); q++)
   {
      if (menu.at(q)->command.compare(menuCommand) == 0)
      {
         if (menu.at(q)->menuText.length())
         {
            return menu.at(q)->menuText;
         }
      }
   }
   return defaultText;
   }

   bool OperationContext::findMenu(QString menuCommand)
   {
   for (int q = 0; q < menu.count(); q++)
      if (menu.at(q)->command.compare(menuCommand) == 0) { return true; }

   return false;
   }*/

QString OperationContext::processText(QString text)
{
#ifdef CURLTEST
   return text;
#else
   return companyConfig().processText(text);
#endif
}


QString OperationContext::formatDate(const QDate date)
{
   return date.toString("MM/dd/yyyy"); //FIX
}

QString OperationContext::formatTime(int timeFormat, const QTime time, bool includeSeconds)
{
/*
        None = 0,
        HourMinute = 1,
        Military1 = 2,
        Military2 = 3,
        Hundredths = 4,
        Culture = 5,
        CultureFixed = 6,
        HourMinuteSecond = 7,
        HourMinuteFixed = 8,   // hh:mm tt
        HourMinuteShort = 9,     // h:mmt
 */

if(!gc.showSeconds) includeSeconds = false;


   switch (timeFormat)
   {
    case 3:
       return includeSeconds ? time.toString("hh:mm:ss") : time.toString("hh:mm");
    case 2:
       return includeSeconds ? time.toString("hh:mm:ss") : time.toString("hhmm");
    case 6:
       return includeSeconds ? time.toString("hh:mm:ss ap") : time.toString("hh:mm ap");
/*    case 4:
    {
       QString str;
       if(includeSeconds) str.sprintf("%d:%02d:%02d", time.hour(), time.minute(),time.second());
       else str.sprintf("%d:%02d", time.hour(), time.minute());
       return str;
    }*/
   }
   if (includeSeconds) { return time.toString("h:mm:ss ap"); }
   return time.toString("h:mm ap");
}

QDateTime OperationContext::timeNow(bool includeSeconds)
{
   QDateTime now = companyConfig().timeZone.timeNow();

   if (!includeSeconds) { now = now.addSecs(-now.time().second()); }
   return now;
}

int OperationContext::saveVerificationSpecTemplates()
{
   int bioType = -1;

   if (!verificationSpec()) { return -1; }
   if (!verificationSpec()->hasTemplates) { return 0; }
   employeeInfo().recordId = verificationSpec()->individualRecordId; //FIX this will only be set if a verification spec is sent
   if (!verificationSpec()->individualRecordId) { return -2; }

   bioType = verificationSpec()->specType();
   if (bioType != RDT_COGENTFP && bioType != RDT_DIGITALPERSONA) { return -3; }

   FPTemplates templates;
   QList<int> savedIndexes;
   if (templates.loadTemplates(companyId(), bioType, verificationSpec()->individualRecordId, true))
   {
      for (FPTemplate *t = verificationSpec()->templates.first(); t; t = t->next)
      {
         FPTemplate *found = NULL;
         for (FPTemplate *t2 = templates.first(); t2 && !found; t2 = t2->next)
            if (t2->fingerIndex() == t->fingerIndex() && t2->md5() == t->md5())
            {
               qDebug() << "Index " << t2->fingerIndex() << "matches print in file system";
               found = t2;
            }

         if (found) { continue; }

         t->saveTemplate(QString("%1/%2.dat").arg(FilenameHelper::bioEmployeeDirectory(companyId(), bioType, verificationSpec()->individualRecordId)).arg(t->fingerIndex()).toLocal8Bit().data());
         savedIndexes.append(t->fingerIndex());
      }
   }
   else{ qDebug() << "ERROR: Templates could not be loaded from file system"; }

   if (savedIndexes.count())
   {
// Remove templates that were not passed in the verification spec
      for (int q = 1; q <= 5; q++)
         if (!savedIndexes.contains(q))
         {
            QString fn = QString("%1/%2.dat").arg(FilenameHelper::bioEmployeeDirectory(companyId(), bioType, verificationSpec()->individualRecordId)).arg(q);
            QFile::remove(fn);
            qDebug() << "Removing print " << fn << "that was not in the verification spec";
         }
   }

   return savedIndexes.count();
}

bool OperationContext::isBiometricsEnabled()
{
   if (!biometrics) { return false; }

   if (companyConfig().cogentConfig.enabled && biometrics == RDT_COGENTFP) { return true; }
   if (companyConfig().digitalPersonaConfig.enabled && biometrics == RDT_DIGITALPERSONA) { return true; }

   return false;
}

bool OperationContext::captureImage()
{
   remove("/tmp/photo.jpg");

   if (!camera.isReady()) { return false; }

   if (!companyConfig().takePhoto) { return true; }

   uint8_t *image = NULL;
   int imageSize = 0;

   if (companyConfig().useFlash)
   {
    // use flash
   }

   if (!database().isOnline()) { return true; }

   if (camera.captureImage(&image, imageSize))
   {
        // resize image
      delete [] image;
      return true;
   }
   return false;
}


void OperationContext::setBreakOnClockOut(BreakOnClockOutInfo *bInfo)
{
   delete this->_breakOnClockOutInfo;
   _breakOnClockOutInfo = bInfo;
}

BreakOnClockOutInfo *  OperationContext::breakOnClockOutInfo()
{
   return _breakOnClockOutInfo;
}

bool OperationContext::loadStringFromObject(QString storeName, QJsonObject& obj, QString subObject, const char *field)
{
   qDebug() << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++";
   qDebug() << "Loading" << field << "from" << subObject;

   QJsonValue val = obj[subObject];
   if (val.isObject())
   {
      QJsonObject obj = val.toObject();
      JsonReader rdr(obj);
      if (rdr.hasField(field))
      {
         language[storeName] = rdr.readString(field);
         return true;
      }
   }
   else{ qDebug() << "subObject is not an object"; }

   return false;
}

bool OperationContext::loadStringsFromObject(QJsonValue value)
{

   if (!value.isObject())
   {
      qDebug() << "ERROR: loadStringsFromObject was passed a value that is not an object";
      return false;
   }

   QJsonObject obj = value.toObject();
   return loadStringsFromObject(obj);
}

bool OperationContext::loadStringsFromObject(QJsonObject& obj)
{
   int count = language.count();
   int keyCount = obj.keys().count();

   qDebug() << "Loading " << keyCount << "keys.";

   for (int q = 0; q < keyCount; q++)
   {
      QString key = obj.keys().at(q);
      if (key.startsWith("Str"))
      {
         if (key.startsWith("StrCompanyTimestamp")) { continue; }
         if (key.startsWith("StrMenuCommand")) { continue; }

         QJsonValue val = obj[key];
         if (val.isString()) { addLanguageKey(key, val.toString()); }
      }
   }

   qDebug() << language.count() - count << "language strings loaded for a total of " << language.count();

   return true;
}

void OperationContext::addLanguageKey(QString key, QString value)
{
   if (key.startsWith("Str")) { key = key.mid(3, key.length() - 3); }

   value = value.trimmed();

   if (value.length())
   {
      if (language.contains(key) && language.value(key) != value)
      {
         logger.addTroubleLog("Key %s already exists as '%s' replaced by '%s'", key.toLatin1().data(), language.value(key).toLatin1().data(), value.toLatin1().data());
      }
      language[key] = value;
   }
   else{ language.remove(key); }

   qDebug() << "Adding" << key << "as" << value;
}

QString OperationContext::getPrompt(QString key, QString defaultText)
{
   if (language.contains(key))
   {
      if (debugLanguage) { return "[" + language.value(key) + "]"; }
      return language.value(key);
   }
   if (debugLanguage) { return "{" + defaultText + "}"; }
   return defaultText;
}
