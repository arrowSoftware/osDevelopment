General-Purpose Registers (GPR) - 16-bit naming conventions
The 8 GPRs are:
    1. Accumulator register (AX). Used in arithmetic operations
    2. Counter register (CX). Used in shift/rotate instructions and loops.
    3. Data register (DX). Used in arithmetic operations and I/O operations.
    4. Base register (BX). Used as a pointer to data (located in segment register DS, when in segmented mode).
    5. Stack Pointer register (SP). Pointer to the top of the stack.
    6. Stack Base Pointer register (BP). Used to point to the base of the stack.
    7. Source Index register (SI). Used as a pointer to a source in stream operations.
    8. Destination Index register (DI). Used as a pointer to a destination in stream operations.

The order in which they are listed here is for a reason: it is the same order that is used in a push-to-stack operation.

+--------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
|Register|     Accumulator    |       Counter      |        Data        |         Base       |    Stack Pointer   ||Stack Base Pointer |        Source      |     Destination    |
+--------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+--------------------+
|64-bit  |         RAX        |         RCX        |         RDX        |         RBX        |         RSP        |         BSP        |         RSI        |         RDI        |
+--------+--------+-----------+--------+-----------+--------+-----------+--------+-----------+--------+-----------+--------+-----------+--------+-----------+--------+-----------+
|32-bit  |        |    EAX    |        |    ECX    |        |    EDX    |        |    EBX    |        |    ESP    |        |    EBP    |        |    ESI    |        |    EDI    |
+--------+--------+-----+-----+--------+-----+-----+--------+-----+-----+--------+-----+-----+--------+-----+-----+--------+-----+-----+--------+-----+-----+--------+-----+-----+
|16-bit  |              | AX  |              | CX  |              | DX  |              | BX  |              | SP  |              | BP  |              | SI  |              | DI  |
+--------+--------------+--+--+--------------+--+--+--------------+--+--+--------------+--+--+--------------+-----+--------------+-----+--------------+-----+--------------+-----+
|8-bit   |              |AH|AL|              |CH|CL|              |DH|DL|              |BH|BL|              | SPL |              | BPL |              | SIL |              | DIL |
+--------+--------------+--+--+--------------+--+--+--------------+--+--+--------------+--+--+--------------+-----+--------------+-----+--------------+-----+--------------+-----+


Segment Registers
The 6 Segment Registers are:
1. Stack Segment (SS). Pointer to the stack.
2. Code Segment (CS). Pointer to the code.
3. Data Segment (DS). Pointer to the data.
4. Extra Segment (ES). Pointer to extra data ('E' stands for 'Extra').
5. F Segment (FS). Pointer to more extra data ('F' comes after 'E').
6. G Segment (GS). Pointer to still more extra data ('G' comes after 'F').
