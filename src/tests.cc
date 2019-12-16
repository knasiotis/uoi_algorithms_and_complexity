#define CATCH_CONFIG_MAIN
#include <../src/catch.hpp>
#include <../src/knapsack.cc>


// UNIT TESTS

TEST_CASE("FileNames", "names")
{
    REQUIRE(FileNames("..\\knapsack_prj\\").size() == 320);
}

TEST_CASE("FileReader", "reader")
{
    std::vector<int64> profits, capacities;
    std::vector<std::vector<int64>> weights;
    FileReader("..\\knapsack_prj\\problem_10_50_1_1_5.txt", capacities, profits, weights);
    REQUIRE(capacities[0]==51);
    REQUIRE(profits.size() == 10);
    REQUIRE(weights[0].size()==10);

    capacities.clear();
    profits.clear();
    weights.clear();
    FileReader("..\\knapsack_prj\\problem_50_50_1_1_5.txt", capacities, profits, weights);
    REQUIRE(capacities[0]==181);
    REQUIRE(profits.size() == 50);
    REQUIRE(weights[0].size()==50);



    capacities.clear();
    profits.clear();
    weights.clear();
    FileReader("..\\knapsack_prj\\problem_500_1000_4_5_5.txt", capacities, profits, weights);
    REQUIRE(capacities[0] == 217655);
    REQUIRE(profits.size() == 500);
    REQUIRE(weights[0].size() == 500);
}

TEST_CASE("Google OR Knapsack", "knapsack")
{
    std::vector<int64> profits, capacities;
    std::vector<std::vector<int64>> weights;
    FileReader("..\\knapsack_prj\\problem_10_50_1_1_5.txt", capacities, profits, weights);
    REQUIRE(operations_research::RunKnapsackExample(weights, capacities, profits) == 123);


    capacities.clear();
    profits.clear();
    weights.clear();
    FileReader("..\\knapsack_prj\\problem_10_50_1_2_5.txt", capacities, profits, weights);
    REQUIRE(operations_research::RunKnapsackExample(weights, capacities, profits) == 127);


    capacities.clear();
    profits.clear();
    weights.clear();
    FileReader("..\\knapsack_prj\\problem_10_50_1_3_5.txt", capacities, profits, weights);
    REQUIRE(operations_research::RunKnapsackExample(weights, capacities, profits) == 167);


    capacities.clear();
    profits.clear();
    weights.clear();
    FileReader("..\\knapsack_prj\\problem_500_1000_4_5_5.txt", capacities, profits, weights);
    REQUIRE(operations_research::RunKnapsackExample(weights, capacities, profits) == 217655);
}


TEST_CASE("Personal Knapsack", "knapsack")
{
    std::vector<int64> profits, capacities;
    std::vector<std::vector<int64>> weights;
    FileReader("..\\knapsack_prj\\problem_10_50_1_1_5.txt", capacities, profits, weights);
    REQUIRE(MyKnapsack(weights, capacities, profits) == 123);

    capacities.clear();
    profits.clear();
    weights.clear();
    FileReader("..\\knapsack_prj\\problem_10_50_1_2_5.txt", capacities, profits, weights);
    REQUIRE(MyKnapsack(weights, capacities, profits) == 127);

    capacities.clear();
    profits.clear();
    weights.clear();
    FileReader("..\\knapsack_prj\\problem_10_50_1_3_5.txt", capacities, profits, weights);
    REQUIRE(MyKnapsack(weights, capacities, profits) == 167);


    capacities.clear();
    profits.clear();
    weights.clear();
    FileReader("..\\knapsack_prj\\problem_500_1000_4_5_5.txt", capacities, profits, weights);
    REQUIRE(MyKnapsack(weights, capacities, profits) == 217655);
}