#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ortools/algorithms/knapsack_solver.h>
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
//output : result.txt
void FileWriter(std::string text);

//filename generator to run all 320 problems
//input : path
//output : filenames
std::vector<std::string> FileNames(std::string path);

//0-1 knapsack function
//input : weights, capacity, profit
//output : value, items, weight
//knapsack example from google or tools
namespace operations_research
{
void RunKnapsackExample(
    std::vector<std::vector<int64>> &weights,
    std::vector<int64> &capacities,
    std::vector<int64> &profits);
};

//Debug Function
void DebugDS(
    std::vector<std::vector<int64>> &weights,
    std::vector<int64> &capacities,
    std::vector<int64> &profits,
    std::vector<std::string> filenames);

int main()
{
    std::vector<int64> profits, capacities;
    std::vector<std::vector<int64>> weights;
    std::vector<std::string> filenames;
    filenames = FileNames("D:\\projects\\algocomplexity\\uoi_algorithms_and_complexity\\knapsack_prj\\");
    // DebugDS(weights, capacities, profits, filenames); //debugging

    for (auto filename : filenames)
    {
        FileReader(filename, capacities, profits, weights);
        operations_research::RunKnapsackExample(weights, capacities, profits);
        weights.clear();
        profits.clear();
        capacities.clear();
    }

    return 0;
}

namespace operations_research
{
void RunKnapsackExample(
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

    // Print solution
    std::vector<int> packed_items;
    for (std::size_t i = 0; i < profits.size(); ++i)
    {
        if (solver.BestSolutionContains(i))
            packed_items.push_back(i);
    }
    std::ostringstream packed_items_ss;
    std::copy(packed_items.begin(), packed_items.end() - 1,
              std::ostream_iterator<int>(packed_items_ss, ", "));
    packed_items_ss << packed_items.back();

    std::vector<int64> packed_weights;
    packed_weights.reserve(packed_items.size());
    for (const auto &it : packed_items)
    {
        packed_weights.push_back(weights[0][it]);
    }
    std::ostringstream packed_weights_ss;
    std::copy(packed_weights.begin(), packed_weights.end() - 1,
              std::ostream_iterator<int>(packed_weights_ss, ", "));
    packed_weights_ss << packed_weights.back();

    int64 total_weights =
        std::accumulate(packed_weights.begin(), packed_weights.end(), 0LL);

    LOG(INFO) << "Total value: " << computed_value;
    LOG(INFO) << "Packed items: {" << packed_items_ss.str() << "}";
    LOG(INFO) << "Total weight: " << total_weights;
    LOG(INFO) << "Packed weights: {" << packed_weights_ss.str() << "}";
}
} // namespace operations_research

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
            std::string word;
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
}

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