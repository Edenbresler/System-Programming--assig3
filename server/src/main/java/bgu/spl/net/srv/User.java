package bgu.spl.net.srv;

import java.util.concurrent.ConcurrentHashMap;

import org.omg.CORBA.PUBLIC_MEMBER;

public class User {
    private String userName;
    private String password;
    private boolean isLogIn;
    private int connectionId;
    private ConcurrentHashMap<String,String> mySub ; //with which id(value) i subscribe to topic(key)

 
    public User(String userName, String password,int connectionId){
        this.userName = userName; 
        this.password = password; 
        this.connectionId = connectionId;
        this.isLogIn = true; 
        this.mySub = new ConcurrentHashMap<>(); 

    }

    public String getUserName(){
        return userName; 
    }

    public String getpassword(){
        return password; 
    }

    public boolean logIn(){
        return isLogIn; 
    }

    public void setLogIN(){
        if(isLogIn)
            isLogIn = false;
        else isLogIn = true; 
    }

    public void removeSub(String topic){
        mySub.remove(topic);
    }

    public void addSub(String subid, String topic){
        mySub.put(topic, subid);
        
    }
    public int getConnectionId(){
        return connectionId;
    }

    public void setConnectionId(int newId ){
        connectionId = newId; 

    }

    /*return the id-subscribe for the input channel */
    public String getSubscribeForChannel(String channel){
        return mySub.get(channel); 
    }

    /*return the topic for the input sub-id */
    public String getTopicForsubid (String subId){
        for (String topic : mySub.keySet()) {
            if (mySub.get(topic).equals(subId))
                return topic; 
            
        }
        return null; 
    }

    public void clearSubList(){
        mySub.clear();
    }
}


	
