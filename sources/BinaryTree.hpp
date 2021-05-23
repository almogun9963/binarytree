//
// Created by Almog on 22/05/2021.
//
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ariel
{
    template <class T>

    class BinaryTree
    {
        struct Node
        {
            T value;
            Node *r = nullptr;
            Node *l = nullptr;
            Node *father = nullptr;
            Node(T v) : value(v), r(nullptr), l(nullptr), father(nullptr) {}
        };
        Node *root;

        class Iterator
        {
        private:
            Node *current;
        public:
            Iterator(Node *ptr = nullptr): current(ptr){}
            T &operator*() const{return current->value;}
            T *operator->() const{return &(current->value);}
            Iterator &operator++(){return *this;}
            const Iterator operator++(int){return *this;}
            bool operator==(const Iterator &rhs) const{return false;} //if i return true, i have core dump error for some reason
            bool operator!=(const Iterator &rhs) const{return false;}
        };
    public:
        BinaryTree<T>(){root = nullptr;}
        BinaryTree<T> add_root(const T &v){return *this;}
        BinaryTree<T> add_left(const T &v, const T &l){return *this;}
        BinaryTree<T> add_right(const T &v, const T &r){return *this;}

        Iterator begin(){return Iterator{root};}
        Iterator end(){return Iterator{root};}
        Iterator begin_inorder(){return Iterator{root};}
        Iterator end_inorder(){return Iterator{root};}
        Iterator begin_preorder(){return Iterator{root};}
        Iterator end_preorder(){return Iterator{root};}
        Iterator begin_postorder(){return Iterator{root};}
        Iterator end_postorder(){return Iterator{root};}

        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &tree){return os;}
    };
}