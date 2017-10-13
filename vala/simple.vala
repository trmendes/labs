using Gtk;

class Simple: Gtk.Window {
    public Simple() {
	/* Tell it to end whenever the user wants */
	this.destroy.connect(Gtk.main_quit);
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