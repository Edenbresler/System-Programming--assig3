package bgu.spl.net.srv.ServerFrames;

public class MessageFrame {
    private String title;
    private String subscription; 
    private String messageId;
    private String destination;
    private String body;


    public MessageFrame(String subscription, String messageId, String destination, String body ){
        this.subscription = subscription;
        this. messageId= messageId; 
        this.destination= destination;
        this.body=body;
        title = "MESSAGE";
    }

    public String toString(){
        String output = title+ "\n" + "subscription:" +subscription+ "\n"+ "message-id:"+ messageId+"\n"+"destination:"+destination+"\n\n" +body+"\n"+'\u0000';
        return output;
    }
    
}
