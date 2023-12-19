package bgu.spl.net.srv;

import java.util.HashMap;
import java.util.concurrent.ConcurrentHashMap;

public class signInUsers {
    static private ConcurrentHashMap<String,String > myMap= new ConcurrentHashMap<>();

    static public void add(String userName,String password ){
        myMap.put(userName, password);

    }

   
    static public boolean isAllreadyExict(String userName){
        if(myMap.containsKey(userName)){
            return true;
        
        }
        return false;
    }

    static public boolean isTheRightPassword(String userName,String password){
        if(myMap.get(userName).equals(password)){
            return true;
        
        }
        return false;
    }

    static public void remove(String userName){
        myMap.remove(userName);

    }


}
