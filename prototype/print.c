#include <stdarg.h> 
#include <stdio.h> 
 
int print(const char *fmt, ...) 
{ 
  va_list va; 
  va_start(va, fmt); 
  int ret = vprintf(fmt, va); 
  va_end(va); 
  return ret; 
} 