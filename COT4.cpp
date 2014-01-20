# include <cstdio>
# include <cstring>
# include <algorithm>
# define REP( i, n ) for ( int i = 1; i <= n; i ++ )
# define REP_0( i, n ) for ( int i = 0; i < n; i ++ )
# define REP_0N( i, n ) for ( int i = 0; i <= n; i ++ )
# define REP_G( i, x ) for ( int i = pos[ x ]; i; i = g[ i ].frt )
# define FOR( i, a, b ) for ( int i = a; i <= b; i ++ )
# define DWN( i, a, b ) for ( int i = b; i >= a; i -- )
# define RST( a ) memset ( a, 0, sizeof ( a ) )
# define FLC( a, x ) memset( a, x, sizeof ( a ) )
# define CPY( a, b ) memcpy( a, b, sizeof ( a ) )
# define NSIZE 280010
# define N2SIZE 560020
# define MOD 910007
# define SG seg[ x ]
# define SGL seg[ x ].ch[ 0 ]
# define SGR seg[ x ].ch[ 1 ]
# define SGZ seg[ sgz ]
# define TXPC trie[ tx ].pos[ c ]
# define TXEI trie[ tx ].edge[ i ]
# define TEZ trie[ tx ].esz
# define TXD trie[ tx ].dep
# define TXP trie[ tx ].par
# define TZ trie[ tsz ]
# define SMTT sam[ tt ]
# define SML sam[ tx ].l
# define SMEC sam[ tx ].edge[ c ]
# define SMP sam[ tx ].par
# define SMTP sam[ tt ].par
# define SMRT sam[ rt ]
# define SMTV sam[ tv ]
# define RTS st[ tx ].sta
# define RTL st[ tx ].l
# define RTN st[ tn ]
# define RTH st[ tx ].hash
# define RTX st[ x ]
# define RTY st[ y ]
# define PTZ part[ psz ]
# define PTY part[ tx ].y
# define PTF part[ tx ].frt
# define HZ h[ szh ]
using namespace std;
typedef unsigned long long LL;
struct edge { int y, frt; } part[ NSIZE ];
struct edgeh { int y, l, r, frt; } h[ MOD + 20 ];
struct segnode { int val, ch[ 2 ]; } seg[ 1700020 ];
struct arr { int x, y, c, ty; } t[ NSIZE ];
struct trienode { int val, par, dep, pos[ 27 ], esz, edge[ 27 ]; } trie[ NSIZE ];
struct arri { int pos1, pos2; } inter[ NSIZE ];
struct arrt { int sta, l; LL hash; } st[ NSIZE ];
struct samnode
{
	int par, l, edge[ 27 ];
	samnode () { FLC ( edge, -1 ); }
} sam[ NSIZE ];
int log2[ NSIZE ], f[ 20 ][ NSIZE ], end[ NSIZE ], q[ NSIZE ], drs[ NSIZE ], posp[ NSIZE ], posh[ MOD + 20 ];
int last[ NSIZE ], ter[ N2SIZE ], dws[ N2SIZE ], post[ NSIZE ], trans[ NSIZE ][ 27 ], root[ NSIZE ];
LL pow[ NSIZE ], HashS[ NSIZE ];
int lst = 0, gsz = 1, sgz = 0, tsz = 1, psz = 0, szh = 0, m, sn = 1, tn = 1, head, tail, lv = 0, szl = 0;
char s[ NSIZE * 3 ];
void Print ( int x )
{
	if ( x == 0 ) s[ szl ++ ] = '0';
	int dit[ 10 ], t = 0;
	for ( ; x; x /= 10 ) dit[ ++ t ] = x % 10;
	DWN ( i, 1, t ) s[ szl ++ ] = dit[ i ] + '0';
	s[ szl ++ ] = '\n';
}
int ScanInt ()
{
	char c; int ret = 0;
	for ( c = ' '; c == ' ' || c == '\n'; c = getchar () ) ;
	for ( ; c >= '0' && c <= '9'; c = getchar () ) ret = ret * 10 + c - '0';
	return ret;
}
char ScanChar () { for ( char c = ' '; ; c = getchar () ) if ( c != ' ' && c != '\n' ) return c - 'a' + 1; }
int BuildSeg ( int l, int r )
{
	int mid = ( l + r ) >> 1, x = ++ sgz;
	if ( l == r ) return sgz;
	SGL = BuildSeg ( l, mid );
	SGR = BuildSeg ( mid + 1, r );
	return x;
}
int Insert ( int x, int h )
{
	int tx = ++ sgz, tt = 0, rt = 0, l = 1, r = lv;
	for ( int mid = ( l + r ) >> 1, d = h > mid; 1; mid = ( l + r ) >> 1, d = h > mid )
	{
		SGZ.val = SG.val + 1, SGZ.ch[ !d ] = SG.ch[ !d ], x = SG.ch[ d ];
		if ( l != r ) tt = sgz, seg[ tt ].ch[ d ] = ++ sgz;
		else break;
		if ( d ) l = mid + 1;
		else r = mid;
	}
	return tx;
}
int SegSum ( int x, int l, int r, int ql, int qr )
{
	if ( ql > qr ) return 0;
	if ( ql <= l && r <= qr ) return seg[ x ].val;
	int mid = ( l + r ) >> 1;
	return SegSum ( SGL, l, mid, ql, min ( qr, mid ) ) + SegSum ( SGR, mid + 1, r, max ( ql, mid + 1 ), qr );
}
void Init ()
{
	m = ScanInt (), pow[ 0 ] = 1;
	REP ( i, m )
	{
		t[ i ].ty = ScanInt (), t[ i ].x = ScanInt ();
		if ( t[ i ].ty == 1 )
		{ 
			t[ i ].c = ScanChar ();
			continue;
		}
		t[ i ].y = ScanInt ();
		if ( t[ i ].ty == 2 ) t[ i ].c = ScanChar ();
	}
	REP ( i, m ) pow[ i ] = ( pow[ i - 1 ] << 7 ) + 3 * pow[ i - 1 ];
}
inline int FindNode ( int x, int l )
{
	while ( l ) x = f[ log2[ l & -l ] ][ x ], l -= l & -l;
	return x;
}
void MakeTrie ()
{
	end[ 1 ] = 1, trie[ 1 ].val = -1, st[ 1 ].sta = 1;
	REP ( i, m )
		if ( t[ i ].ty == 1 )
		{
			int tx = end[ t[ i ].x ], c = t[ i ].c;
			if ( !TXPC ) trie[ tx ].edge[ ++ TEZ ] = ++ tsz, TXPC = TEZ, TZ.val = c, TZ.par = tx, TZ.dep = TXD + 1;
			end[ ++ sn ] = trie[ tx ].edge[ TXPC ];
		}
	for ( int i = 2; i <= tsz; i <<= 1 ) log2[ i ] = log2[ i >> 1 ] + 1;
	for ( head = 1, tail = 1, q[ 1 ] = 1; head <= tail; )
	{
		int tx = q[ head ++ ];
		f[ 0 ][ tx ] = TXP;
		for ( int i = 1; ( 1 << i ) <= TXD; i ++ ) f[ i ][ tx ] = f[ i - 1 ][ f[ i - 1 ][ tx ] ];
		DWN ( i, 1, TEZ ) if ( TXEI ) q[ ++ tail ] = TXEI, HashS[ TXEI ] = ( HashS[ tx ] << 7 ) + 3 * HashS[ tx ] + trie[ TXEI ].val;
	}
}
inline LL CalcHash ( int x, int h ) { return HashS[ x ] - HashS[ FindNode ( x, h ) ] * pow[ h ]; }
int AddNode ( int lst, int c )
{
	int tt = ++ gsz, tx = lst; lst = tt, SMTT.l = SML + 1;
	for ( ; tx != -1 && SMEC == -1; tx = SMP ) SMEC = tt;
	if ( tx == -1 ) SMTP = 1;
	else if ( SML + 1 == sam[ SMEC ].l ) SMTP = SMEC;
	else
	{
		int tv = SMEC, rt = ++ gsz;
		CPY ( SMRT.edge, SMTV.edge ), SMRT.par = SMTV.par, SMRT.l = SML + 1, SMTV.par = SMTP = rt;
		for ( ; tx != -1 && SMEC == tv; tx = SMP ) SMEC = rt;
	}
	return lst;
}
void Search ( int x )
{
	drs[ ++ lv ] = x, inter[ x ].pos1 = lv;
	REP ( i, 26 ) if ( trans[ x ][ i ] ) Search ( trans[ x ][ i ] );
	inter[ x ].pos2 = lv;
}
inline bool Cmp ( int x, int y ) { return sam[ x ].l < sam[ y ].l; }
void MakeSAM ()
{
	last[ 1 ] = 1, sam[ 1 ].par = -1;
	for ( int p = 1, tx = q[ p ]; p <= tsz; tx = q[ ++ p ] )
		DWN ( i, 1, TEZ ) last[ TXEI ] = AddNode ( last[ tx ], trie[ TXEI ].val );
	REP ( i, tsz ) ter[ last[ i ] ] = i;
	FOR ( tx, 2, gsz ) part[ ++ psz ].y = tx, PTZ.frt = posp[ SMP ], posp[ SMP ] = psz;
	REP ( i, gsz ) dws[ i ] = i;
	sort ( dws + 1, dws + gsz + 1, Cmp );
	DWN ( i, 1, gsz )
	{
		if ( ter[ dws[ i ] ] ) post[ dws[ i ] ] = ter[ dws[ i ] ];
		else for ( int tx = posp[ dws[ i ] ]; tx; tx = PTF )
				if ( post[ PTY ] ) { post[ dws[ i ] ] = post[ PTY ]; break; }
	}
	REP ( i, gsz )
		for ( int tx = posp[ i ]; tx; tx = PTF )
			trans[ i ][ trie[ FindNode ( post[ PTY ], sam[ i ].l ) ].val ] = PTY;
	Search ( 1 ), root[ 1 ] = BuildSeg ( 1, lv );
	for ( int p = 1, tx = q[ p ]; p <= tsz; tx = q[ ++ p ] )
		DWN ( i, 1, TEZ ) root[ TXEI ] = Insert ( root[ tx ], inter[ last[ TXEI ] ].pos1 );
	REP ( i, gsz )
	{
		int x = ( inter[ i ].pos1 << 8 ) + 3 * inter[ i ].pos1 + inter[ i ].pos2; while ( x >= MOD ) x -= MOD;
		h[ ++ szh ].l = inter[ i ].pos1, HZ.r = inter[ i ].pos2, HZ.y = i, HZ.frt = posh[ x ], posh[ x ] = szh;
	}
}
int BinSearch ( int x, int y, bool z )
{
	int ql = 1, qr = lv, nx = post[ RTX.sta ], ny = post[ RTY.sta ];
	while ( ql <= qr )
	{
		int mid = ( ql + qr ) >> 1, w = post[ drs[ mid ] ], l = 0, r = min ( sam[ drs[ mid ] ].l, RTX.l + RTY.l );
		while ( l <= r )
		{
			int tm = ( l + r ) >> 1; LL h1 = 0, h2 = CalcHash ( w, tm );
			if ( tm <= RTY.l ) h1 = CalcHash ( ny, tm );
			else h1 = CalcHash ( nx, tm - RTY.l ) * pow[ RTY.l ] + RTY.hash;
			if ( h1 == h2 ) l = tm + 1;
			else r = tm - 1;
		}
		int w2 = FindNode ( w, l - 1 ), w1 = 0;
		if ( l <= RTY.l ) w1 = FindNode ( ny, l - 1 );
		else w1 = FindNode ( nx, l - RTY.l - 1 );
		int tx = trie[ w1 ].val, ty = trie[ w2 ].val;
		if ( l > RTX.l + RTY.l ) tx = -1;
		if ( l > sam[ drs[ mid ] ].l ) ty = -1;
		if ( tx == -1 ) tx = ty;
		if ( ( !z && tx <= ty ) || ( z && tx < ty ) ) qr = mid - 1;
		else ql = mid + 1;
	}
	return ql;
}
int main ()
{
#ifndef ONLINE_JUDGE
	freopen ( "COT4.in", "r", stdin );
	freopen ( "COT4.out", "w", stdout );
#endif
	Init (), MakeTrie (), MakeSAM ();
	REP ( i, m )
	{
		if ( t[ i ].ty == 2 )
		{
			int tx = t[ i ].y, c = t[ i ].c; tn ++;
			if ( !RTS ) continue;
			RTN.l = RTL + 1;
			if ( !t[ i ].x )
			{
				RTN.hash = pow[ RTL ] * c + RTH;
				if ( RTN.l <= sam[ RTS ].l && trie[ FindNode ( post[ RTS ], RTL ) ].val == c ) RTN.sta = RTS;
				else if ( trans[ RTS ][ c ] ) RTN.sta = trans[ RTS ][ c ];
			}
			else
			{
				RTN.hash = ( RTH << 7 ) + RTH * 3 + c;
				if ( sam[ RTS ].edge[ c ] ) RTN.sta = sam[ RTS ].edge[ c ];
			}
		}
		if ( t[ i ].ty == 4 )
		{
			int tx = t[ i ].x, y = t[ i ].y;
			if ( RTS <= 1 ) s[ szl ++ ] = '0', s[ szl ++ ] = '\n';
			else Print ( SegSum ( root[ end[ y ] ], 1, lv, inter[ RTS ].pos1, inter[ RTS ].pos2 ) );
		}
		if ( t[ i ].ty == 3 )
		{
			tn ++;
			int x = t[ i ].x, y = t[ i ].y;
			if ( !RTX.sta || !RTY.sta ) continue;
			if ( RTX.sta == 1 ) RTN.sta = RTY.sta, RTN.l = RTY.l, RTN.hash = RTY.hash;
			else if ( RTY.sta == 1 ) RTN.sta = RTX.sta, RTN.l = RTX.l, RTN.hash = RTX.hash;
			else
			{
				int l = BinSearch ( x, y, 0 ), r = BinSearch ( x, y, 1 ) - 1, w = -1;
				for ( int tx = posh[ ( ( l << 8 ) + 3 * l + r ) % MOD ]; tx; tx = h[ tx ].frt )
					if ( h[ tx ].l == l && h[ tx ].r == r ) { w = h[ tx ].y; break; }
				if ( w != -1 ) RTN.sta = w, RTN.l = RTX.l + RTY.l, RTN.hash = RTX.hash * pow[ RTY.l ] + RTY.hash;
			}
		}
	}
	puts ( s );
	return 0;
}
