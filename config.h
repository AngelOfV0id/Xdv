/*	This is a configuration file of Xdv - extreme directory navigator.
	See license.txt for copyright and licensing details. */

/* Useful constants */

#define KEY_ARROW_UP	0x3F00
#define KEY_ARROW_DOWN	0x4600
#define KEY_ARROW_LEFT	0x41A0
#define KEY_ARROW_RIGHT	0x4360
#define KEY_ENTER		0x000D
#define KEY_ESCAPE		0x001B
#define KEY_SPACE		0x0020
#define KEY_BACKSPACE	0x0008

/* Configuration code starts here */

const char	*SHELL			= "cmd.exe";

const int	CMD_REFRESH[]	= { 'r' };
const int	CMD_QUIT[]		= { KEY_ESCAPE, 'q' };
const int	CMD_SHELL[]		= { KEY_SPACE, '!' };
const int	CMD_MOVEUP[]	= { KEY_ARROW_UP, 'w' };
const int	CMD_MOVEDOWN[]	= { KEY_ARROW_DOWN, 's' };
const int	CMD_GO[]		= { KEY_ARROW_RIGHT, KEY_ENTER, 'd' };
const int	CMD_GOBACK[]	= { KEY_ARROW_LEFT, KEY_BACKSPACE, 'a' };
const int	CMD_EXPLORE[]	= { 'e' };
const int	CMD_PATH[]		= { '/' };
const int	CMD_DISKS[]		= { ':' };