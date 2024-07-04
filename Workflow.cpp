#include "Workflow.h"
#include "OperationContext.h"
#include "JsonReader.h"
#include "Macros.h"
#include "CostCodeItem.h"
#include "MissedPunchItem.h"
#include "GatherMissedTime.h"
#include "CoveredEmployeeItem.h"
#include "BreakOnClockOutInfo.h"
#include "CostCodeOptionInfo.h"
#include "Externs.h"

#include <unistd.h>

Workflow::Workflow()
{

}

Workflow::~Workflow()
{
}

void Workflow::initialize()
{
}


bool Workflow::parseStep(OperationContext& context, QJsonObject& obj)
{
   JsonReader rdr(obj);

   if (!rdr.hasField("StrWorkflowStepCommand"))
   {
      return false; // The json does not contain the proper fields
   }

   shouldFinishWorkflow = rdr.readBool("BlnShouldFinishWorkflow");
   workflowStepCommand = rdr.readString("StrWorkflowStepCommand");
   workflowTitle = rdr.readString("StrTitle");
   context.clockStatus = rdr.readString("StrClockStatus");
   if ((context.isOnBreak = rdr.readBool("BlnIsOnBreak")))
   {
      if (rdr.hasField("IntBreakLengthSeconds"))
      {
         context.breakStartDateTime = context.timeNow(true).addSecs(-rdr.readInt("IntBreakLengthSeconds"));
      }
      else
      {
         context.breakStartDateTime = rdr.readDateTimeFull("StrBreakStartDateTime");
      }
   }


   qDebug() << "The Next Step is " << workflowStepCommand << context.action();
   qDebug() << "The Title is " << workflowTitle << context.action();

   if (workflowStepCommand.compare(WORKFLOW_CONFIRMATION) == 0) { return parseConfirmation(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERJOB) == 0) { return parseGatherJob(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERCOST) == 0) { return parseGatherCost(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERTRACKED) == 0) { return parseGatherTracked(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERMISSEDCONFIRMATION) == 0) { return parseGatherMissedPunchConfirmation(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERMISSEDSUMMARYCONFIRMATION) == 0) { return parseGatherMissedPunchSummaryConfirmation(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERMISSEDIN) == 0) { return parseGatherMissedIn(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERMISSEDOUT) == 0) { return parseGatherMissedOut(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHEROVERRIDE) == 0) { return parseGatherRestrictionOverride(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_PRESENTMESSAGES) == 0) { return parsePresentEmployeeMessages(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERCOVEREDEMPLOYEE) == 0) { return parseGatherCoveredEmployee(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERQUESTIONONCLOCKOUT) == 0) { return parseGatherQuestionOnClockOut(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERQUESTIONONCLOCKOUTACK) == 0) { return parseGatherQuestionOnClockOutAck(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERBREAKONCLOCKOUT) == 0) { return parseGatherBreakOnClockOut(context, rdr); }
   if (workflowStepCommand.compare(WORKFLOW_GATHERCOSTCODEOPTIONSELECTION) == 0) { return parseGatherCostCodeOptionSelection(context, rdr); }
   if (workflowStepCommand.length() == 0 || shouldFinishWorkflow) { return finishWorkflow(context); }

   qDebug() << workflowStepCommand << "not recognized";

   // This only happens with a command we don't recognize.

   return false;
}

bool Workflow::finishWorkflow(OperationContext& context)
{
   qDebug() << "DIGITAL OUTPUT" << context.companyConfig().digitalOutConfig.enabled;
   logger.addDigitalOut("Digital output enabled = %d  action = %d  online = true  id = %ld",
                        context.companyConfig().digitalOutConfig.enabled,
                        (int)context.action(),
                        context.employeeInfo().employeeId);
   if (context.companyConfig().digitalOutConfig.enabled)
   {
      qDebug() << "Action = " << context.action();
      int trigger1 = context.companyConfig().digitalOutConfig.triggerSecondsForAction1(context.action());
      int trigger2 = context.companyConfig().digitalOutConfig.triggerSecondsForAction2(context.action());

      logger.addDigitalOut("Trigger 1 = %d  Trigger 2 = %d", trigger1, trigger2);

        // digital output stuff

      if (trigger1 || trigger2) { context.database().submitDigitalOutputLog(); }
   }
   return true;
}

