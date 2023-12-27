#include "String.h"
#include "UnitTests.h"
#include <vector>
#include <algorithm>

void ReadInputStrings(std::vector<StringContainers::String>& inputStrings)
{
    StringContainers::String startSortString("sort");
    while (true)
    {
        StringContainers::String tmp;
        std::cout << "Please, enter the string:\n";
        tmp.GetLine(std::cin);
        if (tmp == startSortString)
        {
            return;
        }
        inputStrings.push_back(std::move(tmp));
    }
}

bool DoUserWantToStop()
{
    StringContainers::String quitString("quit");
    StringContainers::String continueString("continue");
    std::cout << "\nType \"quit\" to end the programm or \"continue\" to continue typing strings: ";
    bool bValidInput = false;
    while (!bValidInput)
    {
        StringContainers::String tmp;
        tmp.GetLine(std::cin);
        if (tmp == quitString)
        {
            bValidInput = true;
            return true;
        }
        else if (tmp == continueString)
        {
            bValidInput = true;
            return false;
        }
        else
        {
            std::cout << "\nPlease, type \"quit\" to end the programm or \"continue\" to continue typing strings: ";
        }
    }
    return false;
}

int main()
{
#ifdef RUNTESTS
    Tests::RunTests();
#endif

    std::cout << "Hello and welcome to the test program for sorting custom dynamic strings.\n"
                 "Please, enter your strings into the console. If you want to stop and sort read strings, type \"sort\".\n";
    while (true)
    {
        std::vector<StringContainers::String> strings;

        ReadInputStrings(strings);

        std::sort(strings.begin(), strings.end(),
            [](const StringContainers::String& lhs, const StringContainers::String& rhs) { return lhs.LessThan(rhs, false); });

        std::reverse(strings.begin(), strings.end());

        std::cout << "Sorted strings:\n";
        for (auto&& el : strings)
        {
            std::cout << el;
        }

        // bool bEndProgram = DoUserWantToStop();
        if (DoUserWantToStop())
        {
            break;
        }
    }

    std::cout << "\nThank you for your time!\nType ENTER to quit.\n";
    std::cin.get();
}
