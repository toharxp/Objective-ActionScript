#include <stdio.h>
#include <stdlib.h>
extern char currentObject[64];
void ObjASParser();
void errorMessage(char *msg,...){ printf("[Objective-ActionScript 2.0]%s",msg);  }