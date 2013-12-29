#include <cstdio>
#include <cstring>
#include <algorithm>
#define REP( i, n ) for ( int i = 1; i <= n; i ++ )
#define REP_0( i, n ) for ( int i = 0; i < n; i ++ )
#define REP_0N( i, n ) for ( int i = 0; i <= n; i ++ )
#define FOR( i, a, b ) for ( int i = a; i <= b; i ++ )
#define DWN( i, a, b ) for ( int i = b; i >= a; i -- )
#define RST( a, x ) memset ( a, x, sizeof ( a ) );
#define CPY( a, b ) memcpy ( a, b, sizeof ( a ) );
#define ONLINE_JUDGE NULL
#define SSIZE 400000

#define SMIL graph[ i ].l
#define SML graph[ tx ].l
#define SMP graph[ tx ].par
#define SMEC graph[ tx ].edge[ c ]
#define SMTP graph[ tt ].par
#define SMTV graph[ tv ]
#define SMRT graph[ rt ]
#define SMC graph[ tx ].c

int mx[ SSIZE ], dws[ SSIZE ], b[ SSIZE ], szs = 0;
char s[ SSIZE ], str[ 87 * SSIZE ];

namespace SAM
{
	struct node
	{
		int l, par, edge[ 28 ], c, v;
		node ()
		{
			RST ( edge, -1 );
		}
	};
	node graph[ 2 * SSIZE ];
	int sz = 0, tail = 0;

	void Add ( int c )
	{
		int tx = tail, tt = ++ sz; tail = tt;
		graph[ tt ].l = SML + 1;
		for ( ; tx != -1 && SMEC == -1; tx = SMP ) SMEC = tt;
		if ( tx == -1 ) SMTP = 0;
		else
		{
			if ( graph[ SMEC ].l == SML + 1 ) SMTP = SMEC;
			else
			{
				int tv = SMEC, rt = ++ sz;
				CPY ( SMRT.edge, SMTV.edge );
				SMRT.l = SML + 1;
				SMRT.par = SMTV.par;
				SMTV.par = SMTP = rt;
				for ( ; tx != -1 && SMEC == tv; tx = SMP ) SMEC = rt;
			}
		}
	}
}
using namespace std;
using namespace SAM;
void Print ( int x )
{
	int dit[ 10 ], t = 0;
	while ( x > 0 )
	{
		dit[ ++ t ] = x % 10;
		x /= 10;
	}
	DWN ( i, 1, t ) str[ sz ++ ] = dit[ i ] + '0';
	str[ sz ++ ] = '\n';
}
int main ()
{

#ifndef ONLINE_JUDGE
	freopen ( "NSUBSTR.in", "r", stdin );
	freopen ( "NSUBSTR.out", "w", stdout );
#endif

	scanf ( "%s", s );
	int l = strlen ( s );
	graph[ 0 ].par = -1;
	REP_0 ( i, l ) Add ( s[ i ] - 'a' + 1 );
	REP_0N ( i, sz ) dws[ SMIL ] ++;
	REP ( i, l ) dws[ i ] += dws[ i - 1 ];
	REP_0N ( i, sz ) b[ -- dws[ SMIL ] ] = i;
	int tx = 0;
	REP_0 ( i, l )
	{
		tx = graph[ tx ].edge[ s[ i ] - 'a' + 1 ];
		SMC = 1;
	}
	DWN ( i, 0, sz )
	{
		int tx = b[ i ];
		mx[ SML ] = max ( mx[ SML ], SMC );
		graph[ SMP ].c += SMC;
	}
	DWN ( i, 1, l - 1 ) mx[ i ] = max ( mx[ i ], mx[ i + 1 ] );
	int dit[ 10 ], t = 0;
	REP ( i, l )
	{
		t = 0;
		while ( mx[ i ] > 0 )
		{
			dit[ ++ t ] = mx[ i ] % 10;
			mx[ i ] /= 10;
		}
		DWN ( i, 1, t ) str[ szs ++ ] = dit[ i ] + '0';
		str[ szs ++ ] = '\n';
	}
	str[ szs ++ ] = '\0';
	puts ( str );
	return 0;
}
