#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int a = 0, traceNumber = 0;

double calc(int a, int b, std::string cities[4][15]) {
    double suma = 0;
    double x1, y1, x2, y2;
    x1 = std::stod(cities[2][a]);
    y1 = std::stod(cities[2][b]);
    x2 = std::stod(cities[3][a]);
    y2 = std::stod(cities[3][b]);
    suma = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return suma;
}

void salesman(int* table, int n, std::string cities[4][15], double *results, int resultsSize) {
    double result = 0;
    for (int i = 0; i < n-1; i++) {
        result += calc(table[i], table[i + 1], cities);
    }
    results[a] = result;
    a++;
    std::cout << "Length of path between " << cities[0][table[0]] << " & " << cities[0][table[n - 1]] << " has: " << result << std::endl;
}

void generatePermutations(std::vector<int>& nums, std::vector<bool>& chosen, std::vector<int>& permutation, std::string cities[4][15], double *results, int resultsSize, std::vector<std::vector<int>> &vectorOfVectors) {
    if (permutation.size() == nums.size()) {
        int* table = new int[nums.size()];
        vectorOfVectors.push_back(permutation);
        int i = 0;
        std::cout << a+1 << ". ";
        for (int num : permutation) {
            std::cout << num << " ";
            table[i] = num;
            i++;
        }
        std::cout << std::endl;
        salesman(table, nums.size(), cities, results, resultsSize);
        delete[] table;
        return;
    }

    for (int i = 0; i < nums.size(); ++i) {
        if (!chosen[i]) {
            chosen[i] = true;
            permutation.push_back(nums[i]);
            generatePermutations(nums, chosen, permutation, cities, results, resultsSize, vectorOfVectors);
            permutation.pop_back();
            chosen[i] = false;
        }
    }
}

long int factorial(int n) {
    if (n == 1) {
        return 1;
    }
    else {
        return factorial(n - 1) * n;
    }
}

std::string printVector(std::vector<int> vec) {
    std::string result;
    for (double num : vec) {
        result += num + 48;
        result += " ";
    }
    return result;
}

void generateSubsets(std::vector<int>& nums, int K, std::vector<int>& subset, std::vector<std::vector<int>>& subsets, std::string cities[4][15]) {
    if (subset.size() == K) {
        subsets.push_back(subset);
        return;
    }

    for (int i = 0; i < nums.size(); ++i) {
        if (subset.empty() || nums[i] > subset.back()) {
            subset.push_back(nums[i]);
            generateSubsets(nums, K, subset, subsets, cities);
            subset.pop_back();
        }
    }
}


void printSubsets(std::vector<std::vector<int>>& subsets, std::string cities[4][15]) {
    std::cout << "Subsets: " << std::endl;
    int count = 1;
    for (auto& subset : subsets) {
        std::cout << count << ". ";
        for (auto& city : subset) {
            std::cout << cities[0][city] << " ";
        }
        std::cout << std::endl;
        count++;
    }
}

int main() {
    int N;
    std::cout << "Enter the number of cities to choose from (N): ";
    std::cin >> N;

    std::vector<int> nums;
    for (int i = 0; i < N; i++) {
        nums.push_back(i);
    }

    std::vector<bool> chosen(nums.size(), false);
    std::vector<int> permutation;
    std::vector<std::vector<int>> vectorOfVectors;

    std::string table[4][15] = {
        {"Paris", "Marseille", "Lyon", "Toulouse", "Nice", "Nantes", "Strasbourg", "Montpellier", "Bordeaux", "Lille", "Rennes", "Reims", "Le Havre", "Saint-Étienne", "Toulon"},
        {"2100", "860", "500", "480", "340", "310", "280", "280", "250", "230", "210", "180", "175", "170", "170"},
        {"48.8566", "43.2965", "45.7640", "43.6047", "43.7102", "47.2184", "48.5734", "43.6109", "44.8378", "50.6292", "48.1173", "49.2578", "49.4944", "45.4397", "43.1242"},
        {"2.3522", "5.3698", "4.8357", "1.4437", "7.2619", "1.5536", "7.7521", "3.8780", "0.5792", "3.0573", "1.6778", "4.0319", "0.1077", "4.3875", "5.9280"}
    };

    int sil = factorial(nums.size());
    double* results = new double[sil];

    generatePermutations(nums, chosen, permutation, table, results, sil, vectorOfVectors);

    double result = results[0];
    for (int i = 1; i < sil; i++) {
        if (results[i] < result) {
            result = results[i];
            traceNumber = i + 1;
        }
    }
    std::cout << std::endl << "Shortest path is " << traceNumber << ". " << printVector(vectorOfVectors[traceNumber]) << "and have length: " << result << std::endl;
    delete[] results;

    int K = N / 2;

    int totalPopulation = 0;
    for (int i = 0; i < nums.size(); ++i) {
        totalPopulation += std::stoi(table[1][i]);
    }

    int halfPopulation = totalPopulation / 2;

    std::vector<std::vector<int>> subsets;
    std::vector<int> subset;
    generateSubsets(nums, K, subset, subsets, table);
    printSubsets(subsets, table);

    int closestPopulationDiff = std::numeric_limits<int>::max();
    std::vector<int> closestSubset;
    for (auto& s : subsets) {
        int subsetPopulation = 0;
        for (auto& city : s) {
            subsetPopulation += std::stoi(table[1][city]);
        }
        int diff = std::abs(subsetPopulation - halfPopulation);
        if (diff < closestPopulationDiff) {
            closestPopulationDiff = diff;
            closestSubset = s;
        }
    }

    std::cout << "Subset with population closest to 50% of total population: ";
    for (auto& city : closestSubset) {
        std::cout << table[0][city] << " ";
    }
    std::cout << std::endl;

    return 0;
}