#include "jtag.h"
#include <wiring_private.h>

#define TDI 12
#define TDO 15
#define TCK 13
#define TMS 14
#define MB_INT 28
#define MB_INT_PIN 31
#define SIGNAL_OUT 41 // B5 L16
#define SIGNAL_IN 33  // B2 N2

#define no_data                                                                \
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,      \
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  \
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  \
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00

#define NO_BOOTLOADER no_data
#define NO_APP no_data
#define NO_USER_DATA no_data

#ifdef VSCODE
extern void clockout(int a, int b);
#endif

__attribute__((used, section(".fpga_bitstream_signature")))
const unsigned char signatures[4096] = {
    //#include "signature.ttf"
    NO_BOOTLOADER,

    0x00,          0x00, 0x08, 0x00, 0xA9, 0x6F, 0x1F, 0x00, // Don't care.
    0x20,          0x77, 0x77, 0x77, 0x2e, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6d,
    0x65,          0x73, 0x2d, 0x65, 0x6d, 0x62, 0x61, 0x72, 0x71, 0x75, 0x65,
    0x73,          0x2e, 0x66, 0x72, 0x20, 0x00, 0x00, 0xff, 0xf0, 0x0f, 0x01,
    0x00,          0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // Force

    NO_USER_DATA,
};
__attribute__((used, section(".fpga_bitstream")))
const unsigned char bitstream[] = {
#include "app.h"
};

// the setup function runs once when you press reset or power the board
void setup() {

  int ret;
  uint32_t ptr[1];

  // enableFpgaClock();
  pinPeripheral(30, PIO_AC_CLK);
  clockout(0, 1);
  delay(1000);

  // Init Jtag Port
  ret = jtagInit();
  mbPinSet();

  // Load FPGA user configuration
  ptr[0] = 0 | 3;
  mbEveSend(ptr, 1);

  // Give it delay
  delay(1000);

  // Configure onboard LED Pin as output
  pinMode(LED_BUILTIN, OUTPUT);

  for (int i = 1; i < 12; i++) {
    pinMode(i, INPUT);
  }

  pinMode(12, OUTPUT);

  // Configure other share pins as input too
  pinMode(SIGNAL_IN, INPUT); // oSAM_INT
  pinMode(MB_INT_PIN, INPUT);
  pinMode(MB_INT, INPUT);

  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
  digitalWrite(0, LOW);
  delay(1000);
  while (!Serial);
}

// the loop function runs over and over again forever
void loop() {

  digitalWrite(12, HIGH);
  delay(1);
  digitalWrite(12, LOW);

  int bits = 0;
  for (int i = 1; i < 12; i++) {
    if (digitalRead(i) == HIGH) {
      bits |= (1 << (i - 1));
    }
  }
  Serial.println(bits);
  delay(10);
}
