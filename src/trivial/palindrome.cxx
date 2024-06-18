#include <iostream>
#include <string>
#include <vector>

using namespace std;

extern "C" {
    int solution_cxx(const char *s, int n);
}

int solution_cxx(const char *s, int n) {
    int ans = 0;
    if (n == 1) {
        return 2;
    }
    vector<vector<bool>>mp(n + 1, vector<bool>(n + 1, false));
    bool isOk = true;

    for(int i = n / 2;i <= n - 2;i++) {
        mp[n - 2 - i][i] = (isOk && s[i] == s[n - 2 - i]);
        isOk = mp[n - 2 - i][i];
    }
    isOk = true;
    for (int i = n / 2; i >= 1;i--) {
        mp[i][n - i] = (isOk && s[i] == s[n - i]);
        isOk = mp[i][n - i];
    }
    if (!(n & 1)) mp[n / 2 - 1][n / 2 - 1] = true;
    /*for (int i = 0;i <= n;i++) {
        for (int j = 0;j <= n;j++) {
        cout << i << " " << j << " " << mp[i][j] << " " << '\n';
        }
    }*/
    for (int i = 0;i <= n / 2;i++) {
        int l = i - 1, r = n - i;
        bool left = true, right = true;
        if (l >= 0 && r >= 0 && (s[l] != s[r])) right = false;
        if (i <= n / 2 - 1 && !mp[i][n - 2 - i]) left = false;
        if (left && right) ans++;
        else if(!right)break;
    }
    int m = n / 2 + 1;
    if (!(n & 1)) m = n / 2;
    for (int i = 1; i <= m;i++) {
        int l = i - 2, r = n - i + 1;
        bool left = true, right = true;
        if (l >= 0 && r >= 0 && (s[l] != s[r])) right = false;
        if (i <= n / 2 && !mp[i][n - i]) left = false;
        if (left && right) ans++;
        else if(!right)break;
    }
    return ans;
}