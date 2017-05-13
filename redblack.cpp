#include "redblack_tree.h"
#include <assert.h>
#include <iostream>

using namespace std;

struct node *grandparent(struct node *n)
{
    if((n != 0) && (n->parent != 0))
    {
        if((n->parent)->parent != 0);
        {
            return (n->parent)->parent;
        }
    }
    else
    {
        return 0;
    }
}

struct node *uncle(struct node *n)
{
    struct node *g = grandparent(n);

    if(g != 0)
    {
        if(g->left == n->parent)
        {
            return g->right;
        }
        else
        {
            return g->left;
        }
    }
    else
    {
        return 0;
    }
}

void swap(struct node *n,struct node *p,struct node *g)
{
     n->parent = g;
     p->parent = n;

     if( g != 0 && g->left == p)
     {
         g->left = n;
     }
     else if( g != 0)
     {
         g->right = n;
     }
}

void rotate_left(struct node *n)
{
    if(n != 0)
    {
       struct node *g = grandparent(n);

        n->parent->right = n->left;
        n->left = n->parent;

        swap(n,n->left,g);
    }
}

void rotate_right(struct node *n)
{
    if(n != 0)
    {
        struct node *g = grandparent(n);

        n->parent->left = n->right;
        n->right = n->parent;

        swap(n,n->right,g);
    }
}

extern struct node *insert_case2(struct node *n);
extern struct node *insert_case3(struct node *n);
extern struct node *insert_case4(struct node *n);
extern struct node *insert_case5(struct node *n);

struct node *insert_case1(struct node *n)
{
    if(n->parent == 0)
    {
        //cout<<1<<" "<<n->key<<" "<<n->color<<endl;
        //n->color = BLACK;
        //cout<<1<<" "<<n->key<<" "<<n->color<<endl;
        return n;
    }
    else
    {
        return insert_case2(n);
    }
}

struct node *insert_case2(struct node *n)
{
    //cout<<"case 3"<<n->parent->key<<" "<<n->parent->color<<" "<<n->key<<endl;
    if(n->parent->color == BLACK)
    {
        //cout<<2<<" "<<n->key<<" "<<n->color<<endl;
        return 0;
    }
    else
    {
        return insert_case3(n);
    }
}

struct node *insert_case3(struct node *n)
{
    struct node *g = grandparent(n);
    struct node *u = uncle(n);

    if( (u != 0) && (u->color == RED))
    {
        //cout<<3<<" "<<n->key<<" "<<n->color<<endl;
        n->parent->color = BLACK;
        u->color = BLACK;
        g->color = RED;
        //cout<<3<<" "<<n->key<<" "<<n->color<<endl;
        return insert_case1(g);
    }
    else
    {
        return insert_case4(n);
    }
}

struct node *insert_case4(struct node *n)
{
    struct node *g = grandparent(n);
    //cout<<4<<"case "<<n->key<<" "<<n->color<<endl;
    if((n != 0) && (g != 0) && (n->parent != 0) &&
       (n == n->parent->right) && (n->parent == g->left))
    {
        //cout<<"rotate left"<<endl;
        rotate_left(n);
        n = n->left;cout<<n->key<<endl;
    }
    else if((n != 0) && (g != 0) &&(n->parent != 0) &&
            (n == n->parent->left) && (n->parent == g->right))
    {
        rotate_right(n);
        n = n->right;
    }

    return insert_case5(n);
}

struct node *insert_case5(struct node *n)
{
    struct node *g = grandparent(n);

    if(g == 0)
    {
        n->parent->color = BLACK;
    }
    else
    {
        //cout<<5<<"case "<<n->key<<" "<<n->color<<endl;
        n->parent->color = BLACK;
        g->color = RED;
        //cout<<5<<"case "<<n->key<<" "<<n->parent->left->key<<" "<<n->parent->parent->left->key<<" "<<endl;
        if((n != 0) && (n == n->parent->left) && (n->parent == g->left))
        {
            rotate_right(n->parent);
        }
        else if( n != 0)
        {
            rotate_left(n->parent);
        }
    }

    if(n->parent->parent == 0)
    {
        return n->parent;
    }
    else
    {
        return 0;
    }
}

struct node *fix_after_insert(struct node *red_leaf, struct node *root)
{
    if(root == 0 && red_leaf == 0)
    {
        return root;
    }

    if(red_leaf == 0)
    {
        return root;
    }

    struct node *new_root = insert_case1(red_leaf);

    if(new_root != 0)
    {
        return new_root;
    }
    else
    {
        return root;
    }
}

const char first_name[] = {"Anton"};
const char second_name[] = {"Kovachev"};
const char faculty_number[] = {"44390"};
