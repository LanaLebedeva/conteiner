/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 13:47:11 by mlaureen          #+#    #+#             */
/*   Updated: 2021/07/15 13:47:13 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
#define VECTORITERATOR_HPP

#include "iterator.hpp"

class T;


template <class T, class Pointer = T*, class Reference = T& >
class vectorIterator {
public:

    typedef ft::random_access_iterator_tag  iterator_category;
    typedef T                               value_type;
    typedef Pointer                         pointer;
    typedef Reference                       reference;


    vectorIterator() {};
    ~vectorIterator() {};

    template<class NPointer, class NReference>
    vectorIterator<T, Pointer, Reference> & operator=(const vectorIterator<T, NPointer, NReference> & ths);

    template<class NPointer, class NReference>
    vectorIterator<T, Pointer, Reference>(vectorIterator<T, NPointer, NReference> const &ths);

    template<class NPointer, class NReference>
    vectorIterator(vectorIterator<T, NPointer, NReference> const *ths);

    vectorIterator(pointer ptr);

    bool operator<(const vectorIterator &rhs) const;
    bool operator>(const vectorIterator &rhs) const;
  	bool operator<=(const vectorIterator &rhs) const;
  	bool operator>=(const vectorIterator &rhs) const;
    bool operator==(const vectorIterator &rhs) const;
    bool operator!=(const vectorIterator &rhs) const;

    vectorIterator operator++();
    const vectorIterator operator++(int);
    vectorIterator operator--();
    const vectorIterator operator--(int);
    vectorIterator operator+(ptrdiff_t n);
    vectorIterator operator-(ptrdiff_t n);

    reference operator*() const;
    pointer operator->() const;
    ptrdiff_t operator-(const vectorIterator &rhs) const;
    vectorIterator operator-=(ptrdiff_t n);
    vectorIterator operator+=(ptrdiff_t n);
    reference operator[](int n) const;

    pointer getBasePtr() const;



private:
    T* _basePtr;
};

template<class T, class Pointer, class Reference>
template<class NPointer, class NReference>
vectorIterator<T, Pointer, Reference>::vectorIterator(const vectorIterator<T, NPointer, NReference> &ths) {
    _basePtr = const_cast<T*>(ths.getBasePtr());
}

template<class T, class Pointer, class Reference>
vectorIterator<T, Pointer, Reference>::vectorIterator(pointer ptr) {
    this->_basePtr = ptr;
}

template<class T, class Pointer, class Reference>
bool vectorIterator<T, Pointer, Reference>::operator<(const vectorIterator &rhs) const {
    return _basePtr < rhs._basePtr;
}

template<class T, class Pointer, class Reference>
bool vectorIterator<T, Pointer, Reference>::operator>(const vectorIterator &rhs) const {
    return rhs._basePtr < _basePtr;
}

template<class T, class Pointer, class Reference>
bool vectorIterator<T, Pointer, Reference>::operator<=(const vectorIterator &rhs) const {
    return rhs._basePtr >= _basePtr;
}

template<class T, class Pointer, class Reference>
bool vectorIterator<T, Pointer, Reference>::operator>=(const vectorIterator &rhs) const {
    return _basePtr >= rhs._basePtr;
}

template<class T, class Pointer, class Reference>
bool vectorIterator<T, Pointer, Reference>::operator==(const vectorIterator &rhs) const {
    return _basePtr == rhs._basePtr;
}

template<class T, class Pointer, class Reference>
bool vectorIterator<T, Pointer, Reference>::operator!=(const vectorIterator &rhs) const {
    return rhs._basePtr != _basePtr;
}

template<class T, class Pointer, class Reference>
vectorIterator<T, Pointer,Reference> vectorIterator<T, Pointer, Reference>::operator++() {
    ++_basePtr;
    return *this;
}

template<class T, class Pointer, class Reference>
const vectorIterator<T, Pointer, Reference> vectorIterator<T, Pointer, Reference>::operator++(int) {
    vectorIterator temp(*this);
    ++(*this);
    return temp;
}

template<class T, class Pointer, class Reference>
vectorIterator<T, Pointer, Reference> vectorIterator<T, Pointer, Reference>::operator--() {
    --_basePtr;
    return *this;
}

template<class T, class Pointer, class Reference>
const vectorIterator<T, Pointer, Reference> vectorIterator<T, Pointer, Reference>::operator--(int) {
    vectorIterator temp(*this);
    --(*this);
    return temp;
}

template<class T, class Pointer, class Reference>
vectorIterator<T, Pointer, Reference> vectorIterator<T, Pointer, Reference>::operator+(ptrdiff_t n) {
    vectorIterator it(*this);
   // std::cout << "vectorIterator +n";
    if (n > 0) {
        for (ptrdiff_t i = 0; i < n; ++i)
            ++(it._basePtr);
    }
    else {
        for (ptrdiff_t i = n - 1; i != 0; --i)
            --(it._basePtr);
    }
    return it;
}

template<class T, class Pointer, class Reference>
vectorIterator<T, Pointer, Reference> vectorIterator<T, Pointer, Reference>::operator-(ptrdiff_t n) {
    vectorIterator it(*this);
    if (n >= 0) {
        for (ptrdiff_t i = 0; i < n; ++i)
            --(it._basePtr);
    }
    else {
        for (ptrdiff_t i = n - 1; i != 0; --i)
            ++(it._basePtr);
    }
    return it;
}

template<class T, class Pointer, class Reference>
typename vectorIterator<T, Pointer, Reference>::reference vectorIterator<T, Pointer, Reference>::operator*() const {
    return (*_basePtr);
}

template<class T, class Pointer, class Reference>
typename vectorIterator<T, Pointer, Reference>::pointer vectorIterator<T, Pointer, Reference>::operator->() const {
    return _basePtr;
}

template<class T, class Pointer, class Reference>
ptrdiff_t vectorIterator<T, Pointer, Reference>::operator-(const vectorIterator &rhs) const {
    return (_basePtr - rhs._basePtr);
}

template<class T, class Pointer, class Reference>
vectorIterator<T, Pointer, Reference> vectorIterator<T, Pointer, Reference>::operator-=(ptrdiff_t n) {
    if (n > 0) {
        for (ptrdiff_t i = 0; i < n; ++i)
            --_basePtr;
    }
    else {
        for (ptrdiff_t i = n ; i != 0; ++i)
            ++_basePtr;
    }
    return *this;
}

template<class T, class Pointer, class Reference>
vectorIterator<T, Pointer,Reference> vectorIterator<T, Pointer, Reference>::operator+=(ptrdiff_t n) {
    if (n > 0) {
        for (ptrdiff_t i = 0; i < n; ++i)
            ++_basePtr;
    }
    else {
        for (ptrdiff_t i = n ; i != 0; ++i)
            --_basePtr;
    }
    return *this;
}

template<class T, class Pointer, class Reference>
typename vectorIterator<T, Pointer, Reference>::reference vectorIterator<T, Pointer, Reference>::operator[](int n) const {
    value_type* tmp(this->_basePtr);
    tmp += n;
    return (*tmp);
}

template<class T, class Pointer, class Reference>
template<class NPointer, class NReference>
vectorIterator<T, Pointer, Reference> &
vectorIterator<T, Pointer, Reference>::operator=(const vectorIterator<T, NPointer, NReference> &ths) {
    this->_basePtr = ths._basePtr;
    return (*this);
}

template<class T, class Pointer, class Reference>
typename vectorIterator<T,Pointer, Reference>::pointer vectorIterator<T, Pointer, Reference>::getBasePtr() const {
    return _basePtr;
}

template<class T, class Pointer, class Reference>
template<class NPointer, class NReference>
vectorIterator<T, Pointer, Reference>::vectorIterator(const vectorIterator<T, NPointer, NReference> *ths) {
    _basePtr = ths->getBasePtr();
}

template <class T, class Pointer, class Reference>
vectorIterator<T, Pointer, Reference> operator+(ptrdiff_t n, vectorIterator<T, Pointer, Reference> it)
{
    return (it + n);
}

#endif
