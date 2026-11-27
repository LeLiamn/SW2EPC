/*
 * gen_380000.c - small functions between 0x00380000 and 0x00400000, generated from Ghidra
 * output (access widths from the disassembly) and kept only when their compiled size is within
 * 10 % of the original. Machine-like: to be cleaned up by hand later.
 *
 * Decompiled by reading the original machine code (Ghidra + R5900 extension, checked against the
 * disassembly). Unknown functions and globals keep neutral names (func_/g_ + address); comments
 * with a question mark are hypotheses.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u8 g_00799A20[0x18];
extern u8 g_007B4E60[0x18];
extern u8 g_007B9EA0[0x18];
extern u8 g_007B9F44[0x18];
extern u8 g_007BACB8[0x18];
extern u8 g_007BC0C0[0x18];
extern u8 g_007BC0F0[0x18];
#define true 1
#define false 0

extern u8 g_00417650[0x4];
extern u8 g_00418EF0[0x21];
extern u8 g_0041C080[0x4];
extern u8 g_0041C0C0[0x4];
extern u8 g_0041C0E0[0x44];
extern u8 g_00428138[0x4];
extern u8 g_00459720[0xE];
extern u8 g_00459B60[0x8];
extern u8 g_00459C10[0x10];
extern u8 g_00459EF0[0x4];
extern u8 g_0045A830[0x10B];
extern u8 g_0045A894[0x20];
extern u8 g_0045A8B0[0x8C];
extern u8 g_0045AD90[0x4];
extern u8 g_0045C5C0[0x3C];
extern u8 g_0045D7DC[0x8];
extern u8 g_0050074C[0x1A];
extern u8 g_005BA6A0[0x4];
extern u8 g_00669D60[0x10];
extern u8 g_00669DB8[0x4];
extern u8 g_00669DEC[0x4C];
extern u8 g_00669F9C[0x8];
extern u8 g_0068F0F8[0x8];
extern u8 g_00799A24[0x24];
extern u8 g_007B9E58[0x10];
extern u8 g_007B9F40[0x4];
extern u8 g_007BA5CC[0x14];
extern u8 g_007BA8B0[0x10];
extern u8 g_007BA8B8[0x10];
extern u8 g_007BA8BC[0x18];
extern u8 g_007BA8C4[0x4];
extern u8 g_007BAC20[0x1C];
extern u8 g_007BAC24[0x18];
extern u8 g_007BAC34[0x8];
extern u8 g_007BAC38[0x4];
extern u8 g_007BAC40[0x10];
extern u8 g_007BACB4[0x13C];
extern u8 g_007BACC4[0x12C];
extern u8 g_007BADC4[0x4];
extern u8 g_007BADC8[0x28];
extern u8 g_007BAE70[0x24];
extern u8 g_007BAE74[0x4];
extern u8 g_007BAE78[0x8];
extern u8 g_007BAE7C[0x14];
extern u8 g_007BAE88[0x4];
extern u8 g_007BC120[0x10];
extern u8 g_007BEAD0[0xC];
extern u8 g_007BFDD8[0xC];
extern int g_0045D1C8;   /* (small data) */
extern int g_0045D7D4;   /* (small data) */
extern int g_0045D7D8;   /* (small data) */
extern int g_0045D824;   /* (small data) */
extern u32 g_7000015C;   /* (scratchpad) */

int func_00101470();
int func_001020C0();
int func_001026D0();
int func_00102960();
int func_00102EC0();
int func_00104AC0();
int func_00104D00();
int func_001050F0();
int func_00105230();
int func_00105B40();
int func_00105BE0();
int func_00106C50();
int func_00106C90();
int func_00106F10();
int func_00118AC0();
int func_0011EB80();
int func_001204B0();
int func_00120928();
int func_001707A0();
int func_0017D8E0();
int func_0019FBC0();
int func_001A11F0();
int func_001A93A0();
int func_001A9B30();
int func_001AA2C0();
int func_001ABE40();
int func_0021A630();
int func_0021A640();
int func_0023AD10();
void func_002C5AC0(float f, u8 *g, int a, int b, int c, int d);
int func_002C5AE0();
int func_002C6040();
int func_002C7310();
int func_002F27D0();
int func_002F2890();
int func_002F2970();
int func_002F2BB0();
int func_002F33F0();
int func_002F3440();
int func_002F34E0();
int func_002F3660();
int func_002F3770();
int func_002F3960();
int func_002F39F0();
int func_002F3BB0();
int func_002F3CF0();
int func_002F3DC0();
int func_002F3E70();
int func_002F3F20();
int func_002F4080();
int func_002F4660();
int func_002F46D0();
int func_002F47A0();
int func_002F4820();
int func_002F4900();
int func_002F4980();
int func_002F4BB0();
int func_002F4C40();
int func_002F4D40();
int func_002F4DD0();
int func_002F4ED0();
int func_002F4F60();
int func_002F5060();
int func_002F50F0();
int func_002F51F0();
int func_002F5280();
int func_002F5380();
int func_002F5410();
int func_002F5510();
int func_002F55A0();
int func_002F56A0();
int func_002F5730();
int func_002F57A0();
int func_002F57F0();
int func_002F5840();
int func_002F5930();
int func_002F59A0();
int func_002F5BE0();
int func_002F5CC0();
int func_002F5D30();
int func_002F5E10();
int func_002F5E80();
int func_002F5F60();
int func_002F5FD0();
int func_002F60B0();
int func_002F6120();
int func_002F6200();
int func_002F6270();
int func_002F6350();
int func_002F63C0();
int func_002F64A0();
int func_002F6510();
int func_002F65F0();
int func_002F6660();
int func_002F6740();
int func_002F6850();
int func_002F7300();
int func_002F7410();
int func_002F77A0();
int func_002F78C0();
int func_002F7900();
int func_002F7B10();
int func_002F7D90();
int func_002F8CB0();
int func_002F8F20();
int func_002F9060();
int func_002F9190();
int func_002F9480();
int func_002F9990();
int func_002F9C90();
int func_002FAFA0();
int func_002FB2D0();
int func_002FB3B0();
int func_002FB430();
int func_002FC2C0();
int func_002FC660();
int func_0030AAD0();
int func_0030AB90();
int func_0030ABF0();
int func_0030AFF0();
int func_0030B1B0();
int func_0030B240();
int func_0030C280();
int func_0030C6A0();
int func_0030CB00();
int func_0030CB50();
int func_0030CD60();
int func_0030CE90();
int func_0030CF50();
int func_0030D150();
int func_0030D7D0();
int func_0030E100();
int func_0030E140();
int func_0030E1F0();
int func_0030E390();
int func_00315510();
int func_00327140();
int func_00327170();
int func_00327820();
int func_00327C00();
int func_00327C70();
int func_00327CC0();
int func_00327D50();
int func_00327D60();
int func_00327E50();
int func_003280E0();
int func_00328270();
int func_00328A00();
int func_00328AA0();
int func_00328B30();
int func_00329450();
int func_003294A0();
int func_00329540();
int func_00329680();
int func_00329850();
int func_00329860();
int func_0032D2F0();
int func_0032D9C0();
int func_0032E950();
int func_0032EB40();
int func_0032EC50();
int func_0032EE10();
int func_00337A10();
int func_0035DB20();
int func_0035F780();
int func_003620B0();
int func_003620E0();
int func_00362160();
int func_003621B0();
int func_00362220();
int func_00362290();
int func_003622F0();
int func_00362320();
int func_003623B0();
int func_003625B0();
int func_00362600();
int func_00362840();
int func_00362990();
int func_00362AD0();
int func_00362B00();
int func_00362B60();
int func_003635F0();
int func_00363620();
int func_003636F0();
int func_00363720();
int func_003637D0();
int func_00365450();
int func_00365460();
int func_00365470();
int func_0036B260();
int func_0036B4A0();
int func_0036B4D0();
int func_0036B6C0();
int func_0036B8C0();
int func_0036B940();
int func_0036B980();
int func_0036D230();
int func_0036D310();
int func_0036DBA0();
int func_0036DC80();
int func_00372680();
int func_003726B0();
int func_003726E0();
int func_00372710();
int func_00372E30();
int func_003737E0();
int func_00373F60();
int func_00374250();
int func_00374E00();
int func_00374EE0();
int func_00375140();
int func_00375B90();
int func_00376100();
int func_003762C0();
int func_0037DA70();
int func_0037FD50();
int func_00380E80();
int func_003820C0();
int func_00382310();
int func_003823B0();
int func_00382410();
int func_00382590();
int func_00383C40();
int func_00384060();
int func_00388140();
int func_00388340();
int func_00389050();
int func_00389090();
int func_003890B0();
int func_00389B40();
int func_0038D030();
int func_0038D120();
int func_0038D140();
int func_0038D160();
int func_0038D180();
int func_0038D2B0();
int func_0038DC40();
int func_0038DE60();
int func_0038E730();
int func_0038E750();
int func_0038F5E0();
int func_0038FB10();
int func_00390760();
int func_00390940();
int func_00391250();
int func_00391C60();
int func_00391CC0();
int func_00391EB0();
int func_00397B00();
int func_00397B10();
int func_00397F00();
int func_00397F40();
int func_00398630();
int func_0039A630();
int func_0039AC20();
int func_0039AD50();
int func_0039AF30();
int func_0039AF70();
int func_0039BA70();
int func_0039BAC0();
int func_0039BB00();
int func_0039BCE0();
int func_0039C540();
int func_0039C690();
int func_0039C740();
int func_0039D5E0();
int func_0039D930();
int func_0039E650();
int func_0039E6E0();
int func_0039E720();
int func_0039E740();
int func_0039E7C0();
int func_0039EFB0();
int func_0039F040();
int func_0039F920();
int func_0039F940();
int func_0039F950();
int func_0039F9E0();
int func_0039FBF0();
int func_0039FC30();
int func_0039FC70();
int func_0039FCA0();
int func_0039FE00();
int func_0039FF60();
int func_003A0040();
int func_003A00C0();
int func_003A02C0();
int func_003A03E0();
int func_003A0440();
int func_003A0560();
int func_003A05B0();
int func_003A05F0();
int func_003A0630();
int func_003A0670();
int func_003A06B0();
int func_003A06F0();
int func_003A0730();
int func_003A0770();
int func_003A07B0();
int func_003A07F0();
int func_003A0830();
int func_003A0870();
int func_003A08B0();
int func_003A08F0();
int func_003A0930();
int func_003A0970();
int func_003A09B0();
int func_003A09F0();
int func_003A0A30();
int func_003A0A70();
int func_003A0AB0();
int func_003A0B20();
int func_003A0BA0();
int func_003A0C50();
int func_003A0CB0();
int func_003A0D10();
int func_003A0D50();
int func_003A0D90();
int func_003A0DD0();
int func_003A0E90();
int func_003A0EC0();
int func_003A0F30();
int func_003A0F60();
int func_003A1040();
int func_003A1070();
int func_003A1150();
int func_003A1180();
int func_003A11B0();
int func_003A1260();
int func_003A1290();
int func_003A12F0();
int func_003A1350();
int func_003A13B0();
int func_003A1410();
int func_003A15A0();
int func_003A16A0();
int func_003A1830();
int func_003A1B60();
int func_003A1CF0();
int func_003A1DF0();
int func_003A1E80();
int func_003A1F80();
int func_003A1FC0();
int func_003A2000();
int func_003A2050();
int func_003A2090();
int func_003A20D0();
int func_003A2110();
int func_003A2150();
int func_003A2190();
int func_003A21D0();
int func_003A2230();
int func_003A2290();
int func_003A22E0();
int func_003A2320();
int func_003A2360();
int func_003A23A0();
int func_003A23E0();
int func_003A2450();
int func_003A24C0();
int func_003A2500();
int func_003A2540();
int func_003A2580();
int func_003A25C0();
int func_003A2600();
int func_003A2640();
int func_003A26E0();
int func_003A2750();
int func_003A27B0();
int func_003A2810();
int func_003A28B0();
int func_003A3420();
int func_003A34C0();
int func_003A3690();
int func_003A3710();
int func_003A3760();
int func_003A3C10();
int func_003A3E30();
int func_003A3EB0();
int func_003A3F20();
int func_003A47E0();
int func_003A4800();
int func_003A4830();
int func_003A4860();
int func_003A4890();
int func_003A48E0();
int func_003A4970();
int func_003A4980();
int func_003A4B00();
int func_003A4B40();
int func_003A4E50();
int func_003A5BA0();
int func_003A5C10();
int func_003A60F0();
int func_003A64A0();
int func_003A7A10();
int func_003A7AC0();
int func_003A7B60();
int func_003A7C10();
int func_003A8000();
int func_003A80A0();
int func_003A80F0();
int func_003A8240();
int func_003A86F0();
int func_003A89F0();
int func_003A8AD0();
int func_003A8B90();
int func_003A9010();
int func_003A9060();
int func_003A9170();
int func_003A9480();
int func_003A9610();
int func_003A97C0();
int func_003A9AF0();
int func_003A9B00();
int func_003A9BA0();
int func_003A9C20();
int func_003AB200();
int func_003AC7E0();
int func_003AE8E0();
int func_003AEAE0();
int func_003AEB80();
int func_003AF5B0();
int func_003AF670();
int func_003AF8D0();
int func_003AF920();
int func_003AF960();
int func_003B5930();
int func_003B5E10();
int func_003BAF40();
int func_003BE6B0();
int func_003C1120();
int func_003C1850();
int func_003C1ED0();
int func_003C2320();
int func_003C23A0();
int func_003C2570();
int func_003C27A0();
int func_003C2AE0();
int func_003C2C60();
int func_003C2DD0();
int func_003C3060();
int func_003D4500();
int func_003D9450();
int func_003DA750();
int func_003DB900();
int func_003DC2D0();
int func_003E0C90();
int func_003E12A0();
int func_003E46F0();
int func_003E4780();
int func_003E76C0();
int func_003E7770();
int func_003E8430();
int func_003E8470();
int func_003E84B0();
int func_003E8520();
int func_003E9630();
int func_003E9700();
int func_003E9750();
int func_003E97D0();
int func_003EA160();
int func_003F0A00();
int func_003F1020();
int func_003F4CB0();
void func_003821E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
int func_00382620(void);
int func_00383270();
int func_003832E0();
void func_003835D0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
int func_00383610();
int func_00383AB0();
int func_00383E00();
void func_00384870(int param_1, int param_2);
void func_003849F0(void);
void func_00387AC0(void);
void func_00387B70(void);
void func_00388200(int param_1, int param_2);
int func_003886D0();
void func_003889B0(int *param_1, int param_2, int param_3);
int func_003893C0(int param_1);
int func_00389490(int param_1);
int func_00389A50(int param_1, int param_2);
int func_00389CD0(int param_1);
int func_00389D20(int param_1);
int func_00389D90(int param_1);
int func_00389DE0(int param_1, int param_2);
int func_00389F90(int param_1, int param_2, int *param_3);
void func_0038B560(int param_1, u32 *param_2);
void func_0038BE90(int param_1);
void func_0038BEC0(int param_1);
void func_0038C6F0(void);
void func_0038C750(u32 *param_1);
void func_0038C7D0(int param_1);
int func_0038D040(int param_1, int param_2, int param_3);
int func_0038D070(int param_1, int param_2, int param_3);
int func_0038D0C0(int param_1, int param_2, int param_3);
void func_0038D0F0(void);
void func_0038D260(int param_1);
void func_0038D2E0(void);
void func_0038D340(void);
void func_0038DF90(void);
void func_0038E790(void);
void func_0038E7C0(int param_1);
void func_0038E820(void);
int func_0038E940(int param_1, int param_2);
void func_0038ECF0(void);
void func_0038F560(void);
void func_0038F6F0(void);
void func_0038FA80(int param_1, int param_2);
int func_0038FAC0(int param_1);
void func_0038FB30(void);
void func_003907B0(void);
void func_00391390(int param_1);
int func_00394740(void);
int func_00394960(void);
void func_00398AA0(int param_1, int param_2, int param_3, int param_4);
int func_00398D60();
void func_0039A880(int param_1);
int func_0039AAB0(int param_1);
int func_0039AFA0(void);
int func_0039B780(void);
void func_0039B920(void);
int func_0039BB80(void);
void func_0039BC20(u32 *param_1);
void func_0039C410(void);
void func_0039C8C0(void);
void func_0039CE50(void);
void func_0039D080(void);
void func_0039D130(void);
void func_0039D260(void);
void func_0039D7E0(void);
void func_0039D890(void);
void func_0039D8D0(void);
int func_0039D950();
int func_0039D990();
void func_0039E490(void);
void func_0039E8C0(int param_1);
void func_0039EF80(int param_1);
void func_0039F0F0(void);
int func_0039F7E0(void);
void func_0039F840(void);
void func_0039F880(void);
void func_0039F960(void);
void func_0039F9F0(int param_1);
void func_0039FA40(u32 *param_1, u32 *param_2);
void func_003A2940(int param_1, int param_2);
void func_003A2BA0(void);
void func_003A2F10(void);
void func_003A3020(void);
void func_003A32C0(void);
void func_003A3860(int param_1, int param_2);
void func_003A3980(int param_1);
void func_003A3CE0(int param_1);
void func_003A3DB0(void);
void func_003A4990(int param_1);
void func_003A4BC0(void);
void func_003A4C50(int param_1);
void func_003A4F40(void);
void func_003A5010(void);
void func_003A54A0(int param_1);
void func_003A5650(int param_1);
void func_003A5C40(int param_1);
void func_003A5E20(void);
void func_003A6110(int param_1, int param_2);
int func_003A63D0();
void func_003A6FE0(void);
void func_003A77C0(int param_1, int param_2);
void func_003A78E0(int param_1, int param_2, int param_3);
void func_003A7C70(void);
void func_003A7ED0(void);
int func_003A83A0(int param_1, int param_2);
void func_003A8B00(void);
void func_003A8D10(void);
int func_003A8DC0(void);
void func_003A91F0(void);
void func_003A9510(int *param_1, int param_2, int param_3);
void func_003AA920(void);
int func_003AB4F0(int param_1);
void func_003AB800(void);
int func_003ABAB0(int param_1);
int func_003AC380(int param_1, int param_2);
int func_003AC430(int param_1);
int func_003AC510(int param_1, int param_2);
int func_003AC650(int param_1, int param_2);
int func_003AC970(int param_1, int param_2);
int func_003ACA10(int param_1, int param_2);
void func_003ACC90(void);
void func_003AE2D0(void);
void func_003AE420(void);
int func_003AE790(void);
int func_003AE840(int param_1);
void func_003AE9F0(int param_1, u32 *param_2, int param_3);
int func_003AF2A0(int param_1);
void func_003AF3A0(int param_1, int param_2);
void func_003AF500(void);
int func_003AF9F0(void);
int func_003BB060(int param_1);
void func_003BFC30(u32 *param_1, int param_2, int param_3);
void func_003BFCF0(u32 *param_1);
int func_003C5760(void);
int func_003C7550(void);
int func_003CE430(void);
int func_003CE5F0(void);
int func_003CE670(void);
int func_003CE6F0(void);
int func_003CE770(void);
int func_003CE7F0(void);
int func_003CE870(void);
int func_003CE8F0(void);
int func_003CE970(void);
int func_003CE9F0(void);
int func_003CEAB0(void);
int func_003CEBF0(void);
int func_003CECA0(void);
int func_003CF030(void);
int func_003CF140(void);
int func_003CF6D0(void);
int func_003CF7F0(void);
int func_003CF940(void);
int func_003CFDA0(void);
int func_003CFF70(void);
void func_003D4600(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6);
void func_003D94D0(int param_1);
void func_003D9ED0(int param_1, int param_2);
void func_003E4BE0(void);
int func_003E7E60(void);
int func_003E7EC0(int param_1, int param_2, int param_3);
int func_003E7FA0(int param_1);
void func_003ED680(void);
int func_003F1070(int param_1);
int func_003F1160(int param_1);
int func_003F1400(int param_1);
void func_003F1580(void);
int func_003F15C0(u32 *param_1);
void func_003F1810(void);
int func_003F1A30(u32 *param_1);
int func_003F1F10(u32 *param_1);
int func_003F2780(u32 *param_1);
int func_003F2950(u32 *param_1);

/* 0x003821E0, 0x12C bytes. */
void func_003821E0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;
    int iVar2;
    int iVar3;

  
  func_002C7310(param_3,param_4,0,0xe4,param_6 * 0x18 + 0x20,0x80,1);
  iVar3 = (int)param_3;
  iVar1 = (int)param_4;
  func_003B5E10(0,iVar3 + 0x3a,iVar1 + 7,0,0x80,1);
  func_003B5E10(1,iVar3 + 0x84,iVar1 + 7,0,0x80,1);
  func_003B5E10(2,iVar3 + 0xa8,iVar1 + 7,0,0x80,1);
  iVar3 = 0;
  if (0 < param_6) {
    iVar2 = 0;
    do {
      func_003820C0(param_1,param_3,iVar2 + 0x18 + iVar1,*(u8 *)(param_5 + iVar3),
                   param_2 == iVar3);
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 0x18;
    } while (iVar3 < param_6);
  }
  return;
}

/* 0x00382620, 0x68 bytes. */
int func_00382620(void)
{
    int iVar1;

  
  iVar1 = func_0037DA70();
  if (0x21 < iVar1) {
    if ((iVar1 < 0x33) || (0x38 < iVar1)) {
      if (iVar1 == 0x30) {
        iVar1 = 0x28;
      }
      else {
        iVar1 = 0;
      }
    }
    else {
      iVar1 = iVar1 + -0x11;
    }
  }
  return iVar1;
}

/* 0x003835D0, 0x3C bytes. */
void func_003835D0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
  func_001ABE40(param_1,param_6,param_2,param_3,0,0xd8,0x90,param_5);
  return;
}

/* 0x00384870, 0x178 bytes. */
void func_00384870(int param_1, int param_2)
{
    int lVar3;
    u32 * puVar4;
    int uVar1;
    int uVar2;

  
  puVar4 = (u32 *)param_1;
  if ((*puVar4 & 0x40) != 0) {
    uVar1 = func_001050F0();
    *(unsigned long long *)((int)uVar1 + 0x10) = 0x48;
    *(unsigned long long *)((int)uVar1 + 0x18) = 0x43;
    func_00105230(uVar1,1);
  }
  if (g_0045D1C8 == 1) {
    uVar1 = func_00104AC0(puVar4[0xc],0x1320,param_2);
  }
  else {
    uVar1 = func_00104AC0(puVar4[0xc],0x1d00,param_2);
  }
  uVar2 = func_00104D00(puVar4[0xc],0x3ffc,param_2);
  uVar1 = func_00106C50(uVar1,uVar2);
  uVar2 = func_00105B40(uVar1,1);
  lVar3 = func_00384060(uVar2,param_1,0);
  if (lVar3 != 0) {
    func_00105BE0(uVar2,1);
  }
  if ((*puVar4 & 4) != 0) {
    uVar1 = func_00105B40(uVar1,1);
    lVar3 = func_00384060(uVar1,param_1,1);
    if (lVar3 != 0) {
      func_00105BE0(uVar1,1);
    }
  }
  if ((*puVar4 & 0x40) != 0) {
    uVar1 = func_001050F0();
    *(unsigned long long *)((int)uVar1 + 0x10) = 0x8000000044;
    *(unsigned long long *)((int)uVar1 + 0x18) = 0x43;
    func_00105230(uVar1,1);
  }
  return;
}

/* 0x003849F0, 0x3C bytes, matching. */
void func_003849F0(void)
{
    int iVar1;
    int uVar2;

  
  iVar1 = func_00365450();
  uVar2 = func_00365470();
  func_00383C40(iVar1 + 0x13c,0,uVar2,0x1c);
  return;
}

/* 0x00387AC0, 0xB0 bytes, matching. */
void func_00387AC0(void)
{
    u16 * puVar1;

  
  puVar1 = (u16 *)func_00365460();
  func_002C5AC0(1.0f, g_00799A20,0,0x40,0,1);
  *(u8 *)(puVar1 + 10) = 0;
  *puVar1 = 0x100;
  puVar1[1] = 0xd0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0x100;
  puVar1[5] = 0xd0;
  puVar1[6] = 0;
  puVar1[7] = 0;
  *(u8 *)(puVar1 + 9) = 0;
  *(u8 *)((int)puVar1 + 0x13) = 0;
  *(u8 *)(puVar1 + 8) = 0;
  *(u8 *)((int)puVar1 + 0x11) = 0;
  puVar1[4] = 0;
  puVar1[5] = 0x60;
  puVar1[6] = 0x200;
  puVar1[7] = 0xe0;
  *(u8 *)((int)puVar1 + 0x11) = 0x80;
  *(u8 *)(puVar1 + 9) = 10;
  return;
}

/* 0x00387B70, 0x48 bytes, matching. */
void func_00387B70(void)
{
    int iVar1;

  
  iVar1 = func_00365460();
  *(u8 *)(iVar1 + 0x14) = 2;
  *(u16 *)(iVar1 + 8) = 0x100;
  *(u16 *)(iVar1 + 10) = 0xd0;
  *(u16 *)(iVar1 + 0xc) = 0;
  *(u16 *)(iVar1 + 0xe) = 0;
  *(u8 *)(iVar1 + 0x11) = 0;
  *(u8 *)(iVar1 + 0x12) = 10;
  return;
}

/* 0x00388200, 0xBC bytes. */
void func_00388200(int param_1, int param_2)
{
    int bVar1;
    int iVar2;
    int iVar3;

  
  bVar1 = (*(char *)(g_007B9E58 + 0x0)) != (char)param_1;
  (*(u8 *)(g_007B9E58 + 0x2)) = 0;
  iVar3 = 0;
  (*(u8 *)(g_007B9E58 + 0x3)) = 0;
  iVar2 = (int)g_007B9E58;
  (*(u8 *)(g_007B9E58 + 0x4)) = 0;
  (*(char *)(g_007B9E58 + 0x0)) = (char)param_1;
  (*(u8 *)(g_007B9E58 + 0x1)) = param_2;
  do {
    *(u8 *)(iVar2 + 5) = 1;
    iVar3 = iVar3 + 3;
    *(u8 *)(iVar2 + 6) = 1;
    *(u8 *)(iVar2 + 7) = 1;
    iVar2 = iVar2 + 3;
  } while (iVar3 < 9);
  if (((param_1 == 4) || (param_1 == 2)) || (param_1 == 1)) {
    if (bVar1) {
      func_00388140();
    }
  }
  else {
    func_00388140();
  }
  return;
}

/* 0x003889B0, 0x200 bytes. */
void func_003889B0(int *param_1, int param_2, int param_3)
{
    int iVar3;
    int iVar4;
    int iVar6;
    int iVar7;
    int uVar1;
    int uVar2;
    u32 uVar5;
    u32 uVar8;

  
  iVar7 = 0;
  uVar8 = 0;
  iVar4 = (u32)(*(u8 *)(g_007B9E58 + 0x0)) * 0x18;
  iVar3 = *(int *)((g_00459720 + 0x4) + iVar4);
  uVar1 = *(u16 *)((g_00459720 + 0x8) + iVar4);
  uVar2 = *(u16 *)((g_00459720 + 0xA) + iVar4);
  if (0 < iVar3) {
    iVar4 = 0x58;
    do {
      if ((int)uVar8 < param_2) {
        iVar7 = iVar7 - *param_1;
      }
      uVar5 = *(u32 *)((g_00459720 + 0x0) + (u32)(*(u8 *)(g_007B9E58 + 0x0)) * 0x18);
      iVar6 = iVar4;
      if (((*(u8 *)(g_007B9E58 + 0x0)) == 0) && (4 < (int)uVar8)) {
        iVar6 = iVar4 + 8;
      }
      if ((((*(u8 *)(g_007B9E58 + 0x0)) == 0) || ((*(u8 *)(g_007B9E58 + 0x0)) == 3)) && (uVar8 == iVar3 - 1U)) {
        iVar6 = 0x130;
      }
      if (((*(u8 *)(g_007B9E58 + 0x0)) == 3) && (3 < (int)uVar8)) {
        uVar5 = 0;
      }
      if (((*(u8 *)(g_007B9E58 + 0x0)) == 0) && (uVar8 == 3)) {
        uVar5 = 2;
      }
      if ((param_3 != 0) && ((*(u8 *)(g_007B9E58 + 0x1)) == uVar8)) {
        func_002C6040(iVar7 + -0x3c,iVar6 + -4,0x100,0x20,1,0x80);
      }
      func_00388340(iVar7 + 0x10,iVar6,0,uVar1,uVar2,uVar8,uVar5,
                   param_3 != 0 && (*(u8 *)(g_007B9E58 + 0x1)) == uVar8);
      uVar8 = uVar8 + 1;
      param_1 = param_1 + 1;
      iVar4 = iVar4 + 0x1a;
    } while ((int)uVar8 < iVar3);
  }
  return;
}

/* 0x003893C0, 0xCC bytes. */
int func_003893C0(int param_1)
{
    int iVar3;
    int lVar2;
    int uVar1;
    int uVar4;

  
  iVar3 = param_1 + *(int *)(param_1 + 0x68c) * 0x184;
  if (*(int *)(param_1 + 0x690) == 1) {
    lVar2 = func_0030E1F0(*(u32 *)(iVar3 + 0x80));
    if (lVar2 == 2) {
      func_0030E100();
    }
  }
  else if (*(int *)(param_1 + 0x690) == 0) {
    if (*(int *)(iVar3 + 0x84) == 0) {
      uVar4 = 0x31;
    }
    else if (*(int *)(iVar3 + 0x88) == 0) {
      uVar4 = 0x20;
    }
    else {
      uVar4 = 0x21;
    }
    uVar1 = func_002F8F20();
    func_0030E140(uVar4,uVar1,0xffffffffffffffff,0xffffffffffffffff);
  }
  return 0;
}

/* 0x00389490, 0x11C bytes. */
int func_00389490(int param_1)
{
    int iVar1;
    int iVar3;
    int lVar2;
    u32 * puVar4;

  
  iVar3 = param_1 + *(int *)(param_1 + 0x68c) * 0x184;
  puVar4 = (u32 *)(iVar3 + 0x80);
  if (*(int *)(param_1 + 0x690) == 1) {
    lVar2 = func_0030E1F0();
    if (lVar2 == 2) {
      func_0030E100();
    }
  }
  else if (*(int *)(param_1 + 0x690) == 0) {
    iVar1 = *(int *)(param_1 + 8);
    if (iVar1 == 0x39) {
      func_0030E140(0x2b,*puVar4,0xffffffffffffffff,0xffffffffffffffff);
    }
    else if (iVar1 == 0x35) {
      if (*(int *)(iVar3 + 0x8c) == 0) {
        func_0030E140(0x2c,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff);
      }
      else {
        func_0030E140(0x3d,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff);
      }
    }
    else if (iVar1 == 0x34) {
      func_0030E140(0x1e,*puVar4,0xffffffffffffffff,0xffffffffffffffff);
    }
  }
  return 0;
}

/* 0x00389A50, 0x70 bytes. */
int func_00389A50(int param_1, int param_2)
{
    int iVar1;

  
  if (param_1 == 0x24) {
    iVar1 = param_2 * 0xc + 0x4597b0;
  }
  else if (param_1 == 0x25) {
    iVar1 = param_2 * 0xc + 0x4597f0;
  }
  else {
    iVar1 = param_2 * 0xc + 0x459830;
  }
  return iVar1;
}

/* 0x00389CD0, 0x48 bytes, matching. */
int func_00389CD0(int param_1)
{
  func_00389B40(*(u32 *)(param_1 + 8),*(u32 *)(param_1 + 0x690),
               param_1 + *(int *)(param_1 + 0x68c) * 0x184 + 0x80);
  return 0;
}

/* 0x00389D20, 0x34 bytes, matching. */
int func_00389D20(int param_1)
{
    u32 uVar1;

  
  if (param_1 == 0x28) {
    uVar1 = 99;
  }
  else if (param_1 == 0x29) {
    uVar1 = 0x6b;
  }
  else {
    uVar1 = 0x5e;
  }
  return uVar1;
}

