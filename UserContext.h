#ifndef USERCONTEXT_H
#define USERCONTEXT_H

#include <QtCore>
#include "ContextBase.h"
#include "CompanyConfig.h"
#include "ModuleConfigBase.h"
#include "UserStore.h"
#include "VerificationSpec.h"


class UserContext: public ContextBase
{
  public:
  UserContext(int companyId, QString companyName);
  virtual ~UserContext();

  bool                      canAssignBadge;

  inline UserStore&         database() { return *_store; }
  inline int                formTimeout() { return 60; }

  inline CompanyConfig *    companyConfig() { return _companyConfig; }
  inline void               setCompanyConfig(CompanyConfig *config) { delete _companyConfig; _companyConfig = config; }

  inline VerificationSpec * verificationSpec() { return _verificationSpec; }
  inline void               setVerificationSpec(VerificationSpec* spec) { delete _verificationSpec; _verificationSpec = spec; }

  ModuleConfigBase *        moduleConfig(int moduleId);
  bool                      isEnabled(int bioType);

  bool                      deleteCompanyConfig;

 private:
  UserStore *               _store;
  CompanyConfig *           _companyConfig;
  VerificationSpec *       _verificationSpec;
};

#endif