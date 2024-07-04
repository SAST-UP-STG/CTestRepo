#include "CogentConfig.h"
#include "JsonReader.h"

#include <unistd.h>

CogentConfig::CogentConfig()
{
   reset();
   setValid(true);
}

void CogentConfig::reset()
{
   enrollTimeout = 30;

   allowAnyOperationIfNoPrintOnFile = false;
   allowDeleteAll = false;
   enabled = false;
   failBeep = 0;
   successBeep = 0;
   verifyDisplayPrintAccepted = false;
   verifyTimeout = 30;
   setEntryTypeToBioAfterVerify = true;
}