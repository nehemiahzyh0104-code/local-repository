#ifndef CS100_MEMCHECK_H
#define CS100_MEMCHECK_H 1

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 1000

struct Record
{
    void *ptr;
    size_t size;
    int line_no;
    const char *file_name;
};

static struct Record dnote[MAX_RECORDS] = { 0 }; // deathnote for mem

int // 计算长度
fnd ()
{
    int i = 0;
    while (dnote[i].ptr != NULL)
        i++;
    return i;
}

void // 存入deathnote
store (void *ptr, size_t size, int line, const char *file)
{
    int i = fnd ();
    dnote[i].ptr = ptr;
    dnote[i].size = size;
    dnote[i].line_no = line;
    dnote[i].file_name = file;
}

int // 杀了并重排
murder (void *ptr)
{
    int i = fnd ();
    int n = 0;
    while (n < i)
        {
            if (dnote[n].ptr == ptr)
                {
                    dnote[n] = (struct Record){ 0 };

                    for (int k = n; k < i; k++)
                        dnote[k] = dnote[k + 1];

                    return 1;
                }
            n++;
        }
    return 0;
}



void *
recorded_malloc (size_t size, int line, const char *file)
{
    void *ptr = malloc (size);
    if (ptr != NULL)
        store (ptr, size, line, file);
    return ptr;
}

void *
recorded_calloc (size_t cnt, size_t each_size, int line, const char *file)
{
    void *ptr = calloc (cnt, each_size);
    if (ptr != NULL)
        store (ptr, each_size * cnt, line, file);
    return ptr;
}



void
recorded_free (void *ptr, int line, const char *file)
{
    if (ptr != NULL)
        {
            if (murder (ptr))
                free (ptr);
            else
                {
                    printf ("Invalid free in file %s, line %d\n", file, line);
                }
        }
    return;
}



#define malloc(SIZE) recorded_malloc (SIZE, __LINE__, __FILE__)
#define calloc(CNT, EACH_SIZE)                                                \
    recorded_calloc (CNT, EACH_SIZE, __LINE__, __FILE__)
#define free(PTR) recorded_free (PTR, __LINE__, __FILE__)



void check_leak (void) __attribute__ ((destructor));

void
check_leak (void)
{
    printf ("Summary:\n");
    if (fnd ())
        {
            size_t sum = 0;
            int i = fnd ();
            for (int k = 0; k < i; k++)
                {
                    printf ("%zu bytes memory not freed (allocated in file "
                            "%s, line %d)\n",
                            dnote[k].size, dnote[k].file_name,
                            dnote[k].line_no);
                    sum += dnote[k].size;
                }
            printf ("%d allocation records not freed (%zu bytes in total).\n",
                    i, sum);
        }
    else
        {
            printf ("All allocations have been freed.\n");
        }
}

#endif