/* 0x00389D90, 0x4C bytes, matching. */
int func_00389D90(int param_1)
{
    int iVar1;

  
  iVar1 = *(int *)(param_1 + *(int *)(param_1 + 0x68c) * 0x184 + 0xb8);
  if (iVar1 < 4) {
    iVar1 = iVar1 * 2 + 6;
  }
  else {
    iVar1 = (iVar1 + -4) * 2 + 0xf;
  }
  return iVar1;
}

/* 0x00389DE0, 0x54 bytes, matching. */
int func_00389DE0(int param_1, int param_2)
{
    int iVar1;
    int iVar2;

  
  iVar1 = 0;
  iVar2 = param_1 + *(int *)(param_1 + 0x68c) * 0x184 + 0x80;
  do {
    if (param_2 == *(int *)(iVar2 + 0x18)) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 4;
  } while (iVar1 < 8);
  return -1;
}

/* 0x00389F90, 0x78 bytes, matching. */
int func_00389F90(int param_1, int param_2, int *param_3)
{
    int iVar1;

  
  if (param_1 == 0x28) {
    iVar1 = 0x33;
  }
  else if (param_1 == 0x29) {
    iVar1 = 0x36;
  }
  else {
    iVar1 = 0x39;
  }
  if (param_2 < 4) {
    *param_3 = (int)param_2;
  }
  else if (param_2 < 6) {
    iVar1 = iVar1 + 1;
    *param_3 = (int)param_2 + -4;
  }
  else {
    iVar1 = iVar1 + 2;
    *param_3 = -1;
  }
  *param_3 = *param_3 + 1;
  return iVar1;
}

/* 0x0038B560, 0x58 bytes, matching. */
void func_0038B560(int param_1, u32 *param_2)
{
    u32 uVar1;

  
  uVar1 = func_002F39F0();
  *param_2 = uVar1;
  uVar1 = func_002F4C40(param_1);
  param_2[1] = uVar1;
  uVar1 = func_002F4DD0(param_1);
  param_2[2] = uVar1;
  uVar1 = func_002F4F60(param_1);
  param_2[3] = uVar1;
  return;
}

/* 0x0038BE90, 0x28 bytes, matching. */
void func_0038BE90(int param_1)
{
  func_00118AC0(g_007B9EA0,param_1,0x24);
  return;
}

/* 0x0038BEC0, 0x10C bytes. */
void func_0038BEC0(int param_1)
{
    int iVar1;
    int iVar4;
    u32 * puVar2;
    int uVar3;
    int uVar5;

  
  iVar1 = *(int *)(param_1 + 0x68c);
  puVar2 = (u32 *)func_003DB900(0xb);
  iVar4 = *(int *)(param_1 + 8);
  if (iVar4 == 0x27) {
    iVar4 = *(int *)(param_1 + iVar1 * 0x184 + 0x98);
  }
  if (iVar4 == 0x24) {
    uVar5 = 0x152;
  }
  else if (iVar4 == 0x25) {
    uVar5 = 0x153;
  }
  else {
    uVar5 = 0x154;
  }
  if (*(int *)(param_1 + 0x690) == 2) {
    uVar3 = func_0030D7D0();
    func_003835D0(uVar3,*puVar2,puVar2[1],1,puVar2[4],uVar5);
  }
  else if (*(int *)(param_1 + 0x690) == 1) {
    uVar3 = func_0030D7D0();
    func_003835D0(uVar3,*puVar2,puVar2[1],1,puVar2[4],uVar5);
  }
  return;
}

/* 0x0038C6F0, 0x58 bytes. */
void func_0038C6F0(void)
{
    int uVar1;

  
  (*(u32 *)(g_007B9F40 + 0x0)) = 0;
  (*(u32 *)(g_007BA5CC + 0x0)) = 0;
  (*(u32 *)(g_007BA5CC + 0x4)) = 0;
  (*(u32 *)(g_007BA5CC + 0x8)) = 0;
  (*(u32 *)(g_007BA5CC + 0xC)) = 0;
  (*(u32 *)(g_007BA5CC + 0x10)) = 0;
  uVar1 = func_00327D50();
  func_00315510(g_007B9F44,uVar1);
  return;
}

/* 0x0038C750, 0x64 bytes. */
void func_0038C750(u32 *param_1)
{
    int iVar2;
    u32 * puVar3;
    u32 uVar1;

  
  iVar2 = 0xd1;
  puVar3 = (u32 *)0x7b9f44;
  do {
    iVar2 = iVar2 + -1;
    uVar1 = param_1[1];
    *puVar3 = *param_1;
    param_1 = param_1 + 2;
    puVar3[1] = uVar1;
    puVar3 = puVar3 + 2;
  } while (0 < iVar2);
  (*(u32 *)(g_007BA5CC + 0x0)) = 0;
  (*(u32 *)(g_007BA5CC + 0x4)) = 0;
  (*(u32 *)(g_007B9F40 + 0x0)) = 1;
  (*(u32 *)(g_007BA5CC + 0xC)) = 0;
  (*(u32 *)(g_007BA5CC + 0x10)) = 0;
  (*(u32 *)(g_007BA5CC + 0x8)) = 0;
  return;
}

/* 0x0038C7D0, 0x28 bytes. */
void func_0038C7D0(int param_1)
{
  (*(u32 *)(g_007B9F40 + 0x0)) = (u32)param_1;
  if (param_1 == 0) {
    func_003A9610();
  }
  return;
}

/* 0x0038D040, 0x28 bytes. */
int func_0038D040(int param_1, int param_2, int param_3)
{
  return *(u16 *)(param_3 * 2 + param_2 * 0x10 + param_1 * 0x20 + 0x417730);
}

/* 0x0038D070, 0x28 bytes. */
int func_0038D070(int param_1, int param_2, int param_3)
{
  return *(u32 *)(param_3 * 4 + param_2 * 0x20 + param_1 * 0x40 + 0x417af0);
}

/* 0x0038D0C0, 0x28 bytes. */
int func_0038D0C0(int param_1, int param_2, int param_3)
{
  return *(u32 *)(param_3 * 4 + param_2 * 0x20 + param_1 * 0x40 + 0x418360);
}

/* 0x0038D0F0, 0x2C bytes. */
void func_0038D0F0(void)
{
    int iVar2;
    u16 * puVar1;
    int uVar3;
    int uVar4;

  
  uVar4 = 0x1e;
  puVar1 = (u16 *)func_0038D030();
  *puVar1 = uVar4;
  uVar3 = 3;
  iVar2 = func_0038D030();
  *(u8 *)(iVar2 + 2) = uVar3;
  return;
}

/* 0x0038D260, 0x4C bytes. */
void func_0038D260(int param_1)
{
    int iVar1;

  
  iVar1 = func_0038D160();
  *(u32 *)(iVar1 + 4) = 1;
  *(u32 *)(iVar1 + 8) = (u32)(*(int *)(iVar1 + 0x24) == 0);
  if (param_1 != 0) {
    *(u8 *)(iVar1 + 0x20) = 3;
  }
  return;
}

/* 0x0038D2E0, 0x4C bytes, matching. */
void func_0038D2E0(void)
{
    int iVar1;
    int lVar2;

  
  iVar1 = func_0038D160();
  lVar2 = func_003A28B0(0);
  *(u32 *)(iVar1 + 0x24) = (u32)(lVar2 != 0);
  *(u32 *)(iVar1 + 0x28) = 1;
  *(u32 *)(iVar1 + 0x2c) = 1;
  func_0038D2B0();
  func_0038D260(1);
  return;
}

/* 0x0038D340, 0x8E0 bytes. */
void func_0038D340(void)
{
    int iVar2;
    int iVar5;
    int lVar8;
    int * piVar3;
    int sVar1;
    int uVar10;
    u32 uVar11;
    u32 uVar12;
    u32 uVar4;
    int uVar6;
    int uVar7;
    int uVar9;

  
  iVar2 = func_00390940();
  piVar3 = (int *)func_0038D160();
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar9 = 0;
  }
  else {
    uVar9 = (*(u16 *)(g_0050074C + 0x0));
  }
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar10 = 0;
  }
  else {
    uVar10 = (*(u16 *)(g_0050074C + 0x2));
  }
  if (((char)piVar3[8] != '\0') && ((char)piVar3[8] != '\x02')) {
    if ((uVar9 & 0x40) == 0) {
      if ((uVar9 & 0x10) == 0) {
        if ((uVar9 & 0x800) == 0) {
          if ((uVar9 & 0x4000) == 0) {
            if ((uVar10 & 0x4000) == 0) {
              if ((uVar9 & 0x1000) == 0) {
                if ((uVar10 & 0x1000) == 0) {
                  if ((uVar9 & 0x8000) == 0) {
                    if ((uVar10 & 0x8000) == 0) {
                      if ((uVar9 & 0x2000) == 0) {
                        if ((uVar10 & 0x2000) != 0) {
                          if (*piVar3 == 1) {
                            if (piVar3[1] < 2) {
                              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                              piVar3[1] = piVar3[1] + 1;
                            }
                          }
                          else if ((*piVar3 == 0) && (piVar3[2] < 1)) {
                            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                            piVar3[2] = piVar3[2] + 1;
                          }
                        }
                      }
                      else if (*piVar3 == 1) {
                        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                        if (piVar3[1] < 2) {
                          piVar3[1] = piVar3[1] + 1;
                        }
                        else {
                          piVar3[1] = 0;
                        }
                      }
                      else if (*piVar3 == 0) {
                        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                        if (piVar3[2] < 1) {
                          piVar3[2] = piVar3[2] + 1;
                        }
                        else {
                          piVar3[2] = 0;
                        }
                      }
                    }
                    else if (*piVar3 == 1) {
                      if (0 < piVar3[1]) {
                        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                        piVar3[1] = piVar3[1] + -1;
                      }
                    }
                    else if ((*piVar3 == 0) && (0 < piVar3[2])) {
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      piVar3[2] = piVar3[2] + -1;
                    }
                  }
                  else if (*piVar3 == 1) {
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    if (piVar3[1] < 1) {
                      piVar3[1] = 2;
                    }
                    else {
                      piVar3[1] = piVar3[1] + -1;
                    }
                  }
                  else if (*piVar3 == 0) {
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    if (piVar3[2] < 1) {
                      piVar3[2] = 1;
                    }
                    else {
                      piVar3[2] = piVar3[2] + -1;
                    }
                  }
                }
                else {
                  iVar2 = *piVar3;
                  if (0 < iVar2) {
                    *piVar3 = iVar2 + -1;
                    if (piVar3[iVar2 + 8] == 0) {
                      *piVar3 = iVar2;
                    }
                    else {
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    }
                  }
                }
              }
              else {
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                iVar2 = *piVar3;
                if (iVar2 < 1) {
                  *piVar3 = 2;
                }
                else {
                  *piVar3 = iVar2 + -1;
                  if (piVar3[iVar2 + 8] == 0) {
                    *piVar3 = 2;
                  }
                }
              }
            }
            else if (*piVar3 < 2) {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              *piVar3 = *piVar3 + 1;
            }
          }
          else {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            if (*piVar3 < 2) {
              *piVar3 = (*piVar3 + 1) % 3;
            }
            else if (piVar3[9] == 0) {
              *piVar3 = 1;
            }
            else {
              *piVar3 = 0;
            }
          }
        }
        else {
          func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
          func_0038D260(0);
        }
      }
      else {
        func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
        *(u32 *)(iVar2 + 0x8e6c) = 4;
        func_00376100(1,0xffffffffffffffff,0xffffffffffffffff);
      }
    }
    else if (*piVar3 == 2) {
      func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
      func_00376100(10,*(int *)(iVar2 + 0x14) + 0xc,0xffffffffffffffff);
      func_003622F0(1,8);
      func_003635F0();
      uVar12 = 0;
      do {
        uVar11 = 0;
        do {
          uVar6 = func_003623B0();
          sVar1 = func_0038D040(uVar6,uVar12,uVar11);
          uVar6 = func_003623B0();
          uVar6 = func_0038D070(uVar6,uVar12,uVar11);
          uVar4 = func_003635F0();
          func_003620B0(uVar12 != uVar4,uVar11,sVar1);
          if (sVar1 == 0x19f) {
            uVar6 = 0;
          }
          uVar4 = func_003635F0();
          func_00362220(uVar12 != uVar4,uVar11,uVar6);
          uVar4 = func_003635F0();
          uVar6 = func_003623B0();
          uVar6 = func_0038D0C0(uVar6,uVar12,uVar11);
          func_00362840(uVar12 != uVar4,uVar11,uVar6);
          func_003621B0(uVar12,uVar11,10000);
          uVar11 = uVar11 + 1;
        } while (uVar11 < 8);
        uVar12 = uVar12 + 1;
      } while (uVar12 < 2);
      func_0038D120(piVar3[1]);
      func_00362B00(1);
      func_00362B00(2);
      func_00362B00(3);
      iVar2 = piVar3[1];
      uVar6 = 2;
      if (iVar2 == 2) {
        uVar6 = 3;
      }
      else if ((iVar2 != 1) && (iVar2 == 0)) {
        uVar6 = 1;
      }
      func_00362AD0(uVar6);
      uVar12 = 0;
      do {
        uVar6 = func_0038D140();
        uVar7 = func_00363620(uVar12);
        iVar2 = func_0038D180(uVar6,uVar7);
        uVar11 = 0;
        do {
          uVar6 = func_003623B0();
          uVar7 = func_00363620(uVar12);
          iVar5 = func_0038D070(uVar6,uVar7,uVar11);
          iVar5 = (iVar5 * iVar2) / 10;
          if (10000 < iVar5) {
            iVar5 = 10000;
          }
          lVar8 = func_003620E0(uVar12,uVar11);
          if (lVar8 == 0x19f) {
            iVar5 = 0;
          }
          func_00362220(uVar12,uVar11,iVar5);
          uVar11 = uVar11 + 1;
        } while (uVar11 < 8);
        uVar12 = uVar12 + 1;
      } while (uVar12 < 2);
      if (piVar3[2] == 0) {
        func_00362AD0(0);
        iVar2 = 0;
        do {
          uVar6 = func_003A12F0(iVar2);
          func_00328A00(iVar2,uVar6);
          iVar2 = iVar2 + 1;
        } while (iVar2 < 0x1c);
      }
      else {
        func_00362B00(0);
        iVar2 = 0;
        do {
          func_00328A00(iVar2,0);
          iVar2 = iVar2 + 1;
        } while (iVar2 < 0x1c);
      }
      func_0030CD60();
      iVar2 = func_00390940();
      func_0030CF50(*(u32 *)(iVar2 + 0x8ec0));
      uVar6 = func_00362B60(0);
      func_0036D230(uVar6);
      uVar12 = 0;
      do {
        uVar11 = func_00362160(uVar12,0);
        sVar1 = *(short *)((*(u32 *)(g_005BA6A0 + 0x0)) + (uVar11 & 0xffff) * 0x2c);
        if ((sVar1 == 0x18) || (sVar1 == 0x2d2)) {
          sVar1 = 0x17;
        }
        func_00362990(uVar12,sVar1);
        uVar12 = uVar12 + 1;
      } while (uVar12 < 2);
      func_0038E7C0(1);
    }
  }
  return;
}

/* 0x0038DF90, 0x64 bytes, matching. */
void func_0038DF90(void)
{
    u32 * puVar1;

  
  puVar1 = (u32 *)func_0038DC40();
  *puVar1 = 0;
  puVar1[6] = 0;
  puVar1[1] = 1;
  puVar1[7] = 1;
  puVar1[2] = 2;
  puVar1[8] = 2;
  puVar1[3] = 3;
  puVar1[9] = 3;
  puVar1[4] = 4;
  puVar1[10] = 4;
  puVar1[5] = 0;
  puVar1[0x10] = 0;
  puVar1[0x187c] = 0;
  func_0038DE60();
  return;
}

/* 0x0038E790, 0x30 bytes. */
void func_0038E790(void)
{
    int iVar1;

  
  iVar1 = func_00390940();
  *(u32 *)(iVar1 + 0x8e6c) = 8;
  func_003DA750();
  return;
}

/* 0x0038E7C0, 0x58 bytes. */
void func_0038E7C0(int param_1)
{
    int iVar1;

  
  iVar1 = func_00390940();
  if (param_1 == 0) {
    *(u32 *)(iVar1 + 0x8e6c) = 7;
  }
  else {
    *(u32 *)(iVar1 + 0x8e6c) = 6;
  }
  func_003BE6B0();
  return;
}

/* 0x0038E820, 0x60 bytes. */
void func_0038E820(void)
{
    int iVar1;
    int iVar2;

  
  iVar2 = func_00390940();
  iVar1 = *(int *)(iVar2 + 0x8e64);
  *(int *)(iVar2 + 0x8e6c) = iVar1;
  if (iVar1 == 6) {
    func_0038E7C0(1);
  }
  else if (iVar1 == 7) {
    func_0038E7C0(0);
  }
  return;
}

/* 0x0038E940, 0x3A4 bytes. */
int func_0038E940(int param_1, int param_2)
{
    int bVar1;
    int iVar10;
    int iVar11;
    int iVar12;
    int iVar2;
    int iVar3;
    int iVar5;
    int lVar8;
    int lVar9;
    int * piVar13;
    u32 uVar4;
    int uVar6;
    int uVar7;

  
  iVar2 = func_0038E730();
  iVar3 = func_0038E750();
  *(u32 *)(iVar3 + 0x5b6c) = 0;
  *(u32 *)(iVar3 + 0x61ec) = 0;
  if (param_2 == 0) {
    iVar12 = *(int *)(iVar3 + 0x4e68);
    iVar11 = 400;
    piVar13 = (int *)(iVar2 + param_1 * 4 + 0x30);
    do {
      lVar8 = func_0039E650(iVar11 + -400);
      if (lVar8 != 0) {
        iVar2 = 0;
        while( true ) {
          if (param_1 == 1) {
            bVar1 = iVar2 < 2;
          }
          else {
            bVar1 = iVar2 < 1;
          }
          if (!bVar1) break;
          iVar10 = 0;
          do {
            iVar5 = func_003620E0(iVar2,iVar10);
            if ((iVar11 == iVar5) && ((param_1 != iVar2 || (*piVar13 != iVar10)))) {
              iVar5 = *(int *)(iVar3 + 0x5b6c);
              iVar12 = iVar12 + -1;
              *(int *)(iVar3 + 0x5b6c) = iVar5 + 1;
              *(int *)(iVar3 + iVar5 * 4 + 0x54f0) = iVar11;
            }
            iVar10 = iVar10 + 1;
          } while (iVar10 < 8);
          iVar2 = iVar2 + 1;
        }
      }
      iVar11 = iVar11 + 1;
    } while (iVar11 < 0x19f);
    iVar2 = 0;
    while( true ) {
      if (param_1 == 1) {
        bVar1 = iVar2 < 2;
      }
      else {
        bVar1 = iVar2 < 1;
      }
      if (!bVar1) break;
      iVar11 = 0;
      do {
        uVar6 = func_003623B0();
        uVar7 = func_00363620(iVar2);
        uVar4 = func_0038D040(uVar6,uVar7,iVar11);
        uVar4 = uVar4 & 0xffff;
        if ((uVar4 != 0x19f) && (lVar8 = func_003A0040(uVar4), lVar8 == 0)) {
          iVar10 = *(int *)(iVar3 + 0x61ec);
          iVar12 = iVar12 + 1;
          *(int *)(iVar3 + 0x61ec) = iVar10 + 1;
          *(u32 *)(iVar3 + iVar10 * 4 + 0x5b70) = uVar4;
        }
        lVar8 = func_003620E0(iVar2,iVar11);
        if ((lVar8 != 0x19f) &&
           (((lVar8 < 400 || (0x19e < lVar8)) &&
            (lVar9 = func_003620E0(param_1,*piVar13), lVar8 != lVar9)))) {
          iVar10 = *(int *)(iVar3 + 0x5b6c);
          iVar12 = iVar12 + -1;
          *(int *)(iVar3 + 0x5b6c) = iVar10 + 1;
          *(int *)(iVar3 + iVar10 * 4 + 0x54f0) = (int)lVar8;
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < 8);
      iVar2 = iVar2 + 1;
    }
  }
  else {
    iVar12 = *(int *)(iVar3 + 0x54ec);
    iVar11 = 0;
    while( true ) {
      if (param_1 == 1) {
        bVar1 = iVar11 < 2;
      }
      else {
        bVar1 = iVar11 < 1;
      }
      if (!bVar1) break;
      iVar10 = 0;
      do {
        uVar6 = func_003623B0();
        uVar7 = func_00363620(iVar11);
        uVar4 = func_0038D040(uVar6,uVar7,iVar10);
        uVar4 = uVar4 & 0xffff;
        if (((uVar4 != 0x19f) && (0x1b < uVar4)) && (lVar8 = func_003A0040(uVar4), lVar8 == 0)) {
          iVar5 = *(int *)(iVar3 + 0x61ec);
          iVar12 = iVar12 + 1;
          *(int *)(iVar3 + 0x61ec) = iVar5 + 1;
          *(u32 *)(iVar3 + iVar5 * 4 + 0x5b70) = uVar4;
        }
        lVar8 = func_003620E0(iVar11,iVar10);
        if (((lVar8 != 0x19f) && ((lVar8 < 400 || (0x19e < lVar8)))) &&
           (lVar9 = func_003620E0(param_1,*(u32 *)(iVar2 + param_1 * 4 + 0x30)),
           lVar8 != lVar9)) {
          if (0x1b < lVar8) {
            iVar12 = iVar12 + -1;
          }
          iVar5 = *(int *)(iVar3 + 0x5b6c);
          *(int *)(iVar3 + 0x5b6c) = iVar5 + 1;
          *(int *)(iVar3 + iVar5 * 4 + 0x54f0) = (int)lVar8;
        }
        iVar10 = iVar10 + 1;
      } while (iVar10 < 8);
      iVar11 = iVar11 + 1;
    }
  }
  return 0 < iVar12;
}

/* 0x0038ECF0, 0x80 bytes, matching. */
void func_0038ECF0(void)
{
    int iVar1;

  
  iVar1 = func_0038E730();
  *(u32 *)(iVar1 + 0x30) = 0;
  *(u32 *)(iVar1 + 0x34) = 0;
  *(u16 *)(iVar1 + 0x14) = 0x172;
  *(u16 *)(iVar1 + 0x16) = 0x1c;
  *(u16 *)(iVar1 + 0x18) = 0x80;
  *(u16 *)(iVar1 + 0x1a) = 0x18;
  *(u16 *)(iVar1 + 0x1c) = 0x172;
  *(u16 *)(iVar1 + 0x1e) = 0x1c;
  *(u16 *)(iVar1 + 0x20) = 0x80;
  *(u16 *)(iVar1 + 0x22) = 0x18;
  *(u8 *)(iVar1 + 0x26) = 0;
  *(u8 *)(iVar1 + 0x27) = 0;
  *(u8 *)(iVar1 + 0x24) = 0x80;
  *(u8 *)(iVar1 + 0x25) = 0x80;
  *(u16 *)(iVar1 + 0x1c) = 0x172;
  *(u16 *)(iVar1 + 0x1e) = 0x1c;
  *(u16 *)(iVar1 + 0x20) = 0x80;
  *(u16 *)(iVar1 + 0x22) = 0x18;
  *(u8 *)(iVar1 + 0x25) = 0x80;
  *(u8 *)(iVar1 + 0x26) = 0;
  *(u8 *)(iVar1 + 0x28) = 0;
  return;
}

/* 0x0038F560, 0x54 bytes. */
void func_0038F560(void)
{
  func_003A9AF0(1);
  func_003A5E20();
  if (g_0045D7D8 != 0) {
    func_00102EC0();
    g_0045D7D8 = 0;
  }
  if (g_0045D7D4 != 0) {
    func_00102EC0();
    g_0045D7D4 = 0;
  }
  return;
}

/* 0x0038F6F0, 0x48 bytes. */
void func_0038F6F0(void)
{
    int iVar1;

  
  iVar1 = func_00390940();
  func_0038F5E0();
  func_00383C40(iVar1 + 0x8e84,0,*(u32 *)(iVar1 + 0x8ebc),0x47);
  return;
}

/* 0x0038FA80, 0x38 bytes. */
void func_0038FA80(int param_1, int param_2)
{
  if (param_2 == 0) {
    *(u8 *)(param_1 + 0x7ba5e0) = 0;
  }
  else {
    *(u8 *)(param_1 + 0x7ba5e0) = 1;
  }
  return;
}

/* 0x0038FAC0, 0x50 bytes. */
int func_0038FAC0(int param_1)
{
    int iVar1;

  
  iVar1 = func_0038FB10();
  if (param_1 < 0) {
    param_1 = *(int *)(iVar1 + 0x94) + param_1;
  }
  else if (*(int *)(iVar1 + 0x94) <= param_1) {
    param_1 = param_1 - *(int *)(iVar1 + 0x94);
  }
  return param_1;
}

/* 0x0038FB30, 0x94 bytes. */
void func_0038FB30(void)
{
    int iVar1;
    int iVar3;
    int * piVar2;

  
  piVar2 = (int *)func_0038FB10();
  iVar1 = piVar2[piVar2[*piVar2 + 7] + 0xae3];
  iVar3 = func_001020C0();
  if (iVar3 % 5 == 0) {
    piVar2[0x56] = piVar2[0x56] + -1;
  }
  if (piVar2[0x56] + iVar1 * 0x14 < 0x1e) {
    piVar2[0x56] = 0x7a;
  }
  return;
}

/* 0x003907B0, 0x184 bytes. */
void func_003907B0(void)
{
    int iVar1;
    int iVar2;
    int iVar3;

  
  (*(u32 *)(g_0045D7DC + 0x4)) = func_001026D0(1,0x80,0,1,0,0,0x459a30,0x42);
  func_00102960(1);
  iVar2 = 0;
  iVar1 = 0;
  (*(u32 *)(g_0045D7DC + 0x0)) = (*(u32 *)(g_0045D7DC + 0x4));
  do {
    iVar2 = iVar2 + 8;
    *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 4) = *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 4) + (*(u32 *)(g_0045D7DC + 0x0));
    *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 8) = *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 8) + (*(u32 *)(g_0045D7DC + 0x0));
    *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 0xc) = *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 0xc) + (*(u32 *)(g_0045D7DC + 0x0));
    *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 0x10) = *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 0x10) + (*(u32 *)(g_0045D7DC + 0x0));
    *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 0x14) = *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 0x14) + (*(u32 *)(g_0045D7DC + 0x0));
    *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 0x18) = *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 0x18) + (*(u32 *)(g_0045D7DC + 0x0));
    *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 0x1c) = *(int *)((*(u32 *)(g_0045D7DC + 0x0)) + iVar1 + 0x1c) + (*(u32 *)(g_0045D7DC + 0x0));
    iVar3 = (*(u32 *)(g_0045D7DC + 0x0)) + iVar1;
    iVar1 = iVar1 + 0x20;
    *(int *)(iVar3 + 0x20) = *(int *)(iVar3 + 0x20) + (*(u32 *)(g_0045D7DC + 0x0));
  } while (iVar2 < 0x156);
  iVar2 = iVar2 * 4;
  *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 4) = *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 4) + (*(u32 *)(g_0045D7DC + 0x0));
  *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 8) = *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 8) + (*(u32 *)(g_0045D7DC + 0x0));
  *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 0xc) = *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 0xc) + (*(u32 *)(g_0045D7DC + 0x0));
  *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 0x10) = *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 0x10) + (*(u32 *)(g_0045D7DC + 0x0));
  *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 0x14) = *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 0x14) + (*(u32 *)(g_0045D7DC + 0x0));
  *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 0x18) = *(int *)(iVar2 + (*(u32 *)(g_0045D7DC + 0x0)) + 0x18) + (*(u32 *)(g_0045D7DC + 0x0));
  return;
}
/* MISSING ['0x45d7dc', '0x45d7e0'] */

/* 0x00391390, 0x128 bytes. */
void func_00391390(int param_1)
{
    int iVar3;
    int iVar4;
    u32 * puVar1;
    u32 * puVar2;

  
  puVar1 = (u32 *)func_00391250();
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[9] = 0;
  puVar1[10] = 0;
  puVar1[0xc] = 0;
  puVar1[0xd] = param_1;
  *(u16 *)(puVar1 + 0x51) = 0;
  puVar1[0x25] = 0x40;
  *(u16 *)(puVar1 + 0x26) = 0;
  *(u16 *)(puVar1 + 0x26) = 0;
  *(u16 *)(puVar1 + 0x52) = 0;
  *(u16 *)((int)puVar1 + 0x14a) = 0;
  *(u16 *)(puVar1 + 0x53) = 0;
  *(u16 *)((int)puVar1 + 0x14e) = 0;
  puVar1[0x54] = 5;
  puVar1[0x60] = 0;
  *(u16 *)(puVar1 + 0x71) = 0;
  puVar1[5] = 0x7f;
  puVar1[6] = 0x7f;
  puVar1[7] = 0x7f;
  puVar1[8] = 0x7f;
  puVar2 = puVar1;
  iVar3 = 0;
  do {
    iVar4 = iVar3;
    puVar2[0xe] = 0x40;
    puVar2[0xf] = 0x40;
    puVar2[0x10] = 0x40;
    puVar2[0x11] = 0x40;
    puVar2[0x12] = 0x40;
    puVar2[0x13] = 0x40;
    puVar2[0x14] = 0x40;
    puVar2 = puVar2 + 7;
    iVar3 = iVar4 + 7;
  } while (iVar4 + 7 < 0x10);
  iVar3 = 0;
  puVar1[iVar4 + 0x15] = 0x40;
  puVar1[iVar4 + 0x16] = 0x40;
  do {
    *(u16 *)(puVar1 + 0x27) = 0xffff;
    iVar3 = iVar3 + 7;
    *(u16 *)(puVar1 + 0x3c) = 0xffff;
    *(u16 *)((int)puVar1 + 0x9e) = 0xffff;
    *(u16 *)((int)puVar1 + 0xf2) = 0xffff;
    *(u16 *)(puVar1 + 0x28) = 0xffff;
    *(u16 *)(puVar1 + 0x3d) = 0xffff;
    *(u16 *)((int)puVar1 + 0xa2) = 0xffff;
    *(u16 *)((int)puVar1 + 0xf6) = 0xffff;
    *(u16 *)(puVar1 + 0x29) = 0xffff;
    *(u16 *)(puVar1 + 0x3e) = 0xffff;
    *(u16 *)((int)puVar1 + 0xa6) = 0xffff;
    *(u16 *)((int)puVar1 + 0xfa) = 0xffff;
    *(u16 *)(puVar1 + 0x2a) = 0xffff;
    *(u16 *)(puVar1 + 0x3f) = 0xffff;
    puVar1 = (u32 *)((int)puVar1 + 0xe);
  } while (iVar3 < 0x2a);
  return;
}

/* 0x00394740, 0x21C bytes. */
int func_00394740(void)
{
    int iVar2;
    int lVar3;
    int uVar1;

  
  iVar2 = func_00391250();
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar1 = 0;
  }
  else {
    uVar1 = (*(u16 *)(g_0050074C + 0x0));
  }
  if ((uVar1 & 0x100) == 0) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar1 = 0;
    }
    else {
      uVar1 = (*(u16 *)(g_0050074C + 0x0));
    }
    if ((uVar1 & 0x800) == 0) {
      if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
        uVar1 = 0;
      }
      else {
        uVar1 = (*(u16 *)(g_0050074C + 0x0));
      }
      if ((uVar1 & 0x10) != 0) {
        func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
        lVar3 = func_00391C60(*(u32 *)(iVar2 + 0x94));
        if (lVar3 == 0) {
          lVar3 = func_003E9630();
          if (lVar3 == 0) {
            func_003E9750(0);
          }
          else {
            func_003E97D0(3);
          }
          func_003E9700(0);
          *(u32 *)(iVar2 + 4) = 0;
          func_00391CC0();
        }
        else {
          *(u32 *)(iVar2 + 4) = 1;
          func_00391EB0();
          func_00391CC0();
        }
      }
    }
    else if (*(int *)(iVar2 + 0x30) == 0) {
      *(u32 *)(iVar2 + 0x30) = 1;
      func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
    }
    else {
      *(u32 *)(iVar2 + 0x30) = 0;
      func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
    }
  }
  else {
    func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
    *(u32 *)(iVar2 + 4) = 3;
    *(u32 *)(iVar2 + 0x30) = 0;
    func_00391CC0();
  }
  return 0;
}

