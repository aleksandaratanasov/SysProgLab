#ifndef _IN_BUFFER__DEFINED__
#define _IN_BUFFER__DEFINED__

#include "BufferMonitor.h"
#include "InBuffer.h"

// Interface giving various possibilities for reading data from the source file (see ThreadInBuffer for more information)
class InBuffer {

protected:
  
  unsigned int line, column, position, blockSize, readSize, lastColumnCount;

  unsigned int buffer_size;

  unsigned int file;

public:

  // Create a reading buffer for a source file
  InBuffer();

  virtual ~InBuffer() = 0;

  // Returns the row of the reading pointer in the source file
  virtual unsigned int getLine() = 0;

  // Returns the column of the reading pointer in the source file
  virtual unsigned int getColumn() = 0;

  // Sets the reading pointer to the next character in the source file and returns its position
  // Note: in case EOF is reached, for the rest of the buffer '\0' is used. Further access results in memory access violation
  virtual char* getChar() = 0;

  // Returns i characters backwards in the source file by moving the reading pointer
  // Note: following cases are present:
  //  - i is greater than the number of characters present inside the buffer, application exits with error 100
  //  - if going backwards encounters multiple '\n', only the first new line will lead to change in the column;
  //    each of the next new lines will not be taken into consideration and the pointer will not move further
  //    backwards
  virtual unsigned int back(unsigned int i) = 0;

};

#endif
