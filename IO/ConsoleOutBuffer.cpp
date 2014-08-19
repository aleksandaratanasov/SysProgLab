#include "ConsoleOutBuffer.h"
#include <iostream>

ConsoleOutBuffer::ConsoleOutBuffer() {
}

ConsoleOutBuffer::~ConsoleOutBuffer() {
}

void ConsoleOutBuffer::flush() {
 std::cout << std::endl;
}

void ConsoleOutBuffer::outBufferWrite(char* out) {
	std::cout << out;
}
