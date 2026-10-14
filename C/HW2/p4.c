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
    while (k < argc)
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
                    printf ("-I %s: Add the directory %s to the list of "
                            "directories to be searched for header files "
                            "during preprocessing.\n",
                            ver, ver);
                    k++;
                }

            else if (strncmp (argv[k], "-std=", 5) == 0)
                {
                    ver = strtok (argv[k], "=");
                    ver = strtok (NULL, "=");
                    std = convert (ver);
                    printf ("-std=%s: Set the language standard to %s.\n", ver,
                            std);
                }
            else
                {
                    char *typ = "";
                    char *ext = strrchr (argv[k], '.');

                    if (ext != NULL
                        && (strcmp (ext, ".cpp") == 0
                            || strcmp (ext, ".C") == 0
                            || strcmp (ext, ".cc") == 0
                            || strcmp (ext, ".cxx") == 0))
                        {
                            typ = "C++ source code";
                        }
                    else if (ext != NULL
                             && (strcmp (ext, ".hpp") == 0
                                 || strcmp (ext, ".hxx") == 0))
                        {
                            typ = "C++ header file";
                        }
                    else if (ext != NULL && strcmp (ext, ".c") == 0)
                        {
                            typ = "C source code";
                        }
                    else if (ext != NULL && strcmp (ext, ".h") == 0)
                        {
                            typ = "C/C++ header file";
                        }
                    printf ("%s: %s as input file.\n", argv[k], typ);
                }
            k++;
        }

    return 0;
}
