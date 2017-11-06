case 0x00: /** err %d **/
   halt = 1;cycles = cycles + 1;break;
case 0x01: /** sha %d **/
   shiftRoutine();rni();cycles = cycles + 1;break;
case 0x02: /** lpn %d **/
   a = a & (z & 0x3F);rni();cycles = cycles + 1;break;
case 0x03: /** lsn %d **/
   a = a ^ (z & 0x3F);rni();cycles = cycles + 1;break;
case 0x04: /** ldn %d **/
   a = (z & 0x3F);rni();cycles = cycles + 1;break;
case 0x05: /** lcn %d **/
   a = (z & 0x3F) ^ 0xFFF;rni();cycles = cycles + 1;break;
case 0x06: /** adn %d **/
   z = (z & 0x3F);add12bit();rni();cycles = cycles + 1;break;
case 0x07: /** sbn %d **/
   z = (z & 0x3F) ^ 0xFFF;add12bit();rni();cycles = cycles + 1;break;
case 0x10: /** lpd %d **/
   eacd();read();a = a & z;rni();cycles = cycles + 2;break;
case 0x11: /** lpi %i **/
   eaci();read();a = a & z;rni();cycles = cycles + 3;break;
case 0x12: /** lpf %f **/
   eacf();read();a = a & z;rni();cycles = cycles + 2;break;
case 0x13: /** lpb %b **/
   eacb();read();a = a & z;rni();cycles = cycles + 2;break;
case 0x14: /** lsd %d **/
   read();a = a ^ z;rni();cycles = cycles + 2;break;
case 0x15: /** lsi %i **/
   read();a = a ^ z;rni();cycles = cycles + 3;break;
case 0x16: /** lsf %f **/
   read();a = a ^ z;rni();cycles = cycles + 2;break;
case 0x17: /** lsb %b **/
   read();a = a ^ z;rni();cycles = cycles + 2;break;
case 0x20: /** ldd %d **/
   eacd();read();a = z;rni();cycles = cycles + 2;break;
case 0x21: /** ldi %i **/
   eaci();read();a = z;rni();cycles = cycles + 3;break;
case 0x22: /** ldf %f **/
   eacf();read();a = z;rni();cycles = cycles + 2;break;
case 0x23: /** ldb %b **/
   eacb();read();a = z;rni();cycles = cycles + 2;break;
case 0x24: /** lcd %d **/
   eacd();read();a = z ^ 0xFFF;rni();cycles = cycles + 2;break;
case 0x25: /** lci %i **/
   eaci();read();a = z ^ 0xFFF;rni();cycles = cycles + 3;break;
case 0x26: /** lcf %f **/
   eacf();read();a = z ^ 0xFFF;rni();cycles = cycles + 2;break;
case 0x27: /** lcb %b **/
   eacb();read();a = z ^ 0xFFF;rni();cycles = cycles + 2;break;
case 0x30: /** add %d **/
   eacd();read();add12bit();rni();cycles = cycles + 2;break;
case 0x31: /** adi %i **/
   eaci();read();add12bit();rni();cycles = cycles + 3;break;
case 0x32: /** adf %f **/
   eacf();read();add12bit();rni();cycles = cycles + 2;break;
case 0x33: /** adb %b **/
   eacb();read();add12bit();rni();cycles = cycles + 2;break;
case 0x34: /** sbd %d **/
   eacd();read();z = z ^ 0xFFF;add12bit();rni();cycles = cycles + 2;break;
case 0x35: /** sbi %i **/
   eaci();read();z = z ^ 0xFFF;add12bit();rni();cycles = cycles + 3;break;
case 0x36: /** sbf %f **/
   eacf();read();z = z ^ 0xFFF;add12bit();rni();cycles = cycles + 2;break;
case 0x37: /** sbb %b **/
   eacb();read();z = z ^ 0xFFF;add12bit();rni();cycles = cycles + 2;break;
case 0x40: /** std %d **/
   eacd();mbr = a;write();rni();cycles = cycles + 3;break;
case 0x41: /** sti %i **/
   eaci();mbr = a;write();rni();cycles = cycles + 4;break;
case 0x42: /** stf %f **/
   eacf();mbr = a;write();rni();cycles = cycles + 3;break;
case 0x43: /** stb %b **/
   eacb();mbr = a;write();rni();cycles = cycles + 3;break;
case 0x44: /** srd %d **/
   eacd();read();z = ((z << 1) | (z >11)) & 0xFFF;a = z;write();rni();cycles = cycles + 3;break;
case 0x45: /** sri %i **/
   eaci();read();z = ((z << 1) | (z >11)) & 0xFFF;a = z;write();rni();cycles = cycles + 4;break;
case 0x46: /** srf %f **/
   eacf();read();z = ((z << 1) | (z >11)) & 0xFFF;a = z;write();rni();cycles = cycles + 3;break;
case 0x47: /** srb %b **/
   eacb();read();z = ((z << 1) | (z >11)) & 0xFFF;a = z;write();rni();cycles = cycles + 3;break;
case 0x50: /** rad %d **/
   eacd();read();add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x51: /** rai %i **/
   eaci();read();add12bit();z = a;write();rni();cycles = cycles + 4;break;
case 0x52: /** raf %f **/
   eacf();read();add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x53: /** rab %b **/
   eacb();read();add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x54: /** aod %d **/
   eacd();read();a = 1;add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x55: /** aoi %i **/
   eaci();read();a = 1;add12bit();z = a;write();rni();cycles = cycles + 4;break;
case 0x56: /** aof %f **/
   eacf();read();a = 1;add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x57: /** aob %b **/
   eacb();read();a = 1;add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x60: /** zjd %d **/
   eacd();if (a == 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x61: /** nzi %i **/
   eaci();if (a != 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x62: /** pjf %f **/
   eacf();if ((a & 0x800) == 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x63: /** njb %b **/
   eacb();if ((a & 0x800) != 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x64: /** zjd %d **/
   eacd();if (a == 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x65: /** nzi %i **/
   eaci();if (a != 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x66: /** pjf %f **/
   eacf();if ((a & 0x800) == 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x67: /** njb %b **/
   eacb();if ((a & 0x800) != 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x70: /** jpi %i **/
   eaci();jni();cycles = cycles + 2;break;
case 0x71: /** jfi %f **/
   eacf();read();s = z;jni();cycles = cycles + 2;break;
case 0x72: /** inp %f **/
   dataTransfer();cycles = cycles + 2;break;
case 0x73: /** out %f **/
   dataTransfer();cycles = cycles + 2;break;
case 0x74: /** otn %d **/
   doOTN();;cycles = cycles + 1;break;
case 0x75: /** exf %f **/
   doEXF();cycles = cycles + 1;break;
case 0x76: /** ina %c **/
   doINA();;cycles = cycles + 1;break;
case 0x77: /** hlt %d **/
   halt = 1;cycles = cycles + 1;break;
