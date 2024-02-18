/*	This is a source code of Xdv - extreme directory navigator.
	See license.txt for copyright and licensing details. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

#include "config.h"

#define MAX_SIZE				65536

#define DISPLAY_FORMAT			"%.8d / %.8d:    %s > %s%s"
#define DISPLAY_FORMAT_EMPTY	"%s: no items"
#define PATH_PROMPT				"> "
#define DIRECTORY_MARK			"[DIR] "

#define DISKS					"abcdefghijklmnopqrstuvwxyz"

#define NAME					"Xdv - extreme directory navigator"
#define AUTHOR					"AngelOfV0id"
#define YEARS					"2023 - 2024"
#define HOMEPAGE				"https://github.com/AngelOfV0id/Xdv"

#define ARRAY					malloc(MAX_SIZE)
#define STREQU					!strcmp
#define STDOUT					GetStdHandle(STD_OUTPUT_HANDLE)

#define LENGTH(ARRAY)			(sizeof ARRAY / sizeof ARRAY[0])
#define ISDIR(F)				(F.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
#define EXEC(CMD, FILE)			ShellExecute(NULL, CMD, FILE, NULL, NULL, SW_SHOWNORMAL)
#define KEY_SPECIAL(KEY)		(KEY == (0xE0))

#define ERASE(COUNT)				\
	printf("\r");					\
	for (int i = 0; i < COUNT; i++)	\
		printf(" ");				\
	printf("\r");

#define INDEXOF(ARRAY, ITEM, FROM_END)				\
({													\
	int INDEX = -1;									\
	if (FROM_END)									\
	{												\
		for (int i = LENGTH(ARRAY) - 1; i > 0; i--)	\
		{											\
			if (ITEM == ARRAY[i])					\
			{										\
				INDEX = i;							\
				break;								\
			};										\
		};											\
	}												\
	else											\
	{												\
		for (int i = 0; i < LENGTH(ARRAY); i++)		\
		{											\
			if (ITEM == ARRAY[i])					\
			{										\
				INDEX = i;							\
				break;								\
			};										\
		};											\
	};												\
	INDEX;											\
})

#define STR_INDEXOF(STR, CHAR, FROM_END)			\
({													\
	int INDEX = -1;									\
	if (FROM_END)									\
	{												\
		for (int i = strlen(STR) - 1; i > 0; i--)	\
		{											\
			if (CHAR == STR[i])						\
			{										\
				INDEX = i;							\
				break;								\
			};										\
		};											\
	}												\
	else											\
	{												\
		for (int i = 0; i < strlen(STR); i++)		\
		{											\
			if (CHAR == STR[i])						\
			{										\
				INDEX = i;							\
				break;								\
			};										\
		};											\
	};												\
	INDEX;											\
})

#define CONTAINS(ARRAY, ITEM)	(INDEXOF(ARRAY, ITEM, false) != -1)
#define STR_CONTAINS(STR, CHAR)	(STR_INDEXOF(STR, CHAR, false) != -1)

#define READLINE()					\
({									\
	char* STR = ARRAY;				\
	fgets(STR, MAX_SIZE, stdin);	\
	STR[strlen(STR) - 1] = '\0';	\
	STR;							\
})

int readkey()
{
	int k = 0, k2 = 1;
	k = getch();
	if (KEY_SPECIAL(k))
		k2 = getch();
	return (k * k2);
}

void main(int argc, char** argv)
{
	WIN32_FIND_DATA	*items = ARRAY;
	HANDLE			find_file;
	char			*path = ARRAY, *find_path = ARRAY, *info = ARRAY;
	int				index = 0, count = 0, command = 0;
	bool			running = true;

	setlocale(LC_ALL, "");
	
	if (argc == 2)
	{
		running = !STREQU(argv[1], "-v");
		if (!running)
			printf("%s %s\nby %s, %s\n%s\n", NAME, VERSION, AUTHOR, YEARS, HOMEPAGE);
		else
			SetCurrentDirectory(argv[1]);
	};

	while (running)
	{
		GetCurrentDirectory(MAX_SIZE, path);
		sprintf(find_path, "%s\\*", path);

		count = 0;
		find_file = FindFirstFile(find_path, &items[0]);
		while (FindNextFile(find_file, &items[count]) != NULL)
			if (!STREQU(items[count].cFileName, ".."))
				count++;
		FindClose(find_file);
		count--;

		while (1)
		{
			if (index < 0)
				index = count;
			else if (index > count)
				index = 0;

			ERASE(strlen(info));
			
			sprintf(info, DISPLAY_FORMAT_EMPTY, path);
			if (count != -1)
				sprintf(
					info, DISPLAY_FORMAT,
					index + 1, count + 1,
					path,
					(ISDIR(items[index]) ? DIRECTORY_MARK : ""),
					items[index].cFileName
				);
			printf("%s", info);

			command = readkey();

			if (CONTAINS(CMD_REFRESH, command))
				break;
		
			if (CONTAINS(CMD_QUIT, command))
			{
				running = false;
				break;
			};
		
			if (CONTAINS(CMD_SHELL, command))
			{
				printf("\n");
				system(SHELL);
				break;
			};
		
			if (CONTAINS(CMD_MOVEUP, command))
				index--;
			if (CONTAINS(CMD_MOVEDOWN, command))
				index++;

			if (CONTAINS(CMD_GOBACK, command))
			{
				int slash = STR_INDEXOF(path, '\\', true);
				for (int i = strlen(path); i > slash; i--)	// truncate path
					path[i] = '\0';
				if (SetCurrentDirectory(path))
					break;
			};
			
			if (CONTAINS(CMD_GO, command))
			{
				if (ISDIR(items[index]))
					sprintf(path, "%s\\%s", path, items[index].cFileName);
				else
					EXEC("open", items[index].cFileName);
				if (SetCurrentDirectory(path))
					break;
			};

			if (CONTAINS(CMD_EXPLORE, command) && ISDIR(items[index]))
				EXEC("explore", items[index].cFileName);
			
			if (CONTAINS(CMD_PATH, command))
			{
				ERASE(strlen(info));
				printf(PATH_PROMPT);
				path = READLINE();
				if (SetCurrentDirectory(path))
					break;
			};
			
			if (CONTAINS(CMD_DISKS, command))
			{
				printf("\nPress A-Z key to go to disk.");
				char disk = getch();
				printf("\n");
				if (STR_CONTAINS(DISKS, disk))
				{
					sprintf(path, "%c:\\", toupper(disk));
					if (SetCurrentDirectory(path))
						break;
					else
						GetCurrentDirectory(MAX_SIZE, path);
				};
			};
		};
	};
}
