#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

class Reader {
public:
    vector<vector<double>> readDataFile(string filename) {
        ifstream infile(filename);
        vector<vector<double>> data;
        if (infile.is_open()) {
            double x, y, z, energy;
            while (infile >> x >> y >> z >> energy) {
                vector<double> row {x, y, z, energy};
                data.push_back(row);
            }
            infile.close();
        }
        return data;
    }
};

class Vector {
protected:
    double x, y, z;
public:
    Vector(double x, double y, double z): x(x), y(y), z(z) {}
    double magnitude() {
        return sqrt(x*x + y*y + z*z);
    }
    Vector unitVector() {
        double mag = magnitude();
        return Vector(x/mag, y/mag, z/mag);
    }
    double dot(Vector other) {
        return x*other.x + y*other.y + z*other.z;
    }
    Vector cross(Vector other) {
        return Vector(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
    }
};

class FourVector : public Vector {
private:
    double energy;
public:
    FourVector(double x, double y, double z, double energy): Vector(x, y, z), energy(energy) {}
    double mass() {
        return sqrt(energy*energy - magnitude()*magnitude());
    }
    double pt() {
        return sqrt(x*x + y*y);
    }
    double px() {
        return x;
    }
    double py() {
        return y;
    }
    double pz() {
        return z;
    }
};

class Output {
public:
    void generateHistogram(vector<double> data, int numBins, double minVal, double maxVal, string filename) {
        vector<double> histogram(numBins, 0);
        double binWidth = (maxVal - minVal) / numBins;
        for (int i = 0; i < data.size(); i++) {
            int bin = floor((data[i] - minVal) / binWidth);
            if (bin >= 0 && bin < numBins) {
                histogram[bin]++;
            }
        }
        double totalEntries = accumulate(histogram.begin(), histogram.end(), 0.0);
        for (int i = 0; i < histogram.size(); i++) {
            histogram[i] /= (totalEntries * binWidth);
        }
        ofstream outfile(filename);
        if (outfile.is_open()) {
            double xVal = minVal + binWidth/2.0;
            for (int i = 0; i < numBins; i++) {
                outfile << xVal << " " << histogram[i] << endl;
                xVal += binWidth;
            }
            outfile.close();
        }
    }
};


int main(int argc, char* argv[]) {
    // parse command line arguments
    if (argc != 6) {
        cout << "Usage: ./program datafile distribution numBins minX maxX" << endl;
        return 1;
    }
    string datafile = argv[1];
    string distribution = argv[2];
    int numBins = stoi(argv[3]);
    double minX = stod(argv[4]);
    double maxX = stod(argv[5]);

    // read data file
    Reader reader;
    vector<vector<double>> data = reader.readDataFile(datafile);

    // prepare requested distribution
    vector<double> distributionData;
    for (int i = 0; i < data.size(); i++) {
        FourVector fourVector(data[i][0], data[i][1], data[i][2], data[i][3]);
        if (distribution == "pT") {
            distributionData.push_back(fourVector.pt());
        }
        else if (distribution == "pX") {
            distributionData.push_back(fourVector.px());
        }
        else if (distribution == "pY") {
            distributionData.push_back(fourVector.py());
        }
        else if (distribution == "pZ") {
            distributionData.push_back(fourVector.pz());
        }
        else if (distribution == "energy") {
            distributionData.push_back(fourVector.magnitude());
        }
        else if (distribution == "mass") {
            distributionData.push_back(fourVector.mass());
        }
        else {
            cout << "Error: unsupported distribution requested" << endl;
            return 1;
        }
    }

    // generate histogram and output to file
    Output output;
    output.generateHistogram(distributionData, numBins, minX, maxX, distribution + ".txt");

    return 0;
}
