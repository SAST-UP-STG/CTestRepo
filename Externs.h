#ifndef EXTERNS_H
#define EXTERNS_H

#include "i2c.h"
#include "GlobalConfig.h"
#include "JsonReader.h"
#include "Logger.h"
#include "ModuleConfigBase.h"
#include "SingleImage.h"
#include "TimeZoneInfo.h"

// mock externs
extern int biometrics;
extern QString bioVersion;
extern BoardConfig boardConfig;
extern SingleImage camera;
extern int databaseVersion[4];
extern bool debugLogging;
extern QString firmwareVersion;
extern GlobalConfig gc;
extern bool isDMINetwork;
extern bool isWifi;
extern QString slaveVersion;
extern TimeZoneInfo timeZone;
extern bool wantReboot;

extern bool isDBorLater(int v1, int v2, int v3, int v4);

#endif