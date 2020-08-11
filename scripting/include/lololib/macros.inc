#if defined _lololib_macros_included
  #endinput
#endif
#define _lololib_macros_included

#define int(%1) view_as<int>(%1)

#define unpack(%1,%2) 						(view_as<ArrayList>(%1.Get(%2)))
#define unpack2(%1,%2,%3) 					(unpack(unpack(%1,%2),%3))
#define unpack3(%1,%2,%3,%4)				(unpack(unpack2(%1,%2,%3),%4))
#define unpack4(%1,%2,%3,%4,%5)				(unpack(unpack3(%1,%2,%3,%4),%5))
#define unpack5(%1,%2,%3,%4,%5,%6)			(unpack(unpack4(%1,%2,%3,%4,%5),%6))
#define unpack6(%1,%2,%3,%4,%5,%6,%7)		(unpack(unpack5(%1,%2,%3,%4,%5,%6),%7))
#define unpack7(%1,%2,%3,%4,%5,%6,%7,%8)	(unpack(unpack6(%1,%2,%3,%4,%5,%6,%7),%8))
#define unpack8(%1,%2,%3,%4,%5,%6,%7,%8,%9)	(unpack(unpack7(%1,%2,%3,%4,%5,%6,%7,%8),%9))