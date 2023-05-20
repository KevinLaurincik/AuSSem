#include "MySequence.h"

Sequence::Sequence()
{
}

void Sequence::startWithStr(std::string userInput, std::string nazorSuboru)
{
    std::vector<std::vector<std::string>> content;
    std::vector<std::string> row;
    std::string line;
    std::string word;
    std::vector<std::vector<std::string>> result;

    std::fstream file(nazorSuboru);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            std::stringstream str(line);

            while (getline(str, word, ';'))
                row.push_back(word);
            content.push_back(row);
        }
    }
    file.close();

    if (nazorSuboru == "okresy.csv")
    {
        for (int i = 1; i < content.size(); i++)
        {
            if ((content[i][3].rfind(userInput, 0) == 0))
            {
                result.push_back(content[i]);
            }
        }
    }
    else
    {
        for (int i = 1; i < content.size(); i++)
        {
            if ((content[i][2].rfind(userInput, 0) == 0))
            {
                result.push_back(content[i]);
            }
        }
    }

    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[i].size(); j++)
        {
            std::cout << result[i][j] << " ";
        }
        std::cout << "\n";
    }
    //destruktor
    for (auto& row : content) {
        row.clear();
    }
    content.clear();
    row.clear();
    for (auto& row : result) {
        row.clear();
    }
    result.clear();
}

void Sequence::containsStr(std::string userInput, std::string nazorSuboru)
{
    std::vector<std::vector<std::string>> content;
    std::vector<std::string> row;
    std::string line;
    std::string word;
    std::vector<std::vector<std::string>> result;

    std::fstream file(nazorSuboru);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            std::stringstream str(line);

            while (getline(str, word, ';'))
                row.push_back(word);
            content.push_back(row);
        }
    }
    file.close();

    for (int i = 1; i < content.size(); i++)
    {
        if (content[i][2].find(userInput) != std::string::npos)
        {
            result.push_back(content[i]);
        }
    }

    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[i].size(); j++)
        {
            std::cout << result[i][j] << " ";
        }
        std::cout << "\n";
    }

    //destruktor
    for (auto& row : content) {
        row.clear();
    }
    content.clear();
    row.clear();
    for (auto& row : result) {
        row.clear();
    }
    result.clear();
}

void Sequence::searchMenuSequence()
{
    while (true)
    {
        int userInput;
        string stringUserInput;

        cout << endl;
        cout << "#--------------------------------------------------------------#" << endl;
        cout << "Stla�te 1 ak chcete prehlad�va� pomocou startWithStr." << endl;
        cout << "Stla�te 2 ak chcete prehlad�va� pomocou containsStr." << endl;
        cout << "Stla�te 3 ak sa chcete vr�ti� do menu." << endl;
        cout << "#--------------------------------------------------------------#" << endl;
        cout << endl;

        while (!(cin >> userInput))
        {
            cout << "Nezadali ste ��slo. Prosim zadajte znovu ��slo: " << endl;
            cin.clear();
            cin.ignore(123, '\n');
        }

        cout << "Zadali ste ��slo: " << userInput << endl;

        if (userInput == 1)
        {
            cout << "Zadajte re�azec, ktor�m sa m� vyh�ad�van� v�raz za��na�: " << endl;
            cin.ignore();
            getline(cin, stringUserInput);
            cout << "N�jden� kraje: " << endl << "\n";
            startWithStr(stringUserInput, "kraje.csv");
            cout << "N�jden� okresy: " << endl << "\n";
            startWithStr(stringUserInput, "okresy.csv");
            cout << "N�jden� obce: " << endl << "\n";
            startWithStr(stringUserInput, "obce.csv");
        }
        else if (userInput == 2)
        {
            cout << "Zadajte re�azec, ktor� m� vyh�ad�van� v�raz obsahova�: " << endl;
            cin.ignore();
            getline(cin, stringUserInput);
            cout << "N�jden� kraje: " << endl << "\n";
            containsStr(stringUserInput, "kraje.csv");
            cout << "N�jden� okresy: " << endl << "\n";
            containsStr(stringUserInput, "okresy.csv");
            cout << "N�jden� obce: " << endl << "\n";
            containsStr(stringUserInput, "obce.csv");
        }
        else if (userInput == 3)
        {
            break;
        }
        else
        {
            cout << "Zadali ste nespr�vny vstup!" << endl;
        }
    }
}

