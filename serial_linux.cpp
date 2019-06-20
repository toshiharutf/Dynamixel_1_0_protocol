//
// Created by toshi on 6/20/19.
//

#include "serial_linux.h"

serial_linux::~serial_linux() {
  close(serial_port_);
}

void serial_linux::init(const std::string port_name) {
  // SERIAL PORT initialization
  serial_port_ = open(port_name.c_str(), O_RDWR);

  if (serial_port_ < 0) {
    printf("Error %i from open: %s\n", errno, strerror(errno));
  }
  // Common errors
  // 2: No serial port found
  // 13: Permision denied
  // Tried adding your current  user to the dialout group:
  // sudo adduser $USER dialout

  if (tcgetattr(serial_port_, &tty) != 0)  {
    printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
  }
  tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
//  tty.c_cflag |= PARENB;  // Set parity bit, enabling parity
  tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
//  tty.c_cflag |= CSTOPB;  // Set stop field, two stop bits used in communication
  tty.c_cflag |= CS8; // 8 bits per byte
//  tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
//  //tty.c_cflag |= CRTSCTS;  // Enable RTS/CTS hardware flow control
//  tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
//  tty.c_lflag &= ~ICANON; // Disable cannonical mode
//  tty.c_lflag &= ~ECHO; // Disable echo
//  tty.c_lflag &= ~ECHOE; // Disable erasure
//  tty.c_lflag &= ~ECHONL; // Disable new-line echo
//  tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
//  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
//  tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes
//  tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
//  tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
//// tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT IN LINUX)
//// tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT IN LINUX)
//  tty.c_cc[VTIME] = 50;    // Wait for up to 0.5 (50 deciseconds), returning as soon as any data is received.
//  tty.c_cc[VMIN]  = 0;  // No minimum bytes
  cfsetispeed(&tty, B1000000);  // BAUD rate
  cfsetospeed(&tty, B1000000);

  // Save tty settings, also checking for error
  if (tcsetattr(serial_port_, TCSANOW, &tty) != 0)
  {
    printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
  }
}

void serial_linux::write(const unsigned char message[]) {
  uint8_t length=  sizeof(message) + 1;
  ::write(serial_port_, message, length);
}


