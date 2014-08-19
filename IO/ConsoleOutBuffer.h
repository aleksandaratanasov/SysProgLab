#ifndef CONSOLE_OUT_BUFFER_H_
#define CONSOLE_OUT_BUFFER_H_

#include "OutBuffer.h"

// TODO: no longer needed; used to print buffer's content to the console
class ConsoleOutBuffer: public OutBuffer {

public:

	ConsoleOutBuffer();
	virtual ~ConsoleOutBuffer();
	virtual void outBufferWrite(char* out);
	virtual void flush();

};

#endif /* CONSOLEOUTBUFFER_H_ */
