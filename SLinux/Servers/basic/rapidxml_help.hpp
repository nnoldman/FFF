#ifndef rapidxml_help_h__
#define rapidxml_help_h__
#include "Rapidxml/rapidxml.hpp"
#include "Stack.h"
#include "StringHelper.h"

typedef rapidxml::xml_document<Char> CXRapidxmlDocument;
typedef rapidxml::xml_node<Char> CXRapidxmlNode;
typedef rapidxml::xml_attribute<Char> CXRapidxmlAttr;

typedef  class Stack<CXRapidxmlNode*> CXXMLNodeStack;

class CXXMLHelper
{
public:
    CXXMLHelper ( CXXMLNodeStack& stack, CXRapidxmlNode*& n, const char* nodeName );
    ~CXXMLHelper();
private:
    CXXMLNodeStack& mNodeStack;
    CXRapidxmlNode*& mNode;
};
inline CXXMLHelper::CXXMLHelper(CXXMLNodeStack& stack, CXRapidxmlNode*& n, const char* nodeName)
    : mNodeStack(stack)
    , mNode(n)
{
    if (mNode)
        mNodeStack.push(mNode);
    mNode = mNode->first_node(nodeName);
}

inline CXXMLHelper::~CXXMLHelper()
{
    mNode = mNodeStack.top();
    mNodeStack.pop();
}
template<typename T>
bool _xml_get_attribute ( CXRapidxmlNode* node, const char* attr, T& var )
{
    CXASSERT_RETURN_FALSE ( node && attr );
    CXRapidxmlAttr* pAttri = node->first_attribute ( attr );
    CXASSERT_RETURN_FALSE ( pAttri );
    const char* svar = pAttri->value();
    Basic::StringHelper::setValue(svar, &var);
    return true;
}

//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, int& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, float& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, uString& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, uString& var );
//void xml_get_attribute ( CXRapidxmlNode* node, const char* attr, bool& var );

#endif // rapidxml_help_h__
