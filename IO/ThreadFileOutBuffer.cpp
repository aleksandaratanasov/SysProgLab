#include "ThreadFileOutBuffer.h"

#include "OutBuffer.h"
#include "BufferMonitor.h"

#include <string.h>
#include <iostream>

#include <stdlib.h>		// posix_menalign
#include <fcntl.h> 		// Constants for file operations
#include <unistd.h> 	// File operations

#define NUMBER_OF_OUT_BUFFERS 3
#define BUFFER_SIZE 1

using std::cout;


void *t_ThreadFileOutBuffer(void* m)  {
  ThreadFileOutBuffer* t_master = (ThreadFileOutBuffer*)m;
  BufferMonitor* t_actual = &(t_master->buffers[0]);

  while(true) {
    t_actual->startRead();
    {
      int num = write(t_master->datei, t_actual->buffer_void, t_master->buffer_size);
      if (num < 0)
    std::cerr << "Error: unable to write " << t_master->position  << " bytes to file" << std::endl  << "Error code: " << num << std::endl;
      if (t_actual->lastBlock)
	pthread_exit(0);
    }
    t_actual = t_actual->endRead();
  }
}

ThreadFileOutBuffer::ThreadFileOutBuffer(const char* path) {
  buffer_size = getpagesize() * BUFFER_SIZE ;

  buffers = new BufferMonitor[NUMBER_OF_OUT_BUFFERS];
  for (int i = 0; i < NUMBER_OF_OUT_BUFFERS; ++i) {
    buffers[i].startRead(); // block all
    buffers[i].init(&buffers[(i+1)%NUMBER_OF_OUT_BUFFERS],buffer_size);
  }
  actual = &buffers[0];
  actual->startWrite();
  position = 0;

  datei = open(path, O_DIRECT | O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (datei < 0)
    std::cerr << "Error: unable to open file \"" << path << "\". No data will be written" << std::endl;

  pthread_create(&theThread, 0, t_ThreadFileOutBuffer, (void *)this);
}

ThreadFileOutBuffer::~ThreadFileOutBuffer() {
  while (position < buffer_size)
    actual->buffer_char[position++] = '\0';
  actual->lastBlock = true;
  file_write();
  pthread_join(theThread,0);
  close(datei);
  delete[] buffers;
}

void ThreadFileOutBuffer::outBufferWrite(char* out) {
  unsigned int length = 0;
  while (out[length] != '\0')
    ++length;
  if (position + length >= buffer_size) {
    unsigned int splitPos = buffer_size - position;
    memcpy(actual->buffer_char + position, out, splitPos);
    ThreadFileOutBuffer::file_write();
    memcpy(actual->buffer_char, out + splitPos, length - splitPos);
    position = length - splitPos;
  } else {
    memcpy(actual->buffer_char + position, out, length);
    position += length;

  }
}

inline void ThreadFileOutBuffer::file_write() {
  actual = actual->endWrite();
  position = 0;
  actual->startWrite();
}
