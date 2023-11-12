#ifndef __SHELL_PORTING_H_

#include <stdio.h>
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

// clear contents of the specified buffer
size_t clearBuffer (char * buffer) {
  memset(buffer, '\0', LINE_LEN);
  return strlen(buffer);
}

// append a character to the input buffer and return new length
size_t appendChar (char * buffer, char c) {
  if (strlen(buffer) == LINE_LEN) return LINE_LEN;
  buffer[strlen(buffer)] = c;
  return strlen(buffer);
}

// delete character from input buffer and return length
size_t deleteChar (char * buffer) {
  if (strlen(buffer) == 0) return 0;
  buffer[strlen(buffer) - 1] = '\0';
  return strlen(buffer);
}

void flushInput () {
  int16_t c; // must be 16 bit to capture error codes
  do {
    // read characters until nothing left to read
    c = getchar_timeout_us(500);
  } while (c != PICO_ERROR_TIMEOUT && c != PICO_ERROR_GENERIC);
}

char *SHELL_GETS(char *str){
    stdio_flush();
    setbuf(stdout, NULL); // make sure character input is buffered

	int16_t c; // must be 16 bit to get the error codes
	// char lineBuffer[LINE_LEN + 1]; // define input buffer
	size_t cursor = 0;
	for (;;) {
	c = getchar();
		// some characters will not be processed
		if (c <= 0x07) continue;
		if (c >= 0x09 && c <= 0x0c) continue;
		if (c >= 0x0e && c <= 0x1a) continue;
		if (c >= 0x1c && c <= 0x1f) continue;
		// handle escape sequence
		if (c == 0x1b) {
			flushInput();
			continue;
		}
		// handle enter
		if (c == 0x0d) {
			// // copy input line buffer to command line buffer
			// memcpy(commandLine, lineBuffer, LINE_LEN);
			// clear input line buffer and send newline to terminal
			cursor = clearBuffer(str);
			printf("\n");
			// release command semaphore to enable processing of command line
	//		  sem_release(&semCommand);
			continue;
		}
		// handle backspace / del
		if (c == 0x7f || c == 0x08) {
			if (cursor == 0) continue;
			cursor = deleteChar(str);
			// use backspace, space, backspace to erase character on terminal
			printf("%c%c%c", 0x08, ' ', 0x08);
			continue;
		}
		// don't allow characters when at end of buffer
		if (cursor == LINE_LEN) continue;
		// handle character input
		cursor = appendChar(str, c);
		printf("%c", c);
	}

	return str;
};


#endif /* __SIMPLE_SHELL_PORTING_H_ */
