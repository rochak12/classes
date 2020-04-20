
#include <iostream>
using namespace std;

// a represents the array
// n : Number of elements in array a
int getMissingNo(int a[], int n)
{
    int i, total=1;

    for ( i = 2; i<= (n+1); i++)
    {
        total+=i;
        total -= a[i-2];
    }
    return total;
}

//Driver Program
int main() {
    int arr[] = { 2, 3, 4, 5};
    cout<<getMissingNo(arr,sizeof(arr)/sizeof(arr[0]));
    return 0;
}
