# s-expression-calculator

It supports add and multiply function 

The core idea in developing this project involved using re-organize function and stack in order to process token priority and a use of queue implemented using linkedlist to perform calculation(add or multiply).

> **Compilation**
```
g++ -Wall -g -std=c++11 -o calc implementer.cpp
```

> **Execution** 
```
./calc "input query"
```
> **Note:** To attach gdb debugger to the source file during compilation
```
g++ -Wall -ggdb -std=c++11 -o calc implementer.cpp
```

> **Note:** To run gdb debugger for the input query
```
gdb --args calc "input query"
```

<img src="https://github.com/tamizh3110/s-expression-calculator/blob/master/output_screenshot.png"></img>
