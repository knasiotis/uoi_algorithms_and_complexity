# INSTRUCTIONS #
### Consider the following directory tree:
![Directory listing](img/directoryimg.png?raw=true)

#### Prerequisites
* [Build tools](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019) for Visual Studio
* [Google OR Tools](https://developers.google.com/optimization/install/cpp/windows) Library
(More information available [here](https://developers.google.com/optimization/install))

#### Build&Run Guide for Windows
1. Extract OR Tools .zip in the cloned directory
2. Follow Google OR Tools Installation Procedure
3. Open the *x64 Native Tools Command Prompt for VS* xxxx
4. ```chdir "Google OR Tools"``` 
5. Run the following command ```tools\make run SOURCE=..\src\knapsack.cc```
6. Runtime results are saved in src/results.csv
