/**
 * @author John Towler
 * CIS 035A, Section 63Z
 * Lab 7
 * Due Date: March 5, 2010
 * Date Submitted: March 5, 2010
 */

package lab7;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class myframe extends JFrame implements ActionListener {

		/**
         *
         * @param title Title for the panel
         */
        public myframe(String title){
            setTitle(title);
            setSize(300, 200);
            setDefaultCloseOperation(EXIT_ON_CLOSE);
            setVisible(rootPaneCheckingEnabled);

            panel = new JPanel();

            field = new JTextField();
            field.setColumns(10);
            
            button1 = new JButton("Button 1");
            button1.addActionListener(this);

            button2 = new JButton("Button 2");
            button2.addActionListener(this);

            panel.add(field);
            panel.add(button1);
            panel.add(button2);


            Container contentPane = getContentPane();
            contentPane.add(panel);
        }

        public void actionPerformed(ActionEvent evt){
            Object source = evt.getSource();

            if (source == button1){
                String temp = button2.getText();
                button2.setText(field.getText());
                field.setText(temp);
            }

            if (source == button2){
                String temp = button1.getText();   
                button1.setText(field.getText());
                field.setText(temp);
            }
        }

        private JPanel panel;
        private JTextField field;
        private JButton button1;
        private JButton button2;
        private static final long serialVersionUID = -3755210812884359038L;
}
