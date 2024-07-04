#ifndef BREAKONCLOCKOUTINFO_H
#define BREAKONCLOCKOUTINFO_H

#include <QtCore>

class BreakOnClockOutListItem
{
 public:
  BreakOnClockOutListItem(int id, QString name) { itemId = id; itemName = name; }

  int itemId;
  QString itemName;
};


class BreakOnClockOutInfo
{
 public:
  BreakOnClockOutInfo() ;
  virtual ~BreakOnClockOutInfo() { qDeleteAll(breakTypes); qDeleteAll(breakDates); }

  bool parse(QJsonObject& obj);

  bool recordBreak;
  bool enterMinutes;

  bool enterBreak;
  bool requireBreak;
  bool confirmBreak;

  QDate dateIn,dateOut;
  QTime timeIn,timeOut;

  // Prompt For Break;
 
  bool promptForBreak;
  QString promptForBreakText;

  // Select Break

  bool selectBreakDisabled;
  int  selectBreakValue;
  QList<BreakOnClockOutListItem*> breakTypes;

  // Select Date
  int selectDateValue;
  QList<BreakOnClockOutListItem*> breakDates;

  QTime breakStart;
  QTime breakEnd;

  int breakLength;
  int breakLengthMin;
  int breakLengthMax;
};


#endif