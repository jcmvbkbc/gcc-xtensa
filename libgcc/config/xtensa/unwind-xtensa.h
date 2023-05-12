#include "unwind-generic.h"

#ifdef __FDPIC__
static inline _Unwind_Ptr _Unwind_gnu_Find_got (_Unwind_Ptr ptr)
{
    _Unwind_Ptr res;

    (void)ptr;
    asm volatile ("mov %[result], a11"
		  : [result] "=r" (res));

    return res;
}
#endif
