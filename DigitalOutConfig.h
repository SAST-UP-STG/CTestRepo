#ifndef DIGITALOUTCONFIG_H
#define DIGITALOUTCONFIG_H

#include <QtCore>
#include "ModuleConfigBase.h"
#include "ClockOperationDefines.h"

class DigitalOutConfig: public ModuleConfigBase
{
 public:
  DigitalOutConfig();

  void    reset();
  int     triggerSecondsForAction1(ClockAction action);
  int     triggerSecondsForAction2(ClockAction action);

  bool fallbackPerformOperationTriggers;
  bool quickPunchAccessOnly;
  int  quickPunchDurationSeconds1;
  int  quickPunchDurationSeconds2;
  int quickPunchFunctionKey;

  int trigger1[20];
  int trigger2[20];
};

#endif