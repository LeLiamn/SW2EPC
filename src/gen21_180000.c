/*
 * gen21_180000.c - functions between 0x00180000 and 0x003F9680, generated from Ghidra
 * output (access widths from the disassembly) and kept only when they call the same functions as the original and their compiled size is within
 * 40 % of the original (missing arguments read from the original call sites; calls and return values checked against the machine code). Machine-like: to be cleaned up by hand later.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00730564[0x18];
extern u8 g_00730568[0x18];
extern u8 g_0073056C[0x18];
extern u8 g_0074B7F8[0x18];
extern u8 g_0076EC40[0x18];
extern u8 g_0076F3B0[0x18];
extern u8 g_00772670[0x18];
extern u8 g_00772688[0x18];
extern u8 g_007726A0[0x18];
extern u8 g_007726B4[0x18];
extern u8 g_007726C8[0x18];
extern u8 g_007726D0[0x18];
extern u8 g_007726DC[0x18];
extern u8 g_00772808[0x18];
extern u8 g_00772810[0x18];
extern u8 g_0077281C[0x18];
extern u8 g_00772A9C[0x18];
extern u8 g_00772AEC[0x18];
extern u8 g_00772B00[0x18];
extern u8 g_00772B14[0x18];
extern u8 g_00772BF0[0x18];
extern u8 g_00772C18[0x18];
extern u8 g_00772C54[0x18];
extern u8 g_00772C68[0x18];
extern u8 g_00772C7C[0x18];
extern u8 g_00772CA4[0x18];
extern u8 g_00772CB8[0x18];
extern u8 g_00772CCC[0x18];
extern u8 g_00772D30[0x18];
extern u8 g_00772D98[0x18];
extern u8 g_00772DAC[0x18];
extern u8 g_00772DC0[0x18];
extern u8 g_007802B8[0x18];
extern u8 g_007802D0[0x18];
extern u8 g_00780338[0x18];
extern u8 g_007803D8[0x18];
extern u8 g_00794E30[0x18];
extern u8 g_00794FAC[0x18];
extern u8 g_0079502C[0x18];
extern u8 g_00799A20[0x18];
extern u8 g_007A2034[0x18];
extern u8 g_007A2174[0x18];
extern u8 g_007A2188[0x18];
extern u8 g_007B4E60[0x18];
extern u8 g_007B9E74[0x18];
extern u8 g_007B9E84[0x18];
extern u8 g_007B9ED0[0x18];
extern u8 g_007BA7F0[0x18];
extern u8 g_007BA7FC[0x18];
extern u8 g_007BBC80[0x18];
extern u8 g_007BBE80[0x18];
#include "sw2e_mem.h"
#include "sw2e_protos.h"

#define true 1
#define false 0

extern u8 g_00100001[0x6];
extern u8 g_00400870[0x4];
extern u8 g_00406940[0x2C];
extern u8 g_0040C3F0[0x8];
extern u8 g_0040C920[0x400];
extern u8 g_0040CBC0[0x400];
extern u8 g_0040CC00[0x400];
extern u8 g_0040CDAE[0x4];
extern u8 g_0040CFF0[0x28];
extern u8 g_0040D270[0x400];
extern u8 g_0040D2E0[0x4];
extern u8 g_0040D510[0xAC];
extern u8 g_0040D6F0[0x4];
extern u8 g_0040D874[0x4];
extern u8 g_0040D88C[0x4];
extern u8 g_0040D960[0x4];
extern u8 g_0040E720[0x24];
extern u8 g_0040E940[0x28];
extern u8 g_00410AC0[0x8];
extern u8 g_00410D10[0xC];
extern u8 g_00411160[0x38];
extern u8 g_004111E0[0x38];
extern u8 g_00411220[0x3C];
extern u8 g_004112A0[0x24];
extern u8 g_00411444[0x4];
extern u8 g_004114B0[0x4];
extern u8 g_004114B4[0x4];
extern u8 g_004114B8[0x4];
extern u8 g_004114C0[0x4];
extern u8 g_004114C4[0x4];
extern u8 g_004114C8[0x4];
extern u8 g_004114CC[0x4];
extern u8 g_004114D0[0x4];
extern u8 g_004114D4[0x4];
extern u8 g_004114D8[0xC];
extern u8 g_00411820[0x40];
extern u8 g_00411880[0x4];
extern u8 g_00411890[0x10];
extern u8 g_00411980[0x28];
extern u8 g_004119B0[0x4];
extern u8 g_00411B40[0x4];
extern u8 g_00411B44[0x4];
extern u8 g_00411B48[0x4];
extern u8 g_00411B4C[0x4];
extern u8 g_00411B50[0xC];
extern u8 g_00411EB0[0x10];
extern u8 g_00411EC0[0x10];
extern u8 g_00411ED0[0x18];
extern u8 g_00411EF0[0x18];
extern u8 g_00412020[0x400];
extern u8 g_00412190[0x4];
extern u8 g_004121F0[0x4];
extern u8 g_00412230[0x4];
extern u8 g_004123A5[0x20];
extern u8 g_00412470[0x4];
extern u8 g_00412490[0x400];
extern u8 g_00412560[0x38];
extern u8 g_004125E0[0x40];
extern u8 g_00412620[0x38];
extern u8 g_004126A0[0x14];
extern u8 g_004126C0[0x14];
extern u8 g_00412C60[0x4];
extern u8 g_00414DF0[0x4];
extern u8 g_00414E70[0x400];
extern u8 g_00416370[0x400];
extern u8 g_00417330[0xF4];
extern u8 g_00417468[0xC];
extern u8 g_00417480[0x4];
extern u8 g_00417650[0x4];
extern u8 g_00417670[0x400];
extern u8 g_00418AE0[0x84];
extern u8 g_0041BE70[0xC4];
extern u8 g_0041C140[0x4];
extern u8 g_0041C144[0x4];
extern u8 g_0041C148[0x4];
extern u8 g_0041C14C[0x4];
extern u8 g_0041C150[0x4];
extern u8 g_0041C160[0x20];
extern u8 g_0041C400[0x10];
extern u8 g_0041CF00[0x4];
extern u8 g_0041D008[0xC];
extern u8 g_0041D060[0xF4];
extern u8 g_0041D1A0[0x150];
extern u8 g_00424EF0[0x24];
extern u8 g_004251E0[0x14];
extern u8 g_004251F0[0x1];
extern u8 g_00425EB0[0x4];
extern u8 g_00426070[0x4];
extern u8 g_00426230[0x4];
extern u8 g_00428138[0x4];
extern u8 g_004281BD[0x4];
extern u8 g_00428B78[0x5];
extern u8 g_00428B7A[0x4];
extern u8 g_004299B0[0x1C];
extern u8 g_0042A290[0x58];
extern u8 g_0042A2E0[0x400];
extern u8 g_0042A2E4[0x4];
extern u8 g_0042A340[0x4];
extern u8 g_0042D3E0[0x400];
extern u8 g_0042DC10[0x400];
extern u8 g_0042F6B0[0x400];
extern u8 g_0042F880[0x4];
extern u8 g_0042F910[0x400];
extern u8 g_0043C120[0x400];
extern u8 g_0043C128[0x4];
extern u8 g_0043C12C[0x4];
extern u8 g_0043C138[0x4];
extern u8 g_0043C148[0x4];
extern u8 g_0043C150[0x4];
extern u8 g_0043C16C[0x4];
extern u8 g_0043C170[0x4];
extern u8 g_0043C174[0x4];
extern u8 g_0043C178[0x4];
extern u8 g_0043C18C[0x4];
extern u8 g_0043C194[0x4];
extern u8 g_0043C19C[0x4];
extern u8 g_0043C1A0[0x4];
extern u8 g_0043C1C4[0x4];
extern u8 g_0043C1E0[0x4];
extern u8 g_0043C1E4[0x4];
extern u8 g_0043C1F0[0x4];
extern u8 g_0043C200[0x4];
extern u8 g_0043C224[0x4];
extern u8 g_0043C228[0x4];
extern u8 g_0043C244[0x4];
extern u8 g_0043C24C[0x4];
extern u8 g_0043C254[0x4];
extern u8 g_0043C258[0x4];
extern u8 g_0043C27C[0x4];
extern u8 g_0043C3A4[0x4];
extern u8 g_0043C478[0x4];
extern u8 g_0043C480[0x4];
extern u8 g_0043C524[0x4];
extern u8 g_0043C534[0x4];
extern u8 g_0043C578[0x4];
extern u8 g_0043C5A8[0x4];
extern u8 g_0043C5EC[0x4];
extern u8 g_0043C5F0[0x4];
extern u8 g_0043C6DC[0x4];
extern u8 g_0043C6E0[0x4];
extern u8 g_0043C780[0x4];
extern u8 g_0043C784[0x4];
extern u8 g_0043C78C[0x4];
extern u8 g_0043C790[0x4];
extern u8 g_0043C7BC[0x4];
extern u8 g_0043C7C8[0x4];
extern u8 g_0043C7E8[0x4];
extern u8 g_0043C82C[0x4];
extern u8 g_0043C830[0x4];
extern u8 g_0043C834[0x4];
extern u8 g_0043C840[0x4];
extern u8 g_0043C844[0x4];
extern u8 g_0043C858[0x4];
extern u8 g_0043C85C[0x4];
extern u8 g_0043C860[0x4];
extern u8 g_0043C864[0x4];
extern u8 g_0043C870[0x4];
extern u8 g_0043C874[0x4];
extern u8 g_0043C878[0x4];
extern u8 g_0043CB24[0x4];
extern u8 g_0043CB28[0x4];
extern u8 g_0043CB2C[0x4];
extern u8 g_0043CB30[0x4];
extern u8 g_0043F9A0[0x400];
extern u8 g_0043FDB0[0x10];
extern u8 g_0043FE40[0x4];
extern u8 g_0043FE50[0x4];
extern u8 g_0043FE5C[0x400];
extern u8 g_0043FE60[0x4];
extern u8 g_00440638[0x6C];
extern u8 g_00440650[0x1C];
extern u8 g_00440670[0x34];
extern u8 g_004406D0[0x44];
extern u8 g_00440750[0x8];
extern u8 g_00440810[0x4];
extern u8 g_00440950[0x10];
extern u8 g_004417C0[0x10];
extern u8 g_00441D44[0x6];
extern u8 g_00441F60[0x4];
extern u8 g_00441F68[0x14];
extern u8 g_00441F80[0x1C];
extern u8 g_00441FA0[0x34];
extern u8 g_00442030[0xC];
extern u8 g_004420B0[0x400];
extern u8 g_00442370[0x4];
extern u8 g_00442BF0[0x4];
extern u8 g_00442D20[0x400];
extern u8 g_00442D40[0x4];
extern u8 g_00442D60[0x4];
extern u8 g_00447A30[0x10];
extern u8 g_00447B30[0x400];
extern u8 g_004483A0[0x68];
extern u8 g_00448410[0x17];
extern u8 g_004484C0[0x4];
extern u8 g_004562F8[0x4];
extern u8 g_00457B10[0x4];
extern u8 g_00459450[0x4];
extern u8 g_004595F0[0x6];
extern u8 g_00459600[0x400];
extern u8 g_00459720[0xE];
extern u8 g_004599F0[0x400];
extern u8 g_00459B40[0xC8];
extern u8 g_00459B60[0x8];
extern u8 g_00459F20[0x8];
extern u8 g_0045A660[0x4];
extern u8 g_0045A930[0x8];
extern u8 g_0045B6B8[0x1C];
extern u8 g_0045C4A8[0xC];
extern u8 g_0045CDA8[0x4];
extern u8 g_0045CDB8[0x4];
extern u8 g_0045CEC7[0x4];
extern u8 g_0045CFF0[0x10];
extern u8 g_0045D1F0[0x4];
extern u8 g_0045D2C0[0x4];
extern u8 g_0045D3E0[0x4];
extern u8 g_0045D488[0x4];
extern u8 g_0045D494[0xC];
extern u8 g_0045D4A0[0x4];
extern u8 g_0045D5EC[0x4];
extern u8 g_0045D610[0x4];
extern u8 g_0045D6EC[0x4];
extern u8 g_0045D730[0x4];
extern u8 g_0045D73C[0x4];
extern u8 g_0045D7FC[0x4];
extern u8 g_0045D898[0x4];
extern u8 g_0050074C[0xA2];
extern u8 g_0056CCA0[0x10];
extern u8 g_0056CCA4[0x29];
extern u8 g_0056CCB4[0x18];
extern u8 g_0056CCC8[0x4];
extern u8 g_00574DE0[0x10];
extern u8 g_00574E70[0x10];
extern u8 g_005754A0[0x10];
extern u8 g_005755A8[0x1];
extern u8 g_005B4BC0[0x10];
extern u8 g_005B4D80[0x68];
extern u8 g_005B4FC0[0x68];
extern u8 g_005B5030[0x1];
extern u8 g_005BA690[0x10];
extern u8 g_005BA694[0x4];
extern u8 g_005BA6A0[0x4];
extern u8 g_005BA6A4[0x4];
extern u8 g_005BA7C4[0x8];
extern u8 g_005BBF18[0x4];
extern u8 g_005BBF1C[0x4];
extern u8 g_005BC024[0x44];
extern u8 g_005BC03C[0x28];
extern u8 g_005BC3A0[0x5];
extern u8 g_005BD724[0x4];
extern u8 g_005BD734[0x8];
extern u8 g_005BD740[0x4];
extern u8 g_00669D60[0x10];
extern u8 g_00669D81[0x1];
extern u8 g_00669DB0[0x28];
extern u8 g_00669DB2[0x2];
extern u8 g_00669DB8[0x20];
extern u8 g_00669F60[0x40];
extern u8 g_00669F6C[0x4];
extern u8 g_00669F70[0x2C];
extern u8 g_00669F84[0x4];
extern u8 g_00669F98[0x4];
extern u8 g_00669F9C[0x8];
extern u8 g_00669FA4[0x4];
extern u8 g_00669FB3[0x1];
extern u8 g_0068F0F0[0x18];
extern u8 g_0068F0F8[0x8];
extern u8 g_00692DA0[0x11];
extern u8 g_00693380[0x14];
extern u8 g_00693388[0x4];
extern u8 g_006934B9[0x1];
extern u8 g_00693703[0x4];
extern u8 g_0069382B[0x1];
extern u8 g_0069395E[0x1];
extern u8 g_00693968[0x1];
extern u8 g_00693970[0x10];
extern u8 g_00693988[0x4];
extern u8 g_0069398C[0x4];
extern u8 g_006939A8[0x4];
extern u8 g_006939AC[0x4];
extern u8 g_006939EA[0x4];
extern u8 g_006939EC[0x4];
extern u8 g_006939EE[0x4];
extern u8 g_006939F0[0x4];
extern u8 g_006939F4[0x4];
extern u8 g_00693A78[0x4];
extern u8 g_006A1D49[0xB];
extern u8 g_006A1D58[0x4];
extern u8 g_006A1DA4[0x4];
extern u8 g_006A1DBC[0x4];
extern u8 g_006A3A30[0x10];
extern u8 g_006A3A38[0x4];
extern u8 g_006A3A40[0x4];
extern u8 g_006A3A44[0x4];
extern u8 g_006A3A98[0x4];
extern u8 g_006A3AAD[0x4];
extern u8 g_006A3AB0[0x4];
extern u8 g_006A3AB2[0x4];
extern u8 g_006A3AE8[0x4];
extern u8 g_006A3AEC[0x4];
extern u8 g_006A3D30[0x10];
extern u8 g_006A95B0[0x10];
extern u8 g_006AA578[0x8];
extern u8 g_006AA57C[0x4];
extern u8 g_006AA598[0x4];
extern u8 g_006AA5D0[0x4];
extern u8 g_006AA5E0[0x4];
extern u8 g_0072D470[0x4];
extern u8 g_00730560[0x10];
extern u8 g_00730730[0x4];
extern u8 g_00730734[0x4];
extern u8 g_00730738[0x4];
extern u8 g_0073073C[0x4];
extern u8 g_00730740[0x4];
extern u8 g_00730744[0x4];
extern u8 g_00730748[0x4];
extern u8 g_0073074C[0x4];
extern u8 g_00730790[0x4];
extern u8 g_00730794[0x4];
extern u8 g_00730A84[0x4];
extern u8 g_00730DE0[0x4];
extern u8 g_00730DE4[0x4];
extern u8 g_00730DE8[0x4];
extern u8 g_00730DF0[0x4];
extern u8 g_00730DF4[0x4];
extern u8 g_00730DF8[0x4];
extern u8 g_00730DFC[0x4];
extern u8 g_00730E14[0x4];
extern u8 g_00731370[0x4];
extern u8 g_00731390[0x4];
extern u8 g_007315A0[0x40];
extern u8 g_007315C0[0x4];
extern u8 g_007315D0[0x10];
extern u8 g_00732220[0x10];
extern u8 g_00732370[0x4];
extern u8 g_00732380[0x4];
extern u8 g_00732508[0x4];
extern u8 g_0073255A[0x1];
extern u8 g_0073255C[0x4];
extern u8 g_0073255E[0x4];
extern u8 g_00732560[0x4];
extern u8 g_00732562[0x4];
extern u8 g_00732564[0x4];
extern u8 g_00732566[0x4];
extern u8 g_00732568[0x4];
extern u8 g_0073256A[0x4];
extern u8 g_0073256C[0x4];
extern u8 g_0073256E[0x4];
extern u8 g_00732588[0x4];
extern u8 g_00732589[0x4];
extern u8 g_0073258A[0x4];
extern u8 g_007325A8[0x10];
extern u8 g_007325B8[0x2C];
extern u8 g_007325EC[0x4];
extern u8 g_007325F0[0x4];
extern u8 g_007325F4[0x4];
extern u8 g_007325F8[0x4];
extern u8 g_007325FC[0x4];
extern u8 g_00732600[0x4];
extern u8 g_00732604[0x4];
extern u8 g_00732608[0x4];
extern u8 g_0073260C[0x4];
extern u8 g_0073260D[0x4];
extern u8 g_0073260E[0x4];
extern u8 g_0073260F[0x4];
extern u8 g_00732610[0x4];
extern u8 g_00732611[0x4];
extern u8 g_00732612[0x4];
extern u8 g_00732670[0x8];
extern u8 g_00732674[0x4];
extern u8 g_00732CB8[0x4];
extern u8 g_00732DC0[0x8];
extern u8 g_00733408[0x4];
extern u8 g_0073C480[0x4];
extern u8 g_0073C790[0x4];
extern u8 g_0073D6C0[0x40];
extern u8 g_0073D6F0[0x10];
extern u8 g_0073DA10[0x18];
extern u8 g_0073DA20[0x10];
extern u8 g_0073DC60[0x4];
extern u8 g_0073DC64[0x4];
extern u8 g_0073DC68[0x50];
extern u8 g_0073DC6C[0x4];
extern u8 g_0073DC70[0x4];
extern u8 g_0073DC74[0x4];
extern u8 g_0073DC78[0x4];
extern u8 g_0073DC7C[0x4];
extern u8 g_0073DC80[0x4];
extern u8 g_0073DC84[0x4];
extern u8 g_0073DC88[0x4];
extern u8 g_0073DC98[0x4];
extern u8 g_0073DC99[0x4];
extern u8 g_0073DC9A[0x4];
extern u8 g_0073DC9B[0x4];
extern u8 g_0073DC9C[0x4];
extern u8 g_0073DC9D[0x4];
extern u8 g_0073DC9E[0x4];
extern u8 g_0073DCA0[0x4];
extern u8 g_0073DCA1[0x4];
extern u8 g_0073DCA2[0x4];
extern u8 g_0073DCA3[0x4];
extern u8 g_0073DCB0[0x10];
extern u8 g_0073DEF8[0x8];
extern u8 g_0073DF04[0x4];
extern u8 g_0073DF28[0x4];
extern u8 g_0073DF30[0x4];
extern u8 g_0073DF33[0x1];
extern u8 g_0073E020[0x4];
extern u8 g_0073E030[0x10];
extern u8 g_0073E0C0[0x4];
extern u8 g_0073E0C4[0x4];
extern u8 g_0073E0C8[0x4];
extern u8 g_0073E0CC[0x4];
extern u8 g_0073E1F0[0x4];
extern u8 g_0073F350[0x10];
extern u8 g_0074A0A0[0x4];
extern u8 g_0074A0A4[0x4];
extern u8 g_0074A0A8[0x4];
extern u8 g_0074A0AC[0x4];
extern u8 g_0074A0B0[0x4];
extern u8 g_0074A0B4[0x4];
extern u8 g_0074A140[0x4];
extern u8 g_0074A148[0x4];
extern u8 g_0074A14C[0x4];
extern u8 g_0074A150[0x4];
extern u8 g_0074B824[0x10];
extern u8 g_0074B828[0x4];
extern u8 g_00752940[0x8];
extern u8 g_0075294C[0x4];
extern u8 g_0076EC60[0x40];
extern u8 g_0076F3A0[0x28];
extern u8 g_0076F3A4[0x24];
extern u8 g_0076F3AC[0x2C];
extern u8 g_0076F3D4[0x4];
extern u8 g_0076F3D5[0x2];
extern u8 g_0076F62F[0x1];
extern u8 g_0076F634[0x4];
extern u8 g_0076F650[0x4];
extern u8 g_0076F651[0x4];
extern u8 g_0076F652[0x4];
extern u8 g_0076F653[0x4];
extern u8 g_0076F654[0x4];
extern u8 g_0076F655[0x4];
extern u8 g_0076F656[0x4];
extern u8 g_0076F657[0x4];
extern u8 g_0076F690[0x4];
extern u8 g_0076F691[0x4];
extern u8 g_0076F692[0x4];
extern u8 g_0076F693[0x4];
extern u8 g_0076F694[0x4];
extern u8 g_0076F695[0x4];
extern u8 g_0076F696[0x4];
extern u8 g_0076F697[0x4];
extern u8 g_0076F698[0x4];
extern u8 g_0076F699[0x4];
extern u8 g_0076F6FA[0x4];
extern u8 g_0076F6FB[0x4];
extern u8 g_0076F6FC[0x4];
extern u8 g_0076F6FD[0x4];
extern u8 g_0076F6FE[0x4];
extern u8 g_0076F6FF[0x4];
extern u8 g_0076F700[0x4];
extern u8 g_0076F701[0x4];
extern u8 g_0076F702[0x4];
extern u8 g_0076F703[0x4];
extern u8 g_0076F704[0x4];
extern u8 g_0076F705[0x4];
extern u8 g_0076F706[0x4];
extern u8 g_0076F787[0x4];
extern u8 g_0076F790[0x2C];
extern u8 g_0076F8C0[0x4];
extern u8 g_00772674[0x8];
extern u8 g_007726B0[0x2A];
extern u8 g_007726F8[0x4];
extern u8 g_007726FA[0x4];
extern u8 g_0077272C[0x4];
extern u8 g_0077272E[0x4];
extern u8 g_00772730[0x4];
extern u8 g_00772732[0x4];
extern u8 g_00772734[0x4];
extern u8 g_00772736[0x4];
extern u8 g_00772738[0x4];
extern u8 g_0077273A[0x4];
extern u8 g_0077273C[0x4];
extern u8 g_0077273D[0x4];
extern u8 g_0077273E[0x4];
extern u8 g_0077273F[0x4];
extern u8 g_00772770[0x4];
extern u8 g_00772772[0x4];
extern u8 g_00772774[0x4];
extern u8 g_00772776[0x4];
extern u8 g_007727AC[0x4];
extern u8 g_007727AE[0x4];
extern u8 g_007727B0[0x4];
extern u8 g_007727B2[0x4];
extern u8 g_007727E0[0x14];
extern u8 g_007727F4[0x26];
extern u8 g_00772910[0xE3];
extern u8 g_007729C8[0x2A];
extern u8 g_007729CC[0x4];
extern u8 g_007729D0[0x24];
extern u8 g_007729DC[0x4];
extern u8 g_00772A10[0x10];
extern u8 g_00772D48[0x10];
extern u8 g_00772D54[0x4];
extern u8 g_007732B0[0x10];
extern u8 g_00773340[0x4];
extern u8 g_00773418[0x4];
extern u8 g_00773440[0x4];
extern u8 g_00773444[0x4];
extern u8 g_00773448[0x4];
extern u8 g_0077344C[0x4];
extern u8 g_00773450[0x4];
extern u8 g_00773454[0x4];
extern u8 g_00777140[0x10];
extern u8 g_0077A700[0x10];
extern u8 g_0077BE70[0x10];
extern u8 g_0077BE80[0x6C];
extern u8 g_0077BEF0[0x4];
extern u8 g_0077BEF4[0x4];
extern u8 g_0077C040[0x10];
extern u8 g_0077CEA0[0xD0];
extern u8 g_007802A0[0x10];
extern u8 g_007802FC[0x19C];
extern u8 g_00780490[0x8];
extern u8 g_00794590[0x10];
extern u8 g_00795790[0x8];
extern u8 g_00795FC1[0x3F];
extern u8 g_00795FC4[0xC];
extern u8 g_00796044[0x4];
extern u8 g_00796048[0x4];
extern u8 g_007991F0[0x4];
extern u8 g_007991F4[0x4];
extern u8 g_007991F8[0x4];
extern u8 g_007991FC[0x4];
extern u8 g_00799920[0x4];
extern u8 g_00799924[0x4];
extern u8 g_00799928[0x4];
extern u8 g_0079992A[0x4];
extern u8 g_0079992C[0x4];
extern u8 g_00799A68[0x4];
extern u8 g_00799A6C[0x4];
extern u8 g_00799A70[0x7C];
extern u8 g_00799A7C[0x74];
extern u8 g_00799A80[0x70];
extern u8 g_0079FE10[0x10];
extern u8 g_007A05A0[0x10];
extern u8 g_007A1C10[0x18];
extern u8 g_007A1E30[0x8];
extern u8 g_007A219B[0x1];
extern u8 g_007A22B8[0x8];
extern u8 g_007A22BC[0x4];
extern u8 g_007B5E20[0x30];
extern u8 g_007B95E0[0x18];
extern u8 g_007B95E8[0x18];
extern u8 g_007B9620[0x10];
extern u8 g_007B98A4[0x4];
extern u8 g_007B98B0[0xD2];
extern u8 g_007B9E58[0x10];
extern u8 g_007B9E5D[0x4];
extern u8 g_007B9E70[0xC8];
extern u8 g_007B9F30[0x10];
extern u8 g_007BA7F8[0xC];
extern u8 g_007BA850[0xD];
extern u8 g_007BA8B0[0x78];
extern u8 g_007BA8BC[0x4];
extern u8 g_007BAA64[0x4];
extern u8 g_007BAC08[0x6];
extern u8 g_007BAC40[0x10];
extern u8 g_007BACB4[0x14];
extern u8 g_007BACB8[0x8];
extern u8 g_007BACC4[0x12C];
extern u8 g_007BADC8[0x28];
extern u8 g_007BAE22[0x4];
extern u8 g_007BAE74[0x1C];
extern u8 g_007BC2A0[0x10];
extern u8 g_007BC2B0[0x10];
extern int g_0045CDA4;   /* (small data) */
extern int g_0045CDAC;   /* (small data) */
extern int g_0045CDBC;   /* (small data) */
extern int g_0045CE20;   /* (small data) */
extern int g_0045CE24;   /* (small data) */
extern int g_0045CE38;   /* (small data) */
extern int g_0045CE3C;   /* (small data) */
extern int g_0045CE40;   /* (small data) */
extern int g_0045CE41;   /* (small data) */
extern int g_0045CE42;   /* (small data) */
extern int g_0045CEC3;   /* (small data) */
extern int g_0045CF02;   /* (small data) */
extern int g_0045CF06;   /* (small data) */
extern int g_0045CF08;   /* (small data) */
extern int g_0045CF0C;   /* (small data) */
extern int g_0045CF10;   /* (small data) */
extern int g_0045CF14;   /* (small data) */
extern int g_0045CF1A;   /* (small data) */
extern int g_0045CF1E;   /* (small data) */
extern int g_0045CF20;   /* (small data) */
extern int g_0045CF24;   /* (small data) */
extern int g_0045CF2C;   /* (small data) */
extern int g_0045CF2E;   /* (small data) */
extern int g_0045CF30;   /* (small data) */
extern int g_0045CF32;   /* (small data) */
extern int g_0045CF34;   /* (small data) */
extern int g_0045CF36;   /* (small data) */
extern int g_0045CF50;   /* (small data) */
extern int g_0045D0FB;   /* (small data) */
extern int g_0045D0FF;   /* (small data) */
extern int g_0045D1C8;   /* (small data) */
extern int g_0045D2F0;   /* (small data) */
extern int g_0045D2FC;   /* (small data) */
extern int g_0045D32C;   /* (small data) */
extern int g_0045D374;   /* (small data) */
extern int g_0045D378;   /* (small data) */
extern int g_0045D38C;   /* (small data) */
extern int g_0045D390;   /* (small data) */
extern int g_0045D394;   /* (small data) */
extern int g_0045D398;   /* (small data) */
extern int g_0045D3D0;   /* (small data) */
extern int g_0045D400;   /* (small data) */
extern int g_0045D404;   /* (small data) */
extern int g_0045D40C;   /* (small data) */
extern int g_0045D410;   /* (small data) */
extern int g_0045D424;   /* (small data) */
extern int g_0045D428;   /* (small data) */
extern int g_0045D42C;   /* (small data) */
extern int g_0045D430;   /* (small data) */
extern int g_0045D434;   /* (small data) */
extern int g_0045D460;   /* (small data) */
extern int g_0045D464;   /* (small data) */
extern int g_0045D470;   /* (small data) */
extern int g_0045D48C;   /* (small data) */
extern int g_0045D490;   /* (small data) */
extern int g_0045D4A4;   /* (small data) */
extern int g_0045D4A8;   /* (small data) */
extern int g_0045D4D0;   /* (small data) */
extern int g_0045D4E4;   /* (small data) */
extern int g_0045D540;   /* (small data) */
extern int g_0045D544;   /* (small data) */
extern int g_0045D548;   /* (small data) */
extern int g_0045D54C;   /* (small data) */
extern int g_0045D558;   /* (small data) */
extern int g_0045D55C;   /* (small data) */
extern int g_0045D564;   /* (small data) */
extern int g_0045D570;   /* (small data) */
extern int g_0045D5C4;   /* (small data) */
extern int g_0045D5CC;   /* (small data) */
extern int g_0045D5D0;   /* (small data) */
extern int g_0045D5D4;   /* (small data) */
extern int g_0045D5E4;   /* (small data) */
extern int g_0045D5E8;   /* (small data) */
extern int g_0045D5FC;   /* (small data) */
extern int g_0045D600;   /* (small data) */
extern int g_0045D60C;   /* (small data) */
extern int g_0045D620;   /* (small data) */
extern int g_0045D6F8;   /* (small data) */
extern int g_0045D718;   /* (small data) */
extern int g_0045D7C0;   /* (small data) */
extern int g_0045D7D4;   /* (small data) */
extern int g_0045D7D8;   /* (small data) */
extern int g_0045D80C;   /* (small data) */
extern int g_0045D810;   /* (small data) */
extern int g_0045D838;   /* (small data) */
#define g_700000C0 (*(int *)PS2_PTR(0x700000C0))   /* (scratchpad) */
#define g_700000C4 (*(int *)PS2_PTR(0x700000C4))   /* (scratchpad) */
#define g_700000C8 (*(int *)PS2_PTR(0x700000C8))   /* (scratchpad) */
#define g_700000CC (*(int *)PS2_PTR(0x700000CC))   /* (scratchpad) */
#define g_70000130 (*(int *)PS2_PTR(0x70000130))   /* (scratchpad) */
#define g_70000134 (*(int *)PS2_PTR(0x70000134))   /* (scratchpad) */
#define g_70000138 (*(int *)PS2_PTR(0x70000138))   /* (scratchpad) */
#define g_7000013C (*(int *)PS2_PTR(0x7000013C))   /* (scratchpad) */
#define g_70000150 (*(int *)PS2_PTR(0x70000150))   /* (scratchpad) */
#define g_70000154 (*(int *)PS2_PTR(0x70000154))   /* (scratchpad) */
#define g_70000158 (*(int *)PS2_PTR(0x70000158))   /* (scratchpad) */
#define g_7000015C (*(u32 *)PS2_PTR(0x7000015C))   /* (scratchpad) */
#define g_70000160 (*(int *)PS2_PTR(0x70000160))   /* (scratchpad) */
#define g_70000164 (*(int *)PS2_PTR(0x70000164))   /* (scratchpad) */
#define g_700001D0 (*(int *)PS2_PTR(0x700001D0))   /* (scratchpad) */
#define g_700001D4 (*(int *)PS2_PTR(0x700001D4))   /* (scratchpad) */
#define g_700001D8 (*(int *)PS2_PTR(0x700001D8))   /* (scratchpad) */
#define g_700001DC (*(int *)PS2_PTR(0x700001DC))   /* (scratchpad) */
#define g_700001E0 (*(int *)PS2_PTR(0x700001E0))   /* (scratchpad) */
#define g_70000708 (*(int *)PS2_PTR(0x70000708))   /* (scratchpad) */
#define g_70000709 (*(int *)PS2_PTR(0x70000709))   /* (scratchpad) */
#define g_70000710 (*(int *)PS2_PTR(0x70000710))   /* (scratchpad) */
#define g_70000714 (*(int *)PS2_PTR(0x70000714))   /* (scratchpad) */
#define g_70000718 (*(int *)PS2_PTR(0x70000718))   /* (scratchpad) */
#define g_7000071C (*(int *)PS2_PTR(0x7000071C))   /* (scratchpad) */
#define g_700007F0 (*(int *)PS2_PTR(0x700007F0))   /* (scratchpad) */
#define g_70000840 (*(int *)PS2_PTR(0x70000840))   /* (scratchpad) */
#define g_70000841 (*(int *)PS2_PTR(0x70000841))   /* (scratchpad) */
#define g_7000084C (*(int *)PS2_PTR(0x7000084C))   /* (scratchpad) */
#define g_70000878 (*(int *)PS2_PTR(0x70000878))   /* (scratchpad) */
#define g_70000888 (*(int *)PS2_PTR(0x70000888))   /* (scratchpad) */
#define g_7000088C (*(int *)PS2_PTR(0x7000088C))   /* (scratchpad) */
#define g_70000B98 (*(int *)PS2_PTR(0x70000B98))   /* (scratchpad) */
#define g_70000D60 (*(int *)PS2_PTR(0x70000D60))   /* (scratchpad) */
#define g_70000D64 (*(int *)PS2_PTR(0x70000D64))   /* (scratchpad) */
#define g_70000D68 (*(int *)PS2_PTR(0x70000D68))   /* (scratchpad) */
#define g_70000D6C (*(int *)PS2_PTR(0x70000D6C))   /* (scratchpad) */

