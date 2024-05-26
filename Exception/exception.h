#pragma once
#include <string>

#include <stdexcept>

class f92_runtime_error : public std::exception
{
protected:
	std::string msg;
	void vsprintf(const char* format, va_list args);
	f92_runtime_error() {};

public:
	
	f92_runtime_error(const char *format, ...);

	virtual const char* what() const noexcept override { return msg.c_str(); }

};

class f92_runtime_error_not_critical : public f92_runtime_error
{
public:
	f92_runtime_error_not_critical(const char *format, ...);
};