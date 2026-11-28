/*
 * gen24_180000.c - functions between 0x00180000 and 0x003F9680, generated from Ghidra
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
void func_001E01D0(float param_1, int param_2, int p2);
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
void func_002072C0(u8 *param_1, int p1);
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
int func_0022CDA0(u8 *param_1, unsigned long long *param_2, int p2);
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
void func_002723B0(u32 *param_1, int param_2, int p2);
void func_002788F0(void);
void func_00278A20(void);
void func_00278CF0(void);
void func_00279070(int param_1, int param_2, short *param_3, int param_4, int param_5, int param_6);
void func_002790E0(int param_1, int param_2);
void func_00279240(void);
void func_0027A080(int param_1, u32 *param_2, int param_3, int param_4);
int func_0027D6B0(u8 *param_1, int param_2);
int func_0027D960(int param_1, u8 *param_2, u8 *param_3, int *param_4, int param_5);
int func_0027DE50(int p0, int p1, int p2);
void func_0027F800(void);
int func_0027FC60(u8 *param_1);
void func_002861D0(int param_1, int param_2, int param_3, int param_4, int p4);
void func_00286420(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, u8 *param_7, int param_8);
void func_00286CA0(int param_1, int param_2, int param_3);
void func_002875F0(int param_1, int param_2, u8 *param_3, u8 *param_4);
void func_00287A10(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_00288660(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int p6);
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
void func_0029C140(int param_1, int param_2, int p2);
void func_0029C2D0(int param_1, int param_2, int p2);
void func_0029C460(int param_1, int param_2, int param_3, int param_4, u8 *param_5);
void func_0029C690(int param_1, int param_2, int param_3);
void func_0029C800(int param_1, int param_2, u8 *param_3);
void func_0029C8B0(u8 *param_1);
void func_0029C930(u8 *param_1);
void func_0029D520(int param_1, int param_2, int param_3);
void func_0029D6F0(u8 *param_1);
void func_0029DD90(int param_1, int param_2, int param_3, float param_4, float param_5);
void func_0029DDE0(int param_1, int param_2, int param_3, float param_4, float param_5);
void func_002A5D70(int param_1, int param_2, int param_3, int p3, int p4, int p5);
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
void func_002B4BA0(int param_1, int param_2, int p2, int p3, int p4, int p5);
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
void func_002CB550(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7);
void func_002CB5B0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10, int param_11, u32 *param_12, int param_13);
void func_002CC130(unsigned long long *param_1, int param_2, int param_3, int p3);
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
void func_002D37C0(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7);
void func_002D5CE0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8, int param_9, int param_10);
void func_002D81D0(u8 *param_1);
void func_002D8DA0(u8 *param_1);
int func_002DA090(void);
void func_002DA2D0(int param_1);
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
void func_00383880(int param_1, int param_2, int p2, int p3, int p4, int p5, int p6, int p7);
void func_00383A80(int param_1, int param_2, int p2, int p3, int p4, int p5, int p6);
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
void func_003B4F50(int param_1, int p1, int p2, int p3, int p4, int p5);
void func_003B56E0(int param_1, int param_2, int p2, int p3, int p4, int p5);
void func_003B5CC0(int param_1, int param_2, int param_3, int param_4, int p4, int p5);
void func_003B69A0(void);
int func_003B9770(int param_1);
void func_003BC150(void);
void func_003BCDD0(void);
void func_003D4080(int param_1, int param_2, int param_3, int param_4, int param_5, int p5, int p6);
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
void func_003EF930(int param_1, int p1, int p2, int p3, int p4, int p5);
void func_003F0CE0(int param_1, int param_2, u8 *param_3, int param_4, int param_5, int param_6, int param_7);
int func_003F1B50(int param_1);

/* 0x00180D10, 0x174 bytes. */
void func_00180D10(u8 *param_1)
{
    int iVar3;
    int iVar4;
    int sVar1;
    int sVar2;
    int sVar5;

  
  iVar3 = *(int *)(param_1 + 0x14) * 0xc0;
  iVar4 = iVar3 + 0x6a3a30;
  if ((*(u32 *)(g_006A3AE8 + iVar3) & 0x100) == 0) {
    sVar5 = *(short *)(g_006A3AB2 + iVar3);
    sVar1 = *(short *)(param_1 + 0x4c);
    sVar2 = sVar5;
    if (sVar1 < sVar5) {
      sVar2 = sVar1;
    }
    if (sVar2 < 1) {
      sVar5 = 0;
    }
    else if (sVar1 < sVar5) {
      sVar5 = sVar1;
    }
    *(short *)(param_1 + 0x4e) = sVar5;
  }
  else {
    sVar5 = *(short *)(param_1 + 0x4c);
    sVar1 = sVar5;
    if (-1 < sVar5) {
      sVar1 = 0;
    }
    if (sVar1 < 1) {
      sVar5 = 0;
    }
    else if (-1 < sVar5) {
      sVar5 = 0;
    }
    *(short *)(param_1 + 0x4e) = sVar5;
  }
  sVar5 = 0;
  for (; iVar4 != 0; iVar4 = *(int *)((u8 *)PS2_PTR(iVar4) + 4)) {
    sVar5 = sVar5 + *(short *)((u8 *)PS2_PTR(iVar4) + 0x82);
  }
  sVar1 = *(short *)(param_1 + 0x50);
  sVar2 = sVar5;
  if (sVar1 < sVar5) {
    sVar2 = sVar1;
  }
  if (sVar2 < 1) {
    sVar5 = 0;
  }
  else if (sVar1 < sVar5) {
    sVar5 = sVar1;
  }
  *(short *)(param_1 + 0x52) = sVar5;
  return;
}

/* MISSING ['0x574e70', '0x574e78', '0x574e7c', '0x5754a0', '0x5754a8', '0x5754ac'] */

/* MISSING ['0x406940', '0x406944', '0x406948', '0x40694c', '0x406950', '0x406954', '0x406958', '0x40695c', '0x406960', '0x406964', '0x406968'] */

/* 0x00184FA0, 0x1C0 bytes. */
int func_00184FA0(int p0)
{
    u8 * iVar1;
    u8 * iVar3;
    u8 * iVar4;
    unsigned long long uVar2;
    u32 uVar5;

  
  uVar2 = PS2_ADDR(func_0019AE10((unsigned char *)PS2_PTR(p0)));
  uVar2 = PS2_ADDR(func_00186380((unsigned char *)PS2_PTR(uVar2)));
  uVar2 = PS2_ADDR(func_0019A720((unsigned char *)PS2_PTR(uVar2)));
  uVar2 = PS2_ADDR(func_0018B850((unsigned char *)PS2_PTR(uVar2)));
  uVar2 = PS2_ADDR(func_0018BD00((unsigned char *)PS2_PTR(uVar2)));
  uVar2 = PS2_ADDR(func_0018BEA0((unsigned char *)PS2_PTR(uVar2)));
  iVar1 = func_0018C010((unsigned char *)PS2_PTR(uVar2));
  uVar5 = 0;
  iVar4 = g_005BA690;
  do {
    iVar3 = iVar1;
    func_00118AC0((unsigned int *)(iVar3),iVar4 + 0x1c10,4);
    uVar5 = uVar5 + 1;
    iVar4 = iVar4 + 4;
    iVar1 = iVar3 + 4;
  } while (uVar5 < 0x40);
  (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 199;
  func_00118AC0((unsigned int *)(iVar3 + 4),(unsigned char *)PS2_PTR(0x5bc3a0),4);
  (*(u8 *)(g_005BC3A0 + 0x4)) = (*(u8 *)(g_005BC3A0 + 0x4)) & 0xf7;
  func_00118AC0((unsigned int *)(iVar3 + 8),(unsigned char *)PS2_PTR(0x5bc3a4),4);
  uVar2 = PS2_ADDR(func_0023ECA0(iVar3 + 0xc));
  uVar2 = PS2_ADDR(func_003560D0((unsigned char *)PS2_PTR(uVar2)));
  uVar2 = PS2_ADDR(func_00357850((unsigned char *)PS2_PTR(uVar2)));
  uVar2 = PS2_ADDR(func_002C4BB0((unsigned char *)PS2_PTR(uVar2)));
  func_00118AC0((unsigned int *)PS2_PTR(uVar2),(unsigned char *)PS2_PTR(0x5bd728),8);
  iVar1 = (u8 *)PS2_PTR((int)uVar2);
  func_00118AC0((unsigned int *)(iVar1 + 8),(unsigned char *)PS2_PTR(0x5bd730),4);
  func_00118AC0((unsigned int *)(iVar1 + 0xc),(unsigned char *)PS2_PTR(0x5bd734),4);
  func_00118AC0((unsigned int *)(iVar1 + 0x10),(unsigned char *)PS2_PTR(0x5bd738),4);
  func_00118AC0((unsigned int *)(iVar1 + 0x14),(unsigned char *)PS2_PTR(0x5bd73c),4);
  *(u8 *)(iVar1 + 0x18) = (*(u8 *)(g_005BD740 + 0x0));
  *(u8 *)(iVar1 + 0x19) = (*(u8 *)(g_005BD740 + 0x1));
  *(u8 *)(iVar1 + 0x1a) = (*(u8 *)(g_005BD740 + 0x2));
  *(u8 *)(iVar1 + 0x1b) = (*(u8 *)(g_005BD740 + 0x3));
  *(u8 *)(iVar1 + 0x1c) = ((unsigned long long)(*(u8 *)(g_0073DCA3 + 0x0)) & 7) >> 2 != 0;
  *(u8 *)(iVar1 + 0x1d) = ((unsigned long long)(*(u8 *)(g_0073DF33 + 0x0)) & 7) >> 2 != 0;
  return PS2_ADDR(iVar1 + 0x1e);
}

/* 0x00185210, 0xEC bytes. */
void func_00185210(void)
{
    u8 * iVar1;
    u32 uVar2;

  
  if ((*(u32 *)(g_00669DB8 + 0x0)) == 2) {
    if (((((*(u32 *)(g_00669F70 + 0x0)) == 7) || ((*(u32 *)(g_00669F70 + 0x0)) == 4)) || ((*(u32 *)(g_00669F70 + 0x0)) == 1)) ||
       (((*(u32 *)(g_00669F70 + 0x0)) == 3 || ((*(u32 *)(g_00669F70 + 0x28)) % 5 == 4)))) {
      uVar2 = 0;
      iVar1 = g_005BA690;
      do {
        if (*(int *)(iVar1 + 0x14) != 0) {
          func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x5BA6A4)));
          *(u32 *)(iVar1 + 0x14) = 0;
        }
        uVar2 = uVar2 + 1;
        iVar1 = iVar1 + 4;
      } while (uVar2 < 5);
    }
  }
  else if ((*(u32 *)(g_005BA6A4 + 0x0)) != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x5BA6A4)));
    (*(u32 *)(g_005BA6A4 + 0x0)) = 0;
  }
  return;
}

