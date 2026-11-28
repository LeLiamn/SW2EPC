/*
 * gen23_180000.c - functions between 0x00180000 and 0x003F9680, generated from Ghidra
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
int func_00184FA0(void);
void func_00185210(void);
void func_00187F20(u16 *param_1);
void func_00188740(u8 *param_1);
void func_001887A0(u16 *param_1);
void func_0018A290(short *param_1, int param_2, int param_3);
void func_0018DA60(u8 *param_1, int *param_2, int param_3);
void func_00195EF0(void);
int func_001BBEA0(void);
void func_001C3800(u32 *param_1, int param_2);
void func_001C3890(float *param_1, int param_2);
void func_001C4D10(int param_1, float *param_2);
void func_001C66C0(u8 *param_1);
void func_001C7730(void);
void func_001C7CE0(void);
int func_001C7DB0(int param_1, int param_2, int param_3);
void func_001C8CF0(int param_1);
int func_001CAC90(int param_1, u32 *param_2, u8 *param_3, int param_4);
void func_001CF430(float param_1, u8 *param_2, int param_3);
void func_001D0C20(u8 *param_1, int param_2);
void func_001D1B50(u8 *param_1);
int func_001D6C70(u8 *param_1);
void func_001D73A0(u8 *param_1);
void func_001D7470(float param_1, int param_2);
void func_001D7670(int param_1);
void func_001D76F0(void);
void func_001DD350(int param_1, int param_2, int param_3);
void func_001DE980(u8 *param_1);
void func_001E01D0(float param_1, int param_2);
void func_001E0B40(int param_1, int param_2);
void func_001E0E60(int param_1, int param_2);
void func_001E10D0(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_001E1380(int param_1);
void func_001E9850(int param_1);
void func_001E98E0(int param_1);
void func_001E9980(void);
void func_001EC180(u8 *param_1);
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
void func_001EE3B0(u8 *param_1);
void func_001EE970(int param_1);
int func_001EF6B0(u8 *param_1, u8 *param_2, int param_3, int param_4);
int func_001EFD50(u8 *param_1, u8 *param_2);
void func_001F0540(void);
void func_001F5EB0(u8 *param_1, int param_2);
int func_001F62C0(u8 *param_1);
void func_001F6FF0(void);
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
void func_0020ECE0(void);
void func_0020ED30(void);
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
void func_0022F510(void);
void func_0022F730(int param_1);
void func_00236FC0(void);
void func_00237200(u8 *param_1);
void func_00237410(u8 *param_1);
void func_00237550(u8 *param_1);
int func_00237800(int param_1);
int func_00237D00(u8 *param_1);
void func_00239E60(u8 *param_1);
void func_0023A0C0(u8 *param_1);
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
void func_00247970(void);
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
void func_002787E0(void);
void func_002788F0(void);
void func_00278A20(void);
void func_00278CF0(void);
void func_00278FC0(int param_1, u16 *param_2, int param_3);
void func_00279010(int param_1, short *param_2, int param_3, int param_4, int param_5);
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
void func_002863E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
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
void func_00290390(int param_1, int param_2, int param_3, int param_4);
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
void func_0029D230(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_0029D520(int param_1, int param_2, int param_3);
void func_0029D6F0(u8 *param_1);
void func_0029DD90(int param_1, int param_2, int param_3, float param_4, float param_5);
void func_0029DDE0(int param_1, int param_2, int param_3, float param_4, float param_5);
void func_0029DEF0(int param_1, int param_2);
void func_002A5B10(int param_1);
void func_002A5D70(int param_1, int param_2, int param_3);
void func_002A5FD0(int param_1, int param_2);
void func_002A6430(void);
void func_002A6470(void);
int func_002A71A0(int param_1, u8 *param_2, int param_3);
void func_002A7560(void);
void func_002A7CE0(void);
void func_002A85F0(int param_1, int param_2, int param_3, int param_4);
void func_002A86A0(int param_1);
void func_002A9610(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
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
void func_002CE160(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
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
void func_002D68F0(void);
void func_002D6990(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_002D7970(u8 *param_1);
void func_002D7C60(int param_1, u8 *param_2, int param_3);
void func_002D7E30(u8 *param_1);
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
void func_002E0000(int param_1);
void func_002E0040(int param_1);
void func_002E05C0(int param_1, int param_2, int param_3);
void func_002E1820(u8 *param_1);
float func_002E38D0(u8 *param_1);
void func_002E41F0(int param_1, u8 *param_2);
void func_002E5810(void);
int func_002E59C0(u32 *param_1);
int func_002E5A40(u32 *param_1);
void func_002E6070(int param_1, int param_2, int param_3, int param_4);
void func_002E67B0(void);
void func_002E6800(int param_1, int param_2, int param_3, int param_4);
int func_002ECA70(void);
void func_002EF080(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
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
void func_0036EB40(void);
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
int func_00382620(void);
void func_00383270(int param_1, int param_2, int param_3);
void func_003832E0(int param_1, int param_2, int param_3, int param_4);
void func_00383330(int param_1, int param_2);
void func_00383360(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);
void func_00383610(int param_1, int param_2, int param_3, int param_4);
void func_00383650(int param_1, int param_2, int param_3, int param_4, int param_5, int *param_6, int *param_7);
void func_00383880(int param_1, int param_2);
void func_00383A80(int param_1, int param_2);
void func_00383AB0(int param_1, int param_2, int param_3, int param_4, int param_5);
void func_00383D80(u32 *param_1);
void func_00383E00(int param_1);
void func_003852A0(void);
void func_00386520(int param_1);
void func_00388200(int param_1, int param_2);
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
void func_0038F560(void);
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
void func_003A0220(int param_1, int param_2);
void func_003A2940(int param_1, int param_2);
void func_003A34C0(void);
void func_003A5E20(void);
void func_003A63D0(int param_1);
void func_003A6450(int *param_1, int *param_2);
void func_003A70D0(void);
void func_003A7360(void);
void func_003A86F0(u8 *param_1);
void func_003A8B90(void);
void func_003AEF30(int param_1);
void func_003AF040(void);
void func_003B34A0(int param_1);
void func_003B3E70(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void func_003B4180(int param_1, int param_2, int param_3, int param_4, int *param_5, u16 *param_6, u8 *param_7, int param_8);
void func_003B4EC0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void func_003B4F50(int param_1);
void func_003B56E0(int param_1, int param_2);
void func_003B5CC0(int param_1, int param_2, int param_3, int param_4);
void func_003B69A0(void);
int func_003B9770(int param_1);
void func_003BC150(void);
void func_003BCDD0(void);
void func_003BD7A0(void);
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

/* MISSING ['0x406940', '0x406944', '0x406948', '0x40694c', '0x406950', '0x406954', '0x406958', '0x40695c', '0x406960', '0x406964', '0x406968'] */

