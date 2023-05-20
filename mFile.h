#pragma once
#include <iostream> //to use cout, cin ...std
#include <math.h>   // to use pow , floor, ceil ...ets
#include <vector>   //to use vector
#include <iomanip>  //to use the setw mainpulator
#include <string>   //to use string methods
#include <cctype>   //to use the char functions
#include <fstream>  // to deal with file
// my libs
#include "mStringLib.h"
using namespace std;

namespace myFiles
{
    const string ClientsFileName = "ClientsData.txt";

    struct sClient
    {
        string AccountNumber;
        string PinCode;
        string Name;
        string Phone;
        double AccountBalance;
        bool MarkForDelete = false;
    };

    sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
    {
        sClient Client;
        vector<string> vClientData;
        vClientData = mString::SplitString(Line, Seperator);
        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]);
        return Client;
    };

    string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
    {
        string stClientRecord = "";
        stClientRecord += Client.AccountNumber + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += Client.Name + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += to_string(Client.AccountBalance);
        return stClientRecord;
    }

    vector<sClient> LoadCleintsDataFromFile(string FileName)
    {
        vector<sClient> vClients;
        fstream MyFile;
        MyFile.open(FileName, ios::in);
        // read Mode
        if (MyFile.is_open())
        {
            string Line;
            sClient Client;
            while (getline(MyFile, Line))
            {
                Client = ConvertLinetoRecord(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    };

    void showAnErrerMesage(string SearchWord)
    {

        cout << "The User With Account Number (" << SearchWord << ") Not Found :(";
    }

    bool SearchToFintTheClient(vector<sClient> vClient, sClient &TheWantedClient, string SearchWord)
    {
        for (sClient Client : vClient)
        {

            if (Client.AccountNumber == SearchWord)
            {
                TheWantedClient = Client;

                return true;
            }
        }

        return false;
    };

    void ShowClientData(sClient Clinet)
    {
        cout << "Account Number : " << Clinet.AccountNumber << endl;
        cout << "Pin Code       : " << Clinet.PinCode << endl;
        cout << "Client Name    : " << Clinet.Name << endl;
        cout << "Client Phone   : " << Clinet.Phone << endl;
        cout << "Account Balance: " << Clinet.AccountBalance << endl;
    }

    bool FindClientByAccountNumber(string AccountNumber, sClient &Client)
    {
        vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
        for (sClient C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                return true;
            }
        }
        return false;
    };

    // done for update and delete
    bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient &Client)
    {
        for (sClient C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                Client = C;

                return true;
            }
        }
        return false;
    }

    bool FileIsEmpty(string FileName)
    {
        fstream MyFile;

        MyFile.open(FileName, ios::in); // read Modeif

        vector<string> FileContent;
        string line;

        while (getline(MyFile, line))
        {
            FileContent.push_back(line);
        }

        if (FileContent.size() > 0)
        {
            MyFile.close();
            return true;
        }
        else
        {
            MyFile.close();
            return false;
        }
    }

    bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients)
    {
        for (sClient C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                return true;
            }
        }
    }

    sClient ReadNewClient(string AccountNumber)
    {
        sClient Client;

        Client.AccountNumber = AccountNumber;

        cout << "Enter PinCode? ";
        getline(cin >> ws, Client.PinCode);

        cout << "Enter Name? ";
        getline(cin, Client.Name);

        cout << "Enter Phone? ";
        getline(cin, Client.Phone);

        cout << "Enter AccountBalance? ";
        cin >> Client.AccountBalance;

        return Client;
    }

    // done
    void PrintClientCard(sClient Client)
    {
        cout << "\nThe following are the client details:\n";
        cout << string(40, '-') << endl;
        cout << "Accout Number: " << Client.AccountNumber;
        cout << "\nPin Code     : " << Client.PinCode;
        cout << "\nName         : " << Client.Name;
        cout << "\nPhone        : " << Client.Phone;
        cout << "\nAccount Balance: " << Client.AccountBalance << endl;
        cout << string(40, '-') << endl;
    };

    // done
    sClient ChangeClientRecord(string AccountNumber)
    {
        sClient Client;

        Client.AccountNumber = AccountNumber;

        cout << "\n\nEnter PinCode? ";
        getline(cin >> ws, Client.PinCode);

        cout << "Enter Name? ";
        getline(cin, Client.Name);

        cout << "Enter Phone? ";
        getline(cin, Client.Phone);

        cout << "Enter AccountBalance? ";
        cin >> Client.AccountBalance;

        return Client;
    }

    // done vector<sClient>
    void SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
    {
        fstream MyFile;

        MyFile.open(FileName, ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open())
        {
            for (sClient &C : vClients)
            {
                if (C.MarkForDelete == false)
                { // we only write records that are not marked for delete.
                    DataLine = ConvertRecordToLine(C);

                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
        // return vClients;
    }

    // done UPDATE
    bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
    {
        sClient Client;

        char Answer = 'n';

        if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        {
            PrintClientCard(Client);

            cout << "\n\nAre you sure you want update this client? y/n ? ";
            cin >> Answer;

            if (toupper(Answer) == 'Y')
            {
                for (sClient &C : vClients)
                {
                    if (C.AccountNumber == AccountNumber)
                    {
                        C = ChangeClientRecord(AccountNumber);

                        break;
                    }
                }
                SaveCleintsDataToFile(ClientsFileName, vClients);

                cout << "\n\nClient Updated Successfully.";

                return true;
            }
            else
            {
                cout << "\nClient Didn't updated \n";
            }
        }
        else
        {
            cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

            return false;
        }
    };

    // done
    bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient> &vClients)
    {
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.MarkForDelete = true;

                return true;
            }
        }
        return false;
    };

    // done DELETE
    bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
    {
        sClient Client;

        char Answer = 'n';

        if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        {
            PrintClientCard(Client);

            cout << "\n\nAre you sure you want delete this client? y/n ? ";

            cin >> Answer;

            if (toupper(Answer) == 'Y')
            {
                MarkClientForDeleteByAccountNumber(AccountNumber, vClients);

                SaveCleintsDataToFile(ClientsFileName, vClients);

                // // Refresh Clients
                vClients = LoadCleintsDataFromFile(ClientsFileName);

                return true;
            }
            else
            {
                cout << "The Client steal exist  \n";
            }
        }
        else
        {
            return false;
        };
    }

    // done  PRINT showClientRecord
    void PrintClientRecord(sClient Client)
    {
        cout << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(40) << left << Client.Name;
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }
    void PrintClientBalance(sClient Client)
    {
        cout << "| " << setw(15) << left << Client.AccountNumber;
        cout << "| " << setw(40) << left << Client.Name;
        cout << "| " << setw(12) << left << Client.AccountBalance;
    }

    //   donw PRINT ShowAllClientsRecord
    void PrintAllClientsData(vector<sClient> vClients)
    {
        cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        for (sClient Client : vClients)
        {
            PrintClientRecord(Client);
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    };
    //   donw PRINT ShowAllClientsRecord
    void PrintTotalBalanceScreen(vector<sClient> vClients)
    {
        cout << "\n\t\t\t\t\tBalance List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        for (sClient Client : vClients)
        {
            PrintClientBalance(Client);
            cout << endl;
        }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    };

    void AddDataLineToFile(string FileName, string stDataLine)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << stDataLine << endl;
            MyFile.close();
        }
    };

    void ShowFileContent(string FileName)
    {

        fstream MyFile;

        MyFile.open(FileName, ios::in); // read mode onle

        if (MyFile.is_open())
        {
            string line;

            while (getline(MyFile, line))
            {
                cout << line << endl;
            }

            MyFile.close();
        }
    }

    // done
    vector<sClient> LaodClientsDataFromFile(string FileName)
    {

        fstream MyFile;

        vector<sClient> vClients;

        MyFile.open(FileName, ios::in); // read mode onle

        if (MyFile.is_open())
        {

            string line;
            sClient Client;

            while (getline(MyFile, line))
            {
                Client = ConvertLinetoRecord(line);

                vClients.push_back(Client);
            }

            MyFile.close();
        }

        return vClients;
    }

    // done
    void LoadDataFromFileToVector(string FileName, vector<string> &vFileContent)
    {

        fstream MyFile;

        MyFile.open(FileName, ios::in); // read mode onle

        if (MyFile.is_open())
        {

            string line;

            while (getline(MyFile, line))
            {
                vFileContent.push_back(line);
            }

            MyFile.close();
        }
    }

    // done
    void AddVectorDataToFile(string FileName, vector<string> &vFileContent)
    {
        fstream MyFile;

        MyFile.open(FileName, ios::out | ios::app); // write mode

        if (MyFile.is_open())
        {

            for (string &Content : vFileContent)
            {
                if (Content != "") // check if the vector item is empty don't push it to the file
                {
                    MyFile << Content << endl;
                }
            };

            MyFile.close();
        }
    }

    void DeleteRecord(string fileName, string Record)
    {
        vector<string> vFileData;
        LoadDataFromFileToVector(fileName, vFileData);

        for (string &Line : vFileData)
        {
            if (Line == Record)
            {
                Line = "";
            }
        }
        AddVectorDataToFile(fileName, vFileData);
    }

    void UpdateRecord(string fileName, string PreveusRecord, string NewRecord)
    {
        vector<string> vFileData;

        LoadDataFromFileToVector(fileName, vFileData);

        for (string &Line : vFileData)
        {
            if (Line == PreveusRecord)
            {
                Line = NewRecord;
            }
        }
        AddVectorDataToFile(fileName, vFileData);
    }
}
