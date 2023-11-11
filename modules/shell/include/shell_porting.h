#ifndef __SHELL_PORTING_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../../../include/console.h"

#define SHELL_PRINTF      printf
//#define SHELL_GETS(buf)   (const char *)getchar()
// #define SHELL_GETS(buf)   fgetc(buf) //causing exception
// #define SHELL_GETS(buf)   ungetc(buf, stdin)
#define SHELL_GETS(buf)   gets(buf)
// #define SHELL_GETS(buf)   getc(buf) //causing exception
// #define SHELL_GETS(buf)   fgets(&buf, sizeof(buf), stdin)  

#endif /* __SIMPLE_SHELL_PORTING_H_ */