/* 0x00394960, 0x9C4 bytes. */
int func_00394960(void)
{
    int iVar2;
    int iVar3;
    int sVar1;
    u32 uVar4;
    int uVar5;
    u32 uVar6;

  
  iVar2 = func_00391250();
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar5 = 0;
  }
  else {
    uVar5 = (*(u16 *)(g_0050074C + 0x0));
  }
  if ((uVar5 & 0x1000) == 0) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar5 = 0;
    }
    else {
      uVar5 = (*(u16 *)(g_0050074C + 0x0));
    }
    if ((uVar5 & 0x4000) == 0) {
      if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
        uVar5 = 0;
      }
      else {
        uVar5 = (*(u16 *)(g_0050074C + 0x0));
      }
      if ((uVar5 & 0x8000) == 0) {
        if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
          uVar5 = 0;
        }
        else {
          uVar5 = (*(u16 *)(g_0050074C + 0x0));
        }
        if ((uVar5 & 0x2000) == 0) {
          if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
            uVar5 = 0;
          }
          else {
            uVar5 = (*(u16 *)(g_0050074C + 0x2));
          }
          if ((uVar5 & 0x1000) == 0) {
            if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
              uVar5 = 0;
            }
            else {
              uVar5 = (*(u16 *)(g_0050074C + 0x2));
            }
            if ((uVar5 & 0x4000) == 0) {
              if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                uVar5 = 0;
              }
              else {
                uVar5 = (*(u16 *)(g_0050074C + 0x2));
              }
              if ((uVar5 & 0x8000) == 0) {
                if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                  uVar5 = 0;
                }
                else {
                  uVar5 = (*(u16 *)(g_0050074C + 0x2));
                }
                if ((uVar5 & 0x2000) == 0) {
                  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                    uVar5 = 0;
                  }
                  else {
                    uVar5 = (*(u16 *)(g_0050074C + 0x0));
                  }
                  if ((uVar5 & 0x100) == 0) {
                    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
                      uVar5 = 0;
                    }
                    else {
                      uVar5 = (*(u16 *)(g_0050074C + 0x0));
                    }
                    if ((uVar5 & 0x10) != 0) {
                      func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
                      *(u32 *)(iVar2 + 4) = 2;
                      func_00391CC0();
                    }
                  }
                  else {
                    func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
                    *(u32 *)(iVar2 + 4) = 2;
                    func_00391CC0();
                  }
                }
                else {
                  iVar3 = *(int *)(iVar2 + 0x10);
                  if (iVar3 == 2) {
                    if (*(int *)(iVar2 + 0x180) < (int)(*(u8 *)(iVar2 + 0x1c6) - 1)) {
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      func_003E8520();
                      *(int *)(iVar2 + 0x180) = *(int *)(iVar2 + 0x180) + 1;
                    }
                  }
                  else if (iVar3 == 1) {
                    if (1 < *(int *)(iVar2 + 0x28)) {
                      iVar3 = *(int *)(iVar2 + 0x24) + 1;
                      *(int *)(iVar2 + 0x24) = iVar3;
                      if (*(int *)(iVar2 + 0x28) <= iVar3) {
                        *(u32 *)(iVar2 + 0x24) = 0;
                      }
                      func_003E84B0(*(u32 *)(iVar2 + 0x24));
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    }
                  }
                  else if (iVar3 == 0) {
                    if (*(int *)(iVar2 + 0x94) < 0x1c) {
                      if (*(short *)(iVar2 + 0x98) < 1) {
                        sVar1 = *(short *)(iVar2 + 0x98) + 1;
                        *(short *)(iVar2 + 0x98) = sVar1;
                        func_003E8430(sVar1);
                        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      }
                    }
                    else {
                      *(short *)(iVar2 + 0x9a) = (short)((*(short *)(iVar2 + 0x9a) + 9) % 10);
                      func_003E8470(*(u8 *)(iVar2 + 0x9a));
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    }
                  }
                }
              }
              else {
                iVar3 = *(int *)(iVar2 + 0x10);
                if (iVar3 == 2) {
                  if (0 < *(int *)(iVar2 + 0x180)) {
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    func_003E8520();
                    *(int *)(iVar2 + 0x180) = *(int *)(iVar2 + 0x180) + -1;
                  }
                }
                else if (iVar3 == 1) {
                  if (1 < *(int *)(iVar2 + 0x28)) {
                    iVar3 = *(int *)(iVar2 + 0x24) + -1;
                    *(int *)(iVar2 + 0x24) = iVar3;
                    if (iVar3 < 0) {
                      *(int *)(iVar2 + 0x24) = *(int *)(iVar2 + 0x28) + -1;
                    }
                    func_003E84B0(*(u32 *)(iVar2 + 0x24));
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  }
                }
                else if (iVar3 == 0) {
                  if (*(int *)(iVar2 + 0x94) < 0x1c) {
                    if (0 < *(short *)(iVar2 + 0x98)) {
                      sVar1 = *(short *)(iVar2 + 0x98) + -1;
                      *(short *)(iVar2 + 0x98) = sVar1;
                      func_003E8430(sVar1);
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                    }
                  }
                  else {
                    *(short *)(iVar2 + 0x9a) = (short)((*(short *)(iVar2 + 0x9a) + 1) % 10);
                    func_003E8470(*(u8 *)(iVar2 + 0x9a));
                    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  }
                }
              }
            }
            else if (*(int *)(iVar2 + 0x10) < 2) {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              *(int *)(iVar2 + 0x10) = *(int *)(iVar2 + 0x10) + 1;
            }
          }
          else if (0 < *(int *)(iVar2 + 0x10)) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            *(int *)(iVar2 + 0x10) = *(int *)(iVar2 + 0x10) + -1;
          }
        }
        else {
          iVar3 = *(int *)(iVar2 + 0x10);
          if (iVar3 == 2) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            iVar3 = *(int *)(iVar2 + 0x180) + 1;
            *(int *)(iVar2 + 0x180) = iVar3;
            if ((int)(u32)*(u8 *)(iVar2 + 0x1c6) <= iVar3) {
              *(u32 *)(iVar2 + 0x180) = 0;
            }
            func_003E8520();
          }
          else if (iVar3 == 1) {
            if (1 < *(int *)(iVar2 + 0x28)) {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              iVar3 = *(int *)(iVar2 + 0x24) + 1;
              *(int *)(iVar2 + 0x24) = iVar3;
              if (*(int *)(iVar2 + 0x28) <= iVar3) {
                *(u32 *)(iVar2 + 0x24) = 0;
              }
              func_003E84B0(*(u32 *)(iVar2 + 0x24));
            }
          }
          else if (iVar3 == 0) {
            if (*(int *)(iVar2 + 0x94) < 0x1c) {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              uVar6 = (int)*(short *)(iVar2 + 0x98) + 1;
              uVar4 = uVar6 & 1;
              sVar1 = (short)uVar4;
              if (((int)uVar6 < 0) && (uVar4 != 0)) {
                sVar1 = sVar1 + -2;
              }
              *(short *)(iVar2 + 0x98) = sVar1;
              func_003E8430(sVar1);
            }
            else {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              *(short *)(iVar2 + 0x9a) = (short)((*(short *)(iVar2 + 0x9a) + 9) % 10);
              func_003E8470(*(u8 *)(iVar2 + 0x9a));
            }
          }
        }
      }
      else {
        iVar3 = *(int *)(iVar2 + 0x10);
        if (iVar3 == 2) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          iVar3 = *(int *)(iVar2 + 0x180) + -1;
          *(int *)(iVar2 + 0x180) = iVar3;
          if (iVar3 < 0) {
            *(u32 *)(iVar2 + 0x180) = *(u8 *)(iVar2 + 0x1c6) - 1;
          }
          func_003E8520();
        }
        else if (iVar3 == 1) {
          if (1 < *(int *)(iVar2 + 0x28)) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            iVar3 = *(int *)(iVar2 + 0x24) + -1;
            *(int *)(iVar2 + 0x24) = iVar3;
            if (iVar3 < 0) {
              *(int *)(iVar2 + 0x24) = *(int *)(iVar2 + 0x28) + -1;
            }
            func_003E84B0(*(u32 *)(iVar2 + 0x24));
          }
        }
        else if (iVar3 == 0) {
          if (*(int *)(iVar2 + 0x94) < 0x1c) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            uVar6 = (int)*(short *)(iVar2 + 0x98) + 1;
            uVar4 = uVar6 & 1;
            sVar1 = (short)uVar4;
            if (((int)uVar6 < 0) && (uVar4 != 0)) {
              sVar1 = sVar1 + -2;
            }
            *(short *)(iVar2 + 0x98) = sVar1;
            func_003E8430(sVar1);
          }
          else {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            *(short *)(iVar2 + 0x9a) = (short)((*(short *)(iVar2 + 0x9a) + 1) % 10);
            func_003E8470(*(u8 *)(iVar2 + 0x9a));
          }
        }
      }
    }
    else {
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      iVar3 = *(int *)(iVar2 + 0x10) + 1;
      *(int *)(iVar2 + 0x10) = iVar3;
      if (2 < iVar3) {
        *(u32 *)(iVar2 + 0x10) = 0;
      }
    }
  }
  else {
    func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
    iVar3 = *(int *)(iVar2 + 0x10) + -1;
    *(int *)(iVar2 + 0x10) = iVar3;
    if (iVar3 < 0) {
      *(u32 *)(iVar2 + 0x10) = 2;
    }
  }
  return 0;
}

/* 0x00398AA0, 0x124 bytes. */
void func_00398AA0(int param_1, int param_2, int param_3, int param_4)
{
    int bVar1;
    int lVar2;
    int uVar3;
    int uVar4;
    int uVar5;
    int uVar6;

  
  uVar6 = 0x5b;
  uVar5 = 0x80;
  if (*(int *)(param_3 * 4 + 0x7ba8d4) == 0) {
    uVar5 = 0x40;
  }
  bVar1 = false;
  if ((-1 < param_4) && (param_4 < 0x19f)) {
    bVar1 = true;
  }
  if ((bVar1) && (lVar2 = func_002F3F20(param_4), lVar2 != 0)) {
    uVar6 = 0x5a;
  }
  if (((*(u32 *)(g_007BA8C4 + 0x0)) != -1) && ((*(u32 *)(g_007BA8C4 + 0x0)) == param_3)) {
    uVar6 = 0x5c;
  }
  uVar3 = func_0030D7D0();
  uVar4 = func_00397B00(param_2 + ((g_00459B60 + 0x4))[param_3 * 2]);
  func_001ABE40(uVar3,uVar6,param_1 + ((g_00459B60 + 0x0))[param_3 * 2],uVar4,0,0x98,0x14,uVar5);
  return;
}

/* 0x0039A880, 0x224 bytes. */
void func_0039A880(int param_1)
{
    int bVar2;
    int iVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    int lVar3;
    int lVar4;
    int sVar1;

  
  iVar5 = 0;
  lVar3 = func_0030AB90();
  if (0 < lVar3) {
    iVar7 = (int)g_007BA8B0;
    do {
      iVar8 = 0;
      iVar6 = iVar7;
      do {
        sVar1 = *(short *)(iVar6 + 0x78);
        bVar2 = false;
        if ((-1 < sVar1) && (sVar1 < 0x19f)) {
          bVar2 = true;
        }
        if (bVar2) {
          func_002F5BE0(sVar1,iVar5);
          lVar3 = func_002F3E70(sVar1);
          if (lVar3 == 0) {
            func_002F3CF0(sVar1,2);
          }
          else {
            func_002F3CF0(sVar1,3);
          }
        }
        iVar8 = iVar8 + 1;
        iVar6 = iVar6 + 2;
      } while (iVar8 < 3);
      iVar8 = 0;
      iVar6 = iVar7;
      do {
        sVar1 = *(short *)(iVar6 + 0x10e);
        bVar2 = false;
        if ((-1 < sVar1) && (sVar1 < 0x19f)) {
          bVar2 = true;
        }
        if (bVar2) {
          func_002F5BE0(sVar1,iVar5);
          func_002F3CF0(sVar1,1);
        }
        iVar8 = iVar8 + 1;
        iVar6 = iVar6 + 2;
      } while (iVar8 < 3);
      iVar7 = iVar7 + 6;
      iVar5 = iVar5 + 1;
      iVar6 = func_0030AB90();
    } while (iVar5 < iVar6);
  }
  iVar5 = 0;
  iVar7 = (int)g_007BA8B0;
  do {
    sVar1 = *(short *)(iVar7 + 0x1a4);
    bVar2 = false;
    if ((-1 < sVar1) && (sVar1 < 0x19f)) {
      bVar2 = true;
    }
    if (bVar2) {
      if (param_1 == 0) {
        lVar3 = func_002F3E70(sVar1);
        if (lVar3 == 0) {
          func_002F3CF0(sVar1,4);
        }
        else {
          func_002F3CF0(sVar1,5);
        }
        func_002F5BE0(sVar1,0x19);
      }
      else {
        func_002F7410(sVar1);
      }
    }
    iVar5 = iVar5 + 1;
    iVar7 = iVar7 + 2;
  } while (iVar5 < 6);
  lVar3 = func_00327D60();
  bVar2 = false;
  if (-1 < lVar3) {
    lVar4 = func_0030AB90();
    bVar2 = lVar3 < lVar4;
  }
  if (bVar2) {
    func_003A9060(lVar3);
  }
  return;
}

/* 0x0039AAB0, 0x16C bytes. */
int func_0039AAB0(int param_1)
{
    int iVar1;

  
  iVar1 = (int)param_1;
  if ((param_1 < 1) || (3 < param_1)) {
    if ((param_1 < 4) || (6 < param_1)) {
      if ((param_1 < 8) || (10 < param_1)) {
        if ((param_1 < 0xb) || (0xd < param_1)) {
          if ((param_1 < 0xe) || (0x13 < param_1)) {
            iVar1 = 0;
          }
          else {
            iVar1 = (iVar1 + -0xe) * 2 + 0x7baa54;
          }
        }
        else {
          iVar1 = (iVar1 + -0xb) * 2 + (*(u32 *)(g_007BA8B0 + 0x4)) * 6 + 0x7ba9be;
        }
      }
      else {
        iVar1 = (iVar1 + -8) * 2 + (*(u32 *)(g_007BA8B0 + 0x4)) * 6 + 0x7ba928;
      }
    }
    else {
      iVar1 = (iVar1 + -4) * 2 + (*(u32 *)(g_007BA8B0 + 0x0)) * 6 + 0x7ba9be;
    }
  }
  else {
    iVar1 = (iVar1 + -1) * 2 + (*(u32 *)(g_007BA8B0 + 0x0)) * 6 + 0x7ba928;
  }
  return iVar1;
}

/* 0x0039AFA0, 0x710 bytes. */
int func_0039AFA0(void)
{
    int lVar2;
    int uVar1;
    int uVar3;
    int uVar4;

  
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar1 = 0;
  }
  else {
    uVar1 = (*(u16 *)(g_0050074C + 0x0));
  }
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar4 = 0;
  }
  else {
    uVar4 = (*(u16 *)(g_0050074C + 0x2));
  }
  if ((uVar1 & 0x40) == 0) {
    if ((uVar1 & 0x10) == 0) {
      if ((uVar1 & 0x80) == 0) {
        if ((uVar1 & 0x20) == 0) {
          if ((uVar1 & 0x800) == 0) {
            if ((uVar4 & 0x1000) == 0) {
              if ((uVar4 & 0x4000) == 0) {
                if ((uVar4 & 0x8000) == 0) {
                  if ((uVar4 & 0x2000) != 0) {
                    if ((((*(u32 *)(g_007BA8B8 + 0x0)) < 0xe) || (0x13 < (*(u32 *)(g_007BA8B8 + 0x0)))) && ((*(u32 *)(g_007BA8B8 + 0x0)) != 7)) {
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      (*(u32 *)(g_007BA8B8 + 0x0)) = *(int *)((g_00459C10 + 0xC) + (*(u32 *)(g_007BA8B8 + 0x0)) * 0x10);
                    }
                    else if ((uVar1 & 0x2000) != 0) {
                      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                      (*(u32 *)(g_007BA8B8 + 0x0)) = *(int *)((g_00459C10 + 0xC) + (*(u32 *)(g_007BA8B8 + 0x0)) * 0x10);
                    }
                  }
                }
                else if (((*(u32 *)(g_007BA8B8 + 0x0)) < 0) || (6 < (*(u32 *)(g_007BA8B8 + 0x0)))) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  (*(u32 *)(g_007BA8B8 + 0x0)) = *(int *)((g_00459C10 + 0x8) + (*(u32 *)(g_007BA8B8 + 0x0)) * 0x10);
                }
                else if ((uVar1 & 0x8000) != 0) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  (*(u32 *)(g_007BA8B8 + 0x0)) = *(int *)((g_00459C10 + 0x8) + (*(u32 *)(g_007BA8B8 + 0x0)) * 0x10);
                }
              }
              else if ((*(u32 *)(g_007BA8B8 + 0x0)) - 0x13U < 2) {
                if ((uVar1 & 0x4000) != 0) {
                  func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                  (*(u32 *)(g_007BA8B8 + 0x0)) = *(int *)((g_00459C10 + 0x4) + (*(u32 *)(g_007BA8B8 + 0x0)) * 0x10);
                }
              }
              else {
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                (*(u32 *)(g_007BA8B8 + 0x0)) = *(int *)((g_00459C10 + 0x4) + (*(u32 *)(g_007BA8B8 + 0x0)) * 0x10);
              }
            }
            else if ((((*(u32 *)(g_007BA8B8 + 0x0)) == 0) || ((*(u32 *)(g_007BA8B8 + 0x0)) == 7)) || ((*(u32 *)(g_007BA8B8 + 0x0)) == 0xe)) {
              if ((uVar1 & 0x1000) != 0) {
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                (*(u32 *)(g_007BA8B8 + 0x0)) = *(int *)((g_00459C10 + 0x0) + (*(u32 *)(g_007BA8B8 + 0x0)) * 0x10);
              }
            }
            else {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              (*(u32 *)(g_007BA8B8 + 0x0)) = *(int *)((g_00459C10 + 0x0) + (*(u32 *)(g_007BA8B8 + 0x0)) * 0x10);
            }
          }
          else {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            (*(u32 *)(g_007BA8B8 + 0x0)) = 0x14;
          }
        }
        else {
          lVar2 = func_0039A630();
          if (lVar2 != -1) {
            func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
            func_00397B10(6);
          }
        }
      }
      else if (((*(u32 *)(g_007BA8B8 + 0xC)) == -1) &&
              ((((0 < (*(u32 *)(g_007BA8B8 + 0x0)) && ((*(u32 *)(g_007BA8B8 + 0x0)) < 7)) ||
                ((7 < (*(u32 *)(g_007BA8B8 + 0x0)) && ((*(u32 *)(g_007BA8B8 + 0x0)) < 0xe)))) &&
               (lVar2 = func_0039A630(), lVar2 != -1)))) {
        lVar2 = func_0039AF30();
        if (lVar2 == -1) {
          func_0023AD10(4,0,0x2cdc,0x2cdc,0x1000);
        }
        else {
          func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
          (*(u32 *)(g_007BA8B8 + 0xC)) = (*(u32 *)(g_007BA8B8 + 0x0));
          (*(u32 *)(g_007BA8B8 + 0x8)) = func_0039A630();
          func_0039AD50(lVar2);
          (*(u32 *)(g_007BA8B8 + 0xC)) = -1;
          (*(u32 *)(g_007BA8B8 + 0x8)) = 0xffffffff;
          func_00397F40();
        }
      }
    }
    else if ((*(u32 *)(g_007BA8B8 + 0xC)) == -1) {
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      (*(u32 *)(g_007BA8B8 + 0x0)) = 0x14;
    }
    else {
      func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
      (*(u32 *)(g_007BA8B8 + 0xC)) = -1;
      (*(u32 *)(g_007BA8B8 + 0x8)) = 0xffffffff;
      func_00397F40();
    }
  }
  else {
    lVar2 = func_00398630();
    if (lVar2 == 0) {
      func_0023AD10(4,0,0x2cdc,0x2cdc,0x1000);
    }
    else {
      func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
      if ((*(u32 *)(g_007BA8B8 + 0x0)) == 0x14) {
        lVar2 = func_00397F00();
        if (lVar2 == 0) {
          func_0039AF70();
          func_003A9480(0);
          func_003A9010(1);
        }
        else {
          uVar3 = func_00390760(0x76);
          func_00375140(0x100,200,1,uVar3);
          func_00397B10(9);
        }
      }
      else if ((*(u32 *)(g_007BA8B8 + 0x0)) == 0) {
        func_0039AC20();
        func_00397B10(2);
        func_003A9010(2);
        func_003A9610();
      }
      else if ((*(u32 *)(g_007BA8B8 + 0x0)) == 7) {
        func_0039AC20();
        func_00397B10(2);
        func_003A9010(2);
        func_003A9610();
      }
      else if ((*(u32 *)(g_007BA8B8 + 0xC)) == -1) {
        (*(u32 *)(g_007BA8B8 + 0xC)) = (*(u32 *)(g_007BA8B8 + 0x0));
        (*(u32 *)(g_007BA8B8 + 0x8)) = func_0039A630();
        func_00397F40();
      }
      else {
        func_0039AD50();
        (*(u32 *)(g_007BA8B8 + 0xC)) = -1;
        (*(u32 *)(g_007BA8B8 + 0x8)) = 0xffffffff;
        func_00397F40();
      }
    }
  }
  return 2;
}

/* 0x0039B780, 0x94 bytes. */
int func_0039B780(void)
{
  (*(u32 *)(g_007BA8BC + 0x10)) = (*(u32 *)(g_007BA8BC + 0x10)) + 1;
  if (5 < (*(u32 *)(g_007BA8BC + 0x10))) {
    (*(u32 *)(g_007BA8BC + 0x10)) = 0;
    if ((*(u32 *)(g_007BA8BC + 0x0)) == 4) {
      func_00397B10(3);
      return 2;
    }
    if ((*(u32 *)(g_007BA8BC + 0x0)) == 2) {
      func_00397B10(1);
    }
    else if ((*(u32 *)(g_007BA8BC + 0x0)) == 5) {
      (*(u32 *)(g_007BA8BC + 0x10)) = 0;
      return (*(u32 *)(g_007BA8BC + 0x14));
    }
  }
  return 2;
}

/* 0x0039B920, 0x5C bytes. */
void func_0039B920(void)
{
    int lVar1;

  
  lVar1 = func_00375B90();
  if (lVar1 == 2) {
    func_0039AF70();
    func_003A9480(0);
    func_003A9010(1);
  }
  else if (lVar1 == 3) {
    func_00397B10();
  }
  return;
}

/* 0x0039BB80, 0x84 bytes. */
int func_0039BB80(void)
{
    int iVar1;

  
  iVar1 = func_002FC2C0();
  iVar1 = **(int **)(iVar1 + 0x6a4);
  func_003F1070(3);
  if (iVar1 == 2) {
    func_0039BB00();
  }
  else if (iVar1 == 1) {
    func_0039BAC0();
  }
  else if (iVar1 == 0) {
    func_0039BA70();
  }
  return 5;
}

/* 0x0039BC20, 0x54 bytes. */
void func_0039BC20(u32 *param_1)
{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0xffffffff;
  param_1[4] = 0x19;
  param_1[5] = 0x19f;
  param_1[6] = 0x19;
  *(u16 *)(param_1 + 7) = 0xffff;
  *(u16 *)((int)param_1 + 0x1e) = 0xffff;
  *(u8 *)(param_1 + 8) = 0xff;
  *(u8 *)((int)param_1 + 0x21) = 0xff;
  *(u8 *)((int)param_1 + 0x22) = 0xff;
  *(u8 *)((int)param_1 + 0x23) = 0xff;
  *(u8 *)(param_1 + 9) = 0xff;
  *(u8 *)((int)param_1 + 0x25) = 0xff;
  *(u8 *)((int)param_1 + 0x26) = 0;
  param_1[3] = 0;
  return;
}

/* 0x0039C410, 0x74 bytes. */
void func_0039C410(void)
{
    int iVar1;
    int iVar2;
    int iVar3;

  
  iVar1 = func_002FC2C0();
  iVar1 = *(int *)(iVar1 + 0x6ac);
  iVar3 = iVar1 + 0x28;
  func_003F0A00(iVar3);
  iVar2 = 0;
  if (0 < *(int *)(iVar1 + 0x168)) {
    do {
      if (*(int *)(iVar3 + 0x120) != 0) {
        *(int *)(iVar1 + 0x168) = iVar2;
        break;
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 4;
    } while (iVar2 < *(int *)(iVar1 + 0x168));
  }
  *(u32 *)(iVar1 + 0x16c) = 0;
  return;
}

/* 0x0039C8C0, 0x9C bytes. */
void func_0039C8C0(void)
{
    int iVar1;
    int lVar2;

  
  iVar1 = func_002FC2C0();
  iVar1 = *(int *)(iVar1 + 0x6ac);
  if (*(int *)(iVar1 + 4) == 1) {
    lVar2 = func_0039C690();
    if (lVar2 == 0) {
      *(u32 *)(iVar1 + 4) = 0;
      func_0039BCE0();
    }
  }
  else if (*(int *)(iVar1 + 4) == 0) {
    lVar2 = func_0032D9C0();
    if (lVar2 == 1) {
      func_0032D2F0();
    }
    else if (lVar2 == 0) {
      *(u32 *)(iVar1 + 8) = 0xffffffff;
      func_0039C740();
    }
  }
  return;
}

/* 0x0039CE50, 0x204 bytes. */
void func_0039CE50(void)
{
    int bVar1;
    int iVar3;
    int lVar2;
    int uVar4;
    int uVar5;

  
  iVar3 = func_002FC2C0();
  iVar3 = *(int *)(iVar3 + 0x6ac);
  bVar1 = *(u8 *)(iVar3 + 0x26);
  lVar2 = func_003DC2D0(0x10);
  if ((lVar2 == 0) && (lVar2 = func_003DC2D0(0x11), lVar2 == 0)) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar4 = 0;
    }
    else {
      uVar4 = (*(u16 *)(g_0050074C + 0x0));
    }
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar5 = 0;
    }
    else {
      uVar5 = (*(u16 *)(g_0050074C + 0x2));
    }
    if ((uVar4 & 0x10) == 0) {
      if (1 < bVar1) {
        if ((uVar5 & 0x4000) == 0) {
          if ((uVar5 & 0x1000) != 0) {
            if (*(int *)(iVar3 + 0xc) < 1) {
              if ((uVar4 & 0x1000) != 0) {
                func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
                *(u32 *)(iVar3 + 0xc) = bVar1 - 1 & 0xff;
              }
            }
            else {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              *(int *)(iVar3 + 0xc) = *(int *)(iVar3 + 0xc) + -1;
            }
          }
        }
        else if (*(int *)(iVar3 + 0xc) < (int)(bVar1 - 1)) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          *(int *)(iVar3 + 0xc) = *(int *)(iVar3 + 0xc) + 1;
        }
        else if ((uVar4 & 0x4000) != 0) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          *(u32 *)(iVar3 + 0xc) = 0;
        }
      }
    }
    else {
      func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
      func_0039C740();
    }
  }
  return;
}

/* 0x0039D080, 0xA4 bytes. */
void func_0039D080(void)
{
    int lVar1;
    int uVar2;

  
  func_002FC2C0();
  lVar1 = func_003DC2D0(0xf);
  if (lVar1 == 0) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar2 = 0;
    }
    else {
      uVar2 = (*(u16 *)(g_0050074C + 0x0));
    }
    if ((uVar2 & 0x10) != 0) {
      func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
      func_0039C740();
    }
  }
  return;
}

/* 0x0039D130, 0x128 bytes. */
void func_0039D130(void)
{
    int iVar1;
    int iVar2;
    int lVar3;
    int uVar4;
    int uVar5;

  
  iVar2 = func_002FC2C0();
  iVar2 = *(int *)(iVar2 + 0x6ac);
  iVar1 = *(int *)(iVar2 + 4);
  if (iVar1 == 2) {
    uVar4 = func_00327C00();
    uVar5 = func_00374E00();
    func_003737E0(9,0xffffffff80000000,uVar4,uVar5);
    *(u32 *)(iVar2 + 8) = 0xffffffff;
    *(u32 *)(iVar2 + 4) = 0;
  }
  else if (iVar1 == 1) {
    lVar3 = func_003E12A0();
    if (lVar3 == 0) {
      *(u32 *)(iVar2 + 8) = 0xffffffff;
      *(u32 *)(iVar2 + 4) = 2;
    }
  }
  else if (iVar1 == 0) {
    lVar3 = func_00374250();
    if (lVar3 == 1) {
      func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
      uVar4 = func_00374E00();
      uVar4 = func_0030AFF0(uVar4);
      *(int *)(iVar2 + 8) = (int)uVar4;
      func_003E0C90(1,uVar4);
      *(int *)(iVar2 + 4) = *(int *)(iVar2 + 4) + 1;
    }
    else if (lVar3 == 0) {
      *(u32 *)(iVar2 + 8) = 0xffffffff;
      func_0039C740();
      func_00373F60();
    }
  }
  return;
}

/* 0x0039D260, 0x240 bytes. */
void func_0039D260(void)
{
    int iVar1;
    int lVar2;
    int uVar3;
    int uVar4;

  
  iVar1 = func_002FC2C0();
  iVar1 = *(int *)(iVar1 + 0x6ac);
  lVar2 = func_003DC2D0(0xd);
  if (lVar2 == 0) {
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar3 = 0;
    }
    else {
      uVar3 = (*(u16 *)(g_0050074C + 0x2));
    }
    if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
      uVar4 = 0;
    }
    else {
      uVar4 = (*(u16 *)(g_0050074C + 0x0));
    }
    if ((uVar4 & 0x10) == 0) {
      if ((uVar3 & 0x1000) == 0) {
        if ((uVar3 & 0x4000) != 0) {
          if (*(int *)(iVar1 + 0x16c) == *(int *)(iVar1 + 0x168) + -1) {
            if ((1 < *(int *)(iVar1 + 0x168)) && ((uVar4 & 0x4000) != 0)) {
              func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
              *(int *)(iVar1 + 0x16c) = (*(int *)(iVar1 + 0x16c) + 1) % *(int *)(iVar1 + 0x168);
            }
          }
          else {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            *(int *)(iVar1 + 0x16c) = (*(int *)(iVar1 + 0x16c) + 1) % *(int *)(iVar1 + 0x168);
          }
        }
      }
      else if (*(int *)(iVar1 + 0x16c) == 0) {
        if ((1 < *(int *)(iVar1 + 0x168)) && ((uVar4 & 0x1000) != 0)) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          *(int *)(iVar1 + 0x16c) =
               (*(int *)(iVar1 + 0x16c) + *(int *)(iVar1 + 0x168) + -1) % *(int *)(iVar1 + 0x168);
        }
      }
      else {
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        *(int *)(iVar1 + 0x16c) =
             (*(int *)(iVar1 + 0x16c) + *(int *)(iVar1 + 0x168) + -1) % *(int *)(iVar1 + 0x168);
      }
    }
    else {
      func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
      *(u32 *)(iVar1 + 8) = 0xffffffff;
      func_0039C740();
    }
  }
  return;
}

/* 0x0039D7E0, 0x40 bytes, matching. */
void func_0039D7E0(void)
{
    int iVar1;
    int uVar2;

  
  iVar1 = func_002FC2C0();
  uVar2 = func_0030D7D0();
  func_0037FD50(uVar2,0x40,0x50,*(u32 *)(*(int *)(iVar1 + 0x6ac) + 8));
  return;
}

/* 0x0039D890, 0x40 bytes, matching. */
void func_0039D890(void)
{
    int iVar1;
    int uVar2;

  
  iVar1 = func_002FC2C0();
  uVar2 = func_0030D7D0();
  func_00380E80(uVar2,*(u32 *)(*(int *)(iVar1 + 0x6ac) + 8),0x90,0x60);
  return;
}

/* 0x0039D8D0, 0x58 bytes. */
void func_0039D8D0(void)
{
    int iVar1;

  
  iVar1 = func_002FC2C0();
  iVar1 = *(int *)(*(int *)(iVar1 + 0x6ac) + 4);
  if (iVar1 == 1) {
    func_0039D890();
  }
  else if (iVar1 == 0) {
    func_0039D5E0();
  }
  return;
}

