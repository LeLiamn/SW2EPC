/*
 * gen22_180000.c - functions between 0x00180000 and 0x003F9680, generated from Ghidra
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
extern u8 g_00426070[0x4];
extern u8 g_00426230[0x4];
extern u8 g_00428138[0x4];
extern u8 g_004281BD[0x4];
extern u8 g_00428B78[0x5];
extern u8 g_00428B7A[0x4];
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
extern u8 g_0045D4A0[0x4];
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
extern u8 g_00669DB8[0xC];
extern u8 g_00669F60[0x40];
extern u8 g_00669F6C[0x4];
extern u8 g_00669F70[0x2C];
extern u8 g_00669F84[0x4];
extern u8 g_00669F9C[0x8];
extern u8 g_00669FA4[0x4];
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
extern u8 g_00732670[0x8];
extern u8 g_00732674[0x4];
extern u8 g_00732CB8[0x4];
extern u8 g_00732DC0[0x8];
extern u8 g_00733408[0x4];
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
extern u8 g_0073DCA0[0x4];
extern u8 g_0073DCA1[0x4];
extern u8 g_0073DCA2[0x4];
extern u8 g_0073DCA3[0x4];
extern u8 g_0073DCB0[0x10];
extern u8 g_0073DEF8[0x8];
extern u8 g_0073DF04[0x4];
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
extern u8 g_00799A80[0x70];
extern u8 g_0079FE10[0x10];
extern u8 g_007A1C10[0x18];
extern u8 g_007A1E30[0x8];
extern u8 g_007A219B[0x1];
extern u8 g_007A22B8[0x8];
extern u8 g_007A22BC[0x4];
extern u8 g_007B5E20[0x30];
extern u8 g_007B95E0[0x18];
extern u8 g_007B95E8[0x18];
extern u8 g_007B9620[0x10];
extern u8 g_007B98B0[0xD2];
extern u8 g_007B9E58[0x10];
extern u8 g_007B9E70[0xC8];
extern u8 g_007B9F30[0x10];
extern u8 g_007BA7F8[0xC];
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
extern int g_0045D4E4;   /* (small data) */
extern int g_0045D540;   /* (small data) */
extern int g_0045D544;   /* (small data) */
extern int g_0045D548;   /* (small data) */
extern int g_0045D54C;   /* (small data) */
extern int g_0045D558;   /* (small data) */
extern int g_0045D55C;   /* (small data) */
extern int g_0045D564;   /* (small data) */
extern int g_0045D5C4;   /* (small data) */
extern int g_0045D5CC;   /* (small data) */
extern int g_0045D5D0;   /* (small data) */
extern int g_0045D5D4;   /* (small data) */
extern int g_0045D5E4;   /* (small data) */
extern int g_0045D5E8;   /* (small data) */
extern int g_0045D5EC;   /* (small data) */
extern int g_0045D600;   /* (small data) */
extern int g_0045D60C;   /* (small data) */
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
float func_0020A060(int, int);
int func_0020AEA0();
int func_0020AFF0();
int func_0020B110();
int func_0020B2B0();
int func_0020B410();
int func_00210580();
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
int func_0022DD50();
int func_0022DD60();
int func_0022DD70();
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
int func_002BAE40();
int func_002BAF90();
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
int func_002D8950();
int func_002D9010();
int func_002D94F0();
int func_002D9590();
int func_002D9640();
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
int func_0034A450();
int func_0034A550();
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
void func_001EC650(u8 *param_1);
int func_001ECEA0(u8 *param_1, int param_2);
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
void func_0022D590(int param_1);
void func_0022D5D0(int param_1);
void func_0022ECD0(int param_1);
void func_0022F120(u8 *param_1, u8 *param_2, u8 *param_3, int param_4, int param_5);
void func_0022F450(int param_1, int param_2);
void func_0022F4B0(int param_1, int param_2);
void func_0022F730(int param_1);
void func_00237200(u8 *param_1);
int func_00237800(int param_1);
int func_00237D00(u8 *param_1);
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
int func_002DAEE0(void);
int func_002DC510(u8 *param_1, u32 *param_2);
void func_002DC5C0(u8 *param_1);
int func_002DCD80(int param_1, u32 *param_2);
int func_002DCE20(float param_1, u8 *param_2);
void func_002DCF00(u8 *param_1);
int func_002DF700(int param_1, int param_2);
int func_002DF770(float param_1, u8 *param_2);
void func_002E05C0(int param_1, int param_2, int param_3);
float func_002E38D0(u8 *param_1);
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
void func_00399CD0(void);
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
void func_003EEAE0(void);
void func_003EF930(int param_1);
void func_003F0CE0(int param_1, int param_2, u8 *param_3, int param_4, int param_5, int param_6, int param_7);
int func_003F1B50(int param_1);

/* MISSING ['0x574e70', '0x574e78', '0x574e7c', '0x5754a0', '0x5754a8', '0x5754ac'] */

/* 0x00182C30, 0x1F4 bytes. */
void func_00182C30(void)
{
    u8 * iVar1;
    u8 * iVar2;
    int sVar3;
    u32 uVar4;

  
  func_00118850((unsigned char *)PS2_PTR(0x6a3a30),0x6b40);
  uVar4 = 0;
  iVar2 = g_00574DE0;
  iVar1 = g_00693970;
  do {
    sVar3 = (short)uVar4;
    *(short *)(iVar2 + 0x178) = sVar3;
    *(int *)(iVar1 + 0x100d4) = PS2_ADDR(iVar2);
    *(short *)(iVar2 + 0x7a8) = sVar3 + 1;
    *(int *)(iVar1 + 0x10194) = PS2_ADDR(iVar2 + 0x630);
    *(short *)(iVar2 + 0xdd8) = sVar3 + 2;
    *(int *)(iVar1 + 0x10254) = PS2_ADDR(iVar2 + 0xc60);
    *(short *)(iVar2 + 0x1408) = sVar3 + 3;
    *(int *)(iVar1 + 0x10314) = PS2_ADDR(iVar2 + 0x1290);
    *(short *)(iVar2 + 0x1a38) = sVar3 + 4;
    *(int *)(iVar1 + 0x103d4) = PS2_ADDR(iVar2 + 0x18c0);
    *(short *)(iVar2 + 0x2068) = sVar3 + 5;
    *(int *)(iVar1 + 0x10494) = PS2_ADDR(iVar2 + 0x1ef0);
    *(short *)(iVar2 + 0x2698) = sVar3 + 6;
    *(int *)(iVar1 + 0x10554) = PS2_ADDR(iVar2 + 0x2520);
    *(short *)(iVar2 + 0x2cc8) = sVar3 + 7;
    *(int *)(iVar1 + 0x10614) = PS2_ADDR(iVar2 + 0x2b50);
    uVar4 = uVar4 + 8;
    iVar1 = iVar1 + 0x600;
    iVar2 = iVar2 + 0x3180;
  } while (uVar4 < 0x87);
  iVar1 = (u8 *)PS2_PTR(uVar4 * 0xc0);
  iVar2 = (u8 *)PS2_PTR(uVar4 * 0x630);
  *(short *)(iVar2 + 0x574f58) = (short)uVar4;
  *(short *)(iVar2 + 0x575588) = sVar3 + 9;
  *(int *)(iVar1 + 0x6a3a44) = PS2_ADDR(iVar2 + 0x574de0);
  *(short *)(iVar2 + 0x575bb8) = sVar3 + 10;
  *(int *)(iVar1 + 0x6a3b04) = PS2_ADDR(iVar2 + 0x575410);
  *(short *)(iVar2 + 0x5761e8) = sVar3 + 0xb;
  *(int *)(iVar1 + 0x6a3bc4) = PS2_ADDR(iVar2 + 0x575a40);
  *(short *)(iVar2 + 0x576818) = sVar3 + 0xc;
  *(int *)(iVar1 + 0x6a3c84) = PS2_ADDR(iVar2 + 0x576070);
  *(short *)(iVar2 + 0x576e48) = sVar3 + 0xd;
  *(int *)(iVar1 + 0x6a3d44) = PS2_ADDR(iVar2 + 0x5766a0);
  *(int *)(iVar1 + 0x6a3e04) = PS2_ADDR(iVar2 + 0x576cd0);
  *(short *)(iVar2 + 0x577478) = sVar3 + 0xe;
  *(int *)(iVar1 + 0x6a3ec4) = PS2_ADDR(iVar2 + 0x577300);
  (*(u32 *)(g_006AA578 + 0x0)) = 4;
  (*(u32 *)(g_006AA578 + 0x4)) = 0;
  func_003AFAE0();
  return;
}

/* 0x00183FF0, 0x110 bytes. */
void func_00183FF0(void)
{
    int aiStack_30[4];
    int iVar1;
    int * piVar3;
    u32 uStack_10;
    u32 uStack_14;
    u32 uStack_18;
    u32 uStack_1c;
    u32 uStack_20;
    u32 uStack_8;
    u32 uStack_c;
    u32 uVar2;

  
  uVar2 = 0x28;
  iVar1 = 0x6e0;
  aiStack_30[0] = (*(u32 *)(g_00406940 + 0x0));
  aiStack_30[1] = (*(u32 *)(g_00406940 + 0x4));
  aiStack_30[2] = (*(u32 *)(g_00406940 + 0x8));
  aiStack_30[3] = (*(u32 *)(g_00406940 + 0xC));
  uStack_20 = (*(u32 *)(g_00406940 + 0x10));
  uStack_1c = (*(u32 *)(g_00406940 + 0x14));
  uStack_18 = (*(u32 *)(g_00406940 + 0x18));
  uStack_14 = (*(u32 *)(g_00406940 + 0x1C));
  uStack_10 = (*(u32 *)(g_00406940 + 0x20));
  uStack_c = (*(u32 *)(g_00406940 + 0x24));
  uStack_8 = (*(u32 *)(g_00406940 + 0x28));
  do {
    func_00183E70((unsigned char *)PS2_PTR((*(u32 *)(g_005BA6A0 + 0x0)) + iVar1));
    uVar2 = uVar2 + 1;
    iVar1 = iVar1 + 0x2c;
  } while (uVar2 < 0x1a4);
  uVar2 = 0;
  piVar3 = aiStack_30;
  do {
    func_00183E70((unsigned char *)PS2_PTR((*(u32 *)(g_005BA6A0 + 0x0)) + *piVar3 * 0x2c));
    uVar2 = uVar2 + 1;
    piVar3 = piVar3 + 1;
  } while (uVar2 < 0xb);
  return;
}
/* MISSING ['0x406940', '0x406944', '0x406948', '0x40694c', '0x406950', '0x406954', '0x406958', '0x40695c', '0x406960', '0x406964', '0x406968'] */

/* 0x00187DA0, 0x180 bytes. */
void func_00187DA0(u16 *param_1)
{
    int iVar2;
    u8 * iVar3;
    unsigned long long uVar1;
    u32 uVar4;

  
  uVar1 = func_00185E00(*param_1,1);
  if ((uVar1 < 0x1ad) && ((u16)param_1[1] < 4)) {
    iVar3 = g_00693970;
    iVar2 = (int)uVar1 * 0x88;
    if (*(char *)(g_006939EC + iVar2) == '\0') {
      if ((*(u32 *)(g_006AA598 + 0x0)) != 0) {
        uVar4 = 0;
        if ((*(u32 *)(g_006AA598 + 0x0)) != 0) {
          do {
            if (iVar2 + 0x693970 == *(int *)(iVar3 + 0x16c10)) break;
            uVar4 = uVar4 + 1;
            iVar3 = iVar3 + 4;
          } while (uVar4 < (*(u32 *)(g_006AA598 + 0x0)));
        }
        if (uVar4 < (*(u32 *)(g_006AA598 + 0x0)) - 1) {
          iVar3 = (u8 *)PS2_PTR(uVar4 * 4 + 0x693970);
          do {
            uVar4 = uVar4 + 1;
            *(u32 *)(iVar3 + 0x16c10) = *(u32 *)(iVar3 + 0x16c14);
            iVar3 = iVar3 + 4;
          } while (uVar4 < (*(u32 *)(g_006AA598 + 0x0)) - 1);
        }
        (*(u32 *)(g_006AA598 + 0x0)) = (*(u32 *)(g_006AA598 + 0x0)) - 1;
      }
      *(u32 *)(g_006939F0 + iVar2) = *(u32 *)(g_006939F0 + iVar2) & 0xfffffdff;
      *(u8 *)(g_006939EE + iVar2) = 0;
    }
    if (param_1[1] == 0) {
      *(u32 *)(g_006939F0 + iVar2) = *(u32 *)(g_006939F0 + iVar2) | 0x200;
      *(int *)((*(u32 *)(g_006AA598 + 0x0)) * 4 + 0x6aa580) = iVar2 + 0x693970;
      (*(u32 *)(g_006AA598 + 0x0)) = (*(u32 *)(g_006AA598 + 0x0)) + 1;
      *(u8 *)(g_006939EE + iVar2) = 3;
    }
    *(char *)(g_006939EC + iVar2) = (char)param_1[1];
  }
  return;
}

/* 0x001C5230, 0x1B8 bytes. */
void func_001C5230(u8 *param_1)
{
    float fVar18;
    int iVar11;
    int iVar17;
    u8 * iVar3;
    int iVar9;
    u32 * puVar10;
    u32 * puVar12;
    u32 * puVar13;
    u32 * puVar14;
    u32 * puVar15;
    u32 * puVar16;
    u32 uVar1;
    u32 uVar2;
    u32 uVar4;
    u32 uVar5;
    u32 uVar6;
    u32 uVar7;
    u32 uVar8;

  
  iVar3 = param_1;
  uVar4 = *(u32 *)(iVar3 + 0x270);
  uVar2 = *(u32 *)(iVar3 + 0x274);
  uVar1 = *(u32 *)(iVar3 + 0x278);
  iVar11 = PS2_ADDR(iVar3 + g_70000150 * 0x130);
  iVar17 = iVar11 + 0x60;
  puVar13 = (u32 *)(iVar11 + 0xc0);
  iVar9 = PS2_ADDR(iVar3 + (g_70000150 ^ 1) * 0x130);
  uVar5 = (u32)((uVar4 & 4) != 0);
  *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x50) = uVar5;
  *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x50) = uVar5;
  uVar5 = (u32)((uVar4 & 8) != 0);
  *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x54) = uVar5;
  *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x54) = uVar5;
  uVar2 = (u32)((uVar2 & 0x400000) != 0);
  *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x58) = uVar2;
  *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x58) = uVar2;
  uVar2 = (u32)((uVar4 & 0x80000000) != 0);
  *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x5c) = uVar2;
  uVar5 = 1;
  *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x5c) = uVar2;
  fVar18 = *(float *)(iVar3 + 0x294) / 2.0f;
  *(float *)((u8 *)PS2_PTR(iVar11) + 0x90) = *(float *)(iVar3 + 0x290) / 2.0f;
  *(float *)((u8 *)PS2_PTR(iVar11) + 0x94) = fVar18;
  *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x98) = 0;
  do {
    uVar6 = *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x94);
    uVar7 = *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x98);
    uVar8 = *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x9c);
    *puVar13 = *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x90);
    puVar13[1] = uVar6;
    puVar13[2] = uVar7;
    puVar13[3] = uVar8;
    uVar5 = uVar5 + 1;
    puVar13 = puVar13 + 0xc;
  } while (uVar5 < 4);
  func_001C53F0(param_1,iVar17,uVar4);
  func_001C5C70(*(u32 *)(iVar3 + 0x2a0),(unsigned char *)PS2_PTR(iVar17),param_1,uVar1 | 0x10a);
  func_001C5D40(fVar18,(unsigned char *)PS2_PTR(iVar17),uVar4 | 2);
  puVar16 = (u32 *)(iVar11 + 0x80);
  puVar15 = (u32 *)(iVar9 + 0x80);
  puVar13 = (u32 *)(iVar11 + 0x90);
  puVar12 = (u32 *)(iVar11 + 0x70);
  puVar14 = (u32 *)(iVar9 + 0x90);
  puVar10 = (u32 *)(iVar9 + 0x70);
  uVar4 = 0;
  do {
    uVar6 = puVar13[1];
    uVar7 = puVar13[2];
    uVar8 = puVar13[3];
    *puVar14 = *puVar13;
    puVar14[1] = uVar6;
    puVar14[2] = uVar7;
    puVar14[3] = uVar8;
    uVar6 = puVar12[1];
    uVar7 = puVar12[2];
    uVar8 = puVar12[3];
    *puVar10 = *puVar12;
    puVar10[1] = uVar6;
    puVar10[2] = uVar7;
    puVar10[3] = uVar8;
    uVar4 = uVar4 + 1;
    puVar13 = puVar13 + 0xc;
    puVar14 = puVar14 + 0xc;
    puVar12 = puVar12 + 0xc;
    puVar10 = puVar10 + 0xc;
    *puVar15 = *puVar16;
    puVar16 = puVar16 + 1;
    puVar15 = puVar15 + 1;
  } while (uVar4 < 4);
  return;
}

