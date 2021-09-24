/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 12:12:38 by mlaureen          #+#    #+#             */
/*   Updated: 2021/08/13 12:12:41 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
namespace ft {
    template<typename T, class Container = ft::vector<T>, typename Alloc = std::allocator<T> >
    class stack {
    public:
        typedef T               value_type;
        typedef Container       container_type;
        typedef size_t          size_type;

        //Member functions
        ~stack() {};
        explicit stack (const container_type& ctnr = container_type());
        bool empty() const;
        size_type size() const;
        value_type& top();
        const value_type& top() const;
        void push (const value_type& val);
        void pop();
    private:
        container_type  c;
        stack(const stack &ths);
        stack & operator=(const stack &ths);

    };
    //Non-member function overloads
    template <class T, class Container>
            bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
                return lhs == rhs;
            }

    template <class T, class Container>
            bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
                return lhs != rhs;
            }

    template <class T, class Container>
            bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
                return lhs < rhs;
            }

    template <class T, class Container>
            bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs){
                return lhs  <= rhs;
            }

    template <class T, class Container>
            bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
                return lhs > rhs;
            }

    template <class T, class Container, class Alloc>
            bool operator>= (const stack<T,Container, Alloc>& lhs, const stack<T,Container, Alloc>& rhs){
                return lhs >= rhs;
            }

    template<typename T, class Container, class Alloc>
            stack<T, Container, Alloc>::stack(const container_type &ctnr): c(ctnr) {}

    template<typename T, class Container, class Alloc>
    bool stack<T, Container, Alloc>::empty() const {
        return c.empty();
    }

    template<typename T, class Container, class Alloc>
            size_t stack<T, Container, Alloc>::size() const {
        return c.size();
    }

    template<typename T, class Container, class Alloc>
    void stack<T, Container, Alloc>::push(const value_type &val) {
        c.push_back(val);
    }

    template<typename T, class Container, class Alloc>
    typename stack<T, Container, Alloc>::value_type &stack<T, Container, Alloc>::top() {
        return c.back();
    }

    template<typename T, class Container, class Alloc>
    const typename stack<T, Container, Alloc>::value_type &stack<T, Container, Alloc>::top() const {
        return c.back();
    }

    template<typename T, class Container, class Alloc>
    void stack<T, Container, Alloc>::pop() {
        c.pop_back();
    }
} // namespace ft
#endif

