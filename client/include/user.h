#pragma once

#include <string>
using std::string;
#include <vector>
#include <map>
// #include <iostream>
#include <game.h>

using std::string;
using namespace std;


class user{
    private:
    
    string userName;
    string password;
    std::map<string,game> nameGameVSgame; //<name_game,game>
    bool isactive; 
    map<int,string> waitForReceipt;
    
    public:
    user(string userName, string password); 
    ~user(); 
    string getUserName();
    string getPassword();
    void joinAgame(string gameName,game g);
    void exitAgame(string gameName);
    bool gameExist(string gameName);
    void setActive(bool isActive); 
    std::map<string,game>& getMap(); 
    game getGame(string gameName); 
    void addEventToGame(string gameName, string event, string theUser);
    bool isActive();
    string getKind(int receipId);
    int getSubId(string gameName); 
    void addReciept(int receiptId, string val); 
   

};