#include <string>
#include <iostream>
#include <omp.h>

using namespace std;

void permute(string a, int l, int r, int k)
{
    k++;
    // Base case  
    if (l == r) {
        cout << a << endl;
        cout << k;
    }
    else
    {
        // Permutations made
        omp_set_num_threads(10000);
       #pragma omp parallel for shared(k)
        for (int i = l; i <= r; i++)
        {
            // Swapping done  
            swap(a[l], a[i]);
            // Recursion called  
            permute(a, l+1, r, k);
            //backtrack  
            swap(a[l], a[i]);
        }
    }
}

// Driver Code  
int main()
{
    double time = omp_get_wtime();
    string str = "ABCDEF";
    int n = str.size();
    permute(str, 0, n-1, 0);
    time = omp_get_wtime() - time;
    cout << time;
    return 0;
}  