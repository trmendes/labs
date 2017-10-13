using Gtk;

class Simple: Gtk.Window {

    private int click_counter = 0;

    public Simple() {
	/* Set a title to my window */
	this.title = "My first Vala App";
	/* Center it :O */
	this.window_position = WindowPosition.CENTER;
	/* Define a size to it */
	this.set_default_size(350, 70);

	/* Tell it to end whenever the user wants */
	this.destroy.connect(() => {
	    stdout.printf("Bye...\n");
	    Gtk.main_quit();
	});

	/* A new Button */
	Gtk.Button btn = new Gtk.Button.with_label("Simple Button");

	/* Add a propose to this button */
	btn.clicked.connect(() => {
	    btn.set_label("Click me (%d)".printf(++this.click_counter));
	});

	/* Add it to the window */
	this.add(btn);

	/* Display Window */
	this.show_all();
    }
}

int main(string[] args) {
    /* Init GTK */
    Gtk.init(ref args);
    /* Create a new Simple object */
    Simple simple = new Simple();
    /* Start main GUI */
    Gtk.main();
    return 0;
}