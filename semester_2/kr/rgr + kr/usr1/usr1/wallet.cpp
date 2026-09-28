#include "wallet.h"
#include <algorithm>
#include <numeric>
#include <exception>
#include <cmath>

Wallet::Wallet() : total_(0) {};
Wallet::Wallet(int64_t all) :total_(all) {};
Wallet::Wallet(int pound, int shilling, double pence) {
	if (shilling >= 20 || pence >= 12 ||
		pence * 4 - std::round(pence * 4) > 1e-9 ||
		pound < 0 || shilling < 0 || pence < 0) {
		throw std::exception("\nError! Incorrect format of input data.");
	}
	if (abs(pound) > 1000000000) {
		throw std::exception("\nError! Class out of bounds (greater than 1 billion pounds by absolute value)");
	}
	total_ = pence + shilling * 48 + pound * 960;
}

Wallet::Wallet(const Wallet& other){
	total_ = other.total_;
}
Wallet& Wallet::operator=(const Wallet& other){
	if (this != &other) {
		total_ = other.total_;
	}
	return *this;
}

Wallet Wallet::operator -() const {
	return Wallet(-total_);
}
Wallet Wallet::operator +(const Wallet& other) const{
	Wallet finish(total_ + other.total_);
	return finish;
}
Wallet Wallet::operator -(const Wallet& other) const {
	Wallet finish(total_ - other.total_);
	return finish;
}


Wallet& Wallet::operator+=(const Wallet& other) {
	total_ += other.total_;
	return *this;
}

Wallet& Wallet::operator-=(const Wallet& other) {
	total_ -= other.total_;
	return *this;
}


bool Wallet::operator ==(const Wallet& other) {
	return total_ == other.total_;
}
bool Wallet::operator >(const Wallet& other) {
	return total_ > other.total_;
}

std::ostream& operator<<(std::ostream& out, const Wallet& other) {

	if (other.total_ == 0) {
		out << "0p.";
	}

	int64_t all = other.total_;
	if (all < 0) {
		all = -all;
		out << '-';
	}


	int pound_ = all / 960;
	double rest = all - 960 * pound_;
	int shilling_ = rest / 48;
	int pence_ = rest - 48 * shilling_;

	if (pound_ != 0) {
		out << pound_ << "pd.";
	}
	if (shilling_ != 0) {
		out << shilling_ << "sh.";
	}
	if (pence_ != 0) {
		out << pence_ << "p.";
	}
	out << '\n';
	return out;
}