#include "DigitalOutTimer.h"
#include "JsonReader.h"

DigitalOutTimer::DigitalOutTimer()
{
   days = time = duration = index = 0;
}

bool DigitalOutTimer::fromJson(QJsonObject& json)
{
   JsonReader r(json);

   days = r.readInt("Days");
   duration = r.readInt("Duration");
   index = r.readInt("Index");
   time = r.readInt("Time");
   return true;
}
