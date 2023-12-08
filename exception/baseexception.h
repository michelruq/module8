#pragma once
#include <exception>
#include "../stringcontainer/stringcontainer.h"

class BaseException : public std::exception
{
public:
	BaseException(exceptionState exceptionState, int length );
	const char* what() const noexcept override;
	std::string getInfo();
	~BaseException();

protected:
	StringContainer StringContainer;
	exceptionState _exceptionState;
	int _length;

};