int func_00100FB0();
void *func_00100FC0();
float func_00100FD0(void);
int func_00100FE0();
int func_00114470();
int func_00114890();
int func_0011B758();
int func_0011ED38();
int func_001204B0();
void *func_00120928();
int func_00120A40();
int func_00124A20();
int func_001251A0();
int func_00125450();
int func_00125508();
int func_00136DE8();
int func_00141758();
int func_00141880();
int func_001418B8();
int func_00141978();
int func_00141B08();
int func_00141C20();
int func_00141D98();
int func_00141EB8();
int func_001420A8();
int func_001423C8();
int func_001425B8();
void *func_0014F810();
int func_00174A40(float r, u8 *a, u8 *b);
int func_0017AA80();
int func_0017AC50();
int func_0017DC00();
int func_0017DF10();
int func_0017E110();
int func_0017E600();
int func_00181020();
int func_001811A0(int, float *, u8 *, u8 *, u8 *, u8 *, int);
int func_001882F0();
int func_0018D500();
void func_001ACA70(u8 *b, u8 *kind, float *pos, float *dir, u8 *unit);
int func_001C1900();
int func_001C2270();
void func_001C2540(float, int, int, int, float *, int);
int func_001C2D30();
int func_001C3AB0();
int func_001C53F0();
int func_001C6230();
int func_001C64E0();
int func_001C7560();
void func_001C7F30(int k, float *pos, int c, u32 f);
int func_001CBFB0();
int func_001D6CE0();
int func_001D7740();
int func_001DD540();
int func_001EBFC0();
int func_001ED580();
int func_001EE570();
int func_001F5570();
float func_001F5900(u8 *);
int func_001F5A60();
int func_001FCC90();
int func_001FF100();
void *func_001FF140();
void *func_001FF230();
void func_001FF450(float f, u8 *u);
int func_00203C70();
int func_002040C0();
int func_00204300();
int func_00204B60();
void func_002075A0(float yaw, u8 *r, float *out, int a);
int func_00207930();
int func_002093E0(u8 *, float *, int, int);
float func_0020A060(int, int);
int func_0020AEA0();
int func_0020AFF0();
int func_0020B110();
int func_0020B2B0();
int func_0020B410();
int func_00210580();
int func_00211BF0();
int func_00212C00();
int func_002136F0();
int func_00217F40();
void *func_0021A630();
int func_00228580();
int func_0022A000();
int func_0022A010();
int func_0022A0E0();
int func_0022A1F0();
int func_0022C370(int, int, float *, int);
int func_00237740();
int func_00238AE0();
int func_002392D0();
int func_00246680();
int func_00247060();
int func_00247AF0();
int func_00247B90(float, int, u8 *, int);
int func_002481C0();
int func_002486A0();
int func_002493B0();
int func_00249810();
int func_00249AF0();
void func_0024AF80(u8 *, int, int, float *, int);
int func_00254080();
int func_00254330();
int func_00254470();
int func_00254880();
int func_00271CF0();
int func_0027C030();
int func_0027C210();
int func_0027E220();
int func_00286230();
int func_002863C0();
void func_0028EED0(float *out);
int func_00291F10(int, float *);
int func_00293F90();
int func_00295070();
int func_002969B0();
int func_00296F20();
int func_00298A00();
int func_00299B90();
int func_0029D210();
int func_0029D430();
int func_0029D4B0();
float func_0029DB50(float, float, float, float, float, float, float);
float func_0029DBC0(float, float, float, float, float, float, float);
int func_0029F3A0();
int func_002A6910();
int func_002A6D20();
int func_002A6D50();
int func_002A8090();
int func_002A85C0();
void *func_002A85D0();
int func_002AA1E0();
int func_002AA8D0();
int func_002AB0E0();
int func_002AFC20();
int func_002B6340();
int func_002BB490();
int func_002BC110();
int func_002BD220();
int func_002BFD30();
int func_002C0010();
int func_002C0C80();
int func_002C1CC0();
int func_002C5930();
int func_002C7310();
int func_002C8AC0();
int func_002C92A0();
int func_002CA730();
int func_002CE1B0();
int func_002CEF60();
int func_002CF370();
int func_002CF670();
int func_002CFFD0();
int func_002D07E0();
void func_002D37F0(float, int, int, int, int, int, int, int, int, int, int);
int func_002D73D0();
int func_002D8480();
int func_002D9010();
int func_002DA8C0();
int func_002DBAA0();
int func_002E1700();
int func_002E4C40();
int func_002E9FA0();
int func_002EB210();
int func_002ED160();
int func_002ED170();
void *func_002EE5D0();
int func_002F7D90();
void *func_0030D7D0();
int func_00324910();
int func_00347F20();
void *func_0034AB10();
int func_00380E80();
int func_00389AC0();
int func_0038A010();
int func_0038A330();
int func_0038A3D0();
int func_0038A470();
int func_0038C400();
int func_0038C5A0();
void *func_0038C6E0();
void *func_0038E730();
void *func_0038E750();
int func_0038E770();
int func_0038F4A0();
int func_0038F5C0();
int func_0039D930();
int func_0039DB70();
int func_003A64A0();
int func_003A8460();
int func_003BCAE0();
int func_003D96A0();
int func_003DDFB0();
int func_0040C920();
int func_0040CBC0();
int func_0040CC00();
int func_0040D270();
int func_004114B0();
int func_004114B4();
int func_004114B8();
int func_004114C0();
int func_004114C4();
int func_004114C8();
int func_004114CC();
int func_004114D0();
int func_004114D4();
int func_00411B40();
int func_00411B44();
int func_00411B48();
int func_00411B4C();
int func_00412020();
int func_00412490();
int func_00414E70();
int func_00417670();
int func_0041C140();
int func_0041C144();
int func_0041C148();
int func_0041C14C();
int func_0041C150();
int func_0042A340();
int func_0043FE40();
int func_0043FE5C();
int func_00442D20();
int func_00442D40();
void func_001806C0(u8 *param_1);
void func_001817E0(void);
int func_001829E0(int param_1);
void func_00183A40(void);
void func_00184300(int param_1);
void func_00187F20(u16 *param_1);
void func_001887A0(u16 *param_1);
void func_0018A290(short *param_1, int param_2, int param_3);
void func_0018DA60(u8 *param_1, int *param_2, int param_3);
void func_00195EF0(void);
void func_001C3800(u32 *param_1, int param_2);
void func_001C3890(float *param_1, int param_2);
void func_001C4D10(int param_1, float *param_2);
void func_001C66C0(u8 *param_1);
int func_001C7DB0(int param_1, int param_2, int param_3);
void func_001C8CF0(int param_1);
int func_001CAC90(int param_1, u32 *param_2, u8 *param_3, int param_4);
void func_001CF430(float param_1, u8 *param_2, int param_3);
void func_001D0C20(u8 *param_1, int param_2);
void func_001D1B50(u8 *param_1);
int func_001D6C70(u8 *param_1);
void func_001D73A0(u8 *param_1);
void func_001D7470(float param_1, int param_2);
void func_001D76F0(void);
void func_001DD350(int param_1, int param_2, int param_3);
void func_001DE980(u8 *param_1);
void func_001E01D0(float param_1, int param_2);
void func_001E0B40(int param_1, int param_2);
void func_001E0E60(int param_1, int param_2);
void func_001E10D0(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_001E1380(int param_1);
void func_001E9850(int param_1);
void func_001E9980(void);
void func_001EC210(u8 *param_1);
void func_001EC3C0(u8 *param_1);
void func_001EC450(u8 *param_1);
void func_001EC530(u8 *param_1);
void func_001EC5C0(u8 *param_1);
int func_001ED100(int param_1, int param_2, int param_3);
void func_001EDE10(u8 *param_1, int param_2);
void func_001EDFB0(u8 *param_1, int param_2);
int func_001EE150(int param_1);
int func_001EF6B0(u8 *param_1, u8 *param_2, int param_3, int param_4);
int func_001EFD50(u8 *param_1, u8 *param_2);
void func_001F0540(void);
int func_001F62C0(u8 *param_1);
void func_001F9AC0(int param_1, int param_2, int param_3, int param_4);
void func_001FBED0(void);
void func_001FC800(void);
void func_001FEE00(int param_1);
void func_002039F0(u8 *param_1, int param_2);
void func_00204920(void);
void func_00206080(u8 *param_1);
int func_00206290(u8 *param_1);
void func_002071F0(u8 *param_1, int param_2);
void func_002072C0(u8 *param_1);
int func_00207830(u8 *param_1);
u8 *func_00208270(u8 *param_1, u8 *param_2);
int func_00208470(u32 *param_1);
int func_0020CC60(int param_1, int param_2, u8 *param_3, u8 *param_4);
void func_0020CFF0(u8 *param_1);
void func_0020D260(u8 *param_1);
void func_0020D5C0(int param_1, int param_2);
void func_0020DBD0(int param_1, int param_2);
void func_0020DC80(int param_1, int param_2);
int func_0020EEC0(u32 *param_1);
void func_0020F420(void);
void func_00213B40(int param_1, int param_2);
void func_00213F90(void);
void func_00214E50(int param_1);
void func_00214FC0(u8 *param_1);
void func_00218710(float param_1, float param_2, float param_3, float param_4);
void func_00218E80(void);
void func_0021A320(void);
int func_00228320(u32 *param_1);
int func_002283A0(u32 *param_1);
void func_002284E0(int param_1);
int func_00228A00(u32 *param_1, int param_2);
int func_00228B40(u32 *param_1);
void func_00229140(void);
void func_00229340(int param_1, int param_2, int param_3);
int func_00229800(u32 *param_1);
int func_00229A40(u32 *param_1);
int func_0022A480(u32 *param_1, u8 *param_2);
int func_0022AF70(int *param_1, u8 *param_2);
void func_0022B9B0(u8 *param_1, u8 *param_2, u8 *param_3);
void func_0022BC70(u8 *param_1, int param_2);
void func_0022BF40(u8 *param_1, int param_2, u8 *param_3, u8 *param_4);
int func_0022C690(int param_1, int param_2, unsigned long long *param_3);
int func_0022C9E0(u8 *param_1, int param_2, u8 *param_3, int *param_4);
void func_0022CD40(int param_1, int param_2, int param_3);
void func_0022CD70(int param_1, int param_2);
int func_0022CDA0(u8 *param_1, unsigned long long *param_2);
void func_0022ECD0(int param_1);
void func_0022F120(u8 *param_1, u8 *param_2, u8 *param_3, int param_4, int param_5);
void func_0022F450(int param_1, int param_2);
void func_0022F4B0(int param_1, int param_2);
void func_0022F730(int param_1);
void func_00237200(u8 *param_1);
int func_00237800(int param_1);
void func_00239E60(u8 *param_1);
void func_0023BA20(void);
void func_00245570(u8 *param_1);
void func_002456C0(int param_1, int param_2, int param_3);
int func_002456F0(u8 *param_1, int param_2, u32 *param_3, int param_4);
void func_002457D0(int param_1);
void func_00245960(int param_1, int param_2);
void func_00245ED0(int param_1, u8 *param_2);
void func_00246B40(u8 *param_1);
void func_00247250(void);
void func_00247410(void);
void func_002474A0(void);
void func_002477B0(void);
void func_00247850(int param_1, int param_2);
void func_002478E0(int param_1, int param_2);
void func_00248D10(int param_1, u8 *param_2, int param_3, int param_4);
void func_0024A9B0(void);
void func_0024B330(int param_1, int param_2);
void func_002554B0(u8 *param_1);
void func_00256310(u8 *param_1);
void func_00258050(u8 *param_1);
void func_002580C0(u8 *param_1);
void func_00258920(u8 *param_1);
void func_00259400(u8 *param_1);
void func_0025FF80(u8 *param_1, int param_2);
void func_00262130(void);
void func_00264840(int param_1);
int func_00271E70(u8 *param_1);
void func_002723B0(u32 *param_1, int param_2);
void func_002788F0(void);
void func_00278A20(void);
void func_00278CF0(void);
void func_00279070(int param_1, int param_2, short *param_3, int param_4, int param_5, int param_6);
void func_002790E0(int param_1, int param_2);
void func_00279240(void);
void func_0027A080(int param_1, u32 *param_2, int param_3, int param_4);
int func_0027D6B0(u8 *param_1, int param_2);
int func_0027D960(int param_1, u8 *param_2, u8 *param_3, int *param_4, int param_5);
int func_0027DE50(void);
void func_0027F800(void);
int func_0027FC60(u8 *param_1);
void func_002861D0(int param_1, int param_2, int param_3, int param_4);
void func_00286420(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, u8 *param_7, int param_8);
void func_00286CA0(int param_1, int param_2, int param_3);
void func_002875F0(int param_1, int param_2, u8 *param_3, u8 *param_4);
void func_00287A10(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_00288660(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_00288990(void);
void func_00288AA0(void);
int func_00289640(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_0028A580(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_0028AD00(int param_1, int param_2, int param_3, int param_4);
void func_0028B1D0(int param_1, int param_2, int param_3, int param_4);
void func_0028B730(int param_1, int param_2, int param_3, int param_4);
int func_0028C4A0(int param_1);
int func_0028CC20(int param_1, int param_2, int param_3, int param_4);
void func_0028FB40(u8 *param_1);
void func_00290CE0(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002937E0(int param_1, u32 *param_2);
void func_002944D0(void);
void func_00295C70(int param_1, int param_2, int param_3, int param_4);
void func_00296340(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002966E0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9);
void func_00296930(int param_1, u8 *param_2, u8 *param_3);
void func_00297530(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_00297890(u8 *param_1, int param_2, int param_3, int param_4);
void func_00297C00(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_00298670(int param_1, u8 *param_2, int param_3, int param_4, int param_5);
void func_0029A1C0(int param_1, int param_2, int param_3, int param_4, u8 *param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11);
void func_0029A610(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_0029ABA0(int param_1, int param_2, int param_3, int param_4, u8 *param_5, int param_6, int param_7, int *param_8, int param_9);
void func_0029AE90(int param_1, int param_2, int param_3, int param_4, u8 *param_5, int param_6, int param_7, int *param_8, int param_9);
u8 *func_0029B100(int param_1);
void func_0029B1C0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void func_0029BBC0(int param_1, int param_2, int param_3, int param_4, u8 *param_5, int param_6);
void func_0029BEC0(int param_1, int param_2, int param_3, int param_4, u8 *param_5);
void func_0029C140(int param_1, int param_2);
void func_0029C2D0(int param_1, int param_2);
void func_0029C460(int param_1, int param_2, int param_3, int param_4, u8 *param_5);
void func_0029C690(int param_1, int param_2, int param_3);
void func_0029C800(int param_1, int param_2, u8 *param_3);
void func_0029C8B0(u8 *param_1);
void func_0029C930(u8 *param_1);
void func_0029D520(int param_1, int param_2, int param_3);
void func_0029D6F0(u8 *param_1);
void func_0029DD90(int param_1, int param_2, int param_3, float param_4, float param_5);
void func_0029DDE0(int param_1, int param_2, int param_3, float param_4, float param_5);
void func_002A5D70(int param_1, int param_2, int param_3);
void func_002A6430(void);
void func_002A6470(void);
int func_002A71A0(int param_1, u8 *param_2, int param_3);
void func_002A7560(void);
void func_002A85F0(int param_1, int param_2, int param_3, int param_4);
void func_002A86A0(int param_1);
void func_002AA7B0(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void func_002ABB40(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_002ABFD0(int param_1, u8 *param_2, int param_3);
void func_002AC330(int param_1, int param_2, int param_3, int *param_4, u8 *param_5, int param_6, int param_7);
void func_002AC7F0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_002ACC30(int param_1, int param_2, int param_3, int param_4, u8 *param_5);
void func_002ACEC0(int param_1, int param_2, int param_3, int param_4, u8 *param_5);
void func_002ADA00(void);
void func_002ADDE0(void);
void func_002AFA20(int param_1);
void func_002AFB80(u8 *param_1);
void func_002B4BA0(int param_1, int param_2);
void func_002B6120(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11);
int func_002B89E0(int param_1);
int func_002B8BC0(int param_1, u32 *param_2, int param_3);
int func_002B9190(int param_1, u32 *param_2, int param_3, int param_4, int param_5);
int func_002B9360(u8 *param_1, u8 *param_2, int param_3);
void func_002B9CC0(int param_1);
int func_002BBEB0(void);
int func_002BCC00(u32 *param_1, int param_2);
int func_002BCFA0(u8 *param_1, u8 *param_2, int param_3);
int func_002BDE30(u8 *param_1, int param_2);
void func_002BF9E0(int param_1, int param_2);
void func_002BFF70(u8 *param_1);
int func_002C0EE0(int param_1);
int func_002C1080(u8 *param_1, int param_2);
int func_002C12C0(int param_1, u32 *param_2);
int func_002C1880(int param_1, u32 *param_2);
void func_002C1DC0(void);
int func_002C1EF0(int *param_1);
void func_002C2B40(int param_1, int *param_2);
int func_002C3980(int param_1, u8 *param_2, int param_3);
int func_002C43C0(u8 *param_1, int *param_2, int param_3);
void func_002C98E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9);
int func_002CAA90(int param_1, int param_2);
void func_002CB550(void);
void func_002CB5B0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11, u32 *param_12, int param_13);
void func_002CC130(unsigned long long *param_1, int param_2, int param_3);
void func_002CC560(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11, int param_12, int param_13, int param_14, int param_15);
void func_002CD5E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_002CD780(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_002CD940(float param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_002CDB70(float param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_002CE8B0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11, int param_12);
void func_002CFA00(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11, int param_12);
void func_002CFB80(int param_1, u8 *param_2, int param_3, int param_4, int param_5, u8 *param_6, int param_7);
void func_002CFF50(void);
void func_002CFF90(void);
void func_002D1800(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002D1C70(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002D2160(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_002D3490(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void func_002D37C0(void);
void func_002D5CE0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void func_002D81D0(u8 *param_1);
void func_002D8DA0(u8 *param_1);
int func_002DA090(void);
void func_002DA2D0(int param_1);
int func_002DC510(u8 *param_1, u32 *param_2);
void func_002DC5C0(u8 *param_1);
int func_002DCD80(int param_1, u32 *param_2);
void func_002DCF00(u8 *param_1);
int func_002DF700(int param_1, int param_2);
int func_002DF770(float param_1, u8 *param_2);
void func_002E05C0(int param_1, int param_2, int param_3);
void func_002E41F0(int param_1, u8 *param_2);
void func_002E5810(void);
int func_002E59C0(u32 *param_1);
int func_002E5A40(u32 *param_1);
void func_002E6070(int param_1, int param_2, int param_3, int param_4);
void func_002E6800(int param_1, int param_2, int param_3, int param_4);
int func_002ECA70(void);
void func_002EF390(int param_1, int param_2, int param_3, int param_4);
void func_002EFA70(u8 *param_1, u32 *param_2);
void func_002F0490(int param_1);
void func_00320790(void);
void func_003246C0(int param_1, u32 *param_2);
void func_00325710(void);
void func_00325C90(void);
void func_00325D90(void);
int func_00326000(int param_1, int *param_2, u8 *param_3, int *param_4, u8 *param_5);
int func_003261C0(void);
void func_003264B0(void);
void func_003266D0(void);
void func_00326850(void);
void func_00326A90(void);
int func_00326E30(void);
void func_0032C080(void);
int func_0032D180(int param_1);
void func_0032D270(int param_1);
void func_0032D3C0(int param_1);
int func_0032F420(int param_1);
int func_00330650(int param_1);
int func_00334000(void);
void func_0034F730(u8 *param_1);
void func_00369FE0(void);
int func_0036AA60(void);
void func_0036C9A0(void);
void func_0036E740(int param_1);
int func_003748C0(int param_1, int param_2, int param_3);
void func_00375E00(void);
void func_00375F90(void);
void func_003764B0(void);
void func_003765C0(void);
void func_0037DAD0(int param_1);
void func_0037DDD0(int param_1, int param_2, int param_3, int param_4);
void func_0037E230(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void func_0037E480(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9);
void func_0037EB60(int param_1, int param_2, int param_3, int param_4);
void func_0037ED80(int param_1, int param_2, int param_3, int param_4, int *param_5, int *param_6, int param_7);
void func_0037F610(int param_1, int param_2, int param_3, int param_4, int *param_5);
void func_0037FD50(int param_1, int param_2, int param_3, int param_4);
void func_00381390(float param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int *param_7);
void func_00381CA0(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_00383360(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_00383880(int param_1, int param_2);
void func_00383A80(int param_1, int param_2);
void func_00383D80(u32 *param_1);
void func_00383E00(int param_1);
void func_003852A0(void);
void func_00386520(int param_1);
void func_003886D0(void);
void func_00388710(void);
int func_00389150(u8 *param_1);
int func_003892C0(u8 *param_1);
int func_003893C0(u8 *param_1);
int func_003899E0(u8 *param_1);
void func_00389B40(int param_1, int param_2, u8 *param_3);
int func_0038A5D0(u8 *param_1);
void func_0038B3B0(u8 *param_1);
void func_0038B5C0(void);
void func_0038C910(void);
void func_0038DC80(int param_1);
void func_0038E880(int param_1);
void func_0038ED90(void);
void func_00392FF0(int param_1);
void func_00397B10(int param_1);
void func_00397F40(void);
void func_00398C90(int param_1, int param_2, int param_3, int param_4);
void func_00398ED0(void);
int func_0039A160(void);
int func_0039A3B0(void);
int func_0039A630(void);
void func_0039B980(void);
int func_0039D4A0(void);
void func_0039D950(int param_1);
void func_0039D990(int param_1);
void func_0039D9D0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11, int param_12, int param_13, int param_14);
void func_0039E380(void);
int func_0039E500(void);
void func_0039EFB0(int param_1);
void func_003A34C0(void);
void func_003A63D0(int param_1);
void func_003A70D0(void);
void func_003A7360(void);
void func_003A86F0(u8 *param_1);
void func_003A8B90(void);
void func_003AEF30(int param_1);
void func_003B34A0(int param_1);
void func_003B4180(int param_1, int param_2, int param_3, int param_4, int *param_5, u16 *param_6, u8 *param_7, int param_8);
void func_003B4EC0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_003B4F50(int param_1);
void func_003B56E0(int param_1, int param_2);
void func_003B5CC0(int param_1, int param_2, int param_3, int param_4);
void func_003B69A0(void);
int func_003B9770(int param_1);
void func_003BC150(void);
void func_003BCDD0(void);
void func_003D4080(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_003D47A0(int param_1, int param_2, int param_3, int param_4);
void func_003D54C0(void);
void func_003DA1B0(void);
void func_003DACA0(void);
void func_003DAF70(void);
void func_003DC300(void);
void func_003DDBD0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, u8 *param_8, int param_9, int param_10);
void func_003DE580(void);
void func_003DF5C0(int param_1, int param_2, int param_3, u32 *param_4, u32 *param_5);
void func_003DFD80(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int *param_7, u8 *param_8);
void func_003E3770(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_003E3ED0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_003EBE60(void);
void func_003ED480(void);
void func_003EDD00(void);
void func_003EF930(int param_1);
void func_003F0CE0(int param_1, int param_2, u8 *param_3, int param_4, int param_5, int param_6, int param_7);
int func_003F1B50(int param_1);

/* 0x00180F00, 0x118 bytes. */
float func_00180F00(float param_1, u8 *param_2)
{
  if ((*(u32 *)(param_2 + 0x80) & 0x400) != 0) {
    param_1 = param_1 * 0.85f;
  }
  if (*(char *)(param_2 + 0x79) != '\0') {
    param_1 = param_1 * 0.9f;
  }
  if ((*(u32 *)(param_2 + 0x80) & 0x20000) != 0) {
    if ((*(int *)(param_2 + 8) - (*(u32 *)(g_005BA6A0 + 0x0))) / 0x2c == 0x11) {
      param_1 = param_1 * 0.5f;
    }
    else {
      param_1 = param_1 * 0.95f;
      if (*(int *)PS2_PTR((*(int *)PS2_PTR((*(int *)(param_2 + 0x14) * 0xc0 + 0x6a3a44)) + 0x11c)) != 0) {
        param_1 = param_1 * 0.8f;
      }
    }
    if (*(char *)(param_2 + 0x7a) == '\x03') {
      param_1 = param_1 * 0.5f;
    }
  }
  return param_1;
}

/* MISSING ['0x574e70', '0x574e78', '0x574e7c', '0x5754a0', '0x5754a8', '0x5754ac'] */

/* MISSING ['0x406940', '0x406944', '0x406948', '0x40694c', '0x406950', '0x406954', '0x406958', '0x40695c', '0x406960', '0x406964', '0x406968'] */

/* 0x00187CE0, 0xC0 bytes. */
void func_00187CE0(u16 *param_1)
{
    u8 auStack_20[24];
    float fStack_4;
    float fStack_8;

  
  fStack_8 = (float)*param_1 * 100.0f;
  fStack_4 = (float)param_1[1] * 100.0f;
  func_001911A0((float *)(auStack_20),&fStack_8);
  func_0024D070(param_1[2],(unsigned int *)(auStack_20));
  return;
}

/* 0x001C2740, 0x78 bytes. */
void func_001C2740(u8 *param_1, u8 *param_2)
{
  if (g_70000D68 == 0) {
    *(float *)(param_1 + 0x298) = *(float *)(param_1 + 0x298) + *(float *)(param_2 + 0x24);
  }
  else {
    *(float *)(param_1 + 0x298) =
         *(float *)(param_2 + 0x24) * g_70000D6C + *(float *)(param_1 + 0x298) + 0.0f;
  }
  if ((float)(*(int *)(param_2 + 8) * *(int *)(param_2 + 4) + -1) < *(float *)(param_1 + 0x298)) {
    *(u32 *)(param_1 + 0x298) = 0;
  }
  return;
}

/* 0x001C27C0, 0x11C bytes. */
void func_001C27C0(u8 *param_1, u8 *param_2)
{
  if (g_70000D68 == 0) {
    *(float *)(param_1 + 0x288) = *(float *)(param_1 + 0x288) + *(float *)(param_2 + 0x30);
    *(float *)(param_1 + 0x28c) = *(float *)(param_1 + 0x28c) + *(float *)(param_2 + 0x34);
    *(float *)(param_1 + 0x290) =
         *(float *)(param_1 + 0x280) * *(float *)(param_1 + 0x288) +
         *(float *)(param_1 + 0x290) + 0.0f;
    *(float *)(param_1 + 0x294) =
         *(float *)(param_1 + 0x284) * *(float *)(param_1 + 0x28c) +
         *(float *)(param_1 + 0x294) + 0.0f;
  }
  else {
    *(float *)(param_1 + 0x288) =
         *(float *)(param_2 + 0x30) * g_70000D6C + *(float *)(param_1 + 0x288) + 0.0f;
    *(float *)(param_1 + 0x28c) =
         *(float *)(param_2 + 0x34) * g_70000D6C + *(float *)(param_1 + 0x28c) + 0.0f;
    *(float *)(param_1 + 0x290) =
         *(float *)(param_1 + 0x280) * *(float *)(param_1 + 0x288) * g_70000D6C +
         *(float *)(param_1 + 0x290) + 0.0f;
    *(float *)(param_1 + 0x294) =
         *(float *)(param_1 + 0x284) * *(float *)(param_1 + 0x28c) * g_70000D6C +
         *(float *)(param_1 + 0x294) + 0.0f;
  }
  if (*(float *)(param_1 + 0x290) < 0.0f) {
    *(u32 *)(param_1 + 0x290) = 0;
  }
  if (*(float *)(param_1 + 0x294) < 0.0f) {
    *(u32 *)(param_1 + 0x294) = 0;
  }
  return;
}

/* 0x001C5C70, 0xCC bytes. */
void func_001C5C70(float param_1, u8 *param_2, u8 *param_3, int param_4)
{
  param_1 = param_1 * *(float *)(param_3 + 0x2fc);
  if (g_70000D60 == 3) {
    *(u32 *)(param_2 + 0x20) = 0;
    *(u32 *)(param_2 + 0x24) = 0;
    *(u32 *)(param_2 + 0x28) = 0;
    *(u32 *)(param_2 + 0x2c) = 0xff;
  }
  else if ((param_4 & 0x10a) == 0) {
    *(int *)(param_2 + 0x2c) = (int)(param_1 * 128.0f);
  }
  else {
    *(int *)(param_2 + 0x20) = (int)(*(float *)(param_3 + 0x2f0) * 128.0f);
    *(int *)(param_2 + 0x24) = (int)(*(float *)(param_3 + 0x2f4) * 128.0f);
    *(int *)(param_2 + 0x28) = (int)(*(float *)(param_3 + 0x2f8) * 128.0f);
    *(int *)(param_2 + 0x2c) = (int)(param_1 * 128.0f);
  }
  return;
}

/* 0x001C5D40, 0xD0 bytes. */
void func_001C5D40(float param_1, u8 *param_2, int param_3)
{
    float * pfVar1;
    u32 uVar2;

  
  uVar2 = 0;
  pfVar1 = (float *)(g_00425EB0 + 0x0);
  do {
    if ((param_3 & 2) != 0) {
      *(float *)(param_2 + 0x30) = *(float *)(param_2 + 0x30) * *pfVar1;
      if ((g_70000D60 == 6) || (g_70000D60 == 0xe)) {
        *(float *)(param_2 + 0x34) = *(float *)(param_2 + 0x34) * pfVar1[1] * 0.54f;
        *(u32 *)(param_2 + 0x38) = 0xfffe0;
      }
      else {
        *(float *)(param_2 + 0x34) = *(float *)(param_2 + 0x34) * pfVar1[1];
      }
      if ((param_3 & 0x100) != 0) {
        *(float *)(param_2 + 0x34) = *(float *)(param_2 + 0x34) - param_1;
      }
    }
    uVar2 = uVar2 + 1;
    param_2 = param_2 + 0x30;
    pfVar1 = pfVar1 + 4;
  } while (uVar2 < 4);
  return;
}

/* 0x001C72F0, 0xAC bytes. */
int func_001C72F0(int param_1, int param_2, int param_3, int param_4)
{
    int iVar1;
    u32 uVar2;

  
  iVar1 = *(int *)PS2_PTR((g_70000D60 * 0x350 + 0x72d224));
  uVar2 = 1;
  while( true ) {
    if (iVar1 == 0) {
      return uVar2;
    }
    if ((*(int *)((u8 *)PS2_PTR(iVar1) + 0x24) == param_1) && (*(int *)((u8 *)PS2_PTR(iVar1) + 0x104) == param_4)) {
      if (*(float *)((u8 *)PS2_PTR(iVar1) + 0x28) < 0.2f) {
        uVar2 = 0;
      }
      else {
        *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x34) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x34) | 0x800;
      }
    }
    if ((param_2 != 0) && (*(int *)((u8 *)PS2_PTR(iVar1) + 0x24) == param_3)) break;
    iVar1 = *(int *)((u8 *)PS2_PTR(iVar1) + 0xf4);
  }
  *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x34) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x34) | 0x800;
  return uVar2;
}

/* 0x001D6DE0, 0x25C bytes. */
void func_001D6DE0(u8 *param_1, u32 *param_2)
{
    int bVar7;
    int iStack_4;
    int iVar5;
    int iVar6;
    u8 * puVar1;
    u8 * puVar2;
    u32 uVar3;
    u32 uVar4;
    u32 uVar8;
    u32 uVar9;

  
  iVar5 = PS2_ADDR(param_1);
  bVar7 = 0;
  if (*(char *)PS2_PTR((*(int *)((u8 *)PS2_PTR(iVar5) + 8) + 6)) != '\0') {
    do {
      puVar1 = ((u8 *)PS2_PTR(*(ps2ptr *)((u8 *)PS2_PTR(iVar5) + 0x10)));
      *(ps2ptr *)((u8 *)PS2_PTR(iVar5) + 0x10) = PS2_ADDR(puVar1 + 1);
      puVar2 = ((u8 *)PS2_PTR(*(ps2ptr *)((u8 *)PS2_PTR(iVar5) + 0x14)));
      *(ps2ptr *)((u8 *)PS2_PTR(iVar5) + 0x14) = PS2_ADDR(puVar2 + 1);
      uVar3 = func_001D6BD0((unsigned int *)(&iStack_4),(unsigned int *)PS2_PTR(*(u32 *)((u8 *)PS2_PTR(iVar5) + 0xc)),*puVar1,*puVar2);
      *(u32 *)((u8 *)PS2_PTR(iVar5) + 0xc) = uVar3;
      param_2 = (u32 *)PS2_PTR((*(int *)((u8 *)PS2_PTR(iVar5) + 4) + iStack_4));
      if (*(char *)((u8 *)PS2_PTR(iVar5) + 0x50) == '\0') {
        uVar4 = *param_2 & *(u32 *)((u8 *)PS2_PTR(iVar5) + 0x18);
      }
      else if (*(char *)((u8 *)PS2_PTR(iVar5) + 0x50) == '\x01') {
        uVar4 = (u32)(*param_2 == *(u32 *)((u8 *)PS2_PTR(iVar5) + 0x18));
      }
      else {
        uVar4 = 0;
      }
    } while ((uVar4 == 0) && (bVar7 = bVar7 + 1, bVar7 < *(u8 *)PS2_PTR((*(int *)((u8 *)PS2_PTR(iVar5) + 8) + 6))));
  }
  if (bVar7 != *(u8 *)PS2_PTR((*(int *)((u8 *)PS2_PTR(iVar5) + 8) + 6))) {
    if (param_2[1] == 0x51) {
      *(ps2ptr *)((u8 *)PS2_PTR(iVar5) + 0x1c) = PS2_ADDR(param_2);
      *(u32 *)((u8 *)PS2_PTR(iVar5) + 0x44) = 0;
    }
    if ((*(float *)((u8 *)PS2_PTR(iVar5) + 0x40) < 1.0f) || ((*(u32 *)(g_0073C790 + 0x0)) == 0xb6)) {
      func_001D7470(0,PS2_ADDR(param_1));
      iVar6 = (*(u32 *)(g_0073C480 + 0x0));
      if ((*(u32 *)(g_0073C790 + 0x0)) == 0xb6) {
        if (*(float *)((u8 *)PS2_PTR(iVar5) + 0x40) < 1.0f) {
          iVar5 = (*(int *)g_0045D3E0) * 0x240;
          uVar3 = *(u32 *)(g_00730734 + iVar5);
          uVar8 = *(u32 *)(g_00730738 + iVar5);
          uVar9 = *(u32 *)(g_0073073C + iVar5);
          *(u32 *)PS2_PTR(((*(u32 *)(g_0073C480 + 0x0)) + 0x400)) = *(u32 *)(g_00730730 + iVar5);
          *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x404) = uVar3;
          *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x408) = uVar8;
          *(u32 *)((u8 *)PS2_PTR(iVar6) + 0x40c) = uVar9;
          iVar5 = (*(u32 *)(g_0073C480 + 0x0));
          iVar6 = (*(int *)g_0045D3E0) * 0x240;
          uVar3 = *(u32 *)(g_00730744 + iVar6);
          uVar8 = *(u32 *)(g_00730748 + iVar6);
          uVar9 = *(u32 *)(g_0073074C + iVar6);
          *(u32 *)PS2_PTR(((*(u32 *)(g_0073C480 + 0x0)) + 0x410)) = *(u32 *)(g_00730740 + iVar6);
          *(u32 *)((u8 *)PS2_PTR(iVar5) + 0x414) = uVar3;
          *(u32 *)((u8 *)PS2_PTR(iVar5) + 0x418) = uVar8;
          *(u32 *)((u8 *)PS2_PTR(iVar5) + 0x41c) = uVar9;
        }
        func_002E5ED0();
        func_00218790(0,1);
        func_00218C40(0,1);
      }
      else if ((*(int *)g_0045D3E0) == 0) {
        func_00218790(0,1);
        func_00218C40(0,1);
      }
      else if ((*(int *)g_0045D3E0) == 1) {
        func_002E5ED0();
        func_00218790(1,1);
        func_00218C40(1,1);
      }
    }
  }
  return;
}

/* MISSING ['0x730560', '0x730564', '0x730568'] */

/* MISSING ['0x730560', '0x730564', '0x730568', '0x73056c'] */

/* MISSING ['0x45d3e0'] */

/* 0x001FBFB0, 0x70 bytes. */
int func_001FBFB0(float param_1, int param_2)
{
    int iVar2;
    int iVar3;
    u32 uVar1;

  
  iVar3 = g_7000088C * 0x750;
  uVar1 = *(u32 *)(g_00732CB8 + iVar3);
  if (uVar1 < 0x20) {
    *(u32 *)PS2_PTR((uVar1 * 4 + iVar3 + 0x732670 + 0x64c)) = param_2;
    iVar2 = *(int *)(g_00732CB8 + iVar3);
    *(int *)(g_00732CB8 + iVar3) = iVar2 + 1;
    *(float *)PS2_PTR((iVar2 * 4 + iVar3 + 0x732670 + 0x6cc)) = param_1 * 128.0f;
  }
  return uVar1 < 0x20;
}

/* 0x00200360, 0x64 bytes. */
void func_00200360(float *param_1)
{
    float fVar1;

  
  fVar1 = *(float *)((g_004299B0 + 0x18) + g_70000888 * 4) * *(float *)PS2_PTR(((*(u32 *)(g_0045D2C0 + 0x0)) + 0x238));
  *param_1 = 1.0f / ((fVar1 + 0.0f) -
                   *(float *)PS2_PTR(((*(u32 *)(g_0045D2C0 + 0x0)) + 0x238)) * *(float *)((g_004299B0 + 0x0) + g_70000888 * 4));
  param_1[1] = 0.0f;
  param_1[2] = 1.0f;
  param_1[3] = fVar1;
  return;
}
/* MISSING ['0x45d2c0'] */

/* MISSING ['0x40cff0', '0x40cff4', '0x40cff8', '0x40cffc', '0x40d000', '0x40d004', '0x40d008', '0x40d00c', '0x40d010', '0x40d014'] */

/* MISSING ['0x45d2c0'] */

/* 0x002095D0, 0x300 bytes. */
void func_002095D0(int param_1, u8 *param_2)
{
    int bVar1;
    int bVar15;
    int bVar16;
    int bVar5;
    int bVar6;
    float fVar22;
    u8 * iVar11;
    u8 * iVar13;
    int iVar7;
    int iVar8;
    long long lVar14;
    float * pfVar19;
    float * pfVar4;
    int * piVar20;
    u16 * puVar17;
    int uVar10;
    u32 uVar12;
    u32 uVar18;
    int uVar2;
    u32 uVar21;
    u32 uVar3;
    int uVar9;

  
  uVar2 = *(u16 *)(param_2 + 0x54);
  iVar11 = func_001FF140(uVar2);
  uVar3 = *(u32 *)(param_2 + 0x5c);
  pfVar19 = (float *)PS2_PTR((g_700001D4 + (u32)*(u16 *)(param_2 + 0x56) * 0x20));
  bVar1 = *(u8 *)(param_2 + 100);
  uVar9 = func_001FF100(uVar2,0);
  puVar17 = (u16 *)(iVar11 + 0x30);
  uVar21 = 0;
  if (*(short *)(iVar11 + 4) != 0) {
    do {
      if ((uVar3 & 1 << (uVar21 & 0x1f)) != 0) {
        uVar12 = func_00207D80(*puVar17);
        bVar15 = bVar1 & 2;
        if (((bVar1 & 1) != 0) && (lVar14 = func_001FF290(puVar17,uVar9), lVar14 == 1)) {
          bVar15 = bVar15 | 1;
        }
        if (bVar15 == 0) {
          pfVar19 = pfVar19 + uVar12 * 8;
        }
        else {
          uVar18 = 0;
          if (uVar12 != 0) {
            do {
              piVar20 = (int *)PS2_PTR(param_1);
              pfVar4 = (float *)PS2_PTR(*piVar20);
              bVar16 = false;
              bVar6 = false;
              bVar5 = false;
              if ((*pfVar4 < pfVar19[4] + 0.1f) && (pfVar4[2] < pfVar19[6] + 0.1f)) {
                bVar5 = true;
              }
              if ((bVar5) && (*pfVar19 - 0.1f < *pfVar4)) {
                bVar6 = true;
              }
              if ((bVar6) && (pfVar19[2] - 0.1f < pfVar4[2])) {
                bVar16 = true;
              }
              if (bVar16) {
                iVar13 = func_00207DA0(*puVar17);
                if (*(char *)(iVar13 + uVar18) == '\x04') {
                  fVar22 = pfVar19[1];
                  if (fVar22 < (float)piVar20[4]) {
                    if ((bVar15 & 1) != 0) {
                      piVar20[4] = (int)fVar22;
                      *(u8 *)(piVar20 + 6) = *(u8 *)(piVar20 + 6) & 0xfe | 1;
                      iVar8 = g_7000013C;
                      iVar7 = g_70000138;
                      iVar13 = (u8 *)PS2_PTR(g_70000134);
                      piVar20[0xc] = g_70000130;
                      piVar20[0xd] = PS2_ADDR(iVar13);
                      piVar20[0xe] = iVar7;
                      piVar20[0xf] = iVar8;
                    }
                    if ((bVar15 & 2) != 0) {
                      piVar20[5] = (int)fVar22;
                      lVar14 = 1;
                      goto LAB_00209858;
                    }
                  }
                  lVar14 = 0;
                }
                else {
                  lVar14 = func_002093E0((u8 *)PS2_PTR(param_1),pfVar19,
                                        *(char *)(puVar17 + 4) +
                                        *(char *)(iVar13 + uVar18) + *(char *)(param_2 + 0x5b) & 3,
                                        bVar15);
                }
LAB_00209858:
                if (lVar14 != 0) {
                  uVar10 = func_001FF100(*(u16 *)(param_2 + 0x54),6);
                  *(u8 *)(piVar20 + 1) = uVar10;
                }
              }
              uVar18 = uVar18 + 1;
              pfVar19 = pfVar19 + 8;
            } while (uVar18 < uVar12);
          }
        }
      }
      uVar21 = uVar21 + 1;
      puVar17 = (u16 *)func_001FF230(puVar17);
    } while (uVar21 < *(u16 *)(iVar11 + 4));
  }
  return;
}

/* 0x0020EFB0, 0x34 bytes. */
void func_0020EFB0(float param_1, float *param_2, float *param_3)
{
    float fVar1;
    float fVar2;
    float fVar3;

  
  fVar1 = param_3[1];
  fVar2 = param_3[2];
  fVar3 = param_3[3];
  *param_2 = *param_3;
  param_2[1] = fVar1;
  param_2[2] = fVar2;
  param_2[3] = fVar3;
  param_2[4] = *param_3 / param_1;
  param_2[5] = param_3[1] / param_1;
  param_2[6] = 0.0f;
  param_2[7] = 0.0f;
  param_2[8] = param_1;
  return;
}

/* 0x0020F040, 0xE8 bytes. */
void func_0020F040(float *param_1, u8 *param_2, int param_3, int param_4)
{
    float fVar2;
    u8 * iVar1;

  
  iVar1 = param_2;
  if (param_4 == 0) {
    *(float *)(iVar1 + 0x200) = *param_1 + 2048.0f;
    *(float *)(iVar1 + 0x204) = param_1[1] + 2048.0f;
  }
  else {
    *(float *)(iVar1 + 0x200) = *param_1 + 2048.0f;
    if (param_3 == 0) {
      fVar2 = (float)func_00100FD0();
      *(float *)(iVar1 + 0x204) = param_1[1] + (2048.0f - fVar2 * 0.25f);
    }
    else {
      fVar2 = (float)func_00100FD0();
      *(float *)(iVar1 + 0x204) = param_1[1] + fVar2 * 0.25f + 2048.0f;
    }
  }
  func_0017AC50(param_2);
  return;
}

/* MISSING ['0x73dc68', '0x73dc6c', '0x73def8', '0x73defc'] */

/* 0x00210ED0, 0x234 bytes. */
void func_00210ED0(int param_1, int param_2)
{
    float fVar4;
    int iVar1;
    u8 * pbVar2;
    u32 uVar3;

  
  iVar1 = (int)param_1 * 0x290;
  pbVar2 = (u8 *)PS2_PTR((iVar1 + 0x73dca3));
  if (-1 < (long long)((unsigned long long)*(u8 *)(g_0073DCA3 + iVar1) << 0x3e)) {
    *pbVar2 = *(u8 *)(g_0073DCA3 + iVar1) & 0xfe | param_2 != 0;
    if (param_2 == 0) {
      if ((long long)((unsigned long long)*pbVar2 << 0x39) < 0) {
        *(u32 *)(g_0073DC60 + iVar1) = 0x4019999a;
      }
      else if ((long long)((unsigned long long)*pbVar2 << 0x38) < 0) {
        *(u32 *)(g_0073DC60 + iVar1) = 0x41200000;
      }
      else if (((*(u32 *)(g_00669F60 + 0x0)) & 2) == 0) {
        *(u32 *)(g_0073DC60 + iVar1) = 0x3f800000;
      }
      else {
        uVar3 = func_00210E50();
        *(u32 *)(g_0073DC60 + iVar1) = uVar3;
      }
    }
    else if ((long long)((unsigned long long)*pbVar2 << 0x38) < 0) {
      *(u32 *)(g_0073DC60 + iVar1) = 0x41200000;
    }
    else {
      *(u32 *)(g_0073DC60 + iVar1) = 0x40733333;
    }
    *(float *)(g_0073DC64 + iVar1) = *(float *)(g_0073DC60 + iVar1) / 500.0f;
    if ((long long)((unsigned long long)*pbVar2 << 0x3c) < 0) {
      func_00211BF0(param_1,0);
    }
    else {
      fVar4 = *(float *)(g_0073DC68 + iVar1) * *(float *)(g_0073DC60 + iVar1) * 0.5f;
      *(float *)(g_0073DC70 + iVar1) = (496.0f - fVar4) - fVar4;
      fVar4 = *(float *)(g_0073DC6C + iVar1) * *(float *)(g_0073DC60 + iVar1) * 0.5f;
      *(float *)(g_0073DC74 + iVar1) = fVar4 + 52.0f + fVar4;
      if (param_1 == 1) {
        (*(float *)(g_0073DF04 + 0x0)) = (*(float *)(g_0073DF04 + 0x0)) + 192.0f;
      }
    }
    func_00210580(param_1,param_2,g_70000150);
    func_00210580(param_1,param_2,g_70000150 ^ 1);
    *pbVar2 = *pbVar2 & 0xdf | 0x20;
  }
  return;
}
/* MISSING ['0x73df04'] */

/* 0x00211110, 0x5DC bytes. */
void func_00211110(int param_1, int param_2)
{
    int iVar1;
    int iVar4;
    long long lVar3;
    u32 uVar2;
    u32 uVar5;
    u32 uVar6;

  
  param_1 = param_1 * 0x290;
  if ((*(u32 *)(g_00669DB8 + 0x0)) == 2) {
    uVar2 = *(u32 *)PS2_PTR((((*(u32 *)(g_00669F98 + 0x0)) % 5) * 4 + 0x669dd4));
  }
  else {
    uVar2 = (*(u32 *)(g_00669DB8 + 0x1C));
  }
  lVar3 = func_00194260(3,uVar2);
  if (lVar3 != 0) {
    if (*(char *)(g_0073DCA1 + param_1) == '\x01') {
      (*(u8 *)(g_0073DC98 + 0x2)) = (*(u8 *)(g_0073DC98 + 0x2)) | 0x80;
      (*(u8 *)(g_0073DF28 + 0x2)) = (*(u8 *)(g_0073DF28 + 0x2)) | 0x80;
    }
    else {
      (*(u8 *)(g_0073DC98 + 0x2)) = (*(u8 *)(g_0073DC98 + 0x2)) & 0x7f;
      (*(u8 *)(g_0073DF28 + 0x2)) = (*(u8 *)(g_0073DF28 + 0x2)) & 0x7f;
    }
    if (*(char *)(g_0073DCA1 + param_1) == '\x02') {
      (*(u8 *)(g_0073DC98 + 0x3)) = (*(u8 *)(g_0073DC98 + 0x3)) | 1;
      (*(u8 *)(g_0073DF28 + 0x3)) = (*(u8 *)(g_0073DF28 + 0x3)) | 1;
    }
    else {
      (*(u8 *)(g_0073DC98 + 0x3)) = (*(u8 *)(g_0073DC98 + 0x3)) & 0xfe;
      (*(u8 *)(g_0073DF28 + 0x3)) = (*(u8 *)(g_0073DF28 + 0x3)) & 0xfe;
    }
  }
  lVar3 = func_003623B0();
  if (lVar3 == 0x18) {
    (*(u8 *)(g_0073DC98 + 0x2)) = (*(u8 *)(g_0073DC98 + 0x2)) & 0xbf;
    (*(u8 *)(g_0073DF28 + 0x2)) = (*(u8 *)(g_0073DF28 + 0x2)) & 0xbf;
  }
  else if ((lVar3 == 0x17) || (lVar3 == 7)) {
    (*(u8 *)(g_0073DC98 + 0x0)) = (*(u8 *)(g_0073DC98 + 0x0)) & 0xdf;
    (*(u8 *)(g_0073DF28 + 0x0)) = (*(u8 *)(g_0073DF28 + 0x0)) & 0xdf;
  }
  else if (lVar3 == 0xc) {
    (*(u8 *)(g_0073DC98 + 0x0)) = (*(u8 *)(g_0073DC98 + 0x0)) & 0xf8;
    (*(u8 *)(g_0073DF28 + 0x0)) = (*(u8 *)(g_0073DF28 + 0x0)) & 0xf8;
  }
  else if ((lVar3 == 0x13) || (lVar3 == 0xf)) {
    (*(u8 *)(g_0073DC98 + 0x1)) = (*(u8 *)(g_0073DC98 + 0x1)) & 0xfc;
    (*(u8 *)(g_0073DC98 + 0x0)) = 0;
    (*(u8 *)(g_0073DF28 + 0x1)) = (*(u8 *)(g_0073DF28 + 0x1)) & 0xfc;
    (*(u8 *)(g_0073DF28 + 0x0)) = 0;
  }
  else if ((lVar3 == 6) || (lVar3 == 3)) {
    (*(u8 *)(g_0073DC98 + 0x0)) = (*(u8 *)(g_0073DC98 + 0x0)) & 0x9f;
    (*(u8 *)(g_0073DF28 + 0x0)) = (*(u8 *)(g_0073DF28 + 0x0)) & 0x9f;
  }
  iVar1 = *(int *)PS2_PTR((param_2 * 4 + param_1 + 0x73da28));
  uVar6 = 0;
  if (*(char *)(g_0073DC9E + param_1) != '\0') {
    do {
      uVar5 = uVar6 & 7;
      iVar4 = iVar1 + ((*(u8 *)(g_0073DC9E + param_1) - uVar6) + -1) * 0x70;
      if (((int)uVar6 < 0) && (uVar5 != 0)) {
        uVar5 = uVar5 - 8;
      }
      if (((u32)*(u8 *)PS2_PTR((((int)uVar6 >> 3) + 0x73dc98)) & 1 << (uVar5 & 0x1f) & 0xffU) == 0) {
        *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x350) = 0x3f80000000000000;
      }
      else {
        if ((*(u32 *)(g_00669DB8 + 0x0)) == 2) {
          uVar2 = *(u32 *)PS2_PTR((((*(u32 *)(g_00669F98 + 0x0)) % 5) * 4 + 0x669dd4));
        }
        else {
          uVar2 = (*(u32 *)(g_00669DB8 + 0x1C));
        }
        lVar3 = func_00194260(3,uVar2);
        if ((lVar3 == 0) || (1 < uVar6 - 0x17)) {
          *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x350) = 0x3f80000080808080;
        }
        else {
          *(unsigned long long *)((u8 *)PS2_PTR(iVar4) + 0x350) = 0x3f80000002000000;
        }
      }
      uVar6 = uVar6 + 1;
    } while ((int)uVar6 < (int)(u32)*(u8 *)(g_0073DC9E + param_1));
  }
  return;
}

/* MISSING ['0x73df04'] */

/* MISSING ['0x45d488'] */

/* MISSING ['0x45cda8', '0x73f350', '0x73f354', '0x73f358', '0x73f35c'] */

/* MISSING ['0x45d2c0'] */

/* 0x00228180, 0x28 bytes. */
void func_00228180(void)
{
  func_001037F0(0);
  (*(u32 *)(g_0045D494 + 0x0)) = 0;
  (*(u32 *)(g_0045D494 + 0x4)) = 0;
  (*(u32 *)(g_0045D494 + 0x8)) = 0;
  return;
}
/* MISSING ['0x45d494', '0x45d498', '0x45d49c'] */

/* MISSING ['0x45d1f0'] */

/* MISSING ['0x45cdb8', '0x45d4a0'] */

/* 0x0022D6E0, 0x2C bytes. */
int func_0022D6E0(u8 *param_1, int param_2)
{
  if (-1 >= param_2) {
    func_0022D590(*(u32 *)(param_1 + 8));
  }
  return -1 < param_2;
}

/* 0x0022D710, 0x2C bytes. */
int func_0022D710(u8 *param_1, int param_2)
{
  if (param_2 != 0) {
    func_0022D590(*(u32 *)(param_1 + 8));
  }
  return param_2 == 0;
}

/* MISSING ['0x40e940', '0x40e944', '0x40e948', '0x40e94c', '0x40e950', '0x40e954', '0x40e958', '0x40e95c', '0x40e960', '0x40e964'] */

/* MISSING ['0x5bc03c', '0x693703'] */

/* MISSING ['0x5bc050', '0x5bc054', '0x692da0', '0x692da4'] */

/* 0x002372A0, 0x168 bytes. */
void func_002372A0(int param_1)
{
    float fStack_4;
    long long lVar2;
    u8 * pbVar1;

  
  lVar2 = func_00238930((unsigned char *)PS2_PTR(param_1),&fStack_4);
  if (lVar2 != 0) {
    pbVar1 = (u8 *)func_001F14E0((unsigned char *)PS2_PTR(param_1));
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    if ((g_7000015C >> 0x10) % 100 < (u32)(int)((float)*pbVar1 * fStack_4)) {
      func_0027C210(param_1,0);
    }
    else {
      g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
      if ((g_7000015C >> 0x10) % 100 < (u32)(int)((float)pbVar1[1] * fStack_4)) {
        func_0027C1D0((unsigned char *)PS2_PTR(param_1));
      }
      else {
        lVar2 = func_00238F50((unsigned char *)PS2_PTR(param_1));
        if (lVar2 == 0) {
          g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
          if ((g_7000015C >> 0x10) % 100 < (u32)pbVar1[3]) {
            func_0027C030(param_1);
          }
          else {
            func_00206080((u8 *)PS2_PTR(param_1));
          }
        }
      }
    }
  }
  return;
}

/* 0x00239F50, 0x16C bytes. */
void func_00239F50(int param_1)
{
    float fStack_4;
    long long lVar2;
    u8 * pbVar1;

  
  lVar2 = func_00238930((unsigned char *)PS2_PTR(param_1),&fStack_4);
  if (lVar2 != 0) {
    pbVar1 = (u8 *)func_001F14E0((unsigned char *)PS2_PTR(param_1));
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    if ((g_7000015C >> 0x10) % 100 < (u32)(int)((float)*pbVar1 * fStack_4)) {
      func_0027CA60((unsigned char *)PS2_PTR(param_1),0);
    }
    else {
      g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
      if ((g_7000015C >> 0x10) % 100 < (u32)(int)((float)pbVar1[1] * fStack_4)) {
        func_0027CA60((unsigned char *)PS2_PTR(param_1),1);
      }
      else {
        lVar2 = func_00238F50((unsigned char *)PS2_PTR(param_1));
        if (lVar2 == 0) {
          g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
          if ((g_7000015C >> 0x10) % 100 < (u32)pbVar1[3]) {
            func_0027C9C0((unsigned char *)PS2_PTR(param_1));
          }
          else {
            func_00206080((u8 *)PS2_PTR(param_1));
          }
        }
      }
    }
  }
  return;
}

/* 0x002409B0, 0xB0 bytes. */
void func_002409B0(u8 *param_1)
{
  if (*(int *)(param_1 + 0x11c) != 0) {
    if (1.0f <= g_0045D4D0) {
      g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
      if ((g_7000015C >> 0x10) % 100 < 0x28) {
        g_70000D60 = 0;
        func_001C8780(0x20,PS2_ADDR(param_1),0x14,0x10200);
      }
      g_0045D4D0 = 0.0f;
    }
    g_0045D4D0 = g_0045D4D0 + 0.099999994f;
  }
  return;
}

/* MISSING ['0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c'] */

/* MISSING ['0x410ac0', '0x410ac4', '0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x5b4fc0', '0x5b4fc4', '0x5b4fc8', '0x5b4fd0', '0x5b4fd4', '0x5b4fd8', '0x5b5020', '0x5b5024', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c', '0x76ec80', '0x76ec84', '0x76ec88', '0x76ec8c', '0x76ec90', '0x76ec94', '0x76ec98', '0x76ec9c'] */

/* MISSING ['0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c'] */

/* MISSING ['0x410ac0', '0x410ac4', '0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x5b4fc0', '0x5b4fc4', '0x5b4fc8', '0x5b4fd0', '0x5b4fd4', '0x5b4fd8', '0x5b5020', '0x5b5024', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c', '0x76ec80', '0x76ec84', '0x76ec88', '0x76ec8c', '0x76ec90', '0x76ec94', '0x76ec98', '0x76ec9c'] */

/* 0x0025BE80, 0x2D8 bytes. */
void func_0025BE80(u8 *param_1, int param_2, int param_3, int param_4)
{
    float fVar2;
    int iVar1;

  
  if (param_2 == 0) {
    if (param_3 == 0) {
      if (param_4 == 0) {
        *(unsigned long long *)(param_1 + 0x20) = 0x3f80000080404f26;
      }
      else {
        iVar1 = func_001020C0();
        fVar2 = ((float)(u32)(iVar1 % 0x32) / 50.0f) * 2.0f;
        if (1.0f <= fVar2) {
          fVar2 = 2.0f - fVar2;
        }
        *(unsigned long long *)(param_1 + 0x20) =
             (long long)(int)(fVar2 * 39.0f + 64.0f) << 0x10 |
             (long long)(int)(fVar2 * 2.0f + 38.0f) | (long long)(int)(fVar2 * 35.0f + 79.0f) << 8 |
             0x3f80000080000000;
      }
    }
    else {
      *(unsigned long long *)(param_1 + 0x20) = 0x3f800000801e5069;
    }
  }
  else {
    iVar1 = func_001020C0();
    fVar2 = ((float)(u32)(iVar1 % 0x19) / 25.0f) * 2.0f;
    if (1.0f <= fVar2) {
      fVar2 = 2.0f - fVar2;
    }
    *(unsigned long long *)(param_1 + 0x20) =
         (long long)(int)(fVar2 * 22.0f + 39.0f) << 0x10 |
         (long long)(int)(fVar2 * 32.0f + 96.0f) | (long long)(int)(fVar2 * 34.0f + 37.0f) << 8 |
         0x3f80000080000000;
  }
  return;
}

/* 0x0025C750, 0xF8 bytes. */
void func_0025C750(u8 *param_1)
{
    float fVar3;
    int iVar1;
    unsigned long long uVar2;

  
  iVar1 = func_001020C0();
  fVar3 = (float)(u32)(iVar1 % 100) / 50.0f;
  if (1.0f <= fVar3) {
    fVar3 = 2.0f - fVar3;
  }
  uVar2 = (unsigned long long)(int)(fVar3 * 128.0f + 64.0f);
  *(unsigned long long *)(param_1 + 0x20) = uVar2 << 0x10 | uVar2 | uVar2 << 8 | 0x3f80000080000000;
  return;
}

/* 0x002695F0, 0xC0 bytes. */
void func_002695F0(int param_1)
{
    int iVar1;

  
  iVar1 = *(int *)PS2_PTR((param_1 * 0x48 + 0x669dec));
  param_1 = param_1 * 0x2c;
  if (*(char *)(g_0073260E + param_1) == '\x01') {
    if (*(char *)(g_0073260D + param_1) == '\0') {
      *(u32 *)(g_00732604 + param_1) = *(u32 *)(g_007325FC + param_1);
      *(int *)(g_007325FC + param_1) = iVar1 - *(int *)(g_00732608 + param_1);
      *(u8 *)(g_0073260D + param_1) = 0x10;
    }
    else {
      *(int *)(g_007325FC + param_1) = iVar1 - *(int *)(g_00732608 + param_1);
    }
  }
  else if (*(char *)(g_0073260C + param_1) == '\0') {
    *(u32 *)(g_00732600 + param_1) = *(u32 *)(g_007325F8 + param_1);
    *(int *)(g_007325F8 + param_1) = iVar1;
    *(u8 *)(g_0073260C + param_1) = 0xb;
  }
  else {
    *(int *)(g_007325F8 + param_1) = iVar1;
  }
  return;
}

/* 0x002697C0, 0xE0 bytes. */
void func_002697C0(int param_1)
{
    u8 * iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;

  
  iVar5 = 0;
  iVar1 = g_00732220;
  iVar2 = param_1 * 0x2c;
  param_1 = param_1 * 0x1380;
  *(u32 *)(g_007325EC + iVar2) = 0;
  *(u8 *)(g_00732612 + iVar2) = 5;
  *(u32 *)(g_007325F0 + iVar2) = 1;
  do {
    iVar4 = 0;
    iVar3 = 0;
    iVar2 = *(int *)(iVar1 + 0x2e0) + param_1;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x1bb50) = 0;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x1bb60) = 0;
    do {
      iVar4 = iVar4 + 1;
      iVar2 = *(int *)(iVar1 + 0x2e0) + param_1 + iVar3;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x1bba0) = 0;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x1bbb0) = 0;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x1bbc0) = 0;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x1bbd0) = 0;
      iVar2 = *(int *)(iVar1 + 0x2e0) + param_1 + iVar3;
      iVar3 = iVar3 + 0x70;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x1bdf0) = 0;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x1be00) = 0;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x1be10) = 0;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar2) + 0x1be20) = 0;
    } while (iVar4 < 5);
    iVar5 = iVar5 + 1;
    iVar1 = iVar1 + 4;
  } while (iVar5 < 2);
  return;
}

