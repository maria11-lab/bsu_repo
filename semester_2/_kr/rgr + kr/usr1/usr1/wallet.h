#pragma once
#include <iostream> 

class Wallet {
private:
	int64_t total_;

	Wallet(int64_t);
public: 
	Wallet();
	Wallet(int, int, double);

	Wallet(const Wallet&);
	Wallet& operator=(const Wallet&);

	Wallet operator -() const;

	Wallet operator -(const Wallet&) const;
	Wallet operator +(const Wallet&) const;
	
	Wallet& operator -=(const Wallet&);
	Wallet& operator +=(const Wallet&);

	bool operator ==(const Wallet&);
	bool operator >(const Wallet&);

	friend std::ostream& operator<<(std::ostream&, const Wallet&);
};

