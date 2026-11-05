#ifndef LIBSAC_INTEROP_H
#define LIBSAC_INTEROP_H

#include <tamtypes.h>

/* REL-relative offsets. Slots follow FE.REL (0) and LEVELn.REL (1..32),
 * not an assumed runtime level enum. Zero means unavailable.
 * Slots 6 and 12 have no module on the verified USA disc.
 * Include separately from other games' VariableAddress_t definitions. */
typedef struct variableAddress {
	/* 0x00 */ u32 MainMenu; /* 0 */
	/* 0x04 */ u32 Level01Museum; /* 1 */
	/* 0x08 */ u32 Level01Timing; /* 2 */
	/* 0x0c */ u32 Level01Prison; /* 3 */
	/* 0x10 */ u32 Level02Skyscrapers; /* 4 */
	/* 0x14 */ u32 Level02Giant; /* 5 */
	/* 0x18 */ u32 Reserved06; /* 6 */
	/* 0x1c */ u32 Level03Countess; /* 7 */
	/* 0x20 */ u32 Level03Snowboard; /* 8 */
	/* 0x24 */ u32 Level03Cafeteria; /* 9 */
	/* 0x28 */ u32 Level04Carnival; /* 10 */
	/* 0x2c */ u32 Level04Gondola; /* 11 */
	/* 0x30 */ u32 Reserved12; /* 12 */
	/* 0x34 */ u32 Level05Casino; /* 13 */
	/* 0x38 */ u32 Level05Yard; /* 14 */
	/* 0x3c */ u32 Level05Highstakes; /* 15 */
	/* 0x40 */ u32 Level06Lab; /* 16 */
	/* 0x44 */ u32 Level06Race; /* 17 */
	/* 0x48 */ u32 Level06Qwark; /* 18 */
	/* 0x4c */ u32 Level07Foundry; /* 19 */
	/* 0x50 */ u32 Level07Gadgebot; /* 20 */
	/* 0x54 */ u32 Level07Shower; /* 21 */
	/* 0x58 */ u32 Level08Graveyard; /* 22 */
	/* 0x5c */ u32 Level08Qwark; /* 23 */
	/* 0x60 */ u32 Level08GiantClank; /* 24 */
	/* 0x64 */ u32 Level09Escapeyard; /* 25 */
	/* 0x68 */ u32 Level09Damrace; /* 26 */
	/* 0x6c */ u32 Level09Qwarkdam; /* 27 */
	/* 0x70 */ u32 Level10Gadgebot; /* 28 */
	/* 0x74 */ u32 Level10Base; /* 29 */
	/* 0x78 */ u32 Level10Boss; /* 30 */
	/* 0x7c */ u32 HIGTreehouse; /* 31 */
	/* 0x80 */ u32 HIGCredits; /* 32 */
} VariableAddress_t;

#define SAC_VA_COMPACT_BASE(address) ((u32)(address) | (u32)0x80000000)
#define SAC_VA_COMPACT_CUSTOM_BASE(address) ((u32)(address) | (u32)0xc0000000)
#define SAC_VA_COMPACT_OFFSET(base, address) ((address) == 0 ? 0 : \
	(u16)(((s32)(address) - (s32)(base)) / 4 + 0x8000 + \
	0 * sizeof(char[((address) == 0 || (((s32)(address) - (s32)(base)) % 4 == 0 && \
	((s32)(address) - (s32)(base)) / 4 >= -32767 && \
	((s32)(address) - (s32)(base)) / 4 <= 32767)) ? 1 : -1])))

