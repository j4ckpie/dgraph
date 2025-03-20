#ifndef FLAGS_H
#define FLAGS_H

// Define long flags
struct option long_options[] = {
    {"help", no_argument, 0, 'h'},
    {"parts", required_argument, 0, 'k'},
    {"percent", required_argument, 0, 'x'},
    {"filetype", required_argument, 0, 'f'},
    {"input", required_argument, 0, 'i'},
    {0, 0, 0, 0} // Last element must be a zero
};

#endif
