// Copyright 2014 Brendan Hickey
// Released under the MIT license.
// See LICENSE.

#include "ttld.h"

int main (int argc, char** argv) {
  if (argc != 2) {
    return -1;
  }
  expire(argv[1], 0);
}