/* 0x002698A0, 0x248 bytes. */
void func_002698A0(int param_1)
{
    u8 * iVar1;
    u8 * iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    unsigned long long uVar2;

  
  iVar6 = param_1 * 0x1380;
  param_1 = param_1 * 0x2c;
  iVar3 = g_00732220;
  iVar5 = 0;
  *(u32 *)(g_007325EC + param_1) = 0;
  *(u32 *)(g_007325F4 + param_1) = 1;
  *(u32 *)(g_007325F0 + param_1) = 1;
  *(u8 *)(g_00732612 + param_1) = 5;
  do {
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x2e0) + iVar6);
    uVar2 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3efe);
    func_001057F0(iVar1 + 0x1bb20,uVar2,0);
    iVar4 = 0;
    *(unsigned long long *)(iVar1 + 0x1bb40) = 0x3f80000080808080;
    *(unsigned long long *)(iVar1 + 0x1bb48) = 0xb880008;
    iVar7 = 0;
    *(unsigned long long *)(iVar1 + 0x1bb58) = 0xe080308;
    *(unsigned long long *)(iVar1 + 0x1bb50) = 0xfffe80288d10;
    *(unsigned long long *)(iVar1 + 0x1bb60) = 0xfffe81608fa0;
    *(unsigned long long *)(iVar1 + 0x1bb50) = 0;
    *(unsigned long long *)(iVar1 + 0x1bb60) = 0;
    do {
      iVar1 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x2e0) + iVar6 + iVar7);
      uVar2 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef1);
      func_00105A30(iVar1 + 0x1bb70,uVar2,0);
      *(unsigned long long *)(iVar1 + 0x1bba0) = 0;
      *(unsigned long long *)(iVar1 + 0x1bbb0) = 0;
      *(unsigned long long *)(iVar1 + 0x1bbc0) = 0;
      *(unsigned long long *)(iVar1 + 0x1bbd0) = 0;
      iVar1 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x2e0) + iVar6 + iVar7);
      uVar2 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef1);
      func_00105A30(iVar1 + 0x1bdc0,uVar2,0);
      *(unsigned long long *)(iVar1 + 0x1bdf0) = 0;
      iVar4 = iVar4 + 1;
      *(unsigned long long *)(iVar1 + 0x1be00) = 0;
      *(unsigned long long *)(iVar1 + 0x1be10) = 0;
      iVar7 = iVar7 + 0x70;
      *(unsigned long long *)(iVar1 + 0x1be20) = 0;
    } while (iVar4 < 5);
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x2e0) + iVar6);
    func_001050B0(iVar1 + 0x1bff0);
    *(unsigned long long *)(iVar1 + 0x1c000) = 0x8000000044;
    *(unsigned long long *)(iVar1 + 0x1c008) = 0x43;
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar3 + 0x2e0) + iVar6);
    func_001050B0(iVar1 + 0x1bda0);
    *(unsigned long long *)(iVar1 + 0x1bdb0) = 0x48;
    iVar5 = iVar5 + 1;
    *(unsigned long long *)(iVar1 + 0x1bdb8) = 0x43;
    iVar3 = iVar3 + 4;
  } while (iVar5 < 2);
  return;
}

