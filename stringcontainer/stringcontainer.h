#pragma once
#include <string>

enum exceptionState
{
	es_ctor,
	es_insertBefore,
	es_remove,
	es_getter
};

class StringContainer
{
public:
	StringContainer() = default;
	std::string prepareMessage(exceptionState exceptionState, int length);
	std::string prepareMessage(exceptionState exceptionState, int length, int index);

private:
	const std::string messageForCtor = " There is the exception in constructor, because length is incorrect and equal to ";
	const std::string messageForInsertBuffer = " There is the exception when insertBefore method is calling, because index is incorrect and equal to ";
	const std::string messageForRemove = " There is the exception when remove method is calling, because index is incorrect and equal to ";
	const std::string messageForGetter = " There is the exception when operator[] is calling, because index is incorrect and equal to ";

	const std::string expectedMessageForCtor = " however expected more than 0 ";
	const std::string expectedMessageForOther = " however expected in range from 0 to ";

	const std::string expectedMessages[4]
	{
		expectedMessageForCtor,
		expectedMessageForOther,
		expectedMessageForOther,
		expectedMessageForOther
	};

	const std::string messages[4]
	{
		messageForCtor,
		messageForInsertBuffer,
		messageForRemove,
		messageForGetter
	};

};

