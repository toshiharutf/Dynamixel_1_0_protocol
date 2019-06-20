#pragma once

// Linux headers for serial port communication
//https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#include <cstring>
#include <stdio.h>
#include <string>


class serial_linux {
public:
  serial_linux() = default;
  virtual ~serial_linux();

  int serial_port_{-1};
  void init(const std::string port_name);
  void write(const unsigned char message[]);

private:
  struct termios tty;
};


