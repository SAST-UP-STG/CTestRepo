#ifndef GATHERMISSEDTIME_H
#define GATHERMISSEDTIME_H


#include "OperationContext.h"


class GatherMissedTime
{
 Q_OBJECT 

 public:
  GatherMissedTime(OperationContext& context, bool gatherTimeIn, QWidget *parent = 0);
  virtual ~GatherMissedTime();
};

#endif