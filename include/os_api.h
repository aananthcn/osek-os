#ifndef AANANTH_OSEK_OS_API_H
#define AANANTH_OSEK_OS_API_H

#include <ostypes.h>

u32 _GetOsTickCnt(void);
int _OsHandleTicks(void);

/* low level APIs */
u32 _set_stack_ptr(u32 new_stack);
u32 _get_stack_ptr(void);
u32 _get_next_pc(void);
void _set_sp_and_pc(u32 sp, u32 pc);

int pr_log(const char *format, ...);
int pr_log_init(void);


#endif