/* MISSING ['0x730560', '0x730564', '0x730568'] */

/* MISSING ['0x730560', '0x730564', '0x730568', '0x73056c'] */

/* 0x001DCF10, 0x1E0 bytes. */
void func_001DCF10(int param_1, int param_2, int param_3)
{
    int bVar1;
    int cVar2;
    int iVar11;
    int iVar12;
    u8 * iVar6;
    int iVar8;
    long long lVar4;
    u32 * puVar9;
    unsigned long long uVar10;
    u32 uVar3;
    u8 * uVar5;
    u32 uVar7;

  
  iVar11 = (*(u32 *)(g_005BA6A0 + 0x0)) + (param_2 & 0xffff) * 0x2c;
  uVar10 = (unsigned long long)*(u8 *)((u8 *)PS2_PTR(iVar11) + 9);
  lVar4 = func_0032E7B0();
  if (lVar4 == 0) {
    lVar4 = func_0020E140();
    if ((((lVar4 != 0) || (lVar4 = func_0020E170(), lVar4 != 0)) && (0x84 < uVar10)) &&
       (uVar10 < 0x8d)) {
      uVar10 = func_0016CBD0(uVar10);
    }
  }
  else {
    bVar1 = *(u8 *)((u8 *)PS2_PTR(iVar11) + 6);
    if ((bVar1 < 0x22) || (0x26 < bVar1)) {
      uVar10 = func_0032F950(uVar10);
    }
  }
  iVar11 = PS2_ADDR(func_0016CF30(uVar10));
  iVar8 = 3;
  iVar12 = iVar11 + (param_3 & 0xff) * 8;
  iVar6 = (u8 *)PS2_PTR(iVar12 + 6);
  do {
    if (*(char *)(iVar6 + 3) != -1) break;
    iVar8 = iVar8 + -1;
    iVar6 = iVar6 + -2;
  } while (-1 < iVar8);
  if (-1 < iVar8) {
    puVar9 = (u32 *)param_1;
    *puVar9 = iVar8 + 1U;
    uVar3 = PS2_ADDR(func_0020EC50((iVar8 + 1U) * 0x10));
    func_00118850((unsigned char *)PS2_PTR(uVar3),*puVar9 << 4);
    puVar9[1] = uVar3;
    func_001DC650((unsigned int *)PS2_PTR(param_1));
    uVar7 = 0;
    if (*puVar9 != 0) {
      uVar5 = (u8 *)PS2_PTR(uVar3);
      do {
        uVar7 = uVar7 + 1;
        *(u8 *)(uVar5 + 0xe) = *(u8 *)((u8 *)PS2_PTR(iVar12) + 3);
        *(u8 *)(uVar5 + 0xd) = *(u8 *)((u8 *)PS2_PTR(iVar12) + 4);
        iVar12 = iVar12 + 2;
        uVar5 = uVar5 + 0x10;
      } while (uVar7 < *puVar9);
    }
    iVar11 = (param_3 & 0xff) + iVar11;
    cVar2 = *(char *)((u8 *)PS2_PTR(iVar11) + 0x15);
    if ((cVar2 == '\x01') || (cVar2 == '\x03')) {
      *(u8 *)((u8 *)PS2_PTR(uVar3) + 0xc) = 1;
    }
    if (*(u8 *)((u8 *)PS2_PTR(iVar11) + 0x15) - 2 < 2) {
      *(u8 *)((u8 *)PS2_PTR(uVar3) + 0x1c) = 1;
    }
  }
  return;
}

/* MISSING ['0x45d3e0'] */

/* 0x001EA230, 0x41C bytes. */
void func_001EA230(int param_1)
{
    u8 auStack_8[4];
    float fVar11;
    int iStack_4;
    int iStack_40;
    u8 * iVar1;
    int iVar10;
    int iVar2;
    int iVar4;
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    u32 uStack_20;
    int uStack_30;
    u32 uVar3;

  
  (*(u32 *)(g_0056CCB4 + 0x0)) = 6;
  uStack_20 = 0;
  if ((*(u32 *)(g_00731370 + 0x0)) != 0) {
    iStack_40 = 0;
    do {
      iVar1 = (u8 *)PS2_PTR(g_0045D404 + iStack_40);
      if ((*(u32 *)(iVar1 + 0x210) <= param_1) && (param_1 <= *(u32 *)(iVar1 + 0x214))) {
        uVar3 = *(u32 *)(iVar1 + 0x214) - param_1;
        if ((float)uVar3 <= 5.0f) {
          fVar11 = ((float)uVar3 / 5.0f) * 128.0f;
          if (2.1474836e+09f <= fVar11) {
            fVar11 = fVar11 - 2.1474836e+09f;
          }
          uStack_30 = (u8)(int)fVar11;
        }
        else {
          uVar3 = param_1 - *(u32 *)(iVar1 + 0x210);
          if ((float)uVar3 <= 5.0f) {
            fVar11 = ((float)uVar3 / 5.0f) * 128.0f;
            if (2.1474836e+09f <= fVar11) {
              fVar11 = fVar11 - 2.1474836e+09f;
            }
            uStack_30 = (u8)(int)fVar11;
          }
          else {
            uStack_30 = 0x80;
          }
        }
        iVar1 = (u8 *)PS2_PTR(*(int *)(iVar1 + 0x21c));
        iVar8 = 0;
        iVar6 = 0;
        iVar10 = 0;
        iVar5 = 0;
        iVar2 = g_0045D404;
        do {
          if (*(int *)((u8 *)PS2_PTR(iStack_40) + iVar2 + iVar6) == 0) break;
          iVar9 = *(int *)((u8 *)PS2_PTR(iStack_40) + iVar2 + iVar10 + 0x220);
          iVar7 = 0;
          if (*(char *)((u8 *)PS2_PTR(iVar2) + iVar5 + iVar8 + 0x230) != '\0') {
            iVar4 = 0;
            do {
              func_001E95F0((int *)PS2_PTR(iVar2 + iStack_40 + iVar6 + iVar4),iVar9,PS2_ADDR(iVar1),uStack_30,1);
              iVar2 = *(int *)((u8 *)PS2_PTR(iStack_40) + iVar6 + g_0045D404 + iVar4);
              if (iVar2 != 0) {
                (*(u32 *)(g_0056CCB4 + 0xC)) = 0x41a00000;
                (*(u32 *)(g_0056CCB4 + 0x10)) = 0x41a00000;
                func_00146D80((const unsigned char *)PS2_PTR(iVar2),&iStack_4,(int *)(auStack_8));
                (*(u32 *)(g_0056CCB4 + 0xC)) = 0x41800000;
                (*(u32 *)(g_0056CCB4 + 0x10)) = 0x41800000;
                iVar9 = iVar9 + iStack_4;
              }
              iVar7 = iVar7 + 1;
              iVar4 = iVar4 + 0xc;
              iVar2 = g_0045D404;
            } while (iVar7 < (int)(u32)*(u8 *)((u8 *)PS2_PTR(iVar5) + iVar8 + g_0045D404 + 0x230));
          }
          iVar8 = iVar8 + 1;
          iVar1 = iVar1 + 0x18;
          iVar6 = iVar6 + 0x108;
          iVar10 = iVar10 + 4;
          iVar5 = iVar5 + 0x238;
        } while (iVar8 < 2);
        (*(u8 *)(g_0056CCB4 + 0x14)) = 0x80;
        (*(u8 *)(g_0056CCB4 + 0x15)) = 0x80;
        (*(u8 *)(g_0056CCB4 + 0x16)) = 0x80;
        (*(u8 *)(g_0056CCB4 + 0x17)) = 0x80;
      }
      iStack_40 = iStack_40 + 0x238;
      uStack_20 = uStack_20 + 1;
    } while (uStack_20 < (*(u32 *)(g_00731370 + 0x0)));
  }
  (*(u32 *)(g_0056CCB4 + 0x0)) = 5;
  return;
}

/* 0x001EC900, 0x210 bytes. */
void func_001EC900(u8 *param_1, int param_2, int param_3)
{
    int iVar1;
    u32 uVar2;

  
  iVar1 = PS2_ADDR(param_1);
  switch(param_2) {
  case 0:
    return;
  case 1:
    uVar2 = 1;
    if (*(int *)((u8 *)PS2_PTR(iVar1) + 0x18) != 0) {
      func_001ED160(PS2_ADDR(param_1),*(int *)((u8 *)PS2_PTR(iVar1) + 0x18),0);
      *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x18) = 0;
      *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x84) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x84) | 0x10;
    }
    if (*(char *)((u8 *)PS2_PTR(iVar1) + 0x7a) != '\x03') {
      *(u8 *)((u8 *)PS2_PTR(iVar1) + 0x7a) = 0;
    }
    break;
  case 2:
    uVar2 = 2;
    break;
  case 3:
    uVar2 = 4;
    break;
  case 4:
    uVar2 = 0x400;
    break;
  case 5:
    uVar2 = 0x800;
    break;
  case 6:
    uVar2 = 0x1000;
    break;
  case 7:
    uVar2 = 0x2000;
    break;
  case 8:
    uVar2 = 0x4000;
    break;
  case 9:
    uVar2 = 0x8000;
    break;
  case 10:
    uVar2 = 0x10000;
    break;
  case 0xb:
    if (0x46 < *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x10)) {
      return;
    }
    iVar1 = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x10) * 0x68;
    if (param_3 == 0) {
      *(u32 *)(g_006A1DBC + iVar1) = *(u32 *)(g_006A1DBC + iVar1) & 0xfffffffb;
      return;
    }
    *(u32 *)(g_006A1DBC + iVar1) = *(u32 *)(g_006A1DBC + iVar1) | 4;
    return;
  case 0xc:
    uVar2 = 0x200;
    break;
  case 0xd:
    uVar2 = 8;
    break;
  case 0xe:
    if ((*(u32 *)((u8 *)PS2_PTR(iVar1) + 0x80) & 0x20000) != 0) {
      func_0015FB50((void *)PS2_PTR(*(u32 *)(*(int *)((u8 *)PS2_PTR(iVar1) + 0x14) * 0xc0 + 0x6a3a44)),0x97);
    }
    uVar2 = 0x40000;
    break;
  case 0xf:
    uVar2 = 0x80000;
    break;
  case 0x10:
    uVar2 = 0x100000;
    break;
  default:
    goto switchD_001ec93c_default;
  }
  if (param_3 == 0) {
    *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x84) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x84) & ~uVar2;
  }
  else {
    *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x84) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x84) | uVar2;
  }
  if ((*(u32 *)((u8 *)PS2_PTR(iVar1) + 0x80) & 0x400000) != 0) {
    func_001EEB70(PS2_ADDR(param_1));
  }
switchD_001ec93c_default:
  return;
}

/* MISSING ['0x40cff0', '0x40cff4', '0x40cff8', '0x40cffc', '0x40d000', '0x40d004', '0x40d008', '0x40d00c', '0x40d010', '0x40d014'] */

/* MISSING ['0x45d2c0'] */

/* 0x002098E0, 0x2B8 bytes. */
void func_002098E0(int param_1)
{
    int bVar1;
    int bVar13;
    int bVar14;
    int bVar15;
    int cVar7;
    float fVar10;
    float fVar18;
    int iVar16;
    int iVar4;
    int iVar5;
    int iVar6;
    float * pfVar12;
    float * pfVar3;
    int * piVar17;
    u32 * puVar9;
    u32 uVar11;
    u32 uVar2;
    int uVar8;

  
  func_001185B0((void *)PS2_PTR(0x700001e0),0x50);
  piVar17 = (int *)param_1;
  puVar9 = (u32 *)func_001946A0((float *)PS2_PTR(*piVar17),3);
  if (puVar9 != (u32 *)0x0) {
    fVar10 = 0.1f;
    do {
      uVar2 = *puVar9;
      uVar11 = 1 << (uVar2 & 7);
      bVar1 = (&g_700001E0)[uVar2 >> 3];
      if ((uVar11 & 0xff & (u32)bVar1) == 0) {
        (&g_700001E0)[uVar2 >> 3] = bVar1 | (u8)uVar11;
        iVar16 = g_700001D0 + uVar2 * 0x70;
        if ((*(u8 *)((u8 *)PS2_PTR(iVar16) + 100) & 3) == 0) {
          bVar13 = false;
        }
        else if ((((*(u32 *)(g_00669F60 + 0x0)) & 0x100000) == 0) ||
                (cVar7 = func_001FF100(*(u16 *)((u8 *)PS2_PTR(iVar16) + 0x54),4), cVar7 != '\x01')) {
          if ((*(u8 *)((u8 *)PS2_PTR(iVar16) + 0x69) & 4) == 0) {
            bVar13 = true;
          }
          else {
            bVar13 = false;
          }
        }
        else {
          bVar13 = false;
        }
        if (bVar13) {
          bVar1 = *(u8 *)((u8 *)PS2_PTR(iVar16) + 100);
          if ((bVar1 & 4) == 0) {
            func_002095D0(param_1,(unsigned char *)PS2_PTR(iVar16));
          }
          else {
            bVar15 = false;
            pfVar3 = (float *)*piVar17;
            bVar14 = false;
            pfVar12 = (float *)(g_700001D4 + (u32)*(u16 *)((u8 *)PS2_PTR(iVar16) + 0x56) * 0x20);
            bVar13 = false;
            if ((*pfVar3 < fVar10 + pfVar12[4]) && (pfVar3[2] < fVar10 + pfVar12[6])) {
              bVar13 = true;
            }
            if ((bVar13) && (*pfVar12 - fVar10 < *pfVar3)) {
              bVar14 = true;
            }
            if ((bVar14) && (pfVar12[2] - fVar10 < pfVar3[2])) {
              bVar15 = true;
            }
            if (bVar15) {
              fVar18 = pfVar12[1];
            }
            else {
              fVar18 = 0.0f;
            }
            if (fVar18 < (float)piVar17[4]) {
              if ((bVar1 & 1) != 0) {
                piVar17[4] = (int)fVar18;
                *(u8 *)(piVar17 + 6) = *(u8 *)(piVar17 + 6) & 0xfe | 1;
                iVar6 = g_7000013C;
                iVar5 = g_70000138;
                iVar4 = g_70000134;
                piVar17[0xc] = g_70000130;
                piVar17[0xd] = iVar4;
                piVar17[0xe] = iVar5;
                piVar17[0xf] = iVar6;
              }
              if ((bVar1 & 2) == 0) goto LAB_00209b40;
              piVar17[5] = (int)fVar18;
              bVar13 = true;
            }
            else {
LAB_00209b40:
              bVar13 = false;
            }
            if (bVar13) {
              uVar8 = func_001FF100(*(u16 *)((u8 *)PS2_PTR(iVar16) + 0x54),6);
              *(u8 *)(piVar17 + 1) = uVar8;
            }
          }
        }
      }
      puVar9 = (u32 *)puVar9[1];
    } while (puVar9 != (u32 *)0x0);
  }
  return;
}

