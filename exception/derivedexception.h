#pragma once

#include "baseexception.h"

class DerivedException : public BaseException
{
public:
	DerivedException(exceptionState exceptionState, int length, int index);
	const char* what() const noexcept override;
   std::string getInfo();
	~DerivedException();

private:
	int _index;
   
};

