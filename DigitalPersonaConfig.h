#ifndef DP_CONFIG_H
#define DP_CONFIG_H

#include <QtCore>
#include "ModuleConfigBase.h"

class DigitalPersonaConfig: public ModuleConfigBase
{
 public:
  DigitalPersonaConfig();

  void reset();

  // Constants
  int   enrollTimeout;

  // From Server
 
  bool  allowAnyOperationIfNoPrintOnFile;
  bool  allowDeleteAll;
  int   failBeep;
  int   failLED;
  bool  setEntryTypeToBioAfterVerify;
  int   successBeep;
  int   successLED;
  bool  verifyDisplayPrintAccepted;
  int   verifyTimeout;
};

#endif
