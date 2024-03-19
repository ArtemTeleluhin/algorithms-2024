#include <iostream>
#include <string>
#include <vector>

const long long int kMod = 1'000'000'007;

int Bit(int mask, int bit_number) {
    if ((mask & (1 << bit_number)) == 0) {
        return 0;
    }
    return 1;
}

bool CheckResolution(int variant, char resolution) {
    return (resolution != '-' || variant != 1) &&
           (resolution != '+' || variant != 0);
}

void DynamicsBase(int n, std::vector<std::string>& city_map,
                  std::vector<std::vector<long long int>>& dp) {
    for (int mask = 0; mask < (1 << n); ++mask) {
        bool is_suitable = true;
        for (int i = 0; i < n; ++i) {
            if (!CheckResolution(Bit(mask, i), city_map[i][0])) {
                is_suitable = false;
                break;
            }
        }
        if (is_suitable) {
            dp[0][mask] = 1;
        }
    }
}

bool CheckMask(int col, int mask, int n, std::vector<std::string>& city_map,
               std::vector<std::vector<long long int>>& dp) {
    bool is_suitable = true;
    for (int i = 0; i < n; ++i) {
        if (!CheckResolution(Bit(mask, i), city_map[i][col])) {
            is_suitable = false;
            break;
        }
    }
    if (!is_suitable) {
        return false;
    }
    if (is_suitable && col == 0) {
        dp[col][mask] = 1;
        return false;
    }
    return true;
}

void DynamicsRecalculation(int col, int mask, int n,
                           std::vector<std::string>& city_map,
                           std::vector<std::vector<long long int>>& dp) {
    for (int first_bit = 0; first_bit <= 1; ++first_bit) {
        if (!CheckResolution(first_bit, city_map[0][col - 1])) {
            continue;
        }
        int previous_mask = first_bit;
        bool is_suitable = true;
        for (int i = 1; i < n; ++i) {
            int next_bit =
                    2 - Bit(previous_mask, i - 1) - Bit(mask, i) - Bit(mask, i - 1);
            if ((next_bit != 0 && next_bit != 1) ||
                !CheckResolution(next_bit, city_map[i][col - 1])) {
                is_suitable = false;
                break;
            }
            previous_mask += (next_bit << i);
        }
        if (is_suitable) {
            dp[col][mask] = (dp[col][mask] + dp[col - 1][previous_mask]) % kMod;
        }
    }
}

int main() {
    int n_size;
    int m_size;
    std::cin >> n_size >> m_size;
    std::vector<std::string> city_map(n_size);
    for (int i = 0; i < n_size; ++i) {
        std::cin >> city_map[i];
    }

    std::vector<std::vector<long long int>> dp(
            m_size, std::vector<long long int>(1 << n_size, 0));
    DynamicsBase(n_size, city_map, dp);
    long long int answer = 0;

    for (int col = 0; col < m_size; ++col) {
        for (int mask = 0; mask < (1 << n_size); ++mask) {
            if (!CheckMask(col, mask, n_size, city_map, dp)) {
                continue;
            }
            DynamicsRecalculation(col, mask, n_size, city_map, dp);
            if (col == m_size - 1) {
                answer = (answer + dp[col][mask]) % kMod;
            }
        }
    }

    std::cout << answer << "\n";
    return 0;
}