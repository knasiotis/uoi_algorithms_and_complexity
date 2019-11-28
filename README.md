# INSTRUCTIONS #
### Consider the following directory tree:
![Directory listing](img/directoryimg.png?raw=true)

#### Prerequisites
* [Build tools](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019) for Visual Studio
* [Google OR Tools](https://developers.google.com/optimization/install/cpp/windows9) Library
(More information [here](https://developers.google.com/optimization/install))

#### Build&Run Guide for Windows
1. Open the *x64 Native Tools Command Prompt for VS* xxxx
2. ```chdir "Google OR Tools"``` 
3. Run the following command ```tools\make run SOURCE=..\src\knapsack.cc```
4. Runtime results are saved in src/results.csv
