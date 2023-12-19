#include <StompProtocol.h>
#include <iostream>
#include <sstream>
#include <user.h>
#include <Event.h>
#include <fstream>
#include <ConnectionHandler.h>
using namespace std;
// using std::fstream;

//StompProtocol::StompProtocol( user* theUser, ConnectionHandler& ch):theUser(theUser),ch(ch),receiptId(0), SubId(0), souldTerminate(false){};
StompProtocol::StompProtocol( user& theUser, ConnectionHandler& ch):theUser(theUser),ch(ch),receiptId(0), SubId(0), souldTerminate(false){};

StompProtocol::~StompProtocol(){  
  

}
////-----------------------
string StompProtocol:: hashToString(map<string,string> m){
    string output = "{\n";
    for (auto const& p: m){
        output = output + p.first + ": " + p.second + "\n";
    }
    return output + "}\n";
}

vector<string> StompProtocol:: split(const string &s, char del){
    vector<string> res;
    stringstream ss(s);
    string item;
    while (getline(ss,item,del)){
        res.push_back(item);
    }
    return res; 
}
void StompProtocol::processFromUser(string msg){
    string output; 
    vector<string> vecmsg = split(msg, ' ');
    string command = vecmsg.at(0); 


    if(command.compare("login")==0){
        if(!theUser.isActive()){
            // //split the msg to the information we need 
            int first =vecmsg.at(1).find(':');
            string host = vecmsg.at(1).substr(0, first);
            string port = vecmsg.at(1).substr(first+1, (vecmsg[1].length())-first);
            string userName = vecmsg.at(2);
            string password = vecmsg.at(3);
            //create the frame that we sent to the server
            output= "CONNECT\naccept-version:1.2\nhost:"+host+ "\nlogin:" + userName+"\npasscode:"+password+"\n\n";
            
            //send the frame
            ch.sendLine(output);
        }
        else
            cout<<"The client is already logged in, log out before trying again"<<endl;
    }

    else if(command.compare("join")==0){
        //split the msg to the information we need 
        string gameName = vecmsg.at(1); 

        //create the frame that we sent to the server
        output = "SUBSCRIBE\ndestination:" + gameName + "\nid:" + to_string(SubId) + "\nreceipt:" + to_string(receiptId) +"\n\n";
       
        //send the frame
        ch.sendLine(output);
        //add the receipt
        string add = "join " + gameName + " "+to_string(SubId);
        theUser.addReciept(receiptId,add); 
        
          SubId++;
          receiptId++;

        }

    else if (command.compare("exit")==0){
       //split the msg to the information we need 
        string gameName = vecmsg.at(1);
        int gameSubId = theUser.getSubId(gameName);
        //create the frame that we sent to the server
        output = "UNSUBSCRIBE\nid:" + to_string(gameSubId) + "\nreceipt:" + to_string(receiptId) +"\n\n";
        //send the frame
        ch.sendLine(output);
        //add the receipt
        string add = "exit " + gameName;
        theUser.addReciept(receiptId,add);
        
        receiptId++; 
       
    }

    else if (command.compare("report")==0){
        //string rep = msg.substr(count,msg.length());
        string rep = vecmsg.at(1);
        names_and_events theReport = parseEventsFile(rep); //parser the report
        string strDest= theReport.team_a_name + "_"+ theReport.team_b_name;
        output = "SENT\ndestination:" + strDest +"\n\n";
        string userName = theUser.getUserName();
        //for each event in the vector's events - send a frame
        int size = theReport.events.size();
        for( int i =0; i<size; i++){
            Event currEvent = theReport.events.at(i);
            string gameUp = hashToString(currEvent.get_game_updates());
            string teamAup = hashToString(currEvent.get_team_a_updates());
            string teamBup = hashToString(currEvent.get_team_b_updates());
            string frameBody = "user:"+ userName + "\nteam a: "+currEvent.get_team_a_name() +"\nnteam b: "+currEvent.get_team_b_name()
                               +"\nevent name: " + currEvent.get_name() + "\ntime: " + to_string(currEvent.get_time()) + "\ngeneral game updates:\n" + gameUp
                               + "\nteam a updates:\n" + teamAup +"\nteam b updates:\n"+ teamBup 
                               + "\ndescription:\n"+ currEvent.get_discription();
            output = output + frameBody;
            //send the frame
            ch.sendLine(output);
   
        }
    }


    else if (command.compare( "summery")==0){
        //split the msg to the information we need 
        string gameName = vecmsg.at(1);
        string userName = vecmsg.at(2);
        string file = vecmsg.at(3);

        //check if our user is subscribe to this game and got repotrs from the user he asked to summery
        
        if(theUser.gameExist(gameName)){
            game currGame = theUser.getGame(gameName);
            if (currGame.userExist(userName)) {
                vector<string> userReports = currGame.getUserVector(userName);
                //check if the file is exist - if not create one
                fstream myfile;
                myfile.open(file);
                if(!myfile.is_open())
                    myfile.open(file, ios::out);
                //add the reports from the vector to the filr
                int size1 =userReports.size();
                for(int i =0 ; i<size1; i++){
                    myfile<<userReports.at(i); 
                }
            }
            else  
                printf("You havn't received reports from this user");
        }
        else
            printf("You arn't registered to this game!");

    }

    else if (command.compare("logout")==0){
        theUser.setActive(false); 
        output = "DISCONNECT\nreceipt:-1\n\n";
        ch.sendLine(output);

    }

    else{
        printf("I can't recognize your command, please try again");
    }
}


