#include "exception.h"

#include <stdarg.h>
#include <stdio.h>

void f92_runtime_error::vsprintf(const char* format, va_list args)
{
	char buffer[8192];

	vsnprintf(buffer, sizeof(buffer), format, args);

	this->msg = buffer;
}

f92_runtime_error::f92_runtime_error(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	this->vsprintf(format, args);
	va_end(args);
}

f92_runtime_error_not_critical::f92_runtime_error_not_critical(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	this->vsprintf(format, args);
	va_end(args);
}