/* 0x001C39A0, 0xC0 bytes. */
void func_001C39A0(int param_1, int param_2)
{
    u8 * iVar1;
    int * piVar2;

  
  func_001C51A0(param_1,param_2 + 0x20);
  if (*(int *)((u8 *)PS2_PTR(param_2) + 0x2c4) != 0x30) {
    func_002A8030(*(int *)((u8 *)((u8 *)PS2_PTR(param_2)) + 0x2c4));
  }
  piVar2 = (int *)param_1;
  if (*piVar2 == param_2) {
    *piVar2 = *(int *)((u8 *)PS2_PTR(param_2) + 0x14);
    if (*(int *)((u8 *)PS2_PTR(param_2) + 0x14) != 0) {
      *(u32 *)(*(int *)((u8 *)PS2_PTR(param_2) + 0x14) + 0x10) = 0;
    }
    if (piVar2[1] == param_2) {
      piVar2[1] = 0;
    }
  }
  else if (piVar2[1] == param_2) {
    iVar1 = (u8 *)PS2_PTR(*(int *)((u8 *)PS2_PTR(param_2) + 0x10));
    piVar2[1] = PS2_ADDR(iVar1);
    *(u32 *)(iVar1 + 0x14) = 0;
  }
  else {
    *(u32 *)(*(int *)((u8 *)PS2_PTR(param_2) + 0x10) + 0x14) = *(u32 *)((u8 *)PS2_PTR(param_2) + 0x14);
    *(u32 *)(*(int *)((u8 *)PS2_PTR(param_2) + 0x14) + 0x10) = *(u32 *)((u8 *)PS2_PTR(param_2) + 0x10);
  }
  func_001CB640((unsigned char *)PS2_PTR(param_2));
  return;
}

/* MISSING ['0x730560', '0x730564', '0x730568'] */

/* 0x001D7420, 0x4C bytes. */
void func_001D7420(u8 *param_1)
{
    int bVar1;

  
  bVar1 = *(u8 *)(*(int *)(param_1 + 8) + 5);
  if (bVar1 < 6) {
    if ((void *)((u8 *)PS2_PTR(((ps2ptr *)g_0040C920)[bVar1])) != (void *)0x0) {
      ((int (*)())((u8 *)PS2_PTR(((ps2ptr *)g_0040C920)[bVar1])))();
    }
  }
  return;
}

/* MISSING ['0x730560', '0x730564', '0x730568', '0x73056c'] */

/* MISSING ['0x45d3e0'] */

/* 0x001E3260, 0x4C bytes. */
void func_001E3260(u8 *param_1)
{
    int bVar1;

  
  bVar1 = *(u8 *)(*(int *)(param_1 + 8) + 5);
  if (bVar1 < 0xd) {
    if ((void *)((u8 *)PS2_PTR(((ps2ptr *)g_0040CBC0)[bVar1])) != (void *)0x0) {
      ((int (*)())((u8 *)PS2_PTR(((ps2ptr *)g_0040CBC0)[bVar1])))();
    }
  }
  return;
}

/* 0x001E32B0, 0x4C bytes. */
void func_001E32B0(u8 *param_1)
{
    int bVar1;

  
  bVar1 = *(u8 *)(*(int *)(param_1 + 8) + 5);
  if (bVar1 < 8) {
    if ((void *)((u8 *)PS2_PTR(((ps2ptr *)g_0040CC00)[bVar1])) != (void *)0x0) {
      ((int (*)())((u8 *)PS2_PTR(((ps2ptr *)g_0040CC00)[bVar1])))();
    }
  }
  return;
}

/* MISSING ['0x40cff0', '0x40cff4', '0x40cff8', '0x40cffc', '0x40d000', '0x40d004', '0x40d008', '0x40d00c', '0x40d010', '0x40d014'] */

/* MISSING ['0x45d2c0'] */

/* 0x0020DDF0, 0x110 bytes. */
void func_0020DDF0(int param_1, int param_2)
{
    int bVar1;
    int bVar3;
    u8 * iVar5;
    u32 * puVar2;
    u32 uVar4;

  
  func_001185B0((void *)PS2_PTR(0x700001e0),0x50);
  iVar5 = g_0079FE10;
  bVar3 = 0;
  if (g_70000709 != 0) {
    do {
      if ((*(u8 *)(iVar5 + 2) & 0x80) != 0) {
        for (puVar2 = ((u32 *)PS2_PTR(*(ps2ptr *)(iVar5 + 4))); puVar2 != (u32 *)0x0; puVar2 = (u32 *)puVar2[1]) {
          uVar4 = 1 << (*puVar2 & 7);
          bVar1 = (&g_700001E0)[*puVar2 >> 3];
          if ((uVar4 & 0xff & (u32)bVar1) == 0) {
            (&g_700001E0)[*puVar2 >> 3] = bVar1 | (u8)uVar4;
            ((int (*)())((u8 *)PS2_PTR(((ps2ptr *)g_0040D270)[param_2])))(param_1);
          }
        }
      }
      bVar3 = bVar3 + 1;
      iVar5 = iVar5 + 0x50;
    } while (bVar3 < g_70000709);
  }
  return;
}

/* MISSING ['0x73dc68', '0x73dc6c', '0x73def8', '0x73defc'] */

/* MISSING ['0x73df04'] */

/* MISSING ['0x45d488'] */

/* MISSING ['0x45cda8', '0x73f350', '0x73f354', '0x73f358', '0x73f35c'] */

/* MISSING ['0x45d2c0'] */

/* MISSING ['0x45d1f0'] */

/* MISSING ['0x45cdb8', '0x45d4a0'] */

