// Copyright 2014 Brendan Hickey
// Released under the MIT license.
// See LICENSE.

#ifndef __TTLD_HDR__
#define __TTLD_HDR__

#include <stdint.h>
#include <stdbool.h>

uint32_t parse_time(const char* timeval);
bool expire(const char* d_name, uint32_t ttl_s, bool ttl_dir);

#endif /* __TTLD_HDR__ */
