/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "../include/main.h"
#include "../include/types.h"
#include "../modules/shell/include/shell.h"

static int func_math_add_a_b(const char *args, struct shell_setup *setup)
{
	int n = (int)(long)(void*)(setup->priv);
	unsigned long a, b;
	const char *s = args;
	s = shell_parse_long(s, &a);
	s = shell_parse_long(s, &b);
	printf("%d:%u + %u = %u\n", n, a, b, a + b);
	return 0;
}

static int func_math_sub_a_b(const char *args, struct shell_setup *setup)
{
	int n = (int)(long)(void*)(setup->priv);
	long a, b;
	const char *s = args;
	s = shell_parse_long(s, &a);
	s = shell_parse_long(s, &b);
	printf("%d:%u - %u = %u\n", n, a, b, a - b);	
	return 0;
}

const struct shell_cmd math_cmds[] = {
	{ "add",   "a b    - calc a+b",  func_math_add_a_b   },
	{ "sub",   "a b    - calc a-b",  func_math_sub_a_b   },
};

struct shell_setup math_0_setup = {
	.banner = "<TODO: banner for demo/math:0>",
	.prompt = "demo/math:0",
	.cmds = math_cmds,
	.cmds_num = ARRAY_SIZE(math_cmds),
	.priv = (void*)0,
};

struct shell_setup math_1_setup = {
	.banner = "<TODO: banner for demo/math:1>",
	.prompt = "demo/math:1",
	.cmds = math_cmds,
	.cmds_num = ARRAY_SIZE(math_cmds),
	.priv = (void*)1,
};

static int func_top_math(const char *args, struct shell_setup *setup)
{
	long n;
	shell_parse_long(args, &n);
	if (n == 0)
		shell_start(&math_0_setup);
	else if (n == 1)
		shell_start(&math_1_setup);
	return 0;
}

const struct shell_cmd top_cmds[] = {
	{ "math", "n    - Open sub menu for math #n",     func_top_math },
};
struct shell_setup top_setup = {
	.banner = "shell demo v1.0",
	.prompt = "demo",
	.cmds = top_cmds,
	.cmds_num = ARRAY_SIZE(top_cmds),
};

// console line settings
#define LINE_LEN 80
char commandLine[LINE_LEN + 1];

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



int main() {
	stdio_init_all();

    stdio_flush();
    setbuf(stdout, NULL); // make sure character input is buffered

	printf("Test printf : ");

	int16_t c; // must be 16 bit to get the error codes
	char lineBuffer[LINE_LEN + 1]; // define input buffer
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
		  // copy input line buffer to command line buffer
		  memcpy(commandLine, lineBuffer, LINE_LEN);
		  // clear input line buffer and send newline to terminal
		  cursor = clearBuffer(lineBuffer);
		  printf("\n");
		  // release command semaphore to enable processing of command line
//		  sem_release(&semCommand);
		  continue;
		}
		// handle backspace / del
		if (c == 0x7f || c == 0x08) {
		  if (cursor == 0) continue;
		  cursor = deleteChar(lineBuffer);
		  // use backspace, space, backspace to erase character on terminal
		  printf("%c%c%c", 0x08, ' ', 0x08);
		  continue;
		}
		// don't allow characters when at end of buffer
		if (cursor == LINE_LEN) continue;
		// handle character input
		cursor = appendChar(lineBuffer, c);
		printf("%c", c);
	  }

	//    shell_start(&top_setup);

// #ifndef PICO_DEFAULT_LED_PIN
// #warning blink example requires a board with a regular LED
// #else
//     const uint LED_PIN = PICO_DEFAULT_LED_PIN;
//     stdio_init_all();
//     gpio_init(LED_PIN);
//     gpio_set_dir(LED_PIN, GPIO_OUT);
//     unsigned int i = 0;
//     while (true) {
//         printf("Hello, world! %d\n",i);
//         i++;
//         gpio_put(LED_PIN, 1);
//         sleep_ms(25);
//         gpio_put(LED_PIN, 0);
//         sleep_ms(2500);
//     }
// #endif
    return 0;
}
