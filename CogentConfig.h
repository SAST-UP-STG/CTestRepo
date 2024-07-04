#ifndef COGENT_CONFIG_H
#define COGENT_CONFIG_H

#include <QtCore>
#include "ModuleConfigBase.h"

class CogentConfig: public ModuleConfigBase
{
 public:
  CogentConfig();

  void reset();


  // Constants
  int   enrollTimeout;

  // From Server
 
  bool  allowAnyOperationIfNoPrintOnFile;
  bool  allowDeleteAll;
  int   failBeep;
  bool  setEntryTypeToBioAfterVerify;
  int   successBeep;
  bool  verifyDisplayPrintAccepted;
  int   verifyTimeout;
};

#endif