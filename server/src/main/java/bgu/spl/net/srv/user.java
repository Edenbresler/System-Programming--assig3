package bgu.spl.net.srv;

import java.util.concurrent.ConcurrentHashMap;

import org.omg.CORBA.PUBLIC_MEMBER;

public class user {
    private String userName;
    private String password;
    private boolean isLogIn;
    private ConcurrentHashMap<String,String> mySub ; //with which id(key) i subscribe to topic(value)

 
    public user(String userName, String password){
        this.userName = userName; 
        this.password = password; 
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

    public void removeSub(String subid){
        mySub.remove(subid);
    }

    public void addSub(String subid, String topic){
        mySub.put(subid, topic);
        
    }
}
