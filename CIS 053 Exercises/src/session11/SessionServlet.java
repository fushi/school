/*
 * SessionServlet.java
 *
 * Created on December 20, 2005, 7:20 PM
 */

package session11;

import java.io.*;
import java.net.*;

import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
/**
 *
 * In the SJSAppserver 9, put the JDBC driver jar file in the
 * appserver's domain1/lib directory. Don't forget to re-start
 * the appserver after this.
 *
 * Don't forget to create the initial parameters used by this servlet.
 * http://localhost:8080/<project name>/SessionServlet
 */
public class SessionServlet extends HttpServlet {
       ArrayList <Employee> emps = null;

	public void init() {

		// Look for these values from the deployment descriptor
		// file, web.xml.
		String dbURL = (String)getInitParameter("url");
		String dbDriver = (String)getInitParameter("driver");
		String dbLogin = (String)getInitParameter("login");
		String dbPassword = (String)getInitParameter("password");

		DBProc dbp = new DBProc(dbURL, dbDriver, dbLogin, dbPassword);
		//Get the employees from the employee table.
		emps = dbp.getEmployees();
	}
  
    /** Handles the HTTP <code>GET</code> method.
     * @param request servlet request
     * @param response servlet response
     */
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        response.setContentType("text/html");
	PrintWriter out = response.getWriter();

	//Get current session, create one if it does not exist
	HttpSession session = request.getSession(true);
	String acceptFlag = request.getParameter("accept");

	// No nominees yet, display startup page so user
	// can pick nominees.
	if (acceptFlag == null) {
	   out.println("<HTML>");
	   out.println("<BODY>");

		// Note the method of submission (POST).  This will
		// cause the doPost() method of this servlet to get
	    // invoked.
	   out.println("<FORM METHOD=\"POST\" " +
		"ACTION=\"http://localhost:8080/Servlets/SessionServlet\">");
		  // Display employee choice listing using check boxes.
	   for (int idx = 0; idx < emps.size(); ++ idx) {
		   Employee e = emps.get(idx);
		   String fname = e.getEmpFirstName();
		   String lname = e.getEmpLastName();
		   out.println("<INPUT TYPE=\"CHECKBOX\" NAME=\"name\"" +
			" VALUE=\"" + fname + " " + lname + "\">" +
			fname + " " + lname + "<BR>");
	   }
	   out.println("<INPUT TYPE=\"SUBMIT\" VALUE=\"Send Nominees\">");
	   out.println("</FORM>");
	   out.println("</BODY>");
	   out.println("</HTML>");

	}
		// Nominees were entered. Retrieve them from the
		// session's attributes and display them.
		// Include a link to reload the startup page.
	else {
		  Enumeration en = session.getAttributeNames();
		  out.println("<HTML>");
		  out.println("<BODY>");
		  out.println("<H3>Your nominees are:<BR><BR>");
		  while (en.hasMoreElements()) {
			 String attName = (String)en.nextElement();
                         if (attName.startsWith("nominee"))
			  out.println((String)session.getAttribute(attName) +
						 "<BR>");
		  }
		  out.println("<BR><BR>");
		  // This link will cause the doGet() method of this
		  // servlet to get invoked. No query string parameter
		  // passed.
		  out.println("<a href=\"" +
			"/Servlets/SessionServlet" + "\">" +
			"Reload Page<BR></a>");
		  out.println("</BODY>");
		  out.println("</HTML>");
	}
    }
    
    /** Handles the HTTP <code>POST</code> method.
     * @param request servlet request
     * @param response servlet response
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        response.setContentType("text/html");
	PrintWriter out = response.getWriter();

	HttpSession session = request.getSession(true);

	Enumeration en = session.getAttributeNames();

	// Clean up all the stored session attributes, first.
	// This is in case the user submits nominees multiple
	// times in the same session.
	while (en.hasMoreElements()) {
		 String attName = (String)en.nextElement();
		session.removeAttribute(attName);
	}

	// Retrieve all the names that were picked in the
	// startup page and store them as session attributes.
	String [] empNames = request.getParameterValues("name");
	for (int idx=0; idx < empNames.length; ++idx) {
		session.setAttribute ("nominee" + idx, empNames[idx]);
	}

	out.println("<HTML>");
	out.println("<BODY>");
	out.println("<H3> Your nominees have been accepted.<BR>");
	out.println("<BR><BR>");
	// This will cause the doGet() method of this servlet
	// to be invoked. Notice the parameter in the query string.
	out.println("<a href=\"" +
		"/Servlets/SessionServlet?accept=true" + "\">" +
		"View my nominations...<BR></a>");
	out.println("</BODY>");
	out.println("</HTML>");
    }
    
    /** Returns a short description of the servlet.
     */
    public String getServletInfo() {
        return "Short description";
    }
    
}
