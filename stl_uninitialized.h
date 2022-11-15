#ifndef __STL_INTERNAL_UNINITIALIZED_H
#define __STL_INTERNAL_UNINITIALIZED_H
#include "stl_config.h"
#include "stl_iterator_base.h"
#include "type_traits.h"
#include "stl_construct.h"
#include "stl_algobase.h"
#include "stl_pair.h"
__STL_BEGIN_NAMESPACE

// uninitialized_copy

template <class _InputIter, class _ForwardIter>
inline _ForwardIter
__uninitialized_copy_aux(_InputIter __first, _InputIter __last,
                         _ForwardIter __result,
                         __true_type)
{
  return copy(__first, __last, __result);
}

template <class _InputIter, class _ForwardIter>
_ForwardIter
__uninitialized_copy_aux(_InputIter __first, _InputIter __last,
                         _ForwardIter __result,
                         __false_type)
{
  _ForwardIter __cur = __result;
  __STL_TRY {
    for ( ; __first != __last; ++__first, ++__cur)
      _Construct(&*__cur, *__first);
    return __cur;
  }
  __STL_UNWIND(_Destroy(__result, __cur));
}

template <class _InputIter, class _ForwardIter, class _Tp>
inline _ForwardIter
__uninitialized_copy(_InputIter __first, _InputIter __last,
                     _ForwardIter __result, _Tp*)
{
  typedef typename __type_traits<_Tp>::is_POD_type _Is_POD;
  return __uninitialized_copy_aux(__first, __last, __result, _Is_POD());
}

template <class _InputIter, class _ForwardIter>
inline _ForwardIter
uninitialized_copy(_InputIter __first, _InputIter __last,
                   _ForwardIter __result)
{
  return __uninitialized_copy(__first, __last, __result
                                  __VALUE_TYPE(__result));
}

inline char* uninitialized_copy(const char* __first, const char* __last,
                                char* __result) {
  memmove(__result, __first, __last - __first);
  return __result + (__last - __first);
}

inline wchar_t*
uninitialized_copy(const wchar_t* __first, const wchar_t* __last,
                   wchar_t* __result) {
  memmove(__result, __first, sizeof(wchar_t) * (__last - __first));
  return __result + (__last - __first);
}

// uninitialized_copy_n ( not in std )

template <class _InputIter, class _Size, class _ForwardIter>
pair<_InputIter, _ForwardIter>
__uninitialized_copy_n(_InputIter __first, _Size __count,
                       _ForwardIter __result,
                       input_iterator_tag)
{
  _ForwardIter __cur = __result;
  __STL_TRY {
    for ( ; __count > 0; --__count, ++__first, ++__cur)
      _Construct(&*__cur, *__first);
    return pair<_InputIter, _ForwardIter>(__first, __cur);
  }
  __STL_UNWIND(_Destroy(__result, __cur));
}

template <class _RandomAccessIter, class _Size, class _ForwardIter>
inline pair<_RandomAccessIter, _ForwardIter>
__uninitialized_copy_n(_RandomAccessIter __first, _Size __count,
                      _ForwardIter __result,
                      random_access_iterator_tag) {
  _RandomAccessIter __last = __first + __count;
  return pair<_RandomAccessIter, _ForwardIter>{
           __last,
           uninitialized_copy(__first, __last, __result)};
}

template <class _InputIter, class _Size, class _ForwardIter>
pair<_InputIter, _ForwardIter>
uninitialized_copy_n(_InputIter __first, _Size __count,
                     _ForwardIter __result) {
  return __uninitialized_copy_n(__first, __count, __result,
                                __ITERATOR_CATEGORY(__first));
}

// destructor is trivial

template <class _ForwardIter, class _Tp>
inline void
__uninitialized_fill_aux(_ForwardIter __first, _ForwardIter __last,
                         const _Tp& __x, __true_type)
{
  fill(__first, __last, __x);
}