/* 0x0020A2F0, 0x24C bytes. */
float func_0020A2F0(int param_1)
{
    int bVar1;
    int bVar3;
    int bVar4;
    int bVar5;
    int cVar6;
    float fVar12;
    float fVar13;
    int iVar10;
    float * pfVar11;
    float * pfVar9;
    u32 * puVar7;
    u32 uVar2;
    u32 uVar8;

  
  fVar13 = 0.0f;
  func_001185B0((void *)PS2_PTR(0x700001e0),0x50);
  for (puVar7 = (u32 *)func_001946A0((float *)PS2_PTR(param_1),0x40); puVar7 != (u32 *)0x0;
      puVar7 = (u32 *)puVar7[1]) {
    uVar2 = *puVar7;
    uVar8 = 1 << (uVar2 & 7);
    bVar1 = (&g_700001E0)[uVar2 >> 3];
    if ((uVar8 & 0xff & (u32)bVar1) == 0) {
      (&g_700001E0)[uVar2 >> 3] = bVar1 | (u8)uVar8;
      iVar10 = g_700001D0 + uVar2 * 0x70;
      if ((*(u8 *)((u8 *)PS2_PTR(iVar10) + 100) & 0x40) == 0) {
        bVar3 = false;
      }
      else if ((((*(u32 *)(g_00669F60 + 0x0)) & 0x100000) == 0) ||
              (cVar6 = func_001FF100(*(u16 *)((u8 *)PS2_PTR(iVar10) + 0x54),4), cVar6 != '\x01')) {
        if ((*(u8 *)((u8 *)PS2_PTR(iVar10) + 0x69) & 4) == 0) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
      }
      else {
        bVar3 = false;
      }
      if (bVar3) {
        if ((*(u8 *)((u8 *)PS2_PTR(iVar10) + 100) & 4) == 0) {
          fVar12 = (float)func_0020A060(iVar10,param_1);
          fVar13 = (float)((int)fVar13 * (u32)(fVar13 < fVar12) |
                          (int)fVar12 * (u32)(fVar13 >= fVar12));
        }
        else {
          pfVar11 = (float *)param_1;
          bVar5 = false;
          bVar4 = false;
          pfVar9 = (float *)(g_700001D4 + (u32)*(u16 *)((u8 *)PS2_PTR(iVar10) + 0x56) * 0x20);
          bVar3 = false;
          if ((*pfVar11 < pfVar9[4] + 0.1f) && (pfVar11[2] < pfVar9[6] + 0.1f)) {
            bVar3 = true;
          }
          if ((bVar3) && (*pfVar9 - 0.1f < *pfVar11)) {
            bVar4 = true;
          }
          if ((bVar4) && (pfVar9[2] - 0.1f < pfVar11[2])) {
            bVar5 = true;
          }
          if (bVar5) {
            fVar12 = pfVar9[1];
          }
          else {
            fVar12 = 0.0f;
          }
          fVar13 = (float)((int)fVar13 * (u32)(fVar13 < fVar12) |
                          (int)fVar12 * (u32)(fVar13 >= fVar12));
        }
      }
    }
  }
  return fVar13;
}

/* 0x0020FA70, 0x1C8 bytes. */
void func_0020FA70(void)
{
    u32 auStack_1d0[80];
    u8 auStack_90[144];
    int iVar4;
    u8 * iVar7;
    u32 * puVar5;
    u32 * puVar6;
    u32 uVar1;
    unsigned long long uVar2;
    unsigned long long uVar3;

  
  puVar6 = (u32 *)((g_0040D6F0 + 0x0));
  puVar5 = auStack_1d0;
  iVar4 = 0x27;
  do {
    iVar4 = iVar4 + -1;
    uVar1 = puVar6[1];
    *puVar5 = *puVar6;
    puVar5[1] = uVar1;
    puVar6 = puVar6 + 2;
    puVar5 = puVar5 + 2;
  } while (0 < iVar4);
  uVar2 = func_003623B0();
  iVar4 = func_0035D6E0(uVar2);
  uVar2 = func_0020FA20(uVar2);
  (*(u32 *)(g_0073DA10 + 0x0)) = PS2_ADDR(func_001026D0(1,uVar2,0,1,0,0,(const char *)PS2_PTR(0x429ad0),0xa1));
  (*(u32 *)(g_0073DA10 + 0x4)) = (*(u32 *)(g_0073DA10 + 0x0)) + *(int *)((*(u32 *)(g_0073DA10 + 0x0)) + 4);
  iVar7 = (u8 *)PS2_PTR((*(u32 *)(g_0073DA10 + 0x0)) + *(int *)((*(u32 *)(g_0073DA10 + 0x0)) + 8));
  (*(u32 *)(g_0073DA10 + 0xC)) = PS2_ADDR(iVar7 + *(int *)(iVar7 + 0x18) + 0x40);
  (*(u32 *)(g_0073DA10 + 0x8)) = PS2_ADDR(iVar7);
  uVar2 = func_00104A60(auStack_90,iVar7,0x1320);
  uVar3 = func_00104B90(auStack_90,iVar7,0,0x3ffc);
  (*(unsigned long long *)(g_0073DA10 + 0x10)) = func_00106C50(uVar2,uVar3);
  (*(float *)(g_0073DC68 + 0x0)) = (float)auStack_1d0[iVar4 * 2] * 10.0f;
  (*(unsigned long long *)(g_0073DC68 + 0x48)) = (*(unsigned long long *)(g_0073DA10 + 0x10));
  (*(float *)(g_0073DC68 + 0x4)) = (float)auStack_1d0[iVar4 * 2 + 1] * 10.0f;
  (*(float *)(g_0073DEF8 + 0x0)) = (float)auStack_1d0[iVar4 * 2] * 10.0f;
  (*(float *)(g_0073DEF8 + 0x4)) = (float)auStack_1d0[iVar4 * 2 + 1] * 10.0f;
  return;
}
/* MISSING ['0x73dc68', '0x73dc6c', '0x73def8', '0x73defc'] */

/* MISSING ['0x73df04'] */

/* 0x002180F0, 0xB0 bytes. */
void func_002180F0(int param_1)
{
    int iVar1;
    u8 * iVar3;
    u32 uVar2;

  
  func_00218670(param_1,(*(u32 *)(g_0045D488 + 0x0)),3);
  iVar3 = (u8 *)PS2_PTR((int)param_1 * 4);
  *(u32 *)(iVar3 + 0x73e160) = 0x3f800000;
  *(u32 *)(iVar3 + 0x73e0e0) = 0;
  *(u32 *)(iVar3 + 0x7404b0) = 0;
  uVar2 = 0;
  iVar3 = g_0073E030;
  *(u8 *)(g_0073E020 + param_1) = 0;
  do {
    iVar1 = *(int *)(iVar3 + 0x28);
    if (iVar1 != 0) {
      *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) | 8;
      *(u32 *)(iVar3 + 0x28) = 0;
    }
    uVar2 = uVar2 + 1;
    iVar3 = iVar3 + 0x2c;
  } while (uVar2 < 2);
  return;
}
/* MISSING ['0x45d488'] */

/* MISSING ['0x45cda8', '0x73f350', '0x73f354', '0x73f358', '0x73f35c'] */

/* 0x00218790, 0x4A8 bytes. */
void func_00218790(int param_1, int param_2)
{
    float fVar15;
    int iVar10;
    int iVar11;
    int iVar14;
    int iVar2;
    int iVar5;
    long long lVar4;
    int * piVar9;
    u8 * puVar12;
    u32 * puVar3;
    int uVar1;
    u32 uVar13;
    u32 uVar6;
    u32 uVar7;
    u32 uVar8;

  
  puVar12 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0040D88C));
  if ((*(u32 *)(g_00669DB8 + 0x0)) == 2) {
    iVar5 = 0x54;
  }
  else {
    iVar5 = (*(u32 *)(g_00669DB8 + 0x8));
    if ((*(u32 *)(g_00669DB8 + 0x0)) == 3) {
      iVar5 = 0x55;
    }
  }
  uVar1 = *(u16 *)((*(u32 *)(g_005BA694 + 0x0)) + iVar5 * 100 + 2);
  fVar15 = 1.0f;
  if (uVar1 < 0x1b) {
    fVar15 = *(float *)((g_0040D960 + 0x0) + (u32)uVar1 * 4);
  }
  iVar5 = (int)param_1;
  if (param_2 == 0) {
    puVar3 = (u32 *)(iVar5 * 0x630 + 0x574e20);
    iVar11 = iVar5 * 0x240 + 0x5b4bc0;
    iVar10 = iVar11;
    if ((long long)(*(char *)(g_005755A8 + 0x0)) << 0x3e < 0) {
      lVar4 = 0;
    }
    else {
      lVar4 = func_00190610(puVar3,0x8000);
    }
  }
  else {
    puVar12 = (u8 *)((u32)((u8 *)PS2_PTR(*(ps2ptr *)g_0040D88C)) & 0xefffffff);
    puVar3 = (u32 *)func_001D7740(param_1);
    iVar11 = (*(u32 *)(g_0045D2C0 + 0x0));
    lVar4 = func_00190610(puVar3,0x8000);
    iVar10 = iVar5 * 0x240 + 0x5b4bc0;
  }
  if (param_1 == 1) {
    uVar13 = (u32)puVar12 | 0x80;
  }
  else {
    uVar13 = (u32)puVar12 | 0x40;
  }
  iVar14 = iVar5 * 0x10;
  uVar6 = puVar3[1];
  uVar7 = puVar3[2];
  uVar8 = puVar3[3];
  *(u32 *)(g_0073E0C0 + iVar14) = *puVar3;
  *(u32 *)(g_0073E0C4 + iVar14) = uVar6;
  *(u32 *)(g_0073E0C8 + iVar14) = uVar7;
  *(u32 *)(g_0073E0CC + iVar14) = uVar8;
  uVar6 = func_001F2B70((unsigned char *)(puVar3));
  *(u32 *)(g_0073E0C4 + iVar14) = uVar6;
  if (lVar4 == 0) {
    piVar9 = (int *)(iVar5 * 0x2c + 0x73e04c);
    iVar14 = *piVar9;
    if (iVar14 == 0) {
      *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x238) = 0x3f800000;
      if ((long long)*(char *)((u8 *)PS2_PTR(iVar11) + 0x230) << 0x3d < 0) {
        *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x23c) = 0x458ca000;
      }
      else {
        *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x23c) = 0x461c4000;
      }
      *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x238) = 0x3f800000;
      if ((long long)*(char *)((u8 *)PS2_PTR(iVar10) + 0x230) << 0x3d < 0) {
        *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x23c) = 0x458ca000;
      }
      else {
        *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x23c) = 0x461c4000;
      }
    }
    else {
      *(u32 *)((u8 *)PS2_PTR(iVar14) + 0x38) = *(u32 *)((u8 *)PS2_PTR(iVar14) + 0x38) | 8;
      *piVar9 = 0;
      *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x238) = 0x3f800000;
      if ((long long)*(char *)((u8 *)PS2_PTR(iVar11) + 0x230) << 0x3d < 0) {
        *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x23c) = 0x458ca000;
      }
      else {
        *(u32 *)((u8 *)PS2_PTR(iVar11) + 0x23c) = 0x461c4000;
      }
      *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x238) = 0x3f800000;
      if ((long long)*(char *)((u8 *)PS2_PTR(iVar10) + 0x230) << 0x3d < 0) {
        *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x23c) = 0x458ca000;
      }
      else {
        *(u32 *)((u8 *)PS2_PTR(iVar10) + 0x23c) = 0x461c4000;
      }
    }
  }
  else {
    piVar9 = (int *)(iVar5 * 0x2c + 0x73e04c);
    iVar2 = *piVar9;
    if (iVar2 != 0) {
      *(u32 *)((u8 *)PS2_PTR(iVar2) + 0x38) = *(u32 *)((u8 *)PS2_PTR(iVar2) + 0x38) | 8;
      *piVar9 = 0;
    }
    g_70000D60 = 2;
    lVar4 = PS2_ADDR(func_001C8340(0x10c,(unsigned char *)PS2_PTR(iVar14 + 0x73e0c0),0,uVar13 | 0x31));
    *(int *)(iVar5 * 0x2c + 0x73e04c) = (int)lVar4;
    if (lVar4 != 0) {
      uVar13 = 0;
      do {
        *(u32 *)(*piVar9 + 0x40) = 0;
        func_001C8E80((unsigned char *)PS2_PTR(*piVar9));
        uVar13 = uVar13 + 1;
      } while (uVar13 < 2);
    }
    *(float *)((u8 *)PS2_PTR(iVar11) + 0x238) = fVar15;
    if ((long long)*(char *)((u8 *)PS2_PTR(iVar11) + 0x230) << 0x3d < 0) {
      *(float *)((u8 *)PS2_PTR(iVar11) + 0x23c) = fVar15 * 4500.0f;
    }
    else {
      *(float *)((u8 *)PS2_PTR(iVar11) + 0x23c) = fVar15 * 10000.0f;
    }
    *(float *)((u8 *)PS2_PTR(iVar10) + 0x238) = fVar15;
    if ((long long)*(char *)((u8 *)PS2_PTR(iVar10) + 0x230) << 0x3d < 0) {
      *(float *)((u8 *)PS2_PTR(iVar10) + 0x23c) = fVar15 * 4500.0f;
    }
    else {
      *(float *)((u8 *)PS2_PTR(iVar10) + 0x23c) = fVar15 * 10000.0f;
    }
  }
  if (1.0f <= *(float *)((u8 *)PS2_PTR(iVar10) + 0x238)) {
    *(u32 *)(iVar5 * 4 + 0x45d468) = 0;
  }
  else {
    *(u32 *)(iVar5 * 4 + 0x45d468) = 0x3f800000;
  }
  return;
}
/* MISSING ['0x45d2c0'] */

