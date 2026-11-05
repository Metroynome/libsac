#include "interop.h"

u32 sacGetAddressAt(const void *table, int tableLevel,
	u32 moduleBase, u32 moduleSize)
{
	u32 offset;
	if (!table || moduleBase < 0x00100000 || moduleBase >= 0x02000000 ||
		(moduleBase & 0x7f) || !moduleSize || moduleSize > 0x02000000 - moduleBase)
		return 0;
	if (tableLevel == -1)
		tableLevel = 0;
	if (tableLevel < 0 || tableLevel > 32 || tableLevel == 6 || tableLevel == 12)
		return 0;
	/* Read the common first word without aliasing either struct type. */
	__builtin_memcpy(&offset, table, sizeof(offset));
	if (offset & (u32)0x80000000) {
		const u32 base = offset & 0x3fffffff;
		const int custom = (offset & 0x40000000) != 0;
		if (!tableLevel) {
			__builtin_memcpy(&offset, (const char *)table + 4, sizeof(offset));
		} else if (!custom && tableLevel == 1) {
			offset = base;
		} else {
			u16 encoded;
			const int slotOffset = (custom ? 6 : 4) + tableLevel * 2;
			__builtin_memcpy(&encoded, (const char *)table + slotOffset, sizeof(encoded));
			if (!encoded)
				return 0;
			offset = base + ((s32)encoded - 0x8000) * 4;
		}
	} else {
		__builtin_memcpy(&offset, (const char *)table + tableLevel * 4, sizeof(offset));
	}
	return offset && offset < moduleSize ? moduleBase + offset : 0;
}
