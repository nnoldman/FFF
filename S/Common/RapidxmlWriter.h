#ifndef XRapidxmlWriter_h__
#define XRapidxmlWriter_h__

#include "Rapidxml\rapidxml_help.hpp"

class RapidxmlWriter {
  public:
    RapidxmlWriter();

    ~RapidxmlWriter(void);

    bool Write(const char* name);

    bool AppendChild(CXRapidxmlNode* node);

  protected:
    CXRapidxmlNode* mRootNode;
  public:
    inline CXRapidxmlNode* GetRootNode() const {
        return mRootNode;
    }

};
inline void releaseXMLAttribte(CXRapidxmlNode* node) {
    for(CXRapidxmlAttr* attr = node->first_attribute(); attr;) {
        CXRapidxmlAttr* tmp = attr;
        attr = attr->next_attribute();
        delete tmp;
    }
}
inline void releaseXMLNode(CXRapidxmlNode* node) {
    CXRapidxmlNode* child = node->first_node();
    CXRapidxmlNode* sibling = nullptr;
    if(node->parent())
        sibling = node->next_sibling();
    if(child)
        releaseXMLNode(child);
    if(sibling)
        releaseXMLNode(sibling);
    releaseXMLAttribte(node);
    delete node;
}
#include <fstream>
#include "Rapidxml\rapidxml.hpp"
#include "Rapidxml\rapidxml_print.hpp"
inline bool RapidxmlWriter::AppendChild ( CXRapidxmlNode* node ) {
    CXASSERT_RETURN_FALSE ( node );
    if ( !mRootNode ) {
        mRootNode = node;
    } else {
        mRootNode->append_node ( node );
    }
    return true;
}

inline bool RapidxmlWriter::Write ( const char* name ) {
    std::ofstream of ( name );
    CXASSERT_RETURN_FALSE ( !of.bad() );
    CXASSERT_RETURN_FALSE ( mRootNode );
    of << ( *mRootNode );
    of.close();
    return true;
}

inline RapidxmlWriter::~RapidxmlWriter ( void ) {
    if(mRootNode)
        releaseXMLNode(mRootNode);
}

inline RapidxmlWriter::RapidxmlWriter()
    : mRootNode ( 0 ) {

}

#endif // XRapidxmlWriter_h__
