#if defined _lololib_macros_included
  #endinput
#endif
#define _lololib_macros_included

#define int(%1) view_as<int>(%1)

#define packint1(%1,%2) (%1[0]=%2)
#define packint2(%1,%2,%3) (packint1(%1,%2),%1[1]=%3)
#define packint3(%1,%2,%3,%4) (packint2(%1,%2,%3),%1[2]=%4)
#define packint4(%1,%2,%3,%4,%5) (packint3(%1,%2,%3,%4),%1[3]=%5)
#define packint5(%1,%2,%3,%4,%5,%6) (packint4(%1,%2,%3,%4,%5),%1[4]=%6)
#define packint6(%1,%2,%3,%4,%5,%6,%7) (packint5(%1,%2,%3,%4,%5,%6),%1[5]=%7)