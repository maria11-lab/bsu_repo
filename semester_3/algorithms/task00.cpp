#include <iostream>
#include <fstream> 
#include <set>

int main()
{
    std::ifstream in("input.txt");
    std::set<int> base;

    try {

        if (!in.is_open()) {
            throw '1';
        }

        if (in.peek() == std::ifstream::traits_type::eof()) {
            throw'1';
        }

        int x;
        while (in >> x) {
            base.insert(x);
        }

        long long s = 0;
        for (size_t i : base) {
            s += i;
        }
        std::ofstream out("output.txt");
        out << s;
        out.close();


        std::cout << "yes";
    }
    catch (const char* a) {
        std::cout << "no";
        return 1;
    }
}