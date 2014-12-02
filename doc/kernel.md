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

IDATA tape: stores data increments and decrements<br>
IPTR  tape: stores PTR increments and decrements<br>
IJMP  tape: stores INSTR increments and decrements<br>

Pointers/counters:

PTR   counter: index to the data tape<br>
INSTR counter: index to the instruction tapes<br>

- - -

Order of instructions:

00 - DATA[PTR] += IDATA[INSTR]<br>

01 - PTR += IPTR[INSTR]<br>

02 - IJMP[INSTR]:<br>
	JMP = IJMP[INSTR]<br>
	if JMP < 0 (']'):<br>
		if DATA[PTR] != 0: INSTR += IJMP[INSTR]<br>
	if JMP > 0 ('['):<br>
		if DATA[PTR] == 0: INSTR += IJMP[INSTR]<br>
	if JMP = 0: do nothing<br>

03 - INSTR++