/* 0x0026FBE0, 0xA8 bytes. */
void func_0026FBE0(float param_1, float param_2, float param_3, float param_4, int param_5, int param_6)
{
  if (param_5 != 0) {
    *(float *)PS2_PTR(param_5) = (512.0f - param_1 * param_3) * 0.5f;
  }
  if (param_6 != 0) {
    if (((*(u32 *)(g_00669F60 + 0x0)) & 2) == 0) {
      *(float *)PS2_PTR(param_6) = (384.0f - param_2 * param_4) * 0.5f;
    }
    else {
      *(float *)PS2_PTR(param_6) = (192.0f - param_2 * param_4) * 0.5f;
    }
  }
  return;
}

/* 0x0026FC90, 0x264 bytes. */
void func_0026FC90(int param_1)
{
    u8 * iVar1;
    int iVar3;
    int iVar4;
    int iVar5;
    u8 * iVar6;
    int iVar7;
    unsigned long long uVar2;

  
  iVar7 = 0;
  iVar6 = g_00732220;
  iVar4 = param_1 * 0x1380;
  *(u8 *)PS2_PTR((param_1 * 0x2c + 0x732610)) = 0;
  *(u8 *)PS2_PTR((param_1 * 0x2c + 0x732611)) = 0;
  do {
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar6 + 0x2e0) + iVar4);
    func_001050B0(iVar1 + 0x1c010);
    if (((*(u32 *)(g_00669F60 + 0x0)) & 2) == 0) {
      *(unsigned long long *)(iVar1 + 0x1c020) = 0xdf000001ff0000;
      *(unsigned long long *)(iVar1 + 0x1c028) = 0x41;
    }
    else {
      if (param_1 == 0) {
        uVar2 = 0x6f000001ff0000;
      }
      else if (param_1 == 1) {
        uVar2 = 0xdf007001ff0000;
      }
      else {
        uVar2 = 0xdf000001ff0000;
      }
      *(unsigned long long *)(iVar1 + 0x1c020) = uVar2;
      *(unsigned long long *)(iVar1 + 0x1c028) = 0x41;
    }
    iVar1 = (u8 *)PS2_PTR(*(int *)(iVar6 + 0x2e0) + iVar4);
    func_001050B0(iVar1 + 0x1c260);
    iVar3 = 0;
    *(unsigned long long *)(iVar1 + 0x1c270) = 0xdf000001ff0000;
    iVar5 = 0;
    *(unsigned long long *)(iVar1 + 0x1c278) = 0x41;
    do {
      iVar1 = (u8 *)PS2_PTR(*(int *)(iVar6 + 0x2e0) + iVar4 + iVar5);
      uVar2 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3eed);
      func_00105A30(iVar1 + 0x1c030,uVar2,0);
      iVar3 = iVar3 + 1;
      *(unsigned long long *)(iVar1 + 0x1c050) = 0x3f80000080808080;
      *(unsigned long long *)(iVar1 + 0x1c058) = 0x80c88;
      *(unsigned long long *)(iVar1 + 0x1c068) = 0x80f08;
      iVar5 = iVar5 + 0x70;
      *(unsigned long long *)(iVar1 + 0x1c078) = 0x3080c88;
      *(unsigned long long *)(iVar1 + 0x1c088) = 0x3080f08;
      *(unsigned long long *)(iVar1 + 0x1c060) = 0xfffe79007000;
      *(unsigned long long *)(iVar1 + 0x1c070) = 0xfffe79007280;
      *(unsigned long long *)(iVar1 + 0x1c080) = 0xfffe7ac07000;
      *(unsigned long long *)(iVar1 + 0x1c090) = 0xfffe7ac07280;
      *(unsigned long long *)(iVar1 + 0x1c060) = 0;
      *(unsigned long long *)(iVar1 + 0x1c070) = 0;
      *(unsigned long long *)(iVar1 + 0x1c080) = 0;
      *(unsigned long long *)(iVar1 + 0x1c090) = 0;
    } while (iVar3 < 5);
    iVar7 = iVar7 + 1;
    iVar6 = iVar6 + 4;
  } while (iVar7 < 2);
  return;
}

