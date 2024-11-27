#include "ReadMatrix.h"
#include <random>



void GenerateAdjacencyMatrix(const std::string& filename, int size) {
    // ������������� ���������� ��������� �����
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, MAXWEIGHT);

    // �������� ������� ���������
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            int weight = dis(gen); // ��������� ��� �����
            matrix[i][j] = weight;
            matrix[j][i] = weight; // ��������� ��� ������������������ �����
        }
    }

    // ������ ������� � ��������� ����
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& row : matrix) {
            for (size_t j = 0; j < row.size(); ++j) {
                file << row[j];
                if (j < row.size() - 1) {
                    file << ","; // ��������� ������� ����� ���������� ������
                }
            }
            file << "\n"; // ������� �� ��������� ������
        }
        file.close();
    }
    else {
        std::cerr << "������: �� ������� ������� ���� ��� ������." << std::endl;
    }
}


std::vector<std::vector<int>> ReadData(const std::string& filename) {
    std::vector<std::vector<int>> matrix;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> row;
            std::stringstream ss(line);
            std::string value;

            while (std::getline(ss, value, ',')) {
                row.push_back(std::stoi(value));
            }

            if (!row.empty()) {
                matrix.push_back(row);
            }
        }
    }
    file.close();
    return matrix;
}