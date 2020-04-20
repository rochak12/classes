#include <iostream>
#include <list>
using namespace std;

int maxSum(int array[], int size) {
    list<int> myList;
    if (array) {
        int max_ = array[0];
        int maxFinal = max_;
        for (int i = 1; i < size; i++) {
            max_ = max(array[i], max_ + array[i]);
            maxFinal = max(max_, maxFinal);
        }
        return maxFinal;
    }
    return -1000;
}

int main(){
  int testCase;
  cin >> testCase;
  while(testCase--) {
      int size;
      cin >> size;
      int *array = new int[size];

      for (int i = 0 ; i < size; i++) {
          cin >> array[i];
      }
      cout << maxSum(array, size);
      cout << endl;
  }
}

