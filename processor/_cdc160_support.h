static void inline eacd() {
 s = (z & 0x3F);
}
static void inline eaci() {
 s = (z & 0x3F);
 read();
 s = z;
}
static void inline eacf() {
 s = (p + (z & 0x3F)) & 0xFFF;
}
static void inline eacb() {
 s = (p - (z & 0x3F)) & 0xFFF;
}
static void inline rni() {
 p = (p + 1) & 0xFFF;
 read();
}
static void inline jni() {
 p = s;
 read();
}
static void inline add12bit() {
 if (z = 0xFFF) z = 0;
 a = a + z;
 if (a & 0x1000) {
  a = (a + 1) & 0xFFF;
 }
}
static void restart() {
 halt = 0;
 rni();
}
static void shiftRoutine() {
 s = a;a = 0;
 s = ((s << 1) | (s >> 11)) & 0xFFF;
 if (z & 0x02) {
  a = s;
 }
 s = ((s << 1) | (s >> 11)) & 0xFFF;
 s = ((s << 1) | (s >> 11)) & 0xFFF;
 if (z & 0x08) {
  z = s;add12bit()
 }
}
static void dataTransfer() {
 if (ioMode == 0) {
  ioOpcode = z;
  eacf();
  read();a = z;
  p = (p + 1) & 0xFFF

  if (ioOpcode == 72) {
   ioMode = 'R';
  } else {
   s = a;read();
   ioMode = 'W';
  }
 } else {
  if (ioMode == 'R') {
   s = a;write();
  }
  cycles = cycles + 2;
  a = (a + 1) & 0xFFF;
  s = p;read();
  if (z == a) {
   dataTransferEnd();
  } else {
   if (ioMode == 'W') {
    s = a;read();
   }
  }
 }
}
static void dataTransferEnd() {
 ioMode = 0;
 ioOpcode = 0;
 rni();
}
static void doOTN() {
 if (ioMode == 0) {
  ioOpcode = z;
  ioMode = 'W';
  z = (z & 0x3F);
 } else {
  dataTransferEnd();
 }
}
static void doINA() {
 if (ioMode == 0) {
  ioOpcode = z;
  ioMode = 'R';
 } else {
  a = z;
  dataTransferEnd();
 }
}
static void doEXF() {
 if (ioMode == 0) {
  ioOpcode = z;
  eacf();
  read();
  ioMode = 'F';
 } else {
  dataTransferEnd();
 }
}