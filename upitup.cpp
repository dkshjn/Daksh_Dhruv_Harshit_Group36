#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include <cmath>
#include <queue>
#include <cassert>
#include <cstdint>
#include <queue>

using namespace std;

struct Board {
    int cells[3][3];
};

enum {
    X = 1,
    O = 2
};

void printBoard(const Board& board) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            cout << board.cells[r][c] << " ";
        }
        cout << endl;
    }
    return;
}

pair<int, int> findSpace(const Board& board) {
    int r = 0, c = 0;
    for (r = 0; r < 3; r++) {
        for (c = 0; c < 3; c++) {
            if (board.cells[r][c] == 0) {
                return make_pair(r, c);
            }
        }
    }
    assert(0);
}

bool checkValid(const Board& board) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board.cells[r][c] > 1) {
                return false;
            }
            if ((r * c == 1)) {
                if (board.cells[1][1] != 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

int ord(const Board& board) {
    int o = 0;
    int i = 0;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            o += board.cells[r][c] * pow(7, i);
            i++;
        }
    }
    return o;
}

Board moveUp(const Board& b, int r, int c) {
    Board bNew = b;
    int val = b.cells[r - 1][c];
    if (val == 1) {
        val = 6;
    } else if (val == 2) {
        val = 5;
    } else if (val == 5) {
        val = 1;
    } else if (val == 6) {
        val = 2;
    }
    bNew.cells[r][c] = val;
    bNew.cells[r - 1][c] = 0;

    return bNew;
}

Board moveDown(const Board& b, int r, int c) {
    Board bNew = b;
    int val = b.cells[r + 1][c];
    if (val == 1) {
        val = 5;
    } else if (val == 2) {
        val = 6;
    } else if (val == 5) {
        val = 2;
    } else if (val == 6) {
        val = 1;
    }
    bNew.cells[r][c] = val;
    bNew.cells[r + 1][c] = 0;
    return bNew;
}

Board moveLeft(const Board& b, int r, int c) {
    Board bNew = b;
    int val = b.cells[r][c - 1];
    if (val == 1) {
        val = 4;
    } else if (val == 2) {
        val = 3;
    } else if (val == 3) {
        val = 1;
    } else if (val == 4) {
        val = 2;
    }
    bNew.cells[r][c] = val;
    bNew.cells[r][c - 1] = 0;
    return bNew;
}

Board moveRight(const Board& b, int r, int c) {
    Board bNew = b;
    int val = b.cells[r][c + 1];
    if (val == 1) {
        val = 3;
    } else if (val == 2) {
        val = 4;
    } else if (val == 3) {
        val = 2;
    } else if (val == 4) {
        val = 1;
    }
    bNew.cells[r][c] = val;
    bNew.cells[r][c + 1] = 0;
    return bNew;
}

uint8_t visited[40353600] = {0};
uint64_t parent[40353600];

vector<char> solve(const Board& b) {
    int count = 0;
    queue<Board> q;
    q.push(b);
    visited[ord(b)] = 'S'; // S means start
    while (!q.empty()) {
        Board u = q.front();
        q.pop();
        if (checkValid(u)) {
            vector<char> moves;
            int o = ord(u);
            while (visited[o] != 'S') {
                moves.push_back(visited[o]);
                o = parent[o];
            }
            reverse(moves.begin(), moves.end());
            printBoard(u);
            return moves;
        }

        auto p = findSpace(u);
        int row = p.first;
        int col = p.second;
        Board a, b, c, d;
        if (row != 0) {
            a = moveUp(u, row, col);
            int aord = ord(a);
            if (!visited[aord]) {
                visited[aord] = 'U';
                parent[aord] = ord(u);
                q.push(a);
                count++;
            }
        }
        if (row != 2) {
            b = moveDown(u, row, col);
            int bord = ord(b);
            if (!visited[bord]) {
                visited[bord] = 'D';
                parent[bord] = ord(u);
                q.push(b);
                count++;
            }
        }
        if (col != 0) {
            c = moveLeft(u, row, col);
            int cord = ord(c);
            if (!visited[cord]) {
                visited[cord] = 'L';
                parent[cord] = ord(u);
                q.push(c);
                count++;
            }
        }
        if (col != 2) {
            d = moveRight(u, row, col);
            int dord = ord(d);
            if (!visited[dord]) {
                visited[dord] = 'R';
                parent[dord] = ord(u);
                q.push(d);
                count++;
            }
        }
    }
    vector<char> v;
    v.push_back(0);
    return v;
}

void readBoard(Board& b) {
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (r * c == 1) {
                b.cells[r][c] = 0;
            } else {
                int val = 2;
                // cin >> val;
                assert(val != 0);
                b.cells[r][c] = val;
            }
        }
    }
    return;
}

int main() {
    Board b;
    readBoard(b);
    printBoard(b);
    auto moves = solve(b);
    if (moves[0] == 0) {
        cout << "The board is unsolvable";
    }
    for (char c : moves) {
        cout << c << endl;
    }
    return 0;
}
