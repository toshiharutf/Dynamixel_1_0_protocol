#include "dynamixel_protocol_1.h"

__uint8_t DynamixelMX::checksum(__uint8_t *message) {
  __uint8_t sum = 0;

  for (int i = 0; i < sizeof(message); ++i)
  {
    sum += message[i];
  }

  return ~sum; // adding header
}
