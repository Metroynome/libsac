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
		const sacVariableAddressCompact_t *compact = table;
		if (!tableLevel) {
			offset &= 0x7fffffff;
		} else if (tableLevel == 1) {
			offset = compact->Level01Museum;
		} else {
			u16 encoded;
			__builtin_memcpy(&encoded, (const char *)table + 4 + tableLevel * 2, sizeof(encoded));
			if (!encoded)
				return 0;
			offset = compact->Level01Museum + ((s32)encoded - 0x8000) * 4;
		}
	} else {
		__builtin_memcpy(&offset, (const char *)table + tableLevel * 4, sizeof(offset));
	}
	return offset && offset < moduleSize ? moduleBase + offset : 0;
}
