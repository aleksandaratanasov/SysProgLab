#ifndef BUFFER_HANDLER_DEFINED
#define BUFFER_HANDLER_DEFINED

#include <pthread.h>

// BufferMonitor controls the access to the buffers both writing (startWrite/endWrite) and reading (startRead/endRead)
// When a start function is called, while the array is used, the calling thread is blocked until the array is released for access by others
class BufferMonitor {

private:
  // Next monitor in the chain
  BufferMonitor* next;
  
  // Mutexes for reading and writing access
  pthread_mutex_t r_Mutex,w_Mutex;
  
public:
  
  // Marks the last block that is to be processed and signals the thread to be terminated
  bool lastBlock;
  
  // Array with the data from a given source file as char
  char* buffer_char;
  
  // Array with the data from a given source file as void (required for the thread-calls)
  void* buffer_void;

  // Initializes the buffer. A successor is set that is used once the data in the current one is processed.
  // Memory for the buffer of size bufferSize is reserved. We use POSIX memalign, so that we can access it via read and write
  void init(BufferMonitor* next, int bufferSize);

  // Creates a monitor and reserves memory for the array
  BufferMonitor();
  
  ~BufferMonitor();

  // Starts the reading process using the array returning the address of the array
  char* startRead();

  // Starts the reading process using the next array in the chain of buffers returning the monitor that is next in the chain
  BufferMonitor* startNextRead();

  // Ends the reading process using the next array in the chain of buffers returning the monitor that is next in the chain
  BufferMonitor* endRead();

  // Starts the writing process using the array returning the address of the array
  char* startWrite();

  // Ends the reading process using the next array in the chain of buffers returning the monitor that is next in the chain
  BufferMonitor* endWrite();
  
};

#endif //_BUFFER_HANDLER_DEFINED
