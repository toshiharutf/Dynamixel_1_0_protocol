#pragma once

#include <stdio.h>

class DynamixelMX
{
private:
  void write();
  void ping();
  void move();
  void config();

public:
  static __uint8_t checksum(__uint8_t *message);

};
