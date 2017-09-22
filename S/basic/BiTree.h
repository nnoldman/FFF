#pragma once
template<typename T>
class BiTreeNode {
  public:
    typedef BiTreeNode<T> ThisNode;

    BiTreeNode()
        : mData(0), mLeft(0), mRight(0) {

    }
    void destory() {
        if (mLeft != nullptr)
            mLeft->destory();

        if (mRight != nullptr)
            mRight->destory();

        dSafeDelete(mData);
    }
    ~BiTreeNode() {
        destory();
    }
  protected:
    T* mData;
    ThisNode* mLeft;
    ThisNode* mRight;
};
template<typename T>
class BiTree {
  public:
    typedef BiTreeNode<T> ThisBiTreeNode;
    ~BiTree() {
        dSafeDelete(mRoot);
    }
    BiTree(void)
        : mRoot(0) {
        mRoot = new ThisBiTreeNode;
    }

    ThisBiTreeNode* GetLeftest() const {
        ThisBiTreeNode* next = mRoot->mLeft;
        ThisBiTreeNode* last = 0;

        while (next) {
            last = next;
            next = next->mLeft;
        }

        return last;
    }
    ThisBiTreeNode* GetRightest() const {
        ThisBiTreeNode* next = mRoot->mRight;
        ThisBiTreeNode* last = 0;

        while (next) {
            last = next;
            next = next->mRight;
        }

        return last;
    }

    ThisBiTreeNode*  mRoot;
};