/* MISSING ['0x40e940', '0x40e944', '0x40e948', '0x40e94c', '0x40e950', '0x40e954', '0x40e958', '0x40e95c', '0x40e960', '0x40e964'] */

/* MISSING ['0x5bc03c', '0x693703'] */

/* MISSING ['0x5bc050', '0x5bc054', '0x692da0', '0x692da4'] */

/* MISSING ['0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c'] */

/* MISSING ['0x410ac0', '0x410ac4', '0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x5b4fc0', '0x5b4fc4', '0x5b4fc8', '0x5b4fd0', '0x5b4fd4', '0x5b4fd8', '0x5b5020', '0x5b5024', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c', '0x76ec80', '0x76ec84', '0x76ec88', '0x76ec8c', '0x76ec90', '0x76ec94', '0x76ec98', '0x76ec9c'] */

/* 0x00256580, 0x94 bytes. */
void func_00256580(u8 *param_1)
{
    int iVar1;
    int iVar2;

  
  iVar2 = 0;
  iVar1 = PS2_ADDR(param_1);
  do {
    if ((*(int *)(param_1 + 0x38) != 0) &&
       ((long long)*(char *)(*(int *)(param_1 + 0x38) + 0x19c) << 0x3e < 0)) {
      func_001D0E60(*(int *)((u8 *)(param_1) + 0x38));
    }
    if (iVar1 != -0x150) {
      *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x188) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x188) | 8;
    }
    iVar2 = iVar2 + 1;
    param_1 = param_1 + 4;
    iVar1 = iVar1 + 0x120;
  } while (iVar2 < 4);
  g_0045D374 = 2;
  return;
}

/* MISSING ['0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c'] */

/* MISSING ['0x410ac0', '0x410ac4', '0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x5b4fc0', '0x5b4fc4', '0x5b4fc8', '0x5b4fd0', '0x5b4fd4', '0x5b4fd8', '0x5b5020', '0x5b5024', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c', '0x76ec80', '0x76ec84', '0x76ec88', '0x76ec8c', '0x76ec90', '0x76ec94', '0x76ec98', '0x76ec9c'] */

/* 0x00259670, 0xCC bytes. */
void func_00259670(int param_1)
{
    int iVar1;
    u8 * iVar2;
    int iVar3;

  
  iVar3 = 0;
  iVar2 = (u8 *)PS2_PTR(param_1);
  iVar1 = param_1;
  do {
    if ((*(int *)(iVar2 + 0x38) != 0) &&
       ((long long)*(char *)(*(int *)(iVar2 + 0x38) + 0x19c) << 0x3e < 0)) {
      func_001D0E60(*(int *)((u8 *)((u8 *)PS2_PTR(param_1)) + 0x38));
    }
    if (iVar1 != -0x150) {
      *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x188) = *(u32 *)((u8 *)PS2_PTR(iVar1) + 0x188) | 8;
    }
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 4;
    iVar1 = iVar1 + 0x120;
  } while (iVar3 < 4);
  if (param_1 != -0x5d0) {
    *(u32 *)((u8 *)PS2_PTR(param_1) + 0x608) = *(u32 *)((u8 *)PS2_PTR(param_1) + 0x608) | 8;
  }
  g_0045D374 = 2;
  if (*(int *)((u8 *)PS2_PTR(param_1) + 0x38) != 0) {
    func_003E2B30(*(u8 *)(*(int *)((u8 *)PS2_PTR(param_1) + 0x38) + 0x14e));
  }
  return;
}

/* MISSING ['0x76f790', '0x76f794', '0x76f798', '0x76f79c', '0x76f7a0', '0x76f7a4', '0x76f7a8', '0x76f7ac', '0x76f7b8'] */

/* MISSING ['0x43fe50'] */

/* 0x0027F610, 0xB8 bytes. */
void func_0027F610(void)
{
    int iVar2;
    int * piVar1;
    int * piVar5;
    u8 ** ppuVar4;
    unsigned long long uVar3;
    u32 uVar6;

  
  uVar3 = PS2_ADDR(func_001026D0(1,0x3f,0,1,0,0,(const char *)PS2_PTR(0x440420),0x691));
  uVar6 = 0;
  piVar5 = (int *)((int)uVar3 + 4);
  ppuVar4 = (u8 **)(g_0043FE40);
  do {
    iVar2 = *piVar5;
    piVar1 = piVar5 + 1;
    piVar5 = piVar5 + 2;
    if ((void *)*ppuVar4 != (void *)0x0) {
      ((int (*)())*ppuVar4)((int)uVar3 + iVar2,*piVar1);
    }
    uVar6 = uVar6 + 1;
    ppuVar4 = ppuVar4 + 0xc;
  } while (uVar6 < 0x1f);
  func_00102EC0((unsigned char *)PS2_PTR(uVar3));
  g_0045D55C = PS2_ADDR(func_002C44E0());
  g_0045D558 = PS2_ADDR(func_002C44F0());
  return;
}

/* MISSING ['0x4112a0', '0x4112a4', '0x4112a8', '0x4112ac', '0x4112b0', '0x4112b4', '0x4112b8', '0x4112bc', '0x4112c0'] */

