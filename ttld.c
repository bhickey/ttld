// Copyright 2014 Brendan Hickey
// Released under the MIT license.
// See LICENSE.

#include "ttld.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

uint32_t parse_time(const char* timeval) {
  if (!timeval) {
    return 0;
  }
  char suffix = timeval[strlen(timeval) - 1];
  uint32_t m;
  switch (suffix) {
    case 'y':
      m = (uint32_t) (365.25 * 24 * 60 * 60);
      break;
    case 'M':
      m = 30 * 24 * 60 * 60;
      break;
    case 'w':
      m = 7 * 24 * 60 * 60;
      break;
    case 'd':
      m = 24 * 60 * 60;
      break;
    case 'h':
      m = 60 * 60;
      break;
    case 'm':
      m = 60;
      break;
    case 's':
      m = 1;
      break;
    default:
      m = 60 * 60; // Assume hours.
  }
  long result = strtol(timeval, NULL, 10);
  if (result < 0) {
    return 0;
  }
  return (uint32_t) result * m;
}

bool expire(const char* d_name, uint32_t ttl_s, bool ttl_dir) {
  time_t t = time(NULL);
  DIR* d = opendir(d_name);
  if (!d) {
    return 0;
  }
  size_t num_total = 0;
  size_t num_expired = 0;
  while (1) {
    struct dirent* entry = readdir(d);
    if (!entry) {
      break;
    }
    if (strcmp(".", entry->d_name) == 0 ||
        strcmp("..", entry->d_name) == 0) {
      continue;
    }
    ++num_total;
    // No TTL and this isn't a dir? Skip a bit.
    if (!ttl_s && !(entry->d_type & DT_DIR)) {
      continue;
    }
    if (entry->d_type & DT_DIR) {
      bool ttl_dir = false;
      uint32_t next_ttl_s = ttl_s;
      if (strncmp("ttl=", entry->d_name, 4) == 0) {
        uint32_t dir_ttl = parse_time(entry->d_name + 4);
        if (dir_ttl) {
          ttl_dir = true;
          next_ttl_s = dir_ttl;
        }
      }
      char path[PATH_MAX];
      if (PATH_MAX < snprintf(path, PATH_MAX, "%s/%s", d_name, entry->d_name)) {
        continue;
      }
      if (expire(path, next_ttl_s, ttl_dir) && !ttl_dir) {
        rmdir(path);
      }
    }
    if (ttl_s && entry->d_type & DT_REG) {
      char path[PATH_MAX];
      const size_t path_len =
        (size_t) snprintf(path, PATH_MAX, "%s/%s", d_name, entry->d_name);
      if (PATH_MAX < path_len) {
        continue;
      }
      struct stat statbuf;
      if (stat(path, &statbuf) == -1) {
        continue;
      }
      if (statbuf.st_mtime + ttl_s < t) {
        if (unlink(path) == 0) {
          ++num_expired;
        }
      }
    }
  }
  return num_total == num_expired;
}
