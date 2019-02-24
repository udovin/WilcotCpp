# Wilcot Cpp

Wilcot Cpp — a C++ library that helps in developing Linux applications.

## What's supported?

 * Process creation;
 * Linux container creation;
 * Convenient testing utils;
 * Convenient working with filesystem;
 * Convenient working with console;
 * Streams and ring buffer.

## Examples

### Options parsing

```cpp
// Create new option parser
wilcot::cli::OptionParser parser;
// Create arguments for options
wilcot::cli::ValueOption<std::string> inputFile("--input", "path");
wilcot::cli::ValueOption<std::string> outputFile("--output", "path");
// Add options to option parser
parser.addOption(inputFile);
parser.addOption(outputFile);
// Parse arguments passed to main
parser.parse(argc, argv);
```

### Process creation

```cpp
// Create new process instance
wilcot::os::Process process;
// Create an array for arguments
std::vector<std::string> arguments;
arguments.push_back("/bin/bash");
// Set path to program and execute arguments
process.setProgram("/bin/bash");
process.setArguments(arguments);
// Start process
process.start();
// Wait for process exit
process.wait();
```
