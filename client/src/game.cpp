#include "../include/game.h"
#include <string>
using std::string;
using std::pair;
// #include "point.h"
using namespace std;


game:: game(string gameName, int subId): gameName(gameName),subId(subId),userNaVSevents(){};

game::~game(){ 
    for (auto& k: userNaVSevents){
        k.second.clear();
    }
    userNaVSevents.clear();
    }

string game::getGameName(){
 return gameName;
}

void game::addEvent(string userName, string event){
    if(userNaVSevents.find(userName)==userNaVSevents.end()){ // if not exist
        pair<string, vector<string>> newUser;
        newUser.first= userName;
        newUser.second = vector<string>();
        userNaVSevents.insert(newUser);
    }
    userNaVSevents.at(userName).push_back(gameName);

}
//---------------------------------------------------------
int game::getSubId(){return subId;}


bool game::userExist(string userName){  
    if( userNaVSevents.find(userName) != userNaVSevents.end())  //if this user is exist
        return true; 
    return false; 
}


//assume the user is exist
vector<string>& game::getUserVector(string userName){ 
    return userNaVSevents.find(userName)->second;
}