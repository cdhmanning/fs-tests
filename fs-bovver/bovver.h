#ifndef __BOVVER_H__
#define __BOVVER_H__
void * bovver_init(int threadId, const char *baseDir, int bovver_type);
void bovver_do(void *x);
void bovver_stats(void *x, int *cycles, int *lastOp);
void bovver_quit(void *x);
#endif
