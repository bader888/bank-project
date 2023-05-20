#pragma once
#include <iostream> //to use cout, cin ...std
#include <math.h>   // to use pow , floor, ceil ...ets
#include <vector>   //to use vector
#include <cstdio>   // to use %s , %f , %d
#include <iomanip>  //to use the setw mainpulator
#include <string>   //to use string methods
#include <cctype>   //to use the char functions
#include <fstream>  // to deal with file

using namespace std;

enum enWhatToCount
{
    smallLetter = 0,
    CapitalLetter = 1,
    All = 3,
};

namespace mString
{
    string ReadClientAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

    void PrintEachWordInString2(string s1)
    {
        string delim = " ";
        string word = " ";
        short postion = 0;

        while ((postion = s1.find(delim)) != std::string::npos)
        {
            word = s1.substr(0, postion);

            if (word != " ")
            {
                cout << word << endl;
            }

            s1.erase(0, postion + delim.length());
        }

        if (s1 != " ")
        {
            cout << s1;
        }
    }

    string JoinString(vector<string> vWords, string delim)
    {
        string word;

        for (string &s : vWords)
        {
            word = word + s + delim;
        };

        return word.substr(0, word.length() - delim.length());
    }

    vector<string> SplitString(string S1, string Delim)
    {
        vector<string> vString;
        short pos = 0;
        string sWord;
        // define a string variable
        // use find() function to get the position of the delimiters
        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos);
            // store the word
            if (sWord != "")
            {
                vString.push_back(sWord);
            }
            S1.erase(0, pos + Delim.length());
        }
        if (S1 != "")
        {
            vString.push_back(S1); // it adds last word of the string.
        }
        return vString;
    }

    bool IsVowel(char Character)
    {
        return ((tolower(Character) == 'a') ||
                (tolower(Character) == 'o') ||
                (tolower(Character) == 'u') ||
                (tolower(Character) == 'i') ||
                (tolower(Character) == 'e'));
    };

    short CountLetter(string S1, char Character, bool MatchCase = true)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {

            if (MatchCase)
            {
                if (Character == S1[i])
                    Counter++;
            }
            else
            {
                if (tolower(Character) == tolower(S1[i]))
                    Counter++;
            }
        }

        return Counter;
    }

    short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
    {
        short Counter = 0;
        if (WhatToCount == enWhatToCount::All)
        {
            return S1.length();
        }

        for (int i = 0; i < S1.length(); i++)
        {
            if (WhatToCount == enWhatToCount::CapitalLetter && isupper(S1[i]))
            {
                Counter++;
            }
            if (WhatToCount == enWhatToCount::CapitalLetter && islower(S1[i]))
            {
                Counter++;
            }
        }

        return Counter;
    }

    char InvertLetterCase(char char1)
    {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

    bool IsCharacter(char Character)
    {

        if ((int)Character >= 65 && (int)Character <= 122)
            return true;
        else
            return false;
    }

    char InvertCharcter(char Character)
    {

        while (!IsCharacter(Character))
        {
            cout << "Pleas Enter  Valid Character: \n";

            cin >> Character;
        }

        // lower to capital
        if ((int)Character > 90)
        {
            Character = toupper(Character);
        }
        else
        {
            // capial to lower
            Character = tolower(Character);
        }

        return Character;
    };

    string WordsToUpperCase(string s)
    {

        for (int i = 0; i < s.length(); i++)
        {
            // [s] = [s] - 32;
            // upper = lowerCase - 32 ;
            s[i] = toupper(s[i]);
            ;
        }

        return s;
    }

    string WordsToLowerCase(string s)
    {

        for (int i = 0; i < s.length(); i++)
        {
            // [s] = [s] + 32;
            // lowerCase = upper + 32 ;
            s[i] = tolower(s[i]);
        }

        return s;
    }

    void printName(string name)
    {
        cout << name << endl;
    };

    string PrintFirstLetterOfEachWord2(string s)
    {
        bool IsFirstLetter = true;

        for (int i = 0; i < s.length(); i++)
        {

            if (s[i] != ' ' && IsFirstLetter)
            {
                s[i] = toupper(s[i]);
            }

            IsFirstLetter = (s[i] == ' ' ? true : false);
        }

        return s;
    }

    string ReadString()
    {
        string S1 = "";

        getline(cin, S1);

        return S1;
    };

    char ReadCharacter()
    {
        char character = ' ';

        cout << "Enter The char: \n";

        cin >> character;

        return character;
    };

    string LowecaseFirstLetterOfEachWord(string s)
    {
        bool IsFirstLetter = true;

        for (int i = 0; i < s.length(); i++)
        {

            if (s[i] != ' ' && IsFirstLetter)
            {
                s[i] = tolower(s[i]);
            }

            IsFirstLetter = (s[i] == ' ' ? true : false);
        }

        return s;
    }
}
