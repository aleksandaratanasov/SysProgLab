//#include "ParserAST.h"

//template<typename T>
//T& TreeNode<T>::getData() const {
//    return *this->data;
//}

//template<typename T>
//void TreeNode<T>::setData(const T& data) {
//    *this->data = data;
//}

//template<typename T>
//void TreeNode<T>::addChild(const T& data) {
//    children.push_back(new TreeNode<T>(this, data));
//}

//template<typename T>
//void TreeNode<T>::removeChild(const size_t& indx) {
//    children.erase(children.begin()+indx);
//}

//template<typename T>
//TreeNode<T>* TreeNode<T>::findChild(const T& data) const {
//    for(int i=0; i<children.size(); i++)
//        if(children[i]->getData() == data)
//            return children[i];
//    return NULL;
//}

//template<typename T>
//TreeNode<T>* TreeNode<T>::getChild(const size_t& indx) const {
//    return children[indx];
//}

//template<typename T>
//TreeNode<T>* TreeNode<T>::getParent() const {
//    return parent;
//}

//template<typename T>
//int TreeNode<T>::getNumChildren() const {
//    return children.size();
//}
