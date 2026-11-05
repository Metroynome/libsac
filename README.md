# libsac

Secret Agent Clank PS2 address-table library, initially covering the verified USA module-file layout. Uses the same EE Make workflow as librac5; `make` builds `lib/libsacntscu.a`, and `make install` installs its headers/archive into PS2SDK ports.

Include `interop.h` separately from other games' address-table headers. Existing full `VariableAddress_t` tables remain supported. Compact tables use `sacVariableAddressCompact_t`, `SAC_VA_COMPACT_MENU(address)` on MainMenu (even when zero), an ordinary REL-relative offset for Level01Museum, and `SAC_VA_COMPACT_OFFSET(base, address)` for subsequent fields. The website's Address Table (Compact) output emits this format automatically.

Full tables occupy 132 bytes; compact tables occupy 72 bytes including EE padding, saving 60 bytes per table. Non-base fields must be within +/-32767 words of the Museum offset with a multiple-of-four difference. Zero encodes unavailable; equal-to-base is supported. Keep full tables when the range does not fit. Both formats use `sacGetAddressAt(table, tableLevel, moduleBase, moduleSize)`.

Addresses in tables are REL-relative, not fixed EE addresses. MainMenu is FE.REL (slot 0 or -1), and other slots follow LEVELn.REL filenames; 6 and 12 are reserved. This layout is checked against the website's verified SAC catalog and RAC Levels exports. `moduleBase` must identify the currently loaded module; `moduleSize` must be its verified original REL size. The resolver rejects unavailable entries, invalid slots, invalid EE ranges, and offsets outside that module.

This initial library does not guess SAC loader globals or equate file slots with its internal runtime level enum. Unlike librac5's automatic GetAddress, callers explicitly supply the loaded-module context. No gameplay hooks or other game APIs are claimed. Only the USA layout has verified source data; other regions and live PCSX2 behavior have not been verified.
