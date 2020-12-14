package number_finder;

public class Finder {
	
	public Finder(int minimum, int maximum){
		min = minimum;
		max = maximum;
	}

	public int guess(){
		guess = (max + min) / 2;
		return guess;
	}
	
	public int getMax(){
		return max;
	}
	
	public int getMin(){
		return min;
	}
	
	public void isHigher(){
		min = guess;
	}
	
	public void isLower(){
		max = guess;
	}

	
	int guess;
	int max;
	int min;
	
	static public void main(String [] argv){
		Finder f = new Finder(1,100);
		
		int answer = 32;
		int guesses = 0;
		int guess;
		
		do{
			guesses++;
			
			guess = f.guess();
			
			System.out.println("My guess is " + guess);
			
			if(guess > answer){
				System.out.println("Your number is lower than " + guess);
				f.isLower();
			}
			if(guess < answer){
				System.out.println("Your number is higher than " + guess);
				f.isHigher();
			}
			
		}while(f.guess != answer);
		
		System.out.println("You got it right in " + guesses + " guesses!");
	}
}
