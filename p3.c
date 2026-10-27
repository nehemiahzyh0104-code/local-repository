#include <stddef.h>

int
hw3_islower (int ch)
{
    return (ch >= 'a' && ch <= 'z');
}

int
hw3_isupper (int ch)
{
    return (ch >= 'A' && ch <= 'Z');
}

int
hw3_isalpha (int ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int
hw3_isdigit (int ch)
{
    return ('0' <= ch && ch <= '9');
}

int
hw3_tolower (int ch)
{
    return hw3_isupper (ch) ? ch + 32 : ch;
}

int
hw3_toupper (int ch)
{
    return hw3_islower (ch) ? ch - 32 : ch;
}

// --------------------------------------------------

size_t
hw3_strlen (const char *str)
{
    char *i = (char *)str; // no \0
    while (*i)
        i++;
    return i - str;
}


char *
hw3_strchr (const char *str, int ch) // yes \0
{
    char *i = (char *)str;
    do
        {
            if ((int)*i == ch)
                return i;
            i++;
        }
    while (*i);
    return NULL;
}


char *
hw3_strcpy (char *dest, const char *src)
{
    int len = (int)hw3_strlen (src);
    for (int i = 0; i < (len + 1); i++)
        dest[i] = src[i];
    return dest;
}


char *
hw3_strcat (char *dest, const char *src)
{
    int init = (int)hw3_strlen (dest);
    int len = (int)hw3_strlen (src);

    for (int i = 0; i < (len + 1); i++)
        dest[init + i] = src[i];
    return dest;
}


int
hw3_strcmp (const char *lhs, const char *rhs)
{
    const char *n = lhs, *m = rhs;
    while (*n != 0 && *m != 0 && *n == *m)
        n++, m++;
    return *n - *m;
}
