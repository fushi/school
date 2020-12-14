package session4;


//Session 4
//
public class Cloner {

   private Book bk;

   public Cloner() {
	bk = new Book(400, "B. Bryson",
		      "A Walk in the Woods", "B12");
   }

   public Book getBook() {
	return bk;
   }

   // Service method that returns a cloned Book object.
   //
   public Book getBookClone() {
	return (Book)bk.clone();
   }

   public static void main(String[] args){

        Cloner cloner = new Cloner();
	Book bk1 = cloner.getBook();
	Book bk2 = cloner.getBook();
	//
	// Test returns true
	if (bk1 == bk2) 
	   System.out.println("bk1 & bk2 are referencing the same object");

	Book bk3 = cloner.getBookClone();
	// 
	// Test returns false
	if (bk1 == bk3) 
	   System.out.println("bk1 & bk3 are referencing the same object");
	else
	   System.out.println("bk1 & bk3 are not referencing the same object");
   }
}
