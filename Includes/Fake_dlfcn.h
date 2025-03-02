#include <cstdlib>
#include <string.h>
#include <unistd.h>

extern "C" {
  void *dlopen_ex(const char *filename, int flags);
  void *dlsym_ex(void *handle, const char *symbol);
  int dlclose_ex(void *handle);
  const char *dlerror_ex();
};