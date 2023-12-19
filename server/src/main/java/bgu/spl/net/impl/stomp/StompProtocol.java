
package bgu.spl.net.impl.stomp;
import bgu.spl.net.api.StompMessagingProtocol; 
import bgu.spl.net.srv.Connections;

import java.lang.String;

import bgu.spl.net.srv.signInUsers;

public class StompProtocol implements StompMessagingProtocol<String>{


    public void start(int connectionId, Connections<String> connections){}
    
    public void process(String message){ //massage = frame. we need to split it, recognize which frame it is and act according to 
        String[] afterSplit = message.split("\n ");
        String kind= afterSplit[0];
        if(kind.equals("CONNECT")){
           String version = afterSplit[1].split(":")[1];
           String host = afterSplit[2].split(":")[1];
           String userName = afterSplit[3].split(":")[1];
           String password = afterSplit[4].split(":")[1];
           
            if(signInUsers.isAllreadyExict(userName)){
                if(signInUsers.isTheRightPassword(userName, password)) {
                    //need to check if  allready connected
                    // if connected - return "allready connected"
                    // if not connected -  we need to connect them and than return "seccesful..."

                }
                else{
                    // return error of "wrong password"
                }
            }
            else{
                // make a new user
                signInUsers.add(userName, password);
            }   
           
        } 
        if(kind.equals("SEND")){
            String topic = afterSplit[1].split(":")[1];
            String Themessage = afterSplit[3];
            //send this message to all the topic'S subscribed

        } 
        if(kind.equals("SUBSCRIBE")){
            String topic = afterSplit[1].split(":")[1];
            String id = afterSplit[2].split(":")[1];
            //add me to the topic's subscribe list
        } 
        if(kind.equals("UNSUBSCRIBE")){
            String id = afterSplit[1].split(":")[1];
        } 
        if(kind.equals("DISCONNECT")){
            //
        } 


        

    }
    
    /**
     * @return true if the connection should be terminated
     */
     public boolean shouldTerminate(){
        return true; ///
    }
    
    public String connectReaction
}