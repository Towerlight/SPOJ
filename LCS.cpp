#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define REP( i, n ) for ( int i = 1; i <= n; i ++ )
#define REP_S( i, str ) for ( char *i = str; *i; i ++ )
#define FOR( i, a, b ) for ( int i = a; i <= b; i ++ )
#define DWN( i, a, b ) for ( int i = b; i >= a; i -- )
#define RST( a, x ) memset ( a, x, sizeof ( a ) );
#define CPY( a, b ) memcpy ( a, b, sizeof ( a ) );
#define MNS - 'a' + 1
#define SAM_USED
#define ONLINE_JUDGE
#define SSIZE 500000

char s[ SSIZE ], str[ SSIZE ];
int l, lr, ans = 0, ts = 0;

#ifdef SAM_USED

#define SME graph[ tx ].edge
#define SMP graph[ tx ].par
#define SML graph[ tx ].l

namespace SAM
{
    struct node
    {
    	int edge[ 30 ];
    	int par, l;
    };
    node graph[ SSIZE ];
    int tail, sz = 0;

    inline int AddNode()
    {
        RST ( graph[ sz ].edge, 0 ); tail = sz;
        return sz ++;
    }

    inline int AddNode( int x )
    {
        CPY ( graph[ sz ].edge, graph[ x ].edge ); graph[ sz ].par = graph[ x ].par;
        return sz ++;
    }

    void Add( int c )
    {
        int tx = tail, tt = AddNode (); graph[ tt ].l = graph[ tx ].l + 1;
        for ( ; tx && !SME[ c ]; tx = SMP ) SME[ c ] = tt;
        if ( !tx && !SME[ c ] ) SME[ c ] = tt, graph[ tt ].par = 0;
        else
        {
            if ( graph[ SME[ c ] ].l == graph[ tx ].l + 1 ) graph[ tt ].par = SME[ c ];
            else
            {
                int tv = SME[ c ], rt = AddNode ( tv ); graph[ rt ].l = graph[ tx ].l + 1;
                graph[ tv ].par = graph[ tt ].par = rt;
                for ( ; SME[ c ] == tv; tx = SMP ) SME[ c ] = rt;
            }
        }
    }

    void Init ( char *buf )
    {
        sz = 0, tail = AddNode();
        REP_S ( i, buf ) Add ( *i - 'a' + 1 );
    }

}

#endif

using namespace std;
int main ()
{

#ifndef ONLINE_JUDGE
	freopen ( "LCS.in", "r", stdin );
	freopen ( "LCS.out", "w", stdout );
#endif

	scanf ( "%s%s", s, str );
	l = strlen ( s ); lr = strlen ( str ); int tx = 0;
	SAM::Init ( s );
	FOR ( i, 0, lr - 1 )
	{
		int c = str[ i ] MNS;
        if ( SAM::SME[ c ] ) tx = SAM::SME[ c ], ts ++;
        else
        {
            while ( tx && !SAM::SME[ c ] ) tx = SAM::SMP;
            if ( !tx ) ts = 0;
            else ts = SAM::SML + 1, tx = SAM::SME[ c ];
        }
        ans = max ( ans, ts );
	}
	printf ( "%d\n", ans );
	return 0;
}


