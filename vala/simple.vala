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

	/* Create a Box layout */
	Gtk.Box box = new Gtk.Box(Gtk.Orientation.VERTICAL, 0);

	/* A new Button */
	Gtk.Button add = new Gtk.Button.with_label("ADD");
	Gtk.Button sub = new Gtk.Button.with_label("SUB");

	/* A new Label */
	Gtk.Label label = new Gtk.Label("Value: %d".printf(this.click_counter));

	/* Pack all in our Box Layout */
	box.pack_start(label, false, false, 2);
	box.pack_start(add, false, false, 2);
	box.pack_start(sub, false, false, 2);

	/* Give everything equal space among the window */
	box.set_homogeneous(true);

	/* Add a propose to this button */
	add.clicked.connect(() => {
	    this.add_func();
	    label.set_label("Value %d".printf(this.click_counter));
	});

	sub.clicked.connect(() => {
	    this.sub_func();
	    label.set_label("Value %d".printf(this.click_counter));
	});

	/* Add it to the window */
	this.add(box);

	/* Display Window */
	this.show_all();
    }

    public void add_func() {
	++this.click_counter;
    }

    public void sub_func() {
	--this.click_counter;
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