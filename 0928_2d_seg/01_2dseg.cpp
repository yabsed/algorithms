#include <bits/stdc++.h>
using namespace std; 

const int MAXN = 1000; 

int n, m; 

long long arr[MAXN][MAXN]; 
long long seg[4*MAXN][4*MAXN]; 

// build

void build_y(
    int ix, int lx, int rx,
    int iy, int ly, int ry
){  

    // base case of y axis
    if (ly == ry) {
        if (lx == rx){
            seg[ix][iy] = arr[lx][ly]; 
        } 
        else {
            seg[ix][iy]
            = seg[2*ix][iy]
            + seg[2*ix+1][iy]; 
        }
    }
    else {
        int my = (ly + ry) / 2; 

        build_y(
            ix, lx, rx, 
            2*iy, ly,  my
        ); 

        build_y(
            ix, lx, rx, 
            2*iy+1, my+1, ry
        ); 

        seg[ix][iy]
        = seg[ix][2*iy]
        + seg[ix][2*iy+1]; 
    }
}

void build_x(
    int ix, int lx, int rx 
){
    if (lx != rx){

        int mx = (lx + rx) / 2; 

        build_x(2*ix, lx, mx); 
        build_x(2*ix+1, mx+1, rx); 
    }

    build_y(
        ix, lx, rx, 
        1, 0, m-1
    ); 
}

// search

int xa, xb; 
int ya, yb;

long long search_y(
    int ix, 
    int iy, int ly, int ry
)
{
    if (ry < ya || yb < ly) return 0; 

    else if (ya <= ly  && ry <= yb){
        return seg[ix][iy]; 
    }

    else {
        int my = (ly + ry) / 2; 
        
        long long result = 0; 

        result += search_y(
            ix, 
            2 * iy, ly, my
        );  

        result += search_y(
            ix, 
            2 * iy + 1, my + 1, ry
        ); 

        return result; 
    }
}

long long search_x(
    int ix, int lx, int rx
)
{
    if (rx < xa || xb < lx) return 0; 

    else if (xa <= lx && rx <= xb){
        return search_y(
            ix,
            1, 0, m-1
        ); 
    }

    else {
        int mx = (lx + rx) / 2; 
        
        long long result = 0; 

        result += search_x(
            2* ix, lx, mx
        ); 

        result += search_x(
            2 * ix +1, mx+1, rx 
        ); 

        return result; 
    }
}

// update

int ux, uy; 
long long value; 

void update_y(
    int ix, int lx, int rx,
    int iy, int ly, int ry
)
{
    if (ly == ry) {
        if (lx == rx) {
            seg[ix][iy]
            = arr[ux][uy] = value;
        }
        else {
            seg[ix][iy]
                = seg[2*ix][iy]
                + seg[2*ix+1][iy];
        }
        return;
    }

    int my = (ly + ry) / 2;

    if (uy <= my)
        update_y(ix, lx, rx,
                 2*iy, ly, my);
    else
        update_y(ix, lx, rx,
                 2*iy+1, my+1, ry);

    seg[ix][iy]
        = seg[ix][2*iy]
        + seg[ix][2*iy+1];
}

void update_x(int ix, int lx, int rx)
{
    if (lx != rx) {
        int mx = (lx + rx) / 2;

        if (ux <= mx)
            update_x(2*ix, lx, mx);
        else
            update_x(2*ix+1, mx+1, rx);
    }

    update_y(
        ix, lx, rx,
        1, 0, m-1
    );
}


int main(){

    scanf("%d %d", &n, &m); 

    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%lld", &arr[i][j]); 
        }
    }

    build_x(
        1, 0, n-1
    ); 

}