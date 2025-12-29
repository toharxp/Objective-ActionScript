#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ObjASParser(int argc, char** argv){
    if(argc < 2){
        printf("Usage: objas <file.objas>", "");
        return;
    }

    FILE* f = fopen(argv[1], "rb");
    if(!f){
        printf("Failed to open %s", argv[1]);
        return;
    }

    char line_buf[512];

    while(fgets(line_buf, sizeof(line_buf), f)){
        char* line = line_buf;
        while(*line == ' ' || *line == '\t') line++; // trim left

          /* @interface */
        if(strncmp(line,"@startPackage",10)==0){
            char dir[512];
            sscanf(line,"@startPackage %63s", dir);
            printf("package %s{", dir);
            continue;
        }

        /* @interface */
        if(strncmp(line,"@interface",10)==0){
            char name[64];
            if(sscanf(line,"@interface %63s", name)==1){
                printf("public interface %s", name);
            }
            continue;
        }

        /* @implementation */
        if(strncmp(line,"@implementation",15)==0){
            char className[64], baseClass[64];
            if(sscanf(line,"@implementation %63s : %63s", className, baseClass)==2){
                printf("public class %s extends %s {\n", className, baseClass);
            }
            else if(sscanf(line,"@implementation %63s", className)==1){
                printf("public class %s {\n", className);
            }
            continue;
        }
        //[Class doto]
       if(strchr(line,'[') && strchr(line,']')){
            char Object[64], Action[128];
            
            if(sscanf(line," [ %63[^ ] %127[^]] ]", Object, Action) == 2){
                char* tempName = Object;
                printf("var objas_%s = new %s();\n",tempName,Object);
                printf("objas_%s.%s;",Object,Action);
            }
            continue;
        }
        if(strncmp(line,"@endPackage",11)==0){
            sscanf(line,"@endPackage");
            printf("} //end poit of package");
        }
        printf("%s", line);
    }

    fclose(f);
}
int main(int argc, char** argv)
{
    ObjASParser(argc,argv);
    return 0;
}
