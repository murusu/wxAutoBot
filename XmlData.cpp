#include "XmlData.h"

XmlTask::XmlTask():XmlHandler()
{
}

XmlTask::~XmlTask()
{
}

bool XmlTask::InitData(const char * pfilename)
{
    TiXmlString pfullname = TiXmlString(XMLTASK_PATH) + TiXmlString("//") + TiXmlString(pfilename);

    //if(!init(pfullname.c_str(), XMLTASK_ROOTNAME)) return false;
    return true;
}
