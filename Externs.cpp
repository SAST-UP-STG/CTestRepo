#include "Externs.h"

// Mock Properties
int biometrics = 0;
QString bioVersion = QString("");
BoardConfig boardConfig;
SingleImage camera;
int databaseVersion[4] = { 0, 0, 0, 0 };
bool debugLogging = false;
QString firmwareVersion = "7.0.15.12";
GlobalConfig gc;
bool isDMINetwork = false;
bool isWifi = false;
QString slaveVersion = "Unknown";
TimeZoneInfo timeZone;
bool wantReboot = false;

bool isDBorLater(int v1, int v2, int v3, int v4)
{
   int lv[4] = { v1, v2, v3, v4 };


   for (int q = 0; q < 4; q++)
   {
      if (databaseVersion[q] > lv[q]) { return true; }
      if (databaseVersion[q] < lv[q]) { return false; }
   }

   return true;
}
