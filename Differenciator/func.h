#define d_symbol 1
#define d_value 2
#define d_operator 3
#define d_const 4

#define dl                    Differenciator(t, n->left, rofl)
#define dr                    Differenciator(t, n->right, rofl)
#define l                     TreeCopy(t, indif, n->left, 'L')
#define r                     TreeCopy(t, indif, n->right, 'L')

#define ADD(  left , right )  TypeNode(t, d_operator, "+",    left, right)
#define MUL(  left , right )  TypeNode(t, d_operator, "*",    left, right)
#define DIV(  left , right )  TypeNode(t, d_operator, "/",    left, right)
#define SUB(  left , right )  TypeNode(t, d_operator, "-",    left, right)
#define POV(  left , right )  TypeNode(t, d_operator, "^",    left, right)
#define SIN(  left , right )  TypeNode(t, d_operator, "sin",  left, right)
#define COS(  left , right )  TypeNode(t, d_operator, "cos",  left, right)
#define TG(   left , right )  TypeNode(t, d_operator, "tg",   left, right)
#define CTG(  left , right )  TypeNode(t, d_operator, "ctg",  left, right)
#define LN(   left , right )  TypeNode(t, d_operator, "ln",   left, right)
#define MN1(  left , right )  TypeNode(t, d_value,    "-1",   left, right)
#define AD1(  left , right )  TypeNode(t, d_value,    "1",    left, right)
#define COEF2(left , right )  TypeNode(t, d_value,    "2",    left, right)
#define COEF3(left , right )  TypeNode(t, d_value,    "3",    left, right)
#define SQRT( left , right )  TypeNode(t, d_operator, "sqrt", left, right)
#define CBRT( left , right )  TypeNode(t, d_operator, "cbrt", left, right)


DIFF_( +     , d_operator, ADD( dl, dr))
DIFF_( -     , d_operator, SUB( dl, dr))
DIFF_( /     , d_operator, DIV( SUB( MUL( dl, r), MUL( l, dr)), MUL( r, r)))
DIFF_( *     , d_operator, ADD( MUL( dl, r), MUL( l, dr)))
DIFF_( sin   , d_operator, MUL( dl, COS( l, NULL)))
DIFF_( cos   , d_operator, MUL( MN1( NULL, NULL), MUL( dl, SIN( l, NULL))))
DIFF_( tg    , d_operator, DIV( dl, MUL( COS(l, NULL), COS(l, NULL))))
DIFF_( ctg   , d_operator, DIV( MUL( dl, MN1( NULL, NULL)), MUL( SIN(l, NULL), SIN(l, NULL))))
DIFF_( ^     , d_operator, MUL( POV( l, r), ADD( MUL( LN( l, NULL), dr), MUL( dl, DIV( r, l)))))
DIFF_( ln    , d_operator, DIV( dl, l))
DIFF_( log   , d_operator, DIV( dr, MUL( r, LN( l, NULL))))
DIFF_( arcsin, d_operator, DIV( dl, SQRT( SUB( AD1( NULL, NULL), MUL( l, l)), NULL)))
DIFF_( arccos, d_operator, DIV( dl, MUL( MN1( NULL, NULL), SQRT( SUB( AD1( NULL, NULL), MUL( l, l)), NULL))))
DIFF_( arctg , d_operator, DIV( dl, ADD( AD1( NULL, NULL), MUL( l, l))))
DIFF_( arcctg, d_operator, DIV( dl, MUL( MN1( NULL, NULL), ADD( AD1( NULL, NULL), MUL( l, l)))))
DIFF_( sqrt  , d_operator, DIV( AD1 ( NULL, NULL), MUL( COEF2 ( NULL, NULL), SQRT( l, NULL))))
DIFF_( cbrt  , d_operator, DIV( dl, MUL( COEF3( NULL, NULL), POV( CBRT( l, NULL), COEF2( NULL, NULL)))))



#undef d_symbol
#undef d_value
#undef d_operator
#undef d_const
#undef PLUS
#undef MUL
#undef DIV
#undef SUB
#undef POV
#undef SIN
#undef COS
#undef TG
#undef CTG
#undef LN
#undef MN1
#undef SQRT
#undef COEF2
#undef COEF3
#undef CBRT
#undef dl
#undef dr
#undef l
#undef r
