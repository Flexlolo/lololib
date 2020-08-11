#if defined _lololib_macros_included
  #endinput
#endif
#define _lololib_macros_included

#define int(%1) view_as<int>(%1)

#define unpack(%1,%2) (view_as<ArrayList>(%1.Get(%2)))
#define unpack2(%1,%2,%3) (unpack(unpack(%1,%2),%3))
#define unpack3(%1,%2,%3,%4) (unpack(unpack2(%1,%2,%3),%4))
#define unpack4(%1,%2,%3,%4,%5) (unpack(unpack3(%1,%2,%3,%4),%5))
#define unpack5(%1,%2,%3,%4,%5,%6) (unpack(unpack4(%1,%2,%3,%4,%5),%6))
#define unpack6(%1,%2,%3,%4,%5,%6,%7) (unpack(unpack5(%1,%2,%3,%4,%5,%6),%7))
#define unpack7(%1,%2,%3,%4,%5,%6,%7,%8) (unpack(unpack6(%1,%2,%3,%4,%5,%6,%7),%8))
#define unpack8(%1,%2,%3,%4,%5,%6,%7,%8,%9) (unpack(unpack7(%1,%2,%3,%4,%5,%6,%7,%8),%9))
#define unpackable(%1,%2) ((%2)<(view_as<ArrayList>(%1).Length)?(true):(false))
#define unpackable2(%1,%2,%3) ((unpackable(%1,%2))?(unpackable(unpack(%1,%2),%3)):(false))
#define unpackable3(%1,%2,%3,%4) ((unpackable2(%1,%2,%3))?(unpackable(unpack2(%1,%2,%3),%4)):(false))
#define unpackable4(%1,%2,%3,%4,%5) ((unpackable3(%1,%2,%3,%4))?(unpackable(unpack3(%1,%2,%3,%4),%5)):(false))
#define unpackable5(%1,%2,%3,%4,%5,%6) ((unpackable4(%1,%2,%3,%4,%5))?(unpackable(unpack4(%1,%2,%3,%4,%5),%6)):(false))
#define unpackable6(%1,%2,%3,%4,%5,%6,%7) ((unpackable5(%1,%2,%3,%4,%5,%6))?(unpackable(unpack5(%1,%2,%3,%4,%5,%6),%7)):(false))
#define unpackable7(%1,%2,%3,%4,%5,%6,%7,%8) ((unpackable6(%1,%2,%3,%4,%5,%6,%7))?(unpackable(unpack6(%1,%2,%3,%4,%5,%6,%7),%8)):(false))
#define unpackable8(%1,%2,%3,%4,%5,%6,%7,%8,%9) ((unpackable7(%1,%2,%3,%4,%5,%6,%7,%8))?(unpackable(unpack7(%1,%2,%3,%4,%5,%6,%7,%8),%9)):(false))
#define safeunpack(%1,%2) ((unpackable(%1,%2))?(unpack(%1,%2)):(null))
#define safeunpack2(%1,%2,%3) ((unpackable2(%1,%2,%3))?(unpack2(%1,%2,%3)):(null))
#define safeunpack3(%1,%2,%3,%4) ((unpackable3(%1,%2,%3,%4))?(unpack3(%1,%2,%3,%4)):(null))
#define safeunpack4(%1,%2,%3,%4,%5) ((unpackable4(%1,%2,%3,%4,%5))?(unpack4(%1,%2,%3,%4,%5)):(null))
#define safeunpack5(%1,%2,%3,%4,%5,%6) ((unpackable5(%1,%2,%3,%4,%5,%6))?(unpack5(%1,%2,%3,%4,%5,%6)):(null))
#define safeunpack6(%1,%2,%3,%4,%5,%6,%7) ((unpackable6(%1,%2,%3,%4,%5,%6,%7))?(unpack6(%1,%2,%3,%4,%5,%6,%7)):(null))
#define safeunpack7(%1,%2,%3,%4,%5,%6,%7,%8) ((unpackable7(%1,%2,%3,%4,%5,%6,%7,%8))?(unpack7(%1,%2,%3,%4,%5,%6,%7,%8)):(null))
#define safeunpack8(%1,%2,%3,%4,%5,%6,%7,%8,%9) ((unpackable8(%1,%2,%3,%4,%5,%6,%7,%8,%9))?(unpack8(%1,%2,%3,%4,%5,%6,%7,%8,%9)):(null))
