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

const struct shell_cmd demo_math_cmds[] = {
	{ "add",   "a b    - calc a+b",  func_math_add_a_b   },
	{ "sub",   "a b    - calc a-b",  func_math_sub_a_b   },
};
struct shell_setup demo_math_0_setup = {
	.banner = "<TODO: banner for demo/math:0>",
	.prompt = "demo/math:0",
	.cmds = demo_math_cmds,
	.cmds_num = ARRAY_SIZE(demo_math_cmds),
	.priv = (void*)0,
};
struct shell_setup demo_math_1_setup = {
	.banner = "<TODO: banner for demo/math:1>",
	.prompt = "demo/math:1",
	.cmds = demo_math_cmds,
	.cmds_num = ARRAY_SIZE(demo_math_cmds),
	.priv = (void*)1,
};

static int func_top_math(const char *args, struct shell_setup *setup)
{
	long n;
	shell_parse_long(args, &n);
	if (n == 0)
		shell_start(&demo_math_0_setup);
	else if (n == 1)
		shell_start(&demo_math_1_setup);
	return 0;
}

const struct shell_cmd demo_top_cmds[] = {
	{ "math", "n    - Open sub menu for math #n",     func_top_math },
};
struct shell_setup demo_top_setup = {
	.banner = "shell demo v1.0",
	.prompt = "demo",
	.cmds = demo_top_cmds,
	.cmds_num = ARRAY_SIZE(demo_top_cmds),
};

int main() {
	stdio_init_all();
	shell_start(&demo_top_setup);
    return 0;
}
