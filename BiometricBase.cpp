#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "BiometricBase.h"
#include "FilenameHelper.h"
#include "Crypto.h"

#include <QDebug>

/*****************************************************************************************************************
                                             Biometric Template
*****************************************************************************************************************/
FPTemplate::FPTemplate(int fingerIndex)
{
   templateData = NULL;
   templateSize = 0;
   _fingerIndex = fingerIndex;
   next = NULL;
}

FPTemplate::FPTemplate()
{
   templateData = NULL;
   templateSize = 0;
   _fingerIndex = 0;
   next = NULL;
}

FPTemplate::~FPTemplate()
{
   delete [] templateData;
   printf("CLEARING TEMPLATE DATA\n");
}


bool FPTemplate::isValid()
{
   if (!templateData) { return false; }
   return true;
}

bool FPTemplate::copyFrom(FPTemplate *source)
{
   if (!source->data()) { return false; }

   initWithData(source->fingerIndex(), source->data(), source->size());

//   templateSize = source->size();
//   templateData = new uint8_t[templateSize];
//   memcpy(templateData, source->data(), templateSize);

   return true;
}

QString FPTemplate::toString()
{
   static char values[] = "0123456789ABCDEF";

   if (!templateData || !templateSize) { return ""; }

   QString strData;
   strData.reserve(templateSize * 2);

   for (int q = 0; q < templateSize; q++)
   {
      int v1 = templateData[q] / 16;
      int v2 = templateData[q] % 16;

      strData += values[v1];
      strData += values[v2];
   }
   return strData;
}

bool FPTemplate::initWithData(const QString& data)
{
   if (data.length() % 2 != 0) { return false; }

   uint8_t *result = new uint8_t[data.length() / 2];
   int index = 0;

   for (int q = 0; q < data.length(); )
   {
      int value = 0;
      for (int v = 0; v < 2; v++, q++)
      {
         value *= 16;
         int d = data[q].toCaseFolded().toLatin1();
         if (d >= '0' && d <= '9') { value += (d - '0'); }
         else if (d >= 'a' && d <= 'f')
         {
            value += (10 + (d - 'a'));
         }
      }
      result[index++] = (uint8_t)value;
   }

   initWithData(fingerIndex(), result, data.length() / 2);
   delete [] result;
   return true;
}

bool FPTemplate::initWithData(int index, uint8_t *data, uint16_t size)
{
   reset();
   if (!data || !size) { return false; }

   templateSize = size;
   templateData = new uint8_t[templateSize];
   memcpy(templateData, data, templateSize);
   _fingerIndex = index;
   return true;
}

bool FPTemplate::initWithData(int index, QByteArray& data)
{
   return initWithData(index, (uint8_t*)data.data(), (uint16_t)data.count());
}

FPTemplate *FPTemplate::createCopy()
{
   FPTemplate *t = new FPTemplate();

   t->copyFrom(this);
   return t;
}

bool FPTemplate::saveTemplate(const char *fileName)
{
   if (!isValid()) { return false; }

   FILE *outfile = fopen(fileName, "w");
   if (outfile)
   {
      fwrite(templateData, 1, templateSize, outfile);
      fclose(outfile);
      return true;
   }
   return false;
}

bool FPTemplate::loadTemplate(const char *fileName)
{
   struct stat status;

   reset();
   if (stat(fileName, &status) != 0 || status.st_size > 2000 || status.st_size == 0) { return false; }

   templateSize = status.st_size;
   templateData = new uint8_t[templateSize];

   FILE *infile = fopen(fileName, "rb");
   if (infile)
   {
      fread(templateData, 1, templateSize, infile);
      fclose(infile);
      return true;
   }
   reset();
   return false;
}

void FPTemplate::reset()
{
   delete templateData;
   templateData = NULL;
   templateSize = 0;
}

QString FPTemplate::md5() // Not thread safe
{
   if (templateData && templateSize)
   {
      return Crypto::md5(templateData, templateSize);
   }
   return "";
}

/*****************************************************************************************************************
                                                  Biometric Templates
*****************************************************************************************************************/
FPTemplates::FPTemplates()
{
   copies = NULL;
}


