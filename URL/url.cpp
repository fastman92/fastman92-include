#include "url.h"

std::string urlencode(const std::string &s)
{
	//RFC 3986 section 2.3 Unreserved Characters (January 2005)
	const std::string unreserved = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_.~";

	std::string escaped = "";
	for (size_t i = 0; i<s.length(); i++)
	{
		if (unreserved.find_first_of(s[i]) != std::string::npos)
		{
			escaped.push_back(s[i]);
		}
		else
		{
			escaped.append("%");
			char buf[3];
			sprintf(buf, "%.2X", s[i]);
			escaped.append(buf);
		}
	}
	return escaped;
}