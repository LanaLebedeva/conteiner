/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 08:41:59 by mlaureen          #+#    #+#             */
/*   Updated: 2021/08/10 08:42:06 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP


#include "RBtree.hpp"
#include "RBTreeIterator.hpp"
#include "utility.hpp"
#include "iterator.hpp"

class RBTree;

namespace ft {
    template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map: public RBTree<T,Compare, Alloc> {
    public:
        typedef Key												key_type;
        typedef T												mapped_type;
        typedef ft::pair<const key_type, mapped_type>			value_type;
        typedef Compare         								key_compare;
        typedef Alloc											allocator_type;
        typedef typename ft::RBTreeIterator<value_type, value_type*, value_type&>          iterator;
        typedef typename ft::RBTreeIterator<value_type, const value_type*, const value_type&>   const_iterator;
        typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

        class value_compare
                {
                public:
                    typedef typename ft::pair<Key, T> value_type;
                private:
                    Compare cmp;
                public:
                    explicit value_compare (Compare const & c) : cmp(c) {}  // constructed with map's comparison object
                    virtual ~value_compare() {}
                    bool operator() (const value_type &x, const value_type &y) const {
                        return (cmp(x.first, y.first));
                    }
                    bool operator() (const value_type &x, const key_type &y) const {
                        return (cmp(x.first, y));
                    }
                    bool operator() (const key_type &x, const value_type &y) const {
                        return (cmp(x, y.first));
                    }
                };
                public:
                    typedef bool            result_type;
                    typedef value_type      first_argument_type;
                    typedef value_type      second_argument_type;
                    bool operator() (const value_type& x, const value_type& y) const
                    {
                        return cmp(x.first, y.first);
                    }
            private:
                RBTree<value_type, value_compare, allocator_type>        _map;

            public:
                void print();
                map(const key_compare & cmp = Compare(), const allocator_type& alloc = allocator_type());
                template <class InputIterator>
                map (InputIterator first, InputIterator last,
                const key_compare& comp = Compare(),
                const allocator_type& alloc = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0);
                map (const map& x, const key_compare& comp = Compare(),
                     const allocator_type& alloc = allocator_type());

                ~map() {}

                map& operator= (const map& x);
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
                mapped_type& operator[] (const key_type& k);

                //Modifiers:
                pair<iterator,bool> insert (const value_type& val, const key_compare & cmp = Compare(), const allocator_type& alloc = allocator_type());
                iterator insert (iterator position, const value_type& val, const key_compare & cmp = Compare());
                template <class InputIterator>
                void insert (InputIterator first, InputIterator last, const key_compare& comp = Compare(),
                                     typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0);
                void erase (iterator position, const key_compare& comp = Compare());
                size_t erase (const key_type& k, const key_compare& comp = Compare());
                void erase (iterator first, iterator last, const key_compare& comp = Compare());
                void swap (map& x);
                void clear(const key_compare& comp = Compare());
                key_compare key_comp(const key_compare& comp = Compare()) const;
                value_compare value_comp(const key_compare& comp = Compare()) const;
                iterator find (const key_type& k, const key_compare& comp = Compare());
                const_iterator find (const key_type& k, const key_compare& comp = Compare()) const;
                size_t count (const key_type& k, const key_compare& comp = Compare()) const;
                iterator lower_bound (const key_type& k, const key_compare& comp = Compare());
                const_iterator lower_bound (const key_type& k, const key_compare& comp = Compare()) const;
                iterator upper_bound (const key_type& k, const key_compare& comp = Compare());
                const_iterator upper_bound (const key_type& k, const key_compare& comp = Compare()) const;
                pair<iterator,iterator> equal_range (const key_type& k, const key_compare& comp = Compare()) const;
                allocator_type get_allocator(const allocator_type& alloc = allocator_type()) const;

    };
    template <class Key, class T, class Compare, class Alloc>
            bool operator== (const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ) {
                if (lhs.size() != rhs.size())
                    return false;
                if (lhs.size() == 0)
                    return true;
                typename map<Key, T, Compare, Alloc>::const_iterator itL = lhs.begin();
                typename map<Key, T, Compare, Alloc>::const_iterator itR = rhs.begin();
                for (size_t i=0; i<lhs.size(); ++i, ++itL, ++itR) {
                    if ((itL->first != itR->first) || (itL->second != itR->second))
                        return false;
                }
                return true;
            }
    template <class Key, class T, class Compare, class Alloc>
    bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs ){
        return !(lhs == rhs);
    }
    template <class Key, class T, class Compare, class Alloc> bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,
            const map<Key,T,Compare,Alloc>& rhs ){
        size_t nl=lhs.size();
        size_t nr=rhs.size();
        if (nl == 0 && nr != 0)
            return true;
        else if (nl == 0)
            return false;
        else if (nr == 0)
            return false;
        typename map<Key, T, Compare, Alloc>::const_iterator itl = lhs.begin();
        typename map<Key, T, Compare, Alloc>::const_iterator itr = rhs.begin();
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
    template <class Key, class T, class Compare, class Alloc>
            bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
                return ((lhs < rhs) || (lhs == rhs));
            }
    template <class Key, class T, class Compare, class Alloc>
            bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
                              const map<Key,T,Compare,Alloc>& rhs ){
                return (!(lhs < rhs) && !(lhs == rhs));
            }

    template <class Key, class T, class Compare, class Alloc>
            bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
                return ((lhs > rhs) || (lhs == rhs));
            }

    template <class Key, class T, class Compare, class Alloc>
           void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y){
               x.swap(y);
           }
    template <typename Key, typename T, typename Compare, typename Alloc>
    map<Key, T, Compare, Alloc>::map(const key_compare & cmp, const allocator_type& alloc):
    _map(RBTree<value_type, value_compare, allocator_type>(value_compare(cmp), alloc)) {}

    template<class Key, class T, class Compare, class Alloc>
    void map<Key, T, Compare, Alloc>::print() {
        _map.printMlaureen();
    }

    template<class Key, class T, class Compare, class Alloc>
    pair<typename map<Key, T, Compare, Alloc>::iterator,bool> map<Key, T, Compare, Alloc>::insert(const map::value_type &val, const key_compare &cmp,
                                             const allocator_type &alloc) {
        if (&alloc == &alloc) {} ;
        if (_map.insert_map(val, value_compare(cmp)))
        {
            iterator it=_map.lower_bound(val,value_compare(cmp));
            return (ft::make_pair(it, true));
        }
        else
        {
           iterator it=_map.lower_bound(val,value_compare(cmp));
           return (ft::make_pair(it, false));
        }
    }

    template<class Key, class T, class Compare, class Alloc>
    map<Key,T, Compare, Alloc> &map<Key, T, Compare, Alloc>::operator=(const map &x) {
        if(this == &x)
            return *this;
        clear();
        if (x._map.size() == 0)
            return *this;
        iterator    it_begin = x.begin();
        iterator    it_end = x.end();
        insert(it_begin, it_end);

        return *this;
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::begin() {
        return (_map.begin());
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::begin() const {
        return (_map.begin());
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::end() {
        return (_map.end());
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::end() const {
        return (_map.end());
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::reverse_iterator  map<Key, T, Compare, Alloc>::rbegin() {
       return ((_map.rbegin()));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_reverse_iterator map<Key, T, Compare, Alloc>::rbegin() const {
        return ((_map.rbegin()));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::reverse_iterator map<Key, T, Compare, Alloc>::rend() {
        return ((_map.rend()));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_reverse_iterator map<Key, T, Compare, Alloc>::rend() const {
        return ((_map.rend()));
    }

    template<class Key, class T, class Compare, class Alloc>
    bool map<Key, T, Compare, Alloc>::empty() const {
        return (_map.empty());
    }

    template<class Key, class T, class Compare, class Alloc>
    size_t map<Key, T, Compare, Alloc>::size() const {
        return (_map.size());
    }

    template<class Key, class T, class Compare, class Alloc>
    size_t map<Key, T, Compare, Alloc>::max_size() const {
        return (_map.max_size());
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::insert(map::iterator , const map::value_type &val, const key_compare & cmp) {
        _map.insert_map(val, value_compare(cmp));
       // if (position) {};
        return _map.lower_bound(val, value_compare(cmp));
    }

    template<class Key, class T, class Compare, class Alloc>
    template<class InputIterator>
    map<Key, T, Compare, Alloc>::map(InputIterator first, InputIterator last, const key_compare &comp,
                                     const allocator_type &alloc,
                                     typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *):
                                     _map(RBTree<value_type, value_compare, allocator_type>(first, last, value_compare(comp), alloc)) {}

    template<class Key, class T, class Compare, class Alloc>
    map<Key, T, Compare, Alloc>::map(const map &x,const key_compare& comp, const allocator_type& alloc): _map(RBTree<value_type, value_compare, allocator_type>((x.begin()), (x.end()), value_compare(comp), alloc)) {}

    template<class Key, class T, class Compare, class Alloc>
    template<class InputIterator>
    void map<Key, T, Compare, Alloc>::insert(InputIterator first, InputIterator last, const key_compare &comp,
                                             typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *)  {
        _map.insert(first, last, value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
            void map<Key, T, Compare, Alloc>::erase(map::iterator position, const key_compare& comp) {
                _map.erase(position, value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
    size_t map<Key, T, Compare, Alloc>::erase(const key_type &k, const key_compare &cmp) {
        //return (_map.erase(ft::make_pair(k, mapped_type()), value_compare(cmp)));
        iterator it = find(k);
        if (it == end())
            return 0;
        _map.erase(it, value_comp(cmp));
        return 1;
    }

    template<class Key, class T, class Compare, class Alloc>
    void map<Key, T, Compare, Alloc>::erase(map::iterator first, map::iterator last, const key_compare &comp) {
        _map.erase(first, last, value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
    void map<Key, T, Compare, Alloc>::swap(map<Key, T, Compare, Alloc> &xp) {
        _map.swap(xp._map);
    }

    template<class Key, class T, class Compare, class Alloc>
    void map<Key, T, Compare, Alloc>::clear(const key_compare& comp) {
        _map.clear(value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
            typename map<Key, T, Compare, Alloc>::key_compare map<Key, T, Compare, Alloc>::key_comp(const key_compare& comp) const {
        return comp;
    }

    template<class Key, class T, class Compare, class Alloc>
            typename map<Key, T, Compare, Alloc>::value_compare map<Key, T, Compare, Alloc>::value_comp(const key_compare &comp) const {
        return value_compare(comp);
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::find(const key_type &k, const key_compare &comp) {
        return _map.find_map(ft::make_pair(k, mapped_type()), value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::find(const key_type &k, const key_compare &comp) const {
        return _map.find_map(ft::make_pair(k, mapped_type()), value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
    size_t map<Key, T, Compare, Alloc>::count(const key_type &k, const key_compare &comp) const {
        return _map.count(ft::make_pair(k, mapped_type()), value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::lower_bound(const key_type &k, const key_compare &comp) {
        return _map.lower_bound(ft::make_pair(k, mapped_type()), value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::lower_bound(const key_type &k, const key_compare &comp) const {
        return _map.lower_bound(ft::make_pair(k, mapped_type()), value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::upper_bound(const key_type &k, const key_compare &comp) {
        return _map.upper_bound(ft::make_pair(k, mapped_type()), value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::upper_bound(const key_type &k, const key_compare &comp) const {
        return _map.upper_bound(ft::make_pair(k, mapped_type()), value_compare(comp));
    }

    template<class Key, class T, class Compare, class Alloc>
    pair<typename map<Key, T, Compare, Alloc>::iterator, typename map<Key, T, Compare, Alloc>::iterator> map<Key, T, Compare, Alloc>::equal_range(const key_type &k, const key_compare& comp) const {
        return make_pair(_map.lower_bound(ft::make_pair(k, mapped_type()), value_compare(comp)), _map.upper_bound(ft::make_pair(k, mapped_type()), value_compare(comp)));
    }

       template<class Key, class T, class Compare, class Alloc>
       typename map<Key, T, Compare, Alloc>::allocator_type map<Key, T, Compare, Alloc>::get_allocator(const allocator_type &alloc) const {
        return alloc;
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::mapped_type &map<Key, T, Compare, Alloc>::operator[](const key_type &k) {
        iterator    it;
        it = (find(k));
        if (it == end()){
          _map.insert_map(ft::make_pair(k, mapped_type()), value_compare(key_comp()));
          it = find(k);
        }
        return it->second;
    }

} // namespace ft


#endif