/* 0x001BBEA0, 0x3DC bytes. */
int func_001BBEA0(int p0)
{
    int iStack_4;
    u8 * iVar3;
    u8 * iVar5;
    u32 uStack_8;
    u32 uVar1;
    unsigned long long uVar2;
    u32 uVar4;

  
  uVar2 = PS2_ADDR(func_001D5C60((void *)PS2_PTR(p0)));
  uVar2 = func_001820F0((int *)PS2_PTR(uVar2));
  uVar2 = PS2_ADDR(func_00182B40((unsigned char *)PS2_PTR(uVar2)));
  func_00118AC0((unsigned int *)PS2_PTR(uVar2),(unsigned char *)PS2_PTR(0x6aa570),4);
  iVar5 = (u8 *)PS2_PTR((int)uVar2);
  func_00118AC0((unsigned int *)(iVar5 + 4),(unsigned char *)PS2_PTR(0x6aa574),4);
  func_00118AC0((unsigned int *)(iVar5 + 8),(unsigned char *)PS2_PTR(0x6aa578),4);
  func_00118AC0((unsigned int *)(iVar5 + 0xc),(unsigned char *)PS2_PTR(0x6aa57c),4);
  iVar5 = iVar5 + 0x10;
  uVar4 = 0;
  if ((*(u32 *)(g_006AA598 + 0x0)) != 0) {
    iVar3 = g_00693970;
    do {
      iStack_4 = (*(int *)(iVar3 + 0x16c10) + -0x693970) / 0x88;
      func_00118AC0((unsigned int *)(iVar5),(unsigned char *)(&iStack_4),4);
      uVar4 = uVar4 + 1;
      iVar5 = iVar5 + 4;
      iVar3 = iVar3 + 4;
    } while (uVar4 < (*(u32 *)(g_006AA598 + 0x0)));
  }
  for (; uVar4 < 6; uVar4 = uVar4 + 1) {
    iVar5 = iVar5 + 4;
  }
  func_00118AC0((unsigned int *)(iVar5),(unsigned char *)PS2_PTR(0x6aa598),4);
  uVar4 = 0;
  iVar5 = iVar5 + 4;
  do {
    iVar3 = iVar5;
    iVar5 = (u8 *)PS2_PTR(*(int *)PS2_PTR((uVar4 * 4 + 0x6aa59c)));
    if (iVar5 == 0) {
      iStack_4 = -1;
      func_00118AC0((unsigned int *)(iVar3),(unsigned char *)(&iStack_4),4);
    }
    else {
      iStack_4 = (*(int *)(iVar5 + 0x68) - (*(u32 *)(g_005BA6A0 + 0x0))) / 0x2c;
      func_00118AC0((unsigned int *)(iVar3),(unsigned char *)(&iStack_4),4);
      uStack_8 = (u32)(*(int *)(iVar5 + 0xc) != 0);
      func_00118AC0((unsigned int *)(iVar3 + 4),(unsigned char *)(&uStack_8),4);
      uStack_8 = *(u32 *)(iVar5 + 0xbc) & 0x1000000;
      func_00118AC0((unsigned int *)(iVar3 + 8),(unsigned char *)(&uStack_8),4);
      func_00118AC0((unsigned int *)(iVar3 + 0xc),(unsigned char *)PS2_PTR(*(int *)(iVar5 + 0x14) + 0x90),0x10);
      func_00118AC0((unsigned int *)(iVar3 + 0x1c),(unsigned char *)PS2_PTR(*(int *)(iVar5 + 0x14) + 0x50),0x10);
    }
    uVar4 = uVar4 + 1;
    iVar5 = iVar3 + 0x2c;
  } while (uVar4 < 2);
  func_00118AC0((unsigned int *)(iVar3 + 0x2c),(unsigned char *)PS2_PTR(0x6aa5a4),0xc);
  func_00118AC0((unsigned int *)(iVar3 + 0x38),(unsigned char *)PS2_PTR(0x6aa5b0),0xc);
  func_00118AC0((unsigned int *)(iVar3 + 0x44),(unsigned char *)PS2_PTR(0x6aa5bc),0xc);
  func_00118AC0((unsigned int *)(iVar3 + 0x50),(unsigned char *)PS2_PTR(0x6aa5c8),8);
  func_00118AC0((unsigned int *)(iVar3 + 0x58),(unsigned char *)PS2_PTR(0x6aa5d0),8);
  uVar4 = 0;
  iVar5 = g_006A3D30;
  do {
    uVar1 = *(u32 *)(iVar5 + 0xb8);
    if ((((uVar1 & 1) != 0) && ((uVar1 & 2) == 0)) && ((uVar1 & 0x8000) != 0)) break;
    uVar4 = uVar4 + 1;
    iVar5 = iVar5 + 0xc0;
  } while (uVar4 < 0x8f);
  if (uVar4 < 0x8f) {
    iStack_4 = (*(int *)(iVar5 + 0x10) + -0x693970) / 0x88;
    func_00118AC0((unsigned int *)(iVar3 + 0x60),(unsigned char *)(&iStack_4),4);
    func_00118AC0((unsigned int *)(iVar3 + 100),(unsigned char *)PS2_PTR(*(int *)(iVar5 + 0x14) + 0x40),0x10);
    func_00118AC0((unsigned int *)(iVar3 + 0x74),(unsigned char *)PS2_PTR(*(int *)(iVar5 + 0x14) + 0x50),0x10);
  }
  else {
    iStack_4 = -1;
    func_00118AC0((unsigned int *)(iVar3 + 0x60),(unsigned char *)(&iStack_4),4);
  }
  func_00118AC0((unsigned int *)(iVar3 + 0x84),(unsigned char *)PS2_PTR(0x6aa5f0),4);
  uVar2 = PS2_ADDR(func_0034B7D0(iVar3 + 0x88));
  func_00118AC0((unsigned int *)PS2_PTR(uVar2),(unsigned char *)PS2_PTR(0x6aa624),4);
  return (int)uVar2 + 4;
}

/* 0x001C4A00, 0xC0 bytes, matching. */
void func_001C4A00(u8 *param_1, int param_2)
{
    u8 * iVar1;
    u8 * iVar2;

  
  func_001C51A0(PS2_ADDR(param_1),param_2 + 0x30);
  if (*(int *)((u8 *)PS2_PTR(param_2) + 0x2d4) != 0x30) {
    func_002A8030(*(int *)((u8 *)((u8 *)PS2_PTR(param_2)) + 0x2d4));
  }
  iVar2 = param_1;
  if (*(int *)(iVar2 + 8) == param_2) {
    *(u32 *)(iVar2 + 8) = *(u32 *)((u8 *)PS2_PTR(param_2) + 0x18);
    if (*(int *)((u8 *)PS2_PTR(param_2) + 0x18) != 0) {
      *(u32 *)PS2_PTR((*(int *)((u8 *)PS2_PTR(param_2) + 0x18) + 0x14)) = 0;
    }
    if (*(int *)(iVar2 + 0xc) == param_2) {
      *(u32 *)(iVar2 + 0xc) = 0;
    }
  }
  else if (*(int *)(iVar2 + 0xc) == param_2) {
    iVar1 = (u8 *)PS2_PTR(*(int *)((u8 *)PS2_PTR(param_2) + 0x14));
    *(int *)(iVar2 + 0xc) = PS2_ADDR(iVar1);
    *(u32 *)(iVar1 + 0x18) = 0;
  }
  else {
    *(u32 *)PS2_PTR((*(int *)((u8 *)PS2_PTR(param_2) + 0x14) + 0x18)) = *(u32 *)((u8 *)PS2_PTR(param_2) + 0x18);
    *(u32 *)PS2_PTR((*(int *)((u8 *)PS2_PTR(param_2) + 0x18) + 0x14)) = *(u32 *)((u8 *)PS2_PTR(param_2) + 0x14);
  }
  func_001CB720((unsigned char *)PS2_PTR(param_2));
  return;
}

/* 0x001C7730, 0x9C bytes. */
void func_001C7730(void)
{
    int * piVar1;
    u32 uVar2;

  
  func_00103000(0);
  if (g_0045D38C != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x45D38C)));
    g_0045D38C = 0;
  }
  uVar2 = 0;
  piVar1 = (int *)PS2_PTR(0x72cea0);
  do {
    if (*piVar1 != 0) {
      func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x72CEA0)));
      *piVar1 = 0;
    }
    uVar2 = uVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (uVar2 < 4);
  func_00103000(1);
  if (g_0045D398 != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x45D398)));
    g_0045D398 = 0;
  }
  return;
}

/* 0x001C7CE0, 0xC8 bytes. */
void func_001C7CE0(void)
{
    int * piVar1;
    u32 uVar2;

  
  func_00103000(0);
  uVar2 = 0;
  piVar1 = (int *)PS2_PTR(0x72cea0);
  do {
    if (*piVar1 != 0) {
      func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x72CEA0)));
      *piVar1 = 0;
    }
    uVar2 = uVar2 + 1;
    piVar1 = piVar1 + 1;
  } while (uVar2 < 4);
  func_00103000(1);
  if (g_0045D398 != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x45D398)));
    g_0045D398 = 0;
  }
  g_0045D394 = 0;
  uVar2 = 0;
  g_0045D390 = 0;
  do {
    if ((int)uVar2 < 0x18b) {
      *(u32 *)PS2_PTR((uVar2 * 4 + 0x72c870)) = 0;
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < 0x18b);
  g_0045D32C = 0;
  return;
}

/* MISSING ['0x730560', '0x730564', '0x730568'] */

/* MISSING ['0x730560', '0x730564', '0x730568', '0x73056c'] */

/* MISSING ['0x45d3e0'] */

