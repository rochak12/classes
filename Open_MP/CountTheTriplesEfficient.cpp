#include <iostream>
#include <algorithm>

using namespace std;

int countTriples(int array[], int size){
    sort(array, array+size);
    int count = 0;
    for (int i = size-1; i > 1 ; i --){
        int j = 0;
        int k = i-1;

        while(j < k) {
            if (array[i] > array[j] + array[k])
                j++;
            else if (array[i] < array[j]+ array[k])
                k--;
            else
            { count++; j++; }   //k--;} //keep this since array is sorted
        }
    }
    return count;
}



int main() {
  int testCase;
  cin >> testCase;
  while(testCase--){
      int size;
      cin >> size;
      int * array = new int[size];
      for(int i = 0; i < size; i++){
          cin >> array[i];
      }
      if (int count  = countTriples(array, size))
          cout << (count);
      else
          cout << (-1);
      cout << endl;
  }
}