/* 0x00274A20, 0x26C bytes. */
void func_00274A20(float *param_1, int param_2)
{
    float fVar4;
    float fVar5;
    float fVar6;
    int iVar1;
    int iVar2;
    int iVar3;

  
  iVar2 = -1;
  fVar4 = 1.0f - (float)(*(u8 *)(g_0076F3D5 + 0x0)) / 12.0f;
  if ((*(char *)(g_0076F3D5 + 0x1)) == '\x01') {
    iVar3 = (param_2 + 4) % 5;
  }
  else {
    iVar3 = param_2;
    if ((*(char *)(g_0076F3D5 + 0x1)) == '\x02') {
      iVar3 = (param_2 + 1) % 5;
    }
  }
  param_2 = param_2 * 0xc;
  iVar1 = iVar3 * 0xc;
  fVar6 = *(float *)((g_00410D10 + 0x0) + iVar1);
  fVar5 = *(float *)((g_00410D10 + 0x0) + param_2) - fVar6;
  if (g_0045CE24 < fVar5) {
    *param_1 = fVar4 * (fVar5 - g_0045CE20) + fVar6 + 0.0f;
  }
  else if (fVar5 < -g_0045CE24) {
    *param_1 = fVar4 * (g_0045CE20 + fVar5) + fVar6 + 0.0f;
  }
  else {
    *param_1 = fVar4 * fVar5 + fVar6 + 0.0f;
  }
  fVar5 = *param_1;
  if (fVar5 < 0.0f) {
    *param_1 = fVar5 + g_0045CE20;
  }
  else if (g_0045CE20 <= fVar5) {
    *param_1 = fVar5 - g_0045CE20;
  }
  param_1[2] = fVar4 * (*(float *)((g_00410D10 + 0x8) + param_2) - *(float *)((g_00410D10 + 0x8) + iVar1)) +
               *(float *)((g_00410D10 + 0x8) + iVar1) + 0.0f;
  if ((*(char *)(g_0076F3D5 + 0x1)) == '\x01') {
    iVar2 = 4;
  }
  else if ((*(char *)(g_0076F3D5 + 0x1)) == '\x02') {
    iVar2 = 0;
  }
  if (iVar2 == iVar3) {
    fVar4 = fVar4 * -g_0045CE20 + 2.0f;
    if (fVar4 < 0.0f) {
      fVar4 = fVar4 * -1.0f;
    }
    param_1[1] = (float)((int)(fVar4 - 1.0f) * (u32)(0.0f <= fVar4 - 1.0f)) *
                 *(float *)((g_00410D10 + 0x4) + param_2);
  }
  else {
    param_1[1] = fVar4 * (*(float *)((g_00410D10 + 0x4) + param_2) - *(float *)((g_00410D10 + 0x4) + iVar1)) +
                 *(float *)((g_00410D10 + 0x4) + iVar1) + 0.0f;
  }
  return;
}

/* MISSING ['0x76f790', '0x76f794', '0x76f798', '0x76f79c', '0x76f7a0', '0x76f7a4', '0x76f7a8', '0x76f7ac', '0x76f7b8'] */

/* MISSING ['0x43fe50'] */

/* 0x002856D0, 0x110 bytes. */
void func_002856D0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    u8 auStack_20[32];
    float fVar1;

  
  func_001204B0(auStack_20,PS2_PTR(0x4407c8),param_1);
  if (param_6 == 0) {
    if ((long long)param_4 < 0) {
      fVar1 = (float)(param_4 & 0xffffffff);
    }
    else {
      fVar1 = (float)(int)param_4;
    }
    func_002C4F40(fVar1,(char *)(auStack_20),param_2,param_3,param_5,0,6);
  }
  else {
    if ((long long)param_4 < 0) {
      fVar1 = (float)(param_4 & 0xffffffff);
    }
    else {
      fVar1 = (float)(int)param_4;
    }
    func_002C5020(fVar1,(char *)(auStack_20),param_2,param_3,param_5,0,6);
  }
  return;
}

/* 0x00287280, 0x28 bytes. */
void func_00287280(void)
{
  (*(u8 *)(g_00772674 + 0x0)) = 0x40;
  (*(u8 *)(g_00772674 + 0x1)) = 0x40;
  (*(u8 *)(g_00772674 + 0x2)) = 0;
  (*(u32 *)(g_00772674 + 0x4)) = 0;
  return;
}

/* 0x002874C0, 0x128 bytes. */
void func_002874C0(int param_1, int param_2, int *param_3, int *param_4)
{
    int iVar5;
    int * piVar3;
    int * piVar4;
    u32 uVar1;
    u32 uVar2;

  
  iVar5 = 2;
  piVar3 = (int *)((g_004406D0 + 0x0));
  piVar4 = param_4 + 2;
  do {
    func_002856D0(*piVar4,param_1 + *piVar3,param_2 + piVar3[1],0xe,0,1);
    iVar5 = iVar5 + 1;
    piVar3 = piVar3 + 2;
    piVar4 = piVar4 + 1;
  } while (iVar5 < 10);
  if (*param_4 != *param_3) {
    iVar5 = 0;
    piVar4 = (int *)((g_004406D0 + 0x40));
    do {
      uVar1 = param_3[2];
      uVar2 = param_4[2];
      if ((u32)param_4[2] < uVar1) {
        uVar2 = uVar1;
      }
      func_00287360(uVar2 - uVar1,0,param_1 + *piVar4,param_2 + piVar4[1],0,0xe,0xe,0x80, 0);
      iVar5 = iVar5 + 1;
      param_4 = param_4 + 1;
      param_3 = param_3 + 1;
      piVar4 = piVar4 + 2;
    } while (iVar5 < 8);
  }
  return;
}

/* MISSING ['0x4112a0', '0x4112a4', '0x4112a8', '0x4112ac', '0x4112b0', '0x4112b4', '0x4112b8', '0x4112bc', '0x4112c0'] */

/* 0x0028F860, 0x100 bytes. */
void func_0028F860(u8 *param_1)
{
    int bVar1;
    u8 * iVar2;
    int iVar3;
    u32 uVar4;

  
  iVar2 = (u8 *)PS2_PTR((*(u32 *)(g_005BA694 + 0x0)));
  if ((*(u32 *)(g_00669DB8 + 0x0)) == 2) {
    iVar3 = 0x54;
  }
  else {
    iVar3 = (*(u32 *)(g_00669DB8 + 0x8));
    if ((*(u32 *)(g_00669DB8 + 0x0)) == 3) {
      iVar3 = 0x55;
    }
  }
  uVar4 = 0;
  *(u8 *)(param_1 + 8) = 0;
  do {
    bVar1 = *(u8 *)(iVar2 + iVar3 * 100 + uVar4 + 0x3a);
    if ((bVar1 < 0x38) && ((bVar1 != 4 || ((*(char *)(g_00669FB3 + 0x0)) == '\0')))) {
      *(u8 *)(param_1 + (u32)*(u8 *)(param_1 + 8)) = bVar1;
      *(char *)(param_1 + 8) = *(char *)(param_1 + 8) + '\x01';
    }
    uVar4 = uVar4 + 1;
  } while (uVar4 < 8);
  return;
}

/* MISSING ['0x4114d8', '0x4114dc', '0x4114e0'] */

/* MISSING ['0x411820', '0x411824', '0x411828', '0x41182c', '0x411830', '0x411834', '0x411838', '0x41183c', '0x411840', '0x411844', '0x411848', '0x41184c', '0x411850', '0x411854', '0x411858', '0x41185c'] */

/* MISSING ['0x411890', '0x411894', '0x411898', '0x41189c'] */

/* MISSING ['0x411980', '0x411984', '0x411988', '0x41198c', '0x411990', '0x411994', '0x411998', '0x41199c', '0x4119a0', '0x4119a4'] */

/* MISSING ['0x411b50', '0x411b54', '0x411b58'] */

/* 0x002A7A50, 0x9C bytes. */
void func_002A7A50(void)
{
    u8 * iVar1;
    int iVar2;

  
  iVar2 = 0;
  iVar1 = g_0077C040;
  do {
    func_0014F950(iVar1);
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + 0x170;
  } while (iVar2 < 10);
  g_0045D570 = 0;
  (*(u32 *)(g_0077CEA0 + 0x0)) = 0;
  (*(u32 *)(g_0077CEA0 + 0x8)) = 0x11;
  (*(u32 *)(g_0077CEA0 + 0x4)) = 0;
  (*(u32 *)(g_0077CEA0 + 0xC)) = 0;
  (*(u32 *)(g_0077CEA0 + 0x48)) = 0x11;
  (*(u32 *)(g_0077CEA0 + 0x40)) = 0;
  (*(u32 *)(g_0077CEA0 + 0x44)) = 0;
  (*(u32 *)(g_0077CEA0 + 0x4C)) = 0;
  (*(u32 *)(g_0077CEA0 + 0x88)) = 0x11;
  (*(u32 *)(g_0077CEA0 + 0xC8)) = 0x11;
  (*(u32 *)(g_0077CEA0 + 0x80)) = 0;
  (*(u32 *)(g_0077CEA0 + 0x84)) = 0;
  (*(u32 *)(g_0077CEA0 + 0x8C)) = 0;
  (*(u32 *)(g_0077CEA0 + 0xC0)) = 0;
  (*(u32 *)(g_0077CEA0 + 0xC4)) = 0;
  (*(u32 *)(g_0077CEA0 + 0xCC)) = 0;
  return;
}

