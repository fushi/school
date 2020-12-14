/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 1, Project 1
 * Due Date: Jan 18, 2010
 * Date Submitted: Jan 14, 2010
 */

package lab1;

public class lab1project1 {
    public static void main(String[] args) {

        final double price_tv     = 400.00;
        final double price_vcr    = 220.00;
        final double price_remote =  35.20;
        final double price_cd     = 300.00;
        final double price_tape   = 150.00;

        final double tax          = 0.0825;

        int qty_tv     = corejava.Console.readInt("How many TV's were sold? ");
        int qty_vcr    = corejava.Console.readInt("How many VCR's were sold? ");
        int qty_remote = corejava.Console.readInt("How many Remote Controllers were sold? ");
        int qty_cd     = corejava.Console.readInt("How many CD's were sold? ");
        int qty_tape   = corejava.Console.readInt("How many Tape Recorders were sold? ");

        double tv_total     = price_tv * qty_tv;
        double vcr_total    = price_vcr * qty_vcr;
        double remote_total = price_remote * qty_remote;
        double cd_total     = price_cd * qty_cd;
        double tape_total   = price_tape * qty_tape;

        double subtotal     = tv_total + vcr_total + remote_total + cd_total + tape_total;

        corejava.Format.printf("\nQty: %d\n", qty_tv);
        corejava.Format.printf("Desc: %s\n", "TV");
        corejava.Format.printf("Unit Price: %.2f\n", price_tv);
        corejava.Format.printf("Total Price: %.2f\n\n", tv_total);

        corejava.Format.printf("Qty: %d\n", qty_vcr);
        corejava.Format.printf("Desc: %s\n", "VCR");
        corejava.Format.printf("Unit Price: %.2f\n", price_vcr);
        corejava.Format.printf("Total Price: %.2f\n\n", vcr_total);

        corejava.Format.printf("Qty: %d\n", qty_remote);
        corejava.Format.printf("Desc: %s\n", "Remote Control");
        corejava.Format.printf("Unit Price: %.2f\n", price_remote);
        corejava.Format.printf("Total Price: %.2f\n\n", remote_total);

        corejava.Format.printf("Qty: %d\n", qty_cd);
        corejava.Format.printf("Desc: %s\n", "CD Player");
        corejava.Format.printf("Unit Price: %.2f\n", price_cd);
        corejava.Format.printf("Total Price: %.2f\n\n", cd_total);

        corejava.Format.printf("Qty: %d\n", qty_tape);
        corejava.Format.printf("Desc: %s\n", "Tape Recorder");
        corejava.Format.printf("Unit Price: %.2f\n", price_tape);
        corejava.Format.printf("Total Price: %.2f\n\n", tape_total);

        corejava.Format.printf("Subtotal: %.2f\n", subtotal);
        corejava.Format.printf("Tax: %.2f\n", subtotal * tax);
        corejava.Format.printf("Total: %.2f\n", subtotal + (subtotal * tax));
    }

}
