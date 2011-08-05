#include "XmlHandler.h"

XmlHandler::XmlHandler()
{
    m_xmldoc    = NULL;
    m_filename  = NULL;
    m_rootname  = NULL;
}

XmlHandler::~XmlHandler()
{
    if(m_xmldoc)
    {
        delete m_xmldoc;
        m_xmldoc = NULL;
    }

    if(m_filename)
    {
        delete m_filename;
        m_filename = NULL;
    }

    if(m_rootname)
    {
        delete m_rootname;
        m_rootname = NULL;
    }
}

bool XmlHandler::Init(const char *filename, const char *rootname)
{
    m_filename  = new TiXmlString(filename);
    m_rootname  = new TiXmlString(rootname);
    m_xmldoc    = new TiXmlDocument();

    if(!m_filename || !m_rootname || !m_xmldoc) return false;

    if(!m_xmldoc->LoadFile(m_filename->c_str()))
    {
        TiXmlDeclaration *xmlhead = new TiXmlDeclaration("1.0", "utf-8","");
        m_xmldoc->LinkEndChild( xmlhead );
        if(!m_xmldoc->SaveFile(m_filename->c_str())) return false;
    }

    return true;
}

size_t XmlHandler::GetElementNum(const char *pKeyName)
{
    size_t iElementNum          = 0;
    TiXmlString *pStrKeyName    = new TiXmlString(pKeyName);
    TiXmlString *pStrNodeKey    = new TiXmlString();
    TiXmlElement *pElementNode  = NULL;

    size_t start_offset    = 0;
    size_t search_offset = 0;

    while(search_offset != TiXmlString::npos)
    {
        start_offset    = search_offset;
        search_offset   = pStrKeyName->find('/', search_offset + 1);
    }

    pStrNodeKey->assign(pStrKeyName->c_str() + start_offset + 1, pStrKeyName->length() - start_offset - 1);

    pElementNode = GetElement(pStrKeyName->c_str(), 0, false);

    while(pElementNode)
    {
        iElementNum++;
        pElementNode = pElementNode->NextSiblingElement(pStrNodeKey->c_str());
    }

    return iElementNum;
}

TiXmlElement * XmlHandler::GetElement(const char *pKeyName, size_t iIndex, bool bAutoGenerate)
{
    if(!m_rootname || !m_xmldoc) return NULL;

    TiXmlElement *pElementNode      = NULL;
    TiXmlElement *pElementChild     = NULL;
    TiXmlElement *pElementSibling   = NULL;

    if(!(pElementNode = m_xmldoc->RootElement()))
    {
        if(!bAutoGenerate) return NULL;

        pElementChild = new TiXmlElement(m_rootname->c_str());
        m_xmldoc->LinkEndChild(pElementChild);
        pElementNode = pElementChild;
    }

    TiXmlString *pStrKeyName    = new TiXmlString(pKeyName);
    TiXmlString *pStrNodeKey    = new TiXmlString();
    size_t start_position       = 0;
    size_t search_offset        = 0;
    size_t char_num             = pStrKeyName->length();


    while(start_position < char_num)
    {
        search_offset = pStrKeyName->find('/', start_position);

        if(search_offset == TiXmlString::npos) search_offset = char_num;

        pStrNodeKey->assign(pStrKeyName->c_str() + start_position, search_offset - start_position);

        pElementChild = pElementNode->FirstChildElement(pStrNodeKey->c_str());

        if(!pElementChild)
        {
            if(!bAutoGenerate) return NULL;

            pElementChild = new TiXmlElement(pStrNodeKey->c_str());
            pElementNode->LinkEndChild(pElementChild);
        }

        pElementNode = pElementChild;

        start_position = search_offset + 1;
    }

    while(iIndex >0)
    {
        pElementSibling = pElementNode->NextSiblingElement(pStrNodeKey->c_str());

        if(!pElementSibling)
        {
            if(!bAutoGenerate) return NULL;

            pElementSibling = new TiXmlElement(pStrNodeKey->c_str());
            pElementNode->Parent()->LinkEndChild(pElementSibling);
        }

        pElementNode = pElementSibling;
        iIndex--;
    }

    return pElementNode;
}

const char * XmlHandler::GetElementText(TiXmlElement *pElement)
{
    if(!pElement) return NULL;

    return pElement->GetText();
}

const char * XmlHandler::GetElementAttribute(TiXmlElement *pElement, const char *pAttributeName)
{
    if(!pElement) return NULL;

    return pElement->Attribute(pAttributeName);
}

bool XmlHandler::SetElementText(TiXmlElement *pElement, const char *pData)
{
    if(!pElement) return false;

    TiXmlText* pXmlText = NULL;
    pXmlText = new TiXmlText(pData);

    if(pElement->FirstChild())
    {
        pElement->ReplaceChild(pElement->FirstChild(), *pXmlText);
    }
    else
    {
        pElement->LinkEndChild(pXmlText);
    }

    return true;
}

bool XmlHandler::SetElementAttribute(TiXmlElement *pElement, const char *pAttributeName, const char *pData)
{
    if(!pElement) return false;
    pElement->SetAttribute(pAttributeName, pData);

    return true;
}

bool XmlHandler::SetElementAttribute(TiXmlElement *pElement, const char *pAttributeName, int pData)
{
    if(!pElement) return false;
    pElement->SetAttribute(pAttributeName, pData);

    return true;
}

bool XmlHandler::SaveXmlFile()
{
    if(!m_xmldoc) return false;

    return m_xmldoc->SaveFile(m_filename->c_str());
}

void XmlHandler::ClearContent()
{
    if(m_xmldoc)
    {
        if(m_xmldoc->RootElement()) m_xmldoc->RootElement()->Clear();
    }
}
