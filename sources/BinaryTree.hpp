//
// Created by Almog on 30/05/2021.
//
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Node.hpp"

using namespace std;
namespace ariel
{
    template<typename T>
    class BinaryTree
    {
    public:
        Node<T>* root;
        void deep_copy(const Node<T> &start, Node<T> &end)
        {
            if (start.l!=nullptr)
            {
                end.l=new Node<T>(start.l->v);
                deep_copy(*start.l,*end.l);
            }
            if (start.r!=nullptr)
            {
                end.r=new Node<T>(start.r->v);
                deep_copy(*start.r,*end.r);
            }
        }
        BinaryTree():root(nullptr){}
        BinaryTree(const BinaryTree<T>& node)
        {
            if(node.root!=nullptr)
            {
                root=new Node<T>(node.root->v);
                deep_copy(*node.root,*root);
            }
        }
        BinaryTree(BinaryTree<T> && node) noexcept //https://en.cppreference.com/w/cpp/language/noexcept
        {
            root=node.root;
            node.root=nullptr;
        }
        ~BinaryTree(){}
        Node<T>* find(Node<T>* node,T& value){
            if(node==nullptr)
            {
                return nullptr;
            }
            if(node->v==value)
            {
                return node;
            }
            Node<T>* r=find(node->r, value);
            if(r)
            {
                return r;
            }
            Node<T>* l=find(node->l, value);
            return l;
        }
        BinaryTree<T>& add_root(T root_node)
        {
            if(root==nullptr)
            {
                root=new Node<T>(root_node);
            }
            root->v=root_node;
            return *this;
        }
        BinaryTree<T>& add_left(T parent, T child)
        {
            if(!find(root, parent))
            {
                throw invalid_argument("invalid_argument: parent missing in left");
            }
            if(!find(root, parent)->l)
            {
                find(root, parent)->l=new Node<T>(child);
            }
            find(root, parent)->l->v=child;
            return *this;
        }
        BinaryTree<T>& add_right(T parent, T child)
        {
            if(!find(root, parent))
            {
                throw invalid_argument("invalid_argument: parent missing in right");
            }
            if(!find(root, parent)->r)
            {
                find(root, parent)->r=new Node<T>(child);
            }
            find(root, parent)->r->v=child;
            return *this;
        }
        class Iterator
        {
        public:
            void _preorder(Node<T>* node)
            {
                if(node==nullptr)
                {
                    return;
                }
                nodes.push_back(node);
                _preorder(node->l);
                _preorder(node->r);
            }
            void _inorder(Node<T>* node)
            {
                if(node==nullptr)
                {
                    return;
                }
                _inorder(node->l);
                nodes.push_back(node);
                _inorder(node->r);
            }
            void _postorder(Node<T>* node)
            {
                if(node==nullptr)
                {
                    return;
                }
                _postorder(node->l);
                _postorder(node->r);
                nodes.push_back(node);
            }
            vector <Node<T>*> nodes;
            Node<T>* cNode;
            Iterator(Node<T>* node, int num) noexcept
            {
                if(node != nullptr)
                {
                    switch(num)
                    {
                        case 1:
                            _inorder(node);
                            cNode=nodes[0];
                            break;
                        case 2:
                            _postorder(node);
                            cNode=nodes[0];
                            break;
                        case 3:
                            _preorder(node);
                            cNode=nodes[0];
                            break;
                        default:
                            _inorder(node);
                            cNode=nodes[0];
                    }
                }else{
                    cNode=nullptr;
                }
            }
            Iterator():cNode(nullptr){}
            Iterator(Node<T>* n):cNode(n){}
            Iterator& operator++()
            {
                if(nodes.size()!=1)
                {
                    nodes.erase(nodes.begin());
                    cNode=nodes[0];
                }else
                {
                    cNode=nullptr;
                }
                return *this;
            }
            Iterator operator++(int)
            {
                Iterator ans(nodes[0]);
                ++*this;
                return ans;
            }
            bool operator!= (Iterator node)
            {
                return cNode!=nullptr;
            }
            bool operator== (Iterator node)
            {
                return cNode==node.cNode;
            }
            T& operator*()
            {
                return cNode->v;
            }
            T* operator->()
            {
                return &cNode->v;
            }
        };
        Iterator begin()
        {
            return Iterator{root, 1};
        }
        Iterator end(){
            return Iterator();
        }
        Iterator begin_inorder()
        {
            return begin();
        }
        Iterator end_inorder(){
            return Iterator();
        }
        Iterator begin_postorder()
        {
            return Iterator{root, 2};
        }
        Iterator end_postorder()
        {
            return Iterator();
        }
        Iterator begin_preorder()
        {
            return Iterator{root, 3};
        }
        Iterator end_preorder()
        {
            return Iterator();
        }
        BinaryTree& operator=(BinaryTree node)
        {
            if(this==&node)
            {
                return *this;
            }
            if(root!=nullptr)
            {
                delete root;
            }
            root=new Node<T>(node.root->v);
            deep_copy(*node.root,*root);
            return *this;
        }
        BinaryTree& operator=(BinaryTree&& node) noexcept
        {
            *root=node.root;
        }
        friend ostream& operator<< (ostream& os,BinaryTree<T> const& b)
        {
            return os;
        }
    };
}



