#include "ReadMatrix.h"
#include <random>



void GenerateAdjacencyMatrix(const std::string& filename, int size) {
    // Инициализация генератора случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, MAXWEIGHT);

    // Создание матрицы смежности
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            int weight = dis(gen); // Случайный вес ребра
            matrix[i][j] = weight;
            matrix[j][i] = weight; // Симметрия для неориентированного графа
        }
    }

    // Запись матрицы в текстовый файл
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& row : matrix) {
            for (size_t j = 0; j < row.size(); ++j) {
                file << row[j];
                if (j < row.size() - 1) {
                    file << ","; // Добавляем запятую между элементами строки
                }
            }
            file << "\n"; // Переход на следующую строку
        }
        file.close();
    }
    else {
        std::cerr << "Ошибка: не удалось открыть файл для записи." << std::endl;
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