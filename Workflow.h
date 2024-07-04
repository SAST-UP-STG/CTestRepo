#ifndef WORKFLOW_H
#define WORKFLOW_H

#include <QtCore>

class OperationContext;
class JsonReader;
 
#define WORKFLOW_CONFIRMATION                    "GatherEmployeeConfirmation"
#define WORKFLOW_GATHERJOB                       "GatherJobCode"
#define WORKFLOW_GATHERCOST                      "GatherCostCode"
#define WORKFLOW_GATHERTRACKED                   "GatherTrackedValues"
#define WORKFLOW_GATHERMISSEDCONFIRMATION        "GatherMissedPunchConfirmation"
#define WORKFLOW_GATHERMISSEDSUMMARYCONFIRMATION "GatherMissedPunchSummaryConfirmation"
#define WORKFLOW_GATHERMISSEDIN                  "GatherMissedIn"
#define WORKFLOW_GATHERMISSEDOUT                 "GatherMissedOut"
#define WORKFLOW_GATHEROVERRIDE                  "GatherRestrictionOverride"
#define WORKFLOW_PRESENTMESSAGES                 "PresentEmployeeMessages"
#define WORKFLOW_GATHERCOVEREDEMPLOYEE           "GatherCoveredEmployee"
#define WORKFLOW_GATHERQUESTIONONCLOCKOUT        "GatherQuestionOnClockOut"
#define WORKFLOW_GATHERQUESTIONONCLOCKOUTACK     "GatherQuestionOnClockOutAcknowledgement"
#define WORKFLOW_GATHERBREAKONCLOCKOUT           "GatherBreakOnClockOut"
#define WORKFLOW_GATHERCOSTCODEOPTIONSELECTION   "GatherCostCodeOptionSelection"

// Offline operations
#define WORKFLOW_GATHERTRACKEDIN                 "GatherTrackedInValues"
#define WORKFLOW_GATHERTRACKEDOUT                "GatherTrackedOutValues"

class Workflow
{
 public:
  Workflow();
  virtual ~Workflow();

  bool parseStep(OperationContext& context, QJsonObject& obj);
  bool parseSettings(OperationContext& context, QJsonObject& obj);
  void initialize();

  QString workflowStepCommand;
  QString workflowTitle;
  bool shouldFinishWorkflow;

 protected:
  bool parseConfirmation(OperationContext& context, JsonReader& rdr);
  bool parseGatherJob(OperationContext& context, JsonReader& rdr);
  bool parseGatherCost(OperationContext &context, JsonReader& rdr);
  bool parseGatherTracked(OperationContext &context, JsonReader& rdr);
  bool parseGatherMissedPunchConfirmation(OperationContext& context, JsonReader& rdr);
  bool parseGatherMissedPunchSummaryConfirmation(OperationContext& context, JsonReader& rdr);
  bool parseGatherMissedIn(OperationContext& context, JsonReader& rdr);
  bool parseGatherMissedOut(OperationContext& context, JsonReader& rdr);
  bool parseGatherRestrictionOverride(OperationContext& context, JsonReader& rdr);
  bool parsePresentEmployeeMessages(OperationContext& context, JsonReader& rdr);
  bool parseGatherCoveredEmployee(OperationContext& contxt, JsonReader& rdr);
  bool parseGatherQuestionOnClockOut(OperationContext& context, JsonReader& rdr);
  bool parseGatherQuestionOnClockOutAck(OperationContext& context, JsonReader& rdr);
  bool parseGatherBreakOnClockOut(OperationContext& context, JsonReader& rdr);
  bool parseGatherCostCodeOptionSelection(OperationContext& context, JsonReader& rdr);

 private:
  bool finishWorkflow(OperationContext& context);
};

#endif
