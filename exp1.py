from collections import defaultdict, deque

def epsilon_closure(states, transitions):
    stack = list(states)
    closure = set(states)

    while stack:
        state = stack.pop()
        for nxt in transitions.get((state, 'e'), []):
            if nxt not in closure:
                closure.add(nxt)
                stack.append(nxt)

    return closure


def move(states, symbol, transitions):
    result = set()
    for s in states:
        result |= set(transitions.get((s, symbol), []))
    return result


def nfa_to_dfa(states, alphabet, transitions, start, accept):
    start_closure = frozenset(epsilon_closure({start}, transitions))
    dfa_states = {start_closure}
    queue = deque([start_closure])
    dfa_trans = {}
    dfa_accept = set()

    while queue:
        current = queue.popleft()

        for symbol in alphabet:
            nxt = frozenset(
                epsilon_closure(move(current, symbol, transitions), transitions)
            )
            dfa_trans[(current, symbol)] = nxt

            if nxt not in dfa_states:
                dfa_states.add(nxt)
                queue.append(nxt)

    for state in dfa_states:
        if any(s in accept for s in state):
            dfa_accept.add(state)

    return dfa_states, dfa_trans, start_closure, dfa_accept


# -------- INPUT --------
n = int(input("Number of states: "))
states = set(input("States: ").split())

alphabet = set(input("Alphabet (space separated): ").split())

t = int(input("Number of transitions: "))
transitions = defaultdict(list)

print("Enter transitions (from symbol to) (use e for epsilon):")
for _ in range(t):
    s, sym, d = input().split()
    transitions[(s, sym)].append(d)

start = input("Start state: ")
accept = set(input("Accept states: ").split())

# -------- CONVERSION --------
dfa_states, dfa_trans, dfa_start, dfa_accept = nfa_to_dfa(
    states, alphabet, transitions, start, accept
)

# -------- OUTPUT --------
print("\nDFA States:")
for s in dfa_states:
    print(set(s))

print("\nDFA Start State:")
print(set(dfa_start))

print("\nDFA Accept States:")
for s in dfa_accept:
    print(set(s))

print("\nDFA Transitions:")
for (state, sym), nxt in dfa_trans.items():
    print(f"{set(state)} --{sym}--> {set(nxt)}")

Number of states: 3
States: q0 q1 q2
Alphabet (space separated): 0 1
Number of transitions: 3
q0 0 q1
q0 1 q0
q1 1 q2
Start state: q0
Accept states: q2
