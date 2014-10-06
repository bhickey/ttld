// Copyright 2014 Brendan Hickey
// Released under the MIT license.
// See LICENSE.

#ifndef __TTLD_HDR__
#define __TTLD_HDR__

#include <stdint.h>

uint32_t parse_time(const char* timeval);
int expire(const char* d_name, uint32_t ttl_s);

#endif /* __TTLD_HDR__ */
