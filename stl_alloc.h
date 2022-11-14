#ifndef __STL_INTERNAL_ALLOC_H
#define __STL_INTERNAL_ALLOC_H
#include "stl_config.h"
#include "stl_construct.h"
#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <cstdio>
#define THROW_BAD_ALLOC fprintf(stderr, "out of memory\n"); exit(1);
__STL_BEGIN_NAMESPACE
template <int __inst>
class __malloc_alloc_template {
public:
  static void* allocate(size_t __n) {
    void* __result = malloc(__n);
    if (__result == nullptr) __result = oom_malloc(__n);
    return __result;
  }

  static void deallocate(void* __p, size_t) {
    free(__p);
  }

  static void* reallocate(void* __p, size_t, size_t __new_sz) {
    void* __result = realloc(__p, __new_sz);
    if (__result == nullptr) __result = oom_realloc(__p, __new_sz);
    return __result;
  }

  static void (* set_malloc_handler(void (* f) ())) () {
    void (* old) () = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = f;
    return old;
  }
private:
  static void* oom_malloc(size_t);
  static void* oom_realloc(void*, size_t);
  static void (* __malloc_alloc_oom_handler) ();
};

template <int __inst>
void (* __malloc_alloc_template <__inst>::__malloc_alloc_oom_handler) () = nullptr;

template <int __inst>
void* __malloc_alloc_template <__inst>::oom_malloc(size_t __n) {
  void (* __malloc_handler) ();
  void* result;
  for (;;) {
    __malloc_handler = __malloc_alloc_oom_handler;
    if (__malloc_handler == nullptr) { THROW_BAD_ALLOC; }
    (* __malloc_handler) ();
    result = malloc(__n);
    if (result) return result;
  }
}

template <int __inst>
void* __malloc_alloc_template <__inst>::oom_realloc(void *__p, size_t __n) {
  void (* __malloc_handler) ();
  void* result;

  for (;;) {
    __malloc_handler = __malloc_alloc_oom_handler;
    if (0 == __malloc_handler) { THROW_BAD_ALLOC; }
    (* __malloc_handler) ();
    result = realloc(__p, __n);
    if (result) return result;
  }
}

typedef __malloc_alloc_template <0> malloc_alloc;

template <class _Tp, class _Alloc>
class simple_alloc {
public:
  static _Tp *allocate(size_t __n) {
    return 0 == __n ? 0 : (_Tp*) _Alloc::allocate(__n * sizeof(_Tp));
  }

  static _Tp *allocate(void) {
    return (_Tp*) _Alloc::allocate(sizeof(_Tp));
  }

  static void deallocate(_Tp *__p, size_t __n) {
    if (0 != __n) {
      _Alloc::deallocate(__p, __n * sizeof(_Tp));
    }
  }

  static void deallocate(_Tp *__p) {
    _Alloc::deallocate(__p, sizeof(_Tp));
  }
};

typedef malloc_alloc alloc;

__STL_END_NAMESPACE
#endif /* __STL_INTERNAL_ALLOC_H */
