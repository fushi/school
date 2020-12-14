package session3;

// Session 3
//
// This class inherits from the Exception class
// which makes it a checked exception. This is
// a customized exception that will be used
// particularly for book processing.
// 
public class BookException extends Exception {

	private Book bk;

	public BookException(Book b) {
	    bk = b;
	}

	public Book getBook() {
	    return bk;
	}

	public String toString() {
	    return bk.toString();
	}
}
