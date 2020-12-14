/*
 * InfoServlet.java
 *
 */

package session10;

import java.io.*;
import java.net.*;

import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
/**
 *
 * @author Rolly
 *  Include the following initial parameters in web.xml:
 *      hostname=<your hostname>
 *      port=8080
 *  Invoke this servlet like so:
 *  http://localhost:8080/<proj name>/InfoServlet?param1=hello&param2=deanza
 */
public class InfoServlet extends HttpServlet {
    
    Enumeration initParams;
    String servletName;

     public void init() {
	   // Look for these parameters in the web descriptor: web.xml file.
	   // Both methods below are inherited from the GenericServlet
	   // class which is the parent class of HttpServlet.
	   initParams = getInitParameterNames();
	   servletName = getServletName();
     }
     
    /** Processes requests for both HTTP <code>GET</code> and <code>POST</code> methods.
     * @param request servlet request
     * @param response servlet response
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        /* TODO output your page here
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Servlet InfoServlet</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>Servlet InfoServlet at " + request.getContextPath () + "</h1>");
        out.println("</body>");
        out.println("</html>");
         */
        out.close();
    }
    
    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /** Handles the HTTP <code>GET</code> method.
     * @param request servlet request
     * @param response servlet response
     */
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        response.setContentType("text/html");
	PrintWriter out = response.getWriter();
	// What's the <BR> for?
	out.println("Servlet name: " + servletName + "<BR>");
	out.println("Initial parameters:" + "<BR>");
        String host = (String)getInitParameter("hostname");
        out.println("hostname " + host + "<BR>");
	while (initParams.hasMoreElements()) {
		String paramName = (String)initParams.nextElement();
		String value = (String)getInitParameter(paramName);
		out.println("Name: " + paramName + 
			    " Value: " + value + "<BR>");
	}

	out.println ("Client's IP address: " + request.getRemoteHost() + "<BR>");
	out.println ("Server's hostname: " + request.getServerName() + "<BR>");
	out.println ("Server's port: " + request.getServerPort() + "<BR>");
	out.println("Query string parameters:" + "<BR>");

	String [] values1 = request.getParameterValues("param1");
	out.println("param1 values are: <BR>");
	for (int idx = 0; idx < values1.length; ++idx) {
		out.println(values1[idx] + "<BR>");
	}

	String [] values2 = request.getParameterValues("param2");
	out.println("param2 values are: <BR>");
	for (int idx = 0; idx < values2.length; ++idx) {
		out.println(values2[idx] + "<BR>");
	}

	out.println("<HTML>");
	out.println("<BODY>");
	out.println("<FORM METHOD=\"POST\" " +
		"ACTION=\"http://localhost:8080/Servlets/InfoServlet\">");
	out.println("Please enter your name:<BR>");
	out.println("<INPUT TYPE=\"TEXT\" NAME=\"name\" SIZE=\"20\">");
	out.println("<INPUT TYPE=\"SUBMIT\" VALUE=\"Send\">");
	out.println("</FORM>");
	out.println("</BODY>");
	out.println("</HTML>");
    }
    
    /** Handles the HTTP <code>POST</code> method.
     * @param request servlet request
     * @param response servlet response
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        
        response.setContentType("text/html");
	PrintWriter out = response.getWriter();

	String name = request.getParameter("name");
	out.println("Hello, " + name + "!");
    }
    
    /** Returns a short description of the servlet.
     */
    public String getServletInfo() {
        return "Short description";
    }
    // </editor-fold>
}
