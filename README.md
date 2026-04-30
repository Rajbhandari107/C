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
