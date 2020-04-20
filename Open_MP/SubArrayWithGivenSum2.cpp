#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        long long k;
        cin>>n>>k;
        vector<long long> a(n);
        for(int i=0;i<n;i++)
            cin>>a[i];
        int i=0,j=0;
        long long csum=0;
        int s=-1 ,e=-1;
        while(i<n and j<n)
        {
            if(csum<k)
                csum+=a[i];
            //cout<<csum<<" y ";
            while(csum>k and j<n)
            {
                csum-=a[j];
                j++;
            }
            if(csum==k)
            {
                s=j; e=i;
                break;
            }
            i++;
        }
        if(s==-1 || e==-1)
            cout<<"-1\n";
        else
            cout<<s+1<<" "<<e+1<<endl;
    }
    return 0;
}