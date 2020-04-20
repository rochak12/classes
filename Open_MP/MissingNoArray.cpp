#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int testCase;
    cin >> testCase;
    while (testCase--) {
        int size;
        cin >> size;
        int *array = new int(size - 1);
        for (int i = 0; i < size - 1; i++) {
            cin >> array[i];
        }
// There is a seg fault in this.
        sort(array, array+size-1);
        //check
        bool flag1 = false;
        for (int i = 0; i < size - 1; i++) {
            if ((i + 1) != array[i]) {
                flag1 = true;
                cout << i + 1;
                break;
            }
        }
        if (flag1 == false) {
            cout << size;
        }
        cout << endl;
    }
}