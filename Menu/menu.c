#include <stdio.h>
#include "menu.h"

#define MAX_MENU_DEPTH      10

static struct Menu *menupath[MAX_MENU_DEPTH];
static int current_menu= 0;

static void _show_prompt(void);

void menu_set_root(struct Menu *root)
{
    menupath[current_menu]= root;
    _show_prompt();
}

void menu_process_user_input(char input)
{
    struct MenuItem *mit= NULL;
    switch(input)
    {
        case '?':
        // help msg
        mit= menupath[current_menu]->items;
        while(mit->letter != 0)
        {
            printf("%c - %s\n", mit->letter, mit->desc);
            mit++;
        }
        break;

        case '0':
        // parent menu
        if(current_menu > 0)
        {
            current_menu--;
        }
        break;

        default:
        //process an input
        mit= menupath[current_menu]->items;
        int menuitem_found_flag= 0;
        while(mit->letter != 0)
        {
            if(mit->letter == input)
            {
                menuitem_found_flag= 1;
                break;
            }
            mit++;
        }
        if(menuitem_found_flag)
        {
            if(mit->type == MENU_ACTION)
            {
                mit->menuact.action();
            }
            else
            {
                if(current_menu < MAX_MENU_DEPTH-1)
                {
                    menupath[++current_menu]= mit->menuact.menu;
                }
                else
                {
                    printf("No more memory for more deep menues\n");
                }
            }
        }
        else
        {
            printf("%c is not a recognized menu item\n", input);
        }

    }
    _show_prompt();
}

static void _show_prompt(void)
{
    unsigned int index_i= 0;
    printf("\033[1;33m");
    printf("(");
    for(; index_i < current_menu; index_i++)
    {
        printf("%s ->", menupath[index_i]->prompt);
    }
    printf("%s)", menupath[current_menu]->prompt);
    printf("\033[0m");
}

