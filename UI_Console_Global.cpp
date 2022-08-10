#include "UI_Console_Global.h"
#include "UI_Color.h"

unsigned short Console::GetX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}

unsigned short Console::GetY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}

void Console::GotoXY(unsigned short xCor, unsigned short yCor)
{
    COORD position;
    HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    position.X=xCor;
    position.Y=yCor;
    SetConsoleCursorPosition(hStdOut, position);
}

void Console::ClearRect(unsigned short xCor, unsigned short yCor, unsigned short w, unsigned short h)
{
    Console::GotoXY(xCor, yCor);
    unsigned short y=yCor;
    for (unsigned short j=0;j<h;++j)
    {
        for (unsigned short i=0;i<w;++i)
            std::cout << " ";
        ++y;
        Console::GotoXY(xCor, y);
    }
    Console::GotoXY(xCor, yCor);
}

void Console::ClearScreen(unsigned short xCor, unsigned short yCor)
{
	Console::GotoXY(xCor, yCor);
    unsigned short wWidth=Console::GetWindowWidth();
    unsigned short remaining=wWidth*Console::GetWindowHeight()-wWidth*yCor;
    for (unsigned short i=0;i<remaining;++i)
        std::cout << " ";
    Console::GotoXY(0, 0);
}

void Console::FlareClear(unsigned int useBG, unsigned int finalText, unsigned int finalBG)
{
	UI_Color tempColor;
	tempColor.SetColor(tempColor.TEXT_COLOR_BLACK, useBG);
	unsigned short wWidth = Console::GetWindowWidth();
	unsigned short wHeight = Console::GetWindowHeight();
	for (unsigned short i = 0, j=wHeight; i!=j; ++i, --j)
	{
		Console::ClearRect(0, i, wWidth-1, 1);
		Console::ClearRect(0, j, wWidth-1, 1);
		Sleep(40);
	}
	tempColor.SetColor(finalText, finalBG);
	Console::ClearScreen(0, 0);
}

void Console::SetWindowSize(unsigned short width, unsigned short height)
{
	std::string command("mode con cols=");
	std::string widthStr, heightStr;
	while (width)
	{
		widthStr += width % 10 + '0';
		width /= 10;
	}
	reverse(widthStr.begin(), widthStr.end());
	while (height)
	{
		heightStr += height % 10 + '0';
		height /= 10;
	}
	reverse(heightStr.begin(), heightStr.end());
	command = command + widthStr + " lines=" + heightStr;
	char *commandCstr = new char[command.length()+1];
	strcpy(commandCstr, command.c_str() );
	system(commandCstr);
	delete[] commandCstr;
}

unsigned short Console::GetWindowWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwSize.X;
}

unsigned short Console::GetWindowHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwSize.Y;
}

void Console::SetWindowTitle(const char* titleCstring)
{
    SetConsoleTitleA(titleCstring);
}

void Console::SetCoding(int codeN)
{
	std::string command("chcp= ");
	std::string codeNStr;
	while (codeN)
	{
		codeNStr += codeN % 10 + '0';
		codeN /= 10;
	}
	reverse(codeNStr.begin(), codeNStr.end());
	command += codeNStr;
	char *commandCstr = new char[command.length() + 1];
	strcpy(commandCstr, command.c_str());
	system(commandCstr);
	delete[] commandCstr;
}
