#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include "BinaryTree.h"
using namespace std;

namespace Order
{
    template<class Iterator>
    /**
     * @brief order the iterator by using 
     * binarytree
     */
    static void Order( Iterator begin, Iterator end){
        using T = typename std::iterator_traits<Iterator>::
        value_type;
        BinaryTree<T> tree;
        for(auto it = begin; it != end; ++it){
            tree.insert(*it);
        }
        vector<T> treevector = tree.getTreeByVector();
        copy(treevector.begin(),treevector.end(),begin);
    }
};