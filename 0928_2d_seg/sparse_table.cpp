// idempotent
// min, max, gcd, bitwise AND, bitwise OR, lcm

#include <bits/stdc++.h>
using namespace std; 

typedef long long ll; 

vector<vector<ll>> get_table(vector<ll> &values){

    int n = values.size(); 

    vector<vector<ll>> result = {values, };
    vector<ll>         prev   = values;  

    for(int len=2; len<=n; len*=2){

        vector<ll> curr = {}; 

        for(int i=0;i+len<=n;i++){

            curr.push_back(max(
                prev[i], 
                prev[i+len/2]
            )); 

        }

        result.push_back(curr); 
        prev = curr; 

    }

    return result; 

}

/*

            i         i+len/2      i+len
            |            |           |
 len    :   [========================)
 len/2  :   [===========)[===========) ---> prev[i], prev[i + len/2]

*/

ll query(
    vector<vector<ll>> &table, 
    int l, int r
){

    int len = r - l + 1; 
    int msb = __lg(len); 

    return max(
        table[msb][l],
        table[msb][r - (1<<msb) + 1] 
    ); 

}

/*

            l                          r
            |                          |
 range  :   [==========================]
 left   :   [===============)            ---> table[k][l]
 right  :              [===============] ---> table[k][r - 2^k + 1]

*/