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


// void uart_gets(char *buffer, size_t size) {
//     size_t index = 0;

//     while (index < size - 1) {
//         char c = uart_getc(uart0);
//         if (c == '\n') {
//             break;  // Stop on newline
//         }
//         buffer[index++] = c;
//     }

//     buffer[index] = '\0';  // Null-terminate the string
// }


int main() {
	stdio_init_all();

	// char userInput;

    // while (1) {
        
    //     printf("Enter something: ");
	// 	// scanf("%i", input_buffer); // need to enter ascii number of the character
	// 	// userInput = getchar(); // input character 

    //     printf("You entered: %s\n", userInput);
    // }

    shell_start(&top_setup);
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
