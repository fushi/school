package session16;
//Session 16
//
import java.awt.event.*;

// This class represents the view in MVC. It displays output
// on standard out. You will be given the opportunity to
// implement a view, like this one, using JFC in Lab4.
//
public class PartView implements ActionListener{

   private PartModel model; 

   //Register this class as a listener of events triggered
   //by PartModel.
   //
   public PartView(PartModel mo) {
	model = mo;
	model.addActionListener(this);
   }

   public void actionPerformed(ActionEvent ae) {
	if (ae.getSource() == model) {
	   System.out.println(model.getPartName()); 
	   System.out.println(model.getPartNum()); 
	}
   } 
}
