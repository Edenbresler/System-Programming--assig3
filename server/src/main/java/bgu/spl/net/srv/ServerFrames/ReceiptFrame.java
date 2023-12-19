package bgu.spl.net.srv.ServerFrames;

public class ReceiptFrame {
    private String title ;
    private String receiptid;


    public ReceiptFrame(String receiptid){
        this.receiptid= receiptid;
        this.title= "RECEIPT";
    }

    public String toString(){
        String output = title + "\n" + "receipt-id:" + receiptid +"\n\n" + '\u0000';
        return output;
    }
}

