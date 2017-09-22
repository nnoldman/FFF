#ifndef rapidxml_help_h__
#define rapidxml_help_h__
#include "Rapidxml\rapidxml.hpp"
#include "Stack.h"

typedef rapidxml::xml_document<Char> CXRapidxmlDocument;
typedef rapidxml::xml_node<Char> CXRapidxmlNode;
typedef rapidxml::xml_attribute<Char> CXRapidxmlAttr;

typedef  class Stack<CXRapidxmlNode*> CXXMLNodeStack;

class CXXMLHelper {
  public:
    CXXMLHelper ( CXXMLNodeStack& stack, CXRapidxmlNode*& n, const char* nodeName );
    ~CXXMLHelper();
  private:
    CXRapidxmlNode*& mNode;
    CXXMLNodeStack& mNodeStack;
};

template<typename T>
bool _xml_get_attribute ( CXRapidxmlNode* node, const char* attr, T& var ) {
    CXASSERT_RETURN_FALSE ( node && attr );
    CXRapidxmlAttr* pAttri = node->first_attribute ( attr );
    CXASSERT_RETURN_FALSE ( pAttri );
    const char* svar = pAttri->value();
    StringHelper::setValue(svar, &var);
    return true;
}

//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, int& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, float& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, uString& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, uString& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, bool& var );

#endif // rapidxml_help_h__
