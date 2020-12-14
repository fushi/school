/*
 * SampleServlet.java
 *
 */
/*
 *To create a NetBeans project:
 *File - > New Project -> Web -> Web Application 
 *    Name the project: 'Servlets'
 *To create this servlet:
 *    - Create a new package, 'session9', under Source Packages
 *    - Create this servlet under the package you created:
 *         - Right-click on session9 -> New -> Servlet
 *         - Servlet Name: SampleServlet
 *To build the project:
 *    - Compile the servlet
 *    - Right-click on the project node -> Build Project
 *    - Right-click on the project node -> Verify Project
 *To deploy the project:
 *    - Make sure the appserver is running:
 *      - Click on the Runtime tab
 *      - Right-click on the Sun Java System Application Server
 *      - Choose Stop/Start Server...
 *    - Right-click on the project node -> Deploy Project
 *To verify that the project deployed:
 *    - Bring up web browser.  http://localhost:4848
 *    - Enter admin login and password
 *    - Click on the Web Applications link
 *To invoke this servlet:
 *    - Bring up web browser.  http://localhost:8080/<proj name>/SampleServlet
 *
 */
package session9;

import java.io.*;
import java.net.*;

import javax.servlet.*;
import javax.servlet.http.*;

/**
 *
 * @author Rolly
 * @version
 */
public class SampleServlet extends HttpServlet {
    
        String msg = null;

	// The webserver will call this method once.  Then,
	// the servlet will wait for requests until it gets
	// unloaded by the webserver.  This servlet's destroy()
	// method get's called before it is unloaded.
	//
	public void init() {
	    msg = "Hello World";
	}
    /** Processes requests for both HTTP <code>GET</code> and <code>POST</code> methods.
     * @param request servlet request
     * @param response servlet response
     */
    protected void processRequest(HttpServletRequest request, 
                                  HttpServletResponse response, String operation)
    throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Servlet SampleServlet</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>Message is: " + msg + operation + "</h1>");
        out.println("</body>");
        out.println("</html>");
        
        out.close();
    }
    
    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /** Handles the HTTP <code>GET</code> method.
     * @param request servlet request
     * @param response servlet response
     */
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        processRequest(request, response, " from doGet()");
    }
    
    /** Handles the HTTP <code>POST</code> method.
     * @param request servlet request
     * @param response servlet response
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        processRequest(request, response, " from doPost()");
    }
    
    /** Returns a short description of the servlet.
     */
    public String getServletInfo() {
        return "Short description";
    }
    // </editor-fold>
}
