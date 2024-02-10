/* This is a source code of Xdv - extreme directory navigator. See license.txt for copyright and licensing details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

#include "config.h"

#define KEY_ARROW_UP	0x3F00
#define KEY_ARROW_DOWN	0x4600
#define KEY_ARROW_LEFT	0x41A0
#define KEY_ARROW_RIGHT	0x4360
#define KEY_ENTER		0x000D
#define KEY_ESCAPE		0x001B
#define KEY_SPACE		0x0020
#define KEY_BACKSPACE	0x0008

#define MAX_SIZE		65536
#define ARRAY			malloc(MAX_SIZE)

#define is_dir(wfd)		((wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0x10)	// Returns 1 if wfd [WIN32_FIND_DATA] is a directory

void erase(count)	// Erase amount of chars in line
{
	printf("\r");
	for (int i = 0; i < count; i++) printf(" ");
	printf("\r");
}

int readkey()		// Extended version of getch() which works with Arrow keys
{
	int k = 0, k2 = 1;
	k = getch();
	if (k == 0xE0) k2 = getch();	// 0xE0 = Arrow key, the second value is passed into k2 (as another key press)
	return (k * k2);
}

void main(int argc, char** argv)	// Program entry - here the party begins
{
	WIN32_FIND_DATA	*items = ARRAY;
	HANDLE			find_file;
	char			*path = ARRAY, *find_path = ARRAY, *info = ARRAY;
	int				index = 0, count = 0, command = 0, running = 1;

	setlocale(LC_ALL, "");	// Set console locale
	
	if (argc == 2)
	{
		if (!strcmp(argv[1], "-v"))			// If '-v' key passed, display program version and exit
		{
			printf("Xdv - extreme directory navigator, version %s\nhttps://angelofv0id.github.io/Xdv\n", VERSION);
			return;
		}
		else SetCurrentDirectory(argv[1]);	// Use the only argument as the path of working directory (if it is path, of course)
	};

	while (running)	// Program lifetime loop
	{
		GetCurrentDirectory(MAX_SIZE, path);	// Get physical path of the working directory
		sprintf(find_path, "%s\\*", path);

		count = 0;
		find_file = FindFirstFile(find_path, &items[0]);
		while (FindNextFile(find_file, &items[count]) != NULL) if (strcmp(items[count].cFileName, ".") && strcmp(items[count].cFileName, "..")) count++;
		FindClose(find_file);
		count--;

		while (1)	// Interactive mode: enter and execute commands
		{
			if (index < 0) index = count;
			if (index > count) index = 0;

			erase(strlen(info));

			sprintf(info, DISPLAY_FORMAT_EMPTY, path);
			if (count != -1) sprintf(info, DISPLAY_FORMAT, index + 1, count + 1, path, (is_dir(items[index]) ? DIRECTORY_MARK : ""), items[index].cFileName);
			printf("%s", info);	// Generate and display information message about selected item

			command = readkey();							// Get a command from keyboard (key press)

			if (command == 'r') break;						// 'r' = rescan directory
		
			if (command == KEY_ESCAPE || command == 'q')	// <Esc> / 'q' = quit program
			{
				running = 0;
				break;
			};
		
			if (command == KEY_SPACE || command == '!')		// <Space> / '!' = open system command shell
			{
				erase(strlen(info));
				system(SHELL);
				break;
			};
		
			if (command == KEY_ARROW_UP || command == 'w') index--;			// <Arrow Up> / 'w' = go up
			else if (command == KEY_ARROW_DOWN || command == 's') index++;	// <Arrow Down> / 's' = go down

			if (command == KEY_ARROW_LEFT || command == KEY_BACKSPACE || command == 'a')	// <Arrow Left> / <Backspace> / 'a' = go to the parent directory
			{
				for (int i = strlen(path); i > 0; i--) if (path[i] == '\\') break; else path[i] = '\0';	// Truncate path until the backslash
				if (SetCurrentDirectory(path)) break;
			}
			else if (command == KEY_ARROW_RIGHT || command == KEY_ENTER || command == 'd')	// <Arrow Right> / <Enter> / 'd' = go to directory or open file
			{
				if (is_dir(items[index])) sprintf(path, "%s\\%s", path, items[index].cFileName);
				else ShellExecute(NULL, "open", items[index].cFileName, NULL, path, SW_SHOWNORMAL);
				if (SetCurrentDirectory(path)) break;
			};

			if (command == 'e' && is_dir(items[index])) ShellExecute(NULL, "explore", items[index].cFileName, NULL, path, SW_SHOWNORMAL);	// 'e' = open selected directory in Windows Explorer
		};
	};
}
