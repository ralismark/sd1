#pragma once

#include <exception>

class except : public std::exception
{
	const char* msg;
	const char* dflt_msg = "Unspecified error";
public:
	except();
	except(const char* fmt, ...);
	virtual ~except();

	virtual const char* what() const noexcept;
};
