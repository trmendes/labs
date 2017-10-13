using Gtk;

int main(string[] args) {
    /* Init GTK */
    Gtk.init(ref args);
    /* Creates a new GTK Window */
    Gtk.Window win = new Gtk.Window();
    /* Tell it to end whenever the user wants */
    win.destroy.connect(Gtk.main_quit);
    /* Display Window */
    win.show_all();
    /* Start main GUI */
    Gtk.main();
    return 0;
}