/* 0x00218C40, 0x234 bytes. */
void func_00218C40(int param_1, int param_2)
{
    int iVar1;
    int iVar7;
    int iVar8;
    long long lVar3;
    int * piVar9;
    u32 * puVar10;
    u32 * puVar2;
    u32 uVar11;
    u32 uVar12;
    u32 uVar4;
    u32 uVar5;
    u32 uVar6;

  
  iVar7 = (int)param_1;
  if (param_2 == 0) {
    puVar2 = (u32 *)(iVar7 * 0x630 + 0x574e20);
  }
  else {
    puVar2 = (u32 *)func_001D7740();
  }
  iVar8 = iVar7 * 0x10;
  uVar4 = puVar2[1];
  uVar5 = puVar2[2];
  uVar6 = puVar2[3];
  *(u32 *)(g_0073E0C0 + iVar8) = *puVar2;
  *(u32 *)(g_0073E0C4 + iVar8) = uVar4;
  *(u32 *)(g_0073E0C8 + iVar8) = uVar5;
  *(u32 *)(g_0073E0CC + iVar8) = uVar6;
  uVar4 = func_001F2B70((unsigned char *)(puVar2));
  *(u32 *)(g_0073E0C4 + iVar8) = uVar4;
  if (g_0045D48C < 2) {
    uVar12 = 1;
    puVar10 = (u32 *)((g_0040D874 + 0x0));
    piVar9 = (int *)(iVar7 * 0x2c + 0x73e034);
    do {
      uVar11 = *puVar10;
      if (param_2 != 0) {
        uVar11 = uVar11 & 0xefffffff;
      }
      if (param_1 == 1) {
        uVar11 = uVar11 | 0x80;
      }
      else {
        uVar11 = uVar11 | 0x40;
      }
      iVar7 = *(int *)(uVar12 * 4 + 0x40d840);
      if ((iVar7 != 0x18b) && (uVar12 != 7)) {
        lVar3 = func_00190610(puVar2,0x100 << (uVar12 & 0x1f));
        if (lVar3 == 0) {
          iVar7 = *piVar9;
          if (iVar7 != 0) {
            *(u32 *)((u8 *)PS2_PTR(iVar7) + 0x38) = *(u32 *)((u8 *)PS2_PTR(iVar7) + 0x38) | 8;
            *piVar9 = 0;
          }
        }
        else {
          iVar1 = *piVar9;
          if (iVar1 != 0) {
            *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x38) | 8;
            *piVar9 = 0;
          }
          g_70000D60 = 2;
          lVar3 = PS2_ADDR(func_001C8340(iVar7,(unsigned char *)PS2_PTR(iVar8 + 0x73e0c0),0,uVar11 | 0x31));
          *piVar9 = (int)lVar3;
          if (lVar3 != 0) {
            uVar11 = 0;
            do {
              *(u32 *)(*piVar9 + 0x40) = 0;
              func_001C8E80((unsigned char *)PS2_PTR(*piVar9));
              uVar11 = uVar11 + 1;
            } while (uVar11 < 2);
          }
        }
      }
      uVar12 = uVar12 + 1;
      puVar10 = puVar10 + 1;
      piVar9 = piVar9 + 1;
    } while (uVar12 < 10);
  }
  return;
}

/* MISSING ['0x45d1f0'] */

/* MISSING ['0x45cdb8', '0x45d4a0'] */

/* MISSING ['0x40e940', '0x40e944', '0x40e948', '0x40e94c', '0x40e950', '0x40e954', '0x40e958', '0x40e95c', '0x40e960', '0x40e964'] */

/* MISSING ['0x5bc03c', '0x693703'] */

/* MISSING ['0x5bc050', '0x5bc054', '0x692da0', '0x692da4'] */

/* 0x00239520, 0x190 bytes. */
void func_00239520(int param_1)
{
    float fStack_4;
    long long lVar2;
    u8 * pbVar1;

  
  lVar2 = func_00238930((unsigned char *)PS2_PTR(param_1),&fStack_4);
  if (lVar2 != 0) {
    pbVar1 = (u8 *)func_001F14E0((unsigned char *)PS2_PTR(param_1));
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    if ((g_7000015C >> 0x10) % 100 < (u32)(int)((float)*pbVar1 * fStack_4)) {
      func_002392D0(param_1,0);
    }
    else {
      g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
      if ((g_7000015C >> 0x10) % 100 < (u32)(int)((float)pbVar1[1] * fStack_4)) {
        func_002392D0(param_1,1);
      }
      else {
        lVar2 = func_00238F50((unsigned char *)PS2_PTR(param_1));
        if (lVar2 == 0) {
          g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
          if ((g_7000015C >> 0x10) % 100 < (u32)pbVar1[3]) {
            g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
            func_00238AE0(param_1,(g_7000015C >> 0x10) % 0x3c + 0x3c);
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

/* 0x00239C80, 0x1D4 bytes. */
void func_00239C80(u8 *param_1)
{
    u8 * iVar1;
    int iVar4;
    long long lVar3;
    u8 * pbVar2;

  
  pbVar2 = (u8 *)func_001F14E0(param_1);
  iVar4 = PS2_ADDR(param_1);
  iVar1 = (u8 *)PS2_PTR(*(int *)((u8 *)PS2_PTR(iVar4) + 0x14));
  if ((long long)*(char *)(iVar1 + 0x19d) << 0x3c < 0) {
    if ((*(u8 *)(iVar1 + 0xe8) & 1) == 0) {
      *(u32 *)((u8 *)PS2_PTR(iVar4) + 0xbc) = *(u32 *)((u8 *)PS2_PTR(iVar4) + 0xbc) & 0xfff8003f;
      *(u8 *)((u8 *)PS2_PTR(iVar4) + 0x7d) = 1;
      func_00204B60(param_1,0);
      return;
    }
    func_00239980(param_1);
    return;
  }
  if ((((*(int *)(iVar1 + 0x11c) != 0) && (*(int *)((u8 *)PS2_PTR(iVar4) + 8) != 0)) &&
      (iVar4 = *(int *)(*(int *)((u8 *)PS2_PTR(iVar4) + 8) + 0x14), *(int *)((u8 *)PS2_PTR(iVar4) + 0x11c) != 0)) &&
     (((*(u8 *)(iVar1 + 0xe8) & 1) == 0 &&
      (lVar3 = func_00174A40(1.0f,iVar1 + 0x40,(u8 *)PS2_PTR(iVar4 + 0x40)), lVar3 < 3)))) {
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    if ((g_7000015C >> 0x10) % 100 < (u32)*pbVar2) {
      func_00239940(param_1);
      return;
    }
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    if ((g_7000015C >> 0x10) % 100 < (u32)pbVar2[1]) {
      func_00239940(param_1);
      return;
    }
  }
  g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
  if ((g_7000015C >> 0x10) % 100 < (u32)pbVar2[3]) {
    func_00238E80(param_1,1);
  }
  else {
    func_00206080(param_1);
  }
  return;
}

/* 0x0024AC00, 0x374 bytes. */
void func_0024AC00(int param_1, int param_2, float *param_3, int param_4, int param_5)
{
    int bVar2;
    int bVar3;
    int bVar4;
    float fStack_10;
    float fStack_4;
    float fStack_8;
    float fStack_c;
    int iVar1;
    int iVar5;
    int iVar6;
    int iVar7;

  
  iVar1 = *(int *)(g_70000150 * 4 + 0x732500);
  fStack_10 = *param_3;
  fStack_c = param_3[1];
  fStack_8 = param_3[2];
  fStack_4 = param_3[3];
  iVar5 = func_0019AF10(16.0f,param_1,param_2);
  fStack_c = fStack_c - 10.0f;
  fStack_10 = (fStack_10 + 0.0f) - (float)iVar5 * 0.5f;
  iVar5 = func_001AB1D0(20.0f,20.0f,(unsigned char *)PS2_PTR(iVar1 + (*(u32 *)(g_00732508 + 0x0)) * 0x5d0 + 0xd0),param_1,param_2,
                       &fStack_10,param_4,param_5,0,0);
  if (iVar5 < 0x10) {
    if (8 < (int)(0x10U - iVar5)) {
      bVar4 = false;
      bVar3 = false;
      bVar2 = false;
      if ((iVar5 < 0x11) && (iVar5 < 0x7fffffff)) {
        bVar2 = true;
      }
      if ((bVar2) && (iVar5 != -0x80000000)) {
        bVar3 = true;
      }
      if (bVar3) {
        bVar2 = true;
        if (((-iVar5 & 0x80000000U) == 0) && ((0x10U - iVar5 & 0x80000000) != 0)) {
          bVar2 = false;
        }
        if (bVar2) {
          bVar4 = true;
        }
      }
      if (bVar4) {
        iVar6 = iVar5 * 0x50;
        do {
          iVar5 = iVar5 + 8;
          iVar7 = iVar1 + (*(u32 *)(g_00732508 + 0x0)) * 0x5d0 + iVar6;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x100) = 0;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x110) = 0;
          iVar7 = iVar1 + (*(u32 *)(g_00732508 + 0x0)) * 0x5d0 + iVar6;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x150) = 0;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x160) = 0;
          iVar7 = iVar1 + (*(u32 *)(g_00732508 + 0x0)) * 0x5d0 + iVar6;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x1a0) = 0;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x1b0) = 0;
          iVar7 = iVar1 + (*(u32 *)(g_00732508 + 0x0)) * 0x5d0 + iVar6;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x1f0) = 0;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x200) = 0;
          iVar7 = iVar1 + (*(u32 *)(g_00732508 + 0x0)) * 0x5d0 + iVar6;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x240) = 0;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x250) = 0;
          iVar7 = iVar1 + (*(u32 *)(g_00732508 + 0x0)) * 0x5d0 + iVar6;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x290) = 0;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x2a0) = 0;
          iVar7 = iVar1 + (*(u32 *)(g_00732508 + 0x0)) * 0x5d0 + iVar6;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x2e0) = 0;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x2f0) = 0;
          iVar7 = iVar1 + (*(u32 *)(g_00732508 + 0x0)) * 0x5d0 + iVar6;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x330) = 0;
          iVar6 = iVar6 + 0x280;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x340) = 0;
        } while (iVar5 < 8);
      }
    }
    if (iVar5 < 0x10) {
      iVar6 = iVar5 * 0x50;
      do {
        iVar5 = iVar5 + 1;
        iVar7 = iVar1 + (*(u32 *)(g_00732508 + 0x0)) * 0x5d0 + iVar6;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x100) = 0;
        iVar6 = iVar6 + 0x50;
        *(unsigned long long *)((u8 *)PS2_PTR(iVar7) + 0x110) = 0;
      } while (iVar5 < 0x10);
    }
  }
  return;
}

/* MISSING ['0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c'] */

/* MISSING ['0x410ac0', '0x410ac4', '0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x5b4fc0', '0x5b4fc4', '0x5b4fc8', '0x5b4fd0', '0x5b4fd4', '0x5b4fd8', '0x5b5020', '0x5b5024', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c', '0x76ec80', '0x76ec84', '0x76ec88', '0x76ec8c', '0x76ec90', '0x76ec94', '0x76ec98', '0x76ec9c'] */

/* MISSING ['0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c'] */

/* MISSING ['0x410ac0', '0x410ac4', '0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x5b4fc0', '0x5b4fc4', '0x5b4fc8', '0x5b4fd0', '0x5b4fd4', '0x5b4fd8', '0x5b5020', '0x5b5024', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c', '0x76ec80', '0x76ec84', '0x76ec88', '0x76ec8c', '0x76ec90', '0x76ec94', '0x76ec98', '0x76ec9c'] */

/* 0x00262AD0, 0x6A8 bytes. */
void func_00262AD0(void)
{
    float afStack_20[7];
    int bVar1;
    int bVar2;
    int bVar3;
    float fStack_4;
    float fVar10;
    float fVar12;
    int iVar11;
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar9;
    int sVar4;
    unsigned long long uVar8;

  
  sVar4 = (*(short *)(g_007325A8 + 0x4));
  if ((*(short *)(g_007325A8 + 0x0)) == 0) {
    func_00262130();
  }
  else {
    iVar5 = *(int *)(g_70000150 * 4 + 0x732500);
    iVar7 = g_70000150 * 0x170;
    iVar9 = iVar5 + 0x18af0;
    if ((*(short *)(g_007325A8 + 0x4)) < (*(short *)(g_007325A8 + 0x6))) {
      (*(short *)(g_007325A8 + 0x6)) = (*(short *)(g_007325A8 + 0x6)) + -1;
    }
    fVar12 = (float)(int)(*(short *)(g_007325A8 + 0x8));
    fVar10 = (fVar12 / 1000.0f) * 220.0f;
    iVar6 = (int)(*(short *)(g_007325A8 + 0x6));
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x195c0) = 0xfffe79c87110;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x195d0) = 0xfffe7b887490;
    *(unsigned long long *)(g_00732370 + iVar7) = 0xfffe79b07130;
    *(unsigned long long *)(g_00732380 + iVar7) = 0xfffe7b787400;
    iVar11 = (int)fVar10;
    func_001A9B30((unsigned char *)PS2_PTR(iVar7 + 0x732220),(*(u8 *)(g_007325A8 + 0xF)),1);
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x194d0) = 0xfffe7a1872d0;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x194e0) = 0xfffe7a887450;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19520) = 0xfffe7a187450;
    uVar8 = (unsigned long long)((iVar11 + 0x45) * 0x10 + 0x7000);
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19530) = uVar8 | 0xfffe7a880000;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19570) = uVar8 | 0xfffe7a180000;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19580) = (long long)((iVar11 + 0x65) * 0x10 + 0x7000) | 0xfffe7a880000;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x193e0) = 0xfffe7a307430;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x193f0) = (long long)((iVar11 + 0x43) * 0x10 + 0x7000) | 0xfffe7a700000;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19480) = 0xfffe7a307430;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19490) =
         (long long)(((int)((fVar12 / 1000.0f) * ((float)(int)sVar4 / fVar12) * 220.0f) + 0x43) * 0x10 +
               0x7000) | 0xfffe7a700000;
    if ((*(char *)(g_007325A8 + 0xE)) == '\x01') {
      *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19470) = 0x3f8000004e4e49c0;
    }
    else if ((*(char *)(g_007325A8 + 0xE)) == '\x02') {
      *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19470) = 0x3f8000004e4ec0c0;
    }
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19430) = 0xfffe7a307430;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19440) =
         (long long)(((int)((fVar10 * (float)iVar6) / fVar12) + 0x43) * 0x10 + 0x7000) | 0xfffe7a700000;
    if ((*(char *)(g_007325A8 + 0xE)) == '\x01') {
      *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19420) = 0x3f800000284e49c0;
    }
    else if ((*(char *)(g_007325A8 + 0xE)) == '\x02') {
      *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x19420) = 0x3f800000284ec0c0;
    }
    afStack_20[0] = 72.0f;
    afStack_20[1] = 46.0f;
    afStack_20[3] = 0.0f;
    afStack_20[2] = 0.0f;
    iVar7 = func_001AB430(16.0f,16.0f,(unsigned char *)PS2_PTR(iVar5 + 0x18b90),(unsigned char *)PS2_PTR((*(char *)(g_007325A8 + 0xE))),afStack_20,5,0x80,1,
                         &fStack_4);
    if (iVar7 < 10) {
      if (8 < (int)(10U - iVar7)) {
        bVar3 = false;
        bVar2 = false;
        bVar1 = false;
        if ((iVar7 < 0xb) && (iVar7 < 0x7fffffff)) {
          bVar1 = true;
        }
        if ((bVar1) && (iVar7 != -0x80000000)) {
          bVar2 = true;
        }
        if (bVar2) {
          bVar1 = true;
          if (((-iVar7 & 0x80000000U) == 0) && ((10U - iVar7 & 0x80000000) != 0)) {
            bVar1 = false;
          }
          if (bVar1) {
            bVar3 = true;
          }
        }
        if (bVar3) {
          iVar6 = iVar9 + iVar7 * 0x50;
          do {
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0xd0) = 0;
            iVar7 = iVar7 + 8;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0xe0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x120) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x130) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x170) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x180) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x1c0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x1d0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x210) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x220) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x260) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x270) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x2b0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x2c0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x300) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x310) = 0;
            iVar6 = iVar6 + 0x280;
          } while (iVar7 < 2);
        }
      }
      if (iVar7 < 10) {
        iVar6 = iVar9 + iVar7 * 0x50;
        do {
          *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0xd0) = 0;
          iVar7 = iVar7 + 1;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0xe0) = 0;
          iVar6 = iVar6 + 0x50;
        } while (iVar7 < 10);
      }
    }
    iVar7 = (int)fStack_4;
    afStack_20[0] = (float)(iVar7 + 0x4e);
    iVar5 = func_001AB1D0(16.0f,16.0f,(unsigned char *)PS2_PTR(iVar5 + 0x18eb0),(*(u16 *)(g_007325A8 + 0xA)),(*(u16 *)(g_007325A8 + 0xC)),afStack_20,
                         5,0x80,1,&fStack_4);
    if (iVar5 < 0x10) {
      if (8 < (int)(0x10U - iVar5)) {
        bVar3 = false;
        bVar2 = false;
        bVar1 = false;
        if ((iVar5 < 0x11) && (iVar5 < 0x7fffffff)) {
          bVar1 = true;
        }
        if ((bVar1) && (iVar5 != -0x80000000)) {
          bVar2 = true;
        }
        if (bVar2) {
          bVar1 = true;
          if (((-iVar5 & 0x80000000U) == 0) && ((0x10U - iVar5 & 0x80000000) != 0)) {
            bVar1 = false;
          }
          if (bVar1) {
            bVar3 = true;
          }
        }
        if (bVar3) {
          iVar6 = iVar9 + iVar5 * 0x50;
          do {
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x3f0) = 0;
            iVar5 = iVar5 + 8;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x400) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x440) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x450) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x490) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x4a0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x4e0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x4f0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x530) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x540) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x580) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x590) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x5d0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x5e0) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x620) = 0;
            *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x630) = 0;
            iVar6 = iVar6 + 0x280;
          } while (iVar5 < 8);
        }
      }
      if (iVar5 < 0x10) {
        iVar6 = iVar9 + iVar5 * 0x50;
        do {
          *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x3f0) = 0;
          iVar5 = iVar5 + 1;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar6) + 0x400) = 0;
          iVar6 = iVar6 + 0x50;
        } while (iVar5 < 0x10);
      }
    }
    func_001A4C40((unsigned char *)PS2_PTR(iVar9),0x37,0x2b,0,iVar7 + (int)fStack_4 + 0x2c,0x18,0x80, 1, 1);
    (*(short *)(g_007325A8 + 0x0)) = (*(short *)(g_007325A8 + 0x0)) + -1;
  }
  return;
}

