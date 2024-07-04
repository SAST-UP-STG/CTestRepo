#include "DigitalOutConfig.h"
#include "JsonReader.h"

DigitalOutConfig::DigitalOutConfig()
{
   reset();
   setValid(true);

}

int DigitalOutConfig::triggerSecondsForAction1(ClockAction action)
{
   int a = (int)action;

   if (a >= 0 && a < 10) { return trigger1[a]; }

   return 0;
}

int DigitalOutConfig::triggerSecondsForAction2(ClockAction action)
{
   int a = (int)action;

   if (a >= 0 && a < 10) { return trigger2[a]; }

   return 0;
}

void DigitalOutConfig::reset()
{
   enabled = false;
   fallbackPerformOperationTriggers = false;
   quickPunchAccessOnly = false;
   quickPunchDurationSeconds1 = 0;
   quickPunchDurationSeconds2 = 0;
   quickPunchFunctionKey = 0;


   memset(trigger1, 0, sizeof(trigger1));
   memset(trigger2, 0, sizeof(trigger1));
}
