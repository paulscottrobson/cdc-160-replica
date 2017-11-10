abstract class CDC160Generated extends CDC160Base {
private this.eacd() : void {
 this.s = (this.z & 0x3F);
}
private this.eaci() : void {
 this.s = (this.z & 0x3F);
 this.read();
 this.s = this.z;
}
private this.eacf() : void {
 this.s = (this.p + (this.z & 0x3F)) & 0xFFF;
}
private this.eacb() : void {
 this.s = (this.p - (this.z & 0x3F)) & 0xFFF;
}
private this.rni() : void {
 this.p = (this.p + 1) & 0xFFF;
 this.s = this.p;
 this.read();
}
private this.jni() : void {
 this.p = this.s;
 this.read();
}
private this.add12bit() : void {
 if (this.z == 0xFFF) this.z = 0;
 this.a = this.a + this.z;
 if (this.a & 0x1000) {
  this.a = (this.a + 1) & 0xFFF;
 }
}
private this.restart() : void {
 this.halt = 0;
 this.rni();
}
private this.shiftRoutine() : void {
 this.s = this.a;this.a = 0;
 this.s = ((this.s << 1) | (this.s >> 11)) & 0xFFF;
 if (this.z & 0x02) {
  this.a = this.s;
 }
 this.s = ((this.s << 1) | (this.s >> 11)) & 0xFFF;
 this.s = ((this.s << 1) | (this.s >> 11)) & 0xFFF;
 if (this.z & 0x08) {
  this.z = this.s;this.add12bit();
 }
}
private this.dataTransferEnd() : void {
 this.ioMode = 0;
 this.ioOpcode = 0;
 this.rni();
}
private dataTransfer() : void {
 if (this.ioMode == 0) {
  this.ioOpcode = this.z;
  this.eacf();
  this.read();this.a = this.z;
  this.p = (this.p + 1) & 0xFFF;

  if (this.ioOpcode == this.72) {
   this.ioMode = 'R';
  } else {
   this.s = this.a;this.read();
   this.ioMode = 'W';
  }
 } else {
  if (this.ioMode == 'R') {
   this.s = this.a;this.write();
  }
  this.cycles = this.cycles + 2;
  this.a = (this.a + 1) & 0xFFF;
  this.s = this.p;this.read();
  if (this.z == this.a) {
   this.dataTransferEnd();
  } else {
   if (this.ioMode == 'W') {
    this.s = this.a;this.read();
   }
  }
 }
}
private this.doOTN() : void {
 if (this.ioMode == 0) {
  this.ioOpcode = this.z;
  this.ioMode = 'W';
  this.z = (this.z & 0x3F);
 } else {
  this.dataTransferEnd();
 }
}
private this.doINA() : void {
 if (this.ioMode == 0) {
  this.ioOpcode = this.z;
  this.ioMode = 'R';
 } else {
  this.a = this.z;
  this.dataTransferEnd();
 }
}
private this.doEXF() : void {
 if (this.ioMode == 0) {
  this.ioOpcode = this.z;
  this.eacf();
  this.read();
  this.ioMode = 'F';
 } else {
  this.dataTransferEnd();
 }
}private opcode_00(): void { this.halt = 1;this.cycles = this.cycles + 1; };

private opcode_01(): void { this.shiftRoutine();rni();this.cycles = this.cycles + 1; };

private opcode_02(): void { this.a = this.a & (this.z & 0x3F);rni();this.cycles = this.cycles + 1; };

private opcode_03(): void { this.a = this.a ^ (this.z & 0x3F);rni();this.cycles = this.cycles + 1; };

private opcode_04(): void { this.a = (this.z & 0x3F);rni();this.cycles = this.cycles + 1; };

private opcode_05(): void { this.a = (this.z & 0x3F) ^ 0xFFF;rni();this.cycles = this.cycles + 1; };

private opcode_06(): void { this.z = (this.z & 0x3F);this.add12bit();rni();this.cycles = this.cycles + 1; };

private opcode_07(): void { this.z = (this.z & 0x3F) ^ 0xFFF;this.add12bit();rni();this.cycles = this.cycles + 1; };

private opcode_08(): void { this.eacd();this.read();this.a = this.a & this.z;rni();this.cycles = this.cycles + 2; };

private opcode_09(): void { this.eaci();this.read();this.a = this.a & this.z;rni();this.cycles = this.cycles + 3; };

private opcode_0a(): void { this.eacf();this.read();this.a = this.a & this.z;rni();this.cycles = this.cycles + 2; };

private opcode_0b(): void { this.eacb();this.read();this.a = this.a & this.z;rni();this.cycles = this.cycles + 2; };

private opcode_0c(): void { this.read();this.a = this.a ^ this.z;rni();this.cycles = this.cycles + 2; };

private opcode_0d(): void { this.read();this.a = this.a ^ this.z;rni();this.cycles = this.cycles + 3; };

private opcode_0e(): void { this.read();this.a = this.a ^ this.z;rni();this.cycles = this.cycles + 2; };

private opcode_0f(): void { this.read();this.a = this.a ^ this.z;rni();this.cycles = this.cycles + 2; };

private opcode_10(): void { this.eacd();this.read();this.a = this.z;rni();this.cycles = this.cycles + 2; };

private opcode_11(): void { this.eaci();this.read();this.a = this.z;rni();this.cycles = this.cycles + 3; };

private opcode_12(): void { this.eacf();this.read();this.a = this.z;rni();this.cycles = this.cycles + 2; };

private opcode_13(): void { this.eacb();this.read();this.a = this.z;rni();this.cycles = this.cycles + 2; };

private opcode_14(): void { this.eacd();this.read();this.a = this.z ^ 0xFFF;rni();this.cycles = this.cycles + 2; };

private opcode_15(): void { this.eaci();this.read();this.a = this.z ^ 0xFFF;rni();this.cycles = this.cycles + 3; };

private opcode_16(): void { this.eacf();this.read();this.a = this.z ^ 0xFFF;rni();this.cycles = this.cycles + 2; };

private opcode_17(): void { this.eacb();this.read();this.a = this.z ^ 0xFFF;rni();this.cycles = this.cycles + 2; };

private opcode_18(): void { this.eacd();this.read();this.add12bit();rni();this.cycles = this.cycles + 2; };

private opcode_19(): void { this.eaci();this.read();this.add12bit();rni();this.cycles = this.cycles + 3; };

private opcode_1a(): void { this.eacf();this.read();this.add12bit();rni();this.cycles = this.cycles + 2; };

private opcode_1b(): void { this.eacb();this.read();this.add12bit();rni();this.cycles = this.cycles + 2; };

private opcode_1c(): void { this.eacd();this.read();this.z = this.z ^ 0xFFF;this.add12bit();rni();this.cycles = this.cycles + 2; };

private opcode_1d(): void { this.eaci();this.read();this.z = this.z ^ 0xFFF;this.add12bit();rni();this.cycles = this.cycles + 3; };

private opcode_1e(): void { this.eacf();this.read();this.z = this.z ^ 0xFFF;this.add12bit();rni();this.cycles = this.cycles + 2; };

private opcode_1f(): void { this.eacb();this.read();this.z = this.z ^ 0xFFF;this.add12bit();rni();this.cycles = this.cycles + 2; };

private opcode_20(): void { this.eacd();this.z = this.a;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_21(): void { this.eaci();this.z = this.a;this.write();rni();this.cycles = this.cycles + 4; };

private opcode_22(): void { this.eacf();this.z = this.a;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_23(): void { this.eacb();this.z = this.a;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_24(): void { this.eacd();this.read();this.z = ((this.z << 1) | (this.z >11)) & 0xFFF;this.a = this.z;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_25(): void { this.eaci();this.read();this.z = ((this.z << 1) | (this.z >11)) & 0xFFF;this.a = this.z;this.write();rni();this.cycles = this.cycles + 4; };

private opcode_26(): void { this.eacf();this.read();this.z = ((this.z << 1) | (this.z >11)) & 0xFFF;this.a = this.z;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_27(): void { this.eacb();this.read();this.z = ((this.z << 1) | (this.z >11)) & 0xFFF;this.a = this.z;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_28(): void { this.eacd();this.read();this.add12bit();this.z = this.a;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_29(): void { this.eaci();this.read();this.add12bit();this.z = this.a;this.write();rni();this.cycles = this.cycles + 4; };

private opcode_2a(): void { this.eacf();this.read();this.add12bit();this.z = this.a;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_2b(): void { this.eacb();this.read();this.add12bit();this.z = this.a;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_2c(): void { this.eacd();this.read();this.a = 1;this.add12bit();this.z = this.a;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_2d(): void { this.eaci();this.read();this.a = 1;this.add12bit();this.z = this.a;this.write();rni();this.cycles = this.cycles + 4; };

private opcode_2e(): void { this.eacf();this.read();this.a = 1;this.add12bit();this.z = this.a;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_2f(): void { this.eacb();this.read();this.a = 1;this.add12bit();this.z = this.a;this.write();rni();this.cycles = this.cycles + 3; };

private opcode_30(): void { this.eacf();if (this.a == 0) { this.jni(); } else { this.rni(); };this.cycles = this.cycles + 1; };

private opcode_31(): void { this.eacf();if (this.a != 0) { this.jni(); } else { this.rni(); };this.cycles = this.cycles + 1; };

private opcode_32(): void { this.eacf();if ((this.a & 0x800) == 0) { this.jni(); } else { this.rni(); };this.cycles = this.cycles + 1; };

private opcode_33(): void { this.eacf();if ((this.a & 0x800) != 0) { this.jni(); } else { this.rni(); };this.cycles = this.cycles + 1; };

private opcode_34(): void { this.eacb();if (this.a == 0) { this.jni(); } else { this.rni(); };this.cycles = this.cycles + 1; };

private opcode_35(): void { this.eacb();if (this.a != 0) { this.jni(); } else { this.rni(); };this.cycles = this.cycles + 1; };

private opcode_36(): void { this.eacb();if ((this.a & 0x800) == 0) { this.jni(); } else { this.rni(); };this.cycles = this.cycles + 1; };

private opcode_37(): void { this.eacb();if ((this.a & 0x800) != 0) { this.jni(); } else { this.rni(); };this.cycles = this.cycles + 1; };

private opcode_38(): void { this.eaci();this.jni();this.cycles = this.cycles + 2; };

private opcode_39(): void { this.eacf();this.read();this.s = this.z;this.jni();this.cycles = this.cycles + 2; };

private opcode_3a(): void { this.dataTransfer();this.cycles = this.cycles + 2; };

private opcode_3b(): void { this.dataTransfer();this.cycles = this.cycles + 2; };

private opcode_3c(): void { this.doOTN();;this.cycles = this.cycles + 1; };

private opcode_3d(): void { this.doEXF();this.cycles = this.cycles + 1; };

private opcode_3e(): void { this.doINA();;this.cycles = this.cycles + 1; };

private opcode_3f(): void { this.halt = 1;this.cycles = this.cycles + 1; };

protected getOpcodeList():Function() {
 return [opcode_00,opcode_01,opcode_02,opcode_03,opcode_04,opcode_05,opcode_06,opcode_07,opcode_08,opcode_09,opcode_0a,opcode_0b,opcode_0c,opcode_0d,opcode_0e,opcode_0f,opcode_10,opcode_11,opcode_12,opcode_13,opcode_14,opcode_15,opcode_16,opcode_17,opcode_18,opcode_19,opcode_1a,opcode_1b,opcode_1c,opcode_1d,opcode_1e,opcode_1f,opcode_20,opcode_21,opcode_22,opcode_23,opcode_24,opcode_25,opcode_26,opcode_27,opcode_28,opcode_29,opcode_2a,opcode_2b,opcode_2c,opcode_2d,opcode_2e,opcode_2f,opcode_30,opcode_31,opcode_32,opcode_33,opcode_34,opcode_35,opcode_36,opcode_37,opcode_38,opcode_39,opcode_3a,opcode_3b,opcode_3c,opcode_3d,opcode_3e,opcode_3f,opcode_40,opcode_41,opcode_42,opcode_43,opcode_44,opcode_45,opcode_46,opcode_47,opcode_48,opcode_49,opcode_4a,opcode_4b,opcode_4c,opcode_4d,opcode_4e,opcode_4f,opcode_50,opcode_51,opcode_52,opcode_53,opcode_54,opcode_55,opcode_56,opcode_57,opcode_58,opcode_59,opcode_5a,opcode_5b,opcode_5c,opcode_5d,opcode_5e,opcode_5f,opcode_60,opcode_61,opcode_62,opcode_63,opcode_64,opcode_65,opcode_66,opcode_67,opcode_68,opcode_69,opcode_6a,opcode_6b,opcode_6c,opcode_6d,opcode_6e,opcode_6f,opcode_70,opcode_71,opcode_72,opcode_73,opcode_74,opcode_75,opcode_76,opcode_77,opcode_78,opcode_79,opcode_7a,opcode_7b,opcode_7c,opcode_7d,opcode_7e,opcode_7f,opcode_80,opcode_81,opcode_82,opcode_83,opcode_84,opcode_85,opcode_86,opcode_87,opcode_88,opcode_89,opcode_8a,opcode_8b,opcode_8c,opcode_8d,opcode_8e,opcode_8f,opcode_90,opcode_91,opcode_92,opcode_93,opcode_94,opcode_95,opcode_96,opcode_97,opcode_98,opcode_99,opcode_9a,opcode_9b,opcode_9c,opcode_9d,opcode_9e,opcode_9f,opcode_a0,opcode_a1,opcode_a2,opcode_a3,opcode_a4,opcode_a5,opcode_a6,opcode_a7,opcode_a8,opcode_a9,opcode_aa,opcode_ab,opcode_ac,opcode_ad,opcode_ae,opcode_af,opcode_b0,opcode_b1,opcode_b2,opcode_b3,opcode_b4,opcode_b5,opcode_b6,opcode_b7,opcode_b8,opcode_b9,opcode_ba,opcode_bb,opcode_bc,opcode_bd,opcode_be,opcode_bf,opcode_c0,opcode_c1,opcode_c2,opcode_c3,opcode_c4,opcode_c5,opcode_c6,opcode_c7,opcode_c8,opcode_c9,opcode_ca,opcode_cb,opcode_cc,opcode_cd,opcode_ce,opcode_cf,opcode_d0,opcode_d1,opcode_d2,opcode_d3,opcode_d4,opcode_d5,opcode_d6,opcode_d7,opcode_d8,opcode_d9,opcode_da,opcode_db,opcode_dc,opcode_dd,opcode_de,opcode_df,opcode_e0,opcode_e1,opcode_e2,opcode_e3,opcode_e4,opcode_e5,opcode_e6,opcode_e7,opcode_e8,opcode_e9,opcode_ea,opcode_eb,opcode_ec,opcode_ed,opcode_ee,opcode_ef,opcode_f0,opcode_f1,opcode_f2,opcode_f3,opcode_f4,opcode_f5,opcode_f6,opcode_f7,opcode_f8,opcode_f9,opcode_fa,opcode_fb,opcode_fc,opcode_fd,opcode_fe,opcode_ff];
}
