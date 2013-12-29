#include <cstdio>
#include <cstring>
#include <algorithm>
#define REP( i, n ) for ( int i = 1; i <= n; i ++ )
#define REP_G( i, x ) for ( int i = pos[ x ]; i; i = g[ i ].frt )
#define RST( a, x ) memset ( a, x, sizeof ( a ) )
#define GY g[ i ].y
#define GV g[ i ].val
#define GZ g[ sz ]
#define TX tree[ x ]
#define TXL tree[ tree[ x ].lc ]
#define TXR tree[ tree[ x ].rc ]
#define TXP tree[ x ].par
#define TY tree[ y ]
#define TZ tree[ z ]
#define PSIZE 20010
using namespace std;
struct edge
{
	int y, frt, val;
};
struct node
{
	int par, lc, rc, val;
	bool rt;
	void Clean ()
	{
		par = lc = rc = val = 0;
		rt = true;
	}
};
edge g[ PSIZE ];
node tree[ PSIZE ];
int pos[ PSIZE ];
int n, ans, sz, q0, h[ PSIZE ], w[ PSIZE ];
inline void Update ( int x )
{
	TX.val = max ( TXL.val, max ( TXR.val, w[ x ] ) );
}
inline void Set ( int &v, int y, int x )
{
	v = x, TXP = y;
}
void Rotate ( int x )
{
	int y = TXP, z = TY.par;
	if ( !TY.rt ) Set( y == TZ.lc ? TZ.lc : TZ.rc, z, x );
	else TXP = z;
	if ( x == TY.lc ) Set ( TY.lc, y, TX.rc ), Set ( TX.rc, x, y );
	else Set ( TY.rc, y, TX.lc ), Set ( TX.lc, x, y );
	if ( TY.rt ) TY.rt = false, TX.rt = true;
	Update ( y );
}
inline void Splay ( int x )
{
	while ( !TX.rt ) Rotate ( x );
}
void Access ( int x )
{
	int y = 0;
	while ( x )
	{
		Splay ( x );
		TXR.rt = true, tree[ TX.rc = y ].rt = false, Update ( x );
		x = tree[ y = x ].par;
	}
}
int Query ( int x, int y )
{
	Access ( y ), y = 0;
	while ( x )
	{
		Splay ( x );
		if ( !TX.par ) return max ( TXR.val, TY.val );
		TXR.rt = true, tree[ TX.rc = y ].rt = false, Update ( x );
		x = tree[ y = x ].par;
	}
}
inline void Modify ( int x, int val )
{
	Splay ( x ), w[ x ] = val;
}
void Search ( int x )
{
	REP_G ( i, x )
		if ( !tree[ GY ].par )
		{
			tree[ GY ].par = x, w[ GY ] = GV, h[ i / 2 ] = GY;
			Search ( GY );
		}
}
inline void AddEdge ( int x, int y, int v )
{
	g[ ++ sz ].y = y, GZ.val = v, GZ.frt = pos[ x ], pos[ x ] = sz;
}
int main ()
{
	for ( scanf ( "%d", &q0 ); q0; q0 -- )
	{
		RST ( pos, 0 ), tree[ 1 ].Clean (), tree[ 1 ].par = -1, sz = 1;
		int t1, t2, t3;
		scanf ( "%d", &n );
		REP ( i, n - 1 )
		{
			tree[ i + 1 ].Clean ();
			scanf ( "%d%d%d", &t1, &t2, &t3 );
			AddEdge ( t1, t2, t3 ), AddEdge ( t2, t1, t3 );
		}
		Search ( 1 );
		tree[ 1 ].par = 0;
		char str[ 7 ];
		for ( scanf ( "%s", str ); str[ 0 ] != 'D'; scanf ( "%s", str ) )
		{
			scanf ( "%d%d", &t1, &t2 );
			if ( str[ 0 ] == 'C' ) Modify ( h[ t1 ], t2 );
			else if ( str[ 0 ] == 'Q' ) printf ( "%d\n", Query ( t1, t2 ) );
		}
	}
}
