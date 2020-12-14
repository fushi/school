package session21;

import java.util.*;
public class I18NDateTimeClient {
   public static void main(String[] args) {
        try { // Call Web Service Operation
            session21.I18NDateTimeService service =
                new session21.I18NDateTimeService();
            session21.I18NDateTime port = service.getI18NDateTimePort();
            String dateTime = port.getDateTime("tr", "TR", "TR");
            System.out.println("Result = "+dateTime);
        } catch (Exception ex) {
		ex.printStackTrace();
        }
    }
}
