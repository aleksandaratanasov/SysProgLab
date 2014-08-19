#include <pthread.h>
#include <stdlib.h> //posix_menalign, free
#include <unistd.h>

#include "BufferMonitor.h"

BufferMonitor::BufferMonitor() {
  // Initialize mutexes for reading and writing access
  pthread_mutex_init(&r_Mutex,0);
  pthread_mutex_init(&w_Mutex,0);
}

BufferMonitor::~BufferMonitor() {
  // Destroy mutexes for reading and writing access
  pthread_mutex_destroy(&r_Mutex);
  pthread_mutex_destroy(&w_Mutex);
  // Free memory for buffer
  free(buffer_void);
}

void BufferMonitor::init(BufferMonitor* next, int bufferSize) {
  posix_memalign(&buffer_void, getpagesize(), bufferSize);
  buffer_char = (char*) buffer_void;
  this->next = next;
}

BufferMonitor* BufferMonitor::startNextRead() {
  next->startRead();
  return next;
}

char* BufferMonitor::startRead() {
  pthread_mutex_lock(&r_Mutex);
  return buffer_char;
}

BufferMonitor* BufferMonitor::endRead() {
  pthread_mutex_unlock(&w_Mutex);
  return next;
} 

char* BufferMonitor::startWrite() {
  pthread_mutex_lock(&w_Mutex);
  return buffer_char;
}

BufferMonitor* BufferMonitor::endWrite() {
  pthread_mutex_unlock(&r_Mutex);
  return next;
} 
