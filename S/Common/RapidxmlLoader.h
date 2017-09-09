#ifndef XRapidxmlLoader_h__
#define XRapidxmlLoader_h__

#include "Rapidxml\rapidxml.hpp"
#include "FileLoader.h"
#include "Rapidxml\rapidxml_help.hpp"
//--------------------------------------------------------------------------------------------------

class RapidxmlLoader
{
public:
    RapidxmlLoader(const char* name);
    ~RapidxmlLoader(void);

    bool loadFile();
    CXRapidxmlNode* getRootNode();
protected:
    bool loadFile(const char* name);

    const char* mFileName;

    CXRapidxmlDocument mRapidxmlDoc;

    FileLoader mFileLoader;

    Char* mBuffer;
};
inline RapidxmlLoader::RapidxmlLoader(const char* name)
    : mFileName(name)
{
}

inline RapidxmlLoader::~RapidxmlLoader(void)
{
    mFileLoader.Close();

    dSafeDelete(mBuffer);
}

inline bool RapidxmlLoader::loadFile(const char* name)
{
    CXASSERT_RETURN_FALSE(mFileLoader.OpenFile(name));

    mBuffer = new Char[mFileLoader.GetBufferSize() + 1];
    memset(mBuffer, 0, mFileLoader.GetBufferSize() + 1);
    mFileLoader.ReadToBuffer(mBuffer);
    mFileLoader.Close();
    mRapidxmlDoc.parse<rapidxml::parse_default>(mBuffer);
    return true;
}

inline CXRapidxmlNode* RapidxmlLoader::getRootNode()
{
    return mRapidxmlDoc.first_node();
}

inline bool RapidxmlLoader::loadFile()
{
    CXASSERT_RETURN_FALSE(mFileName);
    return loadFile(mFileName);
}

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


#define xml_load(file) RapidxmlLoader loader(file);\
	CXASSERT(loader.loadFile());\
	CXXMLNodeStack _nodeStack;\
	CXRapidxmlNode* _node=loader.getRootNode();\

#define xml_get_node(name) \
	for(CXXMLHelper _helper(_nodeStack, _node, name);_node!=nullptr;_node=_node->next_sibling(name))

#define xml_get_attr(attr,var) if(!_xml_get_attribute(_node,attr,var)) return false;

#endif // XRapidxmlLoader_h__