typedef struct sacVariableAddressCompact {
	/* 0x00 */ u32 Level01Museum;
	/* 0x04 */ u32 MainMenu;
	/* 0x08 */ u16 Level01Timing;
	/* 0x0a */ u16 Level01Prison;
	/* 0x0c */ u16 Level02Skyscrapers;
	/* 0x0e */ u16 Level02Giant;
	/* 0x10 */ u16 Reserved06;
	/* 0x12 */ u16 Level03Countess;
	/* 0x14 */ u16 Level03Snowboard;
	/* 0x16 */ u16 Level03Cafeteria;
	/* 0x18 */ u16 Level04Carnival;
	/* 0x1a */ u16 Level04Gondola;
	/* 0x1c */ u16 Reserved12;
	/* 0x1e */ u16 Level05Casino;
	/* 0x20 */ u16 Level05Yard;
	/* 0x22 */ u16 Level05Highstakes;
	/* 0x24 */ u16 Level06Lab;
	/* 0x26 */ u16 Level06Race;
	/* 0x28 */ u16 Level06Qwark;
	/* 0x2a */ u16 Level07Foundry;
	/* 0x2c */ u16 Level07Gadgebot;
	/* 0x2e */ u16 Level07Shower;
	/* 0x30 */ u16 Level08Graveyard;
	/* 0x32 */ u16 Level08Qwark;
	/* 0x34 */ u16 Level08GiantClank;
	/* 0x36 */ u16 Level09Escapeyard;
	/* 0x38 */ u16 Level09Damrace;
	/* 0x3a */ u16 Level09Qwarkdam;
	/* 0x3c */ u16 Level10Gadgebot;
	/* 0x3e */ u16 Level10Base;
	/* 0x40 */ u16 Level10Boss;
	/* 0x42 */ u16 HIGTreehouse;
	/* 0x44 */ u16 HIGCredits;
	/* 0x46: two bytes of EE alignment padding. */
} sacVariableAddressCompact_t;

typedef struct sacVariableAddressCompactBase {
	/* 0x00 */ u32 Base;
	/* 0x04 */ u32 MainMenu;
	/* 0x08 */ u16 Level01Museum;
	/* 0x0a */ u16 Level01Timing;
	/* 0x0c */ u16 Level01Prison;
	/* 0x0e */ u16 Level02Skyscrapers;
	/* 0x10 */ u16 Level02Giant;
	/* 0x12 */ u16 Reserved06;
	/* 0x14 */ u16 Level03Countess;
	/* 0x16 */ u16 Level03Snowboard;
	/* 0x18 */ u16 Level03Cafeteria;
	/* 0x1a */ u16 Level04Carnival;
	/* 0x1c */ u16 Level04Gondola;
	/* 0x1e */ u16 Reserved12;
	/* 0x20 */ u16 Level05Casino;
	/* 0x22 */ u16 Level05Yard;
	/* 0x24 */ u16 Level05Highstakes;
	/* 0x26 */ u16 Level06Lab;
	/* 0x28 */ u16 Level06Race;
	/* 0x2a */ u16 Level06Qwark;
	/* 0x2c */ u16 Level07Foundry;
	/* 0x2e */ u16 Level07Gadgebot;
	/* 0x30 */ u16 Level07Shower;
	/* 0x32 */ u16 Level08Graveyard;
	/* 0x34 */ u16 Level08Qwark;
	/* 0x36 */ u16 Level08GiantClank;
	/* 0x38 */ u16 Level09Escapeyard;
	/* 0x3a */ u16 Level09Damrace;
	/* 0x3c */ u16 Level09Qwarkdam;
	/* 0x3e */ u16 Level10Gadgebot;
	/* 0x40 */ u16 Level10Base;
	/* 0x42 */ u16 Level10Boss;
	/* 0x44 */ u16 HIGTreehouse;
	/* 0x46 */ u16 HIGCredits;
} sacVariableAddressCompactBase_t;

/* Caller supplies an identified, currently loaded SNR2 module and its verified
 * original REL size. tableLevel is the module-file slot (-1 also means FE).
 * Accepts full or compact tables. Returns zero for invalid/unavailable input.
 * Does not dereference EE RAM or assume unverified loader globals. */
#ifdef __cplusplus
extern "C" {
#endif
u32 sacGetAddressAt(const void *table, int tableLevel,
	u32 moduleBase, u32 moduleSize);
#ifdef __cplusplus
}
#endif
#endif
