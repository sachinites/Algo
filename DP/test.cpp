#include<iostream>
#include<string>
using namespace std;
int minFlips(string arr)
{
    int i,inversion1=0,inversion2=0;
    int n = arr.length();
        for(i=0;i<n;i++)
        {
            if((i%2)==0)
            {
                if(arr[i]!='0')
                    inversion1++;
            }
            else
            {
                if(arr[i]!='1')
                    inversion1++;
            }
        }
        for(i=0;i<n;i++)
        {
            if((i%2)==0)
            {   
                if(arr[i]!='1')
                    inversion2++;
            }
            else
            {
                if(arr[i]!='0')
                    inversion2++;
            }
        }
        
    if(inversion1<inversion2)
        return inversion1;
    else 
        return inversion2;
}
int main()
 {
	//code
    int t,*arr,i,j;
    string N;
    cin>>t;
    while(t--)
    {
        cin>>N;
        cout<<minFlips(N)<<endl;
    }
	return 0;
}
