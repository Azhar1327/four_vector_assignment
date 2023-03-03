# four_vector_assignment
 
This C++ code reads a data file containing four-vector information (momentum vector's x, y, and z directions, and energy), and computes a 1D histogram for a specified distribution. The code includes a reader class to read the data file and prepare the appropriate data class, a data class with a vector class for basic vector computation, and a FourVector class with additional capabilities, such as computing the mass of a particle represented by a vector. The output system generates a two-column text file that can be used to draw a histogram later on.

Installation
To use this code, you will need to have a C++ compiler installed on your system. The code also depends on the Catch2 unit testing library, which is included as a submodule in the repository. To install Catch2, you can run the following commands:

git submodule init
git submodule update
This will download the Catch2 library into the tests/lib directory.

Usage
The main program can be run from the command line with the following arguments:

computeHistogram <datafile> <distribution> <num_bins> <min_value> <max_value>

where:

<datafile> is the path to the input data file.
 
<distribution> is the name of the distribution to compute. Currently supported distributions include: pT, pX, pY, pZ, energy, and mass.
 
<num_bins> is the number of bins to use in the histogram.
 
<min_value> is the minimum value of the x-axis for the histogram.
 
<max_value> is the maximum value of the x-axis for the histogram.

For example:

computeHistogram data.txt mass 100 0 1000
 
This will compute a histogram of the masses of particles in the input data file, with 100 bins ranging from 0 to 1000 MeV.

Testing

The code includes a suite of unit tests that can be run with the following command:

make test

This will compile the code and run the tests using the Catch2 library. If all tests pass, you should see a message indicating that all tests have passed. If any tests fail, you will see an error message indicating which tests failed and why.