/* MISSING ['0x411eb0', '0x411eb4', '0x411eb8', '0x411ebc'] */

/* MISSING ['0x411ec0', '0x411ec4', '0x411ec8', '0x411ecc', '0x45cec7'] */

/* MISSING ['0x411ed0', '0x411ed4', '0x411ed8', '0x411edc', '0x411ee0', '0x411ee4'] */

/* MISSING ['0x411ef0', '0x411ef4', '0x411ef8', '0x411efc', '0x411f00', '0x411f04'] */

/* 0x002B6000, 0x11C bytes. */
void func_002B6000(u8 *param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10)
{
    int aiStack_10[4];
    u8 * iVar1;
    int iVar4;
    int * piVar3;
    unsigned long long uVar2;

  
  uVar2 = (u32)(func_00104E70(param_1 + *(int *)(param_1 + 8) *
                                 *(int *)((param_2 + (u32)param_10) * 8 + param_1 + 0x10),0x1d00,
                       0x3ffc,param_9));
  iVar4 = 0;
  piVar3 = aiStack_10;
  do {
    iVar1 = func_00105860(uVar2,0);
    *piVar3 = PS2_ADDR(iVar1);
    iVar4 = iVar4 + 1;
    *(unsigned long long *)(iVar1 + 0x18) = uVar2;
    piVar3 = piVar3 + 1;
  } while (iVar4 < 3);
  func_002B5D70((unsigned char *)PS2_PTR(aiStack_10[0]),param_3,param_4,param_5,param_6,param_7,param_8);
  iVar4 = 0;
  piVar3 = aiStack_10;
  do {
    func_00105900((unsigned char *)PS2_PTR(*piVar3),param_9);
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 1;
  } while (iVar4 < 3);
  return;
}

/* 0x002B9040, 0x144 bytes. */
void func_002B9040(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9)
{
    int iVar4;
    int iVar5;
    u16 * puVar1;
    u16 * puVar2;
    u16 * puVar3;
    int sStack_2;
    int sStack_6;
    int uStack_4;
    int uStack_8;

  
  puVar2 = (u16 *)0x8;
  puVar3 = (u16 *)(&uStack_8);
  puVar1 = puVar3;
  while (puVar1 != (u16 *)0x0) {
    *(u8 *)puVar3 = 0;
    puVar3 = (u16 *)PS2_PTR(((int)PS2_ADDR(puVar3) + 1));
    puVar2 = (u16 *)PS2_PTR(((int)PS2_ADDR(puVar2) + -1));
    puVar1 = puVar2;
  }
  uStack_4 = g_0045CF2C;
  sStack_2 = g_0045CF2E + 4;
  sStack_6 = (short)param_3 + 6;
  uStack_8 = (u16)param_2;
  func_001A3C20(param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  func_002C99F0((int)param_2 + 6,(int)param_3 + 6 + (u32)param_9 * 0x18,param_4,0x98,0x18,param_7,
               param_8);
  iVar4 = (int)param_3 + 6;
  iVar5 = 0;
  do {
    func_001ABE40((unsigned char *)PS2_PTR(param_1),iVar5 + 3,(int)param_2 + 0xe,iVar4,0,0xffffffffffffffff,0xffffffffffffffff,
                 param_7, param_8, 0);
    iVar5 = iVar5 + 1;
    iVar4 = iVar4 + 0x18;
  } while (iVar5 < 8);
  return;
}

/* MISSING ['0x795ff0', '0x795ff4', '0x795ff8', '0x795ffc'] */

/* MISSING ['0x795fc4', '0x795fc8', '0x795fcc'] */

/* MISSING ['0x795790'] */

/* 0x002CDD90, 0xB4 bytes. */
void func_002CDD90(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int aiStack_24[4];
    u32 uStack_10;
    u32 uStack_14;

  
  aiStack_24[1] = (*(u32 *)(g_004126A0 + 0x0));
  aiStack_24[2] = (*(u32 *)(g_004126A0 + 0x4));
  aiStack_24[3] = (*(u32 *)(g_004126A0 + 0x8));
  uStack_14 = (*(u32 *)(g_004126A0 + 0xC));
  uStack_10 = (*(u32 *)(g_004126A0 + 0x10));
  if (0 < param_7) {
    func_001ABEA0((unsigned char *)PS2_PTR(param_1),(int)*(short *)PS2_PTR((g_0045CF50 + 2)) + aiStack_24[(int)param_7],param_2,param_3
                 ,0,param_4,param_5,0, 0, 0x18, 0x14, 0x80, param_6, 0);
  }
  return;
}
/* MISSING ['0x4126a0', '0x4126a4', '0x4126a8', '0x4126ac', '0x4126b0'] */

/* 0x002CDE50, 0xE8 bytes. */
void func_002CDE50(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    int aiStack_44[4];
    float fStack_18;
    float fStack_1c;
    float fStack_20;
    int uStack_1;
    u32 uStack_14;
    int uStack_2;
    int uStack_3;
    u32 uStack_30;
    u32 uStack_34;
    int uStack_4;

  
  aiStack_44[1] = (*(u32 *)(g_004126C0 + 0x0));
  aiStack_44[2] = (*(u32 *)(g_004126C0 + 0x4));
  aiStack_44[3] = (*(u32 *)(g_004126C0 + 0x8));
  uStack_34 = (*(u32 *)(g_004126C0 + 0xC));
  uStack_30 = (*(u32 *)(g_004126C0 + 0x10));
  if (0 < param_8) {
    uStack_14 = 0x3f800000;
    fStack_20 = (float)param_2;
    fStack_1c = (float)param_3;
    fStack_18 = (float)param_4;
    if (param_7 == 0) {
      uStack_4 = 0x40;
    }
    else {
      uStack_4 = 0x80;
    }
    if (param_7 == 0) {
      uStack_3 = 0x40;
    }
    else {
      uStack_3 = 0x80;
    }
    if (param_7 == 0) {
      uStack_2 = 0x40;
    }
    else {
      uStack_2 = 0x80;
    }
    uStack_1 = param_6;
    func_001ABCE0(param_1,aiStack_44[(int)param_8] + 0x3e,(unsigned char *)(&fStack_20),PS2_ADDR(&uStack_4),(float *)PS2_PTR(param_5),0, param_7, param_8);
  }
  return;
}
/* MISSING ['0x4126c0', '0x4126c4', '0x4126c8', '0x4126cc', '0x4126d0'] */

/* 0x002CE030, 0x90 bytes. */
void func_002CE030(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    unsigned long long uVar1;

  
  uVar1 = func_002CDF40(param_7);
  func_001ABE40((unsigned char *)PS2_PTR(param_1),uVar1,param_2,param_3,0,param_4,param_5,0x80, param_6, 0);
  return;
}

/* 0x002D8050, 0xC bytes. Sets the word at 0x00799A9C (+0x20 of the block at 0x00799A7C). */
void func_002D8050(int v)
{
    *(int *)(g_00799A7C + 0x20) = v;
}

/* 0x002D8060, 0xF4 bytes. */
void func_002D8060(int param_1)
{
    unsigned long long uVar1;

  
  func_0022D550(0);
  func_0022D590(0);
  func_002D8050(param_1);
  if ((*(u32 *)(g_00799A7C + 0x20)) == 0) {
    (*(u32 *)(g_00799A7C + 0x0)) = 0x5d30d0;
  }
  else {
    uVar1 = PS2_ADDR(func_00102DB0(0x40,0x97000));
    (*(u32 *)(g_00799A7C + 0x0)) = (u32)uVar1;
    func_0011ED38(PS2_PTR(uVar1),0,0x97000);
    func_002D7FF0(g_00799A70);
  }
  (*(u32 *)(g_00799A7C + 0x18)) = PS2_ADDR(func_00102D30(0x400));
  (*(u32 *)(g_00799A7C + 0x4)) = 0;
  (*(u32 *)(g_00799A7C + 0x44)) = 1;
  (*(u32 *)(g_00799A7C + 0x24)) = 0;
  (*(u32 *)(g_00799A7C + 0x28)) = 0;
  (*(u32 *)(g_00799A7C + 0x2C)) = 0;
  (*(u32 *)(g_00799A7C + 0x34)) = 0;
  (*(u32 *)(g_00799A7C + 0x38)) = 0;
  (*(u32 *)(g_00799A7C + 0x64)) = 0;
  (*(u32 *)(g_00799A7C + 0x70)) = 0;
  (*(u32 *)(g_00799A7C + 0x3C)) = 0;
  (*(u32 *)(g_00799A7C + 0x40)) = 0;
  (*(u32 *)(g_00799A7C + 0x68)) = 0;
  (*(u32 *)(g_00799A7C + 0x4C)) = 0;
  func_00104030();
  (*(u32 *)(g_0045D5EC + 0x0)) = 0;
  (*(u32 *)(g_00799A7C + 0x48)) = func_001037F0(0);
  func_002C5A60();
  return;
}
/* MISSING ['0x45d5ec'] */

/* The save manager (0x00799A70): +0x10 its step (0x14 busy, 0x16 a question answered), +0x14 /
 * +0x18 the message and its number, +0x24 the text buffer, +0x28 the slot's kind, +0x40 a request
 * is waiting, +0x44 the answer, +0x6C, +0x70 the phase of the start-up check (0-4), +0x78 the mode
 * (0 load, 1 save, 5 none), +0x7C the function run when the message closes. */
#define SV(o) (*(int *)(g_00799A70 + (o)))
#define SV_BASE PS2_ADDR(g_00799A70)
extern u8 g_006934B3[];                  /* per mode, 0x128 bytes apart: +0 stop the check, +1 kind */

/* Shows "there is Samurai Warriors 2 data on the memory card" (two wordings) as a message. */
static void sv_found_message(void)
{
    const char *m = (const char *)PS2_PTR(*(u32 *)(*(int *)g_0045D5EC == 0 ? g_0043C1A0 : g_0043C258));

    func_001204B0((char *)PS2_PTR(SV(0x24)), (const char *)PS2_PTR(0x4426B0), m);
    func_002D82C0(SV_BASE, 1);
    SV(0x14) = 0;
    SV(0x10) = 0x14;
    SV(0x44) = 0;
    SV(0x18) = 0x3B9;
    SV(0x7C) = PS2_CODE(func_002D7EE0);
}

/* 0x002DAEE0, 0x4D4 bytes. One step of the save manager; non-zero when it is done (and the
 * caller may go on). Runs the start-up check of the memory card in phases (+0x70): 0, 1, 2 look
 * for the game's data, 3 the other kind, 4 done. */
int func_002DAEE0(void)
{
    int done = 0, stop, r;

    SV(0x28) = SV(0x78) == 5 ? 0 : g_006934B3[SV(0x78) * 0x128 + 1];
    if (SV(0x70) == 4) {
        if (SV(0x10) == 0x14) {
            if (SV(0x78) == 1) {
                func_002D8950(g_00799A70);
            } else {
                done = 1;
                if (SV(0x78) == 0)
                    done = func_002D8C30(SV_BASE, 0);
            }
        } else {
            done = 1;
        }
        stop = SV(0x78) != 5 && done != 0 && g_006934B3[SV(0x78) * 0x128] != 0;
        if (stop) {
            done = 0;
            SV(0x10) = 0x16;
        }
        return done;
    }
    if (SV(0x40) != 0) {
        func_002D8EE0(SV_BASE);
    } else if (SV(0x10) == 0x14) {
        if (SV(0x78) == 1) {
            func_002D8950(g_00799A70);
        } else if (SV(0x78) == 0) {
            done = func_002D8C30(SV_BASE, 0);
        } else if (SV(0x6C) == 0) {
            if (SV(0x70) == 0)
                func_002D83E0(g_00799A70, 1);
            else if (SV(0x70) == 3)
                func_002D83E0(g_00799A70, 2);
        } else if (func_0022DCD0() != 0) {
            func_002D8480(SV_BASE);
        }
    } else if (SV(0x10) == 0x16) {
        if (SV(0x70) == 0) {
            if (SV(0x44) == 0) {
                SV(0x10) = 0;
                SV(0x70) = 1;
            } else {
                SV(0x10) = 0x14;
                SV(0x40) = 1;
            }
            SV(0x44) = 0;
        } else if (SV(0x70) == 1 || SV(0x70) == 2) {
            int next = SV(0x70) + 1;

            if (SV(0x44) == 0)
                SV(0x10) = 0;
            else
                sv_found_message();
            func_002DBAA0();
            SV(0x44) = 0;
            SV(0x70) = next;
        }
    } else {
        r = func_0022DD60();
        if (r == -1 || r == 2) {
            if (SV(0x70) == 3)
                func_002DA8C0(SV_BASE);
            else
                func_002D9EE0(g_00799A70);
        }
        if (func_0022DCD0() != 0) {
            if (SV(0x70) == 3)
                func_002DA2D0(SV_BASE);
            else
                func_002D9640(g_00799A70);
        }
    }
    stop = SV(0x78) != 5 && done != 0 && g_006934B3[SV(0x78) * 0x128] != 0;
    if (stop) {
        done = 0;
        SV(0x70) = 4;
    }
    return done;
}

/* 0x002DA2C0, 0x8 bytes. Nothing (the save manager's draw step). */
void func_002DA2C0(void)
{
}

/* The message texts: two tables of string addresses (0x0043C130 and 0x0043C1E8, the second for
 * the other game data kind, g_0045D5EC), the same entry order in both. */
#define SV_TEXT(k) ((const char *)PS2_PTR(*(u32 *)PS2_PTR((*(int *)g_0045D5EC == 0 ? 0x43C130 : 0x43C1E8) + (k) * 4)))
enum {
    T_LOADED = 0, T_SAVED_DATA = 1, T_UNABLE_LOAD = 7, T_NO_SAVE = 9, T_SAVED_DATA2 = 15,
    T_NO_CARD = 16, T_NO_CARD2 = 17, T_INSERT = 23, T_NO_CARD3 = 27, T_BEGIN = 40
};
#define SV_FMT1 ((const char *)PS2_PTR(0x4426B0))   /* "%s" */
#define SV_FMT2 ((const char *)PS2_PTR(0x4427C8))   /* "%s\n%s" */
int func_002EFBB0();
int func_002D9010();
extern u8 g_0076F615[];

#define SI(o) (*(int *)(s + (o)))

/* A message with a "Begin game" answer (shown with a choice), the save manager then waits. */
static void sv_ask_begin(u8 *s, int text)
{
    func_001204B0((char *)PS2_PTR(SI(0x24)), SV_FMT2, SV_TEXT(text), SV_TEXT(T_BEGIN));
    func_002D82C0(PS2_ADDR(s), 1);
    SI(0x14) = 0x16;
    SI(0x18) = 0x3B9;
    SI(0x48) = 1;
    SI(0x4C) = 1;
}

/* A plain message. */
static void sv_say(u8 *s, int text)
{
    func_001204B0((char *)PS2_PTR(SI(0x24)), SV_FMT1, SV_TEXT(text));
    func_002D82C0(PS2_ADDR(s), 0);
}

/* A message of two texts. */
static void sv_say2(u8 *s, int a, int b)
{
    func_001204B0((char *)PS2_PTR(SI(0x24)), SV_FMT2, SV_TEXT(a), SV_TEXT(b));
    func_002D82C0(PS2_ADDR(s), 0);
}

enum { T_UNABLE_SAVE = 24, T_FREE_SPACE = 25 };    /* "You are currently unable to save. Continue?",
                                                 * "%s\nAt least %dKB of free space is required..." */
#define SV_NEED_KB 0x2A6                         /* 678 KB for a save */
char *func_001206B0(char *to, const char *from);   /* strcat */

/* Asks to go on (a message with a choice); the save manager waits for the answer. */
static void sv_wait_answer(u8 *s)
{
    func_002D82C0(PS2_ADDR(s), 1);
    SI(0x14) = 0x16;
    SI(0x18) = 0x3B9;
    SI(0x48) = 1;
    SI(0x4C) = 1;
    SI(0x70) = 4;
}

/* 0x002D94F0, 0x98 bytes. The card's data is of another kind: begin the game anyway? */
void func_002D94F0(u8 *s)
{
    func_001204B0((char *)PS2_PTR(SI(0x24)), SV_FMT2, SV_TEXT(T_SAVED_DATA2), SV_TEXT(T_BEGIN));
    sv_wait_answer(s);
}

/* 0x002D9590, 0xB0 bytes. Not enough free space: begin the game anyway? */
void func_002D9590(u8 *s)
{
    func_001204B0((char *)PS2_PTR(SI(0x24)), SV_TEXT(T_FREE_SPACE), SV_TEXT(T_NO_CARD3), SV_NEED_KB, SV_TEXT(T_BEGIN));
    sv_wait_answer(s);
}

/* Message `k` of the save manager's table (0x0043C120: "Checking the memory card...", ...); the
 * first 0x2E have a second wording for the other data kind (g_0045D5EC). */
#define SV_MSG(k) ((const char *)PS2_PTR(*(u32 *)PS2_PTR(0x43C120 + \
    ((k) + ((k) < 0x2E && *(int *)g_0045D5EC != 0 ? 0x2E : 0)) * 4)))
#define M_CARD_CHANGED 1                         /* "The memory card ... was changed" (?) */
#define M_BEGIN 0x2C                             /* "Begin game?" */

/* 0x002D8950, 0x2D4 bytes. The save manager while a message is up (+0x28 4 or 5 for an
 * answered message): checks that the card was not changed, then goes on to the step after the
 * message (+0x14), runs the message's function (+0x7C), or shows the next message (+0x18). */
void func_002D8950(u8 *s)
{
    int m;

    if (SI(0x28) != 4 && SI(0x28) != 5) {
        if (SI(0x4C) == 0 && func_002D8370() == 0 && func_0022DCA0() == 0) {
            func_001204B0((char *)PS2_PTR(SI(0x24)), SV_FMT1, SV_MSG(M_CARD_CHANGED));
            func_002D82C0(PS2_ADDR(s), 0);
        }
        return;
    }
    if (func_0022DCD0() == 0)
        return;
    if (SI(0x4C) == 0 && func_0022DD60() != -1 && func_0022DCA0() == 0) {
        func_001204B0((char *)PS2_PTR(SI(0x24)), SV_FMT1, SV_MSG(M_CARD_CHANGED));
        func_002D82C0(PS2_ADDR(s), 0);
        return;
    }
    if (SI(0x28) == 4) {
        SI(0x10) = SI(0x14);
        if (SI(0x7C) != 0)
            ((void (*)(u8 *))PS2_FUNC(SI(0x7C)))(s);
        SI(0x48) = 0;
        SI(0x4C) = 0;
    } else {
        m = SI(0x18);
        if (m < 0x3B9) {
            if (m == M_BEGIN) {
                func_001204B0((char *)PS2_PTR(SI(0x24)), SV_FMT1, SV_MSG(M_BEGIN));
                func_002D82C0(PS2_ADDR(s), 1);
                SI(0x14) = 0x16;
                SI(0x18) = 0x3B9;
                SI(0x48) = 1;
                SI(0x70) = 4;
                SI(0x4C) = 1;
            } else {
                func_001204B0((char *)PS2_PTR(SI(0x24)), SV_FMT1, SV_MSG(m));
                func_002D82C0(PS2_ADDR(s), 0);
                SI(0x4C) = 0;
            }
        } else {
            SI(0x10) = SI(0x14);
            if (SI(0x48) != 0) {
                SI(0x10) = 0;
                SI(0x70) = 0;
                SI(0x48) = 0;
                SI(0x34) = 0;
            }
            SI(0x4C) = 0;
        }
    }
    SI(0x7C) = 0;
}

/* 0x002D9640, 0x898 bytes. The load side of the start-up check, one step: reads the memory
 * card's state (func_0022DCA0) and the save's, and shows the matching message. Steps (+0x10):
 * 0 look at the card, 1 its files, 4 / 5 / 7 the load, 9 the data checked; 0x14 a message is up,
 * 0x16 done. +0x2C is the kind of check (2: the game's own), +0x58 set when the player may go on
 * without a card. */
void func_002D9640(u8 *s)
{
    int next = 0x16;
    u32 st;
    int k;

    if (func_0022DD60() != -1) {
        if (SI(0x2C) == 2) {
            if (SI(0x58) == 0) {
                if (SI(0x10) == 4) {
                    if (SI(0) == 0)
                        sv_ask_begin(s, T_SAVED_DATA);
                    else
                        sv_say(s, T_SAVED_DATA);
                    SI(0x70) = 4;
                } else if (SI(0x10) == 0) {
                    st = func_0022DCA0();
                    func_00104030();
                    *(int *)g_0045D5EC = 0;
                    if (st & 0x400000)
                        func_002D9400(s);
                    else if (st & 0x40000000)
                        func_002D94F0(s);
                    else
                        func_002D9590(s);
                } else {
                    if (SI(0) == 0)
                        sv_ask_begin(s, T_UNABLE_LOAD);
                    else
                        sv_say(s, T_UNABLE_LOAD);
                    SI(0x70) = 4;
                }
                next = 0x14;
            }
        } else {
            if (SI(0x10) == 4) {
                sv_say(s, T_SAVED_DATA);
            } else if (SI(0x10) == 0) {
                func_00104030();
                *(int *)g_0045D5EC = 0;
                st = func_0022DCA0();
                if (st & 0x400000) {
                    sv_say2(s, T_NO_CARD, T_INSERT);
                    SI(0x10) = 0x14;
                    return;
                }
                if ((st & 0x40000000) == 0) {
                    if ((st & 1) == 0)
                        sv_say2(s, T_NO_CARD3, T_INSERT);
                    else
                        sv_say(s, T_NO_CARD3);
                } else {
                    sv_say(s, T_SAVED_DATA2);
                }
            } else {
                sv_say(s, T_UNABLE_LOAD);
            }
            next = 0x14;
        }
        SI(0x10) = next;
        return;
    }
    k = SI(0x10);
    if (k == 9) {
        u8 *data = (u8 *)PS2_PTR(SI(0xC));

        if (*(short *)(data + 4) == 0x67) {
            if (func_002DAE60(data, 0) == 0) {
                if (SI(0) == 0)
                    sv_ask_begin(s, T_SAVED_DATA);
                else
                    sv_say(s, T_SAVED_DATA);
            } else {
                func_001A1AE0(data);
                sv_say(s, T_LOADED);
                func_0019F550();
                SI(0x30) = 1;
                g_0076F615[0] = func_002EFBB0() == 0;
                func_00160010(1);
            }
        } else if (SI(0) == 0) {
            sv_ask_begin(s, T_SAVED_DATA);
        } else {
            sv_say(s, T_SAVED_DATA);
        }
        SI(0x70) = 4;
        SI(0x10) = 0x14;
        return;
    }
    if (k == 7) {
        next = 9;
    } else if (k == 5) {
        next = 7;
    } else if (k == 4) {
        next = 5;
    } else if (k == 1) {
        next = func_002D9010(s);
    } else if (k != 0) {
        SI(0x10) = 0x16;
        return;
    } else {
        func_00104030();
        *(int *)g_0045D5EC = 0;
        st = func_0022DCA0();
        if ((st & 0x800000) == 0) {
            if ((st & 0x400) == 0) {
                next = 1;
            } else if (SI(0x2C) != 2) {
                sv_say(s, T_NO_SAVE);
                next = 0x14;
            }
            SI(0x10) = next;
            return;
        }
        if (SI(0x58) == 0) {
            if (SI(0x2C) == 2) {
                func_002D9310(s);
            } else {
                sv_say2(s, T_NO_CARD2, T_INSERT);
            }
        }
        if (SI(0x58) == 0) {
            next = 0x14;
        } else {
            SI(0x70) = 4;
            next = 0x16;
        }
    }
    SI(0x10) = next;
}

