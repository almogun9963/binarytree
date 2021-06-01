//
// Created by Almog on 30/05/2021.
//

#pragma once
#include "BinaryTree.hpp"

template<typename T>
class Node {
public:
    T v;
    Node* r;
    Node* l;
    Node(T& value):v(value),r(nullptr),l(nullptr){}
};