#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int min(int x, int y, int z)
{
    if (x < y && x < z)
        return x;
    else if (y < x && y < z)
        return y;
    else
        return z;
}

int editDistance(const string& x, const string& y) {

    int m = x.length();
    int n = y.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1,0));

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // If first string is empty
            if (i == 0)
                dp[i][j] = j;
            // second string is empty
            else if (j == 0)
                dp[i][j] = i;
    }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i-1] == y[j-1]) { // if x[i] = y[j] 
                dp[i][j] = dp[i - 1][j - 1];
            } else { // otherwise: insert, remove or sub
                dp[i][j] = 1 + min(dp[i][j-1], dp[i-1][j], dp[i - 1][j - 1]);
            }
        }
    }



vector<string> changeSequence; // initialize a vector of strings to output needed changes from string to string
int i = m;
int j = n;
    while (i > 0 || j > 0) { // check what change is needed or if change is needed at all. 
        if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            changeSequence.push_back("Delete " + string(1, x[i - 1]));
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            changeSequence.push_back("Insert " + string(1, y[j - 1]));
            j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            changeSequence.push_back("Substitute " + string(1, x[i - 1]) + " into " + string(1, y[j - 1]));
            i--;
            j--;
        } else {
            i--;
            j--;
        }
    }
    reverse(changeSequence.begin(), changeSequence.end());  // Reverse and Print the sequence of changes

    for (const auto& change : changeSequence) {
        cout << change << endl;
    }

   return dp[m][n];
}

int main() {
    string x;
    string y;
    cout << "Enter first string." << endl;
    cin >> x;
    cout << "Enter second string." << endl;
    cin >> y;
    int distance = editDistance(x, y);
    cout << "Edit distance: " << distance << endl;

    return 0;
}