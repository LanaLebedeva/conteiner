/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaureen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:28:19 by mlaureen          #+#    #+#             */
/*   Updated: 2021/07/20 10:28:22 by mlaureen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft {
// integral_constant (обертка)
template<typename T, T v>
    struct integral_constant {
        static const T                      value = v;
        typedef T                           value_type;
        typedef integral_constant<T, v>     type;
        operator value_type() const { return value; }
    };
    template<typename>
        struct remove_cv;

    // remove_const
    template<typename T>
        struct remove_const
    { typedef T     type; };

    template<typename T>
        struct remove_const<T const>
         { typedef T     type; };

    //remove_volatile
    template<typename T>
        struct remove_volatile
        { typedef T     type; };

    template<typename T>
        struct remove_volatile<T volatile>
        { typedef T     type; };

    template<typename T>
        struct remove_cv
         {
           typedef typename
           remove_const<typename remove_volatile<T>::type>::type     type;
         };


// The type used as a compile-time boolean with true value.
    typedef integral_constant<bool, true> true_type;

// The type used as a compile-time boolean with false value.
    typedef integral_constant<bool, false> false_type;

    template<bool B, class T = void>
    struct enable_if {
    };

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template<typename>
    struct is_integral_helper : public false_type {
    };

    template<>
    struct is_integral_helper<bool> : public true_type {
    };

    template<>
    struct is_integral_helper<char> : public true_type {
    };

    template<>
    struct is_integral_helper<signed char> : public true_type {
    };

    template<>
    struct is_integral_helper<unsigned char> : public true_type {
    };

#ifdef _GLIBCXX_USE_WCHAR_T
    template<>
        struct is_integral_helper<wchar_t>: public true_type { };
#endif

    template<>
    struct is_integral_helper<char16_t> : public true_type {
    };

    template<>
    struct is_integral_helper<char32_t> : public true_type {
    };

    template<>
    struct is_integral_helper<short> : public true_type {
    };

    template<>
    struct is_integral_helper<unsigned short> : public true_type {
    };

    template<>
    struct is_integral_helper<int> : public true_type {
    };

    template<>
    struct is_integral_helper<unsigned int> : public true_type {
    };

    template<>
    struct is_integral_helper<long> : public true_type {
    };

    template<>
    struct is_integral_helper<unsigned long> : public true_type {
    };

    template<>
    struct is_integral_helper<long long> : public true_type {
    };

    template<>
    struct is_integral_helper<unsigned long long> : public true_type {
    };

#if !defined(__STRICT_ANSI__) && defined(_GLIBCXX_USE_INT128)
    template<>
        struct is_integral_helper<__int128>: public true_type { };

    template<>
        struct is_integral_helper<unsigned __int128>: public true_type { };
#endif

// is_integral
    template<typename T>
struct is_integral : public integral_constant<bool, (is_integral_helper<typename ft::remove_cv<T>::type>::value)> {
    };
} //namespace ft