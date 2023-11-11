#include <string.h>

#include "../include/shell_porting.h"
#include "../include/shell.h"

const char *trim(const char *s)
{
	const char *WHITE_CHARS = " \t\r\n";
	int i;
	size_t white_chars_len = strlen(WHITE_CHARS);

	while (s && *s) {
		for (i = 0; i < white_chars_len; i++) {
			if (*s == WHITE_CHARS[i]) {
				s++;
				continue;
			}
		}
		break;
	}
	return s;
}

static int display_help(struct shell_setup *setup)
{
	const struct shell_cmd *p = NULL;
	int cmd_width = 0, temp = 0;
	int i;

	if (setup->banner)
		SHELL_PRINTF("%s\n", setup->banner);

    SHELL_PRINTF("Options:\n");
    //width
    for (i = 0, p = setup->cmds; i < setup->cmds_num && p && p->cmd; i++, p++) {
        temp = strlen(p->cmd);
        cmd_width = (cmd_width < temp) ? temp : cmd_width;
    }
    //print cmd display_help message
    for (i = 0, p = setup->cmds; i < setup->cmds_num && p && p->cmd; i++, p++) {
        SHELL_PRINTF("  %-*s %s\n",
            cmd_width, p->cmd,
            p->desc ? p->desc : "");
    }

	return 0;
}

static int get_cmd_key_len(const char *cmd)
{
	int len = 0;
	while (cmd && *cmd != '\0' && *cmd != ' ') {
		len++;
		cmd++;
	}
	return len;
}

static int match_cmd(const char *s, const char *cmd, int cmd_key_len)
{
	if (!strncmp(s, cmd, cmd_key_len)) {
		//cmd chars match
		s += cmd_key_len;
		//and end with a white-space
		return *s == '\0' || s != trim(s);
	}
	return 0;
}

static int parse_cmd(const char *input, struct shell_setup *setup)
{
	const struct shell_cmd *p = NULL;
	int cmd_key_len;
	int i;

	for (i = 0, p = setup->cmds; i < setup->cmds_num && p && p->cmd; i++, p++) {
		cmd_key_len = get_cmd_key_len(p->cmd);
		if (p->func && input && match_cmd(input, p->cmd, cmd_key_len)) {
			p->func(trim(input+cmd_key_len), setup);
			return 0; //handled
		}
	}

	return 1; //not interest
}

static int builtin_quit(const char *s, struct shell_setup *setup)
{
	int *need_quit = setup->priv;
	if (need_quit) {
		*(int*)need_quit = 1;
	}
	return 0;
}

void shell_start(struct shell_setup *setup)
{
	if (!setup)
		return ;
	int need_quit = 0;
	const struct shell_cmd builtin_cmds[] = {
		{"q", "quit", builtin_quit},
	};
	struct shell_setup builtin_setup = {
		.prompt = setup->prompt,
		.cmds = builtin_cmds,
		.cmds_num = ARRAY_SIZE(builtin_cmds),
		.priv = &need_quit
	};
	static char buf[2048] = {0};
	const char *input = NULL;
	static int need_builtin_hint = 1;

	if (need_builtin_hint) {
		SHELL_PRINTF("'h' or '?' for help, 'q' to quit\n");
		need_builtin_hint = 0;
	}
	while(!need_quit) {
		SHELL_PRINTF("%s# ", (setup->prompt ? setup->prompt : ""));
		input = trim(SHELL_GETS(buf));
		if (*input == '\0') {
			continue;
		}

		//parse input cmd
		if (match_cmd(input, "?", 1) || match_cmd(input, "h", 1)) {
			display_help(setup);
			SHELL_PRINTF("\n");
		} else if (parse_cmd(input, setup) &&
			parse_cmd(input, &builtin_setup)) {
			SHELL_PRINTF("invalid cmd\n");
		}
	}
}

const char *shell_parse_long(const char *args, unsigned long *value)
{
	char *end = NULL;
	if (args && value) {
		*value = strtoul(args, &end, 0);
		if (end > args)
			return trim(end);
	}
	return NULL;
}