#include "entities.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
    {
    int c;
    while ((c = fgetc(stdin)) != EOF)
        {
        if (c == '&')
            {
            char buf[30];
            int i = 0;
            while ((c = fgetc(stdin)) != EOF)
                {
                if (c == '&')
                    {
                    fputc('&', stdout);
                    fwrite(buf, i, 1, stdout);
                    i = 0;
                    }
                else if (c == ';')
                    {
                    buf[i] = 0;
                    char * ent = findEntity(buf);
                    if (ent)
                        {
                        fwrite(ent, 1, strlen(ent), stdout);
                        }
                    else
                        {
                        fputc('&', stdout);
                        fwrite(buf, i, 1, stdout);
                        fputc(';', stdout);
                        }
                    break;
                    }
                else if (i == sizeof(buf) || (c < '0' && c != '#') || c > 'z')
                    {
                    fputc('&', stdout);
                    fwrite(buf, i, 1, stdout);
                    fputc(c, stdout);
                    break;
                    }
                else
                    buf[i++] = (char)c;
                }
            if (c == EOF)
                {
                fputc('&', stdout);
                fwrite(buf, i, 1, stdout);
                break;
                }
            }
        else
            fputc(c, stdout);
        }
    return 0;
    }