template <class _ForwardIter, class _Tp>
void
__uninitialized_fill_aux(_ForwardIter __first, _ForwardIter __last,
                         const _Tp& __x, __false_type)
{
  _ForwardIter __cur = __first;
  __STL_TRY {
    for ( ; __cur != __last; ++__cur)
      _Construct(&*__cur, __x);
  }
  __STL_UNWIND(_Destroy(__first, __cur));
}

template <class _ForwardIter, class _Tp, class _Tp1>
inline void __uninitialized_fill(_ForwardIter __first,
                                 _ForwardIter __last, const _Tp& __x, _Tp*)
{
  typedef typename __type_traits<_Tp1>::is_POD_type _Is_POD;
  __uninitialized_fill_aux(__first, __last, __x, _Is_POD());
}

template <class _ForwardIter, class _Tp>
inline void uninitialized_fill(_ForwardIter __first,
                               _ForwardIter __last,
                               const _Tp& __x)
{
  __uninitialized_fill(__first, __last, __x, __VALUE_TYPE(__first));
}

template <class _ForwardIter, class _Size, class _Tp>
inline _ForwardIter
__uninitialized_fill_n_aux(_ForwardIter __first, _Size __n,
                           const _Tp& __x, __true_type)
{
  return fill_n(__first, __n, __x);
}

template <class _ForwardIter, class _Size, class _Tp>
_ForwardIter
__uninitialized_fill_n_aux(_ForwardIter __first, _Size __n,
                           const _Tp& __x, __false_type)
{
  _ForwardIter __cur = __first;
  __STL_TRY {
    for ( ; __n > 0; --__n, ++__cur)
      _Construct(&*__cur, __x);
    return __cur;
  }
  __STL_UNWIND(_Destroy(__first, __cur));
}

template <class _ForwardIter, class _Size, class _Tp, class _Tp1>
inline _ForwardIter
__uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp& __x, _Tp1*)
{
  typedef typename __type_traits<_Tp1>::is_POD_type _Is_POD;
  return __uninitialized_fill_n_aux(__first, __n, __x, _Is_POD());
}

template <class _ForwardIter, class _Size, class _Tp>
inline _ForwardIter
__uninitialized_fill_n(_ForwardIter __first, _Size __n, const _Tp& __x)
{
  return __uninitialized_fill_n_aux(__first, __n, __x, __VALUE_TYPE(__first));
}

// Extensions: 
// __uninitialized_copy_copy
// __uninitialized_fill_copy
// __uninitialized_copy_fill

template <class _InputIter1, class _InputIter2, class _ForwardIter>
inline _ForwardIter
__uninitialized_copy_copy(_InputIter1 __first1, _InputIter1 __last1,
                          _InputIter2 __first2, _InputIter2 __last2,
                          _ForwardIter __result)
{
  _ForwardIter __mid = uninitialized_copy(__first1, __last1, __result);
  __STL_TRY {
    return uninitialized_copy(__first2, __last2, __mid);
  }
  __STL_UNWIND(_Destroy(__result, __mid));
}

template <class _ForwardIter, class _Tp, class _InputIter>
inline _ForwardIter
__uninitialized_fill_copy(_ForwardIter __result, _ForwardIter __mid,
                          const _Tp& __x,
                          _InputIter __first, _InputIter __last)
{
  uninitialized_fill(__result, __mid, __x);
  __STL_TRY {
    return uninitialized_copy(__first, __last, __mid);
  }
  __STL_UNWIND(_Destroy(__result, __mid));
}

template <class _InputIter, class _ForwardIter, class _Tp>
inline void
__uninitialized_copy_fill(_InputIter __first1, _InputIter __last1,
                          _ForwardIter __first2, _ForwardIter __last2,
                          const _Tp& __x)
{
  _ForwardIter __mid2 = uninitialized_copy(__first1, __last1, __first2);
  __STL_TRY {
    return uninitialized_fill(__first2, __mid2);
  }
  __STL_UNWIND(_Destroy(__first2, __mid2));
}

__STL_END_NAMESPACE
#endif /* __STL_INTERNAL_UNINITIALIZED_H */
