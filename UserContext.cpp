#include "UserContext.h"
#include "70Defines.h"


UserContext::UserContext(int companyId, QString companyName)
{
   _store = new UserStore(*this);
   _companyConfig = NULL;
   _verificationSpec = NULL;
   deleteCompanyConfig = true;
   canAssignBadge = false;

   init(companyId, companyName, 0);
}

UserContext::~UserContext()
{
   if (deleteCompanyConfig) { delete _companyConfig; }
   delete _store;
   delete _verificationSpec;
}

ModuleConfigBase *UserContext::moduleConfig(int module)
{
   if (!companyConfig()) { return NULL; }
   return NULL;

}

bool UserContext::isEnabled(int bioType)
{
   ModuleConfigBase *mc = moduleConfig(bioType);

   return mc && mc->enabled;
}
