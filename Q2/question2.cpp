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
    double oldTaxRate; // Old LTCG tax rate
    double newTaxRate; // New LTCG tax rate

    // Function to round a double to a specific number of decimal places
    double roundToPrecision(double value, int precision) const {
        double scale = std::pow(10.0, precision);
        return std::round(value * scale) / scale;
    }

public:
    LTCGCalculator(double initialCostPrice, double oldTaxRate = 0.20, double newTaxRate = 0.125)
        : initialCostPrice(initialCostPrice), oldTaxRate(oldTaxRate), newTaxRate(newTaxRate) {}

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
    pair<double, double> calculateOldLTCG(int buyingYear, int sellingYear) const {
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
            }
        }

        double sellingPrice = roundToPrecision(currentPrice, 4);
        double actualProfit = roundToPrecision(sellingPrice - initialCostPrice, 4);

        // Ensure LTCG Tax is not negative
        double ltcgTax = actualProfit > 0 ? roundToPrecision(oldTaxRate * actualProfit, 4) : 0;

        return make_pair(sellingPrice, ltcgTax);
    }

    // Function to calculate the estimated selling price and LTCG tax under the new scheme
    pair<double, double> calculateNewLTCG(int buyingYear, int sellingYear) const {
        if (sellingYear <= buyingYear) {
            cerr << "Selling year must be greater than buying year." << endl;
            return make_pair(0.0, 0.0);
        }

        double currentPrice = initialCostPrice;

        // Calculate the selling price by compounding growth rate without inflation adjustment for each year
        for (int year = buyingYear; year <= sellingYear; ++year) {
            if (yearData.find(year) != yearData.end()) {
                double growthRate = yearData.at(year).getGrowthRate();
                currentPrice *= (1 + growthRate / 100);
                currentPrice = roundToPrecision(currentPrice, 4); // Ensure precision
            }
        }

        double sellingPrice = roundToPrecision(currentPrice, 4);
        double actualProfit = roundToPrecision(sellingPrice - initialCostPrice, 4);

        // Ensure LTCG Tax is not negative
        double ltcgTax = actualProfit > 0 ? roundToPrecision(newTaxRate * actualProfit, 4) : 0;

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

    // Calculate selling price and LTCG tax under old scheme
    pair<double, double> oldResult = ltcgCalculator.calculateOldLTCG(buyingYear, sellingYear);
    double oldSellingPrice = oldResult.first;
    double oldLtcgTax = oldResult.second;

    // Calculate selling price and LTCG tax under new scheme
    pair<double, double> newResult = ltcgCalculator.calculateNewLTCG(buyingYear, sellingYear);
    double newSellingPrice = newResult.first;
    double newLtcgTax = newResult.second;

    // Output results
    cout << fixed << setprecision(4); // Set decimal precision to 4
    cout << "Estimated Selling Price: Rs " << oldSellingPrice << " (Old Scheme)" << endl;
    cout << "Long-Term Capital Gains Tax (LTCG) to be paid (Old Scheme): Rs " << oldLtcgTax << endl;
    cout << "Estimated Selling Price: Rs " << newSellingPrice << " (New Scheme)" << endl;
    cout << "Long-Term Capital Gains Tax (LTCG) to be paid (New Scheme): Rs " << newLtcgTax << endl;
    cout << "Difference in LTCG Tax: Rs " << (oldLtcgTax - newLtcgTax) << endl;

    return 0;
}
