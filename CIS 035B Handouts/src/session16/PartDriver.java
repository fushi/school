package session16;
//Session 16
//
public class PartDriver {

	public static void main(String[] args) {
	   PartModel model = new PartModel();
	   PartController controller = new PartController(model);
	   controller.buildGUI();
	   PartView view = new PartView(model);
	}
}