void StompProtocol::processFromServer(string msg){
   
    auto theFrame =std::vector<std::string> {};
    auto ss = std::stringstream{msg};
    for(std::string line; std::getline(ss,line,'\n');){
        theFrame.push_back(line);

    }

    if(theFrame.at(0) ==  "CONNECTED"){
        cout << "Login successful" << endl;
        theUser.setActive(1);
        
    }
    else if(theFrame.at(0) ==  "MESSAGE"){

        //add the event to the vector in the correct key (game)
        std::string topicLine = theFrame.at(3);
        std::string topic= topicLine.substr(topicLine.find(':')+1); // the topic
        std::string event = theFrame.at(5); // first line of the body
        std::string sendUser= event.substr(event.find(':')+1); //the username how send the event
        int size2 =theFrame.size();
        for(int i=6; i<size2; i++){ //reconstruct the body(the event we need to add)
            event=event +"\n" +theFrame.at(i);

        }
        theUser.addEventToGame(topic,event,sendUser);
    }
    
    else if(theFrame.at(0) ==  "RECEIPT"){
        // if the receipt-id ==-1: delete the user and than do -> ch.close()
        std::string headerReceipt = theFrame.at(1);
        std::string ReceiptId= headerReceipt.substr(headerReceipt.find(':')+1);
        
        if(ReceiptId.compare("-1")==0){ //if disconnect
            souldTerminate=true;
            theUser.setActive(false);
            //theUser.~user();
            ch.close();
        }
        else{
            int receipINT = stoi(ReceiptId);
            string theKind = theUser.getKind(receipINT);
            auto vec =std::vector<std::string> {};
            auto curr = std::stringstream{theKind};
            for(std::string word; std::getline(curr,word,' ');){
                vec.push_back(word);
            }
            if(vec[0].compare("join")==0){
                string gameName = vec[1];
                string SId= vec[2];
                if(! theUser.gameExist(gameName)){
                    game newGame(gameName, stoi(SId));
                    theUser.joinAgame(gameName, newGame);
                    cout << "Joined channel " + gameName << endl;
                }
            }
            
            if(vec[0].compare("exit")==0){
                string gameName = vec[1];
                theUser.exitAgame(gameName);
                cout << "Exited channel " + gameName << endl;
                
            }

        }
    }
    else if(theFrame.at(0) ==  "ERROR"){
        
        std::string headerMessage = theFrame.at(2);
        std::string theMessage= headerMessage.substr(headerMessage.find(':')+1); 
        std::cout << theMessage << endl;
        souldTerminate=true;
        //theUser.~user();
        ch.close();

    }


}



void StompProtocol::runFromUser(){
    while (!theUser.isActive()){

    }
    while(theUser.isActive()){
        string msg;
        getline(cin,msg);
        processFromUser(msg);

    }
   

}

void StompProtocol::runFromServer(){
    while(!souldTerminate){
        string msg;
        ch.getLine(msg);
        if(msg.compare("") !=0){
            processFromServer(msg);
        }

    }
}