FPTemplates::~FPTemplates()
{
   reset();
}

void FPTemplates::reset()
{
   FPTemplate *curr, *next;

   for (curr = copies; curr; curr = next)
   {
      next = curr->next;
      delete curr;
   }
   copies = NULL;
}

FPTemplate *FPTemplates::findByIndex(int fingerIndex)
{
   for (FPTemplate *t = copies; t; t = t->next)
      if (t->fingerIndex() == fingerIndex) { return t; }

   return NULL;
}

bool FPTemplates::addTemplate(FPTemplate *tmp)
{
   if (!tmp->isValid()) { return false; }

   FPTemplate *tmpData = tmp->createCopy();
   tmpData->next = copies;
   copies = tmpData;

   return true;
}

void FPTemplates::copyFrom(FPTemplates& source)
{
   reset();
   for (FPTemplate *t = source.first(); t; t = t->next) addTemplate(t->createCopy());
}

int FPTemplates::count()
{
   int templateCount = 0;

   for (FPTemplate *tmp = copies; tmp; tmp = tmp->next) templateCount++;
   return templateCount;
}

QString FPTemplates::md5(int index)
{
   FPTemplate *curr;
   int currIndex = 0;
   static const char *empty = "";

   for (curr = copies; curr; curr = curr->next)
   {
      if (currIndex == index) { return curr->md5(); }
      currIndex++;
   }
   return empty;
}

int FPTemplates::fingerIndexAt(int index)
{
   FPTemplate *curr;
   int currIndex = 0;

   for (curr = copies; curr; curr = curr->next)
   {
      if (currIndex == index) { return curr->fingerIndex(); }
      currIndex++;
   }
   return -1;
}

int FPTemplates::countTemplates(int company, int bioType, int id, bool isEmployee)
{
   DIR           *d;
   struct dirent *dirnt;
   QString dir;
   int count = 0;

   if (!isEmployee) { dir = FilenameHelper::bioUserDirectory(company, bioType, id); }
   else { dir = FilenameHelper::bioEmployeeDirectory(company, bioType, id); }

   d = opendir(dir.toLocal8Bit().data());
   struct stat status;

   if (d)
   {
      while ((dirnt = readdir(d)))
      {
         if (dirnt->d_type == DT_REG && strlen(dirnt->d_name) == 5 && (dirnt->d_name[0] >= '1' && dirnt->d_name[0] <= '5')) // Regular file in #.dat format
         {
            QString fn = dir + "/" + dirnt->d_name;
            if (stat(fn.toLocal8Bit().data(), &status) == 0)
            {
               if (status.st_size > 0 && status.st_size < 3000)
               {
                  count++;
               }
            }
         }
      }

      closedir(d);
   }

   return count;
}
bool FPTemplates::loadTemplates(int company, int bioType, int id, bool isEmployee)
{
   DIR           *d;
   struct dirent *dirnt;

   reset();

   QString dir;
   if (!isEmployee) { dir = FilenameHelper::bioUserDirectory(company, bioType, id); }
   else { dir = FilenameHelper::bioEmployeeDirectory(company, bioType, id); }

   d = opendir(dir.toLocal8Bit().data());
   struct stat status;

   if (d)
   {
      while ((dirnt = readdir(d)))
      {
         if (dirnt->d_type == DT_REG && strlen(dirnt->d_name) == 5 && (dirnt->d_name[0] >= '1' && dirnt->d_name[0] <= '5')) // Regular file in #.dat format
         {
            QString fn = dir + "/" + dirnt->d_name;
            if (stat(fn.toLocal8Bit().data(), &status) == 0)
            {
               if (status.st_size > 0 && status.st_size < 3000)
               {
                  FPTemplate *t = new FPTemplate(dirnt->d_name[0] - '0');

                  if (t->loadTemplate(fn.toLocal8Bit().data()))
                  {
                     addTemplate(t);
                     qDebug() << "LOADING TEMPLATE FOR INDEX " << t->fingerIndex();
                  }
                  else
                  {
                     delete t;
                  }
               }
            }
         }
      }

      closedir(d);
   }

   return true;
}


