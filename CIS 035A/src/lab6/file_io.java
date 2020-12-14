/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 6
 * Due Date: Feb 23, 2010
 * Date Submitted: Feb 23, 2010
 */

package lab6;

import java.io.*;
import java.util.*;

public class file_io {
    static student[] readFile(String filename){
        String line;
        ArrayList<student> students = new ArrayList<student>(0);

        try{
            FileReader fin = new FileReader(filename);
            BufferedReader reader = new BufferedReader(fin);
            reader.readLine(); //Reads, then discards header line.
            for (int i = 0;(line = reader.readLine()) != null; i++){
                StringTokenizer tn = new StringTokenizer(line);

                student temp = new student(tn.countTokens()-1);
                temp.setSid(Integer.parseInt(tn.nextToken()));

                for(int j = 0; tn.countTokens() > 0; j++){
                    int score = Integer.parseInt(tn.nextToken());
                    temp.setScore(score, j);
                }
                students.add(temp);
            }
        }
        catch(IOException e){
            System.out.println("Unable to open "+filename+": "+e.getMessage());
        }

        student[] stud_array = new student[students.size()];
        students.toArray(stud_array);
        return stud_array;
    }

    static void writeFile(student[] students, int[] highs, int[] lows, double[] avgs){
        System.out.printf("%-10s%5s%5s%5s%5s%5s\n", "Student", "Q1", "Q2", "Q3", "Q4", "Q5");
        for(student stu : students){
            System.out.printf("%-10d", stu.getSid());
            for(int i = 0;stu.getNumScores() > i;i++){
                System.out.printf("%5d", stu.getScore(i));
            }
            System.out.printf("\n");
        }
        System.out.printf("%-10s", "High");
        for(int high : highs){
            System.out.printf("%5d", high);
        }
        System.out.printf("\n");

        System.out.printf("%-10s", "Low");
        for(int low : lows){
            System.out.printf("%5d", low);
        }

        System.out.printf("\n");
                System.out.printf("%-10s", "Avg");
        for(double avg : avgs){
            System.out.printf("%5.1f", avg);
        }
        System.out.printf("\n");
    }
}
