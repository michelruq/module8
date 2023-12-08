#include "stringcontainer.h"

std::string StringContainer::prepareMessage(exceptionState exceptionState, int length)
{
	return messages[int{ exceptionState }] + std::to_string(length) + expectedMessages[int{ exceptionState }];
}

std::string StringContainer::prepareMessage(exceptionState exceptionState, int length, int index)
{
	return messages[int{ exceptionState }] + std::to_string(index) + expectedMessages[int{ exceptionState }] + std::to_string(length);
}
