#include <QApplication>
#include <QPushButton>
#include <QTimer>
#include <iostream>

using namespace std;

void test_function();
void test_function_timeout();

void test_function(){
	cout << "bla\n";
	return;
}

void test_function_timeout(){
	cout << "bla timeout\n";
	return;
}

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	QFont font("Courier");
	QIcon icon("./icon.png");
	QPushButton btn;
	QObject::connect(&btn, &QPushButton::clicked, test_function);

	QTimer * timer = new QTimer(nullptr);

	timer->start(2000);

	QObject::connect(timer, &QTimer::timeout, test_function_timeout);

	font.setBold(true);
	font.setPixelSize(30);

	btn.setIcon(icon);
	btn.setFont(font);
	btn.setText("Oi Mundo");
	btn.setToolTip("Pois eh...estou aqui");
	btn.show();

	return app.exec();
}
