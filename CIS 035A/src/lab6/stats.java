/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 6
 * Due Date: Feb 23, 2010
 * Date Submitted: Feb 23, 2010
 */

package lab6;
/**
 * Contains methods for displaying the statistics of tests, for Lab 6
 * of CIS 035A-63Z
 * @author John Towler
 * @version 1.0
 */

public class stats {
    /**
     * Will search through all test scores, and return the highest score
     * for each test.
     * @param students A student[] containing all students.
     * @return An int[] containing the highest score for all tests.
     */
    static int[] high(student[] students){
        int[] high = new int[students[0].getNumScores()];
        int newscore = 0;

        for(int i = 0; i < students[i].getNumScores(); i++){
            high[i] = 0;
            for(student x : students){
                newscore = x.getScore(i);
                if (newscore > high[i]) high[i] = newscore;
            }
        }
        return high;
    }
    /**
     * Will search through all test scores, and return the lowest score
     * for each test.
     * @param students A student[] containing all students.
     * @param num_tests The number of tests each student has.
     * @return An int[] containing the lowest score for all tests.
     */
    static int[] low(student[] students){
        int[] low = new int[students[0].getNumScores()];
        int newscore = 0;

        for(int i = 0; i < students[0].getNumScores(); i++){
            low[i] = 100;
            for(student x : students){
                newscore = x.getScore(i);
                if (newscore < low[i]) low[i] = newscore;
            }
        }
        return low;
    }
    /**
     * Will search through all test scores, and return the average of all
     * scores for each test.
     * @param students A student[] containing all students.
     * @param num_tests The number of tests each student has.
     * @return A double[] containing the average score for all tests.
     */
    static double[] avg(student[] students){
        double[] avg = new double[students[0].getNumScores()];

        for(int i = 0; i < students[0].getNumScores(); i++){
            avg[i] = 0;
            for(student x : students){
                avg[i] += x.getScore(i);
            }
            avg[i] /= students.length;
        }
        return avg;
    }
}
