#pragma once
#include <string>
#include <stdexcept>

class f92_runtime_error : public std::exception
{
	std::string msg;

public:
	f92_runtime_error(const char *format, ...);

	virtual const char* what() const noexcept override { return msg.c_str(); }

};