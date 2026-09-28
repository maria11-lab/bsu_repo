#include "wallet.h"
#include <iostream>
int main()
{
    try {
        Wallet x(0, 19, 0);
        Wallet y(9, 0, 10.5);
        Wallet t(4, 19, 0);
        Wallet z(0, 0, 0);
        Wallet r = -y;
        std::cout << x << y << t << z << r;
    }
    catch (const std::exception& msg) {
        std::cout << msg.what();
    }
}