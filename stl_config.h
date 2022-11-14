#ifndef __STL_CONFIG_H
#define __STL_CONFIG_H

#define __STL_BEGIN_NAMESPACE namespace __STL {
#define __STL_END_NAMESPACE }
#define __STL_TEMPLATE_NULL template<>
#define __STL_TRY try
#define __STL_UNWIND(action) catch(...) { action; throw; }
#endif /* __STL_CONFIG_H */
