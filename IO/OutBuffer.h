#ifndef OUT_BUFFER_H_
#define OUT_BUFFER_H_

// Interface giving various possibilities for writing data to the interpreter file (see ThreadFileOutBuffer for more information)
class OutBuffer {

public:

	virtual ~OutBuffer();
    // Writes data in the buffer
	virtual void outBufferWrite(char* out) = 0;
};

// For ease of use overwritten << operator
extern OutBuffer& operator<<(OutBuffer& buffer, const char* out);
extern OutBuffer& operator<<(OutBuffer& buffer, char* out);

// Testing
extern OutBuffer& operator<<(OutBuffer& buffer, int out);
extern OutBuffer& operator<<(OutBuffer& buffer, unsigned int out);
extern OutBuffer& operator<<(OutBuffer& buffer, long out);

#endif /* OUT_BUFFER_H_ */
