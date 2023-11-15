#ifndef __SHELL_H_
#define __SHELL_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct shell_setup;

struct shell_cmd
{
	const char *cmd;
	const char *desc;
	int (*func)(const char *args, struct shell_setup *setup);
};

struct shell_setup
{
	const char *banner;
	const char *prompt;
	const struct shell_cmd *cmds;
	const int cmds_num;
	void *priv;
};

void shell_start(struct shell_setup *setup);
const char *shell_parse_long(const char *args, unsigned long *value);

const char *trim(const char *s);
void shell_demo(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SHELL_H_ */
