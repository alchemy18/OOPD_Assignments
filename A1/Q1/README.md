Files in the Project

questions1.cpp: The main source file containing the logic for calculating LTCG tax.
Makefile: The Makefile used to compile and generate binaries for the project.
price-inflation - price-inflation.csv: The CSV input file that contains data on growth rates and inflation rates for each year. This file is required for the program to work correctly.

Input File Format

Each row of price-inflation - price-inflation.csv represents the following columns:
Year (in YYYY-MM-DD format)
Growth-Price 
Inflation 

Requirements

g++ compiler
Make utility

Building the Project

To build and run both versions (Debug and Optimized):
make
./question1_debug
./question1_optimized

To build and run only the debugging version:
make question1_debug
./question1_debug

To build only the optimized version:
make question1_optimized
./question1_optimized

Note: I have used LLM powered chatbot for writing this code. 




