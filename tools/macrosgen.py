#!/usr/bin/env python
"""
Usage:
  macrosgen.py <length>

Macros generator for sourcepawn
"""

import sys
from docopt import docopt

def unpack(length):
	print('#define unpack(%1,%2) (view_as<ArrayList>(%1.Get(%2)))')

	for i in range(2, length + 1):
		#define unpack2(%1,%2,%3) (unpack(unpack(%1,%2),%3))

		fl = 'unpack' if i == 2 else 'unpack' + str(i - 1)
		f = 'unpack' + str(i)
		a = '%' + ',%'.join([str(i) for i in range(1, i + 2)])
		al = '%' + ',%'.join([str(i) for i in range(1, i + 1)])
		macros = f'#define {f}({a}) (unpack({fl}({al}),%{i + 1}))'
		print(macros)

def unpackable(length):
	unpack(length)

	print('#define unpackable(%1,%2) ((%2)<(view_as<ArrayList>(%1).Length)?(true):(false))')

	for i in range(2, length + 1):
		#define unpackable2(%1,%2,%3) ((unpackable(%1,%2))?(unpackable(unpack(%1,%2),%3)):(false))

		ful = 'unpackable' if i == 2 else 'unpackable' + str(i - 1)
		fcl = 'unpack' if i == 2 else 'unpack' + str(i - 1)
		fu = 'unpack' + str(i)
		fc = 'unpackable' + str(i)
		a = '%' + ',%'.join([str(i) for i in range(1, i + 2)])
		al = '%' + ',%'.join([str(i) for i in range(1, i + 1)])
		macros = f'#define {fc}({a}) (({ful}({al}))?(unpackable({fcl}({al}),%{i+1})):(false))'
		print(macros)

def safeunpack(length):
	unpackable(length)

	for i in range(1, length + 1):
		#define safeunpack(%1,%2) ((unpackable(%1,%2))?(unpack(%1,%2)):(null))

		fu =  'unpack' if i == 1 else 'unpack' + str(i)
		fc = 'unpackable' if i == 1 else 'unpackable' + str(i)
		fs = 'safeunpack' if i == 1 else 'safeunpack' + str(i)
		a = '%' + ',%'.join([str(i) for i in range(1, i + 2)])
		macros = f'#define {fs}({a}) (({fc}({a}))?({fu}({a})):(null))'
		print(macros)

def main():

	args = docopt(__doc__)
	length = int(args['<length>'])
	safeunpack(length)

try:
	main()
except KeyboardInterrupt:
	print('\nExiting.')
	sys.exit(130)
