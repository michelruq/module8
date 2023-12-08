#include "baseexception.h"

BaseException::BaseException(exceptionState exceptionState, int length) : _exceptionState(exceptionState), _length(length)
{

}

const char* BaseException::what() const noexcept
{
	return "The base exception happened";
}

std::string BaseException::getInfo()
{
	return StringContainer.prepareMessage(_exceptionState, _length);
}

BaseException::~BaseException()
{

}

