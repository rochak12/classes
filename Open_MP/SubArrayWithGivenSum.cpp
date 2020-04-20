//
// Created by Rochak on 7/25/2019.
//

#include <stdio.h>
//#include <bits/stdc++.h>
#include <iostream>
using namespace std;


int main() {
    //code
    int testNumber = 0;
//	std::cout << "enter a number of Test case:" << endl;
    std::cin >> testNumber;
    int length[testNumber], sum[testNumber];
    int **array = new int*[testNumber];

    for (int x = 0; x < testNumber ; x++) {
        // cout << "enter a length of input integer and enter the sum you want for respective test case:" << endl;
        cin >> length[x];
        cin >> sum[x];
       // dynamic allocation of pointer
        array[x] = new int[length[x]];

        int y = 0;
        while (y < length[x]) {
            cin >> array[x][y];
            y++;
        }
    }



    for (int i = 0; i < testNumber; i++){
    int sumL = 0;
    int sub = 0;
        for (int j = 0; j < length[i]; j++){
            sumL += array[i][j];

            while (sumL > sum[i]){
                sumL -= array[i][sub];
                sub++;
            }
            if (sumL == sum[i]){
                cout << sub+1 << " " << j+1 << "\n";
                return (sub+1, j+1);
            }
        }
        return -1;
    }


}