# INSTRUCTIONS #
### Consider the following directory listing:
![Directory listing](img/directoryimg.png?raw=true)

#### Prerequisites
* [Build Tools](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019) for Visual Studio (Note: A Complete Visual Studio installation with C++ support might be required)
* [Google OR-Tools](https://developers.google.com/optimization/install/cpp/windows) Library
(More information available [here](https://developers.google.com/optimization/install))

#### Build&Run Guide for Windows
1. Extract OR Tools .zip in the cloned directory
2. Follow Google OR-Tools Installation Procedure
3. Open the *x64 Native Tools Command Prompt for VS* xxxx
4. ```chdir "Google OR Tools"``` 
5. Run the following command ```tools\make run SOURCE=..\src\main.cc```
6. For unit tests run ```tools\make run SOURCE=..\src\tests.cc```
7. Runtime results are saved in src/results.csv