/* 0x00263BD0, 0x5D0 bytes. */
void func_00263BD0(int param_1, int param_2)
{
    int iStack_20;
    int iStack_40;
    int iStack_50;
    int iStack_60;
    u8 * iVar11;
    int iVar12;
    int iVar2;
    int iVar3;
    u8 * iVar4;
    int iVar5;
    int iVar8;
    int iVar9;
    unsigned long long uStack_28;
    u32 uVar1;
    unsigned long long uVar10;
    unsigned long long uVar6;
    unsigned long long uVar7;

  
  iVar11 = g_00732220;
  iVar2 = param_1 * 0x2c;
  *(u8 *)(g_0073260C + iVar2) = 0;
  iStack_20 = 0;
  iVar12 = param_1 * 0x1380;
  uVar1 = *(u32 *)(param_1 * 0x48 + 0x669dec);
  *(u32 *)(g_007325F8 + iVar2) = uVar1;
  *(u32 *)(g_00732600 + iVar2) = uVar1;
  *(u8 *)(g_0073260F + iVar2) = param_2;
  do {
    iVar3 = *(int *)(iVar11 + 0x2e0) + iVar12;
    uVar6 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef2);
    func_001057F0((unsigned char *)PS2_PTR(iVar3 + 0x1af00),uVar6,0);
    *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af20) = 0x3f80000080808080;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af28) = 0x7480008;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af38) = 0xa480388;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af30) = 0xfffe84988c70;
    *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af40) = 0xfffe86208f90;
    if (*(char *)(g_0073260F + iVar2) == '\x01') {
      uVar6 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f01);
      *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af18) = uVar6;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af28) = 0xb880808;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af38) = 0xe080a88;
    }
    else if (*(char *)(g_0073260F + iVar2) == '\x02') {
      uVar6 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3eff);
      *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af18) = uVar6;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af28) = 0xb880308;
      *(unsigned long long *)((u8 *)PS2_PTR(iVar3) + 0x1af38) = 0xe080588;
    }
    iVar3 = 0x144;
    if (*(char *)(g_0073260F + iVar2) == '\x01') {
      uStack_28 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef0);
    }
    else if (*(char *)(g_0073260F + iVar2) == '\x02') {
      uStack_28 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3ef0);
    }
    else {
      uStack_28 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3eed);
    }
    iVar9 = 0;
    iStack_40 = 0;
    iVar8 = 0;
    iStack_50 = 0x8440;
    iStack_60 = 0;
    do {
      iVar4 = (u8 *)PS2_PTR(*(int *)(iVar11 + 0x2e0) + iVar12 + iStack_40);
      func_00105A30(iVar4 + 0x1af50,uStack_28,0);
      *(unsigned long long *)(iVar4 + 0x1af70) = 0x3f80000080808080;
      *(unsigned long long *)(iVar4 + 0x1af78) = 0x80c88;
      *(unsigned long long *)(iVar4 + 0x1af88) = 0x80f08;
      *(unsigned long long *)(iVar4 + 0x1af98) = 0x3080c88;
      *(unsigned long long *)(iVar4 + 0x1afa8) = 0x3080f08;
      uVar7 = (unsigned long long)iStack_50;
      *(unsigned long long *)(iVar4 + 0x1af80) = uVar7 | 0xfffe84a00000;
      uVar10 = (unsigned long long)((iVar3 + 0x24) * 0x10 + 0x7000);
      *(unsigned long long *)(iVar4 + 0x1af90) = uVar10 | 0xfffe84a00000;
      *(unsigned long long *)(iVar4 + 0x1afa0) = uVar7 | 0xfffe86280000;
      *(unsigned long long *)(iVar4 + 0x1afb0) = uVar10 | 0xfffe86280000;
      if (iVar9 < 4) {
        *(unsigned long long *)(iVar4 + 0x1af80) = 0;
        *(unsigned long long *)(iVar4 + 0x1af90) = 0;
        *(unsigned long long *)(iVar4 + 0x1afa0) = 0;
        *(unsigned long long *)(iVar4 + 0x1afb0) = 0;
      }
      iVar4 = (u8 *)PS2_PTR(*(int *)(iVar11 + 0x2e0) + iVar12 + iVar8);
      func_00105A30(iVar4 + 0x1b180,uStack_28,0);
      *(unsigned long long *)(iVar4 + 0x1b1a0) = 0x3f80000080808080;
      *(unsigned long long *)(iVar4 + 0x1b1a8) = 0x80c88;
      *(unsigned long long *)(iVar4 + 0x1b1b8) = 0x80f08;
      *(unsigned long long *)(iVar4 + 0x1b1c8) = 0x3080c88;
      *(unsigned long long *)(iVar4 + 0x1b1d8) = 0x3080f08;
      *(unsigned long long *)(iVar4 + 0x1b1b0) = uVar7 | 0xfffe84a00000;
      *(unsigned long long *)(iVar4 + 0x1b1c0) = uVar10 | 0xfffe84a00000;
      *(unsigned long long *)(iVar4 + 0x1b1d0) = uVar7 | 0xfffe86280000;
      *(unsigned long long *)(iVar4 + 0x1b1e0) = uVar10 | 0xfffe86280000;
      *(unsigned long long *)(iVar4 + 0x1b1b0) = 0;
      *(unsigned long long *)(iVar4 + 0x1b1c0) = 0;
      *(unsigned long long *)(iVar4 + 0x1b1d0) = 0;
      *(unsigned long long *)(iVar4 + 0x1b1e0) = 0;
      iVar4 = (u8 *)PS2_PTR(*(int *)(iVar11 + 0x2e0) + iVar12 + iVar8);
      func_00105A30(iVar4 + 0x1b1f0,uStack_28,0);
      *(unsigned long long *)(iVar4 + 0x1b210) = 0x3f80000080808080;
      *(unsigned long long *)(iVar4 + 0x1b218) = 0x80c88;
      *(unsigned long long *)(iVar4 + 0x1b228) = 0x80f08;
      *(unsigned long long *)(iVar4 + 0x1b238) = 0x3080c88;
      *(unsigned long long *)(iVar4 + 0x1b248) = 0x3080f08;
      *(unsigned long long *)(iVar4 + 0x1b220) = uVar7 | 0xfffe84a00000;
      *(unsigned long long *)(iVar4 + 0x1b230) = uVar10 | 0xfffe84a00000;
      *(unsigned long long *)(iVar4 + 0x1b240) = uVar7 | 0xfffe86280000;
      *(unsigned long long *)(iVar4 + 0x1b250) = uVar10 | 0xfffe86280000;
      *(unsigned long long *)(iVar4 + 0x1b220) = 0;
      *(unsigned long long *)(iVar4 + 0x1b230) = 0;
      *(unsigned long long *)(iVar4 + 0x1b240) = 0;
      *(unsigned long long *)(iVar4 + 0x1b250) = 0;
      iVar4 = (u8 *)PS2_PTR(*(int *)(iVar11 + 0x2e0) + iVar12 + iStack_60);
      uVar6 = func_00106C90((*(unsigned long long *)(g_0068F0F0 + 0x0)),0x3f3b);
      func_001057F0(iVar4 + 0x1b5e0,uVar6,0);
      iVar9 = iVar9 + 1;
      *(unsigned long long *)(iVar4 + 0x1b600) = 0x3f80000080808080;
      *(unsigned long long *)(iVar4 + 0x1b608) = 0x3881e88;
      iVar8 = iVar8 + 0xe0;
      *(unsigned long long *)(iVar4 + 0x1b618) = 0x5481ff8;
      iVar5 = iVar3 + 0x3c;
      *(unsigned long long *)(iVar4 + 0x1b610) = (long long)((iVar3 + -0x24) * 0x10 + 0x7000) | 0xfffe83800000;
      iVar3 = iVar3 + 0x1b;
      iStack_50 = iStack_50 + 0x1b0;
      iStack_40 = iStack_40 + 0x70;
      *(unsigned long long *)(iVar4 + 0x1b620) = (long long)(iVar5 * 0x10 + 0x7000) | 0xfffe87900000;
      *(unsigned long long *)(iVar4 + 0x1b610) = 0;
      iStack_60 = iStack_60 + 0x50;
      *(unsigned long long *)(iVar4 + 0x1b620) = 0;
    } while (iVar9 < 5);
    iStack_20 = iStack_20 + 1;
    iVar11 = iVar11 + 4;
  } while (iStack_20 < 2);
  func_002632B0(param_1);
  return;
}

/* 0x00270C90, 0x554 bytes. */
void func_00270C90(int param_1, int param_2)
{
    int bVar1;
    int bVar2;
    float fStack_4;
    float fStack_8;
    float fVar20;
    u8 * iStack_20;
    int iVar11;
    int iVar12;
    int iVar14;
    int iVar19;
    int iVar4;
    int iVar5;
    long long lVar18;
    unsigned long long uVar10;
    unsigned long long uVar13;
    unsigned long long uVar15;
    unsigned long long uVar16;
    unsigned long long uVar17;
    int uVar3;
    unsigned long long uVar6;
    unsigned long long uVar7;
    unsigned long long uVar8;
    unsigned long long uVar9;

  
  bVar2 = false;
  iVar11 = 0;
  iStack_20 = g_00732220;
  iVar4 = (int)param_1 * 0x2c;
  if (((*(u32 *)(g_00669F60 + 0x0)) & 2) != 0) {
    if (param_1 == 0) {
      bVar2 = true;
    }
    else {
      iVar11 = 0xc0;
      bVar2 = true;
    }
  }
  *(u8 *)(g_00732611 + iVar4) = 0;
  iVar12 = (param_2 / 0x32) * 0x32;
  uVar3 = func_001A2970(iVar12);
  *(u8 *)(g_00732610 + iVar4) = uVar3;
  bVar1 = *(u8 *)(g_00732610 + iVar4);
  uVar10 = (unsigned long long)bVar1;
  if (bVar2) {
    fVar20 = (float)(int)(bVar1 - 1) * 36.0f;
    func_0026FBE0(fVar20 + 40.0f,48.0f,6.400000095367432f,6.400000095367432f,PS2_ADDR(&fStack_4),PS2_ADDR(&fStack_8));
    fStack_4 = fVar20 * 6.4f + fStack_4 + 0.0f;
  }
  else {
    fVar20 = (float)(int)(bVar1 - 1) * 36.0f;
    func_0026FBE0(fVar20 + 40.0f,48.0f,12.800000190734863f,12.800000190734863f,PS2_ADDR(&fStack_4),PS2_ADDR(&fStack_8));
    fStack_4 = fVar20 * 12.8f + fStack_4 + 0.0f;
  }
  lVar18 = 0;
  if (0 < (long long)uVar10) {
    iVar4 = (int)(fStack_8 + (float)iVar11) * 0x280;
    do {
      iVar19 = 0;
      iVar5 = ((iVar12 % 10) % 5) * 0x28;
      iVar11 = (iVar12 % 10) / 5;
      uVar7 = (unsigned long long)(int)((iVar5 + 200) * 0x10 | 8);
      uVar6 = (unsigned long long)(int)((iVar5 + 0xef) * 0x10 | 8);
      uVar8 = (long long)(int)(iVar11 * 0x300 | 8) << 0x10;
      uVar9 = uVar7 | uVar8;
      uVar8 = uVar8 | uVar6;
      uVar13 = (long long)(int)((iVar11 * 0x30 + 0x2f) * 0x10 | 8) << 0x10;
      uVar7 = uVar7 | uVar13;
      uVar6 = uVar6 | uVar13;
      iVar12 = iVar12 / 10;
      iVar11 = PS2_ADDR(iStack_20);
      do {
        iVar5 = *(int *)((u8 *)PS2_PTR(iVar11) + 0x2e0) + (int)param_1 * 0x1380 + (4 - (int)lVar18) * 0x70;
        if (bVar2) {
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c050) = 0x3f80000000808080;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c058) = uVar9;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c068) = uVar8;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c078) = uVar7;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c088) = uVar6;
          iVar14 = (iVar4 / 0x1e0) * 0x1c0;
          if (iVar14 < 0) {
            iVar14 = iVar14 + 0x1ff;
          }
          uVar15 = (long long)((iVar14 >> 9) * 8 + 0x7900) << 0x10;
          uVar16 = (long long)(((iVar14 >> 9) + 0x165) * 8 + 0x7900) << 0x10;
          uVar13 = (unsigned long long)((int)fStack_4 * 0x10 + 0x7000);
          uVar17 = (unsigned long long)(((int)fStack_4 + 0x100) * 0x10 + 0x7000);
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c060) = uVar13 | uVar15 | 0xfffe00000000;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c070) = uVar17 | uVar15 | 0xfffe00000000;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c080) = uVar13 | uVar16 | 0xfffe00000000;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c090) = uVar17 | uVar16 | 0xfffe00000000;
          fStack_4 = fStack_4 - 230.40001f;
        }
        else {
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c050) = 0x3f80000000808080;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c058) = uVar9;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c068) = uVar8;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c078) = uVar7;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c088) = uVar6;
          iVar14 = (iVar4 / 0x1e0) * 0x1c0;
          if (iVar14 < 0) {
            iVar14 = iVar14 + 0x1ff;
          }
          uVar15 = (long long)((iVar14 >> 9) * 8 + 0x7900) << 0x10;
          uVar16 = (long long)(((iVar14 >> 9) + 0x2cb) * 8 + 0x7900) << 0x10;
          uVar13 = (unsigned long long)((int)fStack_4 * 0x10 + 0x7000);
          uVar17 = (unsigned long long)(((int)fStack_4 + 0x200) * 0x10 + 0x7000);
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c060) = uVar13 | uVar15 | 0xfffe00000000;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c070) = uVar17 | uVar15 | 0xfffe00000000;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c080) = uVar13 | uVar16 | 0xfffe00000000;
          *(unsigned long long *)((u8 *)PS2_PTR(iVar5) + 0x1c090) = uVar17 | uVar16 | 0xfffe00000000;
          fStack_4 = fStack_4 - 460.80002f;
        }
        iVar19 = iVar19 + 1;
        iVar11 = iVar11 + 4;
      } while (iVar19 < 2);
      lVar18 = (long long)((int)lVar18 + 1);
    } while (lVar18 < (long long)uVar10);
  }
  return;
}