/* 0x00290770, 0x498 bytes. */
void func_00290770(int param_1, int param_2, int param_3, int param_4)
{
    int aiStack_30[4];
    ps2ptr apuStack_10[4];
    ps2ptr apuStack_50[4];
    u32 auStack_20[4];
    u8 auStack_d0[128];
    int iStack_f0;
    int iVar1;
    u8 * iVar10;
    int iVar11;
    u8 * iVar5;
    int iVar6;
    int iVar8;
    int iVar9;
    long long lVar2;
    int * piVar4;
    u8 ** ppuVar7;
    u8 * puStack_3c;
    u8 * puStack_40;
    unsigned long long uVar3;

  
  iVar9 = 0;
  ppuVar7 = (u8 **)(apuStack_10);
  iVar6 = 0;
  piVar4 = aiStack_30;
  apuStack_10[0] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_004114B0)));
  apuStack_10[1] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_004114B4)));
  apuStack_50[0] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_004114C0)));
  apuStack_10[2] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_004114B8)));
  apuStack_50[1] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_004114C4)));
  apuStack_50[2] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_004114C8)));
  apuStack_50[3] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_004114CC)));
  puStack_40 = ((u8 *)PS2_PTR(*(ps2ptr *)g_004114D0));
  puStack_3c = ((u8 *)PS2_PTR(*(ps2ptr *)g_004114D4));
  auStack_20[0] = (*(u32 *)(g_004114D8 + 0x0));
  auStack_20[1] = (*(u32 *)(g_004114D8 + 0x4));
  auStack_20[2] = (*(u32 *)(g_004114D8 + 0x8));
  do {
    lVar2 = ((int (*)())*ppuVar7)();
    if (lVar2 != 0) {
      *piVar4 = iVar9;
      iVar6 = iVar6 + 1;
      piVar4 = piVar4 + 1;
    }
    iVar9 = iVar9 + 1;
    ppuVar7 = ppuVar7 + 1;
  } while (iVar9 < 3);
  if (iVar6 != 0) {
    func_002C7310(param_1,param_2,param_3,0xb8,iVar6 * 0x28 + 0x1f,0x80,param_4);
    uVar3 = func_00106C90((*(unsigned long long *)(g_0068F0F8 + 0x0)),0x3f6d);
    uVar3 = PS2_ADDR(func_00105860(uVar3,0));
    iVar10 = (u8 *)PS2_PTR((int)uVar3);
    *(unsigned long long *)(iVar10 + 0x20) = 0x3f80000080808080;
    *(unsigned long long *)(iVar10 + 0x28) = 0x1d4806c8;
    *(unsigned long long *)(iVar10 + 0x38) = 0x1ec80bc8;
    iVar9 = (((param_2 + 3) * 0x280) / 0x1e0) * 0x1c0;
    if (iVar9 < 0) {
      iVar9 = iVar9 + 0x1ff;
    }
    iVar8 = (int)param_1;
    *(unsigned long long *)(iVar10 + 0x30) =
         (long long)((iVar8 + 0x10) * 0x10 + 0x7000) |
         (long long)(((iVar9 >> 9) * 0x10 + -0xe00) / g_70000154 + 0x8000) << 0x10 | 0xfffe00000000;
    *(unsigned long long *)(iVar10 + 0x40) =
         (long long)((iVar8 + 0x60) * 0x10 + 0x7000) |
         (long long)((((iVar9 >> 9) + 0x1c) * 0x10 + -0xe00) / g_70000154 + 0x8000) << 0x10 |
         0xfffe00000000;
    func_00105900((unsigned char *)PS2_PTR(uVar3),param_4);
    iVar9 = 0;
    if (0 < iVar6) {
      piVar4 = aiStack_30;
      iVar5 = (u8 *)PS2_PTR(param_2 + 0x1c);
      iVar11 = param_2 + 0x1d;
      iStack_f0 = param_2 + 0x2d;
      iVar10 = iVar5;
      do {
        iVar1 = *piVar4;
        func_002C80A0(iVar8 + 8,PS2_ADDR(iVar5),param_3,0xa8,0x24,0x80,param_4);
        func_003B5820(auStack_20[iVar1],iVar8 + 0x12,PS2_ADDR(iVar10),0,0x80,param_4);
        ((int (*)())apuStack_50[iVar1 * 2])(auStack_d0);
        (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        func_00146B40(auStack_d0,iVar8 + 0x34,iVar11,0x7a,0x10,param_4,0);
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
        ((int (*)())apuStack_50[iVar1 * 2 + 1])(auStack_d0);
        (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        func_00146B40(auStack_d0,iVar8 + 0x34,iStack_f0,0x7a,0x10,param_4,0);
        (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
        iVar9 = iVar9 + 1;
        (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
        piVar4 = piVar4 + 1;
        (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
        iVar5 = iVar5 + 0x28;
        (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
        (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
        iVar10 = iVar10 + 0x28;
        (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
        iStack_f0 = iStack_f0 + 0x28;
        iVar11 = iVar11 + 0x28;
      } while (iVar9 < iVar6);
    }
  }
  return;
}
/* MISSING ['0x4114d8', '0x4114dc', '0x4114e0'] */

/* MISSING ['0x411820', '0x411824', '0x411828', '0x41182c', '0x411830', '0x411834', '0x411838', '0x41183c', '0x411840', '0x411844', '0x411848', '0x41184c', '0x411850', '0x411854', '0x411858', '0x41185c'] */

/* MISSING ['0x411890', '0x411894', '0x411898', '0x41189c'] */

/* MISSING ['0x411980', '0x411984', '0x411988', '0x41198c', '0x411990', '0x411994', '0x411998', '0x41199c', '0x4119a0', '0x4119a4'] */

/* 0x0029CC10, 0x5C bytes. */
void func_0029CC10(int param_1, int param_2, u8 *param_3)
{
    ps2ptr apuStack_10[4];

  
  apuStack_10[0] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_00411B40)));
  apuStack_10[1] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_00411B44)));
  apuStack_10[2] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_00411B48)));
  apuStack_10[3] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_00411B4C)));
  ((int (*)())apuStack_10[*(u8 *)(param_3 + 0x58)])();
  return;
}

/* MISSING ['0x411b50', '0x411b54', '0x411b58'] */

/* MISSING ['0x411eb0', '0x411eb4', '0x411eb8', '0x411ebc'] */

/* MISSING ['0x411ec0', '0x411ec4', '0x411ec8', '0x411ecc', '0x45cec7'] */

/* MISSING ['0x411ed0', '0x411ed4', '0x411ed8', '0x411edc', '0x411ee0', '0x411ee4'] */

/* MISSING ['0x411ef0', '0x411ef4', '0x411ef8', '0x411efc', '0x411f00', '0x411f04'] */

/* MISSING ['0x795ff0', '0x795ff4', '0x795ff8', '0x795ffc'] */

/* MISSING ['0x795fc4', '0x795fc8', '0x795fcc'] */

/* MISSING ['0x795790'] */

/* MISSING ['0x45d610'] */

/* MISSING ['0x45d610'] */

/* MISSING ['0x7a1c10', '0x7a1c14', '0x7a1c18', '0x7a1c1c', '0x7a1e30', '0x7a1e34'] */

/* MISSING ['0x45cff0', '0x45cff4', '0x45cff8', '0x45cffc', '0x45d6ec'] */

