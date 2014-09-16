#include <pthread.h>
#include <string.h>
#include <iostream>

#include <stdlib.h> //posix_menalign, free
#include <fcntl.h> // Konstanten für Dateioperationen
#include <unistd.h> // Dateioperationen

#include "ThreadInBuffer.h"

#define IN_BUFFER_SIZE 16
#define NUMBER_OF_OUT_BUFFERS 4

using std::cout;
using std::endl;
using std::cerr;

class BufferMonitor;

void *t_ThreadInBuffer(void* m)  {
  ThreadInBuffer* t_master = (ThreadInBuffer*)m;
  BufferMonitor* t_actual = &(t_master->buffers[0]);

  while(true) {
    t_actual->startWrite();
    {
      unsigned int num = read(t_master->file, t_actual->buffer_void, t_master->buffer_size);
      if (num < 0)
    cerr << "Error: unable to read " << t_master->position  << " bytes from file" << endl  << "Error code: " << num << endl;
      for ( ; num < t_master->buffer_size; ++num)
	t_actual->buffer_char[num] = '\0';
    }
    t_actual = t_actual->endWrite();
  }
  return 0;
}

ThreadInBuffer::ThreadInBuffer(const char* path) {
  buffer_size = getpagesize() * IN_BUFFER_SIZE ;

  buffers = new BufferMonitor[NUMBER_OF_OUT_BUFFERS];
  for (int i = 0; i < NUMBER_OF_OUT_BUFFERS; ++i) {
    buffers[i].startRead(); // block all
    buffers[i].init(&buffers[(i+1)%NUMBER_OF_OUT_BUFFERS],buffer_size);
  }

  file = open(path, O_SYNC, O_DIRECT, O_RDONLY);
  if (file <= 0) {
    cerr << "Error: unable to find file \"" << path << "\" or unable to read from it";
    exit(101);
  }

  pthread_create(&theThread, 0, t_ThreadInBuffer, (void *)this);

  line = 1;
  position = 0;
  former = 0;
  buffer = actual = &buffers[0];
  actual->startRead();
}

ThreadInBuffer::~ThreadInBuffer() {
  close(file);
  pthread_cancel(theThread);
  delete[] buffers;
}

unsigned int ThreadInBuffer::getLine() {
  return line;
}

unsigned int ThreadInBuffer::getColumn() {
  return column;
}

char* ThreadInBuffer::getChar() {
  if (position >= buffer_size) {
    if (buffer == former) {
      buffer = actual;
    } else {
      former = (former != 0) ? former->endRead() : actual;
      buffer = actual = actual->startNextRead();
    }
    position = 0;
  }
  if (buffer->buffer_char[position] == '\n') {
    ++line;
    lastColumnCount = column;
    column = 1;
  } else {
    ++column;
  }
  return &(buffer->buffer_char[position++]);
}

unsigned int ThreadInBuffer::back(unsigned int i) {
  bool linewrap = false;
  unsigned int pos;
  for (pos = 0; pos < i; ++pos) {
    if (position == 0) {
      if (buffer == former) {
    cerr << "Error: buffer underflow";
	return 0;
      } else {
	buffer = former;
	position = buffer_size-1;
      }
    }
    if (buffer->buffer_char[position--] == '\n') {
      --line;
      if (linewrap) {
	return pos;
      }
      column = lastColumnCount-1;
      linewrap=true;
    } else
      --column;
  }
  return pos;
}

