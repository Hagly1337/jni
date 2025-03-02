#ifndef UTILS
#define UTILS

#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <android/log.h>
#include <libgen.h>
#include <fcntl.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/mman.h>
#include "Logger.h"
#include "xorstr.hpp"

#define HOOKAF(ret, func, ...) \
ret (*orig##func)(__VA_ARGS__); \
ret my##func(__VA_ARGS__)

uintptr_t GetBaseAddress(const char *name) { uintptr_t base = 0; char line[512]; FILE *f = fopen(OBFUSCATE("/proc/self/maps"), OBFUSCATE("r")); if (!f) { return 0; } while (fgets(line, sizeof line, f)) { uintptr_t tmpBase; char tmpName[256]; if (sscanf(line, "%" PRIXPTR "-%*" PRIXPTR "%*s %*s %*s %*s %s", &tmpBase, tmpName) > 0) { if (!strcmp(basename(tmpName), name)) { base = tmpBase; break; }}} fclose(f); return base; }
bool isLibraryLoaded(const char *libraryName) { char line[512] = {0}; FILE *fp = fopen(OBFUSCATE("/proc/self/maps"), OBFUSCATE("rt")); if (fp != NULL) { while (fgets(line, sizeof(line), fp)) {std::string a = line; if (strstr(line, libraryName)) { return true; }} fclose(fp); } return false; }
uintptr_t string2Offset(const char *c) { int base = 16; static_assert(sizeof(uintptr_t) == sizeof(unsigned long) || sizeof(uintptr_t) == sizeof(unsigned long long), "Please add string to handle conversion for this architecture."); if (sizeof(uintptr_t) == sizeof(unsigned long)) { return strtoul(c, nullptr, base); } return strtoull(c, nullptr, base); }

#endif
