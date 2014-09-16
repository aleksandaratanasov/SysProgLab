#include "ConsoleOutBuffer.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

ConsoleOutBuffer::ConsoleOutBuffer() {
}

ConsoleOutBuffer::~ConsoleOutBuffer() {
}

void ConsoleOutBuffer::flush() {
 cout << endl;
}

void ConsoleOutBuffer::outBufferWrite(char* out) {
	cout << out;
}
