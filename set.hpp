/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 13:30:32 by mlaureen          #+#    #+#             */
/*   Updated: 2021/08/13 13:30:35 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
#define SET_HPP
#include "RBtree.hpp"
#include "RBTreeIterator.hpp"
#include "utility.hpp"
#include "iterator.hpp"

class RBTree;

namespace ft{
template <class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
        class set: public RBTree<T,Compare, Alloc> {
        public:
            typedef T												value_type;
            typedef Compare         								key_compare;
            typedef Alloc											allocator_type;
            typedef typename ft::RBTreeIterator<value_type, value_type*, value_type&>          iterator;
            typedef typename ft::RBTreeIterator<value_type, const value_type*, const value_type&>   const_iterator;
            typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

            class value_compare
                    {
                    public:
                        typedef T   value_type;
                    private:
                        Compare cmp;
                    public:
                        explicit value_compare (Compare const & c) : cmp(c) {}  // constructed with map's comparison object
                        virtual ~value_compare() {}
                        bool operator() (const value_type &x, const value_type &y) const {
                            return (cmp(x, y));
                        }
                    };

        private:
            RBTree<value_type, key_compare, allocator_type>        _set;
        public:
        public:
            explicit set(const key_compare & cmp = Compare(), const allocator_type& alloc = allocator_type());
            template <class InputIterator>
            set(InputIterator first, InputIterator last,
                  const key_compare& comp = Compare(),
                  const allocator_type& alloc = allocator_type(),
                  typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0);
            set (const set& x, const key_compare& comp = Compare(),
                 const allocator_type& alloc = allocator_type());
            ~set() {}
            set& operator= (const set& x);
        //Iterators:
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

        //Element access:
        value_type & operator[] (const value_type & k); //начала делать, но не сделала

        //Modifiers:
        pair<iterator,bool> insert (const value_type& val, const key_compare & cmp = Compare());
        iterator insert (iterator position, const value_type& val, const key_compare & cmp = Compare());
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last, const key_compare& comp = Compare(),
                          typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0);
        void erase (iterator position, const key_compare& comp = Compare());
        size_t erase (const value_type & k, const key_compare& comp = Compare());
        void erase (iterator first, iterator last, const key_compare& comp = Compare());
        void swap (set& x);
        void clear(const key_compare& comp = Compare());

        //Observers:
        key_compare key_comp(const key_compare& comp = Compare()) const;
        value_compare value_comp(const key_compare& comp = Compare()) const;

        //Operations:
        iterator find (const value_type& k, const key_compare& comp = Compare());
        size_t count (const value_type& k, const key_compare& comp = Compare()) const;
        iterator lower_bound (const value_type& k, const key_compare& comp = Compare());
        iterator upper_bound (const value_type& k, const key_compare& comp = Compare());

        pair<iterator,iterator> equal_range (const value_type& k, const key_compare& comp = Compare()) const;
        allocator_type get_allocator(const allocator_type& alloc = allocator_type()) const;
    };
    template <class T, class Compare, class Alloc>
    bool operator== (const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs ) {
            if (lhs.size() != rhs.size())
                return false;
            if (lhs.size() == 0)
                return true;
            typename set<T, Compare, Alloc>::const_iterator itL = lhs.begin();
            typename set<T, Compare, Alloc>::const_iterator itR = rhs.begin();
            for (size_t i=0; i<lhs.size(); ++i, ++itL, ++itR) {
                if ((itL->first != itR->first) || (itL->second != itR->second))
                    return false;
            }
            return true;
        }

        template <class T, class Compare, class Alloc>
        bool operator!= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs ){
             return !(lhs == rhs);
        }

        template <class T, class Compare, class Alloc>
        bool operator<  ( const set<T,Compare,Alloc>& lhs,
                        const set<T,Compare,Alloc>& rhs ){
            size_t nl=lhs.size();
            size_t nr=rhs.size();
            if (nl == 0 && nr != 0)
                return true;
            else if (nl == 0)
                return false;
            else if (nr == 0)
                return false;
            typename set<T, Compare, Alloc>::const_iterator itl = lhs.begin();
            typename set<T, Compare, Alloc>::const_iterator itr = rhs.begin();
            size_t i;
            for (i = 0; i < nl && i < nr; ++i){
                if (itl->first > itr->first || itl->second > itr->second)
                    return false;
            }
            if (nl <= nr)
                return true;
            else
                return false;
        }

        template <class T, class Compare, class Alloc>
        bool operator<= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs ){
            return ((lhs < rhs) || (lhs == rhs));
        }
        template <class T, class Compare, class Alloc>
        bool operator>  ( const set<T,Compare,Alloc>& lhs,
                          const set<T,Compare,Alloc>& rhs ){
            return (!(lhs < rhs) && !(lhs == rhs));
        }

        template <class T, class Compare, class Alloc>
        bool operator>= ( const set<T,Compare,Alloc>& lhs,
                const set<T,Compare,Alloc>& rhs ){
            return ((lhs > rhs) || (lhs == rhs));
        }

        template <class T, class Compare, class Alloc>
                void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y){
                    x.swap(y);
                }

    template<class T, class Compare, class Alloc>
    set<T, Compare, Alloc>::set(const key_compare &cmp, const allocator_type &alloc):
        _set(RBTree<value_type, key_compare, allocator_type>(cmp, alloc)) { }

    template<class T, class Compare, class Alloc>
    template<class InputIterator>
    set<T, Compare, Alloc>::set(InputIterator first, InputIterator last, const key_compare &comp,
                                     const allocator_type &alloc,
                                     typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *):
                                     _set(RBTree<value_type, key_compare, allocator_type>(first, last, (comp), alloc)) {}

    template<class T, class Compare, class Alloc>
    set<T, Compare, Alloc>::set(const set &x, const key_compare &comp, const allocator_type &alloc):
    _set(RBTree<value_type, key_compare, allocator_type>((x.begin()), (x.end()), key_compare(comp), alloc)) {}

    template<class T, class Compare, class Alloc>
    set<T, Compare, Alloc> &set<T, Compare, Alloc>::operator=(const set &x) {
        if(this == &x)
            return *this;
        clear();
        if (x._set.size() == 0)
            return *this;
        iterator    it_begin = x.begin();
        iterator    it_end = x.end();
        insert(it_begin, it_end);
        this->_size = x._size;
        return *this;
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::begin() {
        return (_set.begin());
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::const_iterator set<T, Compare, Alloc>::begin() const {
        return (_set.begin());
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::end() {
        return (_set.end());
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::const_iterator set<T, Compare, Alloc>::end() const {
        return (_set.end());
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::reverse_iterator set<T, Compare, Alloc>::rbegin() {
        return ((_set.rbegin()));
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::const_reverse_iterator set<T, Compare, Alloc>::rbegin() const {
        return ((_set.rbegin()));
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::reverse_iterator set<T, Compare, Alloc>::rend() {
        return ((_set.rend()));
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::const_reverse_iterator set<T, Compare, Alloc>::rend() const {
        return ((_set.rend()));
    }

    template<class T, class Compare, class Alloc>
    bool set<T, Compare, Alloc>::empty() const {
        return (_set.empty());
    }

    template<class T, class Compare, class Alloc>
    size_t set<T, Compare, Alloc>::size() const {
        return (_set.size());
    }

    template<class T, class Compare, class Alloc>
    size_t set<T, Compare, Alloc>::max_size() const {
        return (_set.max_size());
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::value_type &set<T, Compare, Alloc>::operator[](const value_type &k) {
        iterator    it;
        it = (find(k));
        if (it == end()){
            _set.insert(k, value_comp());
            it = find(k);
        }
        return it->second;
    }

    template<class T, class Compare, class Alloc>
    pair<typename set<T, Compare, Alloc>::iterator, bool>
    set<T, Compare, Alloc>::insert(const value_type &val, const key_compare &cmp) {
        if (_set.insert_map(val, (cmp)))
        {
            iterator it=_set.lower_bound(val,(cmp));
            return (ft::make_pair(it, true));
        }
        else
        {
            iterator it=_set.lower_bound(val,(cmp));
            return (ft::make_pair(it, false));
        }
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::insert(set::iterator , const value_type &val, const key_compare &cmp) {
        _set.insert_map(val, (cmp));
        return _set.lower_bound(val);
    }

    template<class T, class Compare, class Alloc>
    template<class InputIterator>
    void set<T, Compare, Alloc>::insert(InputIterator first, InputIterator last, const key_compare &comp,
                                        typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *) {
        _set.insert(first, last, (comp));
    }

    template<class T, class Compare, class Alloc>
    void set<T, Compare, Alloc>::erase(set::iterator position, const key_compare &comp) {
        _set.erase(position, (comp));
    }

    template<class T, class Compare, class Alloc>
    size_t set<T, Compare, Alloc>::erase(const value_type &k, const key_compare &comp) {
        iterator it = find(k);
        if (it == end())
            return 0;
        _set.erase(it, (comp));
        return 1;
    }

    template<class T, class Compare, class Alloc>
    void set<T, Compare, Alloc>::erase(set::iterator first, set::iterator last, const key_compare &comp) {
        _set.erase(first, last, (comp));
    }

    template<class T, class Compare, class Alloc>
    void set<T, Compare, Alloc>::swap(set &x) {
        _set.swap(x._set);
    }

    template<class T, class Compare, class Alloc>
    void set<T, Compare, Alloc>::clear(const key_compare &comp) {
        _set.clear((comp));
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::key_compare set<T, Compare, Alloc>::key_comp(const key_compare &comp) const {
        return comp;
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::value_compare set<T, Compare, Alloc>::value_comp(const key_compare &comp) const {
        return value_compare(comp);

    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::find(const value_type &k, const key_compare &comp) {
        return _set.find_map(k, (comp));
    }

    template<class T, class Compare, class Alloc>
    size_t set<T, Compare, Alloc>::count(const value_type &k, const key_compare &comp) const {
        return _set.count(k, (comp));
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::lower_bound(const value_type &k, const key_compare &comp) {
        return _set.lower_bound(k, (comp));
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::upper_bound(const value_type &k, const key_compare &comp) {
        return _set.upper_bound(k, (comp));
    }

    template<class T, class Compare, class Alloc>
    pair<typename set<T, Compare, Alloc>::iterator, typename set<T, Compare, Alloc>::iterator> set<T, Compare, Alloc>::equal_range(const value_type &k, const key_compare &comp) const {
        return make_pair(_set.lower_bound(k, (comp)), _set.upper_bound(k, (comp)));
    }

    template<class T, class Compare, class Alloc>
    typename set<T, Compare, Alloc>::allocator_type set<T, Compare, Alloc>::get_allocator(const allocator_type &alloc) const {
        return alloc;
    }


} //namespace ft
#endif

