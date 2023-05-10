#include "CallWinForm.h"

#include <Windows.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <string.h>

std::vector<std::string> strings = {
    "How do I love thee? Let me count the ways.",
    "I love thee to the depth and breadth and height",
    "My soul can reach, when feeling out of sight",
    "For the ends of Being and ideal Grace.",
    "I love thee to the level of everyday's",
    "Most quiet need, by sun and candlelight.",
    "I love thee freely, as men strive for Right;",
    "I love thee purely, as they turn from Praise.",
    "I love thee with the passion put to use",
    "In my old griefs, and with my childhood's faith.",
    "I love thee with a love I seemed to lose",
    "With my lost saints,I love thee with the breath,",
    "Smiles, tears, of all my life! and, if God choose,",
    "I shall but love thee better after death."};

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (!strcmp(argv[1], "hide"))
        {
            ShowWindow(GetConsoleWindow(), SW_HIDE);
        }
    }

    std::cout << "Create Form Instance\n";
    auto handle = CreateFormInstance(nullptr);
    std::cout << "Instance handle: " << handle << "\n";

    std::cout << "Set UserData to handle string\n";
    SetUserData(handle, std::to_string(handle).data());

    std::cout << "Print UserData set by previous\n";
    std::cout << GetUserData(handle) << "\n";

    std::unordered_map<int, std::string> stringMapping;

    for (const auto &s : strings)
    {
        std::cout << "Add poem string: " << s << " and poem id is: ";
        int stringId = AddTextBoxStrings(handle, s.data());

        stringMapping.insert(std::pair<int, std::string>(stringId, s));
        std::cout << stringId << "\n";
    }

    std::cout << "Set button click handler\n";
    SetButtonClickDelegate(handle, [](const char *userData) -> void
                           { 
                            std::cout << "Handle: " << userData << "clicked the button\n";
                            auto handle = static_cast<FormHandle>(std::stoull(userData)); 
                            
                            AddToTextBox(handle); });

    std::cout << "Show form\n";
    ShowForm(handle);

    while (GetFormCount(handle))
    {
        RenderForm(handle);
    }

    std::cout << "Release Instance\n";
    ReleaseFormInstance(handle);
    return 0;
}