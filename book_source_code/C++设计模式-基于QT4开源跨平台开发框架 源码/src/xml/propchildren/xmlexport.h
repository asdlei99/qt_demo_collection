#ifndef XMLEXPORT_H
#define XMLEXPORT_H
#include <QString>
class QObject;
#include "xmlsupport.h"

using namespace XmlSupport;
/**
   This version does not perform any file i/o -
   just converts a QObject with properties
   into an XML string representation.
  
   @Deprecated - known Issues: This class is not meant to be used in conjunction
   with the DataObjects library.
*/
//start
class XMLExport {
 public:
    virtual ~XMLExport() {}
    virtual QString objectToXml(const QObject* ptr,
                                int indentlevel=0);
};
//end
#endif


