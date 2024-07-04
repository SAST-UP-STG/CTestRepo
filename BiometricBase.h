#ifndef BIOMETRICBASE_H
#define BIOMETRICBASE_H

#include <stdint.h>
#include <QByteArray>

#define FPTEMPLATETYPE_DP       1
#define FPTEMPLATETYPE_COGENT   2

class CancelationToken
{
 public:
  CancelationToken() { abort = false; }

  inline bool shouldAbort() { return abort; }
  inline void setAbort(bool a = true) { abort = a; }

 private:
  bool abort;
};


class FPTemplate
{
 public: 
  FPTemplate();
  FPTemplate(int fingerIndex);
  virtual ~FPTemplate();

  void reset();
  bool isValid();

  FPTemplate *createCopy();

  bool initWithData(int index, uint8_t *data, uint16_t size);
  bool initWithData(int index, QByteArray& data);
  bool initWithData(const QString& data);
  
  inline int templateType() { return _templateType; }
  inline uint8_t *data() { return templateData; }
  inline uint16_t size() { return templateSize; }
  int fingerIndex() { return _fingerIndex; }
  void setFingerIndex(int index) { _fingerIndex = index; }

  bool copyFrom(FPTemplate *source);
 
  bool saveTemplate(const char *fileName);
  bool loadTemplate(const char *fileName);

  QString toString();

  QString md5();

  FPTemplate *next;

 protected:
  uint16_t templateSize;
  uint8_t *templateData;
  int _templateType;
  int _fingerIndex;
};


class FPTemplates
{
 public:
  FPTemplates();
  virtual ~FPTemplates();

  void copyFrom(FPTemplates& source);
  bool addTemplate(FPTemplate *tmp);
  void reset();
  FPTemplate *findByIndex(int fingerIndex);
  QString md5(int index);
  int fingerIndexAt(int index);
  inline FPTemplate *first() { return copies; }
  bool loadTemplates(int company, int bioType, int id, bool isEmployee);
  static int countTemplates(int company, int bioType, int id, bool isEmployee);

  int count();

 protected:
  FPTemplate *copies;
};

#endif
