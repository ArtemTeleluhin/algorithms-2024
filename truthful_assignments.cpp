#include <iostream>
#include <vector>

int main() {
    int count_instructions;
    int max_resources;
    std::cin >> count_instructions >> max_resources;
    std::vector<int> need_resources(count_instructions);
    for (int i = 0; i < count_instructions; ++i) {
        std::cin >> need_resources[i];
    }
    std::vector<int> rewards(count_instructions);
    for (int i = 0; i < count_instructions; ++i) {
        std::cin >> rewards[i];
    }

    std::vector<std::vector<int>> dp(count_instructions + 1,
                                     std::vector<int>(max_resources + 1, 0));
    std::vector<std::vector<bool>> take(
            count_instructions + 1, std::vector<bool>(max_resources + 1, false));
    for (int i = 1; i <= count_instructions; ++i) {
        for (int j = 0; j <= max_resources; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= need_resources[i - 1] &&
                dp[i - 1][j - need_resources[i - 1]] + rewards[i - 1] > dp[i][j]) {
                dp[i][j] = dp[i - 1][j - need_resources[i - 1]] + rewards[i - 1];
                take[i][j] = true;
            }
        }
    }

    int best_reward_resources = 0;
    for (int i = 1; i <= max_resources; ++i) {
        if (dp[count_instructions][best_reward_resources] <
            dp[count_instructions][i]) {
            best_reward_resources = i;
        }
    }
    std::vector<int> answer;
    for (int i = count_instructions; i > 0; --i) {
        if (take[i][best_reward_resources]) {
            answer.push_back(i);
            best_reward_resources -= need_resources[i - 1];
        }
    }
    for (int i = int(answer.size()) - 1; i >= 0; --i) {
        std::cout << answer[i] << "\n";
    }
    return 0;
}