#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST, FOLLOW;
set<char> terminals, nonTerminals;

char startSymbol;

// -------- FIRST --------
set<char> findFirst(char X) {
    if (!isupper(X)) return {X};

    if (!FIRST[X].empty()) return FIRST[X];

    for (auto prod : grammar[X]) {
        for (int i = 0; i < prod.size(); i++) {
            set<char> temp = findFirst(prod[i]);

            for (char c : temp)
                if (c != 'e') FIRST[X].insert(c);

            if (temp.find('e') == temp.end())
                break;

            if (i == prod.size() - 1)
                FIRST[X].insert('e');
        }
    }
    return FIRST[X];
}

// -------- FOLLOW --------
void findFollow(char X) {
    if (X == startSymbol)
        FOLLOW[X].insert('$');

    for (auto g : grammar) {
        char A = g.first;

        for (auto prod : g.second) {
            for (int i = 0; i < prod.size(); i++) {
                if (prod[i] == X) {

                    if (i + 1 < prod.size()) {
                        set<char> temp = findFirst(prod[i + 1]);

                        for (char c : temp)
                            if (c != 'e') FOLLOW[X].insert(c);

                        if (temp.find('e') != temp.end())
                            FOLLOW[X].insert(FOLLOW[A].begin(), FOLLOW[A].end());
                    }
                    else {
                        if (X != A)
                            FOLLOW[X].insert(FOLLOW[A].begin(), FOLLOW[A].end());
                    }
                }
            }
        }
    }
}

// -------- MAIN --------
int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (A->aB):\n";
    for (int i = 0; i < n; i++) {
        string prod;
        cin >> prod;

        char lhs = prod[0];
        string rhs = prod.substr(3);

        grammar[lhs].push_back(rhs);
        nonTerminals.insert(lhs);

        for (char c : rhs) {
            if (!isupper(c) && c != 'e')
                terminals.insert(c);
        }

        if (i == 0) startSymbol = lhs;
    }

    // FIRST
    for (auto nt : nonTerminals)
        findFirst(nt);

    // FOLLOW
    for (auto nt : nonTerminals)
        findFollow(nt);

    // -------- OUTPUT --------
    cout << "\nFIRST:\n";
    for (auto nt : nonTerminals) {
        cout << nt << " = { ";
        for (auto c : FIRST[nt]) cout << c << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW:\n";
    for (auto nt : nonTerminals) {
        cout << nt << " = { ";
        for (auto c : FOLLOW[nt]) cout << c << " ";
        cout << "}\n";
    }

    // -------- Parsing Table --------
    cout << "\nPredictive Parsing Table:\n";

    for (auto A : grammar) {
        for (auto prod : A.second) {
            set<char> firstSet;

            if (!isupper(prod[0]))
                firstSet.insert(prod[0]);
            else
                firstSet = FIRST[prod[0]];

            for (char t : firstSet) {
                if (t != 'e')
                    cout << "M[" << A.first << "," << t << "] = " << A.first << "->" << prod << "\n";
            }

            if (firstSet.find('e') != firstSet.end()) {
                for (char f : FOLLOW[A.first]) {
                    cout << "M[" << A.first << "," << f << "] = " << A.first << "->" << prod << "\n";
                }
            }
        }
    }

    return 0;
}

Enter number of productions: 3
E->TR
R->+TR
R->e
