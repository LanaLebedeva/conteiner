/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtreeV2.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 13:32:40 by mlaureen          #+#    #+#             */
/*   Updated: 2021/08/01 13:32:54 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RBTREEV2_H
#define RBTREEV2_H


namespace ft {
    template <typename T>
    struct Node;

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    class RBTree;

}
#include "iterator.hpp"
#include "RBTreeIterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

#include <iostream> // for test-print


namespace ft {

    class T;

    class InputIterator;

    template <typename T>
    class less {
    public:
        bool operator()(const T& x, const T& y) const;
    };

    template<typename T>
    bool less<T>::operator()(const T &x, const T &y) const { return (x < y); }

    template <typename T >
    // data structure that represents a node in the tree
    struct Node {
   // public:
        T           *data; // holds the key
        Node        *parent; // pointer to the parent
        Node        *left; // pointer to left child
        Node        *right; // pointer to right child
        int         color; // 1 -> Red, 0 -> Black

        T getT() {
           return (*data);

        }

        Node(T *data): data(data), parent(nullptr), left(nullptr), right(nullptr), color(1) {}
    };

    // class RBTree implements the operations in Red Black Tree
    template<typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T>, typename AllocN = std::allocator<Node<T> > >
    class RBTree {
    public:

        typedef T                                           value_type0;
        typedef Node<value_type0>                           value_type_node;
        typedef Alloc                                       allocator_type;
        typedef AllocN                                      allocator_type_N;
        typedef value_type_node&                                 reference;
        typedef const value_type_node&                           const_reference;
        typedef value_type_node*                                 pointer;
        typedef const value_type_node*                           const_pointer;
        typedef Compare                                     key_compare;
        typedef size_t                                      size_type;
        typedef typename ft::RBTreeIterator<T, T*, T&>      iterator;
        typedef typename ft::RBTreeIterator<T, const T*, const T&>   const_iterator;
        typedef typename ft::reverse_iterator<iterator>               reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;


        void printEtully();
        void printMlaureen();

        //TODO Constructs a map container object, initializing its contents depending on the constructor version used
        ~RBTree();

        RBTree(const key_compare& comp = Compare(),
               const allocator_type& alloc = allocator_type(),
               const allocator_type_N &allocN= allocator_type_N());
        template <class InputIterator>
        RBTree(InputIterator first, InputIterator last,
               const key_compare& comp = Compare(),
               const allocator_type& alloc = allocator_type(),
               const allocator_type_N &allocN= allocator_type_N(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0);
     //   RBTree(const RBTree & x);

        RBTree& operator= (const RBTree& x);

        //iterator
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;

        //Capacity:
        bool empty() const;
        size_t size() const;
        size_t max_size() const;

        //Modifiers:
        void insert (const value_type0& val, const Compare & cmp = Compare());

        int  insert_map (const value_type0& val, const Compare & cmp = Compare());

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last, const key_compare& comp = Compare(), typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0);

        void erase (iterator position, const key_compare& comp = Compare());
        size_type erase (const value_type0 & k, const key_compare& comp = Compare());
        void erase (iterator first, iterator last, const key_compare& comp = Compare());
        void clear(const key_compare& comp = Compare());

        void swap (RBTree & x);
        void setSize(size_t n) {_size = n;}

         iterator find_map (const value_type0 & k, const Compare & cmp = Compare());

         size_type count (const value_type0 & k, const Compare & cmp = Compare()) const;
        iterator lower_bound (const value_type0 & k, const Compare & cmp = Compare());
        const_iterator lower_bound (const value_type0 & k, Compare cmp = Compare()) const;
        iterator upper_bound (const value_type0 & k,Compare cmp = Compare()) const;




    protected:
        allocator_type      _alloc;
        allocator_type_N    _allocN;
        Compare             _compare;
        pointer             root;
        pointer             TNULL;
        size_t              _size; //number of elements in the RB-tree container
        pointer             _end;

        void _print(pointer the_node, int place);
        void _printM(pointer the_node, int place);

        // initializes the nodes with appropirate values
        // all the pointers are set to point to the null pointer
        void initializeNULLNode(pointer node, pointer parent);
        void preOrderHelper(pointer node);
        void inOrderHelper(pointer node);
        void postOrderHelper(pointer node);
        pointer searchTreeHelper(pointer node, value_type0 key, Compare cmp = Compare());

        // fix the rb tree modified by the delete operation
        void fixDelete(pointer x);
        void rbTransplant(pointer u, pointer v);
        size_t deleteNodeHelper(pointer node, T key, const Compare cmp = Compare());

        // fix the red-black tree
        void fixInsert(pointer k);
        void printHelper(pointer root, std::string indent, bool last);

    public:


        // Pre-Order traversal
        // Node->Left Subtree->Right Subtree
        void preorder() {preOrderHelper(this->root);}

        // In-Order traversal
        // Left Subtree -> Node -> Right Subtree
        void inorder() {inOrderHelper(this->root);}

        // Post-Order traversal
        // Left Subtree -> Right Subtree -> Node
        void postorder() {postOrderHelper(this->root);}

        // search the tree for the key k
        // and return the corresponding node
        pointer searchTree(value_type0 k, const Compare & cmp = Compare());

        // find the node with the minimum key
        pointer minimum(pointer node);
        // find the node with the maximum key
        pointer maximum(pointer node);
        // find the successor of a given node
        pointer successor(pointer x);
        // find the predecessor of a given node
        pointer predecessor(pointer x);
        // rotate left at node x
        void leftRotate(pointer x);

        // rotate right at node x
        void rightRotate(pointer x);

        // insert the key to the tree in its appropriate position
        // and fix the tree
     //   void insert(T const & key, Compare cmp = Compare());

        pointer getRoot();

        // delete the node from the tree
        size_t deleteNode(value_type0 data, const key_compare& comp = Compare());

        // print the tree structure on the screen
        void prettyPrint();

    };


    template<typename T, typename Compare, typename Alloc, typename AllocN>
    RBTree<T, Compare, Alloc, AllocN>::RBTree(const key_compare &comp, const allocator_type &alloc, const allocator_type_N &allocN): _alloc(alloc), _allocN(allocN), _compare(comp), _size(0) {
        TNULL=_allocN.allocate(1);
           _allocN.construct(TNULL, (nullptr) );
           TNULL->color = 0;
           TNULL->left = nullptr;
           TNULL->right = nullptr;
           root = TNULL;
           _end = _allocN.allocate(1);
           _allocN.construct(_end, (nullptr));
           _end->left = root;
           _end->right = nullptr;
           root->parent = _end;
    }

template<typename T, typename Compare, typename Alloc, typename AllocN>
typename RBTree<T, Compare, Alloc, AllocN>::iterator RBTree<T, Compare, Alloc, AllocN>::begin() {

    pointer         node = root;
    if (node == TNULL)
        return iterator(_end);
    while (node->left != TNULL) {
        node = node->left;
    }
    return iterator(node);
   }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    RBTree<T, Compare, Alloc, AllocN>::~RBTree() {}


    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::_print(RBTree::pointer the_node, int place) {
        if (the_node == TNULL)
            return;
        place += 5;
        _print(the_node->right, place);
        for(int i = 5; i < place; i++)
            std::cout << " ";
        std::cout << (the_node->getT())  << (the_node->color == 1 ? " R" : " B") <<'\n';
        _print(the_node->left, place);
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::printEtully() {
        std::cout << "+++++++++++++++++++++" << '\n' << '\n';
        _print(root, 0);
        std::cout << "\n+++++++++++++++++++++" << '\n';
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::initializeNULLNode(RBTree::pointer node, RBTree::pointer parent) {
        node->data = T();
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::preOrderHelper(RBTree::pointer node) {
        if (node != TNULL) {
            std::cout<<(node->getT())<<" ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::inOrderHelper(RBTree::pointer node) {
        if (node != TNULL) {
            inOrderHelper(node->left);
            std::cout<<(node->getT)<<" ";
            inOrderHelper(node->right);
        }
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::postOrderHelper(RBTree::pointer node) {
        if (node != TNULL) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
           // std::cout<<*(node->data)<<" ";
           _alloc.destroy(node->data);
           _alloc.deallocate(node->data, 1);

           _allocN.destroy(node);
           _allocN.deallocate(node, 1);
        }
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::pointer RBTree<T, Compare, Alloc, AllocN>::searchTreeHelper(RBTree::pointer node, value_type0 key, Compare cmp) {
        //std::cout << "!!! <"<< key.first << ">\n";
        //if (node == TNULL || key == (node->getT())) {
        if (node == TNULL || (!cmp(key, node->getT()) && !cmp(node->getT(), key))) {
            return node;
        }
        if (cmp(key, (node->getT()))){
             return searchTreeHelper(node->left, key, cmp);

        }
        return searchTreeHelper(node->right, key,cmp);

    }
    // fix the rb tree modified by the delete operation
    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::fixDelete(RBTree::pointer x) {
        pointer s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        // case 3.3
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    // case 3.1
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    // case 3.2
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        // case 3.3
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    // case 3.4
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::rbTransplant(RBTree::pointer u, RBTree::pointer v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left){
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    size_t RBTree<T, Compare, Alloc, AllocN>::deleteNodeHelper(RBTree::pointer node, T key, const Compare cmp) {
        // find the node containing key
        pointer z = TNULL;
        pointer x, y;
        while (node != TNULL){
            if ((node->getT()) == key) {
                z = node;
            }

            if (cmp((node->getT()), key)) { //работало до map
                 node = node->right;
            } else {
                node = node->left;
            }
        }

        if (z == TNULL) {
            return 0;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        _alloc.destroy(z->data);
        _alloc.deallocate(z->data, 1);

        _allocN.destroy(z);
        _allocN.deallocate(z, 1);
        if (y_original_color == 0){
            fixDelete(x);
        }
        --_size;
        return 1;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::fixInsert(RBTree::pointer k) {
        pointer u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // uncle
                if (u->color == 1) {
                    // case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        // case 3.2.2
                        k = k->parent;
                        rightRotate(k);
                    }
                    // case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // uncle

                if (u->color == 1) {
                    // mirror case 3.1
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        // mirror case 3.2.2
                        k = k->parent;
                        leftRotate(k);
                    }
                    // mirror case 3.2.1
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::printHelper(RBTree::pointer root, std::string indent, bool last) {
        // print the tree structure on the screen
        if (root != TNULL) {
            std::cout<<indent;
            if (last) {
                std::cout<<"R----";
                indent += "     ";
            } else {
                std::cout<<"L----";
                indent += "|    ";
            }

            std::string sColor = root->color?"RED":"BLACK";
            std::cout<<((root->getT()))<<"("<<sColor<<")"<<std::endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::pointer RBTree<T, Compare, Alloc, AllocN>::minimum(RBTree::pointer node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::pointer RBTree<T, Compare, Alloc, AllocN>::maximum(RBTree::pointer node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::pointer RBTree<T, Compare, Alloc, AllocN>::successor(RBTree::pointer x) {
        // if the right subtree is not null,
        // the successor is the leftmost node in the
        // right subtree
        if (x->right != TNULL) {
            return minimum(x->right);
        }

        // else it is the lowest ancestor of x whose
        // left child is also an ancestor of x.
        pointer y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::pointer RBTree<T, Compare, Alloc, AllocN>::predecessor(RBTree::pointer x) {
        // if the left subtree is not null,
        // the predecessor is the rightmost node in the
        // left subtree
        if (x->left != TNULL) {
            return maximum(x->left);
        }

        pointer y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::leftRotate(RBTree::pointer x) {
        //remove pointer to _end
        root->parent = nullptr;

        pointer y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
        //restore pointer to _end
        root->parent = _end;
        _end->left = root;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::rightRotate(RBTree::pointer x) {
        //remove pointer to _end
        root->parent = nullptr;

        pointer y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
        //restore pointer to _end
        root->parent = _end;
        _end->left = root;
    }


    template<typename T, typename Compare, typename Alloc, typename AllocN>
    size_t RBTree<T, Compare, Alloc, AllocN>::deleteNode(value_type0 data, const key_compare& comp) {
        size_t  res;
        //remove pointer to _end
        root->parent = nullptr;
        res = deleteNodeHelper(this->root, data,  comp);
        //restore pointer to _end
        root->parent = _end;
        _end->left = root;
        return res;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::prettyPrint() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::pointer RBTree<T, Compare, Alloc, AllocN>::getRoot() {
        return this->root;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::pointer RBTree<T, Compare, Alloc, AllocN>::searchTree(value_type0 k, const Compare & cmp) {
      //  std::cout << k.first << '\n';
        return searchTreeHelper(this->root, k, cmp);
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    template<class InputIterator>
    RBTree<T, Compare, Alloc, AllocN>::RBTree(InputIterator first, InputIterator last,
                                              const key_compare &comp,
                                              const allocator_type &alloc,
                                              const allocator_type_N &allocN,
                                              typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type*)
                                              :_alloc(alloc), _allocN(allocN), _compare(comp), _size(0) {

        TNULL=_allocN.allocate(1);
        _allocN.construct(TNULL, value_type_node(nullptr) );
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
        _end = _allocN.allocate(1);
        _allocN.construct(_end, value_type_node(nullptr));
        _end->left = root;
        _end->right = nullptr;
        root->parent = _end;


        while (!(first == last)){

            this->insert_map(*first, comp);
            ++first;

        }

    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::const_iterator RBTree<T, Compare, Alloc, AllocN>::begin() const {
        pointer     node = root;
        while (node->left != TNULL) {
            node = node->left;
        }

        return iterator(node);
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::iterator RBTree<T, Compare, Alloc, AllocN>::end() {
       return iterator((_end));
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::reverse_iterator RBTree<T, Compare, Alloc, AllocN>::rbegin() {
        return (reverse_iterator(end()));
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::const_reverse_iterator RBTree<T, Compare, Alloc, AllocN>::rbegin() const {
        return (const_reverse_iterator(end()));
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::reverse_iterator RBTree<T, Compare, Alloc, AllocN>::rend() {
       return (reverse_iterator(begin()));
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::const_reverse_iterator RBTree<T, Compare, Alloc, AllocN>::rend() const {
        return (const_reverse_iterator(begin()));
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::const_iterator RBTree<T, Compare, Alloc, AllocN>::end() const {
        return iterator((_end));
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    RBTree<T, Compare, Alloc, AllocN> &RBTree<T, Compare, Alloc, AllocN>::operator=(const RBTree &x) {
        clear();
        iterator    it_begin = x.begin();
        iterator    it_end = x.end();
        while (!(it_begin == it_end)){
            this->insert(*it_begin);
            ++it_begin;
        }
        _size = x._size;

        return (*this);
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    size_t RBTree<T, Compare, Alloc, AllocN>::size() const {
        return _size;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    bool RBTree<T, Compare, Alloc, AllocN>::empty() const {
        return (_size == 0);
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    size_t RBTree<T, Compare, Alloc, AllocN>::max_size() const {
       return _alloc.max_size()/5;
    }


    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::insert(const RBTree::value_type0 &val, const Compare & cmp) {
    //pair<typename RBTree<T, Compare, Alloc, AllocN>::iterator, bool> RBTree<T, Compare, Alloc, AllocN>::insert(const RBTree::value_type0

       //remove pointer to _end
       if (root)
           root->parent = nullptr;
       // Ordinary Binary Search Insertion

       T *p = _alloc.allocate(1);
       _alloc.construct(p, val);

       pointer    node = _allocN.allocate(1);
       _allocN.construct(node, (p)); //todo 0

       node->parent = nullptr;
       node->left = TNULL;
       node->right = TNULL;
       node->color = 1; // new node must be red

       pointer y = nullptr;
       pointer x = this->root;
       while (x != TNULL) {
           y = x;
           if ((node->getT()) == (x->getT()))
           {
               _alloc.destroy(node->data);
               _alloc.deallocate(node->data, 1);

               _allocN.destroy(node);
               _allocN.deallocate(node, 1);
               return ;
           }
           if (cmp(*(node->data)), *(x->data)) {
               x = x->left;
           } else {
               x = x->right;
           }
       }
       ++_size;
       // y is parent of x
       node->parent = y;
       if (y == nullptr) {
           root = node;
       } else if (cmp((node->getT()), (y->getT()))) {
           y->left = node;
       } else {
           y->right = node;
       }
       // if new node is a root node, simply return

       if (node->parent == nullptr){
           node->color = 0;
         return ;
       }

       // if the grandparent is null, simply return
       if (node->parent->parent == nullptr) {
           return ;
       }
       // Fix the tree
       fixInsert(node);


       //restore pointer to _end

       root->parent = _end;
       _end->left = root;
     return ;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::printMlaureen() {
        std::cout << "+++++++++++++++++++++" << '\n' << '\n';
        _printM(root, 0);
        std::cout << "\n+++++++++++++++++++++" << '\n';
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::_printM(RBTree::pointer the_node, int place) {
        if (the_node == TNULL)
            return;
        place += 5;
        _printM(the_node->right, place);
        for(int i = 5; i < place; i++)
            std::cout << " ";
        std::cout << (the_node->data->first) << "," << (the_node->data->second)  << (the_node->color == 1 ? " R" : " B") <<'\n';
        _printM(the_node->left, place);
    }
    // pair<typename RBTree<T, Compare, Alloc, AllocN>::iterator, bool>
    template<typename T, typename Compare, typename Alloc, typename AllocN>
    int RBTree<T, Compare, Alloc, AllocN>::insert_map(const RBTree::value_type0 &val, const Compare &cmp) {
        //remove pointer to _end
        if (root)
            root->parent = nullptr;

        // Ordinary Binary Search Insertion
        //pointer node = new Node<T, Alloc>();

        T *p = _alloc.allocate(1);
        _alloc.construct(p, val);
        pointer    node = _allocN.allocate(1);
        _allocN.construct(node, (p));

        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1; // new node must be red

        pointer y = nullptr;
        pointer x = this->root;
        while (x != TNULL) {
            y = x;
            if (!cmp(node->getT(), x->getT()) && !cmp(x->getT(), node->getT()))
            {

                _alloc.destroy(node->data);
                _alloc.deallocate(node->data, 1);

                _allocN.destroy(node);
                _allocN.deallocate(node, 1);
                root->parent = _end;
                _end->left = root;
                return 0;
            }
            if (cmp(*(node->data), *(x->data))) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        ++_size;
        // y is parent of x
        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (cmp(*(node->data), *(y->data))) {
            y->left = node;
        } else {
            y->right = node;
        }
        // if new node is a root node, simply return

        if (node->parent == nullptr){
            node->color = 0;
            root->parent = _end;
            _end->left = root;
            return 1;

        }

        // if the grandparent is null, simply return
        if (node->parent->parent == nullptr) {
            root->parent = _end;
            _end->left = root;
            return 1;

        }
        // Fix the tree
        fixInsert(node);

                //restore pointer to _end

        root->parent = _end;
        _end->left = root;

       return 1;
   }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    template<class InputIterator>
    void RBTree<T, Compare, Alloc, AllocN>::insert(InputIterator first, InputIterator last, const key_compare& comp, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type*) {
        while (!(first == last)){
            this->insert_map(*first, comp);
            ++first;
        }
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::erase(RBTree::iterator position, const key_compare& comp) {

        if (_size == 0)
            return ;
        deleteNode(*position, comp);
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::size_type RBTree<T, Compare, Alloc, AllocN>::erase(const value_type0 &k, const key_compare& comp) {

        if (_size == 0)
            return 0;
        return (deleteNode(k), comp);
    }
    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::erase(RBTree::iterator first, RBTree::iterator last, const key_compare& comp) {
        if (_size == 0)
            return ;

        iterator temp;
        iterator e = end();

        while (!(first == last)){
            temp = first;
            if (temp != e)
                ++temp;
            else
                return ;
            erase(first, comp);
            first = temp;
        }
    }

    template<typename T>
    void change(T &x, T &y) {
        T   temp;
        temp = x;
        x = y;
        y = temp;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::swap(RBTree &x) {
        change(_alloc, x._alloc);
        change(_allocN, x._allocN);
        change(root, x.root);
        change(TNULL, x.TNULL);
        change(_size, x._size);
        change(_end, x._end);
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    void RBTree<T, Compare, Alloc, AllocN>::clear(const key_compare& comp) {
     //   if (_size == 0)
      //     return ;
        erase(begin(), end(), comp);
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::size_type RBTree<T, Compare, Alloc, AllocN>::count(const value_type0 &k, const Compare & cmp) const {

        iterator temp;
        iterator e = end();
        iterator b = begin();
                while (!(e == b)){
                    temp = b;
                    if (temp != e)
                        ++temp;
                    else
                        return 0;

                    if (!cmp(*b, k) && !cmp(k, *b))
                        return 1;
                    b = temp;
                }
                return 0;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::iterator RBTree<T, Compare, Alloc, AllocN>::lower_bound(const value_type0  &k, const Compare & cmp) {
        iterator temp;
        iterator e = end();
        iterator b = begin();
        while (!(e == b)){
            temp = b;
            if (temp != e)
                ++temp;
            else
                return temp;
            if (!cmp(*b, k) && !cmp(k, *b))
                return b;
            else if (!(cmp(*b, k)))
                return b;
            b = temp;
        }
        return b;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::iterator RBTree<T, Compare, Alloc, AllocN>::find_map(const value_type0 &k, const Compare &cmp) {
        pointer temp;
        temp = searchTree(k, cmp);
        if (temp == TNULL)
            return iterator(_end);
        return iterator(temp);
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::iterator RBTree<T, Compare, Alloc, AllocN>::upper_bound(const value_type0 &k, Compare cmp) const {
        iterator temp;
        iterator e = end();
        iterator b = begin();
        while (!(e == b)){
            temp = b;
            if (temp != e)
                ++temp;
            else
                return temp;
            if (cmp(k, *b))
                return b;
            b = temp;
        }
        return b;
    }

    template<typename T, typename Compare, typename Alloc, typename AllocN>
    typename RBTree<T, Compare, Alloc, AllocN>::const_iterator RBTree<T, Compare, Alloc, AllocN>::lower_bound(const value_type0 &k, Compare cmp) const {
        iterator temp;
        iterator e = end();
        iterator b = begin();
        while (!(e == b)){
            temp = b;
            if (temp != e)
                ++temp;
            else
                return temp;
            if (*(b) == k)
                return b;
            else if (!(cmp(*b, k)))
                return b;
            b = temp;
        }
        return b;
    }

} // ft

#endif