bool Workflow::parseSettings(OperationContext& context, QJsonObject& obj)
{
   JsonReader rdr(obj);

   context.employeeInfo().name = rdr.readString("StrEmployeeFullName");

   context.shouldShowNote = rdr.readBool("BlnShouldShowNote");
   context.shouldRequireNote = rdr.readBool("BlnShouldRequireNote");
   context.noteMaxLength = rdr.readInt("IntNoteMaxLength", 100);
   return true;
}

bool Workflow::parseConfirmation(OperationContext& context, JsonReader& rdr)
{
   return true;
}

bool Workflow::parseGatherJob(OperationContext& context, JsonReader& r)
{
   QJsonObject obj = r.getField("ObjGatherJobCodeData").toObject();
   JobCodes *jobs = new JobCodes();

   JsonReader rdr(obj);

   jobs->defaultRecordId = rdr.readInt("IntJobCodeRecordId");

   QJsonObject filter = rdr.getField("ObjFilterData").toObject();
   jobs->paging.loadFromJson(filter);

   QJsonArray a;
   if (!rdr.jsonArray("ArrEmployeeJobCodes", a))
   {
      return false;
   }

   for (int q = 0; q < a.count(); q++)
   {
      QJsonObject o = a.at(q).toObject();
      JobCodeItem *j = JobCodeItem::fromJson(o);
      j->isDefault = (j->recordId == jobs->defaultRecordId);
      jobs->jobs.append(j);
   }


   context.setJobCodes(jobs);

   return true;






   if (jobs) { context.setJobCodes(jobs); }
   return jobs != NULL;
}

bool Workflow::parseGatherCost(OperationContext& context, JsonReader &rdr)
{
   QJsonArray a;

   context.setCostCodes(NULL);

   QJsonValue v = rdr.getField("ObjGatherCostCodeData");
   if (!v.isObject()) { return false; }

   QJsonObject objCost = v.toObject();
   JsonReader r(objCost);

   CostCodeList *list = new CostCodeList;
   if (!list->fromJson(r)) { delete list; list = NULL; }
   context.setCostCodes(list);
   return list != NULL;
}

bool Workflow::parseGatherTracked(OperationContext& context, JsonReader& rdr)
{
   QJsonValue v = rdr.getField("ObjTrackedFieldContext");

   if (!v.isObject()) { return false; }

   QJsonObject o = v.toObject();
   JsonReader r(o);

   TrackedInfo *trackedInfo = new TrackedInfo();

   for (int q = 0; q < 3; q++)
   {
      QString field = QString("ObjTextInputTrack%1").arg(q + 1);
      v = r.getField(field);
      if (v.isObject())
      {
         QJsonObject obj = v.toObject();
         JsonReader r2(obj);
         trackedInfo->trackedName[q] = r2.readString("StrText");
         trackedInfo->isDisabled[q] = r2.readBool("BlnIsDisabled");

         QString sample = r2.readString("StrMaxDecimalValue");
         int index = sample.indexOf('.');
         if (index >= 0) { trackedInfo->decimals[q] = sample.length() - index - 1; }
         else{ trackedInfo->decimals[q] = 0; }
         trackedInfo->value[q] = r2.readString("StrValue");

         bool allZero = true;
         for (int z = 0; z < trackedInfo->value[q].length(); z++)
            if (trackedInfo->value[q].at(z) != '0' && trackedInfo->value[q].at(z) != '.')
            {
               allZero = false;
            }

         if (allZero) { trackedInfo->value[q] = ""; }
      }
      else
      {
         trackedInfo->isDisabled[q] = true;
         trackedInfo->trackedName[q] = "?";
         trackedInfo->decimals[q] = 0;
      }
   }

   context.setTrackedInfo(trackedInfo);
   return true;
}

