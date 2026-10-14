#include <stdio.h>
#include <string.h>

char *
convert (char *inpt)
{
    char *opt;
    static char ttl[64];
    if (strstr (inpt, "gnu++"))
        {
            opt = "GNU dialect of C++";
        }

    else if (strstr (inpt, "gnu"))
        {
            opt = "GNU dialect of C";
        }

    else if (strstr (inpt, "c++"))
        {
            opt = "ISO C++";
        }

    else if (strchr (inpt, 'c'))
        {
            opt = "ISO C";
        }
    else
        return NULL;

    snprintf (ttl, sizeof (ttl), "%s%s", opt, inpt + strlen (inpt) - 2);

    return ttl;
}

int
main (int argc, char *argv[])
{
    int k = 1;
    while(k<argc)
        {
            char *ver, *std;

            if (strcmp (argv[k], "-Wall") == 0)
                {
                    printf ("-Wall: Enable all the warnings about "
                            "constructions that some users consider "
                            "questionable, and that are easy to avoid (or "
                            "modify to prevent the warning).\n");
                }
            else if (strcmp (argv[k], "-Wpedantic") == 0)
                {
                    printf ("-Wpedantic: Issue all the warnings demanded by "
                            "strict ISO C and ISO C++ and reject all programs "
                            "that use forbidden extensions.\n");
                }
            else if (strcmp (argv[k], "-Wextra") == 0)
                {
                    printf ("-Wextra: Enable some extra warning flags that "
                            "are not enabled by -Wall.\n");
                }
            else if (strcmp (argv[k], "-Werror") == 0)
                {
                    printf ("-Werror: Make all warnings into errors.\n");
                }

            else if (strcmp (argv[k], "-o") == 0)
                {
                    ver = argv[k + 1];
                    printf ("-o %s: Place the primary output in file %s.\n",
                            ver, ver);
                    k++;
                }
            else if (strcmp (argv[k], "-I") == 0)
                {
                    ver = argv[k + 1];
                    printf ("-I %s: Add the directory xxx to the list of "
                            "directories to be searched for header files "
                            "during preprocessing.\n",
                            ver);
                    k++;
                }

            else if (strstr (argv[k], "-std"))
                {
                    ver = strtok (argv[k], "=");
                    ver = strtok (NULL, "=");
                    std = convert (ver);
                    printf ("-std=%s: Set the language standard to %s.\n", ver,
                            std);
                }
            k++;
        }

    return 0;
}
