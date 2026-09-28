#include <iostream>
#include <vector>

int main()
{

    int n;
    std::cin >> n;

    std::vector<int> arr(n);
    std::vector<int> result(n);
    std::vector<int> ind(n);

    for (int i = 0; i < n;++i) {
        std::cin >> arr[i];
    }

    if (n == 2) {
        std::cout << "-1";
        return 0;
    }

    if (n == 1) {
        std::cout << arr[0] << "\n1";
        return 0;
    }

    result[0] = arr[0];
    result[1] = -1;
    result[2] = arr[0] + arr[2];
    ind[2] = 0;

    for (int i = 3; i < n; ++i) {
        if (result[i - 3] > result[i - 2]) {
            result[i] = result[i - 3] + arr[i];
            ind[i] = i - 3;
        }else{
            result[i] = result[i - 2] + arr[i];
            ind[i] = i - 2;
        }
    }
    std::cout << result[n - 1]<<'\n';

    std::vector<int> way;
    size_t index = n - 1;

    while (index!=0){
        way.push_back(index + 1);
        index = ind[index];
    }

    way.push_back(1);
    std::reverse(way.begin(), way.end());

    for (int i=0;i<way.size();i++){
        std::cout << way[i]<<' ';
    }

    return 0;
}
