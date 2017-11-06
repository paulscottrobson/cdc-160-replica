case 0x00: /** err %d/err #%d **/
   halt = 1;cycles = cycles + 1;break;
case 0x01: /** sha %d/sha #%d **/
   shiftRoutine();rni();cycles = cycles + 1;break;
case 0x02: /** lpn %d/and #%d **/
   a = a & (z & 0x3F);rni();cycles = cycles + 1;break;
case 0x03: /** lsn %d/xor #%d **/
   a = a ^ (z & 0x3F);rni();cycles = cycles + 1;break;
case 0x04: /** ldn %d/ld #%d **/
   a = (z & 0x3F);rni();cycles = cycles + 1;break;
case 0x05: /** lcn %d/ldm #%d **/
   a = (z & 0x3F) ^ 0xFFF;rni();cycles = cycles + 1;break;
case 0x06: /** adn %d/add #%d **/
   z = (z & 0x3F);add12bit();rni();cycles = cycles + 1;break;
case 0x07: /** sbn %d/sub #%d **/
   z = (z & 0x3F) ^ 0xFFF;add12bit();rni();cycles = cycles + 1;break;
case 0x10: /** lpd %d/and %d **/
   eacd();read();a = a & z;rni();cycles = cycles + 2;break;
case 0x11: /** lpi %i/and (%d) **/
   eaci();read();a = a & z;rni();cycles = cycles + 3;break;
case 0x12: /** lpf %f/and %f **/
   eacf();read();a = a & z;rni();cycles = cycles + 2;break;
case 0x13: /** lpb %b/and %b **/
   eacb();read();a = a & z;rni();cycles = cycles + 2;break;
case 0x14: /** lsd %d/xor %d **/
   read();a = a ^ z;rni();cycles = cycles + 2;break;
case 0x15: /** lsi %i/xor (%d) **/
   read();a = a ^ z;rni();cycles = cycles + 3;break;
case 0x16: /** lsf %f/xor %f **/
   read();a = a ^ z;rni();cycles = cycles + 2;break;
case 0x17: /** lsb %b/xor %b **/
   read();a = a ^ z;rni();cycles = cycles + 2;break;
case 0x20: /** ldd %d/ld %d **/
   eacd();read();a = z;rni();cycles = cycles + 2;break;
case 0x21: /** ldi %i/ld (%d) **/
   eaci();read();a = z;rni();cycles = cycles + 3;break;
case 0x22: /** ldf %f/ld %f **/
   eacf();read();a = z;rni();cycles = cycles + 2;break;
case 0x23: /** ldb %b/ld %b **/
   eacb();read();a = z;rni();cycles = cycles + 2;break;
case 0x24: /** lcd %d/ldm %d **/
   eacd();read();a = z ^ 0xFFF;rni();cycles = cycles + 2;break;
case 0x25: /** lci %i/ldm (%d) **/
   eaci();read();a = z ^ 0xFFF;rni();cycles = cycles + 3;break;
case 0x26: /** lcf %f/ldm %f **/
   eacf();read();a = z ^ 0xFFF;rni();cycles = cycles + 2;break;
case 0x27: /** lcb %b/ldm %b **/
   eacb();read();a = z ^ 0xFFF;rni();cycles = cycles + 2;break;
case 0x30: /** add %d/add %d **/
   eacd();read();add12bit();rni();cycles = cycles + 2;break;
case 0x31: /** adi %i/add (%d) **/
   eaci();read();add12bit();rni();cycles = cycles + 3;break;
case 0x32: /** adf %f/add %f **/
   eacf();read();add12bit();rni();cycles = cycles + 2;break;
case 0x33: /** adb %b/add %b **/
   eacb();read();add12bit();rni();cycles = cycles + 2;break;
case 0x34: /** sbd %d/sub %d **/
   eacd();read();z = z ^ 0xFFF;add12bit();rni();cycles = cycles + 2;break;
case 0x35: /** sbi %i/sub (%d) **/
   eaci();read();z = z ^ 0xFFF;add12bit();rni();cycles = cycles + 3;break;
