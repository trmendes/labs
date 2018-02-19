class base {
	public:
		virtual int metodo_1();
		virtual auto metodo_2() -> int;
};

class heranca: public base {
	public:
		int metodo_1();
		auto metodo_2() -> int;
};
