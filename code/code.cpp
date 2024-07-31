#include <bits/stdc++.h>

std::vector<long long> getNumbers(int n) {
  std::vector<long long> out;
  for (long long i = 1; i < (1 << std::to_string(n).length()); i++) {
    out.push_back(stoi(std::bitset<sizeof(n) * 8>(i).to_string()));
  }
  return out;
}

long long dpTotal(std::vector<long long> &coins, long long n, long long sum) {
  std::vector<std::vector<long long>> dp(n + 1, std::vector<long long>(sum + 1, 0));
  dp[0][0] = 1;
  for (long long i = 1; i <= n; i++) {
    for (long long j = 0; j <= sum; j++) {
      dp[i][j] += dp[i - 1][j];
      if (j - coins[i - 1] >= 0) {
        dp[i][j] += dp[i][j - coins[i - 1]];
      }
    }
  }
  return dp[n][sum];
}

long long countTotal(long long n) {
  std::vector<long long> coins = getNumbers(n);
  return dpTotal(coins, coins.size(), n);
}

long long countMin(long long n) {
  long long dp[n + 1];
  dp[0] = 0;
  for (long long i = 1; i <= n; i++) {
    dp[i] = INT_MAX;
    for (auto c : getNumbers(n)) {
      if (i - c >= 0) {
        dp[i] = std::min(dp[i], dp[i - c] + 1);
      }
    }
  }
  return dp[n];
}

int main() {

  printf("%lld\n", countTotal(1337));
  printf("%lld\n", countMin(12345));

  return 0;
}
