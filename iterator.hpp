/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 13:58:51 by mlaureen          #+#    #+#             */
/*   Updated: 2021/07/15 13:58:56 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stddef.h>
#include <iostream> // todo delete

//#include "RBTreeIterator.hpp"

namespace ft {
    class T;

    //class RBTreeIterator;

    //iterator categories:
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag: public input_iterator_tag {};
    struct bidirectional_iterator_tag: public forward_iterator_tag {};
    struct random_access_iterator_tag: public bidirectional_iterator_tag {};

    template<class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };
    template<class T>
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t                   difference_type;
        typedef T                           value;
        //typedef Node<T>                     value_type;
        typedef T*                          pointer;
        typedef T&                          reference;
        typedef random_access_iterator_tag  iterator_category;
    };
    template<class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
    struct Iterator
    {
        //typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
       // typedef T                               value;
       // typedef Node<T>                         value_type;
       // typedef value_type*                     pointer;
       // typedef value_type&                     reference;
    };

    template<typename Iterator>
    class reverse_iterator { //: public RBTreeIterator<T, T*, T&> {

    public:

        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer  pointer;
      //  typedef typename Iterator::pointer_node pointer_node;
        typedef typename Iterator::reference reference;
       //
       // typedef typename Iterator::value value;
        typedef Iterator iterator_type;


        reverse_iterator(): _currentIterator(Iterator()){};
        reverse_iterator(const iterator_type itr) {//: _currentIterator(itr){}; //{std::cout <<" 1314513451346 " << (*(itr)) <<'\n';};
            _currentIterator =  itr.getBasePtr();
           //_currentIterator = itr;
        }
        //reverse_iterator(iterator_type itr) { *this = itr; }
        reverse_iterator(const reverse_iterator & itr): _currentIterator(itr._currentIterator) {};

        ~reverse_iterator() {};

        reference & operator*() const;
        reverse_iterator operator++();
        reverse_iterator operator++(int);
        reverse_iterator operator--();
        reverse_iterator operator--(int);

        reverse_iterator operator+(ptrdiff_t n) const;
        reverse_iterator& operator+= (ptrdiff_t n);
        reverse_iterator operator-(ptrdiff_t n) const;
        reverse_iterator& operator-= (ptrdiff_t n);
        pointer operator->() const;

        template<class CIterator>
        reverse_iterator& operator= (const reverse_iterator<CIterator>& rev_it);
        iterator_type base() const;
        value_type & operator[] (ptrdiff_t n) const;
        iterator_type getCurrentIterator() const {return (_currentIterator);}


    protected:
        Iterator    _currentIterator;

    };

    template <class Iterator, class CIterator>
    bool operator== (const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<CIterator>& rhs) {
        return (lhs.getCurrentIterator() == rhs.getCurrentIterator());
    }

    template <class Iterator, class CIterator>
    bool operator!= (const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<CIterator>& rhs) {
        return (lhs.getCurrentIterator() != rhs.getCurrentIterator());
    }

    template <class Iterator, class CIterator>
    bool operator<  (const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<CIterator>& rhs) {
        return lhs.getCurrentIterator() < rhs.getCurrentIterator();
    }

    template <class Iterator, class CIterator>
    bool operator<= (const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<CIterator>& rhs)  {
        return lhs.getCurrentIterator() <= rhs.getCurrentIterator();
    }

    template <class Iterator, class CIterator>
    bool operator>  (const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<CIterator>& rhs) {
        return lhs.getCurrentIterator() > rhs.getCurrentIterator();
    }

    template <class Iterator, class CIterator>
    bool operator>= (const reverse_iterator<Iterator>& lhs,
                     const reverse_iterator<CIterator>& rhs) {
        return lhs.getCurrentIterator() >=rhs.getCurrentIterator();
    }


    template<typename Iterator>
    reverse_iterator<Iterator> reverse_iterator<Iterator>::operator++() {
        Iterator    tmp = this->base();
        --tmp;
        *this= reverse_iterator(tmp);

       return (*(this));
    }

    template<typename Iterator>
    typename reverse_iterator<Iterator>::reference &reverse_iterator<Iterator>::operator*() const {
        return (*(--base()));
    }

    template<typename Iterator>
    reverse_iterator<Iterator> reverse_iterator<Iterator>::operator++(int) {

        reverse_iterator    temp(*this);
        --(*this);
        return temp;
    }

    template<typename Iterator>
    reverse_iterator<Iterator> reverse_iterator<Iterator>::operator--() {
        Iterator tmp(this->base());
        ++tmp;
        *this = tmp;
        return (*this);
    }

    template<typename Iterator>
    reverse_iterator<Iterator> reverse_iterator<Iterator>::operator--(int) {
        reverse_iterator    temp(*this);
        ++(*this);
        return temp;
    }

    template<typename Iterator>
    reverse_iterator<Iterator> reverse_iterator<Iterator>::operator+(ptrdiff_t n) const {
       reverse_iterator temp(*this);
       if (n >= 0) {
           for (ptrdiff_t i = 0; i < n; ++i)
               --(temp);
       }
       else {
           for (ptrdiff_t i = n - 1; i != 0; --i)
               ++(temp);
       }
       return (temp);
   }

    template<typename Iterator>
    reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator+=(ptrdiff_t n) {
        if (n >= 0) {
            for (ptrdiff_t i = 0; i < n; ++i)
                --(*this);
        }
        else {
            for (ptrdiff_t i = n - 1; i != 0; --i)
                ++(*this);
        }
        return (this);
    }

    template<typename Iterator>
    reverse_iterator<Iterator> reverse_iterator<Iterator>::operator-(ptrdiff_t n) const {
        reverse_iterator temp(*this);
        if (n >= 0) {
            for (ptrdiff_t i = 0; i < n; ++i)
                --(temp);
        }
        else {
            for (ptrdiff_t i = n - 1; i != 0; --i)
                ++(temp);
        }
        return (temp);
    }

    template<typename Iterator>
    reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator-=(ptrdiff_t n) {
       if (n >= 0) {
           for (ptrdiff_t i = 0; i < n; ++i)
               --(*this);
       }
       else {
           for (ptrdiff_t i = n - 1; i != 0; --i)
               ++(*this);
       }
       return (this);
    }

    template<typename Iterator>
    typename reverse_iterator<Iterator>::pointer reverse_iterator<Iterator>::operator->() const {
        return &(operator*());
    }

    template<typename Iterator>
    template<typename CIterator>
    reverse_iterator<Iterator> &reverse_iterator<Iterator>::operator=(const reverse_iterator<CIterator> &rev_it) {
        _currentIterator = rev_it._currentIterator;
        return *this;
    }

    template<typename Iterator>
    typename reverse_iterator<Iterator>::iterator_type reverse_iterator<Iterator>::base() const {
       return _currentIterator;
    }

    template<typename Iterator>
    typename reverse_iterator<Iterator>::value_type & reverse_iterator<Iterator>::operator[](ptrdiff_t n) const {
        Iterator temp(this->base());

        temp += n + 1;
        return (*((temp.getBasePtr())->data));
    }

}; //namespace ft

#endif
