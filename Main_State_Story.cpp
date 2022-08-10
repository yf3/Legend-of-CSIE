#include "Main_State.h"
#include "Ctrl_UDLR.h"
#include "UI_Menu.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>

using namespace std;
void Display(const string&);

Story::Story()
{
    //ctor
}
Story::~Story()
{
    //dtor
}
Story::Story(const Story &other)
{
    //copy ctor
}

void Display(const string& displayFstream)
{
    if (displayFstream=="#S")
    {
        cout<<endl<<endl;
    }
    else if (displayFstream=="#E")
    {
        cout<< endl <<endl << "\t" << ">...........(Next)";
		cin.ignore(100, '\n');
        system("CLS");
    }
    else if (displayFstream=="@P")
    {
        cout<< endl << endl << "\t" << ">";
        cin.ignore(100, '\n');
        cout<<endl;
    }
    else if (displayFstream=="@N")
    {
        cout<<endl<<endl;
		Sleep(300);
    }
    else if (displayFstream!="")
    {
        cout<<"\t";
        for (string::const_iterator iter=displayFstream.begin() ; iter<displayFstream.end() ; ++iter)
        {
            UI_Color color87;
            if (*iter=='/')
            {
                color87.SetColor(color87.TEXT_COLOR_YELLOW, color87.BG_COLOR_PINK);
            }
			else if (*iter == '+')
				color87.SetColor(color87.TEXT_COLOR_BLACK, color87.BG_COLOR_LIGHT_CYAN);
            else if (*iter=='|')
            {
                color87.SetColorStyle(color87.DEFAULT_COLOR_STYLE);
            }
            else
            {
                cout<<*iter;
            Sleep(50);
            }
        }
    }
}

void Story::handle()
{
    Console::SetWindowSize(120, 40);
    Console::SetWindowTitle("Legend of CSIE");
//    vector<string> display;
	ifstream storyStream("story.txt");
	if (storyStream.fail())
	{
		cout << "Load Fail!" << endl;
	}
    string storyLine;
    while (getline(storyStream, storyLine))
    {
        Display(storyLine);
    }
//    for_each(display.begin(), display.end(), Display);
    storyStream.close();

//    UI_SetSize windowSize(120, 40);
//    windowSize.SetWindowSize();
//    SetConsoleTitleA("Legend of CSIE");
//
//    vector<string> display;
//    fstream storyStream;
//    if (storyStream.fail())
//    {
//        cout << "Load Fail!" << endl;
//    }
//    storyStream.open("story.txt");
//    string storyLine;
//    while (getline(storyStream,storyLine))
//    {
//        display.push_back(storyLine);
//    }
//    for_each(display.begin(), display.end(), Display);
//    storyStream.close();
}
