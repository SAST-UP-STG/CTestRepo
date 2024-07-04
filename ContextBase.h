#ifndef CONTEXTBASE_H
#define CONTEXTBASE_H

#include "CurlRequest.h"
#include "GlobalConfig.h"
#include "GenericException.h"

extern GlobalConfig gc;

class ContextBase
{
 public:
  ContextBase();
  virtual ~ContextBase();
 
  inline CurlRequest& getRequest() { return request; }
  void init(int companyId, QString companyName, int terminalId);

  virtual int companyId() { return _companyId; }
  virtual QString companyName() { return _companyName; }
  virtual int terminalId() { return _terminalId; }

  inline void setTerminalId(int terminalId) { _terminalId = terminalId; }
  inline void setCompanyId(int companyId) { _companyId = companyId; }
  inline void setCompanyName(QString companyName) { _companyName = companyName; }

  QString             baseUrl;
  QString             companyNamespace;
  QString             sessionId;
  GenericException    exception;
  CurlRequestHeaders  headers;

 private:
  CurlRequest         request;
  int                 _terminalId;
  int                 _companyId;
  QString             _companyName;
  
};

#endif
