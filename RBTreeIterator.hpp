/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTreeterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 09:17:00 by mlaureen          #+#    #+#             */
/*   Updated: 2021/08/04 13:05:16 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREEITERATOR_HPP
#define RBTREEITERATOR_HPP

#include <iostream>

namespace ft {
    #include "iterator.hpp"
    #include "RBtree.hpp"


    class T;

    template <class T, class Pointer = T*, class Reference = T&>
    class RBTreeIterator {
    public:
        typedef std::bidirectional_iterator_tag  iterator_category;
        typedef T                               value_type;
        typedef Node<T>                         value_type_node;
        typedef value_type *                    pointer; // было value_type
        typedef value_type_node *               pointer_node;
        typedef value_type &                      reference;


        RBTreeIterator() {};
        ~RBTreeIterator() {};
        template<class NPointer, class NReference>
        RBTreeIterator<T, Pointer, Reference> & operator=(const RBTreeIterator<T, NPointer, NReference> & ths);

        template<class NPointer, class NReference>
        RBTreeIterator<T, Pointer, Reference>(RBTreeIterator<T, NPointer, NReference> const &ths);

        template<class NPointer, class NReference>
        RBTreeIterator(RBTreeIterator<T, NPointer, NReference> const *ths);

        RBTreeIterator(const pointer_node ptr);

        template<class CIterator>
        RBTreeIterator& operator= (const RBTreeIterator<CIterator>& rev_it);

        RBTreeIterator operator++();
        const RBTreeIterator operator++(int);
        RBTreeIterator operator--();
        const RBTreeIterator operator--(int);


        virtual reference operator*() const;
        pointer operator->() const;
        RBTreeIterator operator+=(ptrdiff_t n);

        pointer_node getBasePtr() const;

        private:

            pointer_node     _basePtr;

    };

    template<class T, class Pointer, class Reference, class CPointer, class CReference >
    bool operator==(const RBTreeIterator<T, Pointer, Reference> &lhs, const RBTreeIterator<T, CPointer, CReference> &rhs ) {
        return ((lhs.getBasePtr()) == (rhs.getBasePtr()));
    }
    template<class T, class Pointer, class Reference, class CPointer, class CReference >
    bool operator!=(const RBTreeIterator<T, Pointer, Reference> &lhs, const RBTreeIterator<T, CPointer, CReference> &rhs ) {
                return (lhs.getBasePtr() != rhs.getBasePtr());
            }




    template<class T, class Pointer, class Reference>
    typename RBTreeIterator<T, Pointer, Reference>::reference RBTreeIterator<T, Pointer, Reference>::operator*() const {
      return (*(_basePtr->data));
    }

    template<class T, class Pointer, class Reference>
    template<class NPointer, class NReference>
    RBTreeIterator<T, Pointer, Reference> &
    RBTreeIterator<T, Pointer, Reference>::operator=(const RBTreeIterator<T, NPointer, NReference> &ths) {
        this->_basePtr = ths._basePtr;
        return (*this);
    }

    template<class T, class Pointer, class Reference>
    template<class NPointer, class NReference>
    RBTreeIterator<T, Pointer, Reference>::RBTreeIterator(
            const RBTreeIterator<T, NPointer, NReference> &ths) {
        _basePtr = ths.getBasePtr();
    }

    template<class T, class Pointer, class Reference>
    template<class NPointer, class NReference>
    RBTreeIterator<T, Pointer, Reference>::RBTreeIterator(const RBTreeIterator<T, NPointer, NReference> *ths) {
        _basePtr = ths->getBasePtr();
    }

    template<class T, class Pointer, class Reference>
    RBTreeIterator<T, Pointer,Reference> RBTreeIterator<T, Pointer, Reference>::operator++() {
        if (!_basePtr)
            return *this;
        //Node<T>     *next;
        pointer_node        next;
        if (!_basePtr->right->right){
            next = _basePtr;
            while (next->parent && next == next->parent->right) { next = next->parent; }
            next = next->parent;
        }
        else {
            next = _basePtr->right;
            while (next->left->left)
                next = next->left;
        }
        _basePtr = next;
        return RBTreeIterator(_basePtr);
    }

    template<class T, class Pointer, class Reference>
    const RBTreeIterator<T,Pointer, Reference> RBTreeIterator<T, Pointer, Reference>::operator++(int) {
        RBTreeIterator  temp(*this);
        operator++();
        return RBTreeIterator(temp);
    }

    template<class T, class Pointer, class Reference>
    RBTreeIterator<T, Pointer, Reference> RBTreeIterator<T, Pointer, Reference>::operator--() {
        //Node<T> *next;
        pointer_node     next;
        if (!_basePtr->left->left)
        {
            next = _basePtr;
            while (next->parent && next == next->parent->left)
                next = next->parent;
            next = next->parent;
        }
        else{
            next = _basePtr->left;
            while(next->right->right)
                next = next->right;
        }
        _basePtr = next;
        return RBTreeIterator(_basePtr);
    }

    template<class T, class Pointer, class Reference>
    const RBTreeIterator<T, Pointer, Reference> RBTreeIterator<T, Pointer, Reference>::operator--(int) {
        RBTreeIterator  temp(*this);
        operator--();
        return RBTreeIterator(temp);
    }

    template<class T, class Pointer, class Reference>
    typename RBTreeIterator<T, Pointer, Reference>::pointer RBTreeIterator<T, Pointer, Reference>::operator->() const {
        return _basePtr->data;
    }

    template<class T, class Pointer, class Reference>
    //Node<T> *RBTreeIterator<T, Pointer, Reference>::getBasePtr() const {
    typename RBTreeIterator<T,Pointer, Reference>::pointer_node RBTreeIterator<T, Pointer, Reference>::getBasePtr() const {
        return (_basePtr);
    }

    template<class T, class Pointer, class Reference>
            RBTreeIterator<T, Pointer, Reference>::RBTreeIterator(const pointer_node ptr):_basePtr(ptr) {}

    template<class T, class Pointer, class Reference>
    RBTreeIterator<T, Pointer, Reference> RBTreeIterator<T, Pointer, Reference>::operator+=(ptrdiff_t n) {
        RBTreeIterator  temp(*this);
        if (n >= 0) {
            for (ptrdiff_t i = 0; i < n; ++i)
                --(temp);
        }
        else {
            for (ptrdiff_t i = n  ; i != 0; ++i)
                ++(temp);
        }
        this->_basePtr = temp._basePtr;
        return (*this);
    }

} //namespace ft

#endif
