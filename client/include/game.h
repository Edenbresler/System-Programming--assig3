#pragma once
#include <string>
using std::string;
#include <vector>
#include <map>
#include <iostream>
using namespace std;


class game{
    private:

    string gameName; 
    int subId;
    std::map<string,vector<string>> userNaVSevents; //<userName,eventsFromUser>

    public:
    game(std::string gameName, int subId);
    virtual ~game();

    string getGameName();
    
    void addEvent(string userName, string event);
    //---------------------------

    int getSubId();

    bool userExist(string userName);

    vector<string>& getUserVector(string userName);
};