bool Workflow::parseGatherMissedPunchConfirmation(OperationContext& context, JsonReader& rdr)
{
   ConfirmMissedInfo *item = new ConfirmMissedInfo;

//item->canRevert = rdr.readBool("BlnCanRevert");
//item->isOnBreak = rdr.readBool("BlnIsOnBreak");
//item->shouldHighlightTitle = rdr.readBool("BlnShouldHighlightTitle");
//item->breakStartDateTime = rdr.readString("StrBreakStartDateTime");
//item->clockStatus = rdr.readString("StrClockStatus");
   item->missedPunchConfirmationHelp = rdr.readString("StrMissedPunchConfirmationHelp");
   item->missedPunchConfirmationMessage = rdr.readString("StrMissedPunchConfirmationMessage");
   context.setConfirmMissedInfo(item);
   return true;
}

bool Workflow::parseGatherMissedPunchSummaryConfirmation(OperationContext& context, JsonReader& rdr)
{
   ConfirmMissedSummaryInfo *item = new ConfirmMissedSummaryInfo();

//item->canRevert = rdr.readBool("BlnCanRevert");
//item->isOnBreak = rdr.readBool("BlnIsOnBreak");
//item->shouldHighlightTitle = rdr.readBool("BlnShouldHighlightTitle");
//item->breakStartDateTime = rdr.readString("StrBreakStartDateTime");
//item->clockStatus = rdr.readString("StrClockStatus");
   item->formattedMissedDateTimeIn = rdr.readString("StrFormattedMissedDateTimeIn");
   item->formattedMissedDateTimeOut = rdr.readString("StrFormattedMissedDateTimeOut");


   if (rdr.hasField("ObjGatherJobCodeData"))
   {
      QJsonValue f = rdr.getField("ObjGatherJobCodeData");
      if (f.isObject())
      {
         QJsonObject o = f.toObject();
         JsonReader rf(o);
         item->jobCodeDescription = rf.readString("StrJobCodeDescription");
      }
   }

   else{ item->jobCodeDescription = rdr.readString("StrJobCodeDescription"); }
   item->missedPunchSummaryHelp = rdr.readString("StrMissedPunchSummaryHelp");
   context.setConfirmMissedSummaryInfo(item);

   qDebug() << "PARSING MISSED PUNCH SUMMARY INFORMATION";
   return true;
}

bool Workflow::parseGatherMissedIn(OperationContext& context, JsonReader& rdr)
{
   GatherMissedTimeInfo *item = new GatherMissedTimeInfo();

   item->canEditMissedIn = rdr.readBool("BlnCanEditMissedIn");
   item->canEditMissedOut = rdr.readBool("BlnCanEditMissedOut");
//item->canRevert = rdr.readBool("BlnCanRevert");
//item->isOnBreak = rdr.readBool("BlnIsOnBreak");
//item->shouldHighlightTitle = rdr.readBool("BlnShouldHighlightTitle");
   item->missedDateIn = rdr.readDate("DatMissedDateIn");
   item->missedDateOut = rdr.readDate("DatMissedDateOut");
//item->breakStartDateTime = rdr.readString("StrBreakStartDateTime");
//item->clockStatus = rdr.readString("StrClockStatus");
   item->missedPunchConfirmationHelp = rdr.readString("StrMissedPunchConfirmationHelp");
   item->missedPunchConfirmationMessage = rdr.readString("StrMissedPunchConfirmationMessage");
//item->title = rdr.readString("StrTitle");
//item->workflowStepCommand = rdr.readString("StrWorkflowStepCommand");
   item->missedTimeIn = rdr.readTime("TimMissedTimeIn");
   item->missedTimeOut = rdr.readTime("TimMissedTimeOut");

   context.setMissedTimeInfo(item);

   return true;
}

bool Workflow::parseGatherMissedOut(OperationContext& context, JsonReader& rdr)
{
   return parseGatherMissedIn(context, rdr);
}

