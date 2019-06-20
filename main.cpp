#include <iostream>
#include <boost/format.hpp>
#include "dynamixel_protocol_1.h"
#include "serial_linux.h"

int main() {
  uint8_t message[] = {0x01, 0x05, 0x03, 0x1E, 0XF4, 0x01};
  int checksum = static_cast<int>(DynamixelMX::checksum(message) );
  std::cout << "Checksum is:" << boost::format("0x%02x") %checksum << std::endl;

  serial_linux usb2dynamixel;
  usb2dynamixel.init("/dev/ttyUSB0");
  unsigned char message2[] = {0xFF,0xFF,0x02,0x05,0x03,0x1E,0x00,0x00,0xD7};
  usb2dynamixel.write(message2);
  sleep(2);
  unsigned char message3[] = {0xFF,0xFF,0x02,0x05,0x03,0x1E,0xA0,0x0F,0x28};
  usb2dynamixel.write(message3);

  return 0;
}