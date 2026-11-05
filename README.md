# libsac

Secret Agent Clank PS2 address-table library, initially covering the verified USA module-file layout. Uses the same EE Make workflow as librac5; `make` builds `lib/libsacntscu.a`, and `make install` installs its headers/archive into PS2SDK ports.

Include `interop.h` separately from other games' address-table headers. Full and both compact formats use `sacGetAddressAt(table, tableLevel, moduleBase, moduleSize)`.


Addresses in tables are REL-relative, not fixed EE addresses. MainMenu is FE.REL (slot 0 or -1), and other slots follow LEVELn.REL filenames; 6 and 12 are reserved. This layout is checked against the website's verified SAC catalog and RAC Levels exports. `moduleBase` must identify the currently loaded module; `moduleSize` must be its verified original REL size. The resolver rejects unavailable entries, invalid slots, invalid EE ranges, and offsets outside that module.

This initial library does not guess SAC loader globals or equate file slots with its internal runtime level enum. Unlike librac5's automatic GetAddress, callers explicitly supply the loaded-module context. No gameplay hooks or other game APIs are claimed. Only the USA layout has verified source data; other regions and live PCSX2 behavior have not been verified.

## Compact address tables

The resolver accepts original full `VariableAddress_t` tables, fixed-base `sacVariableAddressCompact_t` tables, and selectable-base `sacVariableAddressCompactBase_t` tables. Full-table ABI is unchanged. Fixed compact tables occupy 72 bytes; custom-base tables occupy 72 bytes on the EE.

```c
/* Illustrative values; not verified game addresses. */
sacVariableAddressCompact_t vaFixed = {
	.MainMenu = 0,
	.Level01Museum = SAC_VA_COMPACT_BASE(0x00400000),
	.Level01Timing = SAC_VA_COMPACT_OFFSET(0x00400000, 0x00400100),
};

sacVariableAddressCompactBase_t vaCustom = {
	.MainMenu = 0,
	.Base = SAC_VA_COMPACT_CUSTOM_BASE(0x00400100),
	.Level01Museum = SAC_VA_COMPACT_OFFSET(0x00400100, 0x00400000),
	.Level01Timing = SAC_VA_COMPACT_OFFSET(0x00400100, 0x00400100),
};
```

The first stored word carries the format marker: 0x80000000 for fixed-base compact, 0xc0000000 for custom-base compact. The resolver removes both marker bits before using the base. Use low EE addresses (or REL offsets), without marker bits, as OFFSET arguments. Nonzero map entries must differ from the chosen base by a multiple of four within +/-32767 words. Encoded zero is unavailable; 0x8000 represents the same address as the base. A custom base need not match any map entry, and omitted maps remain unavailable.

`MainMenu` is a plain 32-bit address at byte 4 in both compact layouts. You may write its initializer first; designated initializer order does not control struct layout. The fixed layout stores `Level01Museum` first internally; the custom layout stores `Base` first.

The unpublished menu/lobby-tagged compact layout has been replaced. Update old compact initializers and rebuild their consumers together with this resolver; old compact binaries are not supported by the revised menu-bearing layouts. Full tables remain compatible. librac3's existing fixed Veldin layout retains its encoding. No live PCSX2 verification was performed for this change.

SAC uses REL-relative offsets and still requires an explicitly identified loaded module and its verified REL size. File slots 6 and 12 remain reserved.