/* 0x001E98E0, 0x78 bytes. */
void func_001E98E0(int param_1)
{
  g_0045D40C = PS2_ADDR((int *)func_001026D0(1,param_1 + 0xd3c,0,1,0,0,(const char *)PS2_PTR(0x429350),0xc6));
  (*(u32 *)(g_007315D0 + 0x0)) = (*(int *)PS2_PTR(g_0045D40C));
  (*(u32 *)(g_007315D0 + 0x4)) = 1;
  (*(u32 *)(g_007315D0 + 0xC)) = (*(u32 *)(g_007315D0 + 0x0)) * 8 + 4;
  (*(u32 *)(g_007315D0 + 0x8)) = 4;
  func_001E9980();
  return;
}

/* 0x001EAC90, 0x644 bytes. */
int func_001EAC90(u8 *param_1, u8 *param_2)
{
    int bVar1;
    int bVar2;
    int bVar4;
    float fVar12;
    float fVar13;
    float fVar15;
    int iStack_4;
    u8 * iVar10;
    u8 * iVar11;
    int iVar14;
    int iVar5;
    int iVar6;
    int iVar8;
    long long lVar7;
    u32 uVar3;
    u32 uVar9;

  
  if (((*(u32 *)(g_00669F60 + 0x0)) & 0x14000008) == 0) {
    iVar11 = param_1;
    iVar14 = *(int *)(iVar11 + 100);
    iVar5 = func_001F10D0(*(u8 *)(iVar11 + 0x7d));
    if (iVar14 < iVar5) {
      bVar4 = false;
    }
    else {
      *(u32 *)(iVar11 + 100) = 0;
      iVar10 = param_2;
      uVar9 = (u32)*(u8 *)(iVar10 + 0x79);
      if (((*(u32 *)(iVar10 + 0x80) & 0x200) == 0) || (uVar9 == 0)) {
        if ((*(u32 *)(iVar10 + 0x84) & 0x800) == 0) {
          iStack_4 = *(u8 *)(iVar11 + 0x74) + 1;
          fVar12 = (float)iStack_4 * 0.2f;
          fVar12 = (float)((int)fVar12 * (u32)(0.25f < fVar12) | (u32)(0.25f >= fVar12) * 0x3e800000
                          );
          iVar6 = func_00349B30(param_1);
          fVar12 = fVar12 * 8.0f * (float)iVar6;
          iVar6 = func_00349BE0(param_2);
          uVar3 = (*(u32 *)(g_00669F60 + 0x14));
          if (*(u32 *)(iVar11 + 0x10) < 0x47) {
            iVar8 = *(u32 *)(iVar11 + 0x10) * 0x68;
            if (((*(u32 *)(g_00669F60 + 0x0)) & 0xc) == 0) {
              iVar8 = *(int *)(g_006A1DA4 + iVar8);
            }
            else if (*(char *)PS2_PTR((*(int *)(g_006A1D58 + iVar8) + 0x79)) == '\0') {
              iVar8 = 0x15e;
            }
            else {
              iVar8 = 0x28a;
            }
            fVar15 = (float)iVar8;
          }
          else {
            fVar15 = 1.0f;
          }
          if (*(u32 *)(iVar10 + 0x10) < 0x47) {
            iVar8 = *(u32 *)(iVar10 + 0x10) * 0x68;
            if (((*(u32 *)(g_00669F60 + 0x0)) & 0xc) == 0) {
              iVar8 = *(int *)(g_006A1DA4 + iVar8);
            }
            else if (*(char *)PS2_PTR((*(int *)(g_006A1D58 + iVar8) + 0x79)) == '\0') {
              iVar8 = 0x15e;
            }
            else {
              iVar8 = 0x28a;
            }
            fVar13 = (float)iVar8;
          }
          else {
            fVar13 = 1.0f;
          }
          fVar12 = (fVar12 / (float)iVar6) * ((float)iVar14 / (float)iVar5) *
                   ((fVar15 * 10.0f) / (fVar15 + fVar13));
          switch(*(u8 *)(iVar11 + 0x7c)) {
          case 0:
          case 1:
          case 2:
            fVar12 = fVar12 * 2.0f;
            break;
          case 3:
            fVar12 = fVar12 * 1.5f;
            break;
          case 5:
            fVar12 = fVar12 * 0.75f;
            break;
          case 6:
            fVar12 = fVar12 * 0.5f;
          }
          switch(*(u8 *)(iVar10 + 0x7c)) {
          case 0:
            if ((long long)((int)*(short *)(iVar10 + 0x52) << 1) < (long long)*(short *)(iVar10 + 0x50)) {
              if ((long long)((int)*(short *)(iVar10 + 0x52) << 2) < (long long)*(short *)(iVar10 + 0x50)) {
                fVar12 = fVar12 * 0.05f;
              }
              else {
                fVar12 = fVar12 * 0.075f;
              }
            }
            else {
              fVar12 = fVar12 * 0.1f;
            }
            if (uVar9 < (*(u32 *)(g_00669F60 + 0x14))) {
              iVar14 = *(int *)PS2_PTR((uVar9 * 4 + 0x669f78));
            }
            else {
              iVar14 = 0;
            }
            iVar5 = func_001839D0();
            fVar15 = (float)(int)(iVar14 * uVar3) / (float)iVar5;
            if (1.4f <= fVar15) {
              fVar12 = fVar12 * 0.4f;
            }
            else if (1.0f <= fVar15) {
              fVar12 = fVar12 * 0.6f;
            }
            else if (0.6f <= fVar15) {
              fVar12 = fVar12 * 0.8f;
            }
            break;
          case 1:
          case 2:
            fVar12 = fVar12 * 0.1f;
            break;
          case 3:
          case 4:
          case 5:
            fVar12 = fVar12 * 0.2f;
            break;
          case 6:
            fVar12 = fVar12 * 0.4f;
          }
          bVar1 = *(u8 *)(iVar11 + 0x79);
          bVar2 = *(u8 *)(iVar10 + 0x79);
          if (bVar1 < 2) {
            lVar7 = func_003F7780(bVar1,1);
            if (lVar7 != 0) {
              fVar12 = fVar12 * 2.0f;
            }
            lVar7 = func_003F7780(bVar1,2);
            if (lVar7 != 0) {
              fVar12 = fVar12 * 4.0f;
            }
            lVar7 = func_003F7780(bVar1,3);
            if (lVar7 != 0) {
              fVar12 = fVar12 * 6.0f;
            }
          }
          if (bVar2 < 2) {
            lVar7 = func_003F7780(bVar2,4);
            if (lVar7 != 0) {
              fVar12 = fVar12 * 0.5f;
            }
            lVar7 = func_003F7780(bVar2,5);
            if (lVar7 != 0) {
              fVar12 = fVar12 * 0.25f;
            }
            lVar7 = func_003F7780(bVar2,6);
            if (lVar7 != 0) {
              fVar12 = fVar12 * 0.16666667f;
            }
          }
          fVar12 = fVar12 * *(float *)(iVar11 + 0x58) * *(float *)(iVar10 + 0x5c) * 10.0f;
          if (1.0f < fVar12) {
            iVar14 = (int)fVar12;
          }
          else {
            iVar14 = 1;
          }
          func_001EA860(param_2,iVar14,1);
          lVar7 = func_001EA680(param_2,(unsigned int *)(&iStack_4));
          if (0 < iStack_4) {
            func_0017E600(param_1,param_2,iStack_4,lVar7,1);
          }
          bVar4 = lVar7 == 0;
          func_001ED160(PS2_ADDR(param_1),PS2_ADDR(param_2),bVar4);
          if (lVar7 != 0) {
            func_001D4C00(param_2);
            func_001EE3B0(param_2);
          }
        }
        else {
          bVar4 = true;
        }
      }
      else {
        bVar4 = true;
      }
    }
  }
  else {
    bVar4 = false;
  }
  return bVar4;
}

/* 0x001EB8C0, 0xA4 bytes. */
void func_001EB8C0(u8 *param_1)
{
    short asStack_4[2];
    short asStack_8[2];
    short asStack_c[2];
    u8 * iVar2;
    long long lVar1;

  
  iVar2 = param_1;
  asStack_4[0] = *(short *)(iVar2 + 0x40);
  asStack_8[0] = *(short *)(iVar2 + 0x42);
  asStack_c[0] = *(short *)(iVar2 + 0x44);
  func_0018F680((short unsigned int *)(asStack_8),(short unsigned int *)(asStack_4),(short unsigned int *)(asStack_c),*(u32 *)(iVar2 + 0x70));
  if ((((asStack_c[0] != asStack_8[0]) && ((*(u32 *)(iVar2 + 0x84) & 1) == 0)) &&
      (lVar1 = func_001F1790((unsigned char *)(asStack_8),param_1), lVar1 == 0)) &&
     (lVar1 = func_00190590((unsigned char *)(asStack_4),2), lVar1 == 0)) {
    asStack_8[0] = asStack_4[0];
  }
  *(short *)(iVar2 + 0x42) = asStack_8[0];
  return;
}

/* 0x001EE970, 0x44 bytes. */
void func_001EE970(int param_1, int p1)
{
  if ((((*(u32 *)(g_006A1D49 + 0x7)) & 1) != 0) && (param_1 == (*(char *)(g_006A1D49 + 0x0)))) {
    func_001EE750(0x6a1cd0, p1);
  }
  return;
}

/* 0x001F6FF0, 0xAC bytes. */
void func_001F6FF0(void)
{
  if (g_0045D410 != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x45D410)));
    g_0045D410 = 0;
  }
  if (g_700001DC != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x700001DC)));
    g_700001DC = 0;
  }
  if (g_700001D8 != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x700001D8)));
    g_700001D8 = 0;
  }
  if (g_700001D4 != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x700001D4)));
    g_700001D4 = 0;
  }
  if (g_700001D0 != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x700001D0)));
    g_700001D0 = 0;
  }
  return;
}

/* MISSING ['0x40cff0', '0x40cff4', '0x40cff8', '0x40cffc', '0x40d000', '0x40d004', '0x40d008', '0x40d00c', '0x40d010', '0x40d014'] */

/* MISSING ['0x45d2c0'] */

/* 0x0020ECE0, 0x50 bytes. */
void func_0020ECE0(void)
{
  if (g_0045D434 <= g_0045D430) {
    g_0045D434 = g_0045D430;
  }
  if (g_0045D434 != 0) {
    func_0020ECA0(*(int *)PS2_PTR(0x45D430));
  }
  g_0045D430 = 0;
  g_0045D434 = 0;
  return;
}

