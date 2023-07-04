#include <stdio.h>
#include "menu.h"

void _newfile(void) {printf("%s", __func__);}
void _openfile(void) {printf("%s", __func__);}
void _copytoclipboard(void) {printf("%s", __func__);}
void _copytofile(void) {printf("%s", __func__);}
void _paste(void) {printf("%s", __func__);}
void _selectall(void) {printf("%s", __func__);}

struct MenuItem file_mit[]={
    {'n', "Creat a new file", MENU_ACTION, {.action= _newfile}},
    {'o', "open an existing file", MENU_ACTION, {.action= _openfile}},
    {0}
};

struct Menu File={
    "File", file_mit
};

struct MenuItem copy_mit[]={
    {'c', "Copy to clipboard", MENU_ACTION, {.action= _copytoclipboard}},
    {'f', "Copy to file", MENU_ACTION, {.action= _copytofile}},
    {0}
};

struct Menu copy={
    "Copy",
    copy_mit
};

struct MenuItem edit_mit[]={
    {'c', "Copy a text", MENU_SUBMENU, {.menu= &copy}},
    {'v', "Paste a text", MENU_ACTION, {.action= _paste}},
    {'a', "Select all text", MENU_ACTION, {.action= _selectall}},
    {0}
};

struct Menu edit={
    "Edit",
    edit_mit
};

struct MenuItem root_mit[]={
    {'f', "file", MENU_SUBMENU, {.menu= &File} },
    {'e', "Edit", MENU_SUBMENU, {.menu= &edit}},
    {0}
};

struct Menu root={
    "Root",
    root_mit
};

int main()
{
    menu_set_root(&root);
    char input[4];
    while(1)
    {
        fgets(input, 4, stdin);
        menu_process_user_input(input[0]);
    }
    return 0;
}