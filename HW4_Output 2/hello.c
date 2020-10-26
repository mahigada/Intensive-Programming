#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {
    printf("argc: addr=%x val=%x\n",&argc,argc);
    printf("argv: addr=%x val=%x\n\n",&argv,argv);
    if(argc>1){
        for (int i=0; i<argc;i++){
            printf("argv[%s]=%x\n",*argv,&argv[i]);
            for (;**argv;++*argv){
                printf("argv[%c]=%x\n",**argv,&(**argv));
            }
            argv++;
        }
    }
}
