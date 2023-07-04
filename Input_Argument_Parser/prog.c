#include <stdio.h>
#include <stdlib.h>
#include "argm.h"

int count= 0;
char *msg= NULL;

void _count(void *c);
void _msg(void *m);

struct Option my_options[]=
{
    {'m', "msg", "The message to be printed", _msg},
    {'c', "count", "How many times to print the message", _count},
    {0}
};

int main(int argc, char *argv[])
{
    argm_parse(my_options, argc, argv);
    unsigned int index_i= 0;
    for(; index_i < count; index_i++)
    {
        printf("%s\n", msg);
    }

    return 0;
}

void _count(void *c)
{
    count= atoi((char *)c);
}

void _msg(void *m)
{
    msg= (char *)m;
}