#include "DigitalPersonaConfig.h"
#include "JsonReader.h"
#include <unistd.h>

DigitalPersonaConfig::DigitalPersonaConfig()
{
   reset();
   setValid(true);
}

void DigitalPersonaConfig::reset()
{

   allowAnyOperationIfNoPrintOnFile = true;
   allowDeleteAll = true;
   enabled = true;
   verifyDisplayPrintAccepted = false;
   setEntryTypeToBioAfterVerify = true;

   failBeep = 0;
   successBeep = 0;
   verifyTimeout = 30;
   enrollTimeout = 30;
}