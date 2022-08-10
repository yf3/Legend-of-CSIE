#ifndef UI_DIALOGUE_H
#define UI_DIALOGUE_H

#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

class UI_Dialogue
{
    public:
        UI_Dialogue();
        string GetDialogue(const string& diaName);
    private:
        unordered_map<string, string> dial;
};

#endif // UI_DIALOGUE_H
