#ifndef RapidxmlLoader_h__
#define RapidxmlLoader_h__
#include "rapidxml_help.hpp"
#include "FileLoader.h"
//--------------------------------------------------------------------------------------------------
namespace Basic
{

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
    };
    inline RapidxmlLoader::RapidxmlLoader(const char* name)
        : mFileName(name)
    {
    }

    inline RapidxmlLoader::~RapidxmlLoader(void)
    {
        mFileLoader.Close();
    }

    inline bool RapidxmlLoader::loadFile(const char* name)
    {
        CXASSERT_RETURN_FALSE(mFileLoader.open(name));
        mRapidxmlDoc.parse<rapidxml::parse_default>(mFileLoader.getBuffer());
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

#define xml_load(file) RapidxmlLoader loader(file);\
	CXASSERT_RETURN_FALSE(loader.loadFile());\
	CXXMLNodeStack _nodeStack;\
	CXRapidxmlNode* _node=loader.getRootNode();\

#define xml_get_node(name) \
	for(CXXMLHelper _helper(_nodeStack, _node, name);_node!=nullptr;_node=_node->next_sibling(name))

#define xml_get_attr(attr,var) if(!_xml_get_attribute(_node,attr,var)) return false;

}
#endif // RapidxmlLoader_h__
