#include "catch.hpp"
#include "main.cpp"

TEST_CASE("Test generateHistogram", "[Output]") {
    Output output;

    // Test histogram generation with normal distribution
    vector<double> normalData {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4};
    int numBins = 5;
    double minX = 1.0;
    double maxX = 2.5;
    output.generateHistogram(normalData, numBins, minX, maxX, "test_normal.txt");
    ifstream normalFile("test_normal.txt");
    REQUIRE(normalFile.is_open());
    vector<vector<double>> normalHist;
    double x, y;
    while (normalFile >> x >> y) {
        vector<double> row {x, y};
        normalHist.push_back(row);
    }
    normalFile.close();
    REQUIRE(normalHist.size() == numBins);
    for (int i = 0; i < numBins; i++) {
        REQUIRE(normalHist[i][0] == Approx(minX + (maxX-minX)/(2.0*numBins) + i*(maxX-minX)/numBins));
        REQUIRE(normalHist[i][1] == Approx((i+1)/8.0));
    }

    // Test histogram generation with uniform distribution
    vector<double> uniformData {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4};
    numBins = 4;
    minX = 0.0;
    maxX = 1.5;
    output.generateHistogram(uniformData, numBins, minX, maxX, "test_uniform.txt");
    ifstream uniformFile("test_uniform.txt");
    REQUIRE(uniformFile.is_open());
    vector<vector<double>> uniformHist;
    while (uniformFile >> x >> y) {
        vector<double> row {x, y};
        uniformHist.push_back(row);
    }
    uniformFile.close();
    REQUIRE(uniformHist.size() == numBins);
    for (int i = 0; i < numBins; i++) {
        REQUIRE(uniformHist[i][0] == Approx(minX + (maxX-minX)/(2.0*numBins) + i*(maxX-minX)/numBins));
        REQUIRE(uniformHist[i][1] == Approx(2.0/15.0));
    }
}