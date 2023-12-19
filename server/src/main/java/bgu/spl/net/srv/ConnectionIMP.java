package bgu.spl.net.srv;

import java.util.LinkedList;
import java.util.concurrent.ConcurrentHashMap;

import bgu.spl.net.srv.ServerFrames.MessageFrame;

public class ConnectionIMP<T> implements Connections {
    private ConcurrentHashMap<String,LinkedList<User>> usersPerTopic ; //<topic, list of the connectioned users>
    private ConcurrentHashMap<Integer, ConnectionHandler<T>> connection;//<connection_ID, ConnectionHandler>
    private signInUsers signInUsers;
    private Integer messageId;  

    public ConnectionIMP(signInUsers signInUsers) {
        usersPerTopic = new ConcurrentHashMap<>();
        connection = new ConcurrentHashMap<>();
        this.signInUsers = signInUsers; 
        messageId = 0; 

    } 
    @Override
    public boolean send(int connectionId, Object msg) {
        ConnectionHandler<T> connectionHandler = connection.get(connectionId);
        if(connectionHandler != null){
            connectionHandler.send((T)msg);
            return true; 
        }
        
        return false;
    }

    @Override
    public void send(String channel, Object msg) {
        // TODO Auto-generated method stub
        LinkedList<User> users =usersPerTopic.get(channel) ;
        if(users !=null){
            for (User user : users) {
                String userSub = user.getSubscribeForChannel(channel);
                MessageFrame toSend = new MessageFrame(userSub, messageId.toString(), channel, (String)msg);
                send(user.getConnectionId(),toSend.toString());
            }
            messageId++; 
        }
        
    }

    @Override
    public void disconnect(int connectionId) {
        User user = getUser(connectionId);
        for (String topic : usersPerTopic.keySet()) {
            usersPerTopic.get(topic).remove(user);
        }
        connection.remove(connectionId);
        if( user != null){
            user.clearSubList();
            user.setLogIN();
        }
       
        
    }

    public void addConnectionHandler(int connectionId, ConnectionHandler<T> con){
        connection.put(connectionId, con);
    }
    
    /*assume the topic is not exsit yet
     */
    public void addTopic(String newTopic){
        usersPerTopic.put(newTopic, new LinkedList<User>());
        
    }

    /*
     * first checking if the topis is exist. if not, add it
     */
    public void addUserToTopic( String topic, User u){
        synchronized(usersPerTopic){
            LinkedList<User> checkIfExist = usersPerTopic.get(topic);
            if ( checkIfExist == null){
                addTopic(topic);
            }
            usersPerTopic.get(topic).add(u);
     }
    }

    public void removeUserFromTopic(String topic, User u){
        usersPerTopic.get(topic).remove(u);
    }


    public signInUsers getUserList(){
        return signInUsers; 
    }


    public User getUser (int connectionId){
        return signInUsers.getUser(connectionId);
    }
   
}
