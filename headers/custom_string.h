#include <stdlib.h>
#include <string.h>

void remove_trailing_newline (char *str)
{
  if (str == NULL)
    return;
  int length = strlen(str);
  if (str[length-1] == '\n')
    str[length-1]  = '\0';
}

char **split (const char *src, const char *delim)
{
    int i = 0, in = 0, nptrs = 2;
    char **dest = NULL;
    const char *p = src, *ep = p;
    if (!(dest = malloc (nptrs * sizeof *dest))) {
        perror ("malloc-dest");
        return NULL;
    }
    *dest = NULL;
    for (;;) {
        if (!*ep || strchr (delim, *ep)) {
            size_t len = ep - p;
            if (in && len) {
                if (i == nptrs - 1) {
                    void *tmp = realloc (dest, 2 * nptrs * sizeof *dest);
                    if (!tmp) {
                        perror ("realloc-dest");
                        break;
                    }
                    dest = tmp;
                    nptrs *= 2;
                }
                if (!(dest[i] = malloc (len + 1))) {
                    perror ("malloc-dest[i]");
                    break;
                }
                memcpy (dest[i], p, len);
                dest[i++][len] = 0;
                dest[i] = NULL;
            }
            if (!*ep)
                break;
            in = 0;
        }
        else {
            if (!in)
                p = ep;
            in = 1;
        }
        ep++;
    }
    return dest;
}