/* 0x002DB700, 0x4C bytes. */
void func_002DB700(void)
{
  if (((g_0045D5FC == 3) || (g_0045D5FC == 2)) || (g_0045D5FC == 1)) {
    func_003BFD80();
  }
  return;
}

/* 0x002DBAF0, 0x80 bytes. */
float func_002DBAF0(float param_1, float param_2)
{
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  return param_1 + ((param_2 - param_1) * (float)(g_7000015C >> 0x10)) / 65535.0f;
}

/* MISSING ['0x45d610'] */

/* MISSING ['0x45d610'] */

/* 0x002E6510, 0x54 bytes. */
int func_002E6510(float param_1)
{
    u32 uVar1;

  
  if ((*(u32 *)(g_007A05A0 + 0xC)) == 0) {
    uVar1 = 0;
  }
  else {
    (*(float *)(g_007A05A0 + 0x0)) = (*(float *)(g_007A05A0 + 0x0)) + param_1;
    uVar1 = 1;
    (*(float *)(g_007A05A0 + 0x4)) = (*(float *)(g_007A05A0 + 0x4)) + param_1;
    if (200.0f <= (*(float *)(g_007A05A0 + 0x0))) {
      uVar1 = 0;
    }
  }
  return uVar1;
}
/* MISSING ['0x7a05a0', '0x7a05a4'] */

/* 0x002E65D0, 0x1B8 bytes. */
void func_002E65D0(void)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;

  
  if ((*(u32 *)(g_007A05A0 + 0xC)) != 0) {
    func_002E6570();
    iVar2 = 0x158;
    iVar1 = 0x6c;
    if ((*(float *)(g_007A05A0 + 0x0)) < 12.0f) {
      iVar3 = (int)(((*(float *)(g_007A05A0 + 0x0)) * 153.6f) / 12.0f);
      iVar2 = (0x99 - iVar3 >> 1) + 0x158;
      iVar4 = (int)(((*(float *)(g_007A05A0 + 0x0)) * 44.8f) / 12.0f);
      iVar1 = (0x2c - iVar4 >> 1) + 0x6c;
    }
    else if (188.0f < (*(float *)(g_007A05A0 + 0x0))) {
      iVar3 = (int)(((200.0f - (*(float *)(g_007A05A0 + 0x0))) * 153.6f) / 12.0f);
      iVar2 = (0x99 - iVar3 >> 1) + 0x158;
      iVar4 = (int)(((200.0f - (*(float *)(g_007A05A0 + 0x0))) * 44.8f) / 12.0f);
      iVar1 = (0x2c - iVar4 >> 1) + 0x6c;
    }
    else {
      iVar3 = 0x99;
      iVar4 = 0x2c;
    }
    g_0045D470 = 2;
    func_002E6070(iVar2,iVar1,iVar3,iVar4);
    func_00191240(4);
    func_00195CE0();
    func_001F5150();
    func_0017A530();
    func_002E5F80(iVar2,iVar1,iVar3,iVar4,0xfff5);
    (*(int *)g_0045D2C0) = g_0045D620;
  }
  return;
}
/* MISSING ['0x7a05a0'] */

/* MISSING ['0x7a1c10', '0x7a1c14', '0x7a1c18', '0x7a1c1c', '0x7a1e30', '0x7a1e34'] */

/* 0x002EF280, 0x78 bytes. */
void func_002EF280(void)
{
    int bVar1;
    int uStack_1;

  
  func_003B2250();
  func_001AE550(1.0f,g_007A2034,0,(unsigned char *)(&uStack_1),0);
  bVar1 = (*(u32 *)(g_007A22B8 + 0x0)) < 0x1e;
  if (bVar1) {
    (*(u32 *)(g_007A22B8 + 0x0)) = (*(u32 *)(g_007A22B8 + 0x0)) + 1;
  }
  (*(u32 *)(g_007A22B8 + 0x4)) = (u32)bVar1;
  return;
}

/* 0x002EF7F0, 0x78 bytes. */
void func_002EF7F0(void)
{
    int bVar1;
    int uStack_1;

  
  func_00395460();
  func_001AE550(1.0f,g_007A2034,0,(unsigned char *)(&uStack_1),0);
  bVar1 = (*(u32 *)(g_007A22B8 + 0x0)) < 0x1e;
  if (bVar1) {
    (*(u32 *)(g_007A22B8 + 0x0)) = (*(u32 *)(g_007A22B8 + 0x0)) + 1;
  }
  (*(u32 *)(g_007A22B8 + 0x4)) = (u32)bVar1;
  return;
}

/* 0x002EF870, 0x78 bytes. */
void func_002EF870(void)
{
    int bVar1;
    int uStack_1;

  
  func_00397A10();
  func_001AE550(1.0f,g_007A2034,0,(unsigned char *)(&uStack_1),0);
  bVar1 = (*(u32 *)(g_007A22B8 + 0x0)) < 0x1e;
  if (bVar1) {
    (*(u32 *)(g_007A22B8 + 0x0)) = (*(u32 *)(g_007A22B8 + 0x0)) + 1;
  }
  (*(u32 *)(g_007A22B8 + 0x4)) = (u32)bVar1;
  return;
}

/* 0x002EF8F0, 0x7C bytes. */
void func_002EF8F0(void)
{
    int bVar1;
    int uStack_1;

  
  func_001AE550(1.0f,g_007A2034,0,(unsigned char *)(&uStack_1),0);
  bVar1 = (*(u32 *)(g_007A22B8 + 0x0)) < 0x18;
  if (bVar1) {
    (*(u32 *)(g_007A22B8 + 0x0)) = (*(u32 *)(g_007A22B8 + 0x0)) + 1;
  }
  (*(u32 *)(g_007A22B8 + 0x4)) = (u32)bVar1;
  func_0039F590();
  return;
}

/* 0x002EF970, 0x7C bytes. */
void func_002EF970(void)
{
    int bVar1;
    int uStack_1;

  
  func_001AE550(1.0f,g_007A2034,0,(unsigned char *)(&uStack_1),0);
  bVar1 = (*(u32 *)(g_007A22B8 + 0x0)) < 0x12;
  if (bVar1) {
    (*(u32 *)(g_007A22B8 + 0x0)) = (*(u32 *)(g_007A22B8 + 0x0)) + 1;
  }
  (*(u32 *)(g_007A22B8 + 0x4)) = (u32)bVar1;
  func_003E7C10();
  return;
}

/* 0x002EF9F0, 0x7C bytes. */
void func_002EF9F0(void)
{
    int bVar1;
    int uStack_1;

  
  func_001AE550(1.0f,g_007A2034,0,(unsigned char *)(&uStack_1),0);
  bVar1 = (*(u32 *)(g_007A22B8 + 0x0)) < 0x12;
  if (bVar1) {
    (*(u32 *)(g_007A22B8 + 0x0)) = (*(u32 *)(g_007A22B8 + 0x0)) + 1;
  }
  (*(u32 *)(g_007A22B8 + 0x4)) = (u32)bVar1;
  func_003F93B0();
  return;
}

/* 0x002F0410, 0x7C bytes. */
int func_002F0410(float *param_1)
{
    float fVar2;
    u32 uVar1;

  
  fVar2 = *param_1;
  if (fVar2 < 20000.0f) {
    uVar1 = 0;
  }
  else if (fVar2 < 40000.0f) {
    uVar1 = 1;
  }
  else if (fVar2 < 60000.0f) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* MISSING ['0x45cff0', '0x45cff4', '0x45cff8', '0x45cffc', '0x45d6ec'] */

/* MISSING ['0x45d73c'] */

/* MISSING ['0x45d730'] */

/* 0x00373A70, 0xF0 bytes. */
void func_00373A70(void)
{
    long long lVar2;
    unsigned long long uVar1;

  
  lVar2 = -1;
  switch((*(u32 *)(g_007B98A4 + 0x0))) {
  case 0:
    lVar2 = 0x21;
    break;
  case 1:
    lVar2 = 0x22;
    break;
  case 2:
    lVar2 = 0x23;
    break;
  case 3:
    lVar2 = 0x24;
    break;
  case 10:
  case 0xb:
    lVar2 = 0x1b;
    break;
  case 0xc:
    lVar2 = 0x25;
    break;
  case 0xd:
    lVar2 = 0x26;
    break;
  case 0xe:
    lVar2 = 0x27;
    break;
  case 0xf:
    lVar2 = 0x28;
    break;
  case 0x11:
    lVar2 = 0x1f;
    break;
  case 0x12:
    lVar2 = 0x20;
    break;
  case 0x13:
    lVar2 = 0x29;
    break;
  case 0x14:
    lVar2 = 0x2a;
    break;
  case 0x15:
    lVar2 = 0x2b;
    break;
  case 0x16:
    lVar2 = 0x2c;
    break;
  case 0x17:
    lVar2 = 0x2d;
    break;
  case 0x18:
    lVar2 = 0x14;
    break;
  case 0x19:
    lVar2 = 0x15;
  }
  if (-1 < lVar2) {
    uVar1 = PS2_ADDR(func_003725A0(0x20));
    func_003838B0(uVar1,1);
  }
  return;
}

/* MISSING ['0x417468', '0x41746c', '0x417470'] */

/* 0x003823B0, 0x54 bytes. */
void func_003823B0(void)
{
    u32 uStack_10;
    u32 uStack_14;
    u32 uStack_18;
    u32 uStack_1c;
    u32 uStack_20;

  
  uStack_20 = 0x168;
  uStack_1c = 0x142;
  uStack_18 = 0xb8;
  uStack_10 = 0x80;
  uStack_14 = 0;
  func_003DC090(1,&uStack_20);
  func_003DC0E0(1,2,1);
  return;
}

/* 0x00382D80, 0x2C4 bytes. */
void func_00382D80(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar1;
    int iVar2;
    int iVar3;

  
  param_7 = param_7 + -0x10;
  param_6 = param_6 + -0x10;
  func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x5e,param_2,param_3,param_4,8,8,0, 0, 8, 8, 0x80, param_5, 0);
  iVar2 = (int)param_2;
  func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x5e,iVar2 + 8,param_3,param_4,param_6,8,8, 0, 8, 8, 0x80, param_5, 0);
  iVar3 = iVar2 + 8 + param_6;
  func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x5e,iVar3,param_3,param_4,8,8,0x10, 0, 8, 8, 0x80, param_5, 0);
  iVar1 = (int)param_3;
  func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x5e,param_2,iVar1 + 8,param_4,8,param_7,0, 8, 8, 8, 0x80, param_5, 0);
  func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x5e,iVar2 + 8,iVar1 + 8,param_4,param_6,param_7, 8, 8, 8, 8, 0x80, param_5, 0);
  func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x5e,iVar3,iVar1 + 8,param_4,8,param_7,0x10, 8, 8, 8, 0x80, param_5, 0);
  param_7 = iVar1 + 8 + param_7;
  func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x5e,param_2,param_7,param_4,8,8,0, 0x10, 8, 8, 0x80, param_5, 0);
  func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x5e,iVar2 + 8,param_7,param_4,param_6,8,8, 0x10, 8, 8, 0x80, param_5, 0);
  func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x5e,iVar3,param_7,param_4,8,8, 0x10, 0x10, 8, 8, 0x80, param_5, 0);
  return;
}

/* 0x00388C70, 0x12C bytes. */
int func_00388C70(int param_1, int param_2, int param_3, int param_4)
{
    u32 uVar1;

  
  uVar1 = 0xff;
  if (param_2 == -1) {
    param_1 = param_1 & 0xff;
    do {
      param_1 = param_1 - 1 & 0xff;
      if (param_1 < (param_3 & 0xff)) goto LAB_00388d58;
    } while (*(char *)(g_007B9E5D + param_1) == '\0');
    uVar1 = param_1;
LAB_00388d58:
    if (uVar1 == 0xff) {
      uVar1 = param_4 & 0xff;
    }
  }
  else if (param_2 == 1) {
    param_1 = param_1 & 0xff;
    do {
      param_1 = param_1 + 1 & 0xff;
      if ((param_4 & 0xff) < param_1) goto LAB_00388ce8;
    } while (*(char *)(g_007B9E5D + param_1) == '\0');
    uVar1 = param_1;
LAB_00388ce8:
    if (uVar1 == 0xff) {
      uVar1 = param_3 & 0xff;
    }
  }
  else {
    uVar1 = param_1 & 0xff;
    if (*(char *)(g_007B9E5D + uVar1) == '\0') {
      uVar1 = param_3 & 0xff;
    }
  }
  return uVar1;
}

/* 0x0038F740, 0x284 bytes. */
void func_0038F740(void)
{
    float fStack_1c;
    float fStack_20;
    u8 * iVar1;
    int iVar4;
    int * piVar2;
    int sStack_10;
    int sStack_e;
    int uStack_1;
    u32 uStack_14;
    u32 uStack_18;
    int uStack_a;
    int uStack_c;
    unsigned long long uVar3;

  
  iVar1 = func_00390940();
  piVar2 = (int *)PS2_PTR(func_0038F5C0());
  iVar4 = piVar2[*piVar2 + 7];
  if (iVar4 == 0x1d) {
    iVar4 = 0xf;
  }
  else if (iVar4 == 0x1c) {
    iVar4 = 0xc;
  }
  else if (iVar4 == 0x1b) {
    iVar4 = 0xe;
  }
  else if (iVar4 == 0x1a) {
    iVar4 = 0xd;
  }
  else if (iVar4 == 0x19) {
    iVar4 = 8;
  }
  func_003A9030(0);
  func_003A7C10();
  func_003A78E0(iVar4,0x1f,1);
  func_003A7360();
  func_00375F90();
  if ((2 < *(int *)(iVar1 + 0x8e6c)) && (*(int *)(iVar1 + 0x8e6c) < 6)) {
    func_001AE550(1.0f,piVar2 + 0x2c,(short int *)(&sStack_10),(unsigned char *)(&uStack_1),0);
    uStack_18 = 0;
    uStack_14 = 0;
    fStack_20 = (float)(int)sStack_10;
    fStack_1c = (float)(int)sStack_e;
    func_001ABB90(1.0f,1.0f,(unsigned char *)PS2_PTR(*(u32 *)(iVar1 + 0x8ebc)),piVar2[2] + 0xe,&fStack_20,
                 uStack_1,3,0);
    func_001AE550(1.0f,piVar2 + 0x40,(short int *)(&sStack_10),(unsigned char *)(&uStack_1),0);
    uVar3 = func_003B23C0(piVar2[2]);
    func_001ABE40((unsigned char *)PS2_PTR(*(u32 *)(iVar1 + 0x8ebc)),uVar3,sStack_10,sStack_e,0,uStack_c,uStack_a,
                 uStack_1, 0, 0);
  }
  if ((3 < *(int *)(iVar1 + 0x8e6c)) && (*(int *)(iVar1 + 0x8e6c) < 6)) {
    func_001AE550(1.0f,piVar2 + 0x4f,(short int *)(&sStack_10),(unsigned char *)(&uStack_1),0);
    uStack_18 = 0;
    uStack_14 = 0;
    fStack_20 = (float)(int)sStack_10;
    fStack_1c = (float)(int)sStack_e;
    func_001ABB90(1.0f,1.0f,(unsigned char *)PS2_PTR(*(u32 *)(iVar1 + 0x8ebc)),piVar2[0x54] + piVar2[5],
                 &fStack_20,uStack_1,3,0);
  }
  return;
}

/* MISSING ['0x7ba7f8'] */

/* 0x00395AC0, 0x1C8 bytes. */
void func_00395AC0(void)
{
    u8 auStack_10[16];
    int iVar1;
    int iVar4;
    int iVar5;
    int iVar6;
    long long lVar2;
    unsigned long long uVar3;

  
  lVar2 = PS2_ADDR(func_00397160());
  if (lVar2 != 0) {
    iVar6 = 0;
    iVar4 = (int)(*(short *)(g_007BA850 + 0x0));
    iVar1 = (int)(*(short *)(g_007BA850 + 0x2));
    iVar5 = iVar4 + 8;
    do {
      func_001ABE40((unsigned char *)PS2_PTR(*(u32 *)PS2_PTR(((int)lVar2 + 0x14))),iVar6 + 2,iVar5,iVar1 + -0x22,0,0x10,0x18,
                   (*(u8 *)(g_007BA850 + 0xC)), 2, 0);
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0xa6;
    } while (iVar6 < 2);
    func_002C7310(iVar4 + 8,iVar1 + -0x22,0,0xb6,0x18,(*(u8 *)(g_007BA850 + 0xC)),0);
    (*(u8 *)(g_0056CCA4 + 0x24)) = (*(u8 *)(g_007BA850 + 0xC));
    (*(u8 *)(g_0056CCA4 + 0x25)) = (*(u8 *)(g_007BA850 + 0xC));
    (*(u8 *)(g_0056CCA4 + 0x26)) = (*(u8 *)(g_007BA850 + 0xC));
    (*(u8 *)(g_0056CCA4 + 0x27)) = (*(u8 *)(g_007BA850 + 0xC));
    (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41a00000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41a00000;
    uVar3 = PS2_ADDR(func_00372890());
    func_00146270((const unsigned char *)PS2_PTR(uVar3),iVar4 + 0x36,iVar1 + -0x20,1,0);
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
    func_001204B0(auStack_10,PS2_PTR(0x459b10),*(int *)PS2_PTR(((int)lVar2 + 0x24)) + 1,4);
    func_002C4F40(20.0f,(char *)(auStack_10),iVar4 + 0x6c,iVar1 + -0x20,1,0,6);
  }
  return;
}

/* 0x00398D60, 0x164 bytes. */
void func_00398D60(int param_1, int param_2, int param_3)
{
    int iVar4;
    int iVar5;
    int uVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;

  
  func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f5b);
  uVar1 = func_002C5AE0(g_00799A20);
  iVar5 = param_2 + ((g_00459B60 + 0x4))[param_3 * 2] + -4;
  iVar4 = param_1 + ((g_00459B60 + 0x0))[param_3 * 2] + -4;
  uVar2 = PS2_ADDR(func_0030D7D0());
  uVar3 = func_00397B00(iVar5);
  func_001ABE40((unsigned char *)PS2_PTR(uVar2),0x59,iVar4,uVar3,0,0xa0,0x1c,0x80, 1, 0);
  uVar2 = PS2_ADDR(func_001050F0());
  *(unsigned long long *)PS2_PTR(((int)uVar2 + 0x10)) = 0x48;
  *(unsigned long long *)PS2_PTR(((int)uVar2 + 0x18)) = 0x43;
  func_00105230((unsigned char *)PS2_PTR(uVar2),1);
  uVar2 = PS2_ADDR(func_0030D7D0());
  uVar3 = func_00397B00(iVar5);
  func_001ABE40((unsigned char *)PS2_PTR(uVar2),0x59,iVar4,uVar3,0,0xa0,0x1c,uVar1, 1, 0);
  uVar2 = PS2_ADDR(func_001050F0());
  *(unsigned long long *)PS2_PTR(((int)uVar2 + 0x10)) = 0x8000000044;
  *(unsigned long long *)PS2_PTR(((int)uVar2 + 0x18)) = 0x43;
  func_00105230((unsigned char *)PS2_PTR(uVar2),1);
  return;
}

/* 0x0039BD40, 0x74 bytes. */
void func_0039BD40(void)
{
    u8 * iVar1;
    u32 uStack_10;
    u32 uStack_14;
    u32 uStack_18;
    u32 uStack_1c;
    u32 uStack_20;

  
  iVar1 = (u8 *)(func_002FC2C0());
  iVar1 = (u8 *)PS2_PTR(*(int *)(iVar1 + 0x6ac));
  *(u32 *)(iVar1 + 8) = 0xffffffff;
  *(u16 *)(iVar1 + 0x1e) = 0;
  *(u16 *)(iVar1 + 0x1c) = 0;
  uStack_20 = 8;
  uStack_1c = 0x54;
  uStack_18 = 0x8e;
  uStack_14 = 0x16;
  uStack_10 = 0x80;
  func_003DC090(0xc,&uStack_20);
  func_003DC0E0(0xc,1,10);
  return;
}

