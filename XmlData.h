#ifndef XMLDATA_H_INCLUDED
#define XMLDATA_H_INCLUDED

#include "XmlHandler.h"
#include "GlobalValue.h"

class XmlTask : public XmlHandler
{
    public:
        XmlTask();
        ~XmlTask();

        bool InitData(const char * pfilename);
};

#endif // XMLDATA_H_INCLUDED
