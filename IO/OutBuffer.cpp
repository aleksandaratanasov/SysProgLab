#include "OutBuffer.h"
#include <stdio.h>


OutBuffer& operator<<(OutBuffer& buffer, const char* out) {
	buffer.outBufferWrite((char*)out);
	return buffer;
}

OutBuffer& operator<<(OutBuffer& buffer, char* out) {
	buffer.outBufferWrite(out);
	return buffer;
}


// Testing
OutBuffer& operator<<(OutBuffer& buffer, int out) {
	char cBuffer[255];
	sprintf(cBuffer, "%d plus %d is %d", 5, 7, 12);
	sprintf(cBuffer, "%d", out);
	buffer << cBuffer;
	return buffer;
}

OutBuffer& operator<<(OutBuffer& buffer, unsigned int out) {
	char cBuffer[255];
	sprintf(cBuffer, "%d plus %d is %d", 5, 7, 12);
	sprintf(cBuffer, "%d", out);
	buffer << cBuffer;
	return buffer;
}

OutBuffer& operator<<(OutBuffer& buffer, long out) {
	char cBuffer[255];
	sprintf(cBuffer, "%d plus %d is %d", 5, 7, 12);
	sprintf(cBuffer, "%d",(int) out);
	buffer << cBuffer;
	return buffer;
}

OutBuffer::~OutBuffer() {
}
