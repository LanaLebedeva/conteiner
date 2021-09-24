/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:04:10 by mlaureen          #+#    #+#             */
/*   Updated: 2021/07/09 12:20:14 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

class T;

class InputIterator;

#include <memory>
#include <iostream>
#include <cmath>

#include <stddef.h>

#include "vectorIterator.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:

	    typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef value_type&                                 reference;
        typedef const value_type&                           const_reference;
        typedef value_type*                                 pointer;
        typedef const value_type*                           const_pointer;
        typedef vectorIterator<T, T*, T&>                   iterator;
        typedef vectorIterator<T, const T*, const T&>       const_iterator;
        typedef ft::reverse_iterator<iterator>              reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>        const_reverse_iterator;
        typedef ptrdiff_t                                   difference_type;
        typedef size_t                                      size_type;


    //private:
    protected:
		T*		_arr;
		size_t	_size;
		size_t	_capacite;
		Alloc	_alloc;


	public:
		// empty container constructor (default constructor)
        explicit vector(const Alloc &alloc = Alloc());
        //fill constructor
        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
        //range constructor
        template <class InputIterator>
        vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type(),  typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0);
        //copy constructor
        vector(vector const &ths);

        //Vector destructor
        ~vector();
        vector & operator=(vector const & ths);


        //Capacity!
        size_type size() const;
        size_type max_size () const;
        void resize (size_type n, value_type val = value_type());
        size_type capacity() const;
        bool empty() const;
        void reserve (size_type n);

        //Element access:
        reference operator[] (size_type n);
        const_reference operator[] (size_type n) const;
        reference at (size_type n);
        const_reference at (size_type n) const;
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;

        //Modifiers
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0);
        //fill
        void assign(size_type n, const value_type& val);
		void push_back(const value_type& value);
   		void pop_back();

   		reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;

   		//single element
        iterator insert (iterator position, const value_type& val);
        //fill (2)
        void insert (iterator position, size_type n, const value_type& val);
        //range (3)
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0);

        iterator erase (iterator position);
        iterator erase (iterator first, iterator last);


        //iterator
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;


        void swap (vector& x);
        void clear();

        //Allocator:
        allocator_type get_allocator() const;
        bool checkLess(const vector & x) const;
	private:
	    size_type _equalStr(size_type len)
	    {
	        double x = static_cast<double>(len - 1);
	        unsigned int *answer = reinterpret_cast<unsigned int*>(&x);
	        ++answer;
	        *answer = 1 << (((*answer & 0x7FF00000) >> 20) - 1022);
	        return *answer;
	    }
    };

    //Non-member function overloads
    //relational operators (vector)
    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i != lhs.size(); ++i)
            if (lhs[i] != rhs[i])
                return false;
        return true;
    }

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator  < (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        size_t nl=lhs.size();
        size_t nr=rhs.size();
        if (nl == 0 && nr != 0)
            return true;
        else if (nl == 0)
            return false;
        else if (nr == 0)
            return false;
        return lhs.checkLess(rhs);
        }


    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
    return !(lhs > rhs);
    }

    template <class T, class Alloc>
    bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs < rhs);
    }

    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
    {
        x.swap(y);
    }

    template<typename T, typename Alloc>
    vector<T, Alloc>::vector(const Alloc &alloc): _size(0), _capacite(0), _alloc(alloc) {
        _arr = _alloc.allocate(_capacite);
    }

    template<typename T, typename Alloc>
    vector<T, Alloc>::vector(vector::size_type n, const value_type &val, const allocator_type &alloc)
            : _size(n), _capacite(n), _alloc(alloc) {
                _arr = _alloc.allocate(_capacite); // !!!!!
                        class less {
                    bool operator() (const T& x, const T& y) const;
                };
                for (size_type i = 0; i < _size; ++i)
                    _alloc.construct(&_arr[i], val);
        }

    template<typename T, typename Alloc>
    vector<T, Alloc>::vector(const vector &ths) {
        {
            try
            {
                _arr = _alloc.allocate(ths._capacite);
            }
            catch (const std::bad_alloc& e)
            {
                std::cerr << "Allocate failed:" << e.what() << std::endl;
                throw;
            }
            size_type i = 0;
            try
            {
                for (; i < ths._size; ++i)
                    push_back(ths._arr[i]);
            }
            catch (...)
            {
                for (size_type j = 0; j < i; j++)
                    _alloc.destroy(&_arr[i]);
                std::cerr << "push_back failed. copy " << (i+1) << "element(s)" << std::endl;
                throw;
            }
            if (_alloc != ths._alloc)
                _alloc = ths._alloc;
            _size = ths._size;
            _capacite = ths._capacite;
        }
    }

    template<typename T, typename Alloc>
    vector<T, Alloc>::~vector() {
        for (size_type i = 0; i < _size; ++i)
            _alloc.destroy(&_arr[i]);
        _alloc.deallocate(_arr, _capacite);
    }

    template<typename T, typename Alloc>
    vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &ths) {
        if (this != &ths)
        {
            pointer temp = _arr;
            size_type sizeTemp = _size;
            try
            {
                _arr = _alloc.allocate(ths._capacite);
            }
            catch (const std::bad_alloc& e)
            {
                std::cerr << "Allocate failed:" << e.what() << std::endl;
                throw;
            }
            size_type i = 0;
            try
            {
                for (; i < ths._size; ++i)
                    push_back(ths._arr[i]);
            }
            catch (...)
            {
                for (size_type j = 0; j < i; j++)
                    _alloc.destroy(&_arr[i]);
                _arr = temp;
                std::cerr << "push_back failed. copy " << (i+1) << "element(s)" << std::endl;
                throw;
            }
            for (size_type j = 0; j < sizeTemp ; ++j)
                _alloc.destroy(&temp[j]);
            _alloc.deallocate(temp, _capacite);
            if (_alloc != ths._alloc)
                _alloc = ths._alloc;
            _size = ths._size;
            _capacite = ths._capacite;
        }
        return *this;

    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const {
        return _size;
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const {
        if (sizeof(value_type) == 1)
            return _alloc.max_size()/2;
        return _alloc.max_size();
    }

    template<typename T, typename Alloc>
    void vector<T, Alloc>::resize(vector::size_type n, value_type val) {
        if (n > _capacite)
            reserve(2 * n);
        while (n < _size)
            pop_back();
        while (n > _size)
            push_back(val);
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const {
        return _capacite;
    }

    template<typename T, typename Alloc>
    bool vector<T, Alloc>::empty() const {
        if (_size == 0)
            return true;
        return false;
    }

    template<typename T, typename Alloc>
    void vector<T, Alloc>::reserve(vector::size_type n) {
        if (n <= _capacite)
            return ;
        T* newarr = _alloc.allocate(n);
        for (size_t i = 0; i <_size; ++i )
            _alloc.construct(&newarr[i], _arr[i]);
        this->~vector();
        _arr = newarr;
        _capacite = n;
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](vector::size_type n) {
        return _arr[n];
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](vector::size_type n) const {
        return _arr[n];
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::at(vector::size_type n) {
        if (n >= _size)
            throw std::out_of_range("ft_vector out of range");
        return _arr[n];
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(vector::size_type n) const {
        if (n >= _size)
            throw std::out_of_range("ft_vector out of range");
        return _arr[n];
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
        return (_arr[0]);
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
        return _arr[0];
    }

    template<typename T, typename Alloc>
    typename vector<T,Alloc>::reference vector<T, Alloc>::back() {
        return _arr[_size - 1];
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
        return _arr[_size - 1];
    }

    template<typename T, typename Alloc>
    void vector<T, Alloc>::assign(vector::size_type n, const value_type &val) {
        while (_size != 0)
            pop_back();
        if (n > _capacite) {
            _capacite *= 2;
            _arr = _alloc.allocate(_capacite);
        }

        while ((n) != _size)
            push_back(val);

    }

    template<typename T, typename Alloc>
    void vector<T, Alloc>::push_back(const T &value) {
        if (_size + 1 > _capacite)
            reserve(_size == 0 ? 1 :  2 * _capacite);
        _alloc.construct(&_arr[_size], value);
        ++_size;
    }

    template<typename T, typename Alloc>
    void vector<T, Alloc>::pop_back() {
        --_size;
        _alloc.destroy(&(_arr[_size]));
    }

    template<typename T, typename Alloc>
    void vector<T, Alloc>::swap(vector &x) {
        pointer tmp = _arr;
        _arr = x._arr;
        x._arr = tmp;
        size_type t;
        t = _size;
        _size = x._size;
        x._size = t;
        t = _capacite;
        _capacite = x._capacite;
        x._capacite = t;
        Alloc tAlloc;
        tAlloc = _alloc;
        _alloc = x._alloc;
        x._alloc = tAlloc;
    }

    template<typename T, typename Alloc>
    void vector<T, Alloc>::clear() {
        while (_size != 0)
            pop_back();
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const {
        return (_alloc); //    new Alloc(_alloc)
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
        return ft::vector<T,Alloc>::iterator(&(_arr[0]));
    }

    template<typename T, typename Alloc>
    typename vector<T,Alloc>::const_iterator vector<T, Alloc>::begin() const {
        return ft::vector<T, Alloc>::const_iterator(&(_arr[0]));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
        return ft::vector<T, Alloc>::iterator(&(_arr[_size]));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
        return ft::vector<T, Alloc>::const_iterator(&(_arr[_size]));
    }

    template<typename T, typename Alloc>
    template<class InputIterator>
    vector<T, Alloc>::vector(InputIterator first, InputIterator last,
                             const allocator_type &alloc,
                             typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type*):
                             _size(0), _capacite(0), _alloc(alloc) {
        ptrdiff_t       len = 0;
        len = last - first;
        _size = len;
        len = _equalStr(len); //https://forum.sources.ru/index.php?showtopic=227130
        _capacite = len;
        _arr = _alloc.allocate(len);
        for (size_t i = 0; i <_size; ++i, ++first)
            _alloc.construct(&_arr[i], *first);
    }

    template<typename T, typename Alloc>
    template<class InputIterator>
    void vector<T, Alloc>::assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type*) {
        clear();
        insert(begin(), first, last);
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(vector::iterator position, const value_type &val) {

        difference_type pos = position - begin();
        insert(position, 1, val);
        return (&_arr[pos]);
    }

    template<typename T, typename Alloc>
    void vector<T, Alloc>::insert(vector::iterator position, vector::size_type n, const value_type &val) {
        difference_type pos = position - begin();
        if (_size + n > _capacite){
            pointer tmp = _arr;
            _arr = _alloc.allocate(_equalStr(_size+ n));
            _capacite = _equalStr(_size + n);
            size_type i = 0;
            if (_size != 0)
                for (; i != static_cast<size_type >(pos); ++i){
                    _arr[i] = tmp[i];
                    _alloc.destroy(&tmp[i]);
                }
            _size +=n;
            // копировать с конца
            for (size_type j=_size - 1; j > i; --j){
                _arr[j] = tmp[j - n];
                _alloc.destroy(&tmp[j - n]);
            }
            for (size_type j = 0; j < n; ++j){
                _arr[i + j] = val;
            }
           _alloc.deallocate(tmp, i);
        } else {
            size_type i = static_cast<size_type>(pos);
            _size += n;
            // copy from the end
            for (size_type j = _size - 1; j > i; --j) {
                _arr[j] = _arr[j - n];
            }
            for (size_type j = 0; j < n; ++j) {
                _arr[i + j] = val;
            }
        }
    }

    template<typename T, typename Alloc>
    template<class InputIterator>
    void vector<T, Alloc>::insert(vector::iterator position, InputIterator first, InputIterator last,
                                  typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type*) {
        ptrdiff_t       n = 0;
        difference_type len = position - begin();
        n = last - first;
        if ((_size + n) > _capacite) {
            pointer tmp = _arr;
            _arr = _alloc.allocate(_equalStr(_size + n));
            _capacite = _equalStr(_size + n);
            size_type i = 0;
            if (_size != 0) {
                for (; i < static_cast<size_type>(len); ++i) {
                    _alloc.construct(&_arr[i], tmp[i]);
                    _alloc.destroy(&tmp[i]);
                }
            }
            _size +=n;
            // copy from the end
            for (size_type j=_size - 1; j > i; --j){
                _alloc.construct(&_arr[j], tmp[j - n]);
                _alloc.destroy(&tmp[j - n]);
            }
            for (size_type j = 0; j < static_cast<size_type >(n); ++j, ++first){
                _alloc.construct(&(_arr[i + j]), (*first));
            }
            _alloc.deallocate(tmp, i);
            }
        else {
            size_type i = static_cast<size_type>(position - begin());
            _size += n;
            // copy from the end
            for (size_type j = _size - 1; j > i; --j) {
                _alloc.construct(&_arr[j], _arr[j - n]);
            }
            for (size_type j = 0; j < static_cast<size_type >(n); ++j, ++first) {
                _alloc.construct(&_arr[i + j], *first);
            }
        }
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(vector::iterator position) {
        return (vector<T, Alloc>::erase(position, position + 1));
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(vector::iterator first, vector::iterator last) {
        difference_type pos = first - begin();
        if (first == end() || first == last)
            return first;

        size_type tmp = _size - (last - first);
        while (last != end())
        {
            _alloc.destroy(&(*first));
            _alloc.construct(&(*first), *last);
            ++first;
            ++last;
        }
        _size = tmp;
        return iterator(&_arr[pos]);
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin() {

        return reverse_iterator(end());
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const {
        return ft::vector<T, Alloc>::const_reverse_iterator(end());
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() {
        return ft::vector<T, Alloc>::reverse_iterator(begin());
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const {

        return ft::vector<T, Alloc>::const_reverse_iterator(begin());
    }

    template<typename T, typename Alloc>
    bool vector<T, Alloc>::checkLess(const vector &x) const {
        size_t nl=_size;
        size_t nr=x.size();
        size_t i;
        for (i = 0; i < nl && i < nr; ++i){
            if (_arr[i] > x._arr[i])
                return false;
        }
        return true;
      }

};
#endif
		 