#ifndef _THREAD_IN_BUFFER__DEFINED__
#define _THREAD_IN_BUFFER__DEFINED__

//#include "InBuffer.h"
#include "BufferMonitor.h"
#include "InBuffer.h"

// Buffer used for reading a source file. It extends the InBuffer by adding thread-support so
// that reading from a file is done in a separate thread. If the source file is not found, the
// application exits with error 101.
// Note: after the initialization is complete, the pointer points at the address before the first
// character in the source file
class ThreadInBuffer: public InBuffer {
  // Called as a separate thread for reading data from a file
  friend void *t_ThreadInBuffer(void* m);

  void* buffer_void;

  BufferMonitor* buffers;
  BufferMonitor* former;
  BufferMonitor* actual;
  BufferMonitor* buffer;

  pthread_t theThread;

public:

  // Creates a threaded buffer with a given source file
  ThreadInBuffer(const char* path);

  // Relseases the buffer
  virtual ~ThreadInBuffer();

  // Returns the line in the source file where the pointer is pointing at
  virtual unsigned int getLine();

  // Returns the column in the source file where the pointer is pointing at
  virtual unsigned int getColumn();

  // Moves the pointer to the next character in the source file and returns the new position
  // Note: in case EOF is reached, the rest of the buffer will be filled with '\0'
  // Warning: accessing further results in an access error
  virtual char* getChar();

  // Returns i characters backwards in the source file by moving the reading pointer
  // Note: following cases are present:
  //  - i is greater than the number of characters present inside the buffer, application exits with error 100
  //  - if going backwards encounters multiple '\n', only the first new line will lead to change in the column;
  //    each of the next new lines will not be taken into consideration and the pointer will not move further
  //    backwards
  virtual unsigned int back(unsigned int i);
};

#endif
