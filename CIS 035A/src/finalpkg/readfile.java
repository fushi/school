package finalpkg;

import java.io.*;
import java.util.*;

public class readfile {

    public readfile(String filename){
        fFile = new File(filename);
    }

    public person[] process() throws FileNotFoundException{
        Scanner scanner = new Scanner(fFile);
        
        while ( scanner.hasNextLine() ){
            people.add(new person(scanner.nextLine().split(" "))) ;
        }

        return people.toArray(new person[0]);
    }

    private File fFile;
    private ArrayList<person> people = new ArrayList<person>();
}