#ifndef __UTILS_H_
#define __UTILS_H_
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define DIE(assertion,message)                                                  \
if(assertion) {                                                                 \
    fprintf(stderr,"Error at line %d in file %s\n",__LINE__,__FILE__);          \
    perror(message);                                                            \
    exit(errno);                                                                \
} 

#endif // __UTILS_H_