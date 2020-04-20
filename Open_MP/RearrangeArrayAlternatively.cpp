#include <iostream>
using namespace std;

void rearrange(int array[], int size){
    int reArray[size];
    int i = 0, j = size-1, index = 0;
/*this whole thing can be written as */
    while(j > i){
        reArray[index] = array[j];
        reArray[index+1] = array[i];
        index += 2;
        i++;
        j--;
    }
    if (j == i){
        reArray[size-1]  = array[j];
    }

    /*This is a copy of uppper part*/
//    int flag = true;
//    for (int k=0; k<size; k++)
//    {
//        if (flag)
//            reArray[k] = array[j--];
//        else
//            reArray[k] = array[i++];
//
//        flag = !flag;
//    }

    for(i= 0 ; i < size ; i++){
        cout << reArray[i] << " ";
    }
}


int main(){
    int testCase;
    cin >> testCase;
    while(testCase--){
        int size;
        cin >> size;
        int *array = new int[size];
        for(int i = 0 ; i < size ; i++){
            cin >> array[i];
        }
        rearrange(array, size);
        cout << endl;
    }
}