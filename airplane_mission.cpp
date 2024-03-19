#include <iostream>
#include <vector>

int const kMAXRANK = 17;

int main() {
    int max_height;
    int planes_count;
    std::cin >> max_height >> planes_count;

    if (max_height == 1) {
        std::cout << "0\n";
        return 0;
    }
    if (planes_count == 0) {
        std::cout << "-1\n";
        return 0;
    }

    if (planes_count > kMAXRANK || max_height <= (1 << planes_count)) {
        for (int i = 1;; ++i) {
            if (max_height <= (1 << i)) {
                std::cout << i << "\n";
                return 0;
            }
        }
    }

    std::vector<std::vector<int>> dp(max_height + 1,
                                     std::vector<int>(planes_count + 1, 0));
    for (int i = 1; i <= max_height; ++i) {
        dp[i][1] = i - 1;
    }

    for (int j = 2; j <= planes_count; ++j) {
        dp[2][j] = 1;
        int optimal_inspection_height = 1;
        for (int i = 3; i <= max_height; ++i) {
            dp[i][j] = 1 + std::max(dp[optimal_inspection_height][j - 1],
                                    dp[i - optimal_inspection_height][j]);
            do {
                int new_value = 1 + std::max(dp[optimal_inspection_height + 1][j - 1],
                                             dp[i - optimal_inspection_height - 1][j]);
                if (new_value < dp[i][j]) {
                    dp[i][j] = new_value;
                    ++optimal_inspection_height;
                } else {
                    break;
                }
            } while (optimal_inspection_height < i - 1);
        }
    }
    std::cout << dp[max_height][planes_count] << "\n";
    return 0;
}