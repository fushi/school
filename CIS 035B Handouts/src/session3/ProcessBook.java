package session3;

// Session 3
//
public class ProcessBook {

	private Book book;

	public ProcessBook(Book bk) {
	    book = bk;
	}

	// The caller of this method needs to handle the
	// exception it's throwing. BookException is a 
	// checked exception.
	//
	public boolean isAvailable() throws BookException {
	    int onHand = book.getNumOnHand();
	    if(onHand > 0)
		    return true;
	    else
		if(onHand == 0)
		    return false;
	        else
		    throw new BookException(book);
	}

	public void checkBookId() throws BookException {
		String id = book.getId();
		if (!id.startsWith("B"))
			throw new BookException(book);
	}

	// To test enter the following when executing:
        // java ProcessBook 275 "P. Buck" "The Good Earth" N1 -3
	// 
	public static void main(String[] arg) {
		Book b = new Book(Integer.parseInt(arg[0]), arg[1],
				   arg[2], arg[3]);
		b.setNumOnHand(Integer.parseInt(arg[4]));
		ProcessBook pb = new ProcessBook(b);
		try {
		   if (pb.isAvailable())
		       System.out.println("Got it.");
		   else
			System.out.println("Out of stock.");
		}catch (BookException bex) {
			Book bk = bex.getBook();
			System.out.println("Bad on hand value: " +
					    bk.getNumOnHand());
		}
		try {
		       pb.checkBookId();
		       System.out.println("Book ID is valid");
		}catch (BookException bex) {
			Book bk = bex.getBook();
			System.out.println("Bad book ID: " +
					    bk.getId());
		}
	}
}