bool Workflow::parseGatherRestrictionOverride(OperationContext& context, JsonReader& rdr)
{
   OverrideInfo *info = new OverrideInfo();

   context.setOverrideInfo(info);

   QJsonArray array;
   if (rdr.jsonArray("ArrOverrides", array))
   {
      for (int q = 0; q < array.count(); q++) info->overrides.append(array.at(q).toString());
   }


   QString field = isDBorLater(7, 0, 47, 0) ? "ArrSelectItemUsers" : "ArrUsers";

   if (rdr.jsonArray(field, array))
   {
      for (int q = 0; q < array.count(); q++)
      {
         QJsonObject obj = array.at(q).toObject();
         JsonReader r(obj);

         User *user = new User();
         user->userId = r.readString("_StrText");
         user->userName = r.readString("_StrSubText");
         user->uid = r.readInt("_IntValue");

         info->users.append(user);
      }
   }

   return true;
}

bool Workflow::parsePresentEmployeeMessages(OperationContext& context, JsonReader& rdr)
{
   QJsonObject obj = rdr.getField("ObjViewMessagesData").toObject();
   JsonReader r2(obj);

   EmployeeMessages *messages = new EmployeeMessages();

   QJsonArray array;

   if (r2.jsonArray("ArrEmployeeMessages", array))
   {
      for (int q = 0; q < array.count(); q++)
      {
         QJsonObject o2 = array.at(q).toObject();
         EmployeeMessageDetail *item = EmployeeMessageDetail::parseJson(o2);
         if (item) { messages->messages.append(item); }
      }
      context.setMessages(messages);
      return true;
   }
   delete messages;
   return false;
}

bool Workflow::parseGatherCoveredEmployee(OperationContext& context, JsonReader& rdr)
{
   QJsonObject obj = rdr.getField("ObjSelectCoveredEmployeeData").toObject();

   CoveredEmployees *item = new CoveredEmployees;

   if (item->parseJson(obj))
   {
      context.setCoveredEmployees(item);
      return true;
   }
   delete item;

   return false;
}

bool Workflow::parseGatherQuestionOnClockOut(OperationContext& context, JsonReader& rdr)
{
   context.clockOutQuestion = rdr.readString("StrQuestionOnClockOut");
   return true;
}

bool Workflow::parseGatherQuestionOnClockOutAck(OperationContext& context, JsonReader& rdr)
{
   context.clockOutQuestionAcknowledgement = rdr.readString("StrQuestionOnClockOutAcknowledgement");
   return true;
}

bool Workflow::parseGatherBreakOnClockOut(OperationContext& context, JsonReader& rdr)
{
   QJsonValue val = rdr.getField("ObjGatherBreakOnClockOutContext");

   if (val.isObject())
   {
      QJsonObject o = val.toObject();
      JsonReader rdr(o);
      context.loadStringsFromObject(rdr.getField(RDT_LANG_KEY));

      context.loadStringsFromObject(o);
      context.loadStringFromObject("BCOStartTime", o, "ObjTimeInputStartTime", "StrText");
      context.loadStringFromObject("BCOEndTime", o, "ObjTimeInputStopTime", "StrText");
      context.loadStringFromObject("BCOClockIn", o, "ObjTextInputClockIn", "StrText");
      context.loadStringFromObject("BCOClockOut", o, "ObjTextInputClockOut", "StrText");

      BreakOnClockOutInfo *breakInfo = new BreakOnClockOutInfo();
      if (breakInfo->parse(o))
      {
         context.setBreakOnClockOut(breakInfo);
         return true;
      }
      delete breakInfo;
   }
   return false;
}

bool Workflow::parseGatherCostCodeOptionSelection(OperationContext& context, JsonReader& rdr)
{
   QJsonValue val = rdr.getField("ObjGatherCostCodeOptionContext");

   if (val.isObject())
   {
      QJsonObject o = val.toObject();
      CostCodeOptionInfo *optionInfo = new CostCodeOptionInfo();
      if (optionInfo->parse(o))
      {
         context.setCostCodeOptionInfo(optionInfo);
         return true;
      }
      delete optionInfo;
   }
   return false;
}
