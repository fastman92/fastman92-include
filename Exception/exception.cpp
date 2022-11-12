#include "exception.h"

#include <stdarg.h>
#include <stdio.h>

f92_runtime_error::f92_runtime_error(const char *format, ...)
{
	char buffer[8192];

	va_list args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	this->msg = buffer;
}