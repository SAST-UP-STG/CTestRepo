#ifndef BADGEINFO_H
#define BADGEINFO_H

#include <QtCore>
#include <string.h>
#include <stdint.h>

enum BadgeParseType { BPTNone = 0, BPTPartial = 1, BPTEnd = 2 };
enum BadgeProximityParsing { BPPNone = 0, BPPBefore = 1, BPPAfter = 2 };

enum ParseLocation
{
 PLNone = 0,
 PLEmployee = 1,
 PLJobCode = 2,
 PLCostCode = 3,
 PLTracked = 4,
 PLPassword = 5,
 PLManager = 6
};

enum ReaderType
{
 RTNone =0,
 RTProximity = 1,
 RTMagnetic =2,
 RTOptical = 3,
 RTCCD = 4,
 RTDigitalIn = 5,
};



class BadgeParseInformation
{
 public:
  BadgeParseInformation() {}

  ParseLocation location;
  ReaderType readerType;

  BadgeProximityParsing proximityParsing;
  unsigned int endLength;
  unsigned int partialLength;
  unsigned int partialFrom;
  BadgeParseType parseType;
  uint8_t costCodeDivider;
  int badgeLength;
  bool isExternal;

  bool isValid()
  {
   if (parseType == BPTNone) return true;
   if (parseType == BPTEnd && endLength == 0) return false;
   if (parseType == BPTPartial && (partialFrom == 0 || partialLength == 0)) return false;
   return true;
  }
};

class BadgeInfo
{
 public:
  BadgeInfo();

  BadgeParseInformation * getRule(QList<BadgeParseInformation*> parseInfo, enum ParseLocation location);
  bool                    parse(QList<BadgeParseInformation*> parseInfo, enum ParseLocation location);
  void                    processProxBadge();

  ReaderType   readerType;
  char         rawBadge[256];
  char         parsedBadge[256];
  bool         processed;
  bool         isExternal;
};

#endif