/* 0x0020ED30, 0x68 bytes. */
void func_0020ED30(void)
{
    int iVar2;
    long long lVar1;

  
  iVar2 = 0;
  do {
    lVar1 = func_0020DFE0(iVar2);
    if (lVar1 != 0) {
      func_0020E9D0(iVar2);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb6);
  if (g_0045D424 != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x45D424)));
    g_0045D424 = 0;
    g_0045D42C = 0;
    g_0045D428 = 0;
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

/* 0x00229E50, 0x104 bytes. */
int func_00229E50(int param_1, u8 *param_2)
{
    long long lVar4;
    u32 ** ppuVar5;
    u32 * puStack_4;
    u32 * puStack_8;
    u32 * puVar1;
    u32 * puVar2;
    u32 * puVar6;
    u32 uVar3;

  
  if (param_1 == 0) {
    puStack_4 = (u32 *)0x0;
  }
  else {
    puStack_4 = (u32 *)0x0;
    puStack_8 = (u32 *)0x0;
    puVar6 = (u32 *)PS2_PTR(param_1);
    puVar2 = (u32 *)PS2_PTR(*puVar6);
    while (puVar2 != (u32 *)0x0) {
      puVar1 = (u32 *)PS2_PTR(*puVar2);
      lVar4 = ((int (*)())param_2)(puVar2,param_1);
      if (lVar4 < 0) {
        ppuVar5 = &puStack_4;
      }
      else {
        ppuVar5 = &puStack_8;
      }
      *puVar2 = PS2_ADDR(*ppuVar5);
      *ppuVar5 = puVar2;
      puVar2 = puVar1;
    }
    puStack_4 = (u32 *)PS2_PTR(func_00229E50(PS2_ADDR(puStack_4),param_2));
    uVar3 = func_00229E50(PS2_ADDR(puStack_8),param_2);
    if (puStack_4 == (u32 *)0x0) {
      puStack_4 = puVar6;
    }
    else {
      puVar2 = puStack_4;
      for (puVar1 = (u32 *)PS2_PTR(*puStack_4); puVar1 != (u32 *)0x0;
          puVar1 = (u32 *)PS2_PTR(*puVar1)) {
        puVar2 = puVar1;
      }
      *puVar2 = PS2_ADDR(puVar6);
    }
    *puVar6 = uVar3;
  }
  return PS2_ADDR(puStack_4);
}

/* 0x0022A200, 0x26C bytes. */
void func_0022A200(int *param_1, u8 *param_2)
{
    int bVar1;
    float fVar21;
    int iVar11;
    int iVar14;
    int iVar18;
    u8 * iVar4;
    u8 * iVar5;
    int iVar6;
    u8 * iVar7;
    int iVar9;
    u8 * pbVar10;
    int * piVar12;
    int * piVar2;
    int * piVar20;
    int * piVar3;
    u32 * puVar16;
    u32 * puVar8;
    u32 uVar13;
    u32 uVar15;
    int uVar17;
    u32 uVar19;

  
  func_0022A120((int *)PS2_PTR(*(u32 *)(param_2 + 4)),PS2_ADDR(param_1 + 4));
  func_0022A120((int *)PS2_PTR(*(u32 *)(param_2 + 8)),PS2_ADDR(param_1 + 6));
  piVar2 = (int *)PS2_PTR(*(ps2ptr *)(param_2 + 4));
  uVar19 = 0;
  piVar3 = (int *)PS2_PTR(*(ps2ptr *)(param_2 + 8));
  iVar4 = (u8 *)PS2_PTR(*param_1);
  iVar5 = (u8 *)PS2_PTR(*piVar2);
  piVar20 = (int *)PS2_PTR(piVar3[1]);
  iVar6 = *(int *)(param_2 + 0xc);
  iVar7 = (u8 *)PS2_PTR(*piVar3);
  piVar12 = piVar3 + 1;
  if (piVar20 != (int *)0x0) {
    iVar14 = iVar6 * 8;
    while (uVar19 < 9) {
      if (((piVar20[3] & 1U) == 0) || ((piVar20[3] & 2U) != 0)) {
        iVar9 = piVar20[1] - *(int *)(iVar7 + 4);
        if (iVar9 < 0) {
          iVar9 = iVar9 + 0xf;
        }
        uVar13 = iVar9 >> 4 & 0xff;
        uVar15 = 0;
        bVar1 = *(u8 *)(iVar5 + iVar14 + uVar13 + 0x20);
        fVar21 = (float)piVar20[2];
        puVar16 = (u32 *)PS2_PTR(*(ps2ptr *)PS2_PTR((*(int *)(param_2 + 4) + 4)));
        puVar8 = (u32 *)PS2_PTR((*(int *)(param_2 + 4) + 4));
        if (puVar16 != (u32 *)0x0) {
          iVar9 = (int)PS2_ADDR(piVar20) - (int)PS2_ADDR((piVar3 + 4));
          iVar11 = iVar9 >> 4;
          if (iVar9 < 0) {
            iVar11 = iVar9 + 0xf >> 4;
          }
          do {
            if (8 < uVar15) {
              return;
            }
            if (((puVar16[3] & 1) == 0) || ((puVar16[3] & 2) != 0)) {
              iVar9 = puVar16[1] - *(int *)(iVar4 + 0x5c);
              if (iVar9 < 0) {
                iVar9 = iVar9 + 0xf;
              }
              pbVar10 = (u8 *)PS2_PTR((*(int *)(iVar4 + 0xf4) + (iVar9 >> 4) * 0x80 + iVar14 + uVar13));
              if ((*pbVar10 & 1) != 0) {
                iVar9 = param_1[1];
                iVar18 = (int)PS2_ADDR(puVar16) - (int)PS2_ADDR((piVar2 + 4));
                uVar17 = (u8)(iVar18 >> 4);
                param_1[1] = iVar9 + 1;
                param_1[iVar9 * 4 + 0xf5] = PS2_ADDR(param_2);
                *(char *)PS2_PTR(((int)PS2_ADDR(param_1) + iVar9 * 0x10 + 0x3de)) = (char)iVar6;
                if (iVar18 < 0) {
                  uVar17 = (u8)(iVar18 + 0xf >> 4);
                }
                *(u8 *)(param_1 + iVar9 * 4 + 0xf7) = uVar17;
                *(char *)PS2_PTR(((int)PS2_ADDR(param_1) + iVar9 * 0x10 + 0x3dd)) = (char)iVar11;
                param_1[iVar9 * 4 + 0xf6] =
                     (int)(fVar21 + (float)((u32)bVar1 + (u32)(*pbVar10 >> 4)) * 2000.0f +
                                    (float)puVar16[2] + 0.0f);
                param_1[iVar9 * 4 + 0xf4] = param_1[3];
                param_1[3] = (int)PS2_ADDR((param_1 + iVar9 * 4 + 0xf4));
              }
              puVar8 = puVar16;
              puVar16 = (u32 *)PS2_PTR(*puVar16);
            }
            else {
              puVar16 = (u32 *)PS2_PTR(*puVar16);
              *puVar8 = PS2_ADDR(puVar16);
            }
            uVar15 = uVar15 + 1;
          } while (puVar16 != (u32 *)0x0);
        }
        piVar12 = piVar20;
        piVar20 = (int *)PS2_PTR(*piVar20);
      }
      else {
        piVar20 = (int *)PS2_PTR(*piVar20);
        *piVar12 = (int)PS2_ADDR(piVar20);
      }
      uVar19 = uVar19 + 1;
      if (piVar20 == (int *)0x0) {
        return;
      }
    }
  }
  return;
}

/* 0x0022A5E0, 0xC8 bytes. */
int func_0022A5E0(int *param_1, int param_2)
{
    int bVar1;
    float fVar6;
    float fVar7;
    u8 * iVar2;
    int iVar3;
    unsigned long long * puVar5;
    unsigned long long uStack_8;
    u32 uVar4;

  
  puVar5 = (unsigned long long *)0x0;
  uVar4 = 0;
  fVar7 = 0.0f;
  bVar1 = *(u8 *)PS2_PTR((*param_1 + 0x1d));
  if (bVar1 != 0) {
    iVar3 = 0;
    do {
      iVar2 = (u8 *)PS2_PTR(param_1[1]);
      uStack_8 = *(unsigned long long *)(iVar2 + iVar3);
      fVar6 = (float)func_0018C3F0((float *)PS2_PTR(param_2),(float *)(&uStack_8));
      if ((puVar5 == (unsigned long long *)0x0) || (fVar6 < fVar7)) {
        fVar7 = fVar6;
        puVar5 = (unsigned long long *)(iVar2 + iVar3);
      }
      uVar4 = uVar4 + 1;
      iVar3 = iVar3 + 0x10;
    } while (uVar4 < bVar1);
  }
  return PS2_ADDR(puVar5);
}

/* 0x0022D910, 0xA8 bytes. */
void func_0022D910(int param_1)
{
    u8 auStack_4[4];
    int iVar1;
    long long lVar2;
    u32 * puVar3;
    u32 uStack_8;

  
  lVar2 = func_00141D98(1,auStack_4,&uStack_8);
  if (lVar2 == 1) {
    puVar3 = (u32 *)PS2_PTR(param_1);
    lVar2 = ((int (*)(u8 *, u32))PS2_FUNC(((u32 *)g_0042A340)[puVar3[1]]))((u8 *)puVar3, uStack_8);   /* the record, as the table's functions take it */
    if (lVar2 == 0) {
      if ((puVar3[1] == 0) && (iVar1 = puVar3[4], puVar3[4] = iVar1 + 1, iVar1 + 1 < 3)) {
        *puVar3 = 0;
        return;
      }
      *puVar3 = 2;
    }
    else {
      *puVar3 = 0xffffffff;
    }
    puVar3[4] = 0;
  }
  return;
}

