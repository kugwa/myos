#include <stdarg.h>
#include "screen.h"

static unsigned int pos = 0;

void screen_clear()
{
	char *pv = (char*)0xb8000;
	unsigned int i;

	for (i = 0; i < 80 * 25 * 2; i += 2) {
		pv[i] = ' ';
		pv[i + 1] = 0x07;
	}
	pos = 0;
}

static void my_putc(int c)
{
	char *pv = (char*)0xb8000;
	if (pos >= 80 * 25 * 2) screen_clear();
	if (c == '\n') {
		pos = (pos / 160 + 1) * 160;
	}
	else {
		pv[pos] = c;
		pv[pos + 1] = 0x07;
		pos += 2;
	}
}

static void my_puts(const char *s)
{
	unsigned int i;
	for (i = 0; s[i] != '\0'; i++) my_putc(s[i]);
}

static void my_puth(unsigned int x)
{
    char x2c[] = "0123456789abcdef";
    char s[20], *ps;

    if (x == 0) my_putc('0');
    else {
        s[19] = '\0';
        ps = s + 18;
        for (; x; x /= 16, ps--) *ps = x2c[x % 16];
        my_puts(ps + 1);
    }
}

void screen_printf(const char *fmt, ...)
{
    va_list args;
    unsigned int i;

    va_start(args, fmt);
    for (i = 0; fmt[i]; i++) {
        if (fmt[i] == '%') {
            i++;
            if (fmt[i] == 'x') my_puth(va_arg(args, unsigned int));
            else if (fmt[i] == 's') my_puts(va_arg(args, const char *));
            else if (fmt[i] == '%') my_putc('%');
            else if (fmt[i] == '\0') break;
        }
        else my_putc(fmt[i]);
    }
    va_end(args);
}
