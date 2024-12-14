
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <climits>

struct Toy {
    std::string name;
    int cost;
    int min_age;
    int max_age;
};

class FileManipulator {
public:
    
    static void generateRandomIntegersFile(const std::string& filename, int count) {
        std::ofstream file(filename, std::ios::binary);
        for (int i = 0; i < count; i++) {
            int num = rand() % 100; // Generate random number between 0 and 99
            file.write(reinterpret_cast<const char *>(&num), sizeof(num));
        }
        file.close();
    }

    static void generateToyFile(const std::string& filename, const std::vector<Toy>& toys) {
        std::ofstream file(filename, std::ios::binary);
        for (const Toy& toy : toys) {
            file.write(toy.name.c_str(), toy.name.size() + 1); // Include null terminator
            file.write(reinterpret_cast<const char *>(&toy.cost), sizeof(toy.cost));
            file.write(reinterpret_cast<const char *>(&toy.min_age), sizeof(toy.min_age));
            file.write(reinterpret_cast<const char *>(&toy.max_age), sizeof(toy.max_age));
        }
        file.close();
    }

    static void createNewFileRule1(const std::string& inputFile, const std::string& outputFile) {
        std::ifstream input(inputFile, std::ios::binary);
        std::ofstream output(outputFile, std::ios::binary);

        int num;
        while (input.read(reinterpret_cast<char *>(&num), sizeof(num))) {
            output.write(reinterpret_cast<const char *>(&num), sizeof(num));
            output.write(reinterpret_cast<const char *>(&num), sizeof(num));

            int nextNum;
            while (input.peek() != EOF) {
                input.read(reinterpret_cast<char *>(&nextNum), sizeof(nextNum));
                output.write(reinterpret_cast<const char *>(&nextNum), sizeof(nextNum));
            }
        }

        input.close();
        output.close();
    }

    static void copyFileToMatrix(const std::string& inputFile, int n) {
        std::ifstream input(inputFile, std::ios::binary);
        std::vector<std::vector<int>> matrix(n, std::vector<int>(n, 0));

        int num;
        int row = 0, col = 0;
        while (input.read(reinterpret_cast<char *>(&num), sizeof(num))) {
            matrix[row][col] = num;
            col++;
            if (col == n) {
                col = 0;
                row++;
                if (row == n) break;
            }
        }

        input.close();

        int closestRow = 0;
        int closestSum = std::abs(matrix[0][0]);
        for (int i = 1; i < n; i++) {
            int rowSum = 0;
            for (int j = 0; j < n; j++) {
                rowSum += matrix[i][j];
            }
            if (std::abs(rowSum) < closestSum) {
                closestRow = i;
                closestSum = std::abs(rowSum);
            }
        }

        std::cout << "Row with sum closest to zero: " << closestRow << std::endl;
    }

    static void findToysForAges(const std::string& inputFile, int minAge, int maxAge) {
        std::ifstream input(inputFile, std::ios::binary);

        std::vector<std::string> suitableToys;

        Toy toy;
        while (input.read(reinterpret_cast<char *>(&toy), sizeof(Toy))) {
            if (toy.min_age <= minAge && toy.max_age >= maxAge) {
                suitableToys.push_back(toy.name);
            }
        }

        input.close();

        std::cout << "Toys suitable for children aged " << minAge << " to " << maxAge << ":" << std::endl;
        for (const std::string& name : suitableToys) {
            std::cout << name << std::endl;
        }
    }

    static void findMinMaxProduct(const std::string& inputFile) {
        std::ifstream input(inputFile);
        int min = INT_MAX;
        int max = INT_MIN;

        int num;
        while (input >> num) {
            min = std::min(min, num);
            max = std::max(max, num);
        }

        input.close();

        std::cout << "Product of min and max elements: " << min * max << std::endl;
    }

    static void countOddElements(const std::string& inputFile) {
        std::ifstream input(inputFile);

        int num;
        int count = 0;
        while (input >> num) {
            if (num % 2 != 0) {
                count++;
            }
        }

        input.close();

        std::cout << "Number of odd elements: " << count << std::endl;
    }
};

int main() {
    FileManipulator::generateRandomIntegersFile("random_numbers.bin", 10);

    std::vector<Toy> toys = {
            { "Teddy Bear", 15, 1, 5 },
            { "Lego Set", 25, 3, 12 },
            { "Dollhouse", 40, 4, 10 }
    };
    FileManipulator::generateToyFile("toys.bin", toys);

    FileManipulator::createNewFileRule1("random_numbers.bin", "output1.bin");

    FileManipulator::copyFileToMatrix("random_numbers.bin", 3);

    FileManipulator::findToysForAges("toys.bin", 4, 10);

    FileManipulator::findMinMaxProduct("random_numbers.bin");

    FileManipulator::countOddElements("random_numbers.bin");

    return 0;
}
