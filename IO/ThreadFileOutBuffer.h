#define F_B_SIZE 128

#ifndef T_FILE_OUT_BUFFER_H_
#define T_FILE_OUT_BUFFER_H_

#include "OutBuffer.h"
#include <pthread.h>

class BufferMonitor;

// Buffer used for writing to an interpreter file (a file that can be "executed" by an interpreter).
// It extends the InBuffer by adding thread-support so that writing to a file is done in a separate
// thread.
class ThreadFileOutBuffer: public OutBuffer {
  // Called as a separate thread for writing data to a file
  friend void *t_ThreadFileOutBuffer(void* m);

  int datei;
  unsigned int buffer_size;
  unsigned int position;
  void* buffer_void;
  BufferMonitor* buffers;
  BufferMonitor* actual;

  pthread_t theThread;

  // Once the buffer is filled, the content is written to an interpreter file so that the buffer can
  // be filled with new content
  void file_write();

public:
  // Creates a buffer using a given interpreter file
  ThreadFileOutBuffer(const char* path);

  // Releases the reserved memeory for the buffer
  virtual ~ThreadFileOutBuffer();

  // Writes an array of characters in the buffer
  virtual void outBufferWrite(char* out);
};

#endif /* OUTBUFFER_H_ */
