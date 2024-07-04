#ifndef DIGITALOUTTIMER_H
#define DIGITALOUTTIMER_H

#include <QtCore>

class DigitalOutTimer
{
 public:
  DigitalOutTimer();

  bool fromJson(QJsonObject& json);

  int days;
  int time;
  int duration;
  int index;
};

#endif
