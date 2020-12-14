/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 6
 * Due Date: Feb 23, 2010
 * Date Submitted: Feb 23, 2010
 */

package lab6;

public class student {

    public student(int num_scores){
        scores = new int[num_scores];
    }

    public void setScore(int score, int test){
        scores[test] = score;
    }

    public int getScore(int test){
        return scores[test];
    }
    public void setSid(int new_sid){
        sid = new_sid;
    }
    public int getSid(){
        return sid;
    }
    public int getNumScores(){
        return scores.length;
    }
    private int[] scores;
    private int sid;
}
