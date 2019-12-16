#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <ratio>
#include <../GoogleORtools/include/ortools/algorithms/knapsack_solver.h>
#include <stdio.h>
#define problemsize 320
//file reader func definition
//input : filename
//output : weights, capacity, profit
void FileReader(
    std::string filename,
    std::vector<int64> &capacities,
    std::vector<int64> &profits,
    std::vector<std::vector<int64>> &weights);

//file exporter
//input : string
//output : results.txt
void FileWriter(std::string text);

//filename generator to run all 320 problems
//input : path
//output : filenames
std::vector<std::string> FileNames(std::string path);

//0-1 knapsack function
//input : weights, capacity, profit
//output : maximum value
//knapsack example from google or tools
namespace operations_research
{
int64 RunKnapsackExample(
    std::vector<std::vector<int64>> &weights,
    std::vector<int64> &capacities,
    std::vector<int64> &profits);
};

//"Personal" implementation of the 0-1 knapsack problem
//Same io as Google OR tools implementation
int64 MyKnapsack(
    std::vector<std::vector<int64>> &weights,
    std::vector<int64> &capacities,
    std::vector<int64> &profits);

//Debug Function
void DebugDS(
    std::vector<std::vector<int64>> &weights,
    std::vector<int64> &capacities,
    std::vector<int64> &profits,
    std::vector<std::string> filenames);

namespace operations_research
{
int64 RunKnapsackExample(
    std::vector<std::vector<int64>> &weights,
    std::vector<int64> &capacities,
    std::vector<int64> &profits)
{
    // Instantiate the solver.
    KnapsackSolver solver(
        KnapsackSolver::KNAPSACK_DYNAMIC_PROGRAMMING_SOLVER,
        "KnapsackExample");

    solver.Init(profits, weights, capacities);

    int64 computed_value = solver.Solve();
    return computed_value;
}
} // namespace operations_research

// A utility function that returns maximum of two integers
int64 maximum(int64 a, int64 b) { return (a > b) ? a : b; }

int64 MyKnapsack(
    std::vector<std::vector<int64>> &weights,
    std::vector<int64> &capacities,
    std::vector<int64> &profits)
{
    int64 i, w;
    std::vector<std::vector<int64>> K;
    std::vector<int64> temp;
    K.reserve(profits.size() + 1);
    temp.reserve(capacities[0] + 1);
    for (i = 0; i <= capacities[0] + 1; i++)
    {
        temp.push_back(0);
    }
    // Build table K[][] in bottom up manner
    for (i = 0; i <= profits.size() + 1; i++)
    {
        K.push_back(temp);
    }

    for (i = 0; i <= profits.size(); i++)
    {
        for (w = 0; w <= capacities[0]; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (weights[0][i - 1] <= w)
                K[i][w] = maximum(profits[i - 1] + K[i - 1][w - weights[0][i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[profits.size()][capacities[0]];
}

void FileReader(
    std::string filename,
    std::vector<int64> &capacities,
    std::vector<int64> &profits,
    std::vector<std::vector<int64>> &weights)
{
    long lines = 0;
    long dump = 0;
    std::string line;
    std::fstream input;
    std::stringstream ss;
    input.open(filename, std::ios::in);

    if (input.is_open())
    {
        long tempprofit, tempweight, tempcapacity = 0;
        std::vector<int64> tempweightvec;
        int lcount = 1;

        getline(input, line);
        ss << line;
        ss >> lines;
        ss.clear();
        profits.reserve(lines);
        tempweightvec.reserve(lines); //memory reservation for temporary container
        do
        {
            getline(input, line);
            ss << line;
            ss >> dump >> tempprofit >> tempweight;
            ss.clear();
            profits.push_back(tempprofit);
            tempweightvec.push_back(tempweight);
            lcount++;
        } while (lcount <= lines);
        getline(input, line);
        ss << line;
        ss >> tempcapacity;
        ss.clear();
        capacities.push_back(tempcapacity);
        weights.push_back(tempweightvec);
        input.close();
    }
    else
    {
        std::cout << "error opening file " << filename << std::endl;
        exit(-1);
    }
}

void FileWriter(std::string text)
{
    std::fstream output;
    output.open("..\\src\\results.csv", std::ios::out | std::ios::app);
    if (output.is_open())
    {
        output << text;
    }
    output.close();
};

std::vector<std::string> FileNames(std::string path)
{
    std::vector<std::string> filenames;
    std::vector<int64> n = {10, 50, 100, 500};
    std::vector<int64> r = {50, 100, 500, 1000};
    std::vector<int64> type = {1, 2, 3, 4};
    std::string filename;
    filenames.reserve(problemsize);

    filename += path + "problem_";
    //read n
    for (auto n : n)
    {
        //read r
        for (auto r : r)
        {
            //read type
            for (auto type : type)
            {
                //5 instances per type
                for (int instance = 1; instance < 6; instance++)
                {
                    filename = path + "problem_" + std::to_string(n) + "_" +
                               std::to_string(r) + "_" + std::to_string(type) + "_" +
                               std::to_string(instance) + "_5.txt";
                    filenames.push_back(filename);
                }
            }
        }
    }
    return filenames;
}

void DebugDS(
    std::vector<std::vector<int64>> &weights,
    std::vector<int64> &capacities,
    std::vector<int64> &profits,
    std::vector<std::string> filenames)
{
    for (auto x : profits)
    {
        std::cout << x << " profit" << std::endl;
    }
    for (auto row : weights)
    {
        for (auto col : row)
            std::cout << col << " weight" << std::endl;
    }
    for (auto x : capacities)
    {
        std::cout << x << " capacity" << std::endl;
    }
    for (auto x : filenames)
    {
        std::cout << x << std::endl;
    }
}



// // Print solution
// std::vector<int> packed_items;
// for (std::size_t i = 0; i < profits.size(); ++i)
// {
//     if (solver.BestSolutionContains(i))
//         packed_items.push_back(i);
// }
// std::ostringstream packed_items_ss;
// std::copy(packed_items.begin(), packed_items.end() - 1,
//           std::ostream_iterator<int>(packed_items_ss, ", "));
// packed_items_ss << packed_items.back();

// std::vector<int64> packed_weights;
// packed_weights.reserve(packed_items.size());
// for (const auto &it : packed_items)
// {
//     packed_weights.push_back(weights[0][it]);
// }
// std::ostringstream packed_weights_ss;
// std::copy(packed_weights.begin(), packed_weights.end() - 1,
//           std::ostream_iterator<int>(packed_weights_ss, ", "));
// packed_weights_ss << packed_weights.back();

// int64 total_weights =
//     std::accumulate(packed_weights.begin(), packed_weights.end(), 0LL);

// LOG(INFO) << "Total value: " << computed_value;
// LOG(INFO) << "Packed items: {" << packed_items_ss.str() << "}";
// LOG(INFO) << "Total weight: " << total_weights;
// LOG(INFO) << "Packed weights: {" << packed_weights_ss.str() << "}";
// LOG(INFO) << "Solver time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms";