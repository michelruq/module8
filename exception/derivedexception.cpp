#include "derivedexception.h"

DerivedException::DerivedException(exceptionState exceptionState, int length, int index) : BaseException(exceptionState, length), _index(index)
{

}

const char* DerivedException::what() const noexcept
{
	return "The derived exception happened";
}

std::string DerivedException::getInfo()
{
	return StringContainer.prepareMessage(_exceptionState, _length, _index);
}

DerivedException::~DerivedException()
{

}