case 0x36: /** sbf %f/sub %f **/
   eacf();read();z = z ^ 0xFFF;add12bit();rni();cycles = cycles + 2;break;
case 0x37: /** sbb %b/sub %b **/
   eacb();read();z = z ^ 0xFFF;add12bit();rni();cycles = cycles + 2;break;
case 0x40: /** std %d/sta %d **/
   eacd();mbr = a;write();rni();cycles = cycles + 3;break;
case 0x41: /** sti %i/sta (%d) **/
   eaci();mbr = a;write();rni();cycles = cycles + 4;break;
case 0x42: /** stf %f/sta %f **/
   eacf();mbr = a;write();rni();cycles = cycles + 3;break;
case 0x43: /** stb %b/sta %b **/
   eacb();mbr = a;write();rni();cycles = cycles + 3;break;
case 0x44: /** srd %d/sld %d **/
   eacd();read();z = ((z << 1) | (z >11)) & 0xFFF;a = z;write();rni();cycles = cycles + 3;break;
case 0x45: /** sri %i/sld (%d) **/
   eaci();read();z = ((z << 1) | (z >11)) & 0xFFF;a = z;write();rni();cycles = cycles + 4;break;
case 0x46: /** srf %f/sld %f **/
   eacf();read();z = ((z << 1) | (z >11)) & 0xFFF;a = z;write();rni();cycles = cycles + 3;break;
case 0x47: /** srb %b/sld %b **/
   eacb();read();z = ((z << 1) | (z >11)) & 0xFFF;a = z;write();rni();cycles = cycles + 3;break;
case 0x50: /** rad %d/adm %d **/
   eacd();read();add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x51: /** rai %i/adm (%d) **/
   eaci();read();add12bit();z = a;write();rni();cycles = cycles + 4;break;
case 0x52: /** raf %f/adm %f **/
   eacf();read();add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x53: /** rab %b/adm %b **/
   eacb();read();add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x54: /** aod %d/ild %d **/
   eacd();read();a = 1;add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x55: /** aoi %i/ild (%d) **/
   eaci();read();a = 1;add12bit();z = a;write();rni();cycles = cycles + 4;break;
case 0x56: /** aof %f/ild %f **/
   eacf();read();a = 1;add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x57: /** aob %b/ild %b **/
   eacb();read();a = 1;add12bit();z = a;write();rni();cycles = cycles + 3;break;
case 0x60: /** zjf %f/jz %f **/
   eacf();if (a == 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x61: /** nzf %f/jnz %f **/
   eacf();if (a != 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x62: /** pjf %f/jp %f **/
   eacf();if ((a & 0x800) == 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x63: /** njf %f/jmi %f **/
   eacf();if ((a & 0x800) != 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x64: /** zjb %b/jz %b **/
   eacb();if (a == 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x65: /** nzb %b/jnz %b **/
   eacb();if (a != 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x66: /** pjb %b/jp %b **/
   eacb();if ((a & 0x800) == 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x67: /** njb %b/jmi %b **/
   eacb();if ((a & 0x800) != 0) { jni(); } else { rni(); };cycles = cycles + 1;break;
case 0x70: /** jpi %i/jmp (%d) **/
   eaci();jni();cycles = cycles + 2;break;
case 0x71: /** jfi %f/jmp (%f) **/
   eacf();read();s = z;jni();cycles = cycles + 2;break;
case 0x72: /** inp %f/inp %f **/
   dataTransfer();cycles = cycles + 2;break;
case 0x73: /** out %f/out %f **/
   dataTransfer();cycles = cycles + 2;break;
case 0x74: /** otn %d/otn #%d **/
   doOTN();;cycles = cycles + 1;break;
case 0x75: /** exf %f/exf (%f) **/
   doEXF();cycles = cycles + 1;break;
case 0x76: /** ina %d/ina %d **/
   doINA();;cycles = cycles + 1;break;
case 0x77: /** hlt %d/hlt #%d **/
   halt = 1;cycles = cycles + 1;break;