/* 0x0032D9C0, 0xD94 bytes. */
int func_0032D9C0(void)
{
    int iVar4;
    int iVar6;
    long long lVar3;
    long long lVar5;
    int uVar1;
    int uVar2;

  
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar1 = 0;
  }
  else {
    uVar1 = (*(u16 *)(g_0050074C + 0x0));
  }
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar2 = 0;
  }
  else {
    uVar2 = (*(u16 *)(g_0050074C + 0x2));
  }
  lVar3 = func_003F1070(2);
  if (lVar3 == 0) {
    if ((*(u32 *)(g_007B5E20 + 0x8)) == 0) {
      if ((*(u32 *)(g_007B5E20 + 0x10)) == 0) {
        if ((*(u32 *)(g_007B5E20 + 0x14)) == 0) {
          if ((*(u32 *)(g_007B5E20 + 0xC)) == 0) {
            if ((*(u32 *)(g_007B5E20 + 0x0)) == 2) {
              if ((uVar1 & 0x20) == 0) {
                if ((uVar1 & 0x80) == 0) {
                  if ((uVar1 & 0x10) != 0) {
                    func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
                    if ((*(u32 *)(g_007B5E20 + 0x1C)) != 0) {
                      func_003A9480(0);
                    }
                    return 0;
                  }
                }
                else {
                  func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
                  (*(u32 *)(g_007B5E20 + 0xC)) = 1;
                }
              }
              else {
                func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
                (*(u32 *)(g_007B5E20 + 0x8)) = 1;
              }
            }
            else if ((uVar1 & 0x20) == 0) {
              if ((uVar1 & 0x80) == 0) {
                if ((uVar1 & 0x40) != 0) {
                  func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
                  if ((*(u32 *)(g_007B5E20 + 0x1C)) != 0) {
                    if ((*(u32 *)(g_007B5E20 + 0x4)) == 0) {
                      func_003A9480(0);
                    }
                    else {
                      func_003A94D0();
                    }
                  }
                  return 1;
                }
                if ((((uVar1 & 0x10) != 0) && ((*(u32 *)(g_007B5E20 + 0x0)) != 0xb)) && ((*(u32 *)(g_007B5E20 + 0x0)) != 0xc)) {
                  func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
                  if ((*(u32 *)(g_007B5E20 + 0x1C)) != 0) {
                    func_003A9480(0);
                  }
                  return 0;
                }
              }
              else {
                func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
                (*(u32 *)(g_007B5E20 + 0xC)) = 1;
              }
            }
            else {
              func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
              (*(u32 *)(g_007B5E20 + 0x8)) = 1;
            }
            if ((uVar2 & 0x4000) == 0) {
              if ((uVar2 & 0x1000) == 0) {
                if ((uVar2 & 0x2000) == 0) {
                  if ((uVar2 & 0x8000) == 0) {
                    if (((uVar1 & 4) != 0) || ((uVar1 & 8) != 0)) {
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      if (g_0045D6F8 == 0) {
                        g_0045D6F8 = 1;
                      }
                      else {
                        g_0045D6F8 = 0;
                      }
                    }
                  }
                  else if ((*(short *)(g_007B5E20 + 0x28)) < (*(short *)(g_007B5E20 + 0x26))) {
                    if (((*(u16 *)(g_007B5E20 + 0x24)) != 0) || ((*(u16 *)(g_007B5E20 + 0x22)) != 0)) {
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      lVar3 = (long long)((int)(short)(*(u16 *)(g_007B5E20 + 0x24)) - (int)(*(short *)(g_007B5E20 + 0x28)));
                      if (lVar3 < 0) {
                        (*(u16 *)(g_007B5E20 + 0x24)) = 0;
                        (*(u16 *)(g_007B5E20 + 0x22)) = 0;
                      }
                      else {
                        if (lVar3 < 1) {
                          lVar3 = 0;
                          lVar5 = 0;
                        }
                        else {
                          lVar5 = lVar3 << 0x30;
                        }
                        (*(u16 *)(g_007B5E20 + 0x24)) = (u16)lVar3;
                        if (lVar5 >> 0x30 < (long long)(short)(*(u16 *)(g_007B5E20 + 0x22))) {
                          (*(u16 *)(g_007B5E20 + 0x22)) = (u16)((unsigned long long)lVar5 >> 0x30);
                        }
                      }
                    }
                  }
                  else if (0 < (short)(*(u16 *)(g_007B5E20 + 0x22))) {
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    (*(u16 *)(g_007B5E20 + 0x22)) = 0;
                    (*(u16 *)(g_007B5E20 + 0x24)) = 0;
                  }
                }
                else if ((*(short *)(g_007B5E20 + 0x28)) < (*(short *)(g_007B5E20 + 0x26))) {
                  if (((long long)(short)(*(u16 *)(g_007B5E20 + 0x24)) != (long long)((*(short *)(g_007B5E20 + 0x26)) + -1)) ||
                     ((long long)(short)(*(u16 *)(g_007B5E20 + 0x22)) != (long long)((*(short *)(g_007B5E20 + 0x28)) + -1))) {
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    iVar4 = (*(short *)(g_007B5E20 + 0x26)) + -1;
                    iVar6 = (int)(short)(*(u16 *)(g_007B5E20 + 0x24)) + (int)(*(short *)(g_007B5E20 + 0x28));
                    if (iVar6 < iVar4) {
                      (*(u16 *)(g_007B5E20 + 0x24)) = (u16)iVar6;
                      if ((long long)(*(short *)(g_007B5E20 + 0x28)) <=
                          (long long)((int)(short)(*(u16 *)(g_007B5E20 + 0x24)) +
                                ((int)(*(short *)(g_007B5E20 + 0x28)) - (int)(short)(*(u16 *)(g_007B5E20 + 0x22))))) {
                        iVar4 = (int)(short)(*(u16 *)(g_007B5E20 + 0x24)) - ((int)(*(short *)(g_007B5E20 + 0x26)) - (int)(*(short *)(g_007B5E20 + 0x28)));
                        if ((long long)(short)(*(u16 *)(g_007B5E20 + 0x22)) <= (long long)iVar4) {
                          (*(u16 *)(g_007B5E20 + 0x22)) = (u16)iVar4;
                        }
                        return 2;
                      }
                    }
                    else {
                      (*(u16 *)(g_007B5E20 + 0x24)) = (u16)iVar4;
                      (*(u16 *)(g_007B5E20 + 0x22)) = (*(short *)(g_007B5E20 + 0x28)) - 1U & 0xff;
                    }
                  }
                }
                else if ((long long)(short)(*(u16 *)(g_007B5E20 + 0x22)) < (long long)((*(short *)(g_007B5E20 + 0x28)) + -1)) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  (*(u16 *)(g_007B5E20 + 0x22)) = (*(short *)(g_007B5E20 + 0x28)) - 1U & 0xff;
                  (*(u16 *)(g_007B5E20 + 0x24)) = (*(short *)(g_007B5E20 + 0x26)) + -1;
                }
              }
              else if ((*(short *)(g_007B5E20 + 0x28)) < (*(short *)(g_007B5E20 + 0x26))) {
                if (0 < (short)(*(u16 *)(g_007B5E20 + 0x24))) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  if (0 < (short)(*(u16 *)(g_007B5E20 + 0x22))) {
                    (*(u16 *)(g_007B5E20 + 0x22)) = (*(u16 *)(g_007B5E20 + 0x22)) - 1;
                  }
                  (*(u16 *)(g_007B5E20 + 0x24)) = (*(u16 *)(g_007B5E20 + 0x24)) + -1;
                  return 2;
                }
                if ((uVar1 & 0x1000) != 0) {
                  if (1 < (*(short *)(g_007B5E20 + 0x26))) {
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  }
                  if ((*(u16 *)(g_007B5E20 + 0x24)) == 0) {
                    (*(u16 *)(g_007B5E20 + 0x24)) = (*(short *)(g_007B5E20 + 0x26)) - 1;
                  }
                  else {
                    (*(u16 *)(g_007B5E20 + 0x24)) = (*(short *)(g_007B5E20 + 0x26)) - 1U & 0xff;
                  }
                  (*(u16 *)(g_007B5E20 + 0x22)) = (*(short *)(g_007B5E20 + 0x28)) - 1U & 0xff;
                  return 2;
                }
              }
              else {
                if (0 < (short)(*(u16 *)(g_007B5E20 + 0x24))) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  if (0 < (short)(*(u16 *)(g_007B5E20 + 0x22))) {
                    (*(u16 *)(g_007B5E20 + 0x22)) = (*(u16 *)(g_007B5E20 + 0x22)) - 1;
                  }
                  (*(u16 *)(g_007B5E20 + 0x24)) = (*(u16 *)(g_007B5E20 + 0x24)) + -1;
                  return 2;
                }
                if ((uVar1 & 0x1000) != 0) {
                  if (1 < (*(short *)(g_007B5E20 + 0x26))) {
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  }
                  if ((*(u16 *)(g_007B5E20 + 0x24)) == 0) {
                    (*(u16 *)(g_007B5E20 + 0x24)) = (*(short *)(g_007B5E20 + 0x26)) - 1;
                  }
                  else {
                    (*(u16 *)(g_007B5E20 + 0x24)) = (*(short *)(g_007B5E20 + 0x26)) - 1U & 0xff;
                  }
                  (*(u16 *)(g_007B5E20 + 0x22)) = (*(short *)(g_007B5E20 + 0x28)) - 1U & 0xff;
                  return 2;
                }
              }
            }
            else if ((*(short *)(g_007B5E20 + 0x28)) < (*(short *)(g_007B5E20 + 0x26))) {
              if ((long long)(short)(*(u16 *)(g_007B5E20 + 0x24)) < (long long)((*(short *)(g_007B5E20 + 0x26)) + -1)) {
                (*(u16 *)(g_007B5E20 + 0x24)) = (*(u16 *)(g_007B5E20 + 0x24)) + 1;
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                if ((long long)(short)(*(u16 *)(g_007B5E20 + 0x22)) < (long long)((*(short *)(g_007B5E20 + 0x28)) + -1)) {
                  (*(u16 *)(g_007B5E20 + 0x22)) = (*(u16 *)(g_007B5E20 + 0x22)) + 1;
                }
                return 2;
              }
              if ((uVar1 & 0x4000) != 0) {
                if (1 < (*(short *)(g_007B5E20 + 0x26))) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                }
                (*(u16 *)(g_007B5E20 + 0x22)) = 0;
                (*(u16 *)(g_007B5E20 + 0x24)) = 0;
                return 2;
              }
            }
            else {
              if ((long long)(short)(*(u16 *)(g_007B5E20 + 0x24)) < (long long)((*(short *)(g_007B5E20 + 0x26)) + -1)) {
                (*(u16 *)(g_007B5E20 + 0x24)) = (*(u16 *)(g_007B5E20 + 0x24)) + 1;
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                if ((long long)(short)(*(u16 *)(g_007B5E20 + 0x22)) < (long long)((*(short *)(g_007B5E20 + 0x28)) + -1)) {
                  (*(u16 *)(g_007B5E20 + 0x22)) = (*(u16 *)(g_007B5E20 + 0x22)) + 1;
                }
                return 2;
              }
              if ((uVar1 & 0x4000) != 0) {
                if (1 < (*(short *)(g_007B5E20 + 0x26))) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                }
                (*(u16 *)(g_007B5E20 + 0x22)) = 0;
                (*(u16 *)(g_007B5E20 + 0x24)) = 0;
                return 2;
              }
            }
          }
          else {
            if ((uVar1 & 0x40) == 0) {
              if ((uVar1 & 0x10) != 0) {
                func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
                (*(u32 *)(g_007B5E20 + 0xC)) = 0;
              }
            }
            else {
              func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
              ((int (*)())((u8 *)PS2_PTR(((ps2ptr *)g_00414E70)[(*(short *)(g_007B5E20 + 0x20))])))((*(u32 *)(g_007B5E20 + 0x2C)),(*(short *)(g_007B5E20 + 0x26)));
              (*(u32 *)(g_007B5E20 + 0xC)) = 0;
            }
            if ((uVar1 & 0x1000) == 0) {
              if ((uVar2 & 0x1000) == 0) {
                if ((uVar1 & 0x4000) == 0) {
                  if (((uVar2 & 0x4000) != 0) && ((*(short *)(g_007B5E20 + 0x20)) < 10)) {
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    (*(short *)(g_007B5E20 + 0x20)) = (*(short *)(g_007B5E20 + 0x20)) + 1;
                  }
                }
                else {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  (*(short *)(g_007B5E20 + 0x20)) = (short)(((*(short *)(g_007B5E20 + 0x20)) + 1) % 0xb);
                }
              }
              else if (0 < (*(short *)(g_007B5E20 + 0x20))) {
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                (*(short *)(g_007B5E20 + 0x20)) = (*(short *)(g_007B5E20 + 0x20)) + -1;
              }
            }
            else {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              if ((*(short *)(g_007B5E20 + 0x20)) == 0) {
                (*(short *)(g_007B5E20 + 0x20)) = 10;
              }
              else {
                (*(short *)(g_007B5E20 + 0x20)) = (*(short *)(g_007B5E20 + 0x20)) + -1;
              }
            }
          }
        }
        else if ((uVar1 & 0x10) == 0) {
          if ((uVar1 & 0xc) == 0) {
            if ((uVar1 & 0x20) == 0) {
              if ((uVar1 & 0x80) == 0) {
                if ((uVar2 & 0x4000) == 0) {
                  if ((uVar2 & 0x1000) == 0) {
                    if ((uVar2 & 0x2000) == 0) {
                      if ((((uVar2 & 0x8000) != 0) && ((*(u8 *)(g_007B5E20 + 0x2A)) != 0xff)) && (9 < (*(u8 *)(g_007B5E20 + 0x2A))))
                      {
                        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                        (*(u8 *)(g_007B5E20 + 0x2A)) = (*(u8 *)(g_007B5E20 + 0x2A)) - 10;
                        func_002B3CF0(6);
                      }
                    }
                    else if (((*(u8 *)(g_007B5E20 + 0x2A)) != 0xff) && ((*(u8 *)(g_007B5E20 + 0x2A)) < 0x1e)) {
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      (*(u8 *)(g_007B5E20 + 0x2A)) = (*(u8 *)(g_007B5E20 + 0x2A)) + 10;
                      func_002B3CF0(6);
                    }
                  }
                  else {
                    if ((*(u8 *)(g_007B5E20 + 0x2A)) == 0xff) {
                      return 2;
                    }
                    if ((u32)(*(u8 *)(g_007B5E20 + 0x2A)) % 10 == 0) {
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      (*(u8 *)(g_007B5E20 + 0x2B)) = (*(u8 *)(g_007B5E20 + 0x2A));
                      (*(u8 *)(g_007B5E20 + 0x2A)) = 0xff;
                      (*(u8 *)(g_007B5E20 + 0x2B)) = (*(u8 *)(g_007B5E20 + 0x2B)) / 10;
                      func_002B3CF0(6);
                    }
                    else {
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      (*(u8 *)(g_007B5E20 + 0x2A)) = (*(u8 *)(g_007B5E20 + 0x2A)) - 1;
                      func_002B3CF0(6);
                    }
                  }
                }
                else if ((*(u8 *)(g_007B5E20 + 0x2A)) == 0xff) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  (*(u8 *)(g_007B5E20 + 0x2A)) = (*(u8 *)(g_007B5E20 + 0x2B)) * '\n';
                  func_002B3CF0(6);
                }
                else if ((u32)(*(u8 *)(g_007B5E20 + 0x2A)) % 10 < 9) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  (*(u8 *)(g_007B5E20 + 0x2A)) = (*(u8 *)(g_007B5E20 + 0x2A)) + 1;
                  func_002B3CF0(6);
                }
              }
              else {
                func_0032D900();
              }
            }
            else {
              func_0032D8B0();
            }
          }
          else {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            (*(u32 *)(g_007B5E20 + 0x18)) = (*(u32 *)(g_007B5E20 + 0x18)) != 0 ^ 1;
            if (((*(u32 *)(g_007B5E20 + 0x18)) != 0) &&
               (lVar3 = func_0036DC30(*(u32 *)((*(u32 *)(g_007B5E20 + 0x2C)) + (short)(*(u16 *)(g_007B5E20 + 0x24)) * 4),
                                     (*(u8 *)(g_007B5E20 + 0x2A))), lVar3 != 0)) {
              func_002B3CF0(6);
            }
          }
        }
        else {
          func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
          (*(u32 *)(g_007B5E20 + 0x8)) = 0;
          (*(u32 *)(g_007B5E20 + 0x10)) = 0;
          (*(u32 *)(g_007B5E20 + 0x14)) = 0;
        }
      }
      else if ((uVar1 & 0x10) == 0) {
        if ((uVar1 & 0x20) == 0) {
          if ((uVar1 & 0x80) != 0) {
            func_0032D950();
          }
        }
        else {
          func_0032D8B0();
        }
      }
      else {
        func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
        (*(u32 *)(g_007B5E20 + 0x8)) = 0;
        (*(u32 *)(g_007B5E20 + 0x10)) = 0;
        (*(u32 *)(g_007B5E20 + 0x14)) = 0;
      }
    }
    else if ((uVar1 & 0x10) == 0) {
      if ((uVar1 & 0x20) == 0) {
        if ((uVar1 & 0x80) != 0) {
          func_0032D950();
        }
      }
      else {
        func_0032D900();
      }
    }
    else {
      func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
      (*(u32 *)(g_007B5E20 + 0x8)) = 0;
      (*(u32 *)(g_007B5E20 + 0x10)) = 0;
      (*(u32 *)(g_007B5E20 + 0x14)) = 0;
    }
  }
  return 2;
}

