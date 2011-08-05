#ifndef XML_CLASS_H_INCLUDED
#define XML_CLASS_H_INCLUDED

#include <stdio.h>
#include "tinyxml/tinyxml.h"

class XmlHandler
{
    protected:
        TiXmlDocument   *m_xmldoc;
        TiXmlString     *m_filename;
        TiXmlString     *m_rootname;

    public:
        size_t  GetElementNum(const char *pKeyName);
        TiXmlElement * GetElement(const char *pKeyName, size_t iIndex = 0, bool bAutoGenerate = false);

        const char * GetElementText(TiXmlElement *pElement);
        const char * GetElementAttribute(TiXmlElement *pElement, const char *pAttributeName);

        bool SetElementText(TiXmlElement *pElement, const char *pData);
        bool SetElementAttribute(TiXmlElement *pElement, const char *pAttributeName, const char *pData);
        bool SetElementAttribute(TiXmlElement *pElement, const char *pAttributeName, int pData);

        bool Init(const char *filename, const char *rootname = "datas");
        bool SaveXmlFile();
        void ClearContent();

    public:
        XmlHandler();
        ~XmlHandler();
};
#endif // XML_CLASS_H_INCLUDED