/* 0x003A3F20, 0x8C0 bytes. */
int func_003A3F20(void)
{
    int aiStack_460[200];
    u32 auStack_140[32];
    u16 auStack_40[32];
    u16 auStack_80[32];
    u16 auStack_c0[32];
    int bVar2;
    int iVar3;
    int iVar6;
    long long lVar4;
    long long lVar5;
    int * piVar11;
    u16 * puVar10;
    u32 * puVar7;
    u16 * puVar8;
    u32 * puVar9;
    int uVar1;

  
  puVar10 = (u16 *)((g_0041BE70 + 0x0));
  puVar8 = auStack_40;
  iVar6 = 0xe;
  do {
    iVar6 = iVar6 + -1;
    uVar1 = puVar10[1];
    *puVar8 = *puVar10;
    puVar8[1] = uVar1;
    puVar10 = puVar10 + 2;
    puVar8 = puVar8 + 2;
  } while (0 < iVar6);
  puVar8 = auStack_80;
  puVar10 = (u16 *)((g_0041BE70 + 0x40));
  iVar6 = 0xe;
  do {
    iVar6 = iVar6 + -1;
    uVar1 = puVar10[1];
    *puVar8 = *puVar10;
    puVar8[1] = uVar1;
    puVar10 = puVar10 + 2;
    puVar8 = puVar8 + 2;
  } while (0 < iVar6);
  puVar8 = auStack_c0;
  puVar10 = (u16 *)((g_0041BE70 + 0x80));
  iVar6 = 0xe;
  do {
    iVar6 = iVar6 + -1;
    uVar1 = puVar10[1];
    *puVar8 = *puVar10;
    puVar8[1] = uVar1;
    puVar10 = puVar10 + 2;
    puVar8 = puVar8 + 2;
  } while (0 < iVar6);
  puVar7 = auStack_140;
  puVar9 = (u32 *)((g_0041BE70 + 0xC0));
  iVar6 = 0x1d;
  do {
    iVar6 = iVar6 + -1;
    *puVar7 = *puVar9;
    puVar9 = puVar9 + 1;
    puVar7 = puVar7 + 1;
  } while (0 < iVar6);
  iVar6 = 0;
  piVar11 = aiStack_460;
  do {
    iVar3 = func_003A1930(iVar6);
    *piVar11 = iVar3;
    iVar6 = iVar6 + 1;
    piVar11 = piVar11 + 1;
  } while (iVar6 < 200);
  iVar6 = 0;
  do {
    lVar4 = func_00327D50();
    lVar5 = func_002F4080(iVar6);
    if (lVar4 == lVar5) {
      func_003A3EC0(iVar6,1);
      func_003A3EC0(iVar6 + 0x1c,1);
    }
    uVar1 = auStack_40[iVar6];
    lVar4 = func_00329540(uVar1);
    if ((lVar4 != 0) || (lVar4 = func_003A1C60(uVar1 - 0x87), lVar4 != 0)) {
      func_003A3EC0(iVar6 + 0x38,1);
    }
    uVar1 = auStack_80[iVar6];
    lVar4 = func_00329540(uVar1);
    if ((lVar4 != 0) || (lVar4 = func_003A1C60(uVar1 - 0x87), lVar4 != 0)) {
      func_003A3EC0(iVar6 + 0x54,1);
    }
    uVar1 = auStack_c0[iVar6];
    lVar4 = func_00329540(uVar1);
    if ((lVar4 != 0) || (lVar4 = func_003A1C60(uVar1 - 0x87), lVar4 != 0)) {
      func_003A3EC0(iVar6 + 0x70,1);
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x1c);
  iVar6 = 0;
  puVar7 = auStack_140;
  do {
    lVar4 = func_0036D2E0();
    if ((lVar4 != 0) && (lVar4 = func_00328C00(*puVar7), lVar4 != 0)) {
      func_003A3EC0(iVar6 + 0x8c,1);
    }
    iVar6 = iVar6 + 1;
    puVar7 = puVar7 + 1;
  } while (iVar6 < 0x1d);
  iVar6 = 0;
  do {
    lVar4 = func_003A2910(0x1a,iVar6);
    if ((lVar4 != 0) || (lVar4 = func_003A2910(0x15,iVar6), lVar4 != 0)) {
      func_003A3EC0(0xa9,1);
    }
    lVar4 = func_003A2910(8,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xaa,1);
    }
    lVar4 = func_003A2910(1,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xab,1);
    }
    lVar4 = func_003A2910(0x11,iVar6);
    if ((lVar4 != 0) || (lVar4 = func_003A2910(0x1d,iVar6), lVar4 != 0)) {
      func_003A3EC0(0xac,1);
    }
    lVar4 = func_003A2910(0xd,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xad,1);
    }
    lVar4 = func_003A2910(0xc,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xae,1);
    }
    lVar4 = func_003A2910(4,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xaf,1);
    }
    lVar4 = func_003A2910(7,iVar6);
    if ((lVar4 != 0) || (lVar4 = func_003A2910(0x17,iVar6), lVar4 != 0)) {
      func_003A3EC0(0xb0,1);
    }
    lVar4 = func_003A2910(0x16,iVar6);
    if (((lVar4 != 0) || (lVar4 = func_003A2910(0x19,iVar6), lVar4 != 0)) ||
       (lVar4 = func_003A2910(5,iVar6), lVar4 != 0)) {
      func_003A3EC0(0xb1,1);
    }
    lVar4 = func_003A2910(0x18,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xb2,1);
    }
    lVar4 = func_003A2910(0xb,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xb3,1);
    }
    lVar4 = func_003A2910(0x14,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xb4,1);
    }
    lVar4 = func_003A2910(0x12,iVar6);
    if ((lVar4 != 0) || (lVar4 = func_003A2910(0x1c,iVar6), lVar4 != 0)) {
      func_003A3EC0(0xb5,1);
    }
    lVar4 = func_003A2910(3,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xb6,1);
    }
    lVar4 = func_003A2910(6,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xb7,1);
    }
    lVar4 = func_003A2910(10,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xb8,1);
    }
    lVar4 = func_003A2910(2,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xb9,1);
    }
    lVar4 = func_003A2910(0xf,iVar6);
    if ((lVar4 != 0) || (lVar4 = func_003A2910(0x13,iVar6), lVar4 != 0)) {
      func_003A3EC0(0xba,1);
    }
    lVar4 = func_003A2910(0x10,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xbb,1);
    }
    lVar4 = func_003A2910(0x1b,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xbc,1);
    }
    lVar4 = func_003A2910(0,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xbd,1);
    }
    lVar4 = func_003A2910(9,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xbe,1);
    }
    lVar4 = func_003A2910(0xe,iVar6);
    if (lVar4 != 0) {
      func_003A3EC0(0xbf,1);
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 2);
  bVar2 = true;
  iVar6 = 0xaa;
  do {
    lVar4 = func_003A17A0(iVar6);
    if (lVar4 == 0) {
      bVar2 = false;
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0xc0);
  if (bVar2) {
    func_003A3EC0(0xc0,1);
  }
  lVar4 = func_003A17A0(0x8c);
  if ((((lVar4 != 0) && (lVar4 = func_003A17A0(0x90), lVar4 != 0)) &&
      (lVar4 = func_003A17A0(0x94), lVar4 != 0)) && (lVar4 = func_003A17A0(0xa1), lVar4 != 0)) {
    func_003A3EC0(0xc1,1);
  }
  lVar4 = func_003A17A0(0x95);
  if (((lVar4 != 0) && (lVar4 = func_003A17A0(0x97), lVar4 != 0)) &&
     ((lVar4 = func_003A17A0(0x9a), lVar4 != 0 && (lVar4 = func_003A17A0(0x9b), lVar4 != 0)))) {
    func_003A3EC0(0xc2,1);
  }
  lVar4 = func_003A17A0(0x8e);
  if (((lVar4 != 0) && (lVar4 = func_003A17A0(0x8f), lVar4 != 0)) &&
     ((lVar4 = func_003A17A0(0x91), lVar4 != 0 && (lVar4 = func_003A17A0(0x96), lVar4 != 0)))) {
    func_003A3EC0(0xc3,1);
  }
  lVar4 = func_003A17A0(0x8c);
  if (((lVar4 != 0) && (lVar4 = func_003A17A0(0xa1), lVar4 != 0)) &&
     (lVar4 = func_003A17A0(0xa4), lVar4 != 0)) {
    func_003A3EC0(0xc4,1);
  }
  lVar4 = func_003A17A0(0x90);
  if (((lVar4 != 0) && (lVar4 = func_003A17A0(0x95), lVar4 != 0)) &&
     ((lVar4 = func_003A17A0(0xa1), lVar4 != 0 && (lVar4 = func_003A17A0(0xa4), lVar4 != 0)))) {
    func_003A3EC0(0xc5,1);
  }
  lVar4 = func_003A17A0(0x8e);
  if (((lVar4 != 0) && (lVar4 = func_003A17A0(0x91), lVar4 != 0)) &&
     ((lVar4 = func_003A17A0(0x99), lVar4 != 0 &&
      (((lVar4 = func_003A17A0(0x9c), lVar4 != 0 && (lVar4 = func_003A17A0(0x9d), lVar4 != 0)) &&
       (lVar4 = func_003A17A0(0x9e), lVar4 != 0)))))) {
    func_003A3EC0(0xc6,1);
  }
  bVar2 = true;
  iVar6 = 0;
  do {
    lVar4 = func_003A17A0(iVar6);
    if (lVar4 == 0) {
      bVar2 = false;
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 199);
  if (bVar2) {
    func_003A3EC0(199,1);
  }
  iVar6 = 0;
  piVar11 = aiStack_460;
  while (((*piVar11 != 0 || (lVar4 = func_003A1930(iVar6), lVar4 == 0)) &&
         ((*piVar11 == 0 || (lVar4 = func_003A1930(iVar6), lVar4 != 0))))) {
    iVar6 = iVar6 + 1;
    piVar11 = piVar11 + 1;
    if (199 < iVar6) {
      return 0;
    }
  }
  return 1;
}

/* 0x003AC7E0, 0x18C bytes. */
int func_003AC7E0(void)
{
    u8 * iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;

  
  iVar1 = func_0021A630();
  iVar2 = (*(u32 *)(g_00669F9C + 0x4)) / 15000;
  iVar4 = iVar2 * 100;
  if ((*(u32 *)(g_00669F9C + 0x0)) < 1) {
    iVar5 = 0;
  }
  else {
    iVar5 = (*(u32 *)(g_00669F9C + 0x0));
  }
  iVar3 = (*(u32 *)(g_00669F9C + 0x4));
  if ((iVar5 <= (*(u32 *)(g_00669F9C + 0x4))) && (iVar3 = (*(u32 *)(g_00669F9C + 0x0)), (*(u32 *)(g_00669F9C + 0x0)) < 1)) {
    iVar3 = 0;
  }
  if (iVar2 < iVar3 / 3000) {
    iVar4 = (iVar3 / 3000) * -0x32 + iVar2 * 0x96;
  }
  if (*(int *)(iVar1 + 0x1664) == 0) {
    iVar4 = 0;
  }
  if (iVar4 < 1) {
    iVar2 = 0;
  }
  else {
    iVar2 = iVar4;
  }
  if (iVar2 < 10000) {
    if (iVar4 < 1) {
      iVar4 = 0;
    }
  }
  else {
    iVar4 = 9999;
  }
  return iVar4;
}

/* 0x003AFE50, 0x120 bytes. */
float func_003AFE50(u8 *param_1)
{
    float fVar5;
    float fVar6;
    int iVar1;
    u8 * iVar4;
    long long lVar2;
    long long lVar3;

  
  iVar4 = param_1;
  iVar1 = *(int *)(iVar4 + 0x10);
  fVar6 = (float)(int)*(short *)(iVar4 + 0x8a) * *(float *)(iVar4 + 0x98);
  if (iVar1 != 0) {
    if (((*(u32 *)(iVar4 + 0xb8) & 0xc) != 0) &&
       (lVar2 = func_0036F520(*(u8 *)((u8 *)PS2_PTR(iVar1) + 0x79),0x15), lVar2 != 0)) {
      fVar6 = fVar6 * 0.5f;
    }
    lVar2 = PS2_ADDR(func_0034A740((unsigned char *)PS2_PTR(iVar1)));
    if ((lVar2 != 0) && (lVar3 = (u32)(func_0033B050((unsigned char **)PS2_PTR(lVar2))), lVar3 != 0)) {
      iVar1 = PS2_ADDR(func_00338410(((int)lVar2 + -0x6a1d58) / 0x68));
      if (*(char *)((u8 *)PS2_PTR(iVar1) + 0x27) == '\0') {
        fVar6 = fVar6 * 2.0f;
      }
    }
  }
  if ((1 < (*(u8 *)(g_00669D81 + 0x0))) && ((*(u32 *)(iVar4 + 0xb8) & 0xc) != 0)) {
    fVar5 = (float)func_003E6DF0(param_1);
    fVar6 = fVar6 * fVar5;
  }
  return fVar6;
}

/* 0x003AFF70, 0x124 bytes. */
float func_003AFF70(u8 *param_1)
{
    float fVar5;
    float fVar6;
    int iVar1;
    u8 * iVar4;
    long long lVar2;
    long long lVar3;

  
  iVar4 = param_1;
  iVar1 = *(int *)(iVar4 + 0x10);
  fVar6 = (float)(int)*(short *)(iVar4 + 0x8c) * *(float *)(iVar4 + 0x9c);
  if (iVar1 != 0) {
    if (((*(u32 *)(iVar4 + 0xb8) & 0xc) != 0) &&
       (lVar2 = func_0036F520(*(u8 *)((u8 *)PS2_PTR(iVar1) + 0x79),0x15), lVar2 != 0)) {
      fVar6 = fVar6 * 0.5f;
    }
    lVar2 = PS2_ADDR(func_0034A740((unsigned char *)PS2_PTR(iVar1)));
    if ((lVar2 != 0) && (lVar3 = (u32)(func_0033B050((unsigned char **)PS2_PTR(lVar2))), lVar3 != 0)) {
      iVar1 = PS2_ADDR(func_00338410(((int)lVar2 + -0x6a1d58) / 0x68));
      if (*(char *)((u8 *)PS2_PTR(iVar1) + 0x27) == '\x01') {
        fVar6 = fVar6 * 2.0f;
      }
    }
  }
  if ((1 < (*(u8 *)(g_00669D81 + 0x0))) && ((*(u32 *)(iVar4 + 0xb8) & 0xc) != 0)) {
    fVar5 = (float)func_003E6DF0(param_1);
    fVar6 = fVar6 * fVar5;
  }
  return fVar6;
}

/* 0x003B3A60, 0x2E4 bytes. */
void func_003B3A60(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7)
{
    int iVar2;
    int iVar3;
    int iVar4;
    unsigned long long uVar1;

  
  param_6 = param_6 + -0x20;
  param_5 = param_5 + -0x20;
  uVar1 = 2;
  if (param_7 != 0) {
    uVar1 = 1;
  }
  func_001ABEA0((unsigned char *)PS2_PTR((*(int *)g_0045D7FC)),uVar1,param_1,param_2,param_3,0x10,0x10,0, 0, 0x10, 0x10, 0x80, param_4, 0);
  iVar3 = (int)param_1;
  func_001ABEA0((unsigned char *)PS2_PTR((*(int *)g_0045D7FC)),uVar1,iVar3 + 0x10,param_2,param_3,param_5,0x10,0x10, 0, 8, 0x10, 0x80, param_4, 0);
  iVar4 = iVar3 + 0x10 + param_5;
  func_001ABEA0((unsigned char *)PS2_PTR((*(int *)g_0045D7FC)),uVar1,iVar4,param_2,param_3,0x10,0x10,0x18, 0, 0x10, 0x10, 0x80, param_4, 0);
  iVar2 = (int)param_2;
  func_001ABEA0((unsigned char *)PS2_PTR((*(int *)g_0045D7FC)),uVar1,param_1,iVar2 + 0x10,param_3,0x10,param_6,0, 0x10, 0x10, 8, 0x80, param_4, 0);
  func_001ABEA0((unsigned char *)PS2_PTR((*(int *)g_0045D7FC)),uVar1,iVar3 + 0x10,iVar2 + 0x10,param_3,param_5,param_6, 0x10, 0x10, 8, 8, 0x80, param_4, 0);
  func_001ABEA0((unsigned char *)PS2_PTR((*(int *)g_0045D7FC)),uVar1,iVar4,iVar2 + 0x10,param_3,0x10,param_6,0x18, 0x10, 0x10, 8, 0x80, param_4, 0);
  param_6 = iVar2 + 0x10 + param_6;
  func_001ABEA0((unsigned char *)PS2_PTR((*(int *)g_0045D7FC)),uVar1,param_1,param_6,param_3,0x10,0x10,0, 0x18, 0x10, 0x10, 0x80, param_4, 0);
  func_001ABEA0((unsigned char *)PS2_PTR((*(int *)g_0045D7FC)),uVar1,iVar3 + 0x10,param_6,param_3,param_5,0x10,0x10, 0x18, 8, 0x10, 0x80, param_4, 0);
  func_001ABEA0((unsigned char *)PS2_PTR((*(int *)g_0045D7FC)),uVar1,iVar4,param_6,param_3,0x10,0x10, 0x18, 0x18, 0x10, 0x10, 0x80, param_4, 0);
  return;
}

/* MISSING ['0x45d7fc'] */

/* MISSING ['0x41c160', '0x41c164', '0x41c168', '0x41c16c', '0x41c170', '0x41c174', '0x41c178', '0x41c17c'] */

/* 0x003BA520, 0x1E0 bytes. */
void func_003BA520(int param_1)
{
    u8 * iVar2;
    long long lVar3;
    short * psVar4;
    int sVar1;

  
  iVar2 = func_00329860();
  if (param_1 == 99) {
    func_003BA4A0(0,1);
  }
  else {
    if (param_1 == 0x24) {
      lVar3 = 0xb;
    }
    else if (param_1 == 0x25) {
      lVar3 = 10;
    }
    else if (param_1 == 0x33) {
      lVar3 = 9;
    }
    else if (param_1 == 0x32) {
      lVar3 = 8;
    }
    else if ((param_1 == 1) || (param_1 == 0)) {
      lVar3 = 7;
    }
    else if (((param_1 == 0x10) || (param_1 == 0xf)) || (param_1 == 0xe)) {
      lVar3 = 6;
    }
    else if (((param_1 == 5) || (param_1 == 4)) || (param_1 == 3)) {
      lVar3 = 5;
    }
    else {
      lVar3 = 4;
      if ((param_1 != 6) && (lVar3 = 3, param_1 != 0x1c)) {
        if ((param_1 == 0x19) ||
           ((((param_1 == 0x18 || (param_1 == 0x17)) || (param_1 == 0x16)) ||
            ((param_1 == 0x15 || (param_1 == 0x14)))))) {
          lVar3 = 2;
        }
        else {
          lVar3 = 1;
          if ((param_1 != 9) && (lVar3 = -1, param_1 == 7)) {
            lVar3 = 0;
          }
        }
      }
    }
    if (lVar3 != -1) {
      psVar4 = (short *)(iVar2 + (int)lVar3 * 2);
      sVar1 = *psVar4;
      if ((long long)sVar1 < 0xffff) {
        *psVar4 = sVar1 + 1;
      }
    }
  }
  return;
}

/* MISSING ['0x41c400', '0x41c404', '0x41c408', '0x41c40c'] */

/* 0x003BE750, 0x1F0 bytes. */
void func_003BE750(float *param_1)
{
    float fVar4;
    int iVar2;
    int iVar3;
    float * pfVar1;

  
  iVar2 = 0;
  do {
    iVar3 = 0;
    pfVar1 = param_1;
    do {
      if ((iVar2 == 0) && (iVar3 == 0)) {
        fVar4 = 1.0f;
      }
      else if ((iVar2 == 6) && (iVar3 == 0)) {
        fVar4 = 1.0f;
      }
      else if ((iVar2 == 0) && (iVar3 == 3)) {
        fVar4 = 1.0f;
      }
      else if ((iVar2 == 6) && (iVar3 == 3)) {
        fVar4 = 1.0f;
      }
      else if ((((iVar2 == 0) || (iVar2 == 6)) && (iVar3 != 0)) && (iVar3 != 3)) {
        fVar4 = 3.0f;
      }
      else if (((iVar2 == 0) || (iVar2 == 6)) || ((iVar3 != 0 && (iVar3 != 3)))) {
        fVar4 = 6.0f;
      }
      else {
        fVar4 = 8.0f;
      }
      fVar4 = (fVar4 * 2.2222223f) / 3.0f;
      pfVar1[0x10] = fVar4;
      pfVar1[0x11] = 1.0f / fVar4;
      *pfVar1 = (float)iVar3 * 50.399998f + -75.6f;
      pfVar1[1] = ((float)iVar2 * 75.0f + -450.0f) - 225.0f;
      pfVar1[2] = -20.0f;
      pfVar1[3] = 1.0f;
      pfVar1[4] = 0.0f;
      pfVar1[5] = 0.0f;
      pfVar1[6] = 0.0f;
      pfVar1[7] = 0.0f;
      pfVar1[8] = 0.0f;
      pfVar1[9] = 0.0f;
      pfVar1[10] = 0.0f;
      pfVar1[0xb] = 0.0f;
      pfVar1[0xc] = 0.0f;
      pfVar1[0xd] = 0.0f;
      pfVar1[0xe] = 0.0f;
      pfVar1[0xf] = 0.0f;
      if (iVar2 == 0) {
        pfVar1[0x12] = 1.4013e-45f;
      }
      else {
        pfVar1[0x12] = 0.0f;
      }
      iVar3 = iVar3 + 1;
      pfVar1 = pfVar1 + 0x14;
    } while (iVar3 < 4);
    iVar2 = iVar2 + 1;
    param_1 = param_1 + 0x50;
  } while (iVar2 < 7);
  return;
}

/* MISSING ['0x41d008', '0x41d00c', '0x41d010'] */

/* MISSING ['0x41d2e0', '0x41d2e4', '0x41d2e8', '0x41d2ec'] */

/* 0x003EFCB0, 0x368 bytes, matching. */
void func_003EFCB0(int param_1, int param_2)
{
  if (param_1 != 0) {
    func_003B58E0(0,0x4c,0,0x200,0x14,1);
    func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0x38,0x48,0,0x48,0x18,0, 0, 0x48, 0x18, 0x80, 1, 0);
    if (param_2 == 0) {
      func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0xa0,0x48,0,0x48,0x18,0, 0x18, 0x48, 0x18, 0x80, 1, 0);
      func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0xf0,0x48,0,0x48,0x18,0, 0x30, 0x48, 0x18, 0x80, 1, 0);
      func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0x12a,0x48,0,0x48,0x18,0, 0x48, 0x48, 0x18, 0x80, 1, 0);
      func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0x170,0x48,0,0x48,0x18,0, 0x60, 0x48, 0x18, 0x80, 1, 0);
      func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0x1b8,0x48,0,0x48,0x18,0, 0x78, 0x48, 0x18, 0x80, 1, 0);
    }
    else {
      func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0x94,0x48,0,0x48,0x18,0, 0x90, 0x48, 0x18, 0x80, 1, 0);
      func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0xd2,0x48,0,0x48,0x18,0, 0xa8, 0x48, 0x18, 0x80, 1, 0);
      func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0x110,0x48,0,0x48,0x18,0, 0xc0, 0x48, 0x18, 0x80, 1, 0);
      func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0x14f,0x48,0,0x48,0x18,0, 0xd8, 0x48, 0x18, 0x80, 1, 0);
      func_001ABEA0((unsigned char *)PS2_PTR(param_1),0x14b,0x19c,0x48,0,0x48,0x18,0, 0xf0, 0x48, 0x18, 0x80, 1, 0);
    }
  }
  return;
}
