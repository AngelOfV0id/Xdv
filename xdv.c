/* See license.txt for copyright and licensing details. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

#include "config.h"

#define MAX_SIZE        65536

#define NAME            "Xdv - extreme directory navigator"
#define COPYRIGHT       "Copyright (c) Ivan Movchan, 2023 - 2024"
#define HOMEPAGE        "https://github.com/AngelOfV0id/Xdv"

#define ARRAY           malloc(MAX_SIZE)
#define LENGTH(ARRAY)   (sizeof ARRAY / sizeof ARRAY[0])

#define IS_DIR(F)       (F.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)

#define EXEC(CMD, F)    ShellExecute(NULL, CMD, F, NULL, NULL, SW_SHOWNORMAL)

#define ERASE(COUNT)                \
	printf("\r");                   \
	for (int i = 0; i < COUNT; i++) \
		printf(" ");		        \
	printf("\r");

#define INDEXOF(ARRAY, ITEM, FROM_END)              \
({                                                  \
	int INDEX = -1;                                 \
	if (FROM_END)                                   \
	{                                               \
		for (int i = LENGTH(ARRAY) - 1; i > 0; i--) \
		{                                           \
			if (ITEM == ARRAY[i])                   \
			{                                       \
				INDEX = i;                          \
				break;                              \
			};                                      \
		};                                          \
	}                                               \
	else                                            \
	{                                               \
		for (int i = 0; i < LENGTH(ARRAY); i++)     \
		{                                           \
			if (ITEM == ARRAY[i])                   \
			{                                       \
				INDEX = i;                          \
				break;                              \
			};                                      \
		};                                          \
	};                                              \
	INDEX;                                          \
})

#define CONTAINS(ARRAY, ITEM)		(INDEXOF(ARRAY, ITEM, false) != -1)

#define READLINE()                  \
({                                  \
	char* STR = ARRAY;              \
	fgets(STR, MAX_SIZE, stdin);    \
	STR[strlen(STR) - 1] = '\0';    \
	STR;                            \
})

int readkey()
{
	int k = getch(), k2 = (k == 0xE0 ? getch() : 1);
	return (k * k2);
}

void main(int argc, char** argv)
{
	WIN32_FIND_DATA	*items = ARRAY;
	HANDLE			find_file;
	char			*path = ARRAY, *find_path = ARRAY, *info = ARRAY;
	int				index = 0, count = 0, command = 0, step = 1;
	bool			running = true, dirs_only = false;

	setlocale(LC_ALL, "");
	
	if (argc == 2)
	{
		running = strcmp(argv[1], "-v") && strcmp(argv[1], "-k");
		if (!strcmp(argv[1], "-v"))
			printf("%s %s\n%s\n%s\n", NAME, VERSION, COPYRIGHT, HOMEPAGE);
		else if (!strcmp(argv[1], "-k"))
		{
			int key = 0;
			printf("Press any key to get its HEX code, Escape to exit.\n");
			while (key != 0x1B)
			{
				key = readkey();
				printf("0x%.8X\n", key);
			};
		}
		else
			SetCurrentDirectory(argv[1]);
	};

	while (running)
	{
		GetCurrentDirectory(MAX_SIZE, path);
		sprintf(find_path, "%s\\*", path);

		count = 0;
		find_file = FindFirstFile(find_path, &items[0]);
		while (FindNextFile(find_file, &items[count]) != 0)
			if (strcmp(items[count].cFileName, ".."))
				if ((dirs_only && IS_DIR(items[count])) || !dirs_only)
					count++;
		FindClose(find_file);
		count--;

		while (1)
		{
			if (index < 0)
				index = count;
			else if (index > count)
				index = 0;

			if (step > count)
				step = 1;

			ERASE(strlen(info));
			
			sprintf(info, "%s: empty.", path);
			if (dirs_only)
				sprintf(info, "%s: no directories.", path);
			if (count != -1)
				sprintf(info, "[%d / %d] %s > %s%c",
					index + 1, count + 1,
					path, items[index].cFileName,
					(IS_DIR(items[index]) ? '\\' : '\0'));
			printf("%s", info);

			command = readkey();

			if (CONTAINS(CMD_REFRESH, command))
				break;
		
			if (CONTAINS(CMD_QUIT, command))
			{
				running = false;
				break;
			};
			
			if (CONTAINS(CMD_VIEWMODE, command))
			{
				dirs_only = !dirs_only;
				break;
			};
			
			if (CONTAINS(CMD_MOVEUP, command))
				index -= step;
			
			if (CONTAINS(CMD_MOVEDOWN, command))
				index += step;

			if (CONTAINS(CMD_STEPINC, command) && (step < count - 1))
				step++;
			
			if (CONTAINS(CMD_STEPDEC, command) && (step > 1))
				step--;
			
			if (CONTAINS(CMD_GO, command))
			{
				if (IS_DIR(items[index]))
					sprintf(path, "%s\\%s", path, items[index].cFileName);
				else
					EXEC("open", items[index].cFileName);
				if (SetCurrentDirectory(path))
					break;
			};

			if (CONTAINS(CMD_GOBACK, command))
			{
				for (int i = strlen(path); i > 0; i--)
					if (path[i] == '\\')
						break;
					else
						path[i] = '\0';
				if (SetCurrentDirectory(path))
					break;
			};

			if (CONTAINS(CMD_EXPLORE, command) && IS_DIR(items[index]))
				EXEC("explore", items[index].cFileName);
			
			if (CONTAINS(CMD_EDIT, command) && !IS_DIR(items[index]))
				EXEC("edit", items[index].cFileName);
			
			if (CONTAINS(CMD_RUNCLI, command) && !IS_DIR(items[index]))
				system(items[index].cFileName);
			
			if (CONTAINS(CMD_RUNADMIN, command) && !IS_DIR(items[index]))
				EXEC("runas", items[index].cFileName);
			
			if (CONTAINS(CMD_PATH, command))
			{
				printf("\nGo to: ");
				path = READLINE();
				if (SetCurrentDirectory(path))
					break;
			};
			
			if (CONTAINS(CMD_DISKS, command))
			{
				printf("\nGo to [A-Z]: ");
				char disk = getch();
				printf("\n");
				sprintf(path, "%c:\\", toupper(disk));
				if (SetCurrentDirectory(path))
					break;
				else
					GetCurrentDirectory(MAX_SIZE, path);
			};
			
			if (CONTAINS(CMD_SHELL, command))
			{
				printf("\n");
				system(SHELL);
				break;
			};
		};
	};
}
