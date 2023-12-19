#include "../include/user.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <game.h>
using std::pair;

user:: user(string userName, string password):userName(userName),password(password), nameGameVSgame(),isactive(false),waitForReceipt(){};
user::~user(){nameGameVSgame.clear();}

string user::getUserName(){return userName;}
string user::getPassword(){return password;}
    
void user::joinAgame(string gameName,game g){
    nameGameVSgame.insert(pair<string, game>(gameName,g));
}
void user::exitAgame(string gameName){
    nameGameVSgame.erase(gameName);
}
bool user::gameExist(string gameName){
    auto search = nameGameVSgame.find(gameName);
    if(search != nameGameVSgame.end())
        return true;
    else return false;

}

void user::setActive(bool active){
    if(active)
        isactive=true;
    else isactive=false;

}

std::map<string,game>& user::getMap(){
    return nameGameVSgame;
}

game user::getGame(string gameName){
    std::map<string,game> ::iterator it;
    it=nameGameVSgame.find(gameName);
    game theGame= it->second;
    return theGame;
}
void user::addEventToGame(string gameName, string event, string theUser){
    std::map<string,game> ::iterator it;
    it=nameGameVSgame.find(gameName); //find the correct game 
    game theGame= it->second;   
    theGame.addEvent(theUser, event); //add the event to the fit username

  
}
bool user::isActive(){
    return isactive;
}
string user::getKind(int receipId){
    auto kind =waitForReceipt.find(receipId)->second;
    return kind;
}
int user::getSubId(string gameName){
    auto curr = nameGameVSgame.find(gameName);
    if (curr != nameGameVSgame.end()){
        int output = curr->second.getSubId();
        return output;
    }
    return -1; 

}



void user::addReciept(int receiptId, string val){
    waitForReceipt.insert(pair<int,string>(receiptId,val));

} 


    