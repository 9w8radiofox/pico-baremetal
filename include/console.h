#ifndef __COMMON_CONSOLE_H__
#define __COMMON_CONSOLE_H__

#include "types.h"

struct console_device {
	/** Name of the console device */
	char name[32];

	/** Write a character to the console output */
	void (*console_putc)(char ch);

	/**
	 * Wait for a character on the uart device before return it.
	 *
	 * @param dev handle to the uart device.
	 * Return: <0 - error, other - the value of the character.
	 */
	int (*console_getc)(void);

	/**
	 * Test if a character has been typed on the uart device and return immediately.
	 *
	 * @param dev handle to the uart device.
	 * Return: <0 - no character, other - the value of the character.
	 */
	int (*console_tstc)(void);
};

void console_set_device(const struct console_device *dev);

const struct console_device *console_get_device(void);

int console_init(void);

char *console_gets(char *s);
int console_sprintf(char *out, const char *format, ...);

#endif /* __COMMON_CONSOLE_H__ */
