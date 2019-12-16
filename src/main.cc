#include <../src/knapsack.cc>

int main()
{
    int problemNo = 1;
    std::vector<std::string> filenames;

    //Removes previously generated file
    remove("..\\src\\results.csv");

    //Filename generator
    filenames = FileNames("..\\knapsack_prj\\");

    FileWriter("Problem Number,ValuePersonal,ValueORTools,TimePersonal(ms),TimeORTools(ms) \n");
    for (auto filename : filenames)
    {
        int64 ORValue, PValue = 0;
        std::vector<int64> profits, capacities;
        std::vector<std::vector<int64>> weights;

        //Prepares the input
        FileReader(filename, capacities, profits, weights);

        FileWriter(std::to_string(problemNo) + ",");

        //Personal implementation
        auto tbegin = std::chrono::high_resolution_clock::now();
        PValue = MyKnapsack(weights, capacities, profits);
        auto tend = std::chrono::high_resolution_clock::now();

        //Google OR tools
        auto begin = std::chrono::high_resolution_clock::now();
        ORValue = operations_research::RunKnapsackExample(weights, capacities, profits);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> t1 = end - begin;
        std::chrono::duration<double, std::milli> t2 = tend - tbegin;

        FileWriter(std::to_string(PValue) + "," + std::to_string(ORValue) + "," +
                   std::to_string(t2.count()) + "," +
                   std::to_string(t1.count()));

        //On to the next problem
        FileWriter("\n");
        problemNo++;
    }
    return 0;
}