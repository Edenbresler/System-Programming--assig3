package bgu.spl.net.srv.ServerFrames;

public class ErrorFrame {
    private String title; 
    private String message; 
    private String receipt; 


   
    public ErrorFrame(String message, String reciept){
        this.message = message; 
        title = "ERROR";
        this.receipt= reciept;
    }

    public String toString(){
        if(receipt != null){
        String output = title + "\n" +"receipt-id: "+ receipt + "\n" + "message: " +message+ "\n\n" +'\u0000';
        return output;
        }
        String output = title  + "\n" + "message: " +message+ "\n\n" +'\u0000';
        return output;
        
    }


}
