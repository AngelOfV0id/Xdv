# Xdv

**[EN](README.md) / [RU](README-RU.md)**

**Xdv** is a tiny and blazingly fast utility for quickly navigating
Windows file system - browsing directories and opening files.
It has a simple and minimalistic command line interface
and is controlled from keyboard.

**Xdv** is NOT a file manager like nnn, ranger, mc and similar.
There are no file operations such as deleting or creating, copy-pasting,
etc.
Xdv just NAVIGATES directories and OPENS files - that's all.

Run `xdv [PATH]` to start working from other directory (`[PATH]`).
By default Xdv starts working from the current working directory
of the system command shell.

Run `xdv -k` to get key codes for keyboard commands configuration.

Run `xdv -v` to display program version and exit.

Use these keyboard commands to navigate the Windows file system using Xdv:

	Arrow Up / w
					Go up
					(if the beginning of directory is reached,
					starts viewing from the end)
					
	Arrow Down / s
					Go down
					(if the end of directory is reached,
					starts viewing from the beginning)

	Arrow Left / Backspace / a
					Go to the parent directory

	Arrow Right / Enter / d
					Go to the selected directory or open the selected file

	Space / !
					Open the system command shell
					(SHELL variable in config.h file)

	e
					Open the selected directory in Windows Explorer

	i
					Open the selected file in the text editor
					(Windows Notepad by default)
	
	!
					Execute the selected file with administrator privileges
					
	#
					Execute the selected file in the command shell

	+/-
					Increase or decrease navigation step (default: 1)

	v
					Toggle view mode:
					view directories and files (default)
					or view directories only

	r
					Immediately rescan the directory
					
	:
					Switch to another drive
					
	/
					Go by the physical path entered by user

	Escape / q
					Quit

**Xdv** is being configured (if you actually need it, of course)
by editing config.h header file and then recompiling the program
from the [updated] source codes.

To compile Xdv from source codes install GCC and make,
then go to the project directory and run `make` (`mingw32-make`) command.

**Xdv** is a free and open source software and is distributed
under the terms of [MIT License](LICENSE.txt).