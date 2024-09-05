#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip> // for std::setprecision
#include <utility> // for std::pair
#include <cmath>   // for std::round

using namespace std;

// Class to model yearly data for inflation rate and property gain rate
class YearData {
private:
    double inflationRate;
    double growthRate;  // Now using "Growth-Price" as growth rate

public:
    YearData(double inflationRate = 0.0, double growthRate = 0.0)
        : inflationRate(inflationRate), growthRate(growthRate) {}

    double getInflationRate() const {
        return inflationRate;
    }

    double getGrowthRate() const {
        return growthRate;
    }
};

// Class to model the Long-Term Capital Gains (LTCG) tax calculation
class LTCGCalculator {
private:
    unordered_map<int, YearData> yearData; // Stores inflation and growth rates by year
    double initialCostPrice; // Initial cost price of the property
    double taxRate; // LTCG tax rate

    // Function to round a double to a specific number of decimal places
    double roundToPrecision(double value, int precision) const {
        double scale = std::pow(10.0, precision);
        return std::round(value * scale) / scale;
    }

public:
    LTCGCalculator(double initialCostPrice, double taxRate = 0.20)
        : initialCostPrice(initialCostPrice), taxRate(taxRate) {}

    // Function to read CSV data and populate yearData map
    void readCSV(const string& filename) {
        ifstream file(filename);
        string line, header;

        if (file.is_open()) {
            // Read the header line
            getline(file, header);

            // Read data line by line
            while (getline(file, line)) {
                stringstream ss(line);
                string yearStr, growthRateStr, inflationRateStr;

                // Read year, growth rate, and inflation rate from the line
                getline(ss, yearStr, ',');  // Format "YYYY-MM-DD"
                getline(ss, growthRateStr, ',');  // "Growth-Price"
                getline(ss, inflationRateStr, ',');  // "Inflation"

                // Extract year from "YYYY-MM-DD" format
                int year = stoi(yearStr.substr(0, 4));  // Extract the year as an integer
                double growthRate = stod(growthRateStr);  // Growth rate (Growth-Price)
                double inflationRate = stod(inflationRateStr);  // Inflation rate

                // Store data in the map
                yearData[year] = YearData(inflationRate, growthRate);
            }
            file.close();
        } else {
            cerr << "Error opening file: " << filename << endl;
        }
    }

    // Function to calculate the estimated selling price and LTCG tax
    pair<double, double> calculateLTCG(int buyingYear, int sellingYear) const {
        if (sellingYear <= buyingYear) {
            cerr << "Selling year must be greater than buying year." << endl;
            return make_pair(0.0, 0.0);
        }

        double currentPrice = initialCostPrice;

        // Calculate the selling price by compounding growth rate adjusted by inflation rate for each year
        for (int year = buyingYear; year <= sellingYear; ++year) {
            if (yearData.find(year) != yearData.end()) {
                double inflationRate = yearData.at(year).getInflationRate();
                double growthRate = yearData.at(year).getGrowthRate();
                currentPrice *= (1 + (growthRate - inflationRate) / 100);
                currentPrice = roundToPrecision(currentPrice, 4); // Ensure precision
                cout << year << endl;
                cout << growthRate << endl;
                cout << inflationRate << endl;
                cout << growthRate - inflationRate << endl;
                cout << currentPrice << endl;
            }
        }

        double sellingPrice = roundToPrecision(currentPrice, 4);
        double actualProfit = roundToPrecision(sellingPrice - initialCostPrice, 4);

        // Ensure LTCG Tax is not negative
        double ltcgTax = actualProfit > 0 ? roundToPrecision(taxRate * actualProfit, 4) : 0;

        return make_pair(sellingPrice, ltcgTax);
    }
};

int main() {
    string filename = "price-inflation - price-inflation.csv"; 
    double initialCostPrice = 5000000; // Initial cost price (Rs 50 lakhs)
    int buyingYear = 2010;
    int sellingYear;

    // Initializing LTCGCalculator Class
    LTCGCalculator ltcgCalculator(initialCostPrice);

    ltcgCalculator.readCSV(filename);

    cout << "Enter the year of selling (between 2011 to 2030): ";
    cin >> sellingYear;

    // Validate year of selling
    if (sellingYear <= buyingYear || sellingYear > 2030) {
        cerr << "Invalid year!! Please enter a year between the following range 2011 and 2030." << endl;
        return 1;
    }

    // Calculate selling price and LTCG tax
    pair<double, double> result = ltcgCalculator.calculateLTCG(buyingYear, sellingYear);
    double sellingPrice = result.first;
    double ltcgTax = result.second;

    // Output results
    cout << fixed << setprecision(4); // Set decimal precision to 4
    cout << "Estimated Selling Price: Rs " << sellingPrice << endl;
    cout << "Long-Term Capital Gains Tax (LTCG) to be paid: Rs " << ltcgTax << endl;

    return 0;
}
