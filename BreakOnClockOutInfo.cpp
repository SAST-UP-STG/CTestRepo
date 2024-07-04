#include "BreakOnClockOutInfo.h"
#include "JsonReader.h"


BreakOnClockOutInfo::BreakOnClockOutInfo()
{
   recordBreak = false;
}

bool BreakOnClockOutInfo::parse(QJsonObject& obj)
{
   JsonReader rdr(obj);

   enterBreak = rdr.readBool("BlnEnterBreak");
   requireBreak = rdr.readBool("BlnRequireBreak");
   dateIn = rdr.readDate("DatDateIn");
   dateOut = rdr.readDate("DatDateOut");
   timeIn = rdr.readTime("TimTimeIn");
   timeOut = rdr.readTime("TimTimeOut");

   if (rdr.hasField("ObjBooleanInputPromptForBreak"))
   {
      QJsonObject o1 = rdr.getField("ObjBooleanInputPromptForBreak").toObject();
      JsonReader r2(o1);

      promptForBreak = !r2.readBool("BlnIsDisabled") && r2.readBool("BlnIsVisible");
      promptForBreakText = r2.readString("StrText");
   }
   else{ promptForBreak = false; }

   if (rdr.hasField("ObjSelectInputBreakType"))
   {
      QJsonObject o = rdr.getField("ObjSelectInputBreakType").toObject();
      JsonReader r(o);

      selectBreakDisabled = r.readBool("BlnIsDisabled");
      selectBreakValue = r.readInt("IntValue");

      QJsonArray array;
      if (r.jsonArray("ArrSelectItemOptions", array))
      {
         for (int q = 0; q < array.count(); q++)
         {
            QJsonObject o2 = array.at(q).toObject();
            JsonReader r2(o2);
            breakTypes.append(new BreakOnClockOutListItem(r2.readInt("_IntValue"), r2.readString("_StrText")));
         }
      }
   }
   else{ return false; }

   QJsonObject od = rdr.getField("ObjSelectInputDate").toObject();
   JsonReader rd(od);

   selectDateValue = rd.readInt("IntValue");
   QJsonArray dateArray;
   if (rd.jsonArray("ArrSelectItemOptions", dateArray))
   {
      for (int q = 0; q < dateArray.count(); q++)
      {
         QJsonObject obj = dateArray.at(q).toObject();
         JsonReader dateRdr(obj);
         breakDates.append(new BreakOnClockOutListItem(dateRdr.readInt("_IntValue"), dateRdr.readString("_StrText")));
      }
   }
   else{ return false; }

   QJsonObject bs = rdr.getField("ObjTimeInputStartTime").toObject();
   JsonReader bsr(bs);
   breakStart = bsr.readTime("TimValue");

   if (rdr.hasField("ObjTimeInputStopTime"))
   {
      QJsonObject be = rdr.getField("ObjTimeInputStopTime").toObject();
      JsonReader ber(be);
      breakEnd = ber.readTime("TimValue");
      enterMinutes = false;
   }

   if (rdr.hasField("ObjHourMinuteInputBreakLength"))
   {
      QJsonObject bl = rdr.getField("ObjHourMinuteInputBreakLength").toObject();
      JsonReader r(bl);

      breakLength = r.readDuration("HrmValue", 0);
      breakLengthMin = r.readInt("IntMinMinutes");
      breakLengthMax = r.readInt("IntMaxMinutes");
      enterMinutes = true;
   }

   confirmBreak = rdr.hasField("ObjBooleanInputConfirmBreak");

   return true;
}
