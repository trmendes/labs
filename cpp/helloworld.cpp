#include <iostream>
#include <cstdint>
using namespace std;

class HelloWorld {
    int32_t language;

    public:
    void set_language(int32_t lang_code);
    void get_language_list();
    void to_string();
};

void HelloWorld::set_language(int32_t lang_code) {
    language = lang_code;
}

void HelloWorld::get_language_list() {
    cout << "Portuguese: 1\n";
    cout << "English   : 2\n";
}

void HelloWorld::to_string() {
    switch (language) {
	case 1:
	    cout << "Ola Mundo\n";
	    break;
	case 2:
	    cout << "Hello World\n";
	    break;
    }
}

int main() {
    HelloWorld obj;
    obj.get_language_list();
    obj.set_language(1);
    obj.to_string();
    obj.set_language(2);
    obj.to_string();
    return 0;
}