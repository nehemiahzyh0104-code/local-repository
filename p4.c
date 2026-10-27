#ifndef CS100_MEMCHECK_H
#define CS100_MEMCHECK_H 1

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 1000


struct Record
{
    void *ptr;             // address of the allocated memory
    size_t size;           // size of the allocated memory
    int line_no;           // line number of the malloc/calloc call
    const char *file_name; // file in which the call happens
};


#define malloc(SIZE) recorded_malloc (SIZE, __LINE__, __FILE__)
#define calloc(CNT, EACH_SIZE)                                                \
    recorded_calloc (CNT, EACH_SIZE, __LINE__, __FILE__)
#define free(PTR) recorded_free (PTR, __LINE__, __FILE__)

#endif