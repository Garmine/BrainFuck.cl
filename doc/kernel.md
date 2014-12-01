OpenCL kernels
==============

There's only one type of OpenCL kernel which is basically a limited BranFuck
interpreter: every operator but the IO ones are legal: +-><[]

This means that a BF code can be simplified to 3 instruction tapes, a data tape
and 2 pointers/counters.

As the code is stored in instruction tapes and the current state is stored in
the data tape and the pointers, the BF code is considered data to the OpenCL
kernel. This means that SIMD is not violated even if every core runs a
different BranFuck code. Thus even massively parallel architectures (e.g. GPUs)
can function as a many-core BrainFuck CPU.

- - -

DATA tape:

Assigned to a BF kernel before running. Intruction tapes are static, created on
compilation. PTR is 0 on start, INSTR can be set to any non-negative integer.

Instruction tapes:

IDATA tape: stores data increments and decrements
IPTR  tape: stores PTR increments and decrements
IJMP  tape: stores INSTR increments and decrements

Pointers/counters:

PTR   counter: index to the data tape
INSTR counter: index to the instruction tapes

- - -

Order of instructions:

00 - DATA[PTR] += IDATA[INSTR]

01 - PTR += IPTR[INSTR]

02 - IJMP[INSTR]:
	JMP = IJMP[INSTR]
	if JMP < 0 (']'):
		if DATA[PTR] != 0: INSTR += IJMP[INSTR]
	if JMP > 0 ('['):
		if DATA[PTR] == 0: INSTR += IJMP[INSTR]
	if JMP = 0: do nothing

03 - INSTR++

