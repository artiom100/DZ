#include <chrono>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include "ReadMatrix.h"

int goldberg(std::vector<std::vector<int>> graph, int source, int sink);
int GuryevEdmondsKarp(std::vector<std::vector<int>> graph, int source, int sink);


template<typename Method>
void Run(const std::string& method_name, Method method, const std::vector<std::vector<int>>& data, int sourse, int sink) {
    std::cout << "Запуск алгоритма: " << method_name << std::endl;

    auto start = std::chrono::system_clock::now();
    int result = method(data, sourse, sink);
    auto stop = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    std::cout << "Время: " << time << " mcs" << std::endl;
    std::cout << "Максимальный поток  " << result << std::endl << std::endl;
}
#define RUN(x, y, z, data) {\
    Run(#x, x, y, z, data);\
}


int main(){
    setlocale(LC_ALL, "RU");
    GenerateAdjacencyMatrix("data1.txt", 20);
	std::vector<std::vector<int>> matrix = ReadData("data1.txt");
    std::cout << "-------Тестирование на графе-дереве (20 вершины)-------";
    std::cout << "" << std::endl;
    int source = 0;
    int sink = 19;
    int res;
    /*RUN(SerkovaFordFulkerson, matrix, source, sink);*/
    RUN(GuryevEdmondsKarp, matrix, source, sink);
    RUN(goldberg, matrix, source, sink);
    //res = Goldberg(matrix, source, sink);
    //std::cout << res << std::endl;
    std::cout << "" << std::endl;
    


    std::cout << "-------Тестирование на графе-дереве (98 вершины)-------";
    std::cout << "" << std::endl;
    GenerateAdjacencyMatrix("data1.txt", 98);
    matrix = ReadData("data1.txt");
    source = 0;
    sink = 97;
    RUN(GuryevEdmondsKarp, matrix, source, sink);
    RUN(goldberg, matrix, source, sink);
    //std::cout << res << std::endl;
    std::cout << "" << std::endl;
    /*
    std::cout << "-------Тестирование на графе-дереве (150 вершины)-------";
    std::cout << "" << std::endl;
    GenerateAdjacencyMatrix("data1.txt", 150);
    matrix = ReadData("data1.txt");
    source = 0;
    sink = 149;
    res = Goldberg(matrix, source, sink);
    std::cout << res << std::endl;
    std::cout << "" << std::endl;




    std::cout << "-------Тестирование на графе-дереве (250 вершины)-------";
    std::cout << "" << std::endl;
    GenerateAdjacencyMatrix("data1.txt", 250);
    matrix = ReadData("data1.txt");
    source = 0;
    sink = 249;
    res = Goldberg(matrix, source, sink);
    std::cout << res << std::endl;
    std::cout << "" << std::endl;

    */
    return 0;

}



