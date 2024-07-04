#include "ContextBase.h"

ContextBase::ContextBase() : baseUrl(gc.serverUrl), companyNamespace(gc.companyNamespace)
{
   _terminalId = 0;
   _companyId = 0;
   _companyName = QString("");
}

ContextBase::~ContextBase()
{
}

void ContextBase::init(int companyId, QString companyName, int terminalId)
{
   _companyId = companyId;
   _companyName = companyName;
   _terminalId = terminalId;
}




