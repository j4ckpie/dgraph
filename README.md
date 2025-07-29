# dgraph

## About
`dgraph` is a program designed to partition graphs described in the CSR-RG format into `k` parts. It aims to ensure that the difference in subgraph sizes doesn't exceed a specified `x%` tolerance, all while minimizing the number of edges that cross partition boundaries. The tool achieves this through a sophisticated heuristic that combines simulated annealing, local refinement, and a multi-start approach.

## Project Structure
```
repository/
├── src/
│   └── filetype.c  # Implementation of different filetypes support
│   └── filetype.h  # Header file for filetypes
│   └── flags.h     # Defined help flags
│   └── graph.c     # Graph partition logic
│   └── graph.h     # Header file for graph partition
│   └── io.c        # Input and output
│   └── io.h        # Header file for input and output
│   └── main.c      # Main
│   └── userdata.c  # Handling user's data
│   └── userdata.h  # Header file for user's data
│   └── vector.c    # Implementation of vector
│   └── vector.h    # Header file for vector
├── Makefile        # Build instructions
└── README.md       # Project documentation
```

## Building the Project
This project includes a `Makefile` for building and running the program.

Build the program using `make`:
```bash
make
```
The compiled executable will be located in the bin directory as `dgraph`.

## Usage & Command-Line Arguments
To execute the program manually, run:
```bash
./dgraph <--input_arg> <input_file_locaiton> <--optional_args> 
```

`dgraph` supports the following command-line arguments:
- `--help`: Displays a brief instruction guide on how to use the program and its available arguments. *[Optional]*
- `--parts k`: Specifies the number of subgraphs `k` to partition the input graph into. The default value for `k` is `2`. *[Optional]*
- `--percent x`: Sets the maximum allowed percentage difference `x` between the sizes of the resulting subgraphs. The default value for `x` is `10%`. *[Optional]*
- `--filetype text|binary`: Allows you to choose the output file format for saving the found subgraphs (either `text` or `binary`). The default value is `text`. *[Optional]*
- `--input filename`: Specifies the path to the input graph file.

Here's an example:
```bash
./dgraph --percent 15 --input graph1.csrrg
```
This command will launch the program, partitioning graph1.csrrg into k = 2 parts (the default --parts value). The maximum allowed size difference between these parts will be x = 15%. The results will be saved to a file named graph1.txt, as the default --filetype is text. All arguments can be provided in any order.

## Authors
Developed by Jakub Pietrala & Bartosz Starzyński.
