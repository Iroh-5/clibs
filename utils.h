#ifndef UTILS_H
#define UTILS_H

#define ASSERT(expr, mes)                             \
    do                                                \
    {                                                 \
	if (!(expr))                                  \
	{                                             \
	    printf("[ERROR][%s]: %s", __func__, mes); \
	    exit(0);                                  \
	}                                             \
    }                                                 \
    while (0)                                         \

#endif
