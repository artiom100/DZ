#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#define MAXWEIGHT 1000
std::vector<std::vector<int>> ReadData(const std::string& filename);
void GenerateAdjacencyMatrix(const std::string& filename, int size);