/* MISSING ['0x76f790', '0x76f794', '0x76f798', '0x76f79c', '0x76f7a0', '0x76f7a4', '0x76f7a8', '0x76f7ac', '0x76f7b8'] */

/* 0x0027A0C0, 0xE4 bytes. */
void func_0027A0C0(u32 *param_1, u32 *param_2, int param_3)
{
    u32 * puVar1;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;

  
  if (((*(u32 *)(g_00669DB8 + 0x0)) == 4) || ((*(u32 *)(g_00669DB8 + 0x0)) == 2)) {
    *param_1 = 0xbd23d70a;
    param_1[1] = 0x3ef0a3d7;
    param_1[2] = 0x3f6147ae;
    param_1[3] = 0;
    *param_2 = 0x43330000;
    param_2[1] = 0x43330000;
    param_2[2] = 0x43330000;
    param_2[3] = 0x3f800000;
    *param_1 = 0x3f800000;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    *param_2 = 0;
    param_2[1] = 0;
    param_2[2] = 0;
    param_2[3] = 0x3f800000;
    *param_1 = 0xbf0a3d71;
    param_1[1] = 0x3f800000;
    param_1[2] = 0;
    param_1[3] = 0;
    *param_2 = 0;
    param_2[1] = 0;
    param_2[2] = 0;
    param_2[3] = 0x3f800000;
  }
  else {
    uVar2 = *(u32 *)(g_0045D460 + 0x14);
    uVar3 = *(u32 *)(g_0045D460 + 0x18);
    uVar4 = *(u32 *)(g_0045D460 + 0x1c);
    *param_1 = *(u32 *)(g_0045D460 + 0x10);
    param_1[1] = uVar2;
    param_1[2] = uVar3;
    param_1[3] = uVar4;
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(param_3 * 4 + 0x73dfa0));
    uVar2 = puVar1[1];
    uVar3 = puVar1[2];
    uVar4 = puVar1[3];
    *param_2 = *puVar1;
    param_2[1] = uVar2;
    param_2[2] = uVar3;
    param_2[3] = uVar4;
  }
  return;
}

/* 0x0027A1B0, 0x60 bytes. */
void func_0027A1B0(u32 *param_1, int param_2)
{
    u32 * puVar1;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;

  
  if (((*(u32 *)(g_00669DB8 + 0x0)) == 4) || ((*(u32 *)(g_00669DB8 + 0x0)) == 2)) {
    *param_1 = 0x43000000;
    param_1[1] = 0x43000000;
    param_1[2] = 0x43000000;
    param_1[3] = 0x3f800000;
  }
  else {
    puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(param_2 * 4 + 0x73dfd0));
    uVar2 = puVar1[1];
    uVar3 = puVar1[2];
    uVar4 = puVar1[3];
    *param_1 = *puVar1;
    param_1[1] = uVar2;
    param_1[2] = uVar3;
    param_1[3] = uVar4;
  }
  return;
}

/* MISSING ['0x43fe50'] */

/* MISSING ['0x4112a0', '0x4112a4', '0x4112a8', '0x4112ac', '0x4112b0', '0x4112b4', '0x4112b8', '0x4112bc', '0x4112c0'] */

/* MISSING ['0x4114d8', '0x4114dc', '0x4114e0'] */

/* MISSING ['0x411820', '0x411824', '0x411828', '0x41182c', '0x411830', '0x411834', '0x411838', '0x41183c', '0x411840', '0x411844', '0x411848', '0x41184c', '0x411850', '0x411854', '0x411858', '0x41185c'] */

/* 0x00294C30, 0x440 bytes. */
void func_00294C30(u8 *param_1, int *param_2, int param_3, int param_4, int param_5)
{
    float fVar11;
    float fVar12;
    float fVar13;
    u8 * iVar1;
    u8 * iVar2;
    int iVar7;
    int iVar8;
    long long lVar10;
    long long lVar3;
    unsigned long long uVar4;
    unsigned long long uVar5;
    unsigned long long uVar6;
    unsigned long long uVar9;

  
  uVar9 = 0;
  if (((param_3 & 0xff) != 0) && ((param_3 & 0xff) != 0)) {
    iVar7 = 0;
    do {
      if (uVar9 == (param_4 & 0xff)) {
        fVar11 = 1.0f;
      }
      else {
        fVar11 = 0.675f;
      }
      fVar11 = fVar11 * 128.0f;
      if (2.1474836e+09f <= fVar11) {
        fVar11 = fVar11 - 2.1474836e+09f;
      }
      lVar10 = 0x80;
      if ((param_2[2] == 3) && (lVar3 = func_002208C0(), lVar3 == 0)) {
        lVar10 = 0x50;
      }
      fVar13 = (float)*param_2;
      fVar12 = (((float)*param_2 + 160.0f) / 10.0f) * (float)(u32)((*(u32 *)(g_00772D48 + 0x0)) - iVar7) + -160.0f;
      if (fVar12 < fVar13) {
        iVar8 = param_2[2];
      }
      else {
        iVar8 = param_2[2];
        fVar12 = fVar13;
      }
      iVar8 = PS2_ADDR(param_1 + *(int *)(param_1 + 8) * *(int *)(param_1 + 0x10 + iVar8 * 8));
      iVar1 = func_00106F10((unsigned char *)PS2_PTR(iVar8));
      uVar4 = func_00104AC0((unsigned char *)PS2_PTR(iVar8),0x1320,param_5);
      uVar5 = func_00104D00((unsigned char *)PS2_PTR(iVar8),0x3ffc,param_5);
      uVar4 = func_00106C50(uVar4,uVar5);
      uVar4 = PS2_ADDR(func_00105860(uVar4,0));
      uVar6 = (unsigned long long)((int)fVar11 & 0xff);
      iVar2 = (u8 *)PS2_PTR((int)uVar4);
      *(unsigned long long *)(iVar2 + 0x20) =
           lVar10 << 0x18 | uVar6 << 0x10 | uVar6 | uVar6 << 8 | 0x3f80000000000000;
      *(unsigned long long *)(iVar2 + 0x28) = 0x80008;
      *(long long *)(iVar2 + 0x38) =
           (long long)(int)((*(u16 *)(iVar1 + 0x14) - 1) * 0x10 | 8) |
           (long long)(int)((*(u16 *)(iVar1 + 0x16) - 1) * 0x10 | 8) << 0x10;
      iVar8 = ((param_2[1] * 0x280) / 0x1e0) * 0x1c0;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0x1ff;
      }
      *(unsigned long long *)(iVar2 + 0x30) =
           (long long)((int)fVar12 * 0x10 + 0x7000) |
           (long long)(((iVar8 >> 9) * 0x10 + -0xe00) / g_70000154 + 0x8000) << 0x10 | 0xfffe00000000;
      iVar8 = ((int)(((u32)*(u16 *)(iVar1 + 0x16) + param_2[1]) * 0x280) / 0x1e0) * 0x1c0;
      if (iVar8 < 0) {
        iVar8 = iVar8 + 0x1ff;
      }
      *(unsigned long long *)(iVar2 + 0x40) =
           (long long)(int)(((u32)*(u16 *)(iVar1 + 0x14) + (int)fVar12) * 0x10 + 0x7000) |
           (long long)(((iVar8 >> 9) * 0x10 + -0xe00) / g_70000154 + 0x8000) << 0x10 | 0xfffe00000000;
      func_00105900((unsigned char *)PS2_PTR(uVar4),param_5);
      uVar9 = (unsigned long long)((int)uVar9 + 1);
      param_2 = param_2 + 3;
      iVar7 = iVar7 + 2;
    } while ((long long)uVar9 < (long long)((unsigned long long)param_3 & 0xffffffff000000ff));
  }
  return;
}

/* MISSING ['0x411890', '0x411894', '0x411898', '0x41189c'] */

/* MISSING ['0x411980', '0x411984', '0x411988', '0x41198c', '0x411990', '0x411994', '0x411998', '0x41199c', '0x4119a0', '0x4119a4'] */

/* 0x0029B5A0, 0x358 bytes. */
void func_0029B5A0(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int iVar1;
    u8 * iVar5;
    unsigned long long uVar2;
    unsigned long long uVar3;
    unsigned long long uVar4;

  
  func_002C7310();
  uVar2 = PS2_ADDR(func_00362A20(0));
  func_002C4E40(20.0f,(char *)PS2_PTR(uVar2),param_1 + 0x9c,param_2 + 8,0x88,param_4,0,3);
  (*(u32 *)(g_0056CCA4 + 0x0)) = 1;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 1;
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41a00000;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 1;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 1;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41a00000;
  uVar2 = PS2_ADDR(func_00362A20(1));
  func_00146B40((const unsigned char *)PS2_PTR(uVar2),param_1 + 0xb4,param_2 + 8,0x88,0x14,param_4,0);
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
  func_003E4140(param_1 + 0x18,param_2 + 0x20,0,param_4);
  if (param_5 == 0) {
    uVar2 = func_003F6E60(0);
  }
  else {
    uVar2 = func_00362CE0(0);
  }
  func_003B5CA0(uVar2,param_1 + 0x6c,param_2 + 0x22,param_3,0x80,param_4);
  func_003E4220(param_1 + 0xc4,param_2 + 0x20,0,param_4);
  if (param_5 == 0) {
    uVar2 = func_003F7B70(1);
    uVar2 = PS2_ADDR(func_0030CB80(uVar2));
    func_002C4F40(16.0f,(char *)PS2_PTR(uVar2),param_1 + 0x128,param_2 + 0x20,param_4,0,1);
  }
  else {
    uVar2 = PS2_ADDR(func_00372D70(1));
    func_002C4F40(16.0f,(char *)PS2_PTR(uVar2),param_1 + 0x128,param_2 + 0x20,param_4,0,1);
  }
  uVar2 = PS2_ADDR(func_00105860(4,0));
  uVar3 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f57);
  iVar5 = (u8 *)PS2_PTR((int)uVar2);
  *(unsigned long long *)(iVar5 + 0x18) = uVar3;
  *(unsigned long long *)(iVar5 + 0x20) = 0x3f80000080808080;
  *(unsigned long long *)(iVar5 + 0x28) = 0x7880908;
  *(unsigned long long *)(iVar5 + 0x38) = 0x9080a88;
  iVar1 = (((param_2 + 0xc) * 0x280) / 0x1e0) * 0x1c0;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 0x1ff;
  }
  uVar4 = (long long)(0xfffe - (int)param_3) << 0x20;
  *(unsigned long long *)(iVar5 + 0x30) =
       uVar4 | (long long)((param_1 + 0x9c) * 0x10 + 0x7000) |
               (long long)(((iVar1 >> 9) * 0x10 + -0xe00) / g_70000154 + 0x8000) << 0x10;
  *(unsigned long long *)(iVar5 + 0x40) =
       uVar4 | (long long)((param_1 + 0xb4) * 0x10 + 0x7000) |
               (long long)((((iVar1 >> 9) + 0x1c) * 0x10 + -0xe00) / g_70000154 + 0x8000) << 0x10;
  func_00105900((unsigned char *)PS2_PTR(uVar2),param_4);
  return;
}

/* MISSING ['0x411b50', '0x411b54', '0x411b58'] */

/* 0x0029F790, 0x194 bytes. */
void func_0029F790(u8 *param_1, u8 *param_2, u8 *param_3, int param_4)
{
    int iVar4;
    u8 * iVar6;
    long long lVar1;
    u32 uStack_10;
    u32 uStack_4;
    u32 uStack_8;
    u32 uStack_c;
    unsigned long long uVar2;
    int uVar3;
    u32 uVar5;

  
  iVar6 = param_2;
  if ((*(u16 *)(param_3 + 0x1c) & 0x200) == 0) {
    uVar3 = *(u8 *)(iVar6 + 0x17e);
    uVar5 = (u32)*(u8 *)(iVar6 + 0x17f);
  }
  else if ((*(int *)(iVar6 + 0x288) == 0) ||
          (lVar1 = func_003DD5B0(*(u8 *)(*(int *)(iVar6 + 0x288) + 0x180),3), lVar1 == 0)) {
    uVar5 = (u32)*(u8 *)(iVar6 + 0x17f);
    uVar3 = *(u8 *)(iVar6 + 0x17e);
  }
  else {
    uVar3 = 1;
    uVar5 = 1;
  }
  switch(uVar3) {
  case 1:
    if (*(short *)(param_1 + 0x172) == 0) {
      if (uVar5 == 0) {
        *(u16 *)(param_1 + 0x15c) = 0;
        *(u16 *)(param_1 + 0x170) = 0;
      }
      else {
        *(u16 *)(param_1 + 0x15c) = 0x96;
        *(short *)(param_1 + 0x170) = (short)(0x10 / uVar5);
      }
    }
    break;
  case 3:
    if ((uVar5 != 0) && (param_4 != 0x75)) {
      iVar4 = g_0045D2FC + 0x10;
      if (*(int *)(param_1 + 0x11c) == 0) {
        uStack_10 = *(u32 *)(param_1 + 0x40);
        uStack_c = *(u32 *)(param_1 + 0x44);
        uStack_8 = *(u32 *)(param_1 + 0x48);
        uStack_4 = *(u32 *)(param_1 + 0x4c);
      }
      else {
        uStack_10 = *(u32 *)(param_1 + 0x90);
        uStack_c = *(u32 *)(param_1 + 0x94);
        uStack_8 = *(u32 *)(param_1 + 0x98);
        uStack_4 = *(u32 *)(param_1 + 0x9c);
      }
      uVar2 = PS2_ADDR(func_00177ED0());
      func_001ACA70((u8 *)PS2_PTR(uVar2),(u8 *)PS2_PTR(iVar4 + (uVar5 + 0x74) * 0x48),(float *)(&uStack_10),(float *)(param_1 + 0x70),param_2);
    }
  }
  if (*(char *)(param_3 + 0x19) == '\x06') {
    *(int *)(param_1 + 0x16c) = PS2_ADDR(iVar6);
  }
  else {
    *(u32 *)(param_1 + 0x16c) = 0;
  }
  return;
}