/* MISSING ['0x45d73c'] */

/* MISSING ['0x45d730'] */

/* MISSING ['0x417468', '0x41746c', '0x417470'] */

/* 0x00383BB0, 0x34 bytes. */
int func_00383BB0(int param_1)
{
    unsigned long long uVar1;

  
  if (param_1 < 0xb) {
                    /* WARNING: Could not recover jumptable at 0x00383bd0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = ((int (*)())((u8 *)PS2_PTR(((ps2ptr *)g_00459600)[(int)param_1])))();
    return uVar1;
  }
  return 0;
}

/* 0x0038C420, 0x178 bytes. */
int func_0038C420(u8 *param_1)
{
    int iVar1;
    u8 * iVar3;
    int iVar5;
    long long lVar2;
    long long lVar4;

  
  iVar3 = param_1;
  iVar1 = PS2_ADDR(iVar3 + *(int *)(iVar3 + 0x68c) * 0x184);
  iVar5 = *(int *)((u8 *)PS2_PTR(iVar1) + 0x7c);
  lVar4 = 0;
  if (iVar5 < 0x16) {
    if (iVar5 != 0x15) {
      lVar4 = ((int (*)())((u8 *)PS2_PTR(((ps2ptr *)g_00417670)[iVar5])))();
    }
    if (lVar4 == 0) {
      lVar2 = func_0038C370(*(u32 *)((u8 *)PS2_PTR(iVar1) + 0x7c));
      if (lVar2 == 0) {
        lVar2 = func_0038A470(param_1);
        if (lVar2 == 0) {
          if (((*(int *)(iVar3 + 0x690) == 0) && (iVar5 = iVar1 + 0xfc, iVar5 != 0)) &&
             (lVar2 = func_00120A40(iVar5), lVar2 != 0)) {
            func_00313AC0(*(u32 *)(iVar3 + 4),*(u32 *)((u8 *)PS2_PTR(iVar1) + 0xf8));
            func_00374EE0(iVar5);
          }
        }
        else {
          iVar1 = iVar1 + 0xfc;
          if ((iVar1 != 0) && (lVar2 = func_00120A40(iVar1), lVar2 != 0)) {
            func_00374EE0(iVar1);
          }
        }
      }
      else if (((*(int *)(iVar3 + 0x690) == 1) && (iVar5 = iVar1 + 0xfc, iVar5 != 0)) &&
              (lVar2 = func_00120A40(iVar5), lVar2 != 0)) {
        func_00313AC0(*(u32 *)(iVar3 + 4),*(u32 *)((u8 *)PS2_PTR(iVar1) + 0xf8));
        func_00374EE0(iVar5);
        return 0;
      }
    }
  }
  else {
    lVar4 = 0;
  }
  return lVar4;
}

/* 0x0038E8F0, 0x34 bytes. */
int func_0038E8F0(int param_1)
{
    unsigned long long uVar1;

  
  if (param_1 < 8) {
                    /* WARNING: Could not recover jumptable at 0x0038e910. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = ((int (*)())((u8 *)PS2_PTR(((ps2ptr *)g_004599F0)[(int)param_1])))();
    return uVar1;
  }
  return 0;
}

/* MISSING ['0x7ba7f8'] */

/* 0x003AFD90, 0xB4 bytes. */
void func_003AFD90(void)
{
    ps2ptr apuStack_20[4];
    u8 ** ppuVar2;
    u8 * puStack_10;
    unsigned long long uVar1;
    u32 uVar3;
    u32 uVar4;

  
  uVar4 = 0;
  apuStack_20[0] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_0041C140)));
  apuStack_20[1] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_0041C144)));
  apuStack_20[2] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_0041C148)));
  apuStack_20[3] = PS2_ADDR(((u8 *)PS2_PTR(*(ps2ptr *)g_0041C14C)));
  puStack_10 = ((u8 *)PS2_PTR(*(ps2ptr *)g_0041C150));
  do {
    uVar3 = 0;
    ppuVar2 = (u8 **)(apuStack_20);
    do {
      uVar1 = ((int (*)())*ppuVar2)(uVar4);
      func_003AFB50(uVar4,uVar3,uVar1);
      uVar3 = uVar3 + 1;
      ppuVar2 = ppuVar2 + 1;
    } while (uVar3 < 5);
    uVar4 = uVar4 + 1;
  } while (uVar4 < 2);
  return;
}

