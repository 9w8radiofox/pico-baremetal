#ifndef __SHELL_PORTING_H_

#include <stdio.h>
#include <ctype.h>

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/stdio_uart.h"

#define SHELL_PRINTF      printf
// #define SHELL_GETS(buf)   gets(buf)
// #define BSHELL_GETS(buf)   fgets(buf, sizeof(buf), stdin)

// console line settings
#define LINE_LEN 80

int isValidCharacter(int ch) {
    // Check if the character is valid
    return isprint(ch); // isalpha(ch) || isspace(ch) || isdigit(ch);
}

char *SHELL_GETS(char *str){
    stdio_flush();
    setbuf(stdout, NULL); // make sure character input is buffered

	int i = 0;
	int16_t c; // must be 16 bit to get the error codes

	str[0] = 0;

	while((c = getchar()) != '\n' && c != EOF) {
		if (c <= 0x07) continue;
		if (c >= 0x09 && c <= 0x0c) continue;
		if (c >= 0x0e && c <= 0x1a) continue;
		if (c >= 0x1c && c <= 0x1f) continue;

		// handle escape sequence
		if (c == 0x1b) {
			continue;
		}

		if (c == 0x7f || c == 0x08) {
			if (i == 0) {
				str[i] = 0;
				continue;
			}
			// use backspace, space, backspace to erase character on terminal
			if (i > 0) {
				i--;
				str[i] = 0;
				printf("%c%c%c", 0x08, ' ', 0x08);
			}
			continue;
		}

		if (c == 0x0d) {
			printf("\n");
			return str;
		}
		
        if (i < LINE_LEN - 1 && isValidCharacter(c)) {
        	str[i+1] = 0;
            str[i++] = (char)c;
			printf("%c", c);
        }
		else
			continue;
    }
};


#endif /* __SIMPLE_SHELL_PORTING_H_ */