/* 0x0039E490, 0x68 bytes, matching. */
void func_0039E490(void)
{
    int iVar2;
    int lVar3;
    u32 * puVar1;

  
  puVar1 = (u32 *)func_002FC2C0();
  func_003A9170();
  lVar3 = func_00389050();
  if (lVar3 == 1) {
    iVar2 = func_00389090();
    func_0039C540(iVar2 + 1);
  }
  else if (lVar3 == 0) {
    func_002FC660();
    *puVar1 = 0;
  }
  return;
}

/* 0x0039E8C0, 0x238 bytes. */
void func_0039E8C0(int param_1)
{
    int iVar3;
    short * psVar5;
    int sVar1;
    int uVar2;
    int uVar4;

  
  psVar5 = (short *)((*(u32 *)(g_005BA6A0 + 0x0)) + ((int)param_1 + 0x1a4) * 0x2c);
  uVar4 = func_0039E720();
  iVar3 = func_0039E7C0(param_1);
  sVar1 = (short)param_1 * 2;
  iVar3 = iVar3 * 0x1e;
  *psVar5 = sVar1 + 0x2d3;
  psVar5[1] = sVar1 + 0x2d4;
  *(u8 *)(psVar5 + 2) = ((g_00418EF0 + 0x10))[iVar3];
  uVar2 = func_0039E740(param_1);
  *(u8 *)((int)psVar5 + 5) = uVar2;
  uVar2 = func_0039E6E0(param_1);
  *(u8 *)(psVar5 + 3) = uVar2;
  *(char *)((int)psVar5 + 7) = (char)uVar4;
  *(u8 *)(psVar5 + 4) = ((g_00418EF0 + 0x11))[iVar3];
  uVar2 = func_001707A0(uVar4,0);
  *(u8 *)((int)psVar5 + 9) = uVar2;
  *(u8 *)(psVar5 + 5) = 0;
  psVar5[6] = *(short *)((g_00418EF0 + 0x0) + iVar3);
  psVar5[7] = *(short *)((g_00418EF0 + 0x2) + iVar3);
  psVar5[8] = *(short *)((g_00418EF0 + 0x4) + iVar3);
  psVar5[9] = *(short *)((g_00418EF0 + 0x6) + iVar3);
  psVar5[10] = *(short *)((g_00418EF0 + 0x8) + iVar3);
  psVar5[0xb] = *(short *)((g_00418EF0 + 0xA) + iVar3);
  psVar5[0xc] = *(short *)((g_00418EF0 + 0xC) + iVar3);
  psVar5[0xd] = *(short *)((g_00418EF0 + 0xE) + iVar3);
  *(u8 *)(psVar5 + 0xe) = ((g_00418EF0 + 0x12))[iVar3];
  *(u8 *)((int)psVar5 + 0x1d) = ((g_00418EF0 + 0x13))[iVar3];
  *(u8 *)(psVar5 + 0xf) = ((g_00418EF0 + 0x14))[iVar3];
  *(u8 *)((int)psVar5 + 0x1f) = ((g_00418EF0 + 0x15))[iVar3];
  psVar5[0x10] = (u16)(u8)((g_00418EF0 + 0x16))[iVar3];
  *(u8 *)(psVar5 + 0x11) = ((g_00418EF0 + 0x18))[iVar3];
  *(u8 *)((int)psVar5 + 0x25) = ((g_00418EF0 + 0x1B))[iVar3];
  *(u8 *)((int)psVar5 + 0x23) = ((g_00418EF0 + 0x19))[iVar3];
  *(u8 *)(psVar5 + 0x13) = ((g_00418EF0 + 0x1C))[iVar3];
  *(u8 *)(psVar5 + 0x12) = ((g_00418EF0 + 0x1A))[iVar3];
  *(u8 *)((int)psVar5 + 0x27) = ((g_00418EF0 + 0x1D))[iVar3];
  psVar5[0x14] = 2;
  psVar5[0x15] = 0;
  return;
}

/* 0x0039EF80, 0x2C bytes, matching. */
void func_0039EF80(int param_1)
{
    int iVar1;

  
  iVar1 = func_002FC2C0();
  *(u32 *)(*(int *)(iVar1 + 0x694) + 0x220) = param_1;
  return;
}

/* 0x0039F0F0, 0x238 bytes. */
void func_0039F0F0(void)
{
    int iVar1;
    int iVar2;
    int uVar3;
    int uVar4;

  
  iVar2 = func_002FC2C0();
  iVar2 = *(int *)(iVar2 + 0x694);
  iVar1 = *(int *)(*(int *)(iVar2 + 0x210) * 4 + iVar2 + 0x1e0);
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar3 = 0;
  }
  else {
    uVar3 = (*(u16 *)(g_0050074C + 0x0));
  }
  if (((*(u8 *)(g_0050074C + 0x18)) & 1) == 0 || ((*(u8 *)(g_0050074C + 0x19)) & 1) != 1) {
    uVar4 = 0;
  }
  else {
    uVar4 = (*(u16 *)(g_0050074C + 0x2));
  }
  if ((uVar3 & 0x10) == 0) {
    if ((uVar3 & 0x4000) == 0) {
      if ((uVar3 & 0x1000) == 0) {
        if ((uVar4 & 0x4000) == 0) {
          if (((uVar4 & 0x1000) != 0) && (0 < *(int *)(iVar2 + 0x214))) {
            func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
            *(int *)(iVar2 + 0x214) = *(int *)(iVar2 + 0x214) + -1;
          }
        }
        else if (*(int *)(iVar2 + 0x214) < iVar1 + -1) {
          func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
          *(int *)(iVar2 + 0x214) = *(int *)(iVar2 + 0x214) + 1;
        }
      }
      else if (1 < iVar1) {
        func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
        if (*(int *)(iVar2 + 0x214) == 0) {
          *(int *)(iVar2 + 0x214) = iVar1 + -1;
        }
        else {
          *(int *)(iVar2 + 0x214) = *(int *)(iVar2 + 0x214) + -1;
        }
      }
    }
    else if (1 < iVar1) {
      func_0023AD10(0,0,0x2cdc,0x2cdc,0x1000);
      if (*(int *)(iVar2 + 0x214) == iVar1 + -1) {
        *(u32 *)(iVar2 + 0x214) = 0;
      }
      else {
        *(int *)(iVar2 + 0x214) = *(int *)(iVar2 + 0x214) + 1;
      }
    }
  }
  else {
    func_0023AD10(2,0,0x2cdc,0x2cdc,0x1000);
    func_0039EFB0(*(u32 *)(iVar2 + 0x218));
    *(u32 *)(iVar2 + 0x214) = *(u32 *)(iVar2 + 0x210);
    *(u32 *)(iVar2 + 0x218) = 0xffffffff;
    func_0039EF80(0);
  }
  return;
}

/* 0x0039F7E0, 0x60 bytes. */
int func_0039F7E0(void)
{
    int iVar1;
    int uVar2;

  
  iVar1 = func_002FC2C0();
  iVar1 = *(int *)(*(int *)(iVar1 + 0x694) + 0x220);
  uVar2 = 0;
  if (iVar1 == 1) {
    func_0039F0F0();
  }
  else {
    if (iVar1 != 0) {
      return 0;
    }
    uVar2 = func_0039F040();
  }
  return uVar2;
}

/* 0x0039F840, 0x40 bytes. */
void func_0039F840(void)
{
  (*(u32 *)(g_007BAC20 + 0x0)) = 0;
  (*(u32 *)(g_007BAC20 + 0x14)) = 1;
  (*(u32 *)(g_007BAC20 + 0x4)) = 0;
  (*(u32 *)(g_007BAC20 + 0x8)) = 0;
  (*(u32 *)(g_007BAC20 + 0xC)) = 0;
  (*(u32 *)(g_007BAC20 + 0x10)) = 0;
  (*(u32 *)(g_007BAC20 + 0x18)) = 0;
  return;
}

/* 0x0039F880, 0x94 bytes, matching. */
void func_0039F880(void)
{
    int uVar1;

  
  uVar1 = func_0030D7D0();
  if ((*(u32 *)(g_007BAC24 + 0x10)) != 0) {
    func_00382310(uVar1,(*(u32 *)(g_007BAC24 + 0x0)),(*(u32 *)(g_007BAC24 + 0x4)));
  }
  if ((*(u32 *)(g_007BAC24 + 0x14)) != 0) {
    func_00382410(uVar1,(*(u32 *)(g_007BAC24 + 0x8)));
  }
  if ((*(u32 *)(g_007BAC24 + 0x10)) != 0) {
    func_00382590(uVar1,(*(u32 *)(g_007BAC24 + 0xC)) * 10);
  }
  return;
}

/* 0x0039F960, 0x7C bytes, matching. */
void func_0039F960(void)
{
    int uVar1;
    int uVar2;
    int uVar3;

  
  uVar1 = func_00327C70();
  uVar2 = func_00327D50();
  uVar3 = func_00327C00();
  uVar3 = func_00327140(uVar3,uVar1);
  uVar1 = func_00327170(uVar1);
  func_0039F920(uVar3,uVar1);
  uVar1 = func_003280E0();
  func_0039F940(uVar1);
  uVar1 = func_002F9060(uVar2);
  func_0039F950(uVar1);
  return;
}

/* 0x0039F9F0, 0x48 bytes. */
void func_0039F9F0(int param_1)
{
  if ((param_1 != 0) && ((*(u32 *)(g_007BAC38 + 0x0)) == 0)) {
    func_003823B0();
  }
  (*(u32 *)(g_007BAC38 + 0x0)) = (int)param_1;
  return;
}

/* 0x0039FA40, 0x64 bytes. */
void func_0039FA40(u32 *param_1, u32 *param_2)
{
    u32 uVar1;
    u32 uVar2;

  
  uVar2 = (*(u32 *)(g_007BAC34 + 0x4));
  uVar1 = (*(u32 *)(g_007BAC34 + 0x0));
  func_0039F9E0(*param_2);
  func_0039F9F0(param_2[1]);
  *param_1 = uVar1;
  param_1[1] = uVar2;
  return;
}

/* 0x003A2940, 0xC0 bytes. */
void func_003A2940(int param_1, int param_2)
{
    int iVar4;
    int lVar2;
    u8 * puVar5;
    int uVar1;
    int uVar3;

  
  lVar2 = func_0039FC70();
  if ((lVar2 != 0) && (param_2 != 0)) {
    uVar3 = func_0039FC30();
    uVar1 = func_003A0DD0(uVar3);
    puVar5 = (u8 *)param_2;
    *puVar5 = uVar1;
    uVar1 = func_003A0EC0(param_1);
    puVar5[1] = uVar1;
    iVar4 = 0;
    do {
      uVar1 = func_003A1070(param_1,iVar4);
      puVar5[iVar4 + 2] = uVar1;
      uVar1 = func_003A1180(param_1,iVar4);
      puVar5[iVar4 + 10] = uVar1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 8);
    uVar1 = func_003A0F60(param_1);
    puVar5[0x12] = uVar1;
    uVar1 = func_003A1260(param_1);
    puVar5[0x13] = uVar1;
  }
  return;
}

/* 0x003A2BA0, 0x180 bytes. */
void func_003A2BA0(void)
{
    int iVar2;
    int iVar3;
    int uVar1;

  
  func_0030CE90(10);
  iVar3 = 0;
  do {
    uVar1 = func_002F34E0(iVar3);
    func_003A0560(iVar3,uVar1);
    uVar1 = func_002F5E10(iVar3);
    func_003A05F0(iVar3,uVar1);
    uVar1 = func_002F5F60(iVar3);
    func_003A0670(iVar3,uVar1);
    uVar1 = func_002F60B0(iVar3);
    func_003A06F0(iVar3,uVar1);
    uVar1 = func_002F6200(iVar3);
    func_003A0770(iVar3,uVar1);
    uVar1 = func_002F6350(iVar3);
    func_003A07F0(iVar3,uVar1);
    uVar1 = func_002F64A0(iVar3);
    func_003A0870(iVar3,uVar1);
    uVar1 = func_002F65F0(iVar3);
    func_003A08F0(iVar3,uVar1);
    uVar1 = func_002F6740(iVar3);
    func_003A0970(iVar3,uVar1);
    uVar1 = func_002F59A0(iVar3);
    func_003A09F0(iVar3,uVar1);
    uVar1 = func_002F5730(iVar3);
    func_003A0A70(iVar3,uVar1);
    iVar2 = 0;
    do {
      uVar1 = func_002F47A0(iVar3,iVar2);
      func_003A0B20(iVar3,iVar2,uVar1);
      uVar1 = func_002F4900(iVar3,iVar2);
      func_003A0C50(iVar3,iVar2,uVar1);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x35);
    uVar1 = func_002F4660(iVar3);
    func_003A0D10(iVar3,uVar1);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x19f);
  return;
}

