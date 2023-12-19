package bgu.spl.net.srv.ServerFrames;

public class ConnectedFrame {
    private String title;
    private String version;
      

    public ConnectedFrame (String version){
        this.version = version;
        title = "CONNECTED"; 
    }

    public String toString(){
        String output = title + "\n" + "version:" + version + "\n\n" + '\u0000';
        return output; 
    }
}
