#include <iostream>
#include <vector>


int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr(n);

    for (int i = 0; i < n;++i) {
        std::cin >> arr[i];
    }

    int k;
    std::cin >> k;

    int num;
    for (int i = 0; i < k;++i) {

        std::cin >> num;

        int l = 0;
        int r = n;
        int ind;
        while (r != l) {
            ind = (l + r) / 2;
            if (num <= arr[ind]) {
                r = ind;
            }
            else {
                l = ind + 1;
            }
        }

        if (l == (int)arr.size()) {
            std::cout << "0 " << n << ' ' << n << '\n';
            continue;
        }

        if (arr[l] == num) {
            std::cout << "1 " << r << ' ';

            l = 0;
            r = n;
            while (l < r) {
                ind = (l + r) / 2;
                if (num < arr[ind]) {
                    r = ind;
                }
                else {
                    l = ind + 1;
                }
            }

            if (l == (int)arr.size()) {
                std::cout << n << '\n';
                continue;
            }

            std::cout << l << '\n';

        }
        else {
            std::cout << "0 " << r << ' ' << r << '\n';
        }
    }

    return 0;
}