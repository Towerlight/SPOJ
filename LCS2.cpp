#include <cstdio>
#include <cstring>
#include <algorithm>
#define REP( i, n ) for ( int i = 1; i <= n; i ++ )
#define REP_0( i, n ) for ( int i = 0; i < n; i ++ )
#define REP_0N( i, n ) for ( int i = 0; i <= n; i ++ )
#define REP_S( i, str ) for ( char *i = str; *i; i ++ )
#define FOR( i, a, b ) for ( int i = a; i <= b; i ++ )
#define DWN( i, a, b ) for ( int i = b; i >= a; i -- )
#define RST( a, x ) memset ( a, x, sizeof ( a ) );
#define CPY( a, b ) memcpy ( a, b, sizeof ( b ) );
#define ONLINE_JUDGE
#define SSIZE 220000
using namespace std;

char s[ SSIZE ], str[ SSIZE ];
int len, dws[ SSIZE ], b[ SSIZE ], ans = 0;

#define SMEC graph[ tx ].edge[ c ]
#define SMP graph[ tx ].par
#define SML graph[ tx ].l
#define SMTP graph[ tt ].par
#define SMX graph[ tx ].maxx
#define SMN graph[ tx ].minn
#define SMPX graph[ graph[ tx ].par ].maxx
#define SMTT graph[ tt ]
#define SMRT graph[ rt ]
#define SMTV graph[ tv ]
#define SMI graph[ i ]
#define MX max ( SMX, ts )
#define MNS - 'a' + 1
namespace SAM
{
	struct node
	{
		int minn, maxx, par, l, edge[ 30 ];
		node ()
		{
			RST ( edge, -1 );
		}
	};
	node graph[ SSIZE ];
	int tail = 0, sz = 0;

	void Add ( int c )
	{
		int tt = ++ sz, tx = tail; tail = tt;
		SMTT.l = SMTT.minn = SML + 1;
		for ( ; tx != -1 && SMEC == -1; tx = SMP ) SMEC = tt;
		if ( tx == -1 ) SMTP = 0;
		else
		{
			if ( SML + 1 == graph[ SMEC ].l )
				SMTP = SMEC;
			else
			{
				int tv = SMEC, rt = ++ sz;
				CPY ( SMRT.edge, SMTV.edge );
				SMRT.par = SMTV.par;
				SMRT.maxx = SMTV.maxx;
				SMRT.l = SMRT.minn = SML + 1;
				SMTV.par = SMTP = rt;
				for ( ; tx != -1 && SMEC == tv; tx = SMP )
					SMEC = rt;
			}
		}
	}
}

using namespace SAM;

int main()
{

#ifndef ONLINE_JUDGE
	freopen ( "LCS2.in", "r", stdin );
	freopen ( "LCS2.out", "w", stdout );
#endif

	scanf ( "%s", s );
	graph[ 0 ].par = -1;
	len = strlen ( s );
	REP_0 ( i, len ) Add ( s[ i ] MNS );
	REP_0N ( i, sz ) dws[ SMI.l ] ++;
	REP ( i, len ) dws[ i ] += dws[ i - 1 ];
	REP_0N ( i, sz ) b[ -- dws[ SMI.l ] ] = i;
	while ( scanf( "%s", str ) != EOF )
	{
		int lr = strlen ( str ), tx = 0, ts = 0;
		REP_0 ( i, lr )
		{
			int c = str[ i ] MNS;
			if ( SMEC != -1 ) ts ++, tx = SMEC, SMX = MX;
			else
			{
				for ( ; tx != -1 && SMEC == -1; tx = SMP ) ;
				if ( tx == -1 ) ts = 0;
				else ts = SML + 1, tx = SMEC, SMX = MX;
			}
		}
		DWN ( i, 1, sz )
		{
			int tx = b[ i ];
			SMN = min ( SMX, SMN );
			SMPX = max ( SMX, SMPX );
			SMX = 0;
		}
	}
	REP_0N ( i, sz ) ans = max ( ans, SMI.minn );
	printf( "%d\n", ans );
	return 0;
}
