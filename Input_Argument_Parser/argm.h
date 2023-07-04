struct Option 
{
    char sname;
    char *lname;
    char *desc;
    void (*action)(void *);
};

void argm_parse(struct Option *option, int argc, char *argv[]);