/* MISSING ['0x45d7fc'] */

/* MISSING ['0x41c160', '0x41c164', '0x41c168', '0x41c16c', '0x41c170', '0x41c174', '0x41c178', '0x41c17c'] */

/* MISSING ['0x41c400', '0x41c404', '0x41c408', '0x41c40c'] */

/* MISSING ['0x41d008', '0x41d00c', '0x41d010'] */

/* MISSING ['0x41d2e0', '0x41d2e4', '0x41d2e8', '0x41d2ec'] */

/* 0x003EA470, 0x1E4 bytes. */
void func_003EA470(int param_1, int param_2, u32 *param_3, int param_4, int param_5, int param_6, int param_7, int param_8)
{
    int iVar2;
    int iVar5;
    int iVar6;
    int iVar7;
    long long lVar4;
    u32 * puVar3;
    u32 uVar1;
    u32 uVar8;

  
  iVar6 = 0;
  if (((param_2 < 3) || (5 < param_2)) && ((int)param_2 != 7)) {
    iVar5 = 9;
  }
  else {
    iVar5 = 0xb;
  }
  iVar7 = 0;
  if (0 < param_4) {
    do {
      if (iVar5 == 0xb) {
        iVar2 = func_002F7D90(iVar6,0x2f8340,*param_3,0,1,0);
      }
      else {
        iVar2 = func_002F7D90(iVar6,0x2f82a0,*param_3,0,1,0);
      }
      iVar6 = iVar6 + iVar2;
      iVar7 = iVar7 + 1;
      param_3 = param_3 + 1;
    } while (iVar7 < param_4);
  }
  puVar3 = (u32 *)func_002F7B10();
  uVar8 = 0x19f;
  iVar5 = 0;
  if (0 < iVar6) {
    do {
      uVar1 = *puVar3;
      lVar4 = func_003EA350(uVar1);
      if (lVar4 == 0) {
        lVar4 = func_002F3770(uVar1);
        if (param_5 <= lVar4) {
          if ((uVar8 < 0x19f) && (param_6 != 0)) {
            lVar4 = ((int (*)())PS2_PTR(param_6))(uVar8,uVar1,param_7,param_8);
            if (lVar4 == 0) goto LAB_003ea5e8;
          }
          uVar8 = uVar1;
        }
      }
LAB_003ea5e8:
      iVar5 = iVar5 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar5 < iVar6);
  }
  if (uVar8 < 0x19f) {
    func_0030CF90(param_1,(int)param_2,uVar8);
  }
  return;
}
