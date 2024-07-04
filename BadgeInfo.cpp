#include "BadgeInfo.h"

BadgeInfo::BadgeInfo()
{
   readerType = RTNone;
   processed = false;
   isExternal = false;
   memset(rawBadge, 0, sizeof(rawBadge));
   memset(parsedBadge, 0, sizeof(parsedBadge));
}

BadgeParseInformation *BadgeInfo::getRule(QList<BadgeParseInformation*> parseInfo, enum ParseLocation location)
{
   int length = strlen(rawBadge);
   BadgeParseInformation *p;

   qDebug() << "RULE COUNT=" << parseInfo.count();

   for (int x = 0; x < parseInfo.count(); x++)
   {
      p = parseInfo.at(x);
      if (p->location == location && p->readerType == readerType && p->badgeLength == length && isExternal == p->isExternal)
      {
         qDebug() << "Found match with length" << isExternal << p->isExternal;
         return p;
      }
   }
   for (int x = 0; x < parseInfo.count(); x++)
   {
      p = parseInfo.at(x);
      if (p->location == location && p->readerType == readerType && p->badgeLength == 0 && isExternal == p->isExternal)
      {
         qDebug() << "Found match without length" << isExternal << p->isExternal;
         return p;
      }

   }
   return NULL;
}

bool BadgeInfo::parse(QList<BadgeParseInformation*> parseInfo, enum ParseLocation location)
{
   memset(parsedBadge, 0, sizeof(parsedBadge));

   BadgeParseInformation *pinfo = getRule(parseInfo, location);

   if (location == PLNone || !pinfo || !pinfo->isValid())
   {
      strcpy(parsedBadge, rawBadge);
      return true;
   }

   strcpy(parsedBadge, rawBadge);
   if (location == PLCostCode && pinfo->costCodeDivider)
   {
      for (unsigned int x = 0; x < strlen(parsedBadge); x++)
         if (parsedBadge[x] == pinfo->costCodeDivider) { parsedBadge[x] = '\\'; }
   }

   if (pinfo->proximityParsing == BPPBefore) { processProxBadge(); }

   if (pinfo->parseType == BPTPartial)
   {

      if (pinfo->partialFrom == 0 || pinfo->partialFrom >= strlen(parsedBadge))
      {
         parsedBadge[0] = 0;
         return false;

      }
      strcpy(parsedBadge, parsedBadge + (pinfo->partialFrom - 1));

      if (strlen(parsedBadge) > pinfo->partialLength) { parsedBadge[pinfo->partialLength] = 0; }
   }
   else if (pinfo->parseType == BPTEnd && pinfo->endLength < strlen(parsedBadge))
   {
      qDebug() << parsedBadge << strlen(parsedBadge) << pinfo->endLength;
      strcpy(parsedBadge, parsedBadge + (strlen(parsedBadge) - pinfo->endLength));
   }

   if (pinfo->proximityParsing == BPPAfter) { processProxBadge(); }

   return strlen(parsedBadge) != 0;
}

void BadgeInfo::processProxBadge()
{
   unsigned long long value = 0;

   for (unsigned int x = 0; x < strlen(parsedBadge); x++)
      if (parsedBadge[x] != '0' && parsedBadge[x] != '1') { return; }
      else
      {
         value *= 2;
         if (parsedBadge[x] == '1') { value++; }
         qDebug() << parsedBadge[x] << value;
      }

   sprintf(parsedBadge, "%llu", value);
}
