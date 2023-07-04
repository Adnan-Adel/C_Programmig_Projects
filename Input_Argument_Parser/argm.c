#include <stdio.h>
#include <string.h>
#include "argm.h"

void _help(void *h)
{
    struct Option * op = (struct Option *)h;
    while (op->sname != 0) 
    {
        printf("-%c, --%s: %s\n", op->sname, op->lname, op->desc);
        op++;
    }
}
struct Option help={'h', "help", NULL, _help};

static struct Option *_find_option_by_sname(struct Option *options, char sname);
static struct Option *_find_option_by_lname(struct Option *options, char *lname);

void argm_parse(struct Option *option, int argc, char *argv[])
{
    unsigned int index_i= 0;
    for(; index_i < argc; index_i++)
    {
        struct Option *op= NULL;
        if(argv[index_i][0] == '-')
        {
            if(argv[index_i][1] == '-')
            {
                // Long Name
                op= _find_option_by_lname(option, &argv[index_i][2]);

            }
            else
            {
                // Short Name
                op= _find_option_by_sname(option, argv[index_i][1]);

            }

            if(op == &help)
            {
                op->action((void *)option);
            }

            else if(op != NULL)
            {
                if((index_i <= argc - 2) && (argv[index_i + 1][0] != '-'))
                {
                    op->action((void *)argv[index_i + 1]);
                    index_i++;
                }
                else
                {
                    op->action(NULL);
                }
            }
            else
            {
                printf("Unrecognized option: %s\n", argv[index_i]);
            }
        }
        else
        {
            printf("Unrecognized option: %s\n", argv[index_i]);
        }
    }
}

static struct Option *_find_option_by_sname(struct Option *options, char sname)
{
    struct Option *op= options;
    if (sname == 'h')
    {
        return &help;
    }
    while(op->sname != 0)
    {
        if(op->sname == sname)
        {
            return op;
        }
        op++;
    }
    return NULL;
}

static struct Option *_find_option_by_lname(struct Option *options, char *lname)
{
    struct Option *op= options;
    if (strcmp(lname, "help")) 
    {
        return &help;
    }
    while(op->lname != 0)
    {
        if(strcmp(op->lname, lname))
        {
            return op;
        }
        op++;
    }
    return NULL;
}