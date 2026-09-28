#include <iostream>

#include <cstring>
#include <iostream>

class Message {
private:
	char* text;
	size_t size;
	const int ID;
	Message();
public:
	static int count;
	static int nextID;

	Message(const char* str) :ID(nextID) {
		size = strlen(str);
		text = new char[size + 1];
		for (size_t i = 0; i < size; ++i) {
			text[i] = str[i];
		}
		text[size] = 0;
		+count;
		std::cout << "create massage " << ID;
	}
	Message(const Message& m) :ID(nextID) {
		size = m.size;
		text = new char[size + 1];
		for (size_t i = 0; i < size; ++i) {
			text[i] = m.text[i];
		}
		text[size] = 0;
		+count;
		std::cout << "create massage " << ID;
	}
	Message(Message&& m) :ID(nextID) {
		size = m.size;
		text = m.text;
		m.text = nullptr;
		++count;
		std::cout << "Move massage " << ID;
	}
	Message& operator=(Message&& m) {
		if (&m != this) {
			delete[] text;
			size = m.size;
			text = m.text;
			m.text = nullptr;
		}
		return *this;
	}

	Message& operator=(const Message& m) {
		if (&m != this) {
			delete[] text;
			size = m.size;
			text = new char[size + 1];
			for (size_t i = 0; i < size; ++i) {
				text[i] = m.text[i];
			}
			text[size] = 0;
		}
		return *this;
	}
	~Message() {
		delete[]text;
		--count;
		std::cout << "Delete message " << ID;
	}
	size_t getSize()const { return size; }
	size_t getID()const { return ID; }
	char* getText()const { 
		char* tmp = new char[size + 1];
		for (size_t i = 0; i < size; ++i) {
			tmp[i] = text[i];
		}
		tmp[size] = 0;
		return tmp;
	}
	void setText(const char* str) {
		delete[] text;
		size = strlen(str);
		text = new char[size + 1];
		for (size_t i = 0; i < size; ++i) {
			text[i] = str[i];
		}
		text[size] = 0;
	}
	friend std::ostream& operator<<(std::ostream& out, const Message& m) {
		out << "Message " << m.ID << ':' << m.text << '\n';
		return out;
	}
};


int Message::count = 0;
int Message::nextID = 1;


class Messenger {
	Message msg;
public:
	Messenger(Message m) :msg(m) {};
	void SendMessage() const {
		std::cout << "Send message " << msg.getID() << ':' << msg.getText();
	}
};

int main()
{
	Message mi("Hello, world");
}