/* 0x003A2F10, 0x10C bytes. */
void func_003A2F10(void)
{
    int iVar1;
    int iVar2;

  
  iVar2 = 0;
  do {
    func_003A1F80(iVar2,4);
    func_003A2000(iVar2,0x459eb8);
    func_003A2090(iVar2,0);
    func_003A2110(iVar2,0);
    func_003A2190(iVar2,0);
    func_003A2230(iVar2,0);
    func_003A22E0(iVar2,0);
    func_003A2360(iVar2,0);
    iVar1 = 0;
    do {
      func_003A23E0(iVar2,iVar1,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 5);
    func_003A24C0(iVar2,0);
    func_003A2540(iVar2,0);
    func_003A25C0(iVar2,0);
    iVar1 = 0;
    do {
      func_003A2640(iVar2,iVar1,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  return;
}

/* 0x003A3020, 0x23C bytes. */
void func_003A3020(void)
{
    int iVar2;
    int uVar1;

  
  iVar2 = 0;
  do {
    func_0039FCA0(iVar2,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb);
  func_0039FCA0(0,1);
  func_0039FCA0(1,1);
  func_0039FCA0(2,1);
  func_0039FCA0(3,1);
  func_0039FCA0(4,1);
  func_0039FCA0(5,1);
  func_0039FCA0(6,1);
  iVar2 = 0;
  do {
    func_0039FE00(iVar2,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x1e);
  iVar2 = 0;
  do {
    func_0039FE00(iVar2,1);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x19);
  iVar2 = 0;
  do {
    func_0039FF60(iVar2,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 400);
  iVar2 = 0;
  do {
    func_003A00C0(iVar2,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 100);
  iVar2 = 0;
  do {
    uVar1 = func_0039FBF0(iVar2);
    func_003A02C0(uVar1,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x75);
  iVar2 = 0;
  do {
    func_003A1290(iVar2,0);
    func_003A1350(iVar2,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x1c);
  iVar2 = 0;
  do {
    func_003A1410(iVar2,0);
    func_003A15A0(iVar2,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x10);
  iVar2 = 0;
  do {
    func_003A16A0(iVar2,0);
    func_003A1830(iVar2,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 200);
  iVar2 = 0;
  do {
    func_003A1B60(iVar2,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xe6);
  iVar2 = 0;
  do {
    func_003A1CF0(iVar2,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x18);
  iVar2 = 0;
  do {
    func_003A1E80(iVar2,0);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x3e);
  iVar2 = 0;
  do {
    func_003A2750(iVar2,4);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  return;
}

/* 0x003A32C0, 0x160 bytes. */
void func_003A32C0(void)
{
    int iVar2;
    int iVar3;
    int uVar1;

  
  func_0030CE90(10);
  iVar3 = 0;
  do {
    func_003A0560(iVar3,0);
    uVar1 = func_002F5E10(iVar3);
    func_003A05F0(iVar3,uVar1);
    uVar1 = func_002F5F60(iVar3);
    func_003A0670(iVar3,uVar1);
    uVar1 = func_002F60B0(iVar3);
    func_003A06F0(iVar3,uVar1);
    uVar1 = func_002F6200(iVar3);
    func_003A0770(iVar3,uVar1);
    uVar1 = func_002F6350(iVar3);
    func_003A07F0(iVar3,uVar1);
    uVar1 = func_002F64A0(iVar3);
    func_003A0870(iVar3,uVar1);
    uVar1 = func_002F65F0(iVar3);
    func_003A08F0(iVar3,uVar1);
    uVar1 = func_002F6740(iVar3);
    func_003A0970(iVar3,uVar1);
    func_003A09F0(iVar3,0);
    func_003A0A70(iVar3,0);
    iVar2 = 0;
    do {
      uVar1 = func_002F47A0(iVar3,iVar2);
      func_003A0B20(iVar3,iVar2,uVar1);
      uVar1 = func_002F4900(iVar3,iVar2);
      func_003A0C50(iVar3,iVar2,uVar1);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x35);
    func_003A0D10(iVar3,0);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x19f);
  return;
}

/* 0x003A3860, 0xB8 bytes. */
void func_003A3860(int param_1, int param_2)
{
    int iVar1;
    int iVar3;
    int iVar4;
    int lVar2;
    u32 uVar5;

  
  iVar1 = func_003A0440();
  uVar5 = 0;
  iVar4 = 0;
  iVar3 = (int)g_00669D60;
  do {
    lVar2 = func_003636F0(iVar4);
    if ((lVar2 != 0) && (uVar5 < *(u32 *)(iVar3 + 0x8c))) {
      uVar5 = *(u32 *)(iVar3 + 0x8c);
    }
    iVar4 = iVar4 + 1;
    iVar3 = iVar3 + 0x48;
  } while (iVar4 < 2);
  if (iVar1 < (int)uVar5) {
    func_003A03E0(param_1,param_2,uVar5);
  }
  return;
}

/* 0x003A3980, 0x288 bytes, matching. */
void func_003A3980(int param_1)
{
    int iVar4;
    int lVar1;
    int lVar2;
    int uVar3;

  
  lVar1 = func_002F34E0();
  lVar2 = func_003A05B0(param_1);
  if (lVar2 < lVar1) {
    func_003A0560(param_1,lVar1);
  }
  lVar1 = func_002F39F0(param_1);
  lVar2 = func_003A0630(param_1);
  if (lVar2 < lVar1) {
    func_003A05F0(param_1,lVar1);
  }
  lVar1 = func_002F4C40(param_1);
  lVar2 = func_003A06B0(param_1);
  if (lVar2 < lVar1) {
    func_003A0670(param_1,lVar1);
  }
  lVar1 = func_002F4DD0(param_1);
  lVar2 = func_003A0730(param_1);
  if (lVar2 < lVar1) {
    func_003A06F0(param_1,lVar1);
  }
  lVar1 = func_002F4F60(param_1);
  lVar2 = func_003A07B0(param_1);
  if (lVar2 < lVar1) {
    func_003A0770(param_1,lVar1);
  }
  lVar1 = func_002F50F0(param_1);
  lVar2 = func_003A0830(param_1);
  if (lVar2 < lVar1) {
    func_003A07F0(param_1,lVar1);
  }
  lVar1 = func_002F5280(param_1);
  lVar2 = func_003A08B0(param_1);
  if (lVar2 < lVar1) {
    func_003A0870(param_1,lVar1);
  }
  lVar1 = func_002F5410(param_1);
  lVar2 = func_003A0930(param_1);
  if (lVar2 < lVar1) {
    func_003A08F0(param_1,lVar1);
  }
  lVar1 = func_002F55A0(param_1);
  lVar2 = func_003A09B0(param_1);
  if (lVar2 < lVar1) {
    func_003A0970(param_1,lVar1);
  }
  lVar1 = func_003A0A30(param_1);
  if (lVar1 == 0) {
    uVar3 = func_002F59A0(param_1);
    func_003A09F0(param_1,uVar3);
  }
  uVar3 = func_002F5730(param_1);
  func_003A0A70(param_1,uVar3);
  iVar4 = 0;
  do {
    lVar1 = func_002F47A0(param_1,iVar4);
    lVar2 = func_003A0BA0(param_1,iVar4);
    if (lVar2 < lVar1) {
      func_003A0B20(param_1,iVar4,lVar1);
    }
    uVar3 = func_002F4900(param_1,iVar4);
    func_003A0C50(param_1,iVar4,uVar3);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x35);
  lVar1 = func_002F4660(param_1);
  lVar2 = func_003A0D50(param_1);
  if (lVar2 < lVar1) {
    func_003A0D10(param_1,lVar1);
  }
  return;
}

/* 0x003A3CE0, 0xC8 bytes. */
void func_003A3CE0(int param_1)
{
    int iVar5;
    u8 * puVar2;
    int uVar1;
    int uVar3;
    int uVar4;

  
  uVar3 = func_0039FBF0();
  puVar2 = (u8 *)func_00328B30(uVar3);
  uVar4 = func_002F57F0(uVar3);
  uVar1 = func_002F5840(uVar4);
  puVar2[0x12] = uVar1;
  func_003A0D90(param_1,*puVar2);
  func_003A0E90(uVar3,puVar2[1]);
  iVar5 = 0;
  do {
    func_003A1040(uVar3,iVar5,puVar2[iVar5 + 2]);
    func_003A1150(uVar3,iVar5,puVar2[iVar5 + 10]);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 8);
  func_003A0F30(uVar3,puVar2[0x12]);
  func_003A11B0(uVar3,puVar2[0x13]);
  return;
}

/* 0x003A3DB0, 0x7C bytes, matching. */
void func_003A3DB0(void)
{
    int iVar4;
    int lVar1;
    int uVar2;
    int uVar3;

  
  iVar4 = 0;
  do {
    lVar1 = func_003636F0(iVar4);
    if (lVar1 != 0) {
      uVar2 = func_00363720(iVar4);
      uVar3 = func_002F5730(uVar2);
      uVar2 = func_0035DB20(uVar2,uVar3);
      uVar2 = func_0039FC30(uVar2);
      func_003A3CE0(uVar2);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 2);
  return;
}

/* 0x003A4990, 0x16C bytes. */
void func_003A4990(int param_1)
{
    int iVar2;
    int iVar3;
    u32 * puVar1;
    u32 uVar4;

  
  puVar1 = (u32 *)func_0019FBC0();
  func_003A2230(param_1,*puVar1);
  iVar2 = func_0019FBC0(param_1);
  func_003A1F80(param_1,*(u8 *)(iVar2 + 4));
  iVar2 = func_0019FBC0(param_1);
  func_003A2090(param_1,*(u8 *)(iVar2 + 5));
  iVar2 = func_0019FBC0(param_1);
  func_003A2110(param_1,*(u8 *)(iVar2 + 6));
  iVar2 = func_0019FBC0(param_1);
  func_003A2190(param_1,*(u8 *)(iVar2 + 7));
  iVar2 = func_0019FBC0(param_1);
  func_003A22E0(param_1,*(u8 *)(iVar2 + 8));
  iVar2 = func_0019FBC0(param_1);
  func_003A2360(param_1,*(u8 *)(iVar2 + 9));
  iVar2 = func_0019FBC0(param_1);
  func_003A24C0(param_1,*(u8 *)(iVar2 + 10));
  iVar2 = func_0019FBC0(param_1);
  func_003A2540(param_1,*(u8 *)(iVar2 + 0xb));
  iVar2 = func_0019FBC0(param_1);
  func_003A25C0(param_1,*(u8 *)(iVar2 + 0xc));
  uVar4 = 0;
  do {
    iVar2 = func_0019FBC0(param_1);
    func_003A2640(param_1,uVar4,(1 << (uVar4 & 0x1f) & (u32)*(u8 *)(iVar2 + 0xd)) != 0);
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 4);
  iVar2 = 0;
  do {
    iVar3 = func_0019FBC0(param_1);
    func_003A23E0(param_1,iVar2,*(u8 *)(iVar2 + iVar3 + 0xe));
    iVar2 = iVar2 + 1;
  } while (iVar2 < 5);
  iVar2 = func_0019FBC0(param_1);
  func_003A2000(param_1,iVar2 + 0x13);
  return;
}

/* 0x003A4BC0, 0x88 bytes, matching. */
void func_003A4BC0(void)
{
  func_003A34C0();
  func_003A3690();
  func_003A3710();
  func_003A3760();
  func_003A3E30();
  func_003A48E0();
  func_003A3EB0();
  func_003A4800();
  func_003A4830();
  func_003A4860();
  func_003A4890();
  func_003A4970();
  func_003A4980();
  func_003A2810(0,1);
  return;
}

/* 0x003A4C50, 0xC0 bytes, matching. */
void func_003A4C50(int param_1)
{
  func_003A3420();
  func_003A34C0();
  func_003A3690();
  func_003A3710();
  func_003A3760();
  func_003A3C10();
  func_003A3E30();
  func_003A48E0();
  func_003A3EB0();
  func_003A3F20();
  func_003A47E0(param_1);
  func_003A4800();
  func_003A4830();
  func_003A4860();
  func_003A4890();
  func_003A4970();
  func_003A4980();
  func_003A4B00();
  func_003A4B40();
  func_003A2810(0,1);
  return;
}

/* 0x003A4F40, 0xD0 bytes. */
void func_003A4F40(void)
{
    int iVar4;
    int iVar5;
    u8 * puVar2;
    int uVar1;
    int uVar3;

  
  iVar4 = 0;
  do {
    uVar3 = func_0039FBF0(iVar4);
    puVar2 = (u8 *)func_00328B30(uVar3);
    uVar1 = func_003A0DD0(iVar4);
    *puVar2 = uVar1;
    uVar1 = func_003A0EC0(uVar3);
    puVar2[1] = uVar1;
    iVar5 = 0;
    do {
      uVar1 = func_003A1070(uVar3,iVar5);
      puVar2[iVar5 + 2] = uVar1;
      uVar1 = func_003A1180(uVar3,iVar5);
      puVar2[iVar5 + 10] = uVar1;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 8);
    uVar1 = func_003A0F60(uVar3);
    puVar2[0x12] = uVar1;
    uVar1 = func_003A1260(uVar3);
    iVar4 = iVar4 + 1;
    puVar2[0x13] = uVar1;
  } while (iVar4 < 0x75);
  return;
}

/* 0x003A5010, 0x228 bytes. */
void func_003A5010(void)
{
    int iVar4;
    int iVar5;
    int iVar9;
    int lVar6;
    u32 * puVar3;
    int uVar1;
    u32 uVar2;
    int uVar7;
    u32 uVar8;

  
  iVar9 = 0;
  do {
    uVar2 = func_003A2290(iVar9);
    puVar3 = (u32 *)func_0019FBC0(iVar9);
    *puVar3 = uVar2;
    uVar1 = func_003A1FC0(iVar9);
    iVar4 = func_0019FBC0(iVar9);
    *(u8 *)(iVar4 + 4) = uVar1;
    uVar1 = func_003A20D0(iVar9);
    iVar4 = func_0019FBC0(iVar9);
    *(u8 *)(iVar4 + 5) = uVar1;
    uVar1 = func_003A2150(iVar9);
    iVar4 = func_0019FBC0(iVar9);
    *(u8 *)(iVar4 + 6) = uVar1;
    uVar1 = func_003A21D0(iVar9);
    iVar4 = func_0019FBC0(iVar9);
    *(u8 *)(iVar4 + 7) = uVar1;
    uVar1 = func_003A2320(iVar9);
    iVar4 = func_0019FBC0(iVar9);
    *(u8 *)(iVar4 + 8) = uVar1;
    uVar1 = func_003A23A0(iVar9);
    iVar4 = func_0019FBC0(iVar9);
    *(u8 *)(iVar4 + 9) = uVar1;
    uVar1 = func_003A2500(iVar9);
    iVar4 = func_0019FBC0(iVar9);
    *(u8 *)(iVar4 + 10) = uVar1;
    uVar1 = func_003A2580(iVar9);
    iVar4 = func_0019FBC0(iVar9);
    *(u8 *)(iVar4 + 0xb) = uVar1;
    uVar1 = func_003A2600(iVar9);
    iVar4 = func_0019FBC0(iVar9);
    *(u8 *)(iVar4 + 0xc) = uVar1;
    uVar8 = 0;
    do {
      lVar6 = func_003A26E0(iVar9,uVar8);
      if (lVar6 == 0) {
        iVar4 = func_0019FBC0(iVar9);
        *(u8 *)(iVar4 + 0xd) = *(u8 *)(iVar4 + 0xd) & ~(u8)(1 << (uVar8 & 0x1f));
      }
      else {
        iVar4 = func_0019FBC0(iVar9);
        *(u8 *)(iVar4 + 0xd) = *(u8 *)(iVar4 + 0xd) | (u8)(1 << (uVar8 & 0x1f));
      }
      uVar8 = uVar8 + 1;
    } while ((int)uVar8 < 4);
    iVar4 = 0;
    do {
      uVar1 = func_003A2450(iVar9,iVar4);
      iVar5 = func_0019FBC0(iVar9);
      *(u8 *)(iVar4 + iVar5 + 0xe) = uVar1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 5);
    uVar7 = func_003A2050(iVar9);
    iVar4 = func_0019FBC0(iVar9);
    func_00120928(iVar4 + 0x13,uVar7);
    iVar9 = iVar9 + 1;
  } while (iVar9 < 4);
  iVar9 = 0;
  do {
    uVar7 = func_003A27B0(iVar9);
    func_00329450(iVar9,uVar7);
    iVar9 = iVar9 + 1;
  } while (iVar9 < 2);
  return;
}

/* 0x003A54A0, 0x1A4 bytes. */
void func_003A54A0(int param_1)
{
    int iVar2;
    int uVar1;

  
  uVar1 = func_003A05B0();
  func_002F3440(param_1,uVar1);
  uVar1 = func_003A0630(param_1);
  func_002F3960(param_1,uVar1);
  uVar1 = func_003A06B0(param_1);
  func_002F4BB0(param_1,uVar1);
  uVar1 = func_003A0730(param_1);
  func_002F4D40(param_1,uVar1);
  uVar1 = func_003A07B0(param_1);
  func_002F4ED0(param_1,uVar1);
  uVar1 = func_003A0830(param_1);
  func_002F5060(param_1,uVar1);
  uVar1 = func_003A08B0(param_1);
  func_002F51F0(param_1,uVar1);
  uVar1 = func_003A0930(param_1);
  func_002F5380(param_1,uVar1);
  uVar1 = func_003A09B0(param_1);
  func_002F5510(param_1,uVar1);
  uVar1 = func_003A0A30(param_1);
  func_002F5930(param_1,uVar1);
  uVar1 = func_003A0AB0(param_1);
  func_002F56A0(param_1,uVar1);
  iVar2 = 0;
  do {
    uVar1 = func_003A0BA0(param_1,iVar2);
    func_002F4820(param_1,iVar2,uVar1);
    uVar1 = func_003A0CB0(param_1,iVar2);
    func_002F4980(param_1,iVar2,uVar1);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x35);
  uVar1 = func_003A0D50(param_1);
  func_002F46D0(param_1,uVar1);
  func_003A4E50(param_1);
  if ((-1 < param_1) && (param_1 < 0x1c)) {
    uVar1 = func_003A12F0(param_1);
    func_00328A00(param_1,uVar1);
    uVar1 = func_003A13B0(param_1);
    func_00328AA0(param_1,uVar1);
  }
  return;
}

/* 0x003A5650, 0x424 bytes. */
void func_003A5650(int param_1)
{
    int lVar1;
    int lVar2;
    int uVar3;

  
  if (((399 < param_1 && param_1 < 0x19f) && (lVar1 = func_0039E650((int)param_1 + -400), lVar1 != 0)
      ) && (lVar1 = func_002F59A0(param_1), lVar1 == 0)) {
    lVar1 = func_002F39F0(param_1);
    if (lVar1 < 1) {
      lVar1 = 0;
    }
    else {
      lVar1 = func_002F39F0(param_1);
    }
    lVar2 = func_002F5D30(param_1);
    if (lVar2 < lVar1) {
      uVar3 = func_002F5D30(param_1);
    }
    else {
      lVar1 = func_002F39F0(param_1);
      if (lVar1 < 1) {
        uVar3 = 0;
      }
      else {
        uVar3 = func_002F39F0(param_1);
      }
    }
    func_002F3960(param_1,uVar3);
    lVar1 = func_002F4C40(param_1);
    if (lVar1 < 1) {
      lVar1 = 0;
    }
    else {
      lVar1 = func_002F4C40(param_1);
    }
    lVar2 = func_002F5E80(param_1);
    if (lVar2 < lVar1) {
      uVar3 = func_002F5E80(param_1);
    }
    else {
      lVar1 = func_002F4C40(param_1);
      if (lVar1 < 1) {
        uVar3 = 0;
      }
      else {
        uVar3 = func_002F4C40(param_1);
      }
    }
    func_002F4BB0(param_1,uVar3);
    lVar1 = func_002F4DD0(param_1);
    if (lVar1 < 1) {
      lVar1 = 0;
    }
    else {
      lVar1 = func_002F4DD0(param_1);
    }
    lVar2 = func_002F5FD0(param_1);
    if (lVar2 < lVar1) {
      uVar3 = func_002F5FD0(param_1);
    }
    else {
      lVar1 = func_002F4DD0(param_1);
      if (lVar1 < 1) {
        uVar3 = 0;
      }
      else {
        uVar3 = func_002F4DD0(param_1);
      }
    }
    func_002F4D40(param_1,uVar3);
    lVar1 = func_002F4F60(param_1);
    if (lVar1 < 1) {
      lVar1 = 0;
    }
    else {
      lVar1 = func_002F4F60(param_1);
    }
    lVar2 = func_002F6120(param_1);
    if (lVar2 < lVar1) {
      uVar3 = func_002F6120(param_1);
    }
    else {
      lVar1 = func_002F4F60(param_1);
      if (lVar1 < 1) {
        uVar3 = 0;
      }
      else {
        uVar3 = func_002F4F60(param_1);
      }
    }
    func_002F4ED0(param_1,uVar3);
    lVar1 = func_002F50F0(param_1);
    if (lVar1 < 1) {
      lVar1 = 0;
    }
    else {
      lVar1 = func_002F50F0(param_1);
    }
    lVar2 = func_002F6270(param_1);
    if (lVar2 < lVar1) {
      uVar3 = func_002F6270(param_1);
    }
    else {
      lVar1 = func_002F50F0(param_1);
      if (lVar1 < 1) {
        uVar3 = 0;
      }
      else {
        uVar3 = func_002F50F0(param_1);
      }
    }
    func_002F5060(param_1,uVar3);
    lVar1 = func_002F5280(param_1);
    if (lVar1 < 1) {
      lVar1 = 0;
    }
    else {
      lVar1 = func_002F5280(param_1);
    }
    lVar2 = func_002F63C0(param_1);
    if (lVar2 < lVar1) {
      uVar3 = func_002F63C0(param_1);
    }
    else {
      lVar1 = func_002F5280(param_1);
      if (lVar1 < 1) {
        uVar3 = 0;
      }
      else {
        uVar3 = func_002F5280(param_1);
      }
    }
    func_002F51F0(param_1,uVar3);
    lVar1 = func_002F5410(param_1);
    if (lVar1 < 1) {
      lVar1 = 0;
    }
    else {
      lVar1 = func_002F5410(param_1);
    }
    lVar2 = func_002F6510(param_1);
    if (lVar2 < lVar1) {
      uVar3 = func_002F6510(param_1);
    }
    else {
      lVar1 = func_002F5410(param_1);
      if (lVar1 < 1) {
        uVar3 = 0;
      }
      else {
        uVar3 = func_002F5410(param_1);
      }
    }
    func_002F5380(param_1,uVar3);
    lVar1 = func_002F55A0(param_1);
    if (lVar1 < 1) {
      lVar1 = 0;
    }
    else {
      lVar1 = func_002F55A0(param_1);
    }
    lVar2 = func_002F6660(param_1);
    if (lVar2 < lVar1) {
      uVar3 = func_002F6660(param_1);
    }
    else {
      lVar1 = func_002F55A0(param_1);
      if (lVar1 < 1) {
        uVar3 = 0;
      }
      else {
        uVar3 = func_002F55A0(param_1);
      }
    }
    func_002F5510(param_1,uVar3);
  }
  return;
}

/* 0x003A5C40, 0x1D8 bytes. */
void func_003A5C40(int param_1)
{
    int iVar1;
    int iVar2;
    int iVar3;

  
  (*(u32 *)(g_007BACC4 + 0x6C)) = 0;
  (*(u32 *)(g_007BACC4 + 0x70)) = 0;
  (*(u32 *)(g_007BACC4 + 0x74)) = 0;
  (*(u32 *)(g_007BACC4 + 0x78)) = 0;
  (*(u32 *)(g_007BACC4 + 0x7C)) = 0;
  (*(u32 *)(g_007BACC4 + 0x80)) = 0;
  (*(u32 *)(g_007BACC4 + 0x104)) = 0;
  (*(u32 *)(g_007BACC4 + 0x108)) = 0;
  (*(u32 *)(g_007BACC4 + 0x120)) = 0;
  (*(u32 *)(g_007BACC4 + 0x10C)) = 0;
  (*(u32 *)(g_007BACC4 + 0x114)) = 0;
  (*(u32 *)(g_007BACC4 + 0x118)) = 0;
  (*(u32 *)(g_007BACC4 + 0x11C)) = 0;
  (*(u32 *)(g_007BACC4 + 0x124)) = 0;
  (*(u32 *)(g_007BACC4 + 0x128)) = 0xffffffff;
  (*(u32 *)(g_007BACC4 + 0x88)) = 0xffffffff;
  (*(u32 *)(g_007BACC4 + 0x94)) = 0;
  (*(u32 *)(g_007BACC4 + 0x8C)) = 1;
  (*(u32 *)(g_007BACC4 + 0xFC)) = 0;
  (*(u32 *)(g_007BACC4 + 0x100)) = 0;
  (*(u32 *)(g_007BACC4 + 0x90)) = 1;
  (*(u32 *)(g_007BACC4 + 0x84)) = param_1;
  func_003A5C10();
  func_003A5BA0();
  iVar3 = 0;
  iVar2 = (int)g_007BAC40;
  iVar1 = iVar2;
  do {
    *(u32 *)(iVar2 + 0x11c) = 0;
    iVar3 = iVar3 + 5;
    *(u8 *)(iVar1 + 0x1b0) = 0xff;
    *(u8 *)(iVar1 + 0x1c9) = 0;
    *(u8 *)(iVar1 + 0x1fb) = 0;
    *(u8 *)(iVar1 + 0x214) = 0;
    *(u8 *)(iVar1 + 0x1e2) = 0x1e;
    *(u32 *)(iVar2 + 0x120) = 0;
    *(u8 *)(iVar1 + 0x1b1) = 0xff;
    *(u8 *)(iVar1 + 0x1ca) = 0;
    *(u8 *)(iVar1 + 0x1fc) = 0;
    *(u8 *)(iVar1 + 0x215) = 0;
    *(u8 *)(iVar1 + 0x1e3) = 0x1e;
    *(u32 *)(iVar2 + 0x124) = 0;
    *(u8 *)(iVar1 + 0x1b2) = 0xff;
    *(u8 *)(iVar1 + 0x1cb) = 0;
    *(u8 *)(iVar1 + 0x1fd) = 0;
    *(u8 *)(iVar1 + 0x216) = 0;
    *(u8 *)(iVar1 + 0x1e4) = 0x1e;
    *(u32 *)(iVar2 + 0x128) = 0;
    *(u8 *)(iVar1 + 0x1b3) = 0xff;
    *(u8 *)(iVar1 + 0x1cc) = 0;
    *(u8 *)(iVar1 + 0x1fe) = 0;
    *(u8 *)(iVar1 + 0x217) = 0;
    *(u8 *)(iVar1 + 0x1e5) = 0x1e;
    *(u32 *)(iVar2 + 300) = 0;
    *(u8 *)(iVar1 + 0x1b4) = 0xff;
    iVar2 = iVar2 + 0x14;
    *(u8 *)(iVar1 + 0x1cd) = 0;
    *(u8 *)(iVar1 + 0x1ff) = 0;
    *(u8 *)(iVar1 + 0x218) = 0;
    *(u8 *)(iVar1 + 0x1e6) = 0x1e;
    iVar1 = iVar1 + 5;
  } while (iVar3 < 0x19);
  func_003A9170();
  (*(u32 *)(g_007BACC4 + 0x0)) = func_001026D0(1,*(u32 *)((g_00459EF0 + 0x0) + param_1 * 4),0,1,0,0,0x45b3e0,0x451)
  ;
  func_00102960(1);
  return;
}

/* 0x003A5E20, 0x174 bytes. */
void func_003A5E20(void)
{
    int iVar1;
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
  iVar1 = (int)g_007BAC40;
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
    func_00102EC0();
    (*(u32 *)(g_007BACC4 + 0x0)) = 0;
  }
  return;
}

/* 0x003A6110, 0xD8 bytes. */
void func_003A6110(int param_1, int param_2)
{
    int bVar1;
    int iVar3;
    int iVar4;
    u8 * pbVar6;
    u32 * puVar7;
    int uVar2;
    u32 uVar5;
    u32 uVar8;

  
  iVar4 = func_00106F10((*(u32 *)(g_007BACC4 + 0x0)) +
                       *(int *)((*(u32 *)(g_007BACC4 + 0x0)) + 8) * *(int *)(param_1 * 8 + (*(u32 *)(g_007BACC4 + 0x0)) + 0x78));
  uVar2 = *(u16 *)(iVar4 + 0xc);
  iVar3 = *(int *)(iVar4 + 8);
  if (0x1d < param_2) {
    param_2 = 0x18;
  }
  uVar8 = 0;
  pbVar6 = (g_0045AD90 + 0x0);
  puVar7 = (u32 *)((int)param_2 * 0x28 + 0x45a980);
  do {
    uVar5 = func_003A60F0(uVar8 & 0xff);
    bVar1 = *pbVar6;
    uVar8 = uVar8 + 1;
    pbVar6 = pbVar6 + 1;
    *(u32 *)(iVar4 + (u32)uVar2 + iVar3 + (uVar5 & 0xff) * 4) = (u32)bVar1 << 0x18 | *puVar7;
    puVar7 = puVar7 + 1;
  } while ((int)uVar8 < 10);
  return;
}

/* 0x003A6FE0, 0xE8 bytes. */
void func_003A6FE0(void)
{
    int bVar3;
    int iVar1;
    int iVar2;
    int iVar4;
    int iVar6;
    int iVar7;
    u32 uVar5;

  
  iVar7 = 0;
  iVar6 = (int)g_007BAC40;
  uVar5 = (*(u32 *)(g_007BADC4 + 0x0)) / 5;
  do {
    iVar1 = *(int *)(iVar6 + 0x88);
    iVar2 = *(int *)(iVar6 + 0x8c);
    bVar3 = false;
    if (-1 < iVar1) {
      iVar4 = func_0030AB90();
      bVar3 = iVar1 < iVar4;
    }
    if (bVar3) {
      bVar3 = false;
      if (-1 < iVar2) {
        iVar4 = func_0030AB90();
        bVar3 = iVar2 < iVar4;
      }
      if (bVar3) {
        func_003A64A0(iVar1,iVar2,uVar5 % 10,0x80);
      }
    }
    iVar7 = iVar7 + 1;
    iVar6 = iVar6 + 8;
  } while (iVar7 < 0xd);
  return;
}

/* 0x003A77C0, 0x110 bytes. */
void func_003A77C0(int param_1, int param_2)
{
    int iVar2;
    int iVar7;
    u8 * pbVar5;
    u32 * puVar6;
    int uVar1;
    u32 uVar3;
    u32 uVar4;

  
  iVar2 = func_00106F10((*(u32 *)(g_007BACC4 + 0x0)) + *(int *)((*(u32 *)(g_007BACC4 + 0x0)) + 8) * *(int *)((*(u32 *)(g_007BACC4 + 0x0)) + 0x28));
  uVar1 = *(u16 *)(iVar2 + 0xc);
  iVar7 = *(int *)(iVar2 + 8);
  uVar3 = func_003A60F0((param_1 & 0x1f) << 3);
  puVar6 = (u32 *)(iVar2 + (u32)uVar1 + iVar7 + (uVar3 & 0xff) * 4);
  if (0x1f < param_2) {
    param_2 = 0x18;
  }
  pbVar5 = (g_0045A830 + 0x100);
  uVar3 = *(u32 *)((g_0045A830 + 0x0) + (int)param_2 * 4);
  iVar7 = 0;
  do {
    if (param_2 == 0x1e) {
      uVar4 = 0;
    }
    else if ((param_2 == 0x1a) || (param_2 == 0x1f)) {
      uVar4 = (u32)(u8)((g_0045A830 + 0x107))[-iVar7] << 0x18;
    }
    else {
      uVar4 = (u32)*pbVar5 << 0x18;
    }
    *puVar6 = uVar3 & 0xffffff | uVar4;
    iVar7 = iVar7 + 1;
    pbVar5 = pbVar5 + 1;
    puVar6 = puVar6 + 1;
  } while (iVar7 < 8);
  return;
}

/* 0x003A78E0, 0x128 bytes. */
void func_003A78E0(int param_1, int param_2, int param_3)
{
    int iVar2;
    int iVar7;
    u8 * pbVar5;
    u32 * puVar6;
    int uVar1;
    u32 uVar3;
    u32 uVar4;

  
  iVar2 = func_00106F10((*(u32 *)(g_007BACC4 + 0x0)) + *(int *)((*(u32 *)(g_007BACC4 + 0x0)) + 8) * *(int *)((*(u32 *)(g_007BACC4 + 0x0)) + 0x20));
  uVar1 = *(u16 *)(iVar2 + 0xc);
  iVar7 = *(int *)(iVar2 + 8);
  uVar3 = func_003A60F0(((u32)param_1 & 0x1f) << 3);
  puVar6 = (u32 *)(iVar2 + (u32)uVar1 + iVar7 + (uVar3 & 0xff) * 4);
  if (0x1f < param_2) {
    param_2 = 0x18;
  }
  iVar7 = 0;
  *(char *)((u32)param_1 + 0x7bae22) = (char)param_2;
  pbVar5 = (g_0045A8B0 + 0x88);
  uVar3 = *(u32 *)((g_0045A8B0 + 0x0) + (int)param_2 * 4);
  do {
    if (param_2 == 0x1e) {
      uVar4 = 0;
    }
    else {
      uVar4 = (u32)*pbVar5 << 0x18;
    }
    *puVar6 = uVar3 & 0xffffff | uVar4;
    iVar7 = iVar7 + 1;
    pbVar5 = pbVar5 + 1;
    puVar6 = puVar6 + 1;
  } while (iVar7 < 8);
  if (param_3 == 0) {
    param_2 = 0x19;
  }
  if (param_2 == 0x1e) {
    param_2 = 0x19;
  }
  func_003A77C0(param_1,param_2);
  return;
}

/* 0x003A7C70, 0x120 bytes. */
void func_003A7C70(void)
{
    int bVar1;
    int iVar3;
    int iVar7;
    int iVar8;
    int lVar4;
    int lVar5;
    int uVar2;
    int uVar6;

  
  iVar7 = 0;
  iVar8 = (int)g_007BAC40;
  do {
    bVar1 = false;
    *(u8 *)(iVar8 + 0x1b0) = 0xff;
    if ((-1 < iVar7) && (iVar3 = func_0030AB90(), iVar7 < iVar3)) {
      bVar1 = true;
    }
    if (bVar1) {
      lVar4 = func_0030AFF0(iVar7);
      bVar1 = false;
      if (-1 < lVar4) {
        lVar5 = func_0030AB90();
        bVar1 = lVar4 < lVar5;
      }
      if (bVar1) {
        uVar6 = func_002F8F20(lVar4);
        uVar2 = func_002F6850(uVar6);
        *(u8 *)(iVar8 + 0x1b0) = uVar2;
      }
    }
    iVar7 = iVar7 + 1;
    iVar8 = iVar8 + 1;
  } while (iVar7 < 0x19);
  func_003A7A10();
  func_003A7AC0();
  func_003A7B60();
  lVar4 = func_00327D60();
  bVar1 = false;
  if (-1 < lVar4) {
    lVar5 = func_0030AB90();
    bVar1 = lVar4 < lVar5;
  }
  lVar5 = -1;
  if (bVar1) {
    lVar5 = lVar4;
  }
  func_003A9060(lVar5);
  return;
}

/* 0x003A7ED0, 0x120 bytes. */
void func_003A7ED0(void)
{
    int bVar1;
    int iVar3;
    int iVar7;
    int iVar8;
    int lVar4;
    int lVar5;
    int uVar2;
    int uVar6;

  
  iVar7 = 0;
  iVar8 = (int)g_007BAC40;
  do {
    bVar1 = false;
    *(u8 *)(iVar8 + 0x1b0) = 0xff;
    if ((-1 < iVar7) && (iVar3 = func_0030AB90(), iVar7 < iVar3)) {
      bVar1 = true;
    }
    if (bVar1) {
      lVar4 = func_0030AFF0(iVar7);
      bVar1 = false;
      if (-1 < lVar4) {
        lVar5 = func_0030AB90();
        bVar1 = lVar4 < lVar5;
      }
      if (bVar1) {
        uVar6 = func_002F8F20(lVar4);
        uVar2 = func_002F6850(uVar6);
        *(u8 *)(iVar8 + 0x1b0) = uVar2;
      }
    }
    iVar7 = iVar7 + 1;
    iVar8 = iVar8 + 1;
  } while (iVar7 < 0x19);
  func_003A7A10();
  func_003A7AC0();
  func_003A7B60();
  lVar4 = func_00327D60();
  bVar1 = false;
  if (-1 < lVar4) {
    lVar5 = func_0030AB90();
    bVar1 = lVar4 < lVar5;
  }
  lVar5 = -1;
  if (bVar1) {
    lVar5 = lVar4;
  }
  func_003A9060(lVar5);
  return;
}

/* 0x003A83A0, 0xC0 bytes. */
int func_003A83A0(int param_1, int param_2)
{
    int iVar2;
    u32 uVar1;
    u32 uVar3;
    u32 uVar4;

  
  uVar1 = *(u32 *)((g_0045A894 + 0x1C) + param_2 * 4);
  iVar2 = *(int *)(param_1 * 4 + 0x7bad5c);
  uVar4 = (*(u32 *)(g_0045A894 + 0x0)) >> 8 & 0xff;
  uVar3 = (*(u32 *)(g_0045A894 + 0x0)) >> 0x10 & 0xff;
  return ((*(u32 *)(g_0045A894 + 0x0)) & 0xff) - (iVar2 * (((*(u32 *)(g_0045A894 + 0x0)) & 0xff) - (uVar1 & 0xff))) / 100 |
         (uVar3 - (iVar2 * (uVar3 - (uVar1 >> 0x10 & 0xff))) / 100) * 0x10000 |
         (uVar4 - (iVar2 * (uVar4 - (uVar1 >> 8 & 0xff))) / 100) * 0x100;
}

/* 0x003A8B00, 0x90 bytes. */
void func_003A8B00(void)
{
  if ((*(u32 *)(g_007BADC8 + 0x20)) == 2) {
    (*(u32 *)(g_007BADC8 + 0x20)) = 0;
    (*(u32 *)(g_007BADC8 + 0x24)) = 0xffffffff;
  }
  else if ((*(u32 *)(g_007BADC8 + 0x20)) == 1) {
    func_003A7C70();
    (*(u32 *)(g_007BADC8 + 0x20)) = (*(u32 *)(g_007BADC8 + 0x20)) + 1;
  }
  else if ((*(u32 *)(g_007BADC8 + 0x20)) == 0) {
    (*(u32 *)(g_007BADC8 + 0x20)) = 1;
    (*(u32 *)(g_007BADC8 + 0x0)) = 0;
  }
  return;
}

/* 0x003A8D10, 0xAC bytes. */
void func_003A8D10(void)
{
  if ((*(u32 *)(g_007BADC8 + 0x20)) == 2) {
    (*(u32 *)(g_007BADC8 + 0x20)) = 0;
    (*(u32 *)(g_007BADC8 + 0x24)) = 0xffffffff;
  }
  else if ((*(u32 *)(g_007BADC8 + 0x20)) == 1) {
    func_003A7C70();
    func_003A9010(0);
    func_003A97C0(g_007BACB8,1,1);
    (*(u32 *)(g_007BADC8 + 0x20)) = (*(u32 *)(g_007BADC8 + 0x20)) + 1;
  }
  else if ((*(u32 *)(g_007BADC8 + 0x20)) == 0) {
    (*(u32 *)(g_007BADC8 + 0x20)) = 1;
    (*(u32 *)(g_007BADC8 + 0x0)) = 0;
  }
  return;
}

/* 0x003A8DC0, 0x244 bytes. */
int func_003A8DC0(void)
{
    int bVar1;
    int bVar2;
    int iVar4;
    int iVar5;
    u32 uVar3;

  
  bVar1 = false;
  bVar2 = false;
  if ((*(u32 *)(g_007BACB4 + 0x138)) == 2) {
    func_003A8D10();
    uVar3 = 0;
  }
  else if ((*(u32 *)(g_007BACB4 + 0x138)) == 1) {
    func_003A8B90();
    uVar3 = 0;
  }
  else if ((*(u32 *)(g_007BACB4 + 0x138)) == 0) {
    func_003A8B00();
    uVar3 = 0;
  }
  else {
    iVar5 = 0;
    iVar4 = (int)g_007BAC40;
    do {
      if (*(char *)(iVar4 + 0x1fb) == '\0') {
        if (*(char *)(iVar4 + 0x214) != '\0') {
          func_003A89F0(iVar5);
          bVar2 = true;
        }
      }
      else {
        func_003A8240(iVar5);
        bVar1 = true;
      }
      func_003A86F0(iVar5);
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 1;
    } while (iVar5 < 0x19);
    if (bVar1) {
      (*(u32 *)(g_007BACB4 + 0xA4)) = (*(u32 *)(g_007BACB4 + 0xA4)) + 1;
      if (0x3f < (*(u32 *)(g_007BACB4 + 0xA4))) {
        (*(u32 *)(g_007BACB4 + 0xA4)) = 0;
      }
    }
    else {
      (*(u32 *)(g_007BACB4 + 0xA4)) = 0;
    }
    if (bVar2) {
      (*(u32 *)(g_007BACB4 + 0x10C)) = (*(u32 *)(g_007BACB4 + 0x10C)) + 1;
      if (0x22 < (*(u32 *)(g_007BACB4 + 0x10C))) {
        (*(u32 *)(g_007BACB4 + 0x10C)) = 0;
      }
    }
    else {
      (*(u32 *)(g_007BACB4 + 0x10C)) = 0;
    }
    (*(u32 *)(g_007BACB4 + 0x110)) = (*(u32 *)(g_007BACB4 + 0x110)) + 1;
    if (0x31 < (*(u32 *)(g_007BACB4 + 0x110))) {
      (*(u32 *)(g_007BACB4 + 0x110)) = 0;
    }
    if (((*(u32 *)(g_007BACB4 + 0x0)) != -1) && ((*(u32 *)(g_007BACB4 + 0x0)) = (*(u32 *)(g_007BACB4 + 0x0)) + 1, 99 < (*(u32 *)(g_007BACB4 + 0x0)))) {
      func_003A5C10();
    }
    iVar4 = func_003A8AD0((*(u32 *)(g_007BACB4 + 0xA0)));
    if ((*(u32 *)(g_007BACB4 + 0x7C)) != iVar4) {
      bVar1 = false;
      if ((*(u32 *)(g_007BACB4 + 0x7C)) < iVar4) {
        (*(u32 *)(g_007BACB4 + 0x7C)) = (*(u32 *)(g_007BACB4 + 0x7C)) + 0xc;
        if (iVar4 <= (*(u32 *)(g_007BACB4 + 0x7C))) {
          bVar1 = true;
        }
      }
      else {
        (*(u32 *)(g_007BACB4 + 0x7C)) = (*(u32 *)(g_007BACB4 + 0x7C)) + -0xc;
        if ((*(u32 *)(g_007BACB4 + 0x7C)) < iVar4) {
          bVar1 = true;
        }
      }
      if (bVar1) {
        (*(u32 *)(g_007BACB4 + 0x9C)) = (*(u32 *)(g_007BACB4 + 0xA0));
        (*(u32 *)(g_007BACB4 + 0x7C)) = iVar4;
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

/* 0x003A91F0, 0xD8 bytes. */
void func_003A91F0(void)
{
    int iVar1;
    int iVar2;

  
  iVar2 = 0;
  iVar1 = (int)g_007BAC40;
  do {
    iVar2 = iVar2 + 6;
    *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 0x88);
    *(u32 *)(iVar1 + 8) = *(u32 *)(iVar1 + 0x8c);
    *(u32 *)(iVar1 + 0xc) = *(u32 *)(iVar1 + 0x90);
    *(u32 *)(iVar1 + 0x10) = *(u32 *)(iVar1 + 0x94);
    *(u32 *)(iVar1 + 0x14) = *(u32 *)(iVar1 + 0x98);
    *(u32 *)(iVar1 + 0x18) = *(u32 *)(iVar1 + 0x9c);
    *(u32 *)(iVar1 + 0x1c) = *(u32 *)(iVar1 + 0xa0);
    *(u32 *)(iVar1 + 0x20) = *(u32 *)(iVar1 + 0xa4);
    *(u32 *)(iVar1 + 0x24) = *(u32 *)(iVar1 + 0xa8);
    *(u32 *)(iVar1 + 0x28) = *(u32 *)(iVar1 + 0xac);
    *(u32 *)(iVar1 + 0x2c) = *(u32 *)(iVar1 + 0xb0);
    *(u32 *)(iVar1 + 0x30) = *(u32 *)(iVar1 + 0xb4);
    iVar1 = iVar1 + 0x30;
  } while (iVar2 < 7);
  iVar2 = iVar2 * 8;
  *(u32 *)(iVar2 + 0x7bac44) = *(u32 *)(iVar2 + 0x7bacc8);
  *(u32 *)(iVar2 + 0x7bac48) = *(u32 *)(iVar2 + 0x7baccc);
  func_003A9170();
  return;
}

/* 0x003A9510, 0xF8 bytes. */
void func_003A9510(int *param_1, int param_2, int param_3)
{
    int bVar4;
    int iVar5;
    int iVar6;
    int lVar1;
    int * piVar3;
    int uVar2;

  
  func_003A7C10();
  iVar6 = 0;
  lVar1 = func_0030AB90();
  if (0 < lVar1) {
    do {
      bVar4 = false;
      iVar5 = 0;
      if (0 < param_2) {
        piVar3 = param_1;
        do {
          if (iVar6 == *piVar3) {
            bVar4 = true;
          }
          iVar5 = iVar5 + 1;
          piVar3 = piVar3 + 1;
        } while (iVar5 < param_2);
      }
      if (bVar4) {
        uVar2 = func_0030AFF0(iVar6);
        uVar2 = func_002F9990(uVar2);
        func_003A78E0(iVar6,uVar2,1);
        func_003A80F0(iVar6,1);
      }
      else if (param_3 != 0) {
        func_003A8000(iVar6);
      }
      iVar6 = iVar6 + 1;
      iVar5 = func_0030AB90();
    } while (iVar6 < iVar5);
  }
  func_003A80A0(1);
  return;
}

/* 0x003AA920, 0x390 bytes. */
void func_003AA920(void)
{
    int iVar1;
    int iVar3;
    int iVar4;
    int iVar5;
    int iVar6;
    u32 uVar2;

  
  iVar1 = func_0021A630();
  if (*(int *)(iVar1 + 0x1664) == 0) {
    *(u32 *)(iVar1 + 0x1ae0) = 0;
  }
  else {
    uVar2 = func_003A9B00();
    *(u32 *)(iVar1 + 0x1ae0) = uVar2;
  }
  if (*(int *)(iVar1 + 0x1664) == 0) {
    *(u32 *)(iVar1 + 0x1ae4) = 0;
  }
  else {
    uVar2 = func_003A9BA0();
    *(u32 *)(iVar1 + 0x1ae4) = uVar2;
  }
  if (*(int *)(iVar1 + 0x1664) == 0) {
    iVar3 = 0;
    *(u32 *)(iVar1 + 0x1ae8) = 0;
  }
  else {
    iVar3 = func_003A9C20();
    *(int *)(iVar1 + 0x1ae8) = iVar3;
  }
  iVar3 = iVar3 + *(int *)(iVar1 + 0x1ae0) + *(int *)(iVar1 + 0x1ae4);
  *(int *)(iVar1 + 0x1aec) = iVar3;
  if (iVar3 < 1) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar3;
  }
  if (iVar4 < 10000) {
    if (iVar3 < 1) {
      iVar3 = 0;
    }
  }
  else {
    iVar3 = 9999;
  }
  *(int *)(iVar1 + 0x1aec) = iVar3;
  if (*(int *)(iVar1 + 0x1664) == 0) {
    *(u32 *)(iVar1 + 0x1aec) = 0;
  }
  uVar2 = func_00362290(1);
  *(u32 *)(iVar1 + 0x1af0) = uVar2;
  uVar2 = func_0036B980(0);
  *(u32 *)(iVar1 + 0x1af4) = uVar2;
  if (((*(u32 *)(g_00669DB8 + 0x0)) == 0) && (*(int *)(iVar1 + 0x1664) != 0)) {
    if (*(int *)(iVar1 + 0x1664) == 0) {
      iVar3 = (*(int *)(iVar1 + 0x1ae0) / 100) * 100;
      if (iVar3 < 1) {
        iVar4 = 0;
      }
      else {
        iVar4 = iVar3;
      }
      if (iVar4 < 0x12d) {
        if (iVar3 < 1) {
          iVar3 = 0;
        }
      }
      else {
        iVar3 = 300;
      }
      *(int *)(iVar1 + 0x1af8) = iVar3;
    }
    else {
      iVar3 = *(int *)(iVar1 + 0x1ae0) / 10;
      if (iVar3 < 0x65) {
        iVar4 = 100;
      }
      else {
        iVar4 = iVar3;
      }
      if (iVar4 < 0x12d) {
        if (iVar3 < 0x65) {
          iVar3 = 100;
        }
      }
      else {
        iVar3 = 300;
      }
      *(int *)(iVar1 + 0x1af8) = iVar3;
    }
    iVar4 = *(int *)(iVar1 + 0x1ae4);
    if (iVar4 < 1) {
      iVar6 = 0;
    }
    else {
      iVar6 = iVar4;
    }
    if (iVar6 < 0x385) {
      if (iVar4 < 1) {
        iVar4 = 0;
      }
    }
    else {
      iVar4 = 900;
    }
    *(int *)(iVar1 + 0x1afc) = iVar4;
    if (*(int *)(iVar1 + 0x1664) == 0) {
      iVar6 = (*(int *)(iVar1 + 0x1ae8) / 100) * 100;
      if (iVar6 < 1) {
        iVar5 = 0;
      }
      else {
        iVar5 = iVar6;
      }
      if (iVar5 < 0x385) {
        if (iVar6 < 1) {
          iVar6 = 0;
        }
      }
      else {
        iVar6 = 900;
      }
    }
    else {
      iVar6 = *(int *)(iVar1 + 0x1ae8);
      if (iVar6 < 0) {
        iVar6 = iVar6 + 1;
      }
      iVar6 = iVar6 >> 1;
      if (iVar6 < 1) {
        iVar5 = 0;
      }
      else {
        iVar5 = iVar6;
      }
      if (iVar5 < 0x385) {
        if (iVar6 < 1) {
          iVar6 = 0;
        }
      }
      else {
        iVar6 = 900;
      }
    }
    *(int *)(iVar1 + 0x1b00) = iVar6;
    iVar6 = iVar6 + (iVar3 - iVar4);
    *(int *)(iVar1 + 0x1b04) = iVar6;
    if (0 < iVar6) {
      *(int *)(iVar1 + 0x1b04) = ((iVar6 + 10) / 10) * 10;
    }
    iVar3 = *(int *)(iVar1 + 0x1b04);
    if (iVar3 < 0) {
      iVar3 = 0;
    }
    *(int *)(iVar1 + 0x1b04) = iVar3;
  }
  else {
    *(u32 *)(iVar1 + 0x1af8) = 0;
    *(u32 *)(iVar1 + 0x1afc) = 0;
    *(u32 *)(iVar1 + 0x1b00) = 0;
    *(u32 *)(iVar1 + 0x1b04) = 0;
  }
  return;
}

/* 0x003AB4F0, 0x310 bytes. */
int func_003AB4F0(int param_1)
{
    int iVar2;
    u32 uVar1;
    int uVar3;

  
  iVar2 = func_0021A630();
  if ((*(int *)(iVar2 + 0x1654) == 0) && (param_1 == 5)) {
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    uVar1 = (g_7000015C >> 0x10) % 100;
    if (uVar1 < 7) {
      uVar3 = 0;
    }
    else if (uVar1 < 0xe) {
      uVar3 = 1;
    }
    else if (uVar1 < 0x15) {
      uVar3 = 2;
    }
    else if (uVar1 < 0x1c) {
      uVar3 = 3;
    }
    else if (uVar1 < 0x23) {
      uVar3 = 4;
    }
    else if (uVar1 < 0x2a) {
      uVar3 = 5;
    }
    else if (uVar1 < 0x31) {
      uVar3 = 6;
    }
    else if (uVar1 < 0x38) {
      uVar3 = 7;
    }
    else if (uVar1 < 0x3f) {
      uVar3 = 8;
    }
    else if (uVar1 < 0x46) {
      uVar3 = 9;
    }
    else if (uVar1 < 0x4b) {
      uVar3 = 10;
    }
    else if (uVar1 < 0x50) {
      uVar3 = 0xb;
    }
    else if (uVar1 < 0x55) {
      uVar3 = 0xc;
    }
    else if (uVar1 < 0x5a) {
      uVar3 = 0xd;
    }
    else if (uVar1 < 0x5c) {
      uVar3 = 0xe;
    }
    else if (uVar1 < 100) {
      uVar3 = 0xf;
    }
    else {
      uVar3 = 0x10;
    }
  }
  else {
    g_7000015C = g_7000015C * 0x41c64e6d + 0x3039;
    uVar1 = (g_7000015C >> 0x10) % 100;
    if (uVar1 < 9) {
      uVar3 = 0;
    }
    else if (uVar1 < 0x12) {
      uVar3 = 1;
    }
    else if (uVar1 < 0x17) {
      uVar3 = 2;
    }
    else if (uVar1 < 0x1c) {
      uVar3 = 3;
    }
    else if (uVar1 < 0x26) {
      uVar3 = 4;
    }
    else if (uVar1 < 0x30) {
      uVar3 = 5;
    }
    else if (uVar1 < 0x3a) {
      uVar3 = 6;
    }
    else if (uVar1 < 0x44) {
      uVar3 = 7;
    }
    else if (uVar1 < 0x4e) {
      uVar3 = 8;
    }
    else if (uVar1 < 0x58) {
      uVar3 = 9;
    }
    else if (uVar1 < 0x5b) {
      uVar3 = 10;
    }
    else if (uVar1 < 0x5e) {
      uVar3 = 0xb;
    }
    else if (uVar1 < 0x61) {
      uVar3 = 0xc;
    }
    else if (uVar1 < 100) {
      uVar3 = 0xd;
    }
    else {
      uVar3 = 0x10;
    }
  }
  return uVar3;
}

/* 0x003AB800, 0x2AC bytes. */
void func_003AB800(void)
{
    int iVar11;
    int iVar12;
    int iVar13;
    int iVar14;
    int iVar2;
    int iVar3;
    int iVar6;
    int iVar7;
    int iVar8;
    u8 * pbVar10;
    u32 * puVar9;
    int uVar1;
    int uVar15;
    u32 uVar4;
    int uVar5;

  
  iVar2 = func_0021A630();
  iVar13 = 0;
  g_7000015C = *(u32 *)(iVar2 + 0x1670) | 1;
  do {
    iVar11 = iVar2 + iVar13 * 0x30;
    *(u32 *)(iVar11 + 0x16ec) = 0x10;
    *(u8 *)(iVar11 + 0x16f0) = 0;
    *(u32 *)(iVar11 + 0x16f4) = 0x10;
    *(u8 *)(iVar11 + 0x16f8) = 0;
    *(u32 *)(iVar11 + 0x16fc) = 0x10;
    *(u8 *)(iVar11 + 0x1700) = 0;
    *(u32 *)(iVar11 + 0x1704) = 0x10;
    *(u8 *)(iVar11 + 0x1708) = 0;
    *(u32 *)(iVar11 + 0x170c) = 0x10;
    *(u8 *)(iVar11 + 0x1710) = 0;
    *(u32 *)(iVar11 + 0x1714) = 0x10;
    *(u8 *)(iVar11 + 0x1718) = 0;
    if (*(int *)(iVar13 * 0x48 + 0x669e00) != 0) {
      iVar14 = 0;
      iVar3 = iVar2 + iVar13 * 0x52;
      iVar12 = iVar11;
      do {
        pbVar10 = (u8 *)(iVar3 + 0x1008 + (u32)*(u8 *)(iVar3 + 0x1059) * 0x14);
        uVar5 = func_002F57A0(*pbVar10);
        uVar15 = 0;
        if (*(int *)(iVar2 + 0x1654) == 0) {
          uVar15 = func_00327D50();
          uVar5 = func_0030AAD0(uVar5);
          uVar15 = func_002F9480(uVar15,uVar5);
        }
        puVar9 = (u32 *)(iVar12 + 0x16ec);
        if (iVar14 < *(int *)(iVar2 + iVar13 * 4 + 0x16e4)) {
          do {
            uVar4 = func_003AB4F0(uVar15);
            iVar7 = 0;
            *puVar9 = uVar4 & 0xff;
            iVar8 = 0;
            if (0 < iVar14) {
              uVar4 = *puVar9;
              iVar6 = iVar11;
              do {
                if (*(u32 *)(iVar6 + 0x16ec) == uVar4) {
                  if (((int)uVar4 < 0) || (9 < (int)uVar4)) break;
                  iVar7 = iVar7 + 1;
                }
                iVar8 = iVar8 + 1;
                iVar6 = iVar6 + 8;
              } while (iVar8 < iVar14);
            }
          } while ((iVar8 != iVar14) || (2 < iVar7));
          uVar4 = *puVar9;
          if (uVar4 == 0xf) {
            uVar1 = func_003AB200(iVar13,0xf);
            *(u8 *)(iVar12 + 0x16f0) = uVar1;
            if (*(u8 *)(iVar12 + 0x16f0) <= (u8)(((g_00428138 + 0x0))[*pbVar10] + pbVar10[0x13])) {
              *puVar9 = 0x10;
              *(u8 *)(iVar12 + 0x16f0) = 0;
            }
          }
          else if ((-1 < (int)uVar4) && ((int)uVar4 < 10)) {
            uVar1 = func_003AB200(iVar13,uVar4 & 0xff);
            *(u8 *)(iVar12 + 0x16f0) = uVar1;
          }
        }
        else {
          *puVar9 = 0x10;
          *(u8 *)(iVar12 + 0x16f0) = 0;
        }
        iVar14 = iVar14 + 1;
        iVar12 = iVar12 + 8;
      } while (iVar14 < 6);
    }
    iVar13 = iVar13 + 1;
    if (1 < iVar13) {
      return;
    }
  } while( true );
}

/* 0x003ABAB0, 0x1CC bytes. */
int func_003ABAB0(int param_1)
{
    int bVar1;
    int iVar10;
    int iVar3;
    int iVar6;
    int iVar7;
    int lVar5;
    u32 uVar2;
    u32 uVar4;
    u32 uVar8;
    u32 uVar9;

  
  iVar6 = 0;
  iVar3 = func_0021A630();
  uVar2 = *(u32 *)((int)param_1 * 4 + iVar3 + 0x1674);
  iVar3 = iVar3 + (int)param_1 * 0x52;
  bVar1 = *(u8 *)(iVar3 + 0x1059);
  lVar5 = func_0036DC80(uVar2,0x24);
  if ((lVar5 != 0) && (lVar5 = func_0036DBA0(uVar2,0x24), lVar5 != 0)) {
    iVar6 = ((int)lVar5 + 1) * 10;
    if (iVar6 < 0xb) {
      iVar10 = 10;
    }
    else {
      iVar10 = iVar6;
    }
    if (iVar10 < 0x1f) {
      if (iVar6 < 0xb) {
        iVar6 = 10;
      }
    }
    else {
      iVar6 = 0x1e;
    }
  }
  iVar10 = 0;
  do {
    iVar7 = iVar3 + 0x1008 + (u32)bVar1 * 0x14 + iVar10;
    if (*(char *)(iVar7 + 2) == '\a') {
      uVar8 = *(u8 *)(iVar7 + 10) + 1;
      uVar4 = 1;
      if (1 < uVar8) {
        uVar4 = uVar8;
      }
      uVar9 = 0x14;
      if ((uVar4 < 0x15) && (uVar9 = 1, 1 < uVar8)) {
        uVar9 = uVar8;
      }
      iVar6 = iVar6 + uVar9;
    }
    iVar10 = iVar10 + 1;
  } while (iVar10 < 8);
  lVar5 = func_003294A0(param_1);
  if ((lVar5 < 4) && (iVar3 = func_0019FBC0(lVar5), (*(u8 *)(iVar3 + 0xd) & 1) != 0)) {
    iVar6 = iVar6 + 0x14;
  }
  if (0x6d < iVar6) {
    iVar6 = 0x6e;
  }
  return iVar6;
}

/* 0x003AC380, 0xAC bytes, matching. */
int func_003AC380(int param_1, int param_2)
{
    int iVar1;
    int lVar3;
    int uVar2;

  
  uVar2 = func_00362320(param_2);
  uVar2 = func_003620E0(0,uVar2);
  lVar3 = func_0036DC80(uVar2,0x25);
  if (lVar3 != 0) {
    uVar2 = func_00362320(param_2);
    uVar2 = func_003620E0(0,uVar2);
    iVar1 = func_0036DBA0(uVar2,0x25);
    param_1 = (param_1 * (iVar1 * 5 + 10)) / 10;
  }
  return param_1;
}

/* 0x003AC430, 0xD4 bytes. */
int func_003AC430(int param_1)
{
    int iVar1;
    int lVar3;
    int uVar2;
    int uVar4;

  
  iVar1 = func_0021A630();
  uVar4 = 1;
  uVar2 = func_003620E0(1,param_1);
  switch(param_1) {
  case 0:
    if (*(int *)(iVar1 + 0x1654) == 1) {
      uVar4 = 0;
    }
    else {
      lVar3 = func_002F3E70(uVar2);
      if (lVar3 != 0) {
        uVar4 = 0;
      }
    }
    break;
  case 1:
  case 2:
    return 1;
  case 3:
  case 4:
  case 5:
  case 7:
    uVar4 = 2;
    break;
  case 6:
    if ((*(int *)(iVar1 + 0x1654) == 0) && (lVar3 = func_002F3E70(uVar2), lVar3 != 0)) {
      uVar4 = 0;
    }
  }
  return uVar4;
}

/* 0x003AC510, 0x140 bytes. */
int func_003AC510(int param_1, int param_2)
{
    int iVar2;
    int iVar4;
    int lVar3;
    u32 uVar1;

  
  iVar2 = 0;
  lVar3 = func_003637D0(0);
  if (lVar3 == 0) {
    iVar4 = 0;
    do {
      uVar1 = func_0036B4D0(param_1,param_2,iVar4);
      iVar4 = iVar4 + 1;
      iVar2 = iVar2 + (uVar1 & 0xff);
    } while (iVar4 < 9);
  }
  else {
    lVar3 = func_00362320(0);
    if (param_2 == lVar3) {
      iVar2 = (*(u32 *)(g_00669DEC + 0x0));
    }
    else {
      lVar3 = func_00362320(1);
      if (param_2 == lVar3) {
        iVar2 = (*(u32 *)(g_00669DEC + 0x48));
      }
      else {
        iVar2 = (*(u32 *)(g_00669DEC + 0x0));
      }
    }
  }
  if (iVar2 < 1) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar2;
  }
  if (iVar4 < 10000) {
    if (iVar2 < 1) {
      iVar2 = 0;
    }
  }
  else {
    iVar2 = 9999;
  }
  iVar2 = iVar2 << 1;
  if (iVar2 < 1) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar2;
  }
  if (iVar4 < 10000) {
    if (iVar2 < 1) {
      iVar2 = 0;
    }
  }
  else {
    iVar2 = 9999;
  }
  return iVar2;
}

/* 0x003AC650, 0x190 bytes. */
int func_003AC650(int param_1, int param_2)
{
    int iVar1;
    int iVar5;
    int iVar6;
    int lVar3;
    int lVar4;
    u32 uVar2;

  
  lVar3 = func_0036B8C0(0);
  iVar1 = func_003625B0();
  iVar5 = 0;
  iVar6 = 0;
  do {
    lVar4 = func_00362160(1,iVar5);
    if (lVar4 != 0x252) {
      uVar2 = func_0036B4D0(param_1,param_2,iVar5);
      lVar4 = func_003AC430(iVar5);
      if (lVar4 < 3) {
        iVar6 = iVar6 + (uVar2 & 0xff) * *(int *)((g_0041C080 + 0x0) + (int)lVar4 * 0x14 + iVar1 * 4);
      }
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 8);
  if (lVar3 < 8) {
    uVar2 = func_0036B4D0(param_1,param_2,8);
    lVar3 = func_003AC430(lVar3);
    if (lVar3 < 3) {
      iVar6 = iVar6 + (uVar2 & 0xff) * *(int *)((g_0041C080 + 0x0) + (iVar1 + (int)lVar3 * 5) * 4);
    }
  }
  if (iVar6 < 1) {
    iVar1 = 0;
  }
  else {
    iVar1 = iVar6;
  }
  if (iVar1 < 0x15af) {
    if (iVar6 < 1) {
      iVar6 = 0;
    }
  }
  else {
    iVar6 = 0x15ae;
  }
  return iVar6;
}

/* 0x003AC970, 0x94 bytes. */
int func_003AC970(int param_1, int param_2)
{
    int iVar1;
    int iVar3;
    u32 uVar2;

  
  iVar1 = func_003625B0();
  iVar1 = *(int *)((g_0041C0C0 + 0x0) + iVar1 * 4);
  uVar2 = func_0036B6C0(param_1,param_2);
  iVar1 = iVar1 * (uVar2 & 0xff);
  if (iVar1 < 1) {
    iVar3 = 0;
  }
  else {
    iVar3 = iVar1;
  }
  if (iVar3 < 10000) {
    if (iVar1 < 1) {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = 9999;
  }
  return iVar1;
}

/* 0x003ACA10, 0x27C bytes. */
int func_003ACA10(int param_1, int param_2)
{
    int iVar1;
    int iVar5;
    int iVar6;
    int iVar7;
    int lVar2;
    int lVar3;
    int uVar4;

  
  iVar1 = func_0021A630();
  iVar6 = 0;
  iVar5 = 10;
  if (0 < *(int *)(iVar1 + 0x1668)) {
    do {
      if ((param_1 == 0) && (lVar2 = func_00362320(iVar6), param_2 == lVar2)) break;
      iVar6 = iVar6 + 1;
    } while (iVar6 < *(int *)(iVar1 + 0x1668));
  }
  if (iVar6 < *(int *)(iVar1 + 0x1668)) {
    lVar2 = func_0036D310();
    if (lVar2 != 0) {
      if (*(int *)(iVar1 + 0x1664) == 0) {
        iVar5 = 0x1e;
      }
      else {
        iVar5 = 0x3c;
      }
    }
    iVar6 = 0;
    do {
      lVar2 = func_00362600(0,iVar6);
      if (lVar2 == 9) {
        iVar5 = (iVar5 * 0x14) / 10;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 2);
    iVar6 = *(int *)(iVar1 + 0x1668);
    iVar7 = 0;
    if (0 < iVar6) {
      do {
        lVar2 = func_00362320(iVar7);
        if ((((param_2 == lVar2) && (lVar2 = func_003294A0(iVar7), lVar2 < 4)) &&
            (lVar3 = func_0036D310(), lVar3 == 0)) &&
           (iVar6 = func_0019FBC0(lVar2), (*(u8 *)(iVar6 + 0xd) & 2) != 0)) {
          iVar5 = (iVar5 * 0xf) / 10;
        }
        iVar6 = *(int *)(iVar1 + 0x1668);
        iVar7 = iVar7 + 1;
      } while (iVar7 < iVar6);
    }
    iVar7 = 0;
    if (0 < iVar6) {
      do {
        lVar2 = func_00362320(iVar7);
        if (param_2 == lVar2) {
          uVar4 = func_00362320(iVar7);
          uVar4 = func_003620E0(0,uVar4);
          lVar2 = func_0036DC80(uVar4,0x13);
          if (lVar2 != 0) {
            uVar4 = func_00362320(iVar7);
            uVar4 = func_003620E0(0,uVar4);
            iVar6 = func_0036DBA0(uVar4,0x13);
            iVar5 = (iVar5 * (iVar6 + 10)) / 10;
          }
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 < *(int *)(iVar1 + 0x1668));
    }
  }
  else {
    iVar5 = 10;
  }
  return iVar5;
}

/* 0x003ACC90, 0xAF8 bytes. */
void func_003ACC90(void)
{
    int iVar11;
    int iVar12;
    int iVar13;
    int iVar14;
    int iVar15;
    int iVar16;
    int iVar2;
    int iVar6;
    int lVar7;
    int lVar8;
    int lVar9;
    int uVar1;
    int uVar10;
    u32 uVar3;
    u32 uVar4;
    u32 uVar5;

  
  iVar2 = func_0021A630();
  lVar7 = func_0036B8C0(1);
  lVar8 = func_0036B8C0(0);
  uVar3 = func_003AC7E0();
  *(u32 *)(iVar2 + 0x1794) = uVar3;
  iVar14 = (*(u32 *)(g_00669F9C + 0x4));
  if ((*(u32 *)(g_00669F9C + 0x0)) < 1) {
    iVar16 = 0;
  }
  else {
    iVar16 = (*(u32 *)(g_00669F9C + 0x0));
  }
  if ((*(u32 *)(g_00669F9C + 0x4)) < iVar16) {
    *(int *)(iVar2 + 0x1828) = (*(u32 *)(g_00669F9C + 0x4));
  }
  else {
    if ((*(u32 *)(g_00669F9C + 0x0)) < 1) {
      iVar14 = 0;
    }
    else {
      iVar14 = (*(u32 *)(g_00669F9C + 0x0));
    }
    *(int *)(iVar2 + 0x1828) = iVar14;
  }
  if (iVar14 < 1) {
    iVar16 = 0;
  }
  else {
    iVar16 = iVar14;
  }
  if (iVar16 < 0x41eb1) {
    if (iVar14 < 1) {
      iVar14 = 0;
    }
  }
  else {
    iVar14 = 270000;
  }
  *(int *)(iVar2 + 0x1828) = iVar14;
  iVar15 = 0;
  iVar14 = iVar2;
  iVar16 = iVar2;
  do {
    lVar9 = func_00362160(0,iVar15);
    if ((lVar9 == 0x252) || (lVar9 = func_0036B940(0,iVar15), lVar9 != 0)) {
      *(u32 *)(iVar14 + 0x174c) = 0;
      *(u32 *)(iVar14 + 6000) = 0;
      iVar13 = 0;
      *(u32 *)(iVar14 + 0x1798) = 0;
      *(u32 *)(iVar14 + 0x17bc) = 0;
      *(u32 *)(iVar14 + 0x17e0) = 0;
      *(u32 *)(iVar14 + 0x1804) = 0;
      *(u32 *)(iVar14 + 0x182c) = 0;
      iVar12 = iVar16;
      do {
        *(u32 *)(iVar12 + 0x1858) = 0x252;
        *(u8 *)(iVar12 + 0x185c) = 0;
        iVar13 = iVar13 + 3;
        *(u32 *)(iVar12 + 0x1860) = 0x252;
        *(u8 *)(iVar12 + 0x1864) = 0;
        *(u32 *)(iVar12 + 0x1868) = 0x252;
        *(u8 *)(iVar12 + 0x186c) = 0;
        iVar12 = iVar12 + 0x18;
      } while (iVar13 < 9);
    }
    else {
      uVar3 = func_003AC510(0,iVar15);
      *(u32 *)(iVar14 + 0x174c) = uVar3;
      uVar3 = func_003AC650(0,iVar15);
      *(u32 *)(iVar14 + 6000) = uVar3;
      uVar3 = func_003AC970(0,iVar15);
      *(u32 *)(iVar14 + 0x1798) = uVar3;
      iVar12 = func_003ACA10(0,iVar15);
      *(int *)(iVar14 + 0x17bc) = iVar12;
      iVar12 = (iVar12 * (*(int *)(iVar14 + 0x1798) +
                         *(int *)(iVar2 + 0x1794) +
                         *(int *)(iVar14 + 0x174c) + *(int *)(iVar14 + 6000))) / 10;
      *(int *)(iVar14 + 0x17e0) = iVar12;
      if (iVar12 < 1) {
        iVar13 = 0;
      }
      else {
        iVar13 = iVar12;
      }
      if (iVar13 < 10000) {
        if (iVar12 < 1) {
          iVar12 = 0;
        }
      }
      else {
        iVar12 = 9999;
      }
      *(int *)(iVar14 + 0x17e0) = iVar12;
      lVar9 = func_003637D0(0,iVar15);
      if (lVar9 == 0) {
        uVar3 = func_0036B4A0(0,iVar15);
        *(u32 *)(iVar14 + 0x1804) = uVar3;
        iVar12 = 0;
        *(u32 *)(iVar14 + 0x1804) = 0;
        do {
          uVar4 = func_0036B4D0(0,iVar15,iVar12);
          iVar12 = iVar12 + 1;
          *(u32 *)(iVar14 + 0x1804) = *(int *)(iVar14 + 0x1804) + (uVar4 & 0xff);
        } while (iVar12 < 9);
      }
      else {
        iVar12 = func_00362320(0);
        if (iVar15 == iVar12) {
          *(u32 *)(iVar14 + 0x1804) = (*(u32 *)(g_00669DEC + 0x0));
        }
        else {
          iVar12 = func_00362320(1);
          if (iVar15 == iVar12) {
            *(u32 *)(iVar14 + 0x1804) = (*(u32 *)(g_00669DEC + 0x48));
          }
          else {
            *(u32 *)(iVar14 + 0x1804) = (*(u32 *)(g_00669DEC + 0x0));
          }
        }
      }
      iVar12 = *(int *)(iVar14 + 0x1804);
      if (iVar12 < 1) {
        iVar13 = 0;
      }
      else {
        iVar13 = iVar12;
      }
      if (iVar13 < 0x13881) {
        if (iVar12 < 1) {
          iVar12 = 0;
        }
      }
      else {
        iVar12 = 80000;
      }
      *(int *)(iVar14 + 0x1804) = iVar12;
      uVar5 = func_0036B6C0(0,iVar15);
      uVar5 = uVar5 & 0xff;
      *(u32 *)(iVar14 + 0x182c) = uVar5;
      uVar4 = uVar5;
      if (uVar5 == 0) {
        uVar4 = 0;
      }
      if (uVar4 < 0x100) {
        if (uVar5 == 0) {
          uVar5 = 0;
        }
      }
      else {
        uVar5 = 0xff;
      }
      *(u32 *)(iVar14 + 0x182c) = uVar5;
      iVar13 = 0;
      iVar12 = iVar16;
      do {
        lVar9 = func_00362160(1,iVar13);
        if (lVar9 == 0x252) {
          *(u32 *)(iVar12 + 0x1858) = 0x252;
          *(u8 *)(iVar12 + 0x185c) = 0;
        }
        else {
          uVar3 = func_00362160(1,iVar13);
          *(u32 *)(iVar12 + 0x1858) = uVar3;
          uVar1 = func_0036B4D0(0,iVar15,iVar13);
          *(u8 *)(iVar12 + 0x185c) = uVar1;
        }
        iVar13 = iVar13 + 1;
        iVar12 = iVar12 + 8;
      } while (iVar13 < 9);
      if ((lVar8 < 8) && (lVar9 = func_0036B940(0,lVar8), lVar9 != 0)) {
        lVar9 = func_00362160(0,lVar8);
        if (lVar9 == 0x252) {
          *(u32 *)(iVar16 + 0x1898) = 0x252;
          *(u8 *)(iVar16 + 0x189c) = 0;
        }
        else {
          uVar3 = func_00362160(0,lVar8);
          *(u32 *)(iVar16 + 0x1898) = uVar3;
          uVar1 = func_0036B4D0(0,iVar15,8);
          *(u8 *)(iVar16 + 0x189c) = uVar1;
        }
      }
    }
    iVar15 = iVar15 + 1;
    iVar14 = iVar14 + 4;
    iVar16 = iVar16 + 0x48;
  } while (iVar15 < 8);
  *(u32 *)(iVar2 + 0x176c) = 0;
  iVar14 = 0;
  *(u32 *)(iVar2 + 0x1790) = 0;
  iVar16 = iVar2 + 0x240;
  *(u32 *)(iVar2 + 0x17b8) = 0;
  *(u32 *)(iVar2 + 0x17dc) = 0;
  *(u32 *)(iVar2 + 0x1800) = 0;
  *(u32 *)(iVar2 + 0x1824) = 0;
  *(u32 *)(iVar2 + 0x184c) = 0;
  do {
    *(u32 *)(iVar16 + 0x1858) = 0x252;
    iVar14 = iVar14 + 3;
    *(u8 *)(iVar16 + 0x185c) = 0;
    *(u32 *)(iVar16 + 0x1860) = 0x252;
    *(u8 *)(iVar16 + 0x1864) = 0;
    *(u32 *)(iVar16 + 0x1868) = 0x252;
    *(u8 *)(iVar16 + 0x186c) = 0;
    iVar16 = iVar16 + 0x18;
  } while (iVar14 < 9);
  if ((lVar7 < 8) && (lVar9 = func_0036B940(1,lVar7), lVar9 != 0)) {
    uVar3 = func_003AC510(1,lVar7);
    *(u32 *)(iVar2 + 0x176c) = uVar3;
    uVar3 = func_003AC650(1,lVar7);
    *(u32 *)(iVar2 + 0x1790) = uVar3;
    uVar3 = func_003AC970(1,lVar7);
    *(u32 *)(iVar2 + 0x17b8) = uVar3;
    iVar14 = func_003ACA10(1,lVar7);
    *(int *)(iVar2 + 0x17dc) = iVar14;
    iVar14 = (iVar14 * (*(int *)(iVar2 + 0x17b8) +
                       *(int *)(iVar2 + 0x1794) +
                       *(int *)(iVar2 + 0x176c) + *(int *)(iVar2 + 0x1790))) / 10;
    *(int *)(iVar2 + 0x1800) = iVar14;
    if (iVar14 < 1) {
      iVar16 = 0;
    }
    else {
      iVar16 = iVar14;
    }
    if (iVar16 < 0x10000) {
      if (iVar14 < 1) {
        iVar14 = 0;
      }
    }
    else {
      iVar14 = 0xffff;
    }
    *(int *)(iVar2 + 0x1800) = iVar14;
    uVar3 = func_0036B4A0(1,lVar7);
    *(u32 *)(iVar2 + 0x1824) = uVar3;
    iVar14 = 0;
    *(u32 *)(iVar2 + 0x1824) = 0;
    do {
      uVar4 = func_0036B4D0(1,lVar7,iVar14);
      iVar14 = iVar14 + 1;
      *(u32 *)(iVar2 + 0x1824) = *(int *)(iVar2 + 0x1824) + (uVar4 & 0xff);
    } while (iVar14 < 9);
    iVar14 = *(int *)(iVar2 + 0x1824);
    if (iVar14 < 1) {
      iVar16 = 0;
    }
    else {
      iVar16 = iVar14;
    }
    if (iVar16 < 0x13881) {
      if (iVar14 < 1) {
        iVar14 = 0;
      }
    }
    else {
      iVar14 = 80000;
    }
    *(int *)(iVar2 + 0x1824) = iVar14;
    uVar5 = func_0036B6C0(1,lVar7);
    uVar5 = uVar5 & 0xff;
    *(u32 *)(iVar2 + 0x184c) = uVar5;
    uVar4 = uVar5;
    if (uVar5 == 0) {
      uVar4 = 0;
    }
    if (uVar4 < 0x100) {
      if (uVar5 == 0) {
        uVar5 = 0;
      }
    }
    else {
      uVar5 = 0xff;
    }
    *(u32 *)(iVar2 + 0x184c) = uVar5;
    iVar14 = 0;
    iVar16 = iVar2 + 0x240;
    do {
      lVar9 = func_00362160(1,iVar14);
      if (lVar9 == 0x252) {
        *(u32 *)(iVar16 + 0x1858) = 0x252;
        *(u8 *)(iVar16 + 0x185c) = 0;
      }
      else {
        uVar3 = func_00362160(1,iVar14);
        *(u32 *)(iVar16 + 0x1858) = uVar3;
        uVar1 = func_0036B4D0(1,lVar7,iVar14);
        *(u8 *)(iVar16 + 0x185c) = uVar1;
      }
      iVar14 = iVar14 + 1;
      iVar16 = iVar16 + 8;
    } while (iVar14 < 9);
    if ((lVar8 < 8) && (lVar9 = func_0036B940(0,lVar8), lVar9 != 0)) {
      lVar9 = func_00362160(0,lVar8);
      if (lVar9 == 0x252) {
        *(u32 *)(iVar2 + 0x1ad8) = 0x252;
        *(u8 *)(iVar2 + 0x1adc) = 0;
      }
      else {
        uVar3 = func_00362160(0,lVar8);
        *(u32 *)(iVar2 + 0x1ad8) = uVar3;
        uVar1 = func_0036B4D0(1,lVar7,8);
        *(u8 *)(iVar2 + 0x1adc) = uVar1;
      }
    }
  }
  iVar14 = 0;
  if (0 < *(int *)(iVar2 + 0x1668)) {
    do {
      uVar10 = func_0035F780(iVar14);
      iVar16 = func_003AC380(uVar10,iVar14);
      if (0 < iVar16) {
        iVar16 = ((iVar16 + 9) / 10) * 10;
        iVar15 = iVar16;
        if (iVar16 < 1) {
          iVar15 = 0;
        }
        if (iVar15 < 0x1f5) {
          if (iVar16 < 1) {
            iVar16 = 0;
          }
        }
        else {
          iVar16 = 500;
        }
      }
      iVar15 = func_00362320(iVar14);
      iVar15 = func_003AC380(*(int *)(iVar2 + iVar15 * 4 + 0x174c) / 10,iVar14);
      if (0 < iVar15) {
        iVar15 = ((iVar15 + 9) / 10) * 10;
        iVar12 = iVar15;
        if (iVar15 < 1) {
          iVar12 = 0;
        }
        if (iVar12 < 0x1f5) {
          if (iVar15 < 1) {
            iVar15 = 0;
          }
        }
        else {
          iVar15 = 500;
        }
      }
      iVar12 = func_00362320(iVar14);
      iVar12 = func_003AC380(*(int *)(iVar2 + iVar12 * 4 + 6000) / 10,iVar14);
      if (0 < iVar12) {
        iVar12 = ((iVar12 + 9) / 10) * 10;
        iVar13 = iVar12;
        if (iVar12 < 1) {
          iVar13 = 0;
        }
        if (iVar13 < 0x1f5) {
          if (iVar12 < 1) {
            iVar12 = 0;
          }
        }
        else {
          iVar12 = 500;
        }
      }
      iVar13 = *(int *)(iVar2 + 0x1794);
      if (iVar13 < 0) {
        iVar13 = iVar13 + 1;
      }
      iVar13 = func_003AC380(iVar13 >> 1,iVar14);
      if (0 < iVar13) {
        iVar13 = ((iVar13 + 9) / 10) * 10;
        iVar6 = iVar13;
        if (iVar13 < 1) {
          iVar6 = 0;
        }
        if (iVar6 < 0x2ef) {
          if (iVar13 < 1) {
            iVar13 = 0;
          }
        }
        else {
          iVar13 = 0x2ee;
        }
      }
      iVar6 = func_00362320(iVar14);
      iVar6 = *(int *)(iVar2 + iVar6 * 4 + 0x1798);
      if (iVar6 < 0) {
        iVar6 = iVar6 + 1;
      }
      iVar6 = func_003AC380(iVar6 >> 1,iVar14);
      if (0 < iVar6) {
        iVar6 = ((iVar6 + 9) / 10) * 10;
        iVar11 = iVar6;
        if (iVar6 < 1) {
          iVar11 = 0;
        }
        if (iVar11 < 0x1f5) {
          if (iVar6 < 1) {
            iVar6 = 0;
          }
        }
        else {
          iVar6 = 500;
        }
      }
      *(int *)(iVar2 + iVar14 * 4 + 0x1850) = iVar6 + iVar13 + iVar12 + iVar16 + iVar15;
      iVar14 = iVar14 + 1;
    } while (iVar14 < *(int *)(iVar2 + 0x1668));
  }
  return;
}

/* 0x003AE2D0, 0x14C bytes. */
void func_003AE2D0(void)
{
    int iVar1;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    int * piVar2;
    u32 uVar3;
    int uVar4;
    int uVar5;

  
  iVar1 = func_0021A630();
  iVar9 = 0;
  if (0 < *(int *)(iVar1 + 0x1668)) {
    do {
      iVar7 = iVar1 + iVar9 * 4;
      *(u32 *)(iVar7 + 0x1ba0) = 0;
      uVar4 = func_00362320(iVar9);
      uVar4 = func_003620E0(0,uVar4);
      uVar5 = func_003294A0(iVar9);
      if (*(int *)(iVar7 + 0x1bf0) != 0) {
        piVar2 = (int *)func_0019FBC0(uVar5);
        iVar6 = *piVar2 + *(int *)(iVar7 + 0x1b08);
        iVar8 = iVar6;
        if (iVar6 < 1) {
          iVar8 = 0;
        }
        if (iVar8 < 100000) {
          if (iVar6 < 1) {
            iVar6 = 0;
          }
        }
        else {
          iVar6 = 99999;
        }
        iVar8 = iVar1 + iVar9 * 0x24;
        uVar3 = func_001A11F0(uVar4,uVar5,iVar6,*piVar2,iVar8 + 0x1b10);
        *(u32 *)(iVar7 + 0x1ba0) = uVar3;
        uVar4 = func_0019FBC0(uVar5);
        func_0011EB80(iVar8 + 7000,uVar4,0x24);
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < *(int *)(iVar1 + 0x1668));
  }
  return;
}

/* 0x003AE420, 0x360 bytes. */
void func_003AE420(void)
{
    int iVar1;
    int iVar3;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    int lVar4;
    u32 uVar2;
    int uVar5;

  
  iVar1 = func_0021A630();
  iVar7 = 0;
  do {
    if (*(int *)(iVar7 * 0x48 + 0x669e00) == 0) {
      *(u32 *)(iVar1 + iVar7 * 4 + 0x1b08) = 0;
    }
    else {
      iVar6 = *(int *)(iVar7 * 0x48 + 0x669dec) << 1;
      if (iVar6 < 1) {
        iVar8 = 0;
      }
      else {
        iVar8 = iVar6;
      }
      if (iVar8 < 10000) {
        if (iVar6 < 1) {
          iVar6 = 0;
        }
      }
      else {
        iVar6 = 9999;
      }
      iVar8 = 0;
      iVar9 = 0;
      do {
        lVar4 = func_00362160(1,iVar8);
        if (lVar4 != 0x252) {
          uVar5 = func_00362320(iVar7);
          uVar2 = func_0036B4D0(0,uVar5,iVar8);
          lVar4 = func_0021A640(iVar8);
          if (lVar4 < 3) {
            iVar3 = func_003625B0();
            iVar9 = iVar9 + (uVar2 & 0xff) * *(int *)((g_0041C0E0 + 0x0) + ((int)lVar4 * 5 + iVar3) * 4);
          }
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < 8);
      lVar4 = func_0036B8C0(0);
      if (lVar4 < 8) {
        uVar5 = func_00362320(iVar7);
        uVar2 = func_0036B4D0(0,uVar5,8);
        uVar5 = func_0036B8C0(0);
        lVar4 = func_0021A640(uVar5);
        if (lVar4 < 3) {
          iVar8 = func_003625B0();
          iVar9 = iVar9 + (uVar2 & 0xff) * *(int *)((g_0041C0E0 + 0x0) + ((int)lVar4 * 5 + iVar8) * 4);
        }
      }
      uVar5 = func_00362320(iVar7);
      uVar2 = func_0036B6C0(0,uVar5);
      iVar8 = func_003625B0();
      if ((int)((uVar2 & 0xff) * *(int *)((g_0041C0E0 + 0x40) + iVar8 * 4)) < 1) {
        iVar8 = 0;
      }
      else {
        uVar5 = func_00362320(iVar7);
        uVar2 = func_0036B6C0(0,uVar5);
        iVar8 = func_003625B0();
        iVar8 = (uVar2 & 0xff) * *(int *)((g_0041C0E0 + 0x40) + iVar8 * 4);
      }
      if (iVar8 < 10000) {
        uVar5 = func_00362320(iVar7);
        uVar2 = func_0036B6C0(0,uVar5);
        iVar8 = func_003625B0();
        if ((int)((uVar2 & 0xff) * *(int *)((g_0041C0E0 + 0x40) + iVar8 * 4)) < 1) {
          iVar8 = 0;
        }
        else {
          uVar5 = func_00362320(iVar7);
          uVar2 = func_0036B6C0(0,uVar5);
          iVar8 = func_003625B0();
          iVar8 = (uVar2 & 0xff) * *(int *)((g_0041C0E0 + 0x40) + iVar8 * 4);
        }
      }
      else {
        iVar8 = 9999;
      }
      iVar6 = (iVar8 + iVar6 + iVar9) * 2;
      if (iVar6 < 1) {
        iVar8 = 0;
      }
      else {
        iVar8 = iVar6;
      }
      if (iVar8 < 10000) {
        if (iVar6 < 1) {
          iVar6 = 0;
        }
      }
      else {
        iVar6 = 9999;
      }
      *(int *)(iVar1 + iVar7 * 4 + 0x1b08) = iVar6;
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 2);
  return;
}

/* 0x003AE790, 0x90 bytes. */
int func_003AE790(void)
{
    int bVar2;
    int iVar3;
    int lVar5;
    u32 uVar1;
    int uVar4;

  
  uVar4 = func_00327D50();
  uVar1 = *(u32 *)((*(u32 *)(g_007BAE7C + 0x0)) * 4 + 0x7bae94);
  iVar3 = func_002F9190(uVar4);
  if (iVar3 < (*(u32 *)(g_007BAE7C + 0x10))) {
    bVar2 = false;
  }
  else {
    uVar4 = func_002F4080(uVar1);
    lVar5 = func_002FB3B0(uVar4);
    if (lVar5 < 1) {
      bVar2 = true;
    }
    else {
      lVar5 = func_002F3DC0(uVar1);
      bVar2 = lVar5 != 3;
    }
  }
  return bVar2;
}

/* 0x003AE840, 0x94 bytes. */
int func_003AE840(int param_1)
{
    int bVar1;
    int iVar3;
    int lVar2;

  
  iVar3 = 0;
  while( true ) {
    lVar2 = func_003620E0(1,iVar3);
    bVar1 = false;
    if ((-1 < lVar2) && (lVar2 < 0x19f)) {
      bVar1 = true;
    }
    if (((bVar1) && (lVar2 == param_1)) && (lVar2 = func_0036B940(1,iVar3), lVar2 != 0)) break;
    iVar3 = iVar3 + 1;
    if (7 < iVar3) {
      return 0;
    }
  }
  return 1;
}

/* 0x003AE9F0, 0xF0 bytes. */
void func_003AE9F0(int param_1, u32 *param_2, int param_3)
{
    int iVar2;
    int iVar3;
    int uVar1;

  
  iVar3 = 0;
  (*(u32 *)(g_007BAE70 + 0x4)) = 0;
  (*(u32 *)(g_007BAE70 + 0xC)) = 0;
  (*(u32 *)(g_007BAE70 + 0x8)) = 4;
  iVar2 = (int)g_007BAE70;
  (*(u32 *)(g_007BAE70 + 0x0)) = param_1;
  (*(u32 *)(g_007BAE70 + 0x10)) = param_3;
  do {
    *(u32 *)(iVar2 + 0x24) = 0xffffffff;
    if (iVar3 < param_3) {
      *(u32 *)(iVar2 + 0x24) = *param_2;
      param_2 = param_2 + 1;
    }
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 4;
  } while (iVar3 < 6);
  (*(u32 *)(g_007BAE70 + 0x1C)) = 0;
  (*(u32 *)(g_007BAE70 + 0x14)) = 0;
  uVar1 = func_00327D50();
  iVar2 = func_002FB430(uVar1);
  (*(u32 *)(g_007BAE70 + 0x18)) = func_00327E50();
  (*(u32 *)(g_007BAE70 + 0x18)) = (*(u32 *)(g_007BAE70 + 0x18)) - iVar2;
  iVar3 = (int)g_007BAE70;
  iVar2 = 0;
  do {
    *(u32 *)(iVar3 + 0x3c) = 0xffffffff;
    iVar2 = iVar2 + 3;
    *(u32 *)(iVar3 + 0x40) = 0xffffffff;
    *(u32 *)(iVar3 + 0x44) = 0xffffffff;
    iVar3 = iVar3 + 0xc;
  } while (iVar2 < 9);
  (*(u32 *)(g_007BAE70 + 0x20)) = 0;
  func_00376100(4,0x28);
  return;
}

/* 0x003AF2A0, 0xF4 bytes. */
int func_003AF2A0(int param_1)
{
    int iVar1;
    int iVar3;
    int iVar6;
    int lVar5;
    int * piVar2;
    int uVar4;

  
  piVar2 = (int *)func_002F7B10();
  uVar4 = func_002F4080(param_1);
  iVar3 = func_002F7D90(0,0x2f8160,uVar4,0xffffffffffffffff,0,0);
  iVar6 = 0;
  if (0 < iVar3) {
    do {
      iVar1 = *piVar2;
      if (param_1 != iVar1) {
        lVar5 = func_002F77A0(param_1,iVar1);
        if (lVar5 != 0) {
          return 0;
        }
        lVar5 = func_002F78C0(param_1,iVar1);
        if (lVar5 != 0) {
          return 0;
        }
        lVar5 = func_002F7900(param_1,iVar1);
        if (lVar5 != 0) {
          return 0;
        }
      }
      iVar6 = iVar6 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar6 < iVar3);
  }
  return 1;
}

/* 0x003AF3A0, 0x160 bytes. */
void func_003AF3A0(int param_1, int param_2)
{
    int lVar1;
    int uVar2;
    int uVar3;

  
  if (param_1 == 2) {
    uVar2 = func_00390760(0xbf);
    uVar3 = func_002F2890(param_2);
    func_001204B0(g_007B4E60,uVar2,uVar3);
    func_00375140(0x100,200,1,g_007B4E60);
    func_003AE8E0(3);
  }
  else if (param_1 == 1) {
    func_003AE8E0(4);
  }
  else if (param_1 == 0) {
    lVar1 = func_003AF2A0(param_2);
    if (lVar1 == 0) {
      uVar2 = func_00390760(0xbd);
      uVar3 = func_002F2890(param_2);
      func_001204B0(g_007B4E60,uVar2,uVar3);
      func_00374EE0(g_007B4E60);
      func_003AE8E0(3);
    }
    else if ((*(u32 *)(g_007BAE88 + 0x0)) < 1) {
      uVar2 = func_00390760(0xbe);
      uVar3 = func_002F2890(param_2);
      func_001204B0(g_007B4E60,uVar2,uVar3);
      func_00375140(0x100,200,1,g_007B4E60);
      func_003AE8E0(3);
    }
    else {
      func_003AE8E0(4);
    }
  }
  return;
}

/* 0x003AF500, 0xB0 bytes. */
void func_003AF500(void)
{
    int lVar2;
    int lVar3;
    u32 uVar1;

  
  func_00327D50();
  uVar1 = *(u32 *)((*(u32 *)(g_007BAE78 + 0x4)) * 4 + 0x7bae94);
  func_00329860();
  lVar2 = func_003DC2D0(9);
  if (lVar2 == 0) {
    func_003890B0(1);
    lVar2 = func_00389050();
    func_003890B0(0);
    lVar3 = func_00389090();
    if (lVar2 == 1) {
      (*(u32 *)(g_007BAE78 + 0x0)) = (u32)lVar3;
      if (lVar3 == 3) {
        func_003AE8E0(7);
      }
      else {
        func_003AF3A0(lVar3,uVar1);
      }
    }
  }
  return;
}

/* 0x003AF9F0, 0xEC bytes. */
int func_003AF9F0(void)
{
    int uVar1;

  
  uVar1 = 2;
  switch((*(u32 *)(g_007BAE74 + 0x0))) {
  case 0:
    uVar1 = func_003AEAE0();
    break;
  case 1:
    uVar1 = func_003AEB80();
    break;
  case 2:
    func_003AF500();
    return 2;
  case 3:
    uVar1 = func_003AF5B0();
    break;
  case 4:
    func_003AF670();
    break;
  case 5:
    func_003AF8D0();
    break;
  case 6:
    func_003F1070(3);
    func_003AF920();
    break;
  case 7:
    func_003AF960();
    break;
  case 8:
    func_003762C0();
    func_003A9010(1);
    uVar1 = 1;
  }
  return uVar1;
}

/* 0x003BB060, 0x4B8 bytes. */
int func_003BB060(int param_1)
{
    int iVar4;
    u32 * puVar5;
    int uVar1;
    u32 uVar2;
    u32 uVar3;
    int uVar6;
    int uVar7;
    int uVar8;
    int uVar9;

  
  iVar4 = func_00329850();
  puVar5 = (u32 *)(iVar4 + (int)param_1 * 0x20);
  uVar1 = *(u8 *)((int)puVar5 + 7);
  uVar6 = puVar5[4];
  uVar2 = puVar5[5];
  uVar3 = *puVar5;
  if (param_1 < 0x2d) {
    switch(param_1) {
    case 0:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_003BAF40(uVar6,uVar1);
      uVar7 = func_0030ABF0(uVar2);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9,uVar7);
      break;
    case 1:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_003BAF40(uVar2,uVar1);
      uVar7 = func_0030ABF0(uVar6);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9,uVar7);
      break;
    case 3:
      uVar8 = func_003726E0(param_1);
      func_001204B0(g_007BC120,uVar8,uVar3);
      break;
    case 4:
    case 5:
    case 6:
    case 7:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_003BAF40(uVar6,uVar1);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9);
      break;
    case 8:
      uVar8 = func_002F2BB0(uVar6);
      func_001204B0(g_007BC0F0,uVar8);
      uVar8 = func_002F2890(uVar6);
      func_001204B0(g_007BC0C0,uVar8);
      uVar8 = func_003726E0(param_1);
      func_001204B0(g_007BC120,uVar8,uVar3,g_007BC0F0,g_007BC0C0);
      break;
    case 9:
    case 10:
    case 0xb:
    case 0xc:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_003BAF40(uVar6,uVar1);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9);
      break;
    case 0xd:
    case 0xe:
      uVar8 = func_003BAF40(uVar6,uVar1);
      func_001204B0(g_007BC0F0,uVar8);
      uVar8 = func_003BAF40(uVar2,uVar1);
      func_001204B0(g_007BC0C0,uVar8);
      uVar8 = func_003726E0(param_1);
      func_001204B0(g_007BC120,uVar8,uVar3,g_007BC0F0,g_007BC0C0);
      break;
    case 0xf:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_003BAF40(uVar6,uVar1);
      uVar7 = func_00372680(uVar2);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9,uVar7);
      break;
    case 0x10:
    case 0x11:
      uVar8 = func_003726E0(param_1);
      func_001204B0(g_007BC120,uVar8,uVar3);
      break;
    case 0x12:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_003BAF40(uVar6,uVar1);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9);
      break;
    case 0x13:
      uVar8 = func_003726E0(param_1);
      func_001204B0(g_007BC120,uVar8,uVar3);
      break;
    case 0x14:
    case 0x15:
    case 0x16:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_003BAF40(uVar6,uVar1);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9);
      break;
    case 0x17:
    case 0x18:
      uVar8 = func_003726E0(param_1);
      func_001204B0(g_007BC120,uVar8,uVar3);
      break;
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_00372710(uVar2);
      uVar7 = func_003726B0(uVar6);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9,uVar7);
      break;
    case 0x1e:
    case 0x1f:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_0030ABF0(uVar6);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9);
      break;
    case 0x20:
      uVar8 = func_003726E0(param_1);
      func_001204B0(g_007BC120,uVar8,uVar3);
      break;
    case 0x21:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_003BAF40(uVar6,uVar1);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9);
      break;
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
      uVar8 = func_003726E0(param_1);
      uVar9 = func_003BAF40(uVar6,uVar1);
      func_001204B0(g_007BC120,uVar8,uVar3,uVar9);
    }
    uVar6 = (int)g_007BC120;
  }
  else {
    uVar6 = 0;
  }
  return uVar6;
}

/* 0x003BFC30, 0xB4 bytes. */
void func_003BFC30(u32 *param_1, int param_2, int param_3)
{
    int iVar1;
    u32 * puVar2;
    u32 * puVar3;

  
  (*(u32 *)(g_007BEAD0 + 0x8)) = (u32)(param_3 != 0);
  (*(u32 *)(g_007BEAD0 + 0x0)) = 0;
  puVar3 = (u32 *)0x7beadc;
  iVar1 = 0x11;
  puVar2 = param_1;
  (*(u32 *)(g_007BEAD0 + 0x4)) = param_2;
  do {
    iVar1 = iVar1 + -1;
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  } while (0 < iVar1);
  puVar3 = param_1 + 0x11;
  puVar2 = (u32 *)0x7beb20;
  iVar1 = 0x11;
  do {
    iVar1 = iVar1 + -1;
    *puVar2 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar2 = puVar2 + 1;
  } while (0 < iVar1);
  param_1 = param_1 + 0x22;
  puVar2 = (u32 *)0x7beb64;
  iVar1 = 0x11;
  do {
    iVar1 = iVar1 + -1;
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  } while (0 < iVar1);
  return;
}

/* 0x003BFCF0, 0x8C bytes. */
void func_003BFCF0(u32 *param_1)
{
    int iVar1;
    u32 * puVar2;
    u32 * puVar3;

  
  iVar1 = 0x11;
  puVar2 = (u32 *)0x7beadc;
  puVar3 = param_1;
  do {
    iVar1 = iVar1 + -1;
    *puVar2 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar2 = puVar2 + 1;
  } while (0 < iVar1);
  puVar2 = param_1 + 0x11;
  puVar3 = (u32 *)0x7beb20;
  iVar1 = 0x11;
  do {
    iVar1 = iVar1 + -1;
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  } while (0 < iVar1);
  param_1 = param_1 + 0x22;
  puVar3 = (u32 *)0x7beb64;
  iVar1 = 0x11;
  do {
    iVar1 = iVar1 + -1;
    *puVar3 = *param_1;
    param_1 = param_1 + 1;
    puVar3 = puVar3 + 1;
  } while (0 < iVar1);
  return;
}

/* 0x003C5760, 0x14C bytes. */
int func_003C5760(void)
{
    int lVar2;
    u32 uVar1;
    int uVar3;

  
  lVar2 = func_00329540(0x92);
  if (lVar2 == 0) {
    uVar3 = func_00327820();
    lVar2 = func_0032EC50(uVar3,1,0x16,1);
    if (lVar2 == 0) {
      uVar3 = func_00327820();
      lVar2 = func_0032EB40(uVar3,1,1);
      if (lVar2 == 0) {
        uVar3 = func_00327820();
        lVar2 = func_0032EB40(uVar3,0x16,1);
        if (lVar2 == 0) {
          return 0;
        }
      }
      lVar2 = func_0032E950();
      if ((lVar2 == 1) || (lVar2 = func_0032E950(), lVar2 == 0x16)) {
        lVar2 = func_0032E950();
        if (lVar2 == 1) {
          uVar3 = func_00327820();
          lVar2 = func_0032EB40(uVar3,0x16,1);
          if (lVar2 == 0) {
            return 0;
          }
        }
        lVar2 = func_0032E950();
        if (lVar2 == 0x16) {
          uVar3 = func_00327820();
          lVar2 = func_0032EB40(uVar3,1,1);
          if (lVar2 == 0) {
            return 0;
          }
        }
        uVar1 = 1;
      }
      else {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x003C7550, 0x164 bytes. */
int func_003C7550(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar2 = func_00329540(0xbe);
  if (lVar2 == 0) {
    lVar2 = func_003C23A0();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      lVar2 = func_002F4080(4);
      lVar3 = func_002F4080(0x1b);
      if (lVar2 == lVar3) {
        bVar1 = false;
      }
      else {
        lVar2 = func_003C2AE0(4,0x1b);
        if (lVar2 == 0) {
          bVar1 = false;
        }
        else {
          lVar2 = func_003C1850();
          if ((lVar2 == 0) && (lVar2 = func_0030D150(), lVar2 != 6)) {
            bVar1 = false;
          }
          else {
            lVar2 = func_00327C00();
            if ((lVar2 == 2) && (lVar2 = func_0030D150(), lVar2 != 1)) {
              bVar1 = false;
            }
            else {
              lVar2 = func_00327C00();
              if (lVar2 == 0) {
                bVar1 = false;
              }
              else {
                lVar2 = func_00327C00();
                if (lVar2 == 1) {
                  bVar1 = false;
                }
                else {
                  lVar2 = func_00327C00();
                  if (lVar2 == 3) {
                    bVar1 = false;
                  }
                  else {
                    lVar2 = func_00327C00();
                    if (lVar2 == 4) {
                      bVar1 = false;
                    }
                    else {
                      lVar2 = func_00327C00();
                      bVar1 = lVar2 != 5;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CE430, 0xF8 bytes. */
int func_003CE430(void)
{
    int bVar1;
    int lVar2;
    int lVar3;
    int uVar4;
    int uVar5;

  
  lVar2 = func_00329540(0x15c);
  if (lVar2 == 0) {
    lVar2 = func_00337A10(0x176);
    lVar3 = func_00327820();
    if (lVar2 == lVar3) {
      uVar4 = func_00327820();
      uVar5 = func_00337A10(0x173);
      lVar2 = func_0032EB40(uVar4,uVar5,0);
      if (lVar2 == 0) {
        bVar1 = false;
      }
      else {
        uVar4 = func_00327820();
        uVar5 = func_00337A10(0x174);
        lVar2 = func_0032EB40(uVar4,uVar5,0);
        if (lVar2 == 0) {
          bVar1 = false;
        }
        else {
          lVar2 = func_0032EE10(0x10);
          if (lVar2 == 0) {
            bVar1 = false;
          }
          else {
            uVar4 = func_00327D50();
            uVar5 = func_002F4080(0x10);
            lVar2 = func_002FAFA0(uVar4,uVar5);
            bVar1 = lVar2 != 0;
          }
        }
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CE5F0, 0x80 bytes. */
int func_003CE5F0(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar2 = func_00329540(0x15e);
  if (lVar2 == 0) {
    lVar2 = func_003C23A0();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      lVar2 = func_002F4080(0x19);
      lVar3 = func_002F4080(2);
      if (lVar2 == lVar3) {
        bVar1 = false;
      }
      else {
        lVar2 = func_003C2AE0(0x19,2);
        bVar1 = lVar2 != 0;
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CE670, 0x80 bytes. */
int func_003CE670(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar2 = func_00329540(0x15f);
  if (lVar2 == 0) {
    lVar2 = func_003C23A0();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      lVar2 = func_002F4080(0x19);
      lVar3 = func_002F4080(3);
      if (lVar2 == lVar3) {
        bVar1 = false;
      }
      else {
        lVar2 = func_003C2AE0(0x19,3);
        bVar1 = lVar2 != 0;
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CE6F0, 0x80 bytes. */
int func_003CE6F0(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar2 = func_00329540(0x160);
  if (lVar2 == 0) {
    lVar2 = func_003C23A0();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      lVar2 = func_002F4080(0x19);
      lVar3 = func_002F4080(4);
      if (lVar2 == lVar3) {
        bVar1 = false;
      }
      else {
        lVar2 = func_003C2AE0(0x19,4);
        bVar1 = lVar2 != 0;
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CE770, 0x80 bytes. */
int func_003CE770(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar2 = func_00329540(0x161);
  if (lVar2 == 0) {
    lVar2 = func_003C23A0();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      lVar2 = func_002F4080(0x19);
      lVar3 = func_002F4080(7);
      if (lVar2 == lVar3) {
        bVar1 = false;
      }
      else {
        lVar2 = func_003C2AE0(0x19,7);
        bVar1 = lVar2 != 0;
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CE7F0, 0x80 bytes. */
int func_003CE7F0(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar2 = func_00329540(0x162);
  if (lVar2 == 0) {
    lVar2 = func_003C23A0();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      lVar2 = func_002F4080(0x19);
      lVar3 = func_002F4080(0xc);
      if (lVar2 == lVar3) {
        bVar1 = false;
      }
      else {
        lVar2 = func_003C2AE0(0x19,0xc);
        bVar1 = lVar2 != 0;
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CE870, 0x80 bytes. */
int func_003CE870(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar2 = func_00329540(0x163);
  if (lVar2 == 0) {
    lVar2 = func_003C23A0();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      lVar2 = func_002F4080(0x19);
      lVar3 = func_002F4080(0xe);
      if (lVar2 == lVar3) {
        bVar1 = false;
      }
      else {
        lVar2 = func_003C2AE0(0x19,0xe);
        bVar1 = lVar2 != 0;
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CE8F0, 0x80 bytes. */
int func_003CE8F0(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar2 = func_00329540(0x164);
  if (lVar2 == 0) {
    lVar2 = func_003C23A0();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      lVar2 = func_002F4080(0x19);
      lVar3 = func_002F4080(0x15);
      if (lVar2 == lVar3) {
        bVar1 = false;
      }
      else {
        lVar2 = func_003C2AE0(0x19,0x15);
        bVar1 = lVar2 != 0;
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CE970, 0x80 bytes. */
int func_003CE970(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar2 = func_00329540(0x165);
  if (lVar2 == 0) {
    lVar2 = func_003C23A0();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      lVar2 = func_002F4080(0x19);
      lVar3 = func_002F4080(0x1a);
      if (lVar2 == lVar3) {
        bVar1 = false;
      }
      else {
        lVar2 = func_003C2AE0(0x19,0x1a);
        bVar1 = lVar2 != 0;
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CE9F0, 0xB4 bytes. */
int func_003CE9F0(void)
{
    int bVar1;
    int lVar2;
    int uVar3;
    int uVar4;

  
  lVar2 = func_00329540(0x166);
  if (lVar2 == 0) {
    uVar3 = func_00337A10(0xab);
    lVar2 = func_0032EE10(uVar3);
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      uVar3 = func_00327820();
      uVar4 = func_00337A10(0xab);
      lVar2 = func_0032EC50(uVar3,uVar4,0x19,1);
      if (lVar2 == 0) {
        bVar1 = false;
      }
      else {
        uVar3 = func_00337A10(0xab);
        lVar2 = func_003C27A0(0,uVar3,0x19,0x19f,0x19f);
        bVar1 = lVar2 == 2;
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CEAB0, 0x80 bytes. */
int func_003CEAB0(void)
{
    int bVar1;
    int lVar2;
    int lVar3;

  
  lVar2 = func_00329540(0x167);
  if (lVar2 == 0) {
    lVar2 = func_003C23A0();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      lVar2 = func_002F4080(0x1a);
      lVar3 = func_002F4080(4);
      if (lVar2 == lVar3) {
        bVar1 = false;
      }
      else {
        lVar2 = func_003C2AE0(0x1a,4);
        bVar1 = lVar2 != 0;
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CEBF0, 0xA8 bytes. */
int func_003CEBF0(void)
{
    int bVar1;
    int lVar2;
    int uVar3;

  
  lVar2 = func_00329540(0x169);
  if (lVar2 == 0) {
    uVar3 = func_00327820();
    lVar2 = func_0032EB40(uVar3,0x1b,1);
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else {
      uVar3 = func_00327820();
      lVar2 = func_0032EB40(uVar3,3,0);
      if (lVar2 == 0) {
        bVar1 = false;
      }
      else {
        lVar2 = func_002F33F0(0x1b);
        if (lVar2 < 10) {
          bVar1 = false;
        }
        else {
          lVar2 = func_002F33F0(3);
          bVar1 = 9 < lVar2;
        }
      }
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CECA0, 0x128 bytes. */
int func_003CECA0(void)
{
    int lVar2;
    u32 uVar1;
    int uVar3;

  
  lVar2 = func_00329540(0x16a);
  if (lVar2 == 0) {
    uVar3 = func_00327820();
    lVar2 = func_0032EB40(uVar3,0x1b,1);
    if (lVar2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar3 = func_00327820();
      lVar2 = func_0032EB40(uVar3,0xd,0);
      if (lVar2 == 0) {
        uVar1 = 0;
      }
      else {
        uVar3 = func_00327820();
        lVar2 = func_0032EB40(uVar3,5,0);
        if (lVar2 == 0) {
          uVar1 = 0;
        }
        else {
          uVar3 = func_00327820();
          lVar2 = func_0032EB40(uVar3,0x12,1);
          if (lVar2 == 0) {
            lVar2 = func_003C1120(0x12);
            if ((lVar2 == 0) || (lVar2 = func_002F3BB0(0x12), lVar2 != 2)) {
              lVar2 = func_00328270();
              if ((lVar2 == 0) || (lVar2 = func_00328270(), lVar2 == 2)) {
                uVar1 = 1;
              }
              else {
                uVar1 = 0;
              }
            }
            else {
              uVar1 = 0;
            }
          }
          else {
            uVar1 = 0;
          }
        }
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x003CF030, 0x70 bytes. */
int func_003CF030(void)
{
    int bVar1;
    int lVar2;
    int uVar3;

  
  lVar2 = func_00329540(0x16d);
  if (lVar2 == 0) {
    lVar2 = func_003C1850();
    if (lVar2 == 0) {
      bVar1 = false;
    }
    else if (g_0045D824 == 0) {
      bVar1 = false;
    }
    else {
      uVar3 = func_00327D50();
      lVar2 = func_002FB3B0(uVar3);
      bVar1 = 2 < lVar2;
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CF140, 0x2F0 bytes. */
int func_003CF140(void)
{
    int lVar3;
    int lVar4;
    u32 uVar1;
    int uVar2;

  
  uVar2 = func_00327820();
  lVar3 = func_002F3BB0(1);
  lVar4 = func_00329540(0x178);
  if (lVar4 == 0) {
    lVar4 = func_00329540(0x1a0);
    if (lVar4 == 0) {
      if (lVar3 == 0) {
        uVar1 = 0;
      }
      else if (lVar3 == 1) {
        uVar1 = 0;
      }
      else {
        lVar3 = func_003C2320();
        if (lVar3 == 0) {
          uVar1 = 0;
        }
        else {
          lVar3 = func_0032EB40(uVar2,0,0);
          if (lVar3 == 0) {
            uVar1 = 0;
          }
          else {
            lVar3 = func_0032EB40(uVar2,0x11,0);
            if (lVar3 == 0) {
              uVar1 = 0;
            }
            else {
              lVar3 = func_0032EB40(uVar2,0x16,0);
              if (lVar3 == 0) {
                uVar1 = 0;
              }
              else {
                lVar3 = func_003C27A0(0,0,0x11,0x16,0x19f);
                if (lVar3 == 3) {
                  lVar3 = func_003620E0(0,0);
                  if (lVar3 == 0) {
                    lVar3 = func_003C1850();
                    if ((lVar3 == 0) && (lVar3 = func_0030D150(), lVar3 == 8)) {
                      uVar1 = 0;
                    }
                    else {
                      lVar3 = func_003C1850();
                      if ((lVar3 == 0) && (lVar3 = func_0030D150(), lVar3 == 0xc)) {
                        uVar1 = 0;
                      }
                      else {
                        lVar3 = func_003C1850();
                        if ((lVar3 == 0) && (lVar3 = func_0030D150(), lVar3 == 0xd)) {
                          uVar1 = 0;
                        }
                        else {
                          lVar3 = func_00327C00();
                          if ((lVar3 == 1) && (lVar3 = func_0030D150(), lVar3 == 3)) {
                            uVar1 = 0;
                          }
                          else {
                            lVar3 = func_00327C00();
                            if ((lVar3 == 2) && (lVar3 = func_0030D150(), lVar3 == 3)) {
                              uVar1 = 0;
                            }
                            else {
                              lVar3 = func_00327C00();
                              if ((lVar3 == 2) && (lVar3 = func_0030D150(), lVar3 == 7)) {
                                uVar1 = 0;
                              }
                              else {
                                lVar3 = func_00327C00();
                                if ((lVar3 == 3) && (lVar3 = func_0030D150(), lVar3 == 0)) {
                                  uVar1 = 0;
                                }
                                else {
                                  lVar3 = func_00327C00();
                                  if ((lVar3 == 3) && (lVar3 = func_0030D150(), lVar3 == 1)) {
                                    uVar1 = 0;
                                  }
                                  else {
                                    lVar3 = func_00327C00();
                                    if ((lVar3 == 3) && (lVar3 = func_0030D150(), lVar3 == 4)) {
                                      uVar1 = 0;
                                    }
                                    else {
                                      uVar1 = 1;
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                  else {
                    uVar1 = 0;
                  }
                }
                else {
                  uVar1 = 0;
                }
              }
            }
          }
        }
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x003CF6D0, 0xC8 bytes. */
int func_003CF6D0(void)
{
    int bVar1;
    int lVar2;

  
  lVar2 = func_003C1850();
  if (lVar2 == 0) {
    lVar2 = func_00329540(0x196);
    if (lVar2 == 0) {
      lVar2 = func_0032EE10(2);
      if (lVar2 == 0) {
        lVar2 = func_003C2320();
        if (lVar2 == 0) {
          bVar1 = false;
        }
        else {
          lVar2 = func_00327820();
          if (lVar2 == 0xd) {
            lVar2 = func_003C3060(0x10);
            if (lVar2 == 0) {
              bVar1 = false;
            }
            else {
              lVar2 = func_003C27A0(0,0xd,0x11,0x19f,0x19f);
              bVar1 = lVar2 == 2;
            }
          }
          else {
            bVar1 = false;
          }
        }
      }
      else {
        bVar1 = false;
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003CF7F0, 0x120 bytes. */
int func_003CF7F0(void)
{
    int lVar2;
    u32 uVar1;
    int uVar3;

  
  lVar2 = func_00329540(0x19c);
  if (lVar2 == 0) {
    lVar2 = func_003C2570();
    if (lVar2 == 0) {
      uVar1 = 0;
    }
    else {
      uVar3 = func_00327820();
      lVar2 = func_0032EC50(uVar3,0x10,0xe,1);
      if (lVar2 == 0) {
        uVar1 = 0;
      }
      else {
        lVar2 = func_003C27A0(0,0x10,0xe,0x19f,0x19f);
        if (lVar2 == 2) {
          lVar2 = func_00327820();
          if (lVar2 == 0x10) {
            lVar2 = func_0036B260();
            if (lVar2 == 0) {
              lVar2 = func_003C2C60(0x10,0xe,1);
              if (((lVar2 == 0) && (lVar2 = func_003C2C60(0x10,0xe,0), lVar2 == 0)) &&
                 (lVar2 = func_003C2DD0(0x10,0xe), lVar2 == 0)) {
                uVar1 = 0;
              }
              else {
                uVar1 = 1;
              }
            }
            else {
              uVar1 = 0;
            }
          }
          else {
            uVar1 = 0;
          }
        }
        else {
          uVar1 = 0;
        }
      }
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x003CF940, 0x39C bytes. */
int func_003CF940(void)
{
    int bVar1;
    int lVar5;
    int lVar6;
    u32 uVar2;
    int uVar3;
    int uVar4;

  
  uVar3 = func_00327D50();
  uVar4 = func_00327820();
  lVar5 = func_002F4080(9);
  bVar1 = false;
  if (-1 < lVar5) {
    lVar6 = func_0030AB90();
    bVar1 = lVar5 < lVar6;
  }
  if (bVar1) {
    lVar6 = func_00329540(0x1a0);
    if (lVar6 == 0) {
      lVar6 = func_00329540(0x178);
      if (lVar6 == 0) {
        lVar6 = func_0032EB40(uVar4,9,0);
        if ((lVar6 == 0) &&
           ((lVar6 = func_0032EE10(9), lVar6 == 0 || (lVar5 = func_002F9C90(uVar3,lVar5), lVar5 != 3))
           )) {
          uVar2 = 0;
        }
        else {
          lVar5 = func_003C27A0(0,9,0x19f,0x19f,0x19f);
          if (lVar5 == 1) {
            uVar2 = 0;
          }
          else {
            lVar5 = func_003620E0(0,6);
            if (lVar5 == 9) {
              uVar2 = 0;
            }
            else {
              lVar5 = func_003C2320();
              if (lVar5 == 0) {
                uVar2 = 0;
              }
              else {
                lVar5 = func_0032EB40(uVar4,0,0);
                if (lVar5 == 0) {
                  uVar2 = 0;
                }
                else {
                  lVar5 = func_0032EB40(uVar4,0x11,0);
                  if (lVar5 == 0) {
                    uVar2 = 0;
                  }
                  else {
                    lVar5 = func_0032EB40(uVar4,0x16,0);
                    if (lVar5 == 0) {
                      uVar2 = 0;
                    }
                    else {
                      lVar5 = func_003C27A0(0,0,0x11,0x16,0x19f);
                      if (lVar5 == 3) {
                        lVar5 = func_003620E0(0,0);
                        if (lVar5 == 0) {
                          uVar2 = 0;
                        }
                        else {
                          lVar5 = func_003C1850();
                          if ((lVar5 == 0) && (lVar5 = func_0030D150(), lVar5 == 8)) {
                            uVar2 = 0;
                          }
                          else {
                            lVar5 = func_003C1850();
                            if ((lVar5 == 0) && (lVar5 = func_0030D150(), lVar5 == 0xc)) {
                              uVar2 = 0;
                            }
                            else {
                              lVar5 = func_003C1850();
                              if ((lVar5 == 0) && (lVar5 = func_0030D150(), lVar5 == 0xd)) {
                                uVar2 = 0;
                              }
                              else {
                                lVar5 = func_00327C00();
                                if ((lVar5 == 1) && (lVar5 = func_0030D150(), lVar5 == 3)) {
                                  uVar2 = 0;
                                }
                                else {
                                  lVar5 = func_00327C00();
                                  if ((lVar5 == 2) && (lVar5 = func_0030D150(), lVar5 == 3)) {
                                    uVar2 = 0;
                                  }
                                  else {
                                    lVar5 = func_00327C00();
                                    if ((lVar5 == 2) && (lVar5 = func_0030D150(), lVar5 == 7)) {
                                      uVar2 = 0;
                                    }
                                    else {
                                      lVar5 = func_00327C00();
                                      if ((lVar5 == 3) && (lVar5 = func_0030D150(), lVar5 == 0)) {
                                        uVar2 = 0;
                                      }
                                      else {
                                        lVar5 = func_00327C00();
                                        if ((lVar5 == 3) && (lVar5 = func_0030D150(), lVar5 == 1)) {
                                          uVar2 = 0;
                                        }
                                        else {
                                          lVar5 = func_00327C00();
                                          if ((lVar5 == 3) && (lVar5 = func_0030D150(), lVar5 == 4))
                                          {
                                            uVar2 = 0;
                                          }
                                          else {
                                            uVar2 = 1;
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                      else {
                        uVar2 = 0;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      else {
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* 0x003CFDA0, 0x14C bytes. */
int func_003CFDA0(void)
{
    int lVar3;
    u32 uVar1;
    int uVar2;
    int uVar4;

  
  uVar2 = func_00337A10(0x157);
  lVar3 = func_003C1850();
  if (lVar3 == 0) {
    lVar3 = func_00329540(0x1ad);
    if (lVar3 == 0) {
      lVar3 = func_00329680(0xd);
      if ((lVar3 == 0) && (lVar3 = func_00329680(0xc), lVar3 == 0)) {
        uVar1 = 0;
      }
      else {
        uVar4 = func_00327820();
        lVar3 = func_0032EB40(uVar4,0x14,1);
        if (lVar3 == 0) {
          uVar1 = 0;
        }
        else {
          uVar4 = func_00327820();
          lVar3 = func_0032EB40(uVar4,uVar2,0);
          if (lVar3 == 0) {
            uVar1 = 0;
          }
          else {
            lVar3 = func_003C23A0();
            if (lVar3 == 0) {
              uVar1 = 0;
            }
            else {
              lVar3 = func_003C27A0(0,0x14,uVar2,0x19f,0x19f);
              if (lVar3 == 2) {
                lVar3 = func_0030D150();
                if (lVar3 != 0xc) {
                  uVar2 = func_0030D150();
                  lVar3 = func_0030C280(uVar2,0xc);
                  if (lVar3 == 0) {
                    return 0;
                  }
                }
                uVar1 = 1;
              }
              else {
                uVar1 = 0;
              }
            }
          }
        }
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x003CFF70, 0x104 bytes. */
int func_003CFF70(void)
{
    int bVar1;
    int lVar2;
    int lVar4;
    int uVar3;

  
  lVar2 = func_00327820();
  uVar3 = func_002F5CC0(lVar2);
  lVar4 = func_00329540(0x1b6);
  if (lVar4 == 0) {
    lVar4 = func_003C1850();
    if (lVar4 == 0) {
      if (lVar2 == 0xd) {
        lVar2 = func_0032EB40(0xd,0x17,0);
        if (lVar2 == 0) {
          bVar1 = false;
        }
        else {
          lVar2 = func_002F5CC0(0xd);
          if ((lVar2 == 9) || (lVar2 = func_002F5CC0(0xd), lVar2 == 3)) {
            lVar2 = func_003C1ED0(uVar3,4);
            if (lVar2 == 0) {
              bVar1 = false;
            }
            else {
              lVar2 = func_002F5CC0(0xd);
              lVar4 = func_002F5CC0(0x17);
              bVar1 = lVar2 != lVar4;
            }
          }
          else {
            bVar1 = false;
          }
        }
      }
      else {
        bVar1 = false;
      }
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

/* 0x003D4600, 0x168 bytes. */
void func_003D4600(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar7;
    int iVar8;
    int iVar9;
    int uVar5;
    int uVar6;

  
  func_002C5AE0(param_6);
  iVar9 = 0;
  do {
    if (iVar9 % 3 == 0) {
      iVar3 = 0xc;
      uVar5 = 0;
      iVar1 = param_1;
      iVar7 = iVar3;
    }
    else if (iVar9 % 3 == 1) {
      iVar3 = param_3 + -0x18;
      uVar5 = 0xc;
      iVar1 = param_1 + 0xc;
      iVar7 = 8;
    }
    else {
      iVar3 = 0xc;
      uVar5 = 0x14;
      iVar1 = param_1 + param_3 + -0xc;
      iVar7 = iVar3;
    }
    iVar8 = iVar9 >> 0x1f;
    iVar2 = iVar9 / 3 + iVar8;
    if (iVar2 == iVar8) {
      iVar4 = 0xc;
      uVar6 = 0;
      iVar2 = param_2;
      iVar8 = iVar4;
    }
    else if (iVar2 - iVar8 == 1) {
      iVar4 = param_4 + -0x18;
      uVar6 = 0xc;
      iVar2 = param_2 + 0xc;
      iVar8 = 8;
    }
    else {
      iVar4 = 0xc;
      uVar6 = 0x14;
      iVar2 = param_2 + param_4 + -0xc;
      iVar8 = iVar4;
    }
    func_003D4500(iVar1,iVar2,iVar3,iVar4,uVar5,uVar6,iVar7,iVar8);
    iVar9 = iVar9 + 1;
  } while (iVar9 < 9);
  return;
}

/* 0x003D94D0, 0x1C8 bytes. */
void func_003D94D0(int param_1)
{
    int iVar1;
    int iVar2;
    int iVar4;
    int iVar6;
    int iVar7;
    int * piVar3;
    int * piVar5;

  
  piVar3 = (int *)func_003D9450();
  iVar1 = piVar3[5];
  if (iVar1 == *piVar3 + -1) {
    *piVar3 = iVar1;
    piVar3[1] = piVar3[5] + 1;
    piVar3[2] = piVar3[5] + 2;
    piVar3[3] = piVar3[5] + 3;
    piVar3[4] = piVar3[5] + 4;
  }
  else if (iVar1 == piVar3[4] + 1) {
    *piVar3 = iVar1 + -4;
    piVar3[1] = piVar3[5] + -3;
    piVar3[2] = piVar3[5] + -2;
    piVar3[3] = piVar3[5] + -1;
    piVar3[4] = piVar3[5];
  }
  iVar1 = piVar3[6];
  iVar2 = piVar3[0x10];
  if (piVar3[piVar3[5] + 0x1b] + -1 < 9) {
    iVar4 = (piVar3[piVar3[5] + 0x1b] + -1) * 4;
  }
  else {
    iVar4 = 0x24;
  }
  iVar4 = *(int *)((int)piVar3 + iVar4 + 0x18);
  iVar7 = 0;
  piVar5 = piVar3;
  while( true ) {
    iVar6 = piVar3[piVar3[5] + 0x1b];
    if (9 < iVar6) {
      iVar6 = 10;
    }
    if (iVar6 <= iVar7) break;
    if (param_1 == 0) {
      if (iVar1 + -1 < iVar2) {
        if (iVar2 < iVar4 + 1) {
          return;
        }
        iVar6 = piVar3[0x10] + -9 + iVar7;
      }
      else {
        iVar6 = piVar3[0x10] + iVar7;
      }
    }
    else {
      iVar6 = iVar7;
    }
    iVar7 = iVar7 + 1;
    piVar5[0x11] = piVar3[piVar3[5] * 0x19f + iVar6 + 0x26];
    piVar5[6] = iVar6;
    piVar5 = piVar5 + 1;
  }
  return;
}

/* 0x003D9ED0, 0x134 bytes. */
void func_003D9ED0(int param_1, int param_2)
{
    int bVar2;
    int iVar3;
    int iVar4;
    int lVar6;
    int uVar1;
    int uVar5;

  
  iVar3 = func_003D9450();
  iVar3 = *(int *)(*(int *)(iVar3 + 0x40) * 4 + *(int *)(iVar3 + 0x14) * 0x67c + iVar3 + 0x98);
  iVar4 = func_002F27D0(iVar3);
  uVar1 = *(u8 *)((*(u32 *)(g_005BA6A0 + 0x0)) + iVar4 * 0x2c + 6);
  uVar5 = func_001A93A0(param_1 + 0x10,param_2 + 8,0,0x3c,0x44,0x80,0,0);
  func_001A9B30(uVar5,uVar1,0);
  func_001AA2C0(uVar5,3);
  if (((iVar3 < 0) || (399 < iVar3)) || (lVar6 = func_003A0040(iVar3), lVar6 == 0)) {
    bVar2 = false;
    if ((399 < iVar3) && (iVar3 < 0x19f)) {
      bVar2 = true;
    }
    if (!bVar2) {
      return;
    }
  }
  func_003B5930(param_1 + 0x3c,param_2 + 0x3c,0,3);
  return;
}

/* 0x003E4BE0, 0xF0 bytes. */
void func_003E4BE0(void)
{
    int iVar5;
    int lVar4;
    short * psVar3;
    int sVar1;
    u32 uVar2;

  
  psVar3 = (short *)func_003E46F0();
  if (*psVar3 == 0) {
    iVar5 = (int)psVar3[7] + (int)psVar3[6];
    if (0xd < iVar5) {
      return;
    }
    lVar4 = func_003E4780(iVar5);
    if (lVar4 == 0) {
      func_0023AD10(4,0,0x2cdc,0x2cdc,0x1000);
      return;
    }
    uVar2 = *(u32 *)((g_0045C5C0 + 0x0) + iVar5 * 4);
  }
  else {
    sVar1 = psVar3[6];
    if (2 < sVar1) {
      return;
    }
    lVar4 = func_003E4780(sVar1 + 0xe);
    if (lVar4 == 0) {
      func_0023AD10(4,0,0x2cdc,0x2cdc,0x1000);
      return;
    }
    uVar2 = *(u32 *)((g_0045C5C0 + 0x38) + sVar1 * 4);
  }
  func_0017D8E0(uVar2);
  func_00101470(1);
  return;
}

/* 0x003E7E60, 0x60 bytes. */
int func_003E7E60(void)
{
    int iVar1;
    int uVar2;

  
  iVar1 = func_002FC2C0();
  iVar1 = *(int *)(*(int *)(iVar1 + 0x694) + 0x220);
  uVar2 = 0;
  if (iVar1 == 1) {
    func_003E7770();
  }
  else {
    if (iVar1 != 0) {
      return 0;
    }
    uVar2 = func_003E76C0();
  }
  return uVar2;
}

/* 0x003E7EC0, 0xD8 bytes. */
int func_003E7EC0(int param_1, int param_2, int param_3)
{
  if (param_1 == 0x1a) {
    param_3 = param_3 + 0x85;
  }
  else if (param_1 == 0x1b) {
    param_3 = param_3 + 0x89;
  }
  else if (param_2 == 0x26) {
    param_3 = 0x7f;
  }
  else if (param_2 == 0x24) {
    param_3 = 0x7d;
  }
  else if (param_2 == 0x25) {
    param_3 = 0x7e;
  }
  else if (param_2 == 0x1e) {
    param_3 = 0x74;
  }
  else if (param_2 == 0x20) {
    param_3 = 0x79;
  }
  else if (param_2 == 0x21) {
    param_3 = 0x7a;
  }
  else if (param_2 == 0x22) {
    param_3 = 0x7b;
  }
  else if (param_2 == 0x23) {
    param_3 = 0x7c;
  }
  else {
    param_3 = param_3 + (int)param_2 * 4;
  }
  return param_3;
}

/* 0x003E7FA0, 0x1B4 bytes. */
int func_003E7FA0(int param_1)
{
    int lVar1;

  
  if (param_1 < 0x1c) {
    if (param_1 == 0x1a) {
      lVar1 = 0x1d;
    }
    else {
      lVar1 = 0x1b;
      if (param_1 != 0x1b) {
        lVar1 = param_1;
      }
    }
  }
  else if ((((param_1 == 0x1d) || (param_1 == 0x21)) || (param_1 == 0x22)) || (param_1 == 0x2d)) {
    lVar1 = 0x1a;
  }
  else if (((param_1 == 0x1c) || (param_1 == 0x1e)) ||
          ((param_1 == 0x23 || ((param_1 == 0x24 || ((int)param_1 - 0x2bU < 2)))))) {
    lVar1 = 0x1b;
  }
  else if (((param_1 == 0x1f) || (param_1 == 0x20)) || (param_1 == 0x26)) {
    lVar1 = 0x1c;
  }
  else {
    lVar1 = 0x26;
    if (param_1 != 0x25) {
      if (param_1 == 0x27) {
        lVar1 = 0x24;
      }
      else if (param_1 == 0x28) {
        lVar1 = 0x25;
      }
      else if (((param_1 == 0x29) || (param_1 == 0x2a)) || (param_1 == 0x32)) {
        lVar1 = 0x1e;
      }
      else if (param_1 == 0x2e) {
        lVar1 = 0x20;
      }
      else if (param_1 == 0x2f) {
        lVar1 = 0x21;
      }
      else if (param_1 == 0x30) {
        lVar1 = 0x22;
      }
      else if (param_1 == 0x31) {
        lVar1 = 0x23;
      }
      else {
        lVar1 = 0x1a;
      }
    }
  }
  return lVar1;
}

/* 0x003ED680, 0x16C bytes. */
void func_003ED680(void)
{
    int bVar2;
    int iVar1;
    int iVar10;
    int iVar4;
    int lVar5;
    int lVar6;
    int * piVar3;
    int * piVar9;
    int uVar7;
    int uVar8;

  
  lVar5 = func_002F4080(0);
  lVar6 = func_00327D50();
  if (lVar5 != lVar6) {
    uVar7 = func_003EA160();
    uVar8 = func_002FB2D0(uVar7);
    lVar6 = func_0030C6A0(uVar8);
    if (lVar6 == 3) {
      lVar6 = func_002F7D90(0,0x2f80c0,uVar8,0,0,0);
      piVar3 = (int *)func_002F7B10();
      if (lVar6 == 3) {
        iVar10 = 0;
        piVar9 = piVar3;
        do {
          iVar1 = *piVar9;
          iVar4 = func_002F8F20(uVar7);
          if (iVar1 != iVar4) {
            func_002F7410(piVar3[iVar10]);
            break;
          }
          iVar10 = iVar10 + 1;
          piVar9 = piVar9 + 1;
        } while (iVar10 < 3);
      }
    }
    bVar2 = false;
    if (-1 < lVar5) {
      lVar6 = func_0030AB90();
      bVar2 = lVar5 < lVar6;
    }
    if ((bVar2) && (lVar5 = func_002F8CB0(lVar5), lVar5 != 0)) {
      func_002F7410(0);
    }
    func_002F7300(0,uVar7,uVar8,2);
  }
  return;
}

/* 0x003F1070, 0xEC bytes. */
int func_003F1070(int param_1)
{
    int lVar2;
    u32 uVar1;

  
  lVar2 = func_003A1DF0();
  if (lVar2 == 0) {
    func_003A1CF0(param_1,1);
    (*(u32 *)(g_007BFDD8 + 0x0)) = (*(u32 *)(g_007BFDD8 + 0x0)) + 1;
    if (0x17 < param_1) {
      param_1 = 0x17;
    }
    (*(u32 *)(g_007BFDD8 + 0x4)) = (u32)param_1;
    (*(u8 *)(g_007BFDD8 + 0x8)) = 0;
    (*(u8 *)(g_007BFDD8 + 0x9)) = func_003F1020(param_1);
    (*(u8 *)(g_007BFDD8 + 0xA)) = (*(u32 *)(g_00799A24 + 0x8)) == 0;
    (*(u8 *)(g_007BFDD8 + 0xB)) = (*(u32 *)(g_00799A24 + 0x20)) == 0;
    (*(u8 *)(g_00799A24 + 0x0)) = (*(u8 *)(g_00799A24 + 0x2));
    uVar1 = 1;
    (*(u32 *)(g_00799A24 + 0x4)) = 0;
    (*(u32 *)(g_00799A24 + 0x1C)) = 0;
    (*(u32 *)(g_00799A24 + 0x8)) = 1;
    (*(u32 *)(g_00799A24 + 0x20)) = 1;
    (*(u8 *)(g_00799A24 + 0x18)) = (*(u8 *)(g_00799A24 + 0x1A));
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* 0x003F1160, 0x54 bytes. */
int func_003F1160(int param_1)
{
    int lVar1;
    u32 uVar2;

  
  uVar2 = 0;
  if ((*(u32 *)(g_007BFDD8 + 0x0)) < 1) {
    if ((param_1 != 0) && (lVar1 = func_003F4CB0(), lVar1 != 0)) {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

/* 0x003F1400, 0x180 bytes. */
int func_003F1400(int param_1)
{
    int bVar1;
    u32 uVar2;
    int uVar3;

  
  uVar2 = 0;
  if (0 < (*(u32 *)(g_007BFDD8 + 0x0))) {
    (*(u32 *)(g_007BFDD8 + 0x0)) = (*(u32 *)(g_007BFDD8 + 0x0)) + 1;
    uVar2 = 1;
    if (0x18 < (*(u32 *)(g_007BFDD8 + 0x0))) {
      param_1 = param_1 * 0x88;
      if ((*(u8 *)(param_1 + 0x500764) & 1) == 0) {
        bVar1 = false;
      }
      else {
        bVar1 = (*(u8 *)(param_1 + 0x500765) & 1) == 1;
      }
      if (bVar1) {
        uVar3 = *(u16 *)(param_1 + 0x50074c);
      }
      else {
        uVar3 = 0;
      }
      if ((uVar3 & 0x40) != 0) {
        func_0023AD10(1,0,0x2cdc,0x2cdc,0x1000);
        if ((int)(u32)(*(u8 *)(g_007BFDD8 + 0x8)) < (int)((*(u8 *)(g_007BFDD8 + 0x9)) - 1)) {
          (*(u8 *)(g_007BFDD8 + 0x8)) = (*(u8 *)(g_007BFDD8 + 0x8)) + 1;
          uVar2 = 1;
          (*(u32 *)(g_007BFDD8 + 0x0)) = 1;
        }
        else {
          (*(u8 *)(g_007BFDD8 + 0x8)) = 0;
          (*(u32 *)(g_007BFDD8 + 0x0)) = 0;
          if ((*(char *)(g_007BFDD8 + 0xA)) == '\x01') {
            (*(u8 *)(g_00799A24 + 0x0)) = (*(u8 *)(g_00799A24 + 0x2));
            (*(u32 *)(g_00799A24 + 0x4)) = 1;
            (*(u32 *)(g_00799A24 + 0x8)) = 0;
            (*(char *)(g_007BFDD8 + 0xA)) = '\0';
          }
          if ((*(char *)(g_007BFDD8 + 0xB)) == '\x01') {
            (*(char *)(g_007BFDD8 + 0xB)) = '\0';
            (*(u32 *)(g_00799A24 + 0x1C)) = 1;
            (*(u32 *)(g_00799A24 + 0x20)) = 0;
            (*(u8 *)(g_00799A24 + 0x18)) = (*(u8 *)(g_00799A24 + 0x1A));
          }
          uVar2 = 2;
        }
      }
    }
  }
  return uVar2;
}

/* 0x003F1580, 0x34 bytes, matching. */
void func_003F1580(void)
{
  (*(u32 *)(g_007BFDD8 + 0x0)) = 0;
  (*(u32 *)(g_007BFDD8 + 0x4)) = 0;
  (*(u8 *)(g_007BFDD8 + 0x8)) = 0;
  (*(u8 *)(g_007BFDD8 + 0x9)) = 0;
  (*(u8 *)(g_007BFDD8 + 0xA)) = 0;
  (*(u8 *)(g_007BFDD8 + 0xB)) = 0;
  return;
}

/* 0x003F15C0, 0xFC bytes. */
int func_003F15C0(u32 *param_1)
{
    int iVar1;
    int iVar5;
    int lVar3;
    u32 uVar2;
    int uVar4;

  
  *param_1 = 0;
  lVar3 = func_00327CC0();
  if (lVar3 == 3) {
    iVar5 = 0;
    lVar3 = func_0030AB90();
    if (0 < lVar3) {
      do {
        func_0030B1B0(iVar5,0,0);
        iVar5 = iVar5 + 1;
        iVar1 = func_0030AB90();
      } while (iVar5 < iVar1);
    }
    lVar3 = func_0030CB50(0x19);
    if (lVar3 != 0) {
      iVar5 = func_0030CB00(3);
      iVar1 = 0;
      if (0 < iVar5 + 2) {
        do {
          uVar4 = func_0030AB90();
          uVar4 = func_0030CB00(uVar4);
          lVar3 = func_0030B240(uVar4,0);
          if (lVar3 == 1) {
            iVar1 = iVar1 + -1;
          }
          else {
            func_0030B1B0(uVar4,0);
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 < iVar5 + 2);
      }
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* 0x003F1810, 0xEC bytes. */
void func_003F1810(void)
{
    int iVar1;
    int iVar3;
    int iVar5;
    int iVar6;
    int lVar4;
    u32 * puVar2;

  
  iVar6 = 0;
  lVar4 = func_0030AB90();
  if (0 < lVar4) {
    do {
      lVar4 = func_0030B240(iVar6,1);
      if (lVar4 == 2) {
        iVar1 = func_002F7D90(0,0x2f7ec0,iVar6,0,0,0);
        puVar2 = (u32 *)func_002F7B10();
        iVar5 = 0;
        if (0 < iVar1) {
          do {
            iVar3 = func_002F3770(*puVar2);
            func_002F3660(*puVar2,(iVar3 << 3) / 10);
            iVar5 = iVar5 + 1;
            puVar2 = puVar2 + 1;
          } while (iVar5 < iVar1);
        }
      }
      iVar6 = iVar6 + 1;
      iVar1 = func_0030AB90();
    } while (iVar6 < iVar1);
  }
  return;
}

/* 0x003F1A30, 0x120 bytes. */
int func_003F1A30(u32 *param_1)
{
    int bVar1;
    int iVar2;
    int iVar5;
    int lVar4;
    u32 uVar3;

  
  *param_1 = 0;
  iVar5 = 0;
  lVar4 = func_0030AB90();
  if (0 < lVar4) {
    do {
      lVar4 = func_0030B240(iVar5,1);
      if (lVar4 == 1) {
        return 0;
      }
      iVar5 = iVar5 + 1;
      iVar2 = func_0030AB90();
    } while (iVar5 < iVar2);
  }
  bVar1 = false;
  iVar5 = 0;
  lVar4 = func_0030AB90();
  if (0 < lVar4) {
    do {
      iVar2 = func_0030B240(iVar5,1);
      if (iVar2 - 2U < 2) {
        bVar1 = true;
        break;
      }
      iVar5 = iVar5 + 1;
      iVar2 = func_0030AB90();
    } while (iVar5 < iVar2);
  }
  if (bVar1) {
    func_0030E390(0xd,99,0xffffffffffffffff,0xffffffffffffffff,0,0);
    iVar5 = 0;
    lVar4 = func_0030AB90();
    if (0 < lVar4) {
      do {
        func_0030B1B0(iVar5,1,0);
        iVar5 = iVar5 + 1;
        iVar2 = func_0030AB90();
      } while (iVar5 < iVar2);
    }
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

/* 0x003F1F10, 0x11C bytes. */
int func_003F1F10(u32 *param_1)
{
    int bVar1;
    int iVar2;
    int iVar6;
    int lVar4;
    u32 uVar3;
    int uVar5;

  
  iVar2 = 0;
  *param_1 = 0;
  bVar1 = false;
  lVar4 = func_0030AB90();
  if (0 < lVar4) {
    do {
      lVar4 = func_0030B240(iVar2,1);
      if (lVar4 != 0) {
        bVar1 = true;
        break;
      }
      iVar2 = iVar2 + 1;
      iVar6 = func_0030AB90();
    } while (iVar2 < iVar6);
  }
  if (bVar1) {
    uVar3 = 0;
  }
  else {
    iVar2 = func_00327CC0();
    lVar4 = func_0030CB50(*(u32 *)(iVar2 * 4 + 0x45c9b0));
    if (lVar4 != 0) {
      iVar2 = func_0030CB00(3);
      iVar6 = 0;
      if (0 < iVar2 + 1) {
        do {
          uVar5 = func_0030AB90();
          uVar5 = func_0030CB00(uVar5);
          lVar4 = func_0030B240(uVar5,1);
          if (lVar4 == 1) {
            iVar6 = iVar6 + -1;
          }
          else {
            func_0030B1B0(uVar5,1,1);
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar2 + 1);
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

/* 0x003F2780, 0x90 bytes. */
int func_003F2780(u32 *param_1)
{
    int iVar1;
    int iVar4;
    int lVar2;
    u32 uVar3;

  
  iVar4 = 0;
  *param_1 = 0;
  uVar3 = 0;
  lVar2 = func_0030AB90();
  if (0 < lVar2) {
    do {
      iVar1 = func_0030B240(iVar4,4);
      if (iVar1 - 2U < 2) {
        func_0030B1B0(iVar4,4,0);
        uVar3 = 1;
      }
      iVar4 = iVar4 + 1;
      iVar1 = func_0030AB90();
    } while (iVar4 < iVar1);
  }
  return uVar3;
}

/* 0x003F2950, 0xAC bytes. */
int func_003F2950(u32 *param_1)
{
    int iVar1;
    int iVar4;
    int lVar2;
    int uVar3;

  
  *param_1 = 0;
  lVar2 = func_0030CB50(3);
  if (lVar2 != 0) {
    iVar1 = func_0030CB00(4);
    iVar4 = 0;
    if (0 < iVar1 + 1) {
      do {
        uVar3 = func_0030AB90();
        uVar3 = func_0030CB00(uVar3);
        lVar2 = func_0030B240(uVar3,4);
        if (lVar2 == 1) {
          iVar4 = iVar4 + -1;
        }
        else {
          func_0030B1B0(uVar3,4);
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < iVar1 + 1);
    }
  }
  return 1;
}