/* 0x002A5790, 0xE4 bytes. */
void func_002A5790(void)
{
    u8 * iVar1;
    u32 * puVar3;
    u32 uVar2;

  
  uVar2 = 0;
  do {
    puVar3 = (u32 *)(uVar2 * 0x3c + 0x77a700);
    *(u32 *)(uVar2 * 0x3c + 0x77a72c) = 0x107;
    func_00114890(puVar3);
    uVar2 = uVar2 + 1;
    *puVar3 = 0x3f800000;
  } while (uVar2 < 100);
  uVar2 = 0;
  (*(u32 *)(g_0077BEF4 + 0x0)) = 0;
  iVar1 = g_007732B0;
  do {
    *(u32 *)(iVar1 + 0x194) = 0;
    uVar2 = uVar2 + 8;
    *(u32 *)(iVar1 + 0x204) = 0;
    *(u32 *)(iVar1 + 0x274) = 0;
    *(u32 *)(iVar1 + 0x2e4) = 0;
    *(u32 *)(iVar1 + 0x354) = 0;
    *(u32 *)(iVar1 + 0x3c4) = 0;
    *(u32 *)(iVar1 + 0x434) = 0;
    *(u32 *)(iVar1 + 0x4a4) = 0;
    iVar1 = iVar1 + 0x380;
  } while (uVar2 < 0xff);
  iVar1 = (u8 *)PS2_PTR(uVar2 * 0x70);
  *(u32 *)(iVar1 + 0x773444) = 0;
  *(u32 *)(iVar1 + 0x7734b4) = 0;
  *(u32 *)(iVar1 + 0x773524) = 0;
  *(u32 *)(iVar1 + 0x773594) = 0;
  *(u32 *)(iVar1 + 0x773604) = 0;
  *(u32 *)(iVar1 + 0x773674) = 0;
  *(u32 *)(iVar1 + 0x7736e4) = 0;
  return;
}

/* 0x002A5D00, 0x68 bytes. */
void func_002A5D00(void)
{
    u8 * iVar1;
    u32 uVar2;

  
  uVar2 = 0x8f;
  iVar1 = g_00777140;
  do {
    *(u32 *)(iVar1 + 400) = 0;
    uVar2 = uVar2 + 8;
    *(u32 *)(iVar1 + 0x200) = 0;
    *(u32 *)(iVar1 + 0x270) = 0;
    *(u32 *)(iVar1 + 0x2e0) = 0;
    *(u32 *)(iVar1 + 0x350) = 0;
    *(u32 *)(iVar1 + 0x3c0) = 0;
    *(u32 *)(iVar1 + 0x430) = 0;
    *(u32 *)(iVar1 + 0x4a0) = 0;
    iVar1 = iVar1 + 0x380;
  } while (uVar2 < 0xeb);
  iVar1 = (u8 *)PS2_PTR(uVar2 * 0x70);
  *(u32 *)(iVar1 + 0x773440) = 0;
  *(u32 *)(iVar1 + 0x7734b0) = 0;
  *(u32 *)(iVar1 + 0x773520) = 0;
  *(u32 *)(iVar1 + 0x773590) = 0;
  return;
}

/* 0x002A5ED0, 0xF4 bytes. */
void func_002A5ED0(void)
{
    u8 * iVar1;
    u32 uVar2;

  
  uVar2 = 0;
  iVar1 = g_0077A700;
  do {
    if (*(u32 *)(iVar1 + 0x2c) < 0x8f) {
      *(u32 *)(iVar1 + 0x34) = 0;
      func_002A5080((unsigned char *)PS2_PTR(*(int *)(iVar1 + 0x2c) * 0x70 + 0x7733f0),iVar1,uVar2 + 1);
    }
    uVar2 = uVar2 + 1;
    iVar1 = iVar1 + 0x3c;
  } while (uVar2 < 100);
  uVar2 = 0;
  iVar1 = g_007732B0;
  do {
    *(u32 *)(iVar1 + 400) = 0;
    uVar2 = uVar2 + 8;
    *(u32 *)(iVar1 + 0x200) = 0;
    *(u32 *)(iVar1 + 0x270) = 0;
    *(u32 *)(iVar1 + 0x2e0) = 0;
    *(u32 *)(iVar1 + 0x350) = 0;
    *(u32 *)(iVar1 + 0x3c0) = 0;
    *(u32 *)(iVar1 + 0x430) = 0;
    *(u32 *)(iVar1 + 0x4a0) = 0;
    iVar1 = iVar1 + 0x380;
  } while (uVar2 < 0x87);
  iVar1 = (u8 *)PS2_PTR(uVar2 * 0x70);
  *(u32 *)(iVar1 + 0x773440) = 0;
  *(u32 *)(iVar1 + 0x7734b0) = 0;
  *(u32 *)(iVar1 + 0x773520) = 0;
  *(u32 *)(iVar1 + 0x773590) = 0;
  *(u32 *)(iVar1 + 0x773600) = 0;
  *(u32 *)(iVar1 + 0x773670) = 0;
  *(u32 *)(iVar1 + 0x7736e0) = 0;
  return;
}

/* MISSING ['0x411eb0', '0x411eb4', '0x411eb8', '0x411ebc'] */

/* MISSING ['0x411ec0', '0x411ec4', '0x411ec8', '0x411ecc', '0x45cec7'] */

/* MISSING ['0x411ed0', '0x411ed4', '0x411ed8', '0x411edc', '0x411ee0', '0x411ee4'] */

/* MISSING ['0x411ef0', '0x411ef4', '0x411ef8', '0x411efc', '0x411f00', '0x411f04'] */

/* MISSING ['0x795ff0', '0x795ff4', '0x795ff8', '0x795ffc'] */

/* MISSING ['0x795fc4', '0x795fc8', '0x795fcc'] */

/* 0x002C24B0, 0xBC bytes. */
void func_002C24B0(int param_1, u8 *param_2)
{
    u8 auStack_40[64];
    u8 * iVar2;
    int iVar5;
    u16 * puVar3;
    int uVar1;
    u32 uVar4;

  
  iVar2 = func_0027E660((unsigned char *)PS2_PTR(param_1));
  iVar5 = (u32)*(u8 *)(iVar2 + 10) * 0x400 + 0x7957a0;
  iVar2 = func_001FF140(*(u16 *)(param_2 + 0x54));
  uVar1 = *(u16 *)(iVar2 + 4);
  uVar4 = 0;
  puVar3 = (u16 *)(iVar2 + 0x30);
  if (uVar1 != 0) {
    do {
      func_002BB490(iVar5,auStack_40);
      func_001FD4B0(param_1,PS2_ADDR(param_2),*puVar3,PS2_ADDR(auStack_40));
      puVar3 = (u16 *)func_001FF230(puVar3);
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 0x40;
    } while (uVar4 < uVar1);
  }
  return;
}

/* MISSING ['0x795790'] */

/* 0x002D6A40, 0x98 bytes. */
int func_002D6A40(int param_1)
{
    int bVar1;
    int bVar2;
    u8 * iVar5;
    int * piVar3;
    u32 uVar4;

  
  if (param_1 != 0) {
    bVar1 = *(u8 *)PS2_PTR(param_1);
    if ((bVar1 < 0x20) && (bVar2 = ((u8 *)param_1)[1], bVar2 < 0x20)) {
      piVar3 = (int *)PS2_PTR(*(ps2ptr *)(*(int *)(g_0045D2F0 + 4) + ((u32)bVar1 + (u32)bVar2 * 0x20) * 4));
      goto LAB_002d6a98;
    }
  }
  piVar3 = (int *)0x0;
LAB_002d6a98:
  if (piVar3 == (int *)0x0) {
    uVar4 = 0;
  }
  else {
    iVar5 = (u8 *)PS2_PTR(*piVar3);
    uVar4 = 0;
    do {
      if (*(short *)(iVar5 + 0x20) == -1) {
        return uVar4;
      }
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 2;
    } while (uVar4 < 2);
  }
  return uVar4;
}

/* 0x002D6AE0, 0x6C bytes. */
int func_002D6AE0(int param_1, int param_2)
{
    int bVar1;
    int bVar2;
    int * piVar3;

  
  if (((param_1 == 0) || (bVar1 = *(u8 *)PS2_PTR(param_1), 0x1f < bVar1)) ||
     (bVar2 = ((u8 *)param_1)[1], 0x1f < bVar2)) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = (int *)PS2_PTR(*(ps2ptr *)(*(int *)(g_0045D2F0 + 4) + ((u32)bVar1 + (u32)bVar2 * 0x20) * 4));
  }
  return *(u16 *)(param_2 * 2 + *piVar3 + 0x20);
}

/* MISSING ['0x45d610'] */

/* MISSING ['0x45d610'] */

/* MISSING ['0x7a1c10', '0x7a1c14', '0x7a1c18', '0x7a1c1c', '0x7a1e30', '0x7a1e34'] */

/* 0x003298B0, 0x148 bytes. */
void func_003298B0(void)
{
    int bVar3;
    u8 * iVar4;
    int iVar6;
    int iVar7;
    int iVar8;
    u32 * puVar1;
    u32 * puVar5;
    unsigned long long uVar2;

  
  iVar4 = (u8 *)(func_002FC2C0());
  puVar1 = (u32 *)PS2_PTR(*(ps2ptr *)(iVar4 + 0x698));
  puVar5 = (u32 *)func_002F7B10();
  func_002FD490();
  uVar2 = func_00327D50();
  iVar6 = func_002F7D90(0,0x2f8160,uVar2,0,1,0);
  iVar8 = 0;
  if (0 < iVar6) {
    if (8 < iVar6) {
      bVar3 = false;
      if ((-1 < iVar6) && (iVar6 < 0x7fffffff)) {
        bVar3 = true;
      }
      if (bVar3) {
        iVar7 = PS2_ADDR(iVar4);
        do {
          iVar8 = iVar8 + 8;
          *(u32 *)((u8 *)PS2_PTR(iVar7) + 0xc) = *puVar5;
          *(u32 *)((u8 *)PS2_PTR(iVar7) + 0x10) = puVar5[1];
          *(u32 *)((u8 *)PS2_PTR(iVar7) + 0x14) = puVar5[2];
          *(u32 *)((u8 *)PS2_PTR(iVar7) + 0x18) = puVar5[3];
          *(u32 *)((u8 *)PS2_PTR(iVar7) + 0x1c) = puVar5[4];
          *(u32 *)((u8 *)PS2_PTR(iVar7) + 0x20) = puVar5[5];
          *(u32 *)((u8 *)PS2_PTR(iVar7) + 0x24) = puVar5[6];
          *(u32 *)((u8 *)PS2_PTR(iVar7) + 0x28) = puVar5[7];
          puVar5 = puVar5 + 8;
          iVar7 = iVar7 + 0x20;
        } while (iVar8 < iVar6 + -8);
      }
    }
    if (iVar8 < iVar6) {
      iVar7 = PS2_ADDR(iVar4 + iVar8 * 4);
      do {
        iVar8 = iVar8 + 1;
        *(u32 *)((u8 *)PS2_PTR(iVar7) + 0xc) = *puVar5;
        puVar5 = puVar5 + 1;
        iVar7 = iVar7 + 4;
      } while (iVar8 < iVar6);
    }
  }
  func_0032D300(4,PS2_ADDR(iVar4 + 0xc),iVar6);
  *puVar1 = 1;
  return;
}

/* MISSING ['0x45cff0', '0x45cff4', '0x45cff8', '0x45cffc', '0x45d6ec'] */

/* MISSING ['0x45d73c'] */

/* MISSING ['0x45d730'] */

/* 0x00343670, 0x29C bytes. */
int func_00343670(int param_1)
{
    int iVar10;
    int iVar2;
    u8 * iVar3;
    int iVar9;
    long long lVar11;
    long long lVar6;
    long long lVar8;
    int * piVar12;
    int sVar1;
    u32 uVar4;
    u32 uVar5;
    unsigned long long uVar7;

  
  if (param_1 == 0) {
    uVar5 = 0;
  }
  else {
    piVar12 = (int *)param_1;
    if (*(char *)(*piVar12 + 0x79) == '\0') {
      iVar3 = (u8 *)PS2_PTR((int)(piVar12 + -0x1a8756) / 0x68);
      iVar2 = PS2_ADDR(func_00338410(PS2_ADDR(iVar3)));
      if (*(char *)((u8 *)PS2_PTR(iVar2) + 8) == '\x04') {
        iVar2 = PS2_ADDR(func_00338410(PS2_ADDR(iVar3)));
        if (*(char *)((u8 *)PS2_PTR(iVar2) + 2) == '\x04') {
          uVar5 = 0;
        }
        else {
          iVar3 = func_00338410(PS2_ADDR(iVar3));
          if (*(u8 *)(iVar3 + 4) < 0x3c) {
            uVar5 = 0;
          }
          else {
            lVar11 = 0;
            iVar2 = 0;
            iVar3 = g_00669D60;
            do {
              if ((((*(int *)(iVar3 + 0xa0) != 0) && (lVar6 = PS2_ADDR(func_0035DD10(iVar2)), lVar6 != 0)) &&
                  (uVar7 = func_0033D050((unsigned char **)PS2_PTR(param_1),(unsigned char **)PS2_PTR(lVar6)), uVar7 < 4)) &&
                 (lVar8 = func_0033CAA0((unsigned char **)PS2_PTR(lVar6),*(u8 *)(*piVar12 + 0x79)), lVar8 == 0)) {
                iVar10 = iVar2 * 0xc0;
                uVar4 = 0;
                iVar9 = (int)*(short *)(g_006A3AB0 + iVar10);
                if (*(short *)(g_006A3AB0 + iVar10) < 0) {
                  iVar9 = iVar9 + 3;
                }
                lVar8 = (long long)(iVar9 >> 2);
                if (lVar8 < 0x32) {
                  sVar1 = *(short *)(g_006A3AB2 + iVar10);
                }
                else {
                  lVar8 = 0x32;
                  sVar1 = *(short *)(g_006A3AB2 + iVar10);
                }
                if (sVar1 < lVar8) {
                  uVar4 = 3;
                }
                else {
                  iVar9 = (int)*(short *)(g_006A3AB0 + iVar10);
                  if (*(short *)(g_006A3AB0 + iVar10) < 0) {
                    iVar9 = iVar9 + 3;
                  }
                  lVar8 = (long long)(iVar9 >> 2);
                  if (lVar8 < 0x32) {
                    sVar1 = *(short *)(g_006A3AB2 + iVar10);
                  }
                  else {
                    lVar8 = 0x32;
                    sVar1 = *(short *)(g_006A3AB2 + iVar10);
                  }
                  if (sVar1 < lVar8) {
                    uVar4 = 1;
                  }
                }
                g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
                if ((g_7000015C >> 0x10) % 100 < uVar4) {
                  lVar11 = lVar6;
                }
              }
              iVar2 = iVar2 + 1;
              iVar3 = iVar3 + 0x48;
            } while (iVar2 < 2);
            if (lVar11 == 0) {
              uVar5 = 0;
            }
            else {
              func_003386D0((unsigned char **)PS2_PTR(param_1),4,((int)lVar11 + -0x6a1d58) / 0x68);
              uVar5 = 1;
            }
          }
        }
      }
      else {
        uVar5 = 0;
      }
    }
    else {
      uVar5 = 0;
    }
  }
  return uVar5;
}

