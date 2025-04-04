// PermaBlockVisualStudio.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <string>


using namespace std;

// open a connection to the host file

bool isAdministrator()
{
   return geteuid()==0;
}

bool checkForDupes(fstream &hostfile)
{
    string line;
    while (getline(hostfile, line))
    {
        cout << line << endl;
    }
    return true;
}


void blockGivenFile()
{
    const std::string file_path = "/private/etc/hosts";
    std::fstream hostFile(file_path, ios::app);
    if (isAdministrator())
    {
        if (hostFile.is_open())
        {
            // now that the file is open, append the text that blocks tiktok
            string blockedSite;
            while(true)
            {
                cout<<"Please enter the full URL of the site you want blocked (example: www.youtube.com, not youtube.com) and type 'quit' to quit "  <<endl;
                getline(cin, blockedSite);
                blockedSite.erase(0,blockedSite.find_first_not_of(" \t\n\r"));
                blockedSite.erase(blockedSite.find_last_not_of(" \t\n\r") + 1);
                if(blockedSite!="quit" && blockedSite!= ""){
                    hostFile << "127.0.0.1 " << blockedSite << endl;
                    cout << " " << blockedSite << " is now blocked" << endl;
                }
                else{
                    break;
                }
            }
            // hostFile << "127.0.0.1" << " www.tiktok.com" << endl;
            // hostFile << "127.0.0.1" << " tiktok.com" << endl;
            // hostFile << "127.0.0.1" << " api.tiktok.com" << endl;
            // hostFile << "127.0.0.1" << " m.tiktok.com" << endl;
            // hostFile << "127.0.0.1" << " v16m.tiktok.com" << endl;
            // hostFile << "127.0.0.1" << " mon.musical.ly" << endl;
           // cout << "www.tiktok.com" << " is blocked until restart" << endl;
        }
        else
        {
            cout << "Connection to Host File Failed" << endl;
        }
    }
    else
    {
        cout << "You do not have Admin Status. Please run this program as administrator" << endl;
    }
    hostFile.close();
    string command = "sudo dscacheutil -flushcache; sudo killall -HUP mDNSResponder";
    int result = system(command.c_str()); // Execute the command
}

int main()
{
    blockGivenFile();
    return 0;
}