/* 0x0022D9C0, 0x1EC bytes. */
void func_0022D9C0(u32 *param_1)
{
    int iVar1;
    int iVar2;
    int iVar4;
    long long lVar3;

  
  lVar3 = -1;
  iVar1 = param_1[2];
  iVar2 = param_1[1];
  if (iVar2 == 9) {
    lVar3 = func_001423C8(iVar1,0);
  }
  else if (iVar2 == 8) {
    lVar3 = func_001420A8(iVar1,0,param_1 + 5,0,1,iVar1 * 0x40 + 0x74a180);
  }
  else if (iVar2 == 7) {
    lVar3 = func_00141880(iVar1,0,param_1 + 5);
  }
  else if (iVar2 == 0) {
    lVar3 = func_00141EB8(iVar1,0,PS2_PTR(iVar1 * 0x14 + 0x74a144),PS2_PTR(iVar1 * 0x14 + 0x74a148),0);
  }
  else {
    iVar4 = iVar1 * 0x98;
    switch(iVar2) {
    case 1:
      lVar3 = func_00141758(iVar1,0,iVar4 + 0x74a0b8,*(u32 *)(g_0074A0A0 + iVar4));
      break;
    case 2:
      lVar3 = func_001418B8(*(u32 *)(g_0074A0A8 + iVar4));
      break;
    case 3:
      lVar3 = func_00141978(*(u32 *)(g_0074A0A8 + iVar4),*(u32 *)(g_0074A0AC + iVar4),
                           *(u32 *)(g_0074A0A4 + iVar4));
      break;
    case 4:
      lVar3 = func_00141B08(*(u32 *)(g_0074A0A8 + iVar4),*(u32 *)(g_0074A0B4 + iVar4),
                           *(u32 *)(g_0074A0B0 + iVar4));
      break;
    case 5:
      lVar3 = func_00141C20(*(u32 *)(g_0074A0A8 + iVar4),*(u32 *)(g_0074A0B4 + iVar4),
                           *(u32 *)(g_0074A0B0 + iVar4));
      break;
    case 6:
      lVar3 = func_001425B8(*(u32 *)(g_0074A0A8 + iVar4));
    }
  }
  if (lVar3 == 0) {
    param_1[3] = 0;
    *param_1 = 1;
  }
  else {
    iVar1 = param_1[3];
    param_1[3] = iVar1 + 1;
    if (2 < iVar1 + 1) {
      param_1[3] = 0;
      *param_1 = 2;
    }
  }
  return;
}

/* MISSING ['0x40e940', '0x40e944', '0x40e948', '0x40e94c', '0x40e950', '0x40e954', '0x40e958', '0x40e95c', '0x40e960', '0x40e964'] */

/* 0x0022F510, 0x218 bytes. */
void func_0022F510(void)
{
    int bVar2;
    int cVar1;
    long long lVar3;

  
  if (((*(u8 *)(g_005BC3A0 + 0x0)) & 0x20) == 0) {
    if (((*(u8 *)(g_005BC3A0 + 0x0)) & 8) != 0) {
      if ((*(u32 *)(g_005BC03C + 0x24)) == 2) {
        if ((*(u32 *)(g_00693703 + 0x0)) == '\x03') {
          func_001AFE20(*(int *)PS2_PTR(0x5BC060));
          (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xf7;
        }
        else if ((*(u32 *)(g_00693703 + 0x0)) == '\0') {
          (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xf7;
        }
      }
      else if ((*(u32 *)(g_005BC03C + 0x0)) == 0) {
        if (*(char *)PS2_PTR(((*(u32 *)(g_005BC03C + 0x24)) * 0x128 + 0x6934b3)) == '\0') {
          (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xf7;
          (*(u16 *)(g_00693388 + 0x2)) = (*(u16 *)(g_00693388 + 0x2)) | 0x8000;
          (*(u16 *)(g_00693388 + 0x0)) = (*(u16 *)(g_00693388 + 0x0)) | 0x8000;
          func_0017E110((*(u8 *)(g_00669DB2 + 0x0)));
          func_0023B530((*(u8 *)(g_00669DB2 + 0x1)));
        }
      }
      else {
        cVar1 = *(char *)PS2_PTR(((*(u32 *)(g_005BC03C + 0x24)) * 0x128 + 0x6934b3));
        if ((((cVar1 == '\0') || (bVar2 = true, cVar1 == '\x01')) || (cVar1 == '\b')) ||
           (cVar1 == '\x03')) {
          bVar2 = false;
        }
        if (!bVar2) {
          (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xf7;
        }
      }
    }
  }
  else {
    lVar3 = func_00102960(0);
    if (lVar3 != 0) {
      (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) & 0xdf;
      func_0022F730(1);
      (*(u8 *)(g_005BC3A0 + 0x0)) = (*(u8 *)(g_005BC3A0 + 0x0)) | 8;
    }
  }
  if ((((*(u8 *)(g_005BC3A0 + 0x4)) & 8) != 0) && ((*(char *)(g_0069382B + 0x0)) == '\x03')) {
    func_001AFE20(3);
    (*(u8 *)(g_005BC3A0 + 0x4)) = (*(u8 *)(g_005BC3A0 + 0x4)) & 0xf7;
  }
  return;
}
/* MISSING ['0x5bc03c', '0x693703'] */

/* MISSING ['0x5bc050', '0x5bc054', '0x692da0', '0x692da4'] */

/* 0x00247970, 0x48 bytes. */
void func_00247970(void)
{
  if ((*(u32 *)(g_00752940 + 0x0)) != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x752940)));
    (*(u32 *)(g_00752940 + 0x0)) = 0;
    func_00102EC0((unsigned char *)PS2_PTR((*(u32 *)(g_00752940 + 0x4))));
    (*(u32 *)(g_00752940 + 0x4)) = 0;
  }
  return;
}

/* MISSING ['0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c'] */

/* MISSING ['0x410ac0', '0x410ac4', '0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x5b4fc0', '0x5b4fc4', '0x5b4fc8', '0x5b4fd0', '0x5b4fd4', '0x5b4fd8', '0x5b5020', '0x5b5024', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c', '0x76ec80', '0x76ec84', '0x76ec88', '0x76ec8c', '0x76ec90', '0x76ec94', '0x76ec98', '0x76ec9c'] */

/* MISSING ['0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c'] */

/* MISSING ['0x410ac0', '0x410ac4', '0x5b4d80', '0x5b4d84', '0x5b4d88', '0x5b4d90', '0x5b4d94', '0x5b4d98', '0x5b4de0', '0x5b4de4', '0x5b4fc0', '0x5b4fc4', '0x5b4fc8', '0x5b4fd0', '0x5b4fd4', '0x5b4fd8', '0x5b5020', '0x5b5024', '0x76ec60', '0x76ec64', '0x76ec68', '0x76ec6c', '0x76ec70', '0x76ec74', '0x76ec78', '0x76ec7c', '0x76ec80', '0x76ec84', '0x76ec88', '0x76ec8c', '0x76ec90', '0x76ec94', '0x76ec98', '0x76ec9c'] */

/* 0x00271A10, 0x38 bytes. */
void func_00271A10(int param_1, int param_2)
{
  if (param_2 < 0x27) {
                    /* WARNING: Could not recover jumptable at 0x00271a34. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    ((int (*)())((u8 *)PS2_PTR(((ps2ptr *)g_0043F9A0)[(int)param_2])))();
    return;
  }
  return;
}

/* 0x00273B10, 0x1E4 bytes. */
void func_00273B10(void)
{
    int iVar2;
    int uVar1;

  
  if ((*(u8 *)(g_0076F62F + 0x0)) == 0) {
    (*(u8 *)(g_0076F62F + 0x0)) = 0;
    iVar2 = 0;
    do {
      uVar1 = 0;
      switch(iVar2) {
      case 0:
        break;
      case 1:
        uVar1 = 1;
        break;
      case 2:
        uVar1 = 2;
        break;
      case 3:
        uVar1 = 3;
        break;
      case 4:
        uVar1 = 4;
        break;
      case 5:
        uVar1 = 5;
        break;
      case 6:
        uVar1 = 7;
        break;
      case 7:
        uVar1 = 8;
        break;
      case 8:
        uVar1 = 9;
        break;
      case 9:
        uVar1 = 10;
        break;
      case 10:
        uVar1 = 0xb;
        break;
      case 0xb:
        uVar1 = 0xd;
        break;
      case 0xc:
        uVar1 = 0xe;
        break;
      case 0xd:
        uVar1 = 0xf;
        break;
      case 0xe:
        uVar1 = 0x10;
        break;
      case 0xf:
        uVar1 = 0x11;
        break;
      case 0x10:
        uVar1 = 0x12;
        break;
      case 0x11:
        uVar1 = 0x13;
        break;
      case 0x12:
        uVar1 = 0x14;
        break;
      case 0x13:
        uVar1 = 0x15;
        break;
      case 0x14:
        uVar1 = 0x16;
        break;
      case 0x15:
        uVar1 = 0x17;
        break;
      case 0x16:
        uVar1 = 0x18;
        break;
      case 0x17:
        uVar1 = 0x19;
      }
      iVar2 = iVar2 + 1;
      *(u8 *)PS2_PTR(((*(u8 *)(g_0076F62F + 0x0)) + 0x76f617)) = uVar1;
      (*(u8 *)(g_0076F62F + 0x0)) = (*(u8 *)(g_0076F62F + 0x0)) + 1;
    } while (iVar2 < 0x18);
    func_00273AB0();
  }
  else {
    func_00273AB0();
  }
  return;
}

/* 0x00278150, 0x16C bytes. */
void func_00278150(int param_1)
{
    int uVar1;

  
  uVar1 = (*(char *)(g_0076F3D4 + 0x0));
  (*(char *)(g_0076F3D4 + 0x0)) = param_1;
  switch(param_1) {
  case '\0':
    func_00273B10();
    func_00276DD0();
    return;
  case '\x01':
    (*(u8 *)(g_0076F3D4 + 0x1)) = 0xc;
    func_002771E0();
    break;
  case '\x02':
    (*(u8 *)(g_0076F3D4 + 0x1)) = 0xc;
    break;
  case '\x03':
    (*(u8 *)(g_0076F3D4 + 0x1)) = 0xc;
    func_00277420();
    func_00277C60();
    break;
  case '\x04':
    func_00277670();
    (*(u8 *)(g_0076F3D4 + 0x1)) = 0;
    (*(u8 *)(g_0076F3D4 + 0x2)) = 3;
    (*(char *)(g_0076F3D4 + 0x0)) = (*(char *)(g_0076F3D4 + 0x3)) + '\x06';
    break;
  case '\x05':
    (*(u8 *)(g_0076F3D4 + 0x2)) = 3;
    (*(u8 *)(g_0076F3D4 + 0x1)) = 0xc;
    func_00277960();
    func_00277C60();
    break;
  case '\x06':
  case '\a':
  case '\b':
  case '\t':
  case '\n':
    func_00277B90();
    break;
  case '\v':
    (*(u8 *)(g_0076F3D4 + 0x1)) = 0xc;
    (*(u8 *)(g_0076F3D4 + 0x2)) = 4;
    break;
  case '\f':
    (*(u8 *)(g_0076F3D4 + 0x1)) = 0xc;
    break;
  case '\r':
    (*(u8 *)(g_0076F3D4 + 0x1)) = 0x32;
    func_00277E30();
    break;
  case '\x0e':
    (*(u8 *)(g_0076F3D4 + 0x1)) = 0x19;
    break;
  case '\x0f':
    (*(u8 *)(g_0076F3D4 + 0x1)) = 0xc;
    func_001B8F60(0,6,8);
    func_00277FB0();
  }
  return;
}

/* 0x002787E0, 0x88 bytes. */
void func_002787E0(void)
{
    int iVar1;

  
  iVar1 = 0x305;
  do {
    func_0023ACC0(iVar1,1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 799);
  func_0023ACC0(0x302,2);
  func_0023ACC0(0x300,0);
  func_0023ADA0();
  if ((*(u32 *)(g_0076F3A0 + 0x8)) != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x76F3A8)));
    (*(u32 *)(g_0076F3A0 + 0x8)) = 0;
    (*(u32 *)(g_0076F3A0 + 0x0)) = 0;
  }
  return;
}

/* 0x00278FC0, 0x48 bytes. */
void func_00278FC0(int param_1, u16 *param_2, int param_3, int p3, int p4)
{
  func_001ABE40((unsigned char *)PS2_PTR((*(u32 *)(g_0076F3AC + 0x0))),param_1,*param_2,param_2[1],0,param_2[2],param_2[3],param_3, p4, p3);
  return;
}

/* 0x00279010, 0x60 bytes. */
void func_00279010(int param_1, short *param_2, int param_3, int param_4, int param_5, int p5, int p6, int p7)
{
    float fStack_10;
    float fStack_c;
    u32 uStack_4;
    u32 uStack_8;

  
  fStack_10 = (float)(int)*param_2;
  fStack_c = (float)(int)param_2[1];
  uStack_8 = 0;
  uStack_4 = 0;
  func_001ABB90((*(u32 *)(g_0076F3AC + 0x0)),param_1,(unsigned char *)(&fStack_10),param_3,(float *)PS2_PTR(param_5),param_4, param_1, p7);
  return;
}

/* MISSING ['0x76f790', '0x76f794', '0x76f798', '0x76f79c', '0x76f7a0', '0x76f7a4', '0x76f7a8', '0x76f7ac', '0x76f7b8'] */

/* MISSING ['0x43fe50'] */

/* 0x002863E0, 0x3C bytes, matching. */
void func_002863E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int p6)
{
  func_002CC190((unsigned char *)PS2_PTR(param_2),param_1,param_3,param_4,0,param_5,param_6,0x80, p6, 0);
  return;
}

