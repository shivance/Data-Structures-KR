#include <iostream>

using namespace std;

int editDP(string s1,string s2)
{
    int m = s1.length(),n = s2.length();
    int D[m+1][n+1];

    for (int i=0;i<=m;++i)
        D[i][0] = i;

    for (int j=0;j<=n;++j)
        D[0][j] = j;

    for (int i=1;i<=m;++i)
    {
        for (int j=1;j<=n;++j)
        {
            if (s1[i-1]==s2[j-1])
                D[i][j] = D[i-1][j-1]

            else
                D[i][j] = 1 + min(D[i][j-1],D[i-1][j],D[i-1][j-1]);
        }
    }

    return D[m][n];
}

int editRecur(string s1,string s2,int m,int n)
{
    if (m==0) return n; // total insertion
    if (n==0) return m; // total deletion

    if (s1[m-1]==s2[n-1])
        return editRecur(s1,s2,m-1,n-1);

    return 1+min(editRecur(s1,s2,m-1,n),editRecur(s1,s2,m,n-1),editRecur(s1,s2,m-1,n-1));
}