/* 0x00349DF0, 0x230 bytes. */
void func_00349DF0(u8 *param_1, u8 *param_2, int param_3, int param_4)
{
    u8 auStack_30[44];
    int bStack_3;
    int bStack_4;
    int bVar1;
    u8 * iVar2;
    int iVar7;
    int iVar8;
    int * piVar6;
    int * piVar9;
    int sVar4;
    int sVar5;
    int uVar3;

  
  iVar8 = *(int *)param_1;
  iVar2 = (u8 *)PS2_PTR(*(int *)((u8 *)PS2_PTR(iVar8) + 4));
  bVar1 = *(u8 *)((u8 *)PS2_PTR(iVar8) + 0x79);
  func_00118AC0((unsigned int *)(auStack_30),iVar2,0x20);
  *(u8 *)(iVar2 + 0x17) = 0;
  func_001F1640((unsigned char *)PS2_PTR(param_4),(short int *)(&bStack_4));
  sVar5 = (short)(int)(((float)bStack_4 * 1000.0f + 500.0f) / 100.0f);
  sVar4 = sVar5;
  if (0x63f < sVar5) {
    sVar4 = 0x63f;
  }
  if (sVar4 < 1) {
    sVar5 = 0;
  }
  else if (0x63f < sVar5) {
    sVar5 = 0x63f;
  }
  *(short *)(iVar2 + 2) = sVar5;
  sVar5 = (short)(int)(((float)bStack_3 * 1000.0f + 500.0f) / 100.0f);
  sVar4 = sVar5;
  if (0x63f < sVar5) {
    sVar4 = 0x63f;
  }
  if (sVar4 < 1) {
    *(u16 *)(iVar2 + 4) = 0;
  }
  else {
    if (0x63f < sVar5) {
      sVar5 = 0x63f;
    }
    *(short *)(iVar2 + 4) = sVar5;
  }
  *(u8 *)(iVar2 + 0x11) = 0;
  *(u16 *)(iVar2 + 6) = 500;
  func_00347F20(iVar2,param_2,param_3,0);
  func_00118AC0((unsigned int *)(iVar2),auStack_30,0x20);
  iVar7 = (u32)bVar1 * 4;
  piVar9 = (int *)(iVar7 + 0x6aa5bc);
  *(int *)param_2 = iVar8;
  piVar6 = (int *)(iVar7 + 0x6aa5b0);
  iVar8 = *piVar9 + 1;
  *piVar9 = iVar8;
  if (*piVar6 < iVar8) {
    *piVar6 = iVar8;
  }
  func_001BB5C0(iVar2,param_2,(int *)(param_1));
  ((int *)param_1)[0x13] = 4;
  func_001F1A30(param_2);
  uVar3 = func_0033B970((unsigned char **)(param_1));
  *(u8 *)((int)(int *)param_2 + 0x7f) = uVar3;
  return;
}

/* 0x00372C80, 0x6C bytes. */
int func_00372C80(int param_1, int param_2)
{
    u8 * puVar1;

  
  if ((((param_1 < 0) || (0x38 < param_1)) || (param_2 < 0)) ||
     ((long long)(unsigned long long)(u8)((g_00457B10 + 0x0))[(int)param_1] <= param_2)) {
    puVar1 = (g_004484C0 + 0x0);
  }
  else {
    puVar1 = (u8 *)PS2_PTR(*(ps2ptr *)(((u8 *)PS2_PTR(((ps2ptr *)g_00416370)[(int)param_1])) + (int)param_2 * 4));
  }
  return PS2_ADDR(puVar1);
}

/* MISSING ['0x417468', '0x41746c', '0x417470'] */

/* 0x003914C0, 0x23C bytes. */
void func_003914C0(void)
{
    u8 * iVar1;
    int iVar3;
    int iVar4;
    int * piVar5;
    int sVar2;

  
  iVar1 = func_00391250();
  sVar2 = 0;
  iVar4 = 0;
  iVar3 = PS2_ADDR(iVar1);
  do {
    *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x38) = 0x40;
    iVar4 = iVar4 + 7;
    *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x3c) = 0x40;
    *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x40) = 0x40;
    *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x44) = 0x40;
    *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x48) = 0x40;
    *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x4c) = 0x40;
    *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x50) = 0x40;
    iVar3 = iVar3 + 0x1c;
  } while (iVar4 < 0x10);
  iVar3 = PS2_ADDR(iVar4 * 4 + iVar1);
  *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x38) = 0x40;
  *(u32 *)((u8 *)PS2_PTR(iVar3) + 0x3c) = 0x40;
  iVar3 = *(int *)(iVar1 + 8);
  if (iVar3 == 4) {
    if ((*(u32 *)(g_00418AE0 + 0x80)) != 0x40) {
      piVar5 = (int *)((g_00418AE0 + 0x80));
      iVar3 = PS2_ADDR(iVar1);
      do {
        sVar2 = sVar2 + 1;
        *(int *)((u8 *)PS2_PTR(iVar3) + 0x38) = *piVar5;
        piVar5 = piVar5 + 1;
        iVar3 = iVar3 + 4;
      } while (*piVar5 != 0x40);
    }
  }
  else if (iVar3 == 3) {
    if ((*(u32 *)(g_00418AE0 + 0x60)) != 0x40) {
      piVar5 = (int *)((g_00418AE0 + 0x60));
      iVar3 = PS2_ADDR(iVar1);
      do {
        sVar2 = sVar2 + 1;
        *(int *)((u8 *)PS2_PTR(iVar3) + 0x38) = *piVar5;
        piVar5 = piVar5 + 1;
        iVar3 = iVar3 + 4;
      } while (*piVar5 != 0x40);
    }
  }
  else if (iVar3 == 2) {
    if ((*(u32 *)(g_00418AE0 + 0x40)) != 0x40) {
      piVar5 = (int *)((g_00418AE0 + 0x40));
      iVar3 = PS2_ADDR(iVar1);
      do {
        sVar2 = sVar2 + 1;
        *(int *)((u8 *)PS2_PTR(iVar3) + 0x38) = *piVar5;
        piVar5 = piVar5 + 1;
        iVar3 = iVar3 + 4;
      } while (*piVar5 != 0x40);
    }
  }
  else if (iVar3 == 1) {
    if ((*(u32 *)(g_00418AE0 + 0x20)) != 0x40) {
      piVar5 = (int *)((g_00418AE0 + 0x20));
      iVar3 = PS2_ADDR(iVar1);
      do {
        sVar2 = sVar2 + 1;
        *(int *)((u8 *)PS2_PTR(iVar3) + 0x38) = *piVar5;
        piVar5 = piVar5 + 1;
        iVar3 = iVar3 + 4;
      } while (*piVar5 != 0x40);
    }
  }
  else {
    if (iVar3 != 0) {
      return;
    }
    if ((*(u32 *)(g_00418AE0 + 0x0)) != 0x40) {
      piVar5 = (int *)((g_00418AE0 + 0x0));
      iVar3 = PS2_ADDR(iVar1);
      do {
        sVar2 = sVar2 + 1;
        *(int *)((u8 *)PS2_PTR(iVar3) + 0x38) = *piVar5;
        piVar5 = piVar5 + 1;
        iVar3 = iVar3 + 4;
      } while (*piVar5 != 0x40);
      *(short *)(iVar1 + 0x144) = sVar2;
      goto LAB_003916e8;
    }
  }
  *(short *)(iVar1 + 0x144) = sVar2;
LAB_003916e8:
  *(u16 *)(iVar1 + 0x146) = 9;
  return;
}

/* MISSING ['0x7ba7f8'] */

/* 0x0039F340, 0x23C bytes. */
void func_0039F340(void)
{
    int bVar1;
    int bVar2;
    int bVar3;
    u8 * iVar4;
    int iVar5;
    int iVar7;
    int iVar9;
    long long lVar6;
    u32 * puVar8;

  
  iVar4 = (u8 *)(func_002FC2C0());
  iVar4 = (u8 *)PS2_PTR(*(int *)(iVar4 + 0x694));
  func_0011ED38(iVar4 + 0x1e0,0,0x30);
  iVar9 = 0;
  do {
    if (((iVar9 != 0x13) && (lVar6 = func_003A01A0(iVar9), lVar6 != 0)) &&
       (lVar6 = func_00313CB0(iVar9), lVar6 < 0xc)) {
      iVar7 = PS2_ADDR(iVar4 + (int)lVar6 * 4);
      *(int *)(iVar4 + (int)lVar6 * 0x28 + *(int *)((u8 *)PS2_PTR(iVar7) + 0x1e0) * 4) = iVar9;
      *(int *)((u8 *)PS2_PTR(iVar7) + 0x1e0) = *(int *)((u8 *)PS2_PTR(iVar7) + 0x1e0) + 1;
    }
    iVar9 = iVar9 + 1;
  } while (iVar9 < 100);
  iVar7 = 0;
  bVar2 = true;
  iVar9 = PS2_ADDR(iVar4);
  do {
    iVar5 = *(int *)(iVar4 + 0x1e0);
    if (iVar5 < 10) {
      if (8 < 10 - iVar5) {
        bVar1 = false;
        if ((iVar5 < 0xb) && (iVar5 < 0x7fffffff)) {
          bVar1 = bVar2;
        }
        bVar3 = false;
        if ((bVar1) && (*(int *)(iVar4 + 0x1e0) != -0x80000000)) {
          bVar3 = bVar2;
        }
        bVar1 = false;
        if (bVar3) {
          bVar3 = bVar2;
          if (((-*(int *)(iVar4 + 0x1e0) & 0x80000000U) == 0) &&
             ((10U - *(int *)(iVar4 + 0x1e0) & 0x80000000) != 0)) {
            bVar3 = false;
          }
          if (bVar3) {
            bVar1 = bVar2;
          }
        }
        if (bVar1) {
          puVar8 = (u32 *)(iVar9 + iVar5 * 4);
          do {
            *puVar8 = 100;
            puVar8[1] = 100;
            iVar5 = iVar5 + 8;
            puVar8[2] = 100;
            puVar8[3] = 100;
            puVar8[4] = 100;
            puVar8[5] = 100;
            puVar8[6] = 100;
            puVar8[7] = 100;
            puVar8 = puVar8 + 8;
          } while (iVar5 < 2);
        }
      }
      if (iVar5 < 10) {
        puVar8 = (u32 *)(iVar9 + iVar5 * 4);
        do {
          iVar5 = iVar5 + 1;
          *puVar8 = 100;
          puVar8 = puVar8 + 1;
        } while (iVar5 < 10);
      }
    }
    iVar7 = iVar7 + 1;
    iVar4 = iVar4 + 4;
    iVar9 = iVar9 + 0x28;
  } while (iVar7 < 0xc);
  func_0039EFB0(0);
  func_0039EF80(0);
  (*(u32 *)(g_007BAC08 + 0x0)) = 0x3f800000;
  (*(u8 *)(g_007BAC08 + 0x5)) = (*(u8 *)(g_007BAC08 + 0x5)) & 0xfe;
  return;
}

/* 0x003AAD30, 0x244 bytes. */
void func_003AAD30(void)
{
    int bVar1;
    int bVar2;
    int bVar3;
    u8 * iVar4;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    int * piVar5;

  
  iVar4 = func_0021A630();
  iVar6 = 0;
  do {
    iVar9 = 0;
    iVar7 = PS2_ADDR(iVar4 + iVar6 * 4);
    piVar5 = (int *)(iVar7 + 0x167c);
    if (0 < *(int *)((u8 *)PS2_PTR(iVar7) + 0x167c)) {
      iVar8 = PS2_ADDR(iVar4 + iVar6 * 0x30);
      do {
        *(u32 *)((u8 *)PS2_PTR(iVar8) + 0x1684) = 0xd;
        iVar9 = iVar9 + 1;
        iVar8 = iVar8 + 8;
      } while (iVar9 < *piVar5);
    }
    iVar9 = 0;
    if (0 < *(int *)((u8 *)PS2_PTR(iVar7) + 0x16e4)) {
      iVar8 = PS2_ADDR(iVar4 + iVar6 * 0x30);
      do {
        *(u32 *)((u8 *)PS2_PTR(iVar8) + 0x1688) = 0x11;
        iVar9 = iVar9 + 1;
        iVar8 = iVar8 + 8;
      } while (iVar9 < *(int *)((u8 *)PS2_PTR(iVar7) + 0x16e4));
    }
    iVar7 = *piVar5;
    if (iVar7 < 6) {
      if (8 < 6 - iVar7) {
        bVar3 = false;
        bVar2 = false;
        bVar1 = false;
        if ((iVar7 < 7) && (iVar7 < 0x7fffffff)) {
          bVar1 = true;
        }
        if ((bVar1) && (*piVar5 != -0x80000000)) {
          bVar2 = true;
        }
        if (bVar2) {
          bVar1 = true;
          if (((-*piVar5 & 0x80000000U) == 0) && ((6U - *piVar5 & 0x80000000) != 0)) {
            bVar1 = false;
          }
          if (bVar1) {
            bVar3 = true;
          }
        }
        if (bVar3) {
          iVar9 = PS2_ADDR(iVar4 + iVar6 * 0x30 + iVar7 * 8);
          do {
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x1684) = 4;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x1688) = 0x12;
            iVar7 = iVar7 + 8;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x168c) = 4;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x1690) = 0x12;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x1694) = 4;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x1698) = 0x12;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x169c) = 4;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x16a0) = 0x12;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x16a4) = 4;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x16a8) = 0x12;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x16ac) = 4;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x16b0) = 0x12;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x16b4) = 4;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x16b8) = 0x12;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x16bc) = 4;
            *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x16c0) = 0x12;
            iVar9 = iVar9 + 0x40;
          } while (iVar7 < -2);
        }
      }
      if (iVar7 < 6) {
        iVar9 = PS2_ADDR(iVar4 + iVar6 * 0x30 + iVar7 * 8);
        do {
          *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x1684) = 4;
          iVar7 = iVar7 + 1;
          *(u32 *)((u8 *)PS2_PTR(iVar9) + 0x1688) = 0x12;
          iVar9 = iVar9 + 8;
        } while (iVar7 < 6);
      }
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 2);
  return;
}

/* MISSING ['0x45d7fc'] */

/* MISSING ['0x41c160', '0x41c164', '0x41c168', '0x41c16c', '0x41c170', '0x41c174', '0x41c178', '0x41c17c'] */

/* MISSING ['0x41c400', '0x41c404', '0x41c408', '0x41c40c'] */

/* 0x003DE3A0, 0x1DC bytes. */
void func_003DE3A0(int param_1, int param_2)
{
    int iVar1;
    u8 * iVar2;
    int iVar3;
    int iVar5;
    int iVar6;
    int iVar7;
    int uStack_4;
    unsigned long long uVar4;

  
  iVar2 = func_0021A630();
  func_002C7310(param_1,param_2,0,0x98,0xb3,0x80,0);
  (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41a00000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41a00000;
  uVar4 = PS2_ADDR(func_00372B30());
  func_00146270((const unsigned char *)PS2_PTR(uVar4),(int)param_1 + 0x10,(int)param_2 + 8,0,0);
  (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
  (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
  (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
  (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
  iVar1 = *(int *)(*(int *)(iVar2 + 0x1c) * 4 + iVar2 + 0x167c);
  iVar7 = 0;
  if ((0 < iVar1) && (0 < iVar1)) {
    iVar5 = (int)param_2 + 0x1d;
    iVar6 = 0;
    do {
      iVar3 = PS2_ADDR(iVar2 + *(int *)(iVar2 + 0x1c) * 0x30 + iVar6);
      uStack_4 = (u8)*(u32 *)((u8 *)PS2_PTR(iVar3) + 0x16f0);
      func_003DDFB0(iVar7,(int)param_1 + 0x10,iVar5,*(u32 *)((u8 *)PS2_PTR(iVar3) + 0x16ec),uStack_4);
      iVar7 = iVar7 + 1;
      iVar6 = iVar6 + 8;
      iVar5 = iVar5 + 0x18;
    } while (iVar7 < iVar1);
  }
  func_003B4720(0x10,0x130,0,2);
  if ((*(int *)(iVar2 + 0x1178) == 6) && (*(int *)(iVar2 + 0x1174) == 0)) {
    func_002C6040(0xffffffffffffffd4,0x12e,0x100,0x1c,1,0x80);
  }
  return;
}

/* MISSING ['0x41d008', '0x41d00c', '0x41d010'] */

/* MISSING ['0x41d2e0', '0x41d2e4', '0x41d2e8', '0x41d2ec'] */