/* MISSING ['0x4112a0', '0x4112a4', '0x4112a8', '0x4112ac', '0x4112b0', '0x4112b4', '0x4112b8', '0x4112bc', '0x4112c0'] */

/* 0x00290390, 0xD4 bytes. */
void func_00290390(int param_1, int param_2, int param_3, int param_4)
{
    u8 auStack_4[4];
    int iVar3;
    u8 * puVar2;
    unsigned long long uVar1;
    u32 uVar4;

  
  uVar4 = 0;
  iVar3 = 0;
  puVar2 = auStack_4;
  do {
    uVar1 = func_00362600(0,uVar4);
    *puVar2 = (char)uVar1;
    if (uVar1 < 0x1f) {
      iVar3 = iVar3 + 1;
    }
    uVar4 = uVar4 + 1;
    puVar2 = puVar2 + 1;
  } while (uVar4 < 2);
  if (iVar3 != 0) {
    func_0029A1C0(param_1,param_2,param_3,param_4,auStack_4,2,2,0, 3, 0, 0);
  }
  return;
}

/* MISSING ['0x4114d8', '0x4114dc', '0x4114e0'] */

/* MISSING ['0x411820', '0x411824', '0x411828', '0x41182c', '0x411830', '0x411834', '0x411838', '0x41183c', '0x411840', '0x411844', '0x411848', '0x41184c', '0x411850', '0x411854', '0x411858', '0x41185c'] */

/* MISSING ['0x411890', '0x411894', '0x411898', '0x41189c'] */

/* MISSING ['0x411980', '0x411984', '0x411988', '0x41198c', '0x411990', '0x411994', '0x411998', '0x41199c', '0x4119a0', '0x4119a4'] */

/* 0x0029D230, 0xD4 bytes. */
void func_0029D230(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    u32 auStack_20[6];
    u8 auStack_8[8];
    u32 * puVar3;
    u8 * puVar4;
    int uVar1;
    u32 uVar2;
    u32 uVar5;

  
  uVar5 = 0;
  puVar4 = auStack_8;
  puVar3 = auStack_20;
  do {
    uVar1 = func_00362C10(0,uVar5);
    *puVar4 = uVar1;
    uVar2 = func_00362D10(0,uVar5);
    *puVar3 = uVar2;
    uVar5 = uVar5 + 1;
    puVar4 = puVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (uVar5 < 6);
  func_0029ABA0(param_1,param_2,param_3,param_4,auStack_8,6,param_5,(int *)(auStack_20), 1);
  return;
}

/* MISSING ['0x411b50', '0x411b54', '0x411b58'] */

/* 0x002A7CE0, 0xA4 bytes. */
void func_002A7CE0(void)
{
    int iVar1;
    int * piVar2;

  
  iVar1 = 0;
  piVar2 = (int *)PS2_PTR(0x77cea0);
  do {
    if ((piVar2[2] != 0x11) && (piVar2[3] == 0)) {
      if (*piVar2 != 0) {
        func_00103000(0);
        func_00102EC0((unsigned char *)PS2_PTR(*piVar2));
        func_00103000(1);
        *piVar2 = 0;
      }
      if (piVar2[1] != 0) {
        func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x77CEA4)));
        piVar2[1] = 0;
      }
      piVar2[2] = 0x11;
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 0x10;
  } while (iVar1 < 4);
  return;
}

/* 0x002A9610, 0x44 bytes. */
void func_002A9610(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int p6)
{
  func_001ABE40((unsigned char *)PS2_PTR(param_1),1,param_2,param_3,0,param_4,param_5,param_6, p6, 0);
  return;
}

/* MISSING ['0x411eb0', '0x411eb4', '0x411eb8', '0x411ebc'] */

/* MISSING ['0x411ec0', '0x411ec4', '0x411ec8', '0x411ecc', '0x45cec7'] */

/* MISSING ['0x411ed0', '0x411ed4', '0x411ed8', '0x411edc', '0x411ee0', '0x411ee4'] */

/* MISSING ['0x411ef0', '0x411ef4', '0x411ef8', '0x411efc', '0x411f00', '0x411f04'] */

/* MISSING ['0x795ff0', '0x795ff4', '0x795ff8', '0x795ffc'] */

/* MISSING ['0x795fc4', '0x795fc8', '0x795fcc'] */

/* MISSING ['0x795790'] */

/* 0x002CE160, 0x44 bytes. */
void func_002CE160(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int p6)
{
  func_001ABE40((unsigned char *)PS2_PTR(param_1),0x28,param_2,param_3,0,param_4,param_5,param_6, p6, 0);
  return;
}

/* 0x002D68F0, 0x34 bytes. */
void func_002D68F0(void)
{
  if ((*(u32 *)(g_00799A6C + 0x0)) != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x799A6C)));
  }
  (*(u32 *)(g_00799A6C + 0x0)) = 0;
  return;
}

/* 0x002D6990, 0xA4 bytes. */
void func_002D6990(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int p7)
{
    float fStack_18;
    float fStack_1c;
    float fStack_20;
    int uStack_1;
    u32 uStack_14;
    int uStack_2;
    int uStack_3;
    int uStack_4;

  
  fStack_20 = (float)param_2;
  uStack_14 = 0x3f800000;
  fStack_1c = (float)param_3;
  fStack_18 = (float)param_4;
  if (param_7 == 0) {
    uStack_4 = 0x40;
    uStack_3 = 0x40;
    uStack_2 = 0x40;
  }
  else {
    uStack_4 = 0x80;
    uStack_3 = 0x80;
    uStack_2 = 0x80;
  }
  uStack_1 = param_6;
  func_001ABCE0((*(u32 *)(g_00799A6C + 0x0)),param_1,(unsigned char *)(&fStack_20),PS2_ADDR(&uStack_4),(float *)PS2_PTR(param_5),0, param_7, p7);
  return;
}

/* 0x002D8280, 0x38 bytes. */
void func_002D8280(u8 *param_1)
{
  if (*(int *)(param_1 + 0x78) != 5) {
    func_001AFE20(*(int *)((u8 *)(param_1) + 0x78));
  }
  (*(u8 *)(g_006934B9 + 0x0)) = 0;
  func_001B8BF0();
  return;
}

/* 0x002D8730, 0x1D4 bytes. */
void func_002D8730(u8 *param_1, int param_2, int param_3)
{
    u8 auStack_400[1024];
    unsigned long long uVar1;

  
  if (*(int *)(param_1 + 0x70) == 1) {
    uVar1 = func_0022DBB0();
    func_001204B0(auStack_400,PS2_PTR(0x4426c0),uVar1);
  }
  else if (*(int *)(param_1 + 0x70) == 2) {
    uVar1 = func_0022DBB0();
    func_001204B0(auStack_400,PS2_PTR(0x4426e0),uVar1);
  }
  else {
    uVar1 = func_0022DBB0();
    func_001204B0(auStack_400,PS2_PTR(0x442700),uVar1);
  }
  switch(param_2) {
  case 0:
    if (*(int *)(param_1 + 0x70) == 1) {
      func_001204B0(PS2_PTR(param_3),PS2_PTR(0x442718),0x442720);
      return;
    }
    if (*(int *)(param_1 + 0x70) == 2) {
      func_001204B0(PS2_PTR(param_3),PS2_PTR(0x442718),0x442740);
    }
    else {
      func_001204B0(PS2_PTR(param_3),PS2_PTR(0x442718),0x442760);
    }
    break;
  case 1:
    func_001204B0(PS2_PTR(param_3),PS2_PTR(0x442718),auStack_400);
    break;
  case 2:
    func_001204B0(PS2_PTR(param_3),PS2_PTR(0x442778),auStack_400,auStack_400);
    break;
  case 3:
    func_001204B0(PS2_PTR(param_3),PS2_PTR(0x442778),auStack_400,0x442780);
    break;
  case 4:
    func_001204B0(PS2_PTR(param_3),PS2_PTR(0x442778),auStack_400,0x442790);
  }
  return;
}

