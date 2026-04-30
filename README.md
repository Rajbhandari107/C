exp 10

3
E->E+T
E->T
T->id


LR(0) Items (Closure):
E->.E+T
E->.T
T->.id

Transitions (GOTO):
GOTO: E->E.+T
GOTO: E->T.
GOTO: T->i.d

exp11

a+b*c

t1 = b * c
t2 = a + t


Sample Input
a=b+c*d
Sample Output (cleaned)
Quadruple
Op   Arg1 Arg2 Result
*    c    d    t1
+    b    t1   t2
Triple
Index Op  Arg1 Arg2
0     *   c    d
1     +   b    (0)
Indirect Triple
Pointer Table:
Pointer[0] -> 0
Pointer[1] -> 1


exp12

Sample Input
a=b+c*d
Sample Output
--- Generated Code ---
MOV R0, c
MUL R0, d
MOV a, R0
MOV R0, b
ADD R0, c
MOV a, R0
