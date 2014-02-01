#include <cstdio>
#include <cstring>
#include <algorithm>
#define REP( i, n ) for ( int i = 1; i <= n; i ++ )
#define REP_G( i, x ) for ( int i = pos[ x ]; i; i = g[ i ].frt )
#define RST( a, x ) memset ( a, x, sizeof ( a ) );
#define SRT 1, 1, tz
#define SLC x * 2, l, mid
#define SRC x * 2 + 1, mid + 1, r
#define GY g[ i ].y
#define TI tree[ i ]
#define PSIZE 100001
using namespace std;
struct edge
{
    int x, val, y, frt; 
};
edge tree[ PSIZE ], g[ PSIZE ];
int n, q0, tz, sz, root, top[ PSIZE ], son[ PSIZE ], siz[ PSIZE ];
int pos[ PSIZE ], dep[ PSIZE ], w[ PSIZE ], fa[ PSIZE ], segtree[ 4 * PSIZE ];
char str[ 10 ];
 
void AddEdge ( int x, int y )
{
    g[ ++ sz ].y = y; g[ sz ].frt = pos[ x ]; pos[ x ] = sz;
}
void Search ( int x )
{
    siz[ x ] = 1; son[ x ] = 0;
    REP_G ( i, x )
        if ( GY != fa[ x ] )
        {
            fa[ GY ] = x;
            dep[ GY ] = dep[ x ] + 1;
            Search ( GY );
            if ( siz[ GY ] > siz[ son[ x ] ] ) son[ x ] = GY;
            siz[ x ] += siz[ GY ];
        }
}
void BuildTree ( int x, int tp )
{
    w[ x ] = ++ tz, top[ x ] = tp;
    if ( son[ x ] ) BuildTree ( son[ x ], top[ x ] );
    REP_G ( i, x )
        if ( GY != son[ x ] && GY != fa[ x ] ) BuildTree ( GY, GY );
}
void Update ( int x, int l, int r, int loc, int v )
{
    if ( loc > r || l > loc ) return;
    if ( l == r ) 
    { 
        segtree[ x ] = v; 
        return; 
    }
    int mid = ( l + r ) / 2;
    Update ( SLC, loc, v );
    Update ( SRC, loc, v );
    segtree[ x ] = max ( segtree[ x * 2 ], segtree[ x * 2 + 1 ] );
}
int SegMax ( int x, int l, int r, int ql, int qr )
{
    if ( ql > r || qr < l ) return 0;
    if ( ql <= l && r <= qr ) return segtree[ x ];
    int mid = ( l + r ) / 2;
    return max ( SegMax ( SLC, ql, qr ), SegMax ( SRC, ql, qr ) );
}
int Query ( int va, int vb )
{
    int f1 = top[ va ], f2 = top[ vb ], tmp = 0, cnt;
    while ( f1 != f2 )
    {
        if ( dep[ f1 ] < dep[ f2 ] )
        { 
            swap ( f1, f2 ); 
            swap ( va, vb ); 
        }
        tmp = max ( tmp, SegMax ( SRT, w[ f1 ], w[ va ] ) );
        va = fa[ f1 ], f1 = top[ va ];
    }
    if ( va == vb ) return tmp;
    if ( dep[ va ] > dep[ vb ] ) swap ( va, vb );
    return max ( tmp, SegMax ( SRT, w[ son[ va ] ], w[ vb ] ) );
}
int main()
{
    freopen ( "QTREE.in", "r", stdin );
    freopen ( "QTREE.out", "w", stdout );
    for ( scanf ( "%d", &q0 ); q0; q0 -- )
    {
        int t1, t2, t3;
        scanf ( "%d", &n );
        root = ( n + 1 ) / 2, fa[ root ] = tz = dep[ root ] = sz = siz[ n ] = segtree[ n ] = 0;
        RST ( pos, 0 );
        REP ( i, n - 1 )
        {
            scanf ( "%d%d%d", &t1, &t2, &t3 );
            TI.x = t1, TI.y = t2, TI.val = t3, siz[ i ] = segtree[ i ] = 0;
            AddEdge ( t1, t2 );
            AddEdge ( t2, t1 );
        }
        Search ( root );
        BuildTree ( root, root );
        REP ( i, n - 1 )
        {
            if ( dep[ TI.x ] > dep[ TI.y ] ) swap ( TI.x, TI.y );
            Update( SRT, w[ TI.y ], TI.val );
        }
        for ( scanf ( "%s", str ); str[ 0 ] != 'D'; scanf ( "%s", str ) )
        {
            scanf ( "%d%d", &t1, &t2 );
            if ( str[ 0 ] == 'Q' ) printf ( "%d\n", Query ( t1, t2 ) );
            else Update ( SRT, w[ tree[ t1 ].y ], t2 );
        }
    }
    return 0;
}