/* MISSING ['0x45d610'] */

/* MISSING ['0x45d610'] */

/* 0x002E0000, 0x3C bytes. */
void func_002E0000(int param_1, int p1, int p2, int p3, int p4)
{
  func_002DFF70(param_1, p1, p2, p3, p4);
  func_002456C0(param_1,0x442a00,0x442ba0);
  return;
}

/* 0x002E0040, 0x3C bytes. */
void func_002E0040(int param_1, int p1, int p2, int p3, int p4)
{
  func_002DFF40(param_1, p1, p2, p3, p4);
  func_002456C0(param_1,0x442a00,0x442ba8);
  return;
}

/* 0x002E18C0, 0x154 bytes. */
void func_002E18C0(u8 *param_1, float *param_2, int param_3)
{
    float afStack_20[3];
    float fStack_10;
    float fStack_8;
    float fVar1;
    u32 uStack_14;
    u32 uStack_4;
    u32 uStack_c;

  
  g_70000718 = PS2_ADDR(afStack_20);
  fVar1 = *(float *)(param_1 + 0xc) + 0.1f;
  uStack_c = 0;
  afStack_20[1] = 0.0f;
  uStack_4 = 0x3f800000;
  uStack_14 = 0x3f800000;
  if ((param_3 & 1) == 0) {
    afStack_20[2] = param_2[2] - fVar1;
    fStack_8 = param_2[6] + fVar1;
    g_70000710 = 0.0f;
    g_70000714 = fVar1 * 2.0f + (param_2[6] - param_2[2]) + 0.0f;
  }
  else {
    afStack_20[0] = *param_2 - fVar1;
    fStack_10 = param_2[4] + fVar1;
    g_70000710 = fVar1 * 2.0f + (param_2[4] - *param_2) + 0.0f;
    g_70000714 = 0.0f;
  }
  if (param_3 == 0) {
    afStack_20[0] = param_2[4] + fVar1;
    fStack_10 = afStack_20[0];
  }
  else if (param_3 == 1) {
    afStack_20[2] = param_2[6] + fVar1;
    fStack_8 = afStack_20[2];
  }
  else if (param_3 == 2) {
    afStack_20[0] = *param_2 - fVar1;
    fStack_10 = afStack_20[0];
  }
  else {
    afStack_20[2] = param_2[2] - fVar1;
    fStack_8 = afStack_20[2];
  }
  g_7000071C = g_70000718;
  ((int (*)())((u8 *)PS2_PTR(((ps2ptr *)g_00442D20)[(int)param_3 * 2])))();
  return;
}

/* 0x002E67B0, 0x44 bytes. */
void func_002E67B0(int p0, int p1)
{
  if (((*(u32 *)(g_00669F60 + 0x3C)) < 0x5dc) && (((*(u32 *)(g_00669F60 + 0x0)) & 2) != 0)) {
    func_0019EBA0(p0, p1);
  }
  return;
}

/* MISSING ['0x7a1c10', '0x7a1c14', '0x7a1c18', '0x7a1c1c', '0x7a1e30', '0x7a1e34'] */

/* 0x002EF080, 0xCC bytes. */
void func_002EF080(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int p6)
{
    int iVar1;
    int iVar2;

  
  func_002C7310(param_2,param_3,0,param_4,param_5,0x80, p6);
  iVar1 = (int)param_4;
  if (param_4 < 0) {
    iVar1 = iVar1 + 1;
  }
  iVar2 = (int)param_5;
  if (param_5 < 0) {
    iVar2 = iVar2 + 1;
  }
  func_001ABE40((unsigned char *)PS2_PTR(param_1),0x3c,(int)param_2 + (iVar1 >> 1),(int)param_3 + (iVar2 >> 1),0,
               0xffffffffffffffff,0xffffffffffffffff,param_6, p6, 1);
  return;
}

/* MISSING ['0x45cff0', '0x45cff4', '0x45cff8', '0x45cffc', '0x45d6ec'] */

/* MISSING ['0x45d73c'] */

/* MISSING ['0x45d730'] */

/* MISSING ['0x417468', '0x41746c', '0x417470'] */

/* 0x00382770, 0x608 bytes. */
void func_00382770(int param_1, int param_2, int *param_3)
{
    u8 auStack_10[16];
    int iVar2;
    int iVar4;
    u32 uVar1;
    unsigned long long uVar3;
    unsigned long long uVar5;

  
  param_1 = param_1 * 0x5c;
  if (param_2 == 0) {
    func_002C7310(0,param_1 + 0x3d,0,0x200,0x5c,0x80,1);
  }
  else {
    func_002C7A30(0,param_1 + 0x3d,0,0x200,0x5c,0x80,1);
  }
  uVar3 = PS2_ADDR(func_001050F0());
  *(unsigned long long *)PS2_PTR(((int)uVar3 + 0x10)) = 0x8000000044;
  *(unsigned long long *)PS2_PTR(((int)uVar3 + 0x18)) = 0x43;
  func_00105230((unsigned char *)PS2_PTR(uVar3),1);
  if (*param_3 == 0) {
    uVar3 = PS2_ADDR(func_00372E50());
    iVar2 = func_00146CA0(16.0f,(const unsigned char *)PS2_PTR(uVar3));
    (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
    uVar3 = PS2_ADDR(func_00372E50());
    iVar4 = -iVar2 + 0x200;
    if (iVar4 < 0) {
      iVar4 = -iVar2 + 0x201;
    }
    func_00146270((const unsigned char *)PS2_PTR(uVar3),iVar4 >> 1,param_1 + 99,1,0);
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
  }
  else {
    func_003B5970(8,param_1 + 0x48,0,0x1f0,0x18,0x80,1);
    (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
    func_00146B40((const unsigned char *)(param_3 + 10),0x14,param_1 + 0x4b,0x7a,0x10,1,0);
    (*(u32 *)(g_0056CCA4 + 0x0)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 6;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 6;
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
    uVar3 = PS2_ADDR(func_003724D0(param_3[1]));
    func_00146B40((const unsigned char *)PS2_PTR(uVar3),0x9e,param_1 + 0x4b,0xd4,0x10,1,0);
    (*(u32 *)(g_0056CCA4 + 0x1C)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x20)) = 0x41800000;
    (*(u32 *)(g_0056CCA4 + 0x0)) = 5;
    (*(u32 *)(g_0056CCA4 + 0x4)) = 5;
    (*(u32 *)(g_0056CCA4 + 0x8)) = 5;
    (*(u32 *)(g_0056CCA4 + 0xC)) = 5;
    func_001204B0(auStack_10,PS2_PTR(0x459540),param_3[2]);
    func_002C4F40(16.0f,(char *)(auStack_10),0x178,param_1 + 0x4b,1,0,6);
    func_003B53C0(0x1ac,param_1 + 0x43,0,0x80,1,param_3[3]);
    uVar3 = PS2_ADDR(func_00372A10(param_3[4]));
    func_002C4C50(16.0f,(char *)PS2_PTR(uVar3),0x18c,param_1 + 0x79,0x5c,1,0,6);
    func_001204B0(auStack_10,PS2_PTR(0x459550),param_3[5]);
    func_002C5020(16.0f,(char *)(auStack_10),0x1d8,param_1 + 99,1,0,6);
    func_003B5410(0x1d8,param_1 + 0x5f,0,0x80,1,6);
    func_003B5410(0xf8,param_1 + 0x5f,0,0x80,1,4);
    func_001204B0(auStack_10,PS2_PTR(0x459550),param_3[6]);
    func_002C5020(16.0f,(char *)(auStack_10),0x168,param_1 + 99,1,0,6);
    func_003B5410(0x18,param_1 + 0x5f,0,0x80,1,1);
    func_002C4D60(16.0f,(char *)PS2_PTR((g_0042F880)[param_3[7]]),0xd4,param_1 + 99,1,0,6);
    func_003B5410(0x18,param_1 + 0x74,0,0x80,1,0);
    uVar5 = (unsigned long long)param_3[8];
    if (0xcdfe5c4 < uVar5) {
      uVar5 = 0xcdfe5c4;
    }
    uVar1 = (int)uVar5 % 180000;
    iVar2 = (int)((uVar5 & 0xffffffff) * 0x74d3b7bb >> 0x20);
    func_001204B0(auStack_10,PS2_PTR(0x459580),((u32)((int)uVar5 - iVar2) >> 1) + iVar2 >> 0x11,uVar1 / 3000,
                 (u32)((int)uVar1 % 3000) / 0x32);
    func_002C5020(16.0f,(char *)(auStack_10),0xd4,param_1 + 0x79,1,0,6);
    func_003B5410(0xf8,param_1 + 0x74,0,0x80,1,2);
    func_001204B0(auStack_10,PS2_PTR(0x459550),param_3[9]);
    func_002C5020(16.0f,(char *)(auStack_10),0x168,param_1 + 0x79,1,0,6);
    func_002CA490(0x10,param_1 + 0x74,0,0xd0,3,0x80,1);
    func_002CA490(0x10,param_1 + 0x89,0,0xd0,3,0x80,1);
    func_002CA490(0x184,param_1 + 0x74,0,0x6c,3,0x80,1);
    func_002CA490(0xf0,param_1 + 0x74,0,0x84,3,0x80,1);
    func_002CA490(0xf0,param_1 + 0x89,0,0x84,3,0x80,1);
    func_002CA490(0x184,param_1 + 0x89,0,0x6c,3,0x80,1);
  }
  return;
}

/* 0x00383270, 0x40 bytes, matching. */
void func_00383270(int param_1, int param_2, int param_3, int p3)
{
  func_001ABE40((unsigned char *)PS2_PTR(param_1),0xd1,param_2,param_3,0,0x160,0x38,0x80, p3, 0);
  return;
}

/* 0x003832E0, 0x44 bytes, matching. */
void func_003832E0(int param_1, int param_2, int param_3, int param_4, int p4)
{
  func_001ABE40((unsigned char *)PS2_PTR(param_1),param_4 + 0x5f,param_2,param_3,0,200,0x28,0x80, p4, 0);
  return;
}

/* 0x00383330, 0x30 bytes, matching. */
void func_00383330(int param_1, int param_2, int p2, int p3, int p4, int p5)
{
  func_001ABE40((unsigned char *)PS2_PTR(param_1),param_2 + 0xa4, p2, p3, p4, 0xe8, 0x20, 0x80, p5, 0);
  return;
}

/* 0x00383610, 0x40 bytes, matching. */
void func_00383610(int param_1, int param_2, int param_3, int param_4, int p4)
{
  func_001ABE40((unsigned char *)PS2_PTR(param_1),0x14d,param_2,param_3,0,0xe0,0x98,param_4, p4, 0);
  return;
}

/* 0x00383650, 0x22C bytes. */
void func_00383650(int param_1, int param_2, int param_3, int param_4, int param_5, int *param_6, int *param_7)
{
    int bVar4;
    int bVar5;
    int iVar1;
    int iVar10;
    int iVar13;
    int iVar14;
    int iVar2;
    int iVar3;
    int * piVar9;
    unsigned long long uVar11;
    u32 uVar12;
    u32 uVar6;
    unsigned long long uVar7;
    u32 uVar8;

  
  func_002C7310(param_2,param_3,0,0x200,0xf8,param_5,param_4);
  iVar14 = (int)param_2;
  iVar13 = (int)param_3;
  if (param_5 == 0x80) {
    func_00383610(param_1,iVar14 + 0x90,iVar13 + 0x30,0x80,param_4);
    uVar12 = 0;
    do {
      uVar6 = uVar12;
      if ((int)uVar12 < 0) {
        uVar6 = uVar12 + 3;
      }
      uVar8 = uVar12 & 3;
      iVar3 = ((int)uVar6 >> 2) * 0x15e;
      if (((int)uVar12 < 0) && (uVar8 != 0)) {
        uVar8 = uVar8 - 4;
      }
      iVar1 = *param_6;
      bVar5 = false;
      iVar10 = 0;
      piVar9 = param_7;
      do {
        iVar2 = *piVar9;
        bVar4 = false;
        if ((-1 < iVar2) && (iVar2 < 0x19f)) {
          bVar4 = true;
        }
        if ((bVar4) && (iVar2 == iVar1)) {
          bVar5 = true;
          break;
        }
        iVar10 = iVar10 + 1;
        piVar9 = piVar9 + 1;
      } while (iVar10 < 7);
      if (bVar5) {
        uVar11 = 0x40;
      }
      else {
        uVar11 = 0x80;
      }
      func_001ABE40((unsigned char *)PS2_PTR(param_1),0x14e,iVar14 + iVar3 + 0x10,iVar13 + uVar8 * 0x30 + 0x24,0,0x88,0x1c,
                   uVar11, param_4, 0);
      if (bVar5) {
        uVar11 = 0;
      }
      else {
        uVar11 = 6;
      }
      uVar7 = PS2_ADDR(func_002F2890(iVar1));
      func_002C4C50(16.0f,(char *)PS2_PTR(uVar7),iVar14 + iVar3 + 0x14,iVar13 + uVar8 * 0x30 + 0x2a,0x7a,param_4,
                   0,uVar11);
      uVar12 = uVar12 + 1;
      param_6 = param_6 + 1;
    } while ((int)uVar12 < 8);
  }
  func_001ABE40((unsigned char *)PS2_PTR(param_1),0x14f,iVar14 + 0xc4,iVar13 + 0x58,0,0x78,0x40,param_5, param_4, 0);
  return;
}

/* 0x00383AB0, 0x40 bytes, matching. */
void func_00383AB0(int param_1, int param_2, int param_3, int param_4, int param_5, int p5)
{
  func_001ABE40((unsigned char *)PS2_PTR(param_1),0xda,param_2,param_3,0,param_4,param_5,0x80, p5, 0);
  return;
}

/* 0x00383C10, 0x30 bytes. */
void func_00383C10(u16 *param_1, int param_2)
{
    int uVar1;

  
  uVar1 = *(u16 *)((g_004595F0 + 0x2) + param_2 * 4);
  *param_1 = *(u16 *)((g_004595F0 + 0x0) + param_2 * 4);
  param_1[1] = uVar1;
  return;
}

/* 0x00383C40, 0x124 bytes. */
void func_00383C40(int param_1, int param_2, u8 *param_3, int param_4)
{
    u32 * puVar1;

  
  func_00118850((unsigned char *)PS2_PTR(param_1),0x34);
  puVar1 = (u32 *)PS2_PTR(param_1);
  puVar1[0xc] = PS2_ADDR(param_3 + *(int *)(param_3 + 8) * *(int *)(param_4 * 8 + param_3 + 0x10));
  puVar1[7] = 0x3f800000;
  puVar1[8] = 0x3f800000;
  if (param_2 == 1) {
    *puVar1 = 99;
    puVar1[3] = 0xc2d00000;
    puVar1[5] = 0x42ac0000;
    puVar1[4] = 0x43c50000;
    puVar1[6] = puVar1[5];
    puVar1[7] = 0x3f000000;
    puVar1[8] = 0x3f000000;
    puVar1[1] = 0;
    puVar1[2] = 0x437f0000;
    puVar1[10] = 0x43960000;
    puVar1[0xb] = 0x43b40000;
  }
  else if (param_2 == 0) {
    *puVar1 = 0x65;
    puVar1[3] = 0xc2c80000;
    puVar1[5] = 0x43040000;
    puVar1[4] = puVar1[3];
    puVar1[6] = puVar1[5];
    puVar1[1] = 0x42800000;
    puVar1[2] = 0x43bf0000;
    puVar1[10] = 0;
    puVar1[0xb] = 0x42960000;
  }
  return;
}

/* 0x0038F560, 0x54 bytes. */
void func_0038F560(void)
{
  func_003A9AF0(1);
  func_003A5E20();
  if (g_0045D7D8 != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x45D7D8)));
    g_0045D7D8 = 0;
  }
  if (g_0045D7D4 != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x45D7D4)));
    g_0045D7D4 = 0;
  }
  return;
}

