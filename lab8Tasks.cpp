#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <iomanip>
using namespace std;
 
// task 1                          
pair<int,int> findPeak(const vector<vector<int>>& a) {
    int rows = a.size(), lo = 0, hi = a[0].size() - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2, r = 0;
        for (int i = 0; i < rows; i++)            // row of max in mid column
            if (a[i][mid] > a[r][mid]) r = i;
        bool leftBigger  = mid > 0 && a[r][mid - 1] > a[r][mid];
        bool rightBigger = mid < (int)a[0].size() - 1 && a[r][mid + 1] > a[r][mid];
        if (leftBigger) hi = mid - 1;
        else if (rightBigger) lo = mid + 1;
        else return {r, mid};
    }
    return {-1, -1};
}
 
// task 2
int N;
int board[20][20];
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
 
bool ok(int x, int y) { return x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1; }
 
int degree(int x, int y) {                         // onward moves from (x,y)
    int c = 0;
    for (int k = 0; k < 8; k++) if (ok(x + dx[k], y + dy[k])) c++;
    return c;
}
 
bool tour(int x, int y, int step) {
    board[x][y] = step;
    if (step == N * N - 1) return true;            // all squares visited
    int order[8], deg[8], n = 0;                   // candidate moves
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if (ok(nx, ny)) { order[n] = k; deg[n] = degree(nx, ny); n++; }
    }
    for (int i = 0; i < n; i++)                    // sort by fewest onward moves
        for (int j = i + 1; j < n; j++)
            if (deg[j] < deg[i]) { swap(deg[i], deg[j]); swap(order[i], order[j]); }
    for (int i = 0; i < n; i++)
        if (tour(x + dx[order[i]], y + dy[order[i]], step + 1)) return true;
    board[x][y] = -1;                              // backtrack
    return false;
}
 
// task 3
void moveLegal(stack<int>& a, stack<int>& b, char na, char nb) {
    if (b.empty() || (!a.empty() && a.top() < b.top())) {
        cout << "Move disk " << a.top() << " from " << na << " to " << nb << "\n";
        b.push(a.top()); a.pop();
    } else {
        cout << "Move disk " << b.top() << " from " << nb << " to " << na << "\n";
        a.push(b.top()); b.pop();
    }
}
 
void hanoi(int n) {
    stack<int> S, A, D;                            // source, aux, destination
    char ns = 'A', na = 'B', nd = 'C';
    if (n % 2 == 0) swap(na, nd);                  // even N: swap aux and dest roles
    for (int i = n; i >= 1; i--) S.push(i);
    long long total = (1LL << n) - 1;
    for (long long i = 1; i <= total; i++) {
        if (i % 3 == 1)      moveLegal(S, D, ns, nd);
        else if (i % 3 == 2) moveLegal(S, A, ns, na);
        else                 moveLegal(A, D, na, nd);
    }
}
 
int main() {
    // task 1
    vector<vector<int>> m = {{10, 8, 10, 10}, {14, 13, 12, 11}, {15, 9, 11, 21}, {16, 17, 19, 20}};
    auto p = findPeak(m);
    cout << "Peak at (" << p.first << "," << p.second << ") = " << m[p.first][p.second] << "\n\n";
 
    // task 2
    N = 8;
    for (auto& r : board) for (int& c : r) c = -1;
    int sx = 0, sy = 0;
    if (tour(sx, sy, 0)) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) cout << setw(3) << board[i][j];
            cout << "\n";
        }
    } else cout << "No tour exists\n";
    cout << "\n";
 
    // task 3
    hanoi(3);
    return 0;
}
 