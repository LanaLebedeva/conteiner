/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 15:21:10 by mlaureen          #+#    #+#             */
/*   Updated: 2021/08/06 15:21:15 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft{
    // Struct holding two objects of arbitrary type.
    template<class T1, class T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;
        T1     first;
        T2     second;

        //Member variables
        pair():first(), second() {}
        pair(const T1 &x, const T2 &y):first(x), second(y) {}
        template<class R1, class R2>
        pair(const pair<R1, R2> &x): first(x.first), second(x.second){}
        pair& operator= (const pair& pr){
            first = pr.first;
            second = pr.second;
            return *this;
        }
        template<class R1, class R2, class R_1, class R_2>
        pair<R_1, R_2> & operator=(const pair<R1, R2> & pr){
            first = pr.first;
            second = pr.second;
            return *this;
        }

        T1 operator*(){
            return first;
        }


    };
    //Non-member function overloads
    template <class T1, class T2>
    bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
        return ((lhs.first == rhs.first) && (lhs.second ==rhs.second));
    }

    template <class T1, class T2>
    bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
        return ((lhs.first != rhs.first) || (lhs.second !=rhs.second));
    }

    template <class T1, class T2>
    bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return ((lhs.first < rhs.first) || (lhs.second  <rhs.second));
    }
    template <class T1, class T2>
    bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return (!(lhs > rhs));
    }
    template <class T1, class T2>
    bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
        return (rhs < lhs);
    }
    template <class T1, class T2>
    bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs){
        return (!(lhs < rhs));
    }
    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y){
        return ( pair<T1,T2>(x,y) );
    }

} // namespace ft
#endif