/* MISSING ['0x7ba7f8'] */

/* 0x003A5E20, 0x174 bytes. */
void func_003A5E20(void)
{
    u8 * iVar1;
    int iVar2;

  
  (*(u32 *)(g_007BACC4 + 0x6C)) = 0;
  (*(u32 *)(g_007BACC4 + 0x70)) = 0;
  iVar2 = 0;
  (*(u32 *)(g_007BACC4 + 0x74)) = 0;
  (*(u32 *)(g_007BACC4 + 0x78)) = 0;
  (*(u32 *)(g_007BACC4 + 0x7C)) = 0;
  (*(u32 *)(g_007BACC4 + 0x80)) = 0;
  (*(u32 *)(g_007BACC4 + 0x108)) = 0;
  (*(u32 *)(g_007BACC4 + 0x120)) = 0;
  (*(u32 *)(g_007BACC4 + 0x10C)) = 0;
  (*(u32 *)(g_007BACC4 + 0x110)) = 0;
  (*(u32 *)(g_007BACC4 + 0x114)) = 0;
  (*(u32 *)(g_007BACC4 + 0x118)) = 0;
  (*(u32 *)(g_007BACC4 + 0x11C)) = 0;
  (*(u32 *)(g_007BACC4 + 0x124)) = 0;
  (*(u32 *)(g_007BACC4 + 0x128)) = 0xffffffff;
  (*(u32 *)(g_007BACC4 + 0x84)) = 0xb;
  (*(u32 *)(g_007BACC4 + 0x88)) = 0xffffffff;
  (*(u32 *)(g_007BACC4 + 0x8C)) = 1;
  (*(u32 *)(g_007BACC4 + 0x104)) = 0;
  (*(u32 *)(g_007BACC4 + 0x90)) = 1;
  iVar1 = g_007BAC40;
  do {
    *(u8 *)(iVar1 + 0x1b0) = 0xff;
    iVar2 = iVar2 + 5;
    *(u8 *)(iVar1 + 0x1c9) = 0;
    *(u8 *)(iVar1 + 0x1fb) = 0;
    *(u8 *)(iVar1 + 0x214) = 0;
    *(u8 *)(iVar1 + 0x1e2) = 0x1e;
    *(u8 *)(iVar1 + 0x1b1) = 0xff;
    *(u8 *)(iVar1 + 0x1ca) = 0;
    *(u8 *)(iVar1 + 0x1fc) = 0;
    *(u8 *)(iVar1 + 0x215) = 0;
    *(u8 *)(iVar1 + 0x1e3) = 0x1e;
    *(u8 *)(iVar1 + 0x1b2) = 0xff;
    *(u8 *)(iVar1 + 0x1cb) = 0;
    *(u8 *)(iVar1 + 0x1fd) = 0;
    *(u8 *)(iVar1 + 0x216) = 0;
    *(u8 *)(iVar1 + 0x1e4) = 0x1e;
    *(u8 *)(iVar1 + 0x1b3) = 0xff;
    *(u8 *)(iVar1 + 0x1cc) = 0;
    *(u8 *)(iVar1 + 0x1fe) = 0;
    *(u8 *)(iVar1 + 0x217) = 0;
    *(u8 *)(iVar1 + 0x1e5) = 0x1e;
    *(u8 *)(iVar1 + 0x1b4) = 0xff;
    *(u8 *)(iVar1 + 0x1cd) = 0;
    *(u8 *)(iVar1 + 0x1ff) = 0;
    *(u8 *)(iVar1 + 0x218) = 0;
    *(u8 *)(iVar1 + 0x1e6) = 0x1e;
    iVar1 = iVar1 + 5;
  } while (iVar2 < 0x19);
  func_003A9170();
  func_003A5C10();
  if ((*(u32 *)(g_007BACC4 + 0x0)) != 0) {
    func_00102EC0((unsigned char *)PS2_PTR(*(int *)PS2_PTR(0x7BACC4)));
    (*(u32 *)(g_007BACC4 + 0x0)) = 0;
  }
  return;
}

/* 0x003A6450, 0x48 bytes, matching. */
void func_003A6450(int *param_1, int *param_2, int p2)
{
  func_003A6060(param_1, param_2, p2);
  *param_1 = *param_1 + 0xc;
  *param_2 = *param_2 + 0xc;
  return;
}

/* MISSING ['0x45d7fc'] */

/* MISSING ['0x41c160', '0x41c164', '0x41c168', '0x41c16c', '0x41c170', '0x41c174', '0x41c178', '0x41c17c'] */

/* MISSING ['0x41c400', '0x41c404', '0x41c408', '0x41c40c'] */

/* MISSING ['0x41d008', '0x41d00c', '0x41d010'] */

/* MISSING ['0x41d2e0', '0x41d2e4', '0x41d2e8', '0x41d2ec'] */
