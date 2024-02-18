	#     #       #
	 #   #        #
	  # #    ###### #     #
	   #    #     # #    #
	  # #   #     # #   #
	 #   #  #     # #  #
	#     #  ###### ###

NAME

	Xdv - extreme directory navigator.

SYNOPSIS

	Xdv [PATH] [-v]

DESCRIPTION

	Xdv is a tiny and blazingly fast utility for quickly navigating
	Windows file system - browsing directories and opening files.
	It has a simple and minimalistic command line interface
	and is controlled from keyboard.
	
	Xdv is NOT a file manager like nnn, ranger, mc and similar.
	There are no file operations such as deleting or creating, copy-pasting,
	etc. (but they may appear in the future, who knows)
	It just NAVIGATES directories and OPENS files - that's all.

USAGE

	Xdv has simple and easy to remember keyboard commands.
	They can be easily modified - see CONFIGURATION section for details.

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

	r
					Immediately rescan the directory
					
	:
					Switch to another drive
					
	/
					Go by the physical path entered by user

	Escape / q
					Quit
	
OPTIONS

	[PATH]
					The path to the working directory from which
					should Xdv start working.
					If it is not specified, Xdv starts working from
					the current working directory of the system command shell
					(or somewhere else)

	-v
					If this flag is specified, Xdv displays
					the program version and exits

CONFIGURATION

	Xdv is being configured by editing config.h header file
	and recompiling the program from [updated] source codes
	(see MAKE section for details).
	This keeps Xdv simple, fast and safe.

MAKE

	To compile Xdv from source codes, tcc is recommended to use.
	However, you can use any other C compiler you like - just edit make.bat
	build script to satisfy your needs.
	To create Xdv distros, 7z archiver and zip.bat script are used.

	If you are ready to rock, just run:

		make && zip

HISTORY

	I came up with an idea of Xdv in late December 2023, inspired by
	some Linux console system utilities, file managers and
	Suckless.org philosophy (see THANKS for details).
	Actually, I was looking for a tiny console file manager for Windows.
	FAR Manager and similar console file managers I found did not satisfy me,
	so I decided to start my own project.

	That's how Xdv history started.
	
	I have been working on the first draft version of Xdv
	about a month (January 2024). For all this time I rewrote this program
	from scratch about eight times. Eight. 0x08.
	
	Xdv has been planned as another console file manager with
	over 9000 cool functions and operations [nobody needed], but with every
	erased line of code it became much smaller and simpler thing
	than planned already.
	I decided not to transform my project into something big and complex
	(which could be called "file manager"), but instead make a tiny and nice
	system utility I would enjoy using and developing.

	As a result, the first public version of Xdv consisted of ~120 lines of code.
	In comparison, the first draft version of Xdv (codename NTXDV;
	NT stands for "Windows NT") consisted of about 1000 lines of complex
	(and 0.666% working) code.
	
	See changelog.txt for the version history.

AUTHOR

	Made with love for you by Ivan Movchan aka AngelOfV0id <AngelOfV0id@yandex.ru>.
	
	I hope you will enjoy using Xdv as much as I enjoy developing it.
	Any ideas and suggestions will be highly appreciated.

LICENSE

	Xdv is a free and open source software provided "as is",
	without any warranties. You are using this software at your own risk.

	See license.txt for further details.

THANKS

	Authors of my favourite development tools:
		micro <https://micro-editor.github.io>,
		tcc <https://bellard.org/tcc>,
		7z <https://7-zip.org>.

	Authors of these Linux console file managers
	the "Xdv" project was inspired by:
		nnn <https://github.com/jarun/nnn>,
		ranger <https://ranger.github.io>,
		sfm <https://github.com/afify/sfm>.

	Suckless.org <https://suckless.org> for their interesting philosophy,
	projects and inspiration.

	Friends and relatives for their love and support.

HOME

	https://github.com/AngelOfV0id/Xdv
