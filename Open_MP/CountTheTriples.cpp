#include <iostream>
#include <set>
#include <list>
using namespace std;

int main(){
    int testCase;
    cin >> testCase;
    while (testCase--){
        int size;
        cin >> size;
        int * array = new int[size];
        for (int i = 0; i < size ; i ++){
            cin >> array[i];
        }

        set<int> sett;
        for (int j = 0; j < size; j++){
            sett.insert(array[j]);
        }

        int count =0;
        for (int k = 0; k < size ; k++) {
            for (int l = k+1; l < size; l++) {
                if (k != l) {
                    int sum = array[k] + array[l];
                    if (sett.find(sum) != sett.end()) {
                        count++;
                    }
                }
            }
        }

        cout << count;

    }


    return 0;
}