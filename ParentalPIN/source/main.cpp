#if __INTELLISENSE__
typedef unsigned int __SIZE_TYPE__;
typedef unsigned long __PTRDIFF_TYPE__;
#define __attribute__(q)
#define __builtin_strcmp(a,b) 0
#define __builtin_strlen(a) 0
#define __builtin_memcpy(a,b) 0
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __extension__
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
#include <3ds.h>
#include <cstring>
#include <iostream>
#include <3ds/services/cfgu.h>
static int ll = 15;;
static int size = 0xC0;
int main() {
	gfxInitDefault();
	cfguInit();
	consoleInit(GFX_TOP, NULL);
	std::cout << "Hello world!\n";

	// CFG_GetConfigInfoBlk8(0x2, 0x000A0001, &data);
	u8 data2;
	CFGU_GetConfigInfoBlk2(size, 0x000C0000, &data2);
	char* array = (char * ) &data2;

	std::cout << "Your PIN is " << (char) array[0xC] << (char)array[0xD] << (char)array[0xE] << (char)array[0xF] << "\n";
	std::cout << "Dump of 0x000C0000 block (has your secret answer and PIN and other stuff) \n";

	for (int i = 0; i < size; i+=ll)
	{
		for (int xi = 0; xi < ll; xi++)
		{
			if (i + xi == size) break;
			std::cout << (int)array[i + xi] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "Press START to exit.\n";
	u32 down;
	while (aptMainLoop()) {
		hidScanInput();
		down = hidKeysDown();
		if (down & KEY_START) {
			break;
		}
	}

	cfguExit();
	gfxExit();
	return 0;
}