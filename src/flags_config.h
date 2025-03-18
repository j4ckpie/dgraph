// Define long flags
struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"parts", optional_argument, 0, 'k'},
    {"percent", optional_argument, 0, 'x'},
    {"filetype", optional_argument, 0, 'f'},
    {"input", required_argument, 0, 'i'},
    {0, 0, 0, 0} // Last element must be a zero
};
