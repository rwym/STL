#ifndef __STL_INTERNAL_FUNCTION_H
#define __STL_INTERNAL_FUNCTION_H
#include "stl_config.h"
#include <cstddef>
__STL_BEGIN_NAMESPACE
template <class _Arg, class _Result>
struct unary_function {
  typedef _Arg argument_type;
  typedef _Result result_type;
};

template <class _Arg1, class _Arg2, class _Result>
struct binary_function {
  typedef _Arg1 first_argument_type;
  typedef _Arg2 second_argument_type;
  typedef _Result result_type;
};

template <class _Tp>
struct plus : public binary_function<_Tp, _Tp, _Tp> {
  _Tp operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs + __rhs; }
};

template <class _Tp>
struct minus : public binary_function<_Tp, _Tp, _Tp> {
  _Tp operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs - __rhs; }
};

template <class _Tp>
struct multiplies : public binary_function<_Tp, _Tp, _Tp> {
  _Tp operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs  * __rhs; }
};

template <class _Tp>
struct divides : public binary_function<_Tp, _Tp, _Tp> {
  _Tp operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs / __rhs; }
};

template <class _Tp>
struct modules : public binary_function<_Tp, _Tp, _Tp> {
  _Tp operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs % __rhs; }
};

template <class _Tp>
struct negate : public unary_function<_Tp, _Tp> {
  _Tp operator()(const _Tp& __x) { return __x; }
};

template <class _Tp>
struct equal_to : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs == __rhs; }
};

template <class _Tp>
struct unequal_to : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs != __rhs; }
};

template <class _Tp>
struct greater : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs > __rhs; }
};

template <class _Tp>
struct less : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs < __rhs; }
};

template <class _Tp>
struct greater_equal : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs >= __rhs; }
};

template <class _Tp>
struct less_equal : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs <= __rhs; }
};

template <class _Tp>
struct logical_and : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs && __rhs; }
};

template <class _Tp>
struct logical_or : public binary_function<_Tp, _Tp, bool> {
  bool operator()(const _Tp& __lhs, const _Tp& __rhs) const { return __lhs || __rhs; }
};

template <class _Tp>
struct logical_not : public unary_function<_Tp, bool> {
  bool operator()(const _Tp& __x) const { return !__x; }
};

template <class _Tp>
struct _Identity : public unary_function<_Tp, _Tp> {
  const _Tp& operator()(const _Tp& __x) const { return __x; }
};

template <class _Pair>
struct _Select1st : public unary_function<_Pair, typename _Pair::first> {
  const typename _Pair::first_type& operator()(const _Pair& __x) const {
    return __x.first;
  }
};

template <class _Pair>
struct _Select2nd : public unary_function<_Pair, typename _Pair::second> {
  const typename _Pair::second_type& operator()(const _Pair& __x) const {
    return __x.second;
  }
};

template <class _Arg1, class _Arg2>
struct _Projectfirst: public binary_function<_Arg1, _Arg2, _Arg1> {
  _Arg1 operator()(const _Arg1& __lhs, const _Arg2& __rhs) { return __lhs; }
};

template <class _Arg1, class _Arg2>
struct _Projectsecond: public binary_function<_Arg1, _Arg2, _Arg1> {
  _Arg1 operator()(const _Arg1& __lhs, const _Arg2& __rhs) { return __rhs; }
};
__STL_END_NAMESPACE
#endif /* __STL_INTERNAL_FUNCTION_H */
