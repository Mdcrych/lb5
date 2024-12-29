#include <clocale>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>


class WorkFile {
public:
    static void RandBinFile(const std::string& filename, int count,int minimal_number, int maximum_number) {

    if (minimal_number > maximum_number) {
      minimal_number = 1;
      maximum_number = 9;
    }
    if (count <= 0)
      count = 10;

    std::ofstream file(filename, std::ios::binary);

    static bool flag = false;
    if (!flag) {
      std::srand(static_cast<unsigned int>(std::time(0)));
      flag = true;
    }

    for (int i = 0; i < count; i++) {
      int random = (minimal_number) + (rand() % (maximum_number - minimal_number + 1));
      std::cout << random << ' ';
      file.write(reinterpret_cast<char *>(&random), sizeof(int));
    }
    std::cout << '\n';
    file.close();
  }

    static void CopyFile(const std::string &input_file,const std::string &output_file) {
        std::ifstream input(input_file, std::ios::binary);
        std::ofstream output(output_file, std::ios::binary);
    std::vector<int> nums;
    int num;
    while (input.read(reinterpret_cast<char *>(&num), sizeof(int))) {
        nums.push_back(num);
    }

    for (int i = 1; i <= nums.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            output.write(reinterpret_cast<char *>(&nums[j]), sizeof(int));
        }
    }

input.close();
output.close();

}

  static void ViewFile(const std::string &input_file) {
    std::ifstream input(input_file, std::ios::binary);

    int num;
    while (input.read(reinterpret_cast<char *>(&num), sizeof(int)))
      std::cout << num << ' ';
    input.close();
    std::cout << '\n' << '\n';
  }

  static std::vector<std::vector<int>> 
  ReadMatrix(const std::string &input_file, int k) {
    std::ifstream input(input_file, std::ios::binary);
    std::vector<std::vector<int>> arr(k, std::vector<int>(k, 0));
    int num;
    int count = 0;
    while (input.read(reinterpret_cast<char *>(&num), sizeof(int)) &&
           count < k * k) {
      arr[count / k][count % k] = num;
      count++;
    }
    input.close();
    return arr;
  }

  static int MinRows(std::vector<std::vector<int>> &arr) {
    int k = arr.size();
    if (!k)
      return 0;
    int ind, min_sum;

    for (int i = 0; i < k; i++) {
      int sum = 0;

      for (int j = 0; j < k; j++) {
        sum += arr[i][j];
      }

      if (!i) {
        min_sum = sum;
        ind = 0;
      }
      if (std::abs(sum) < std::abs(min_sum)) {
        min_sum = sum;
        ind = i;
      }
    }
    return ind;
  }

  static void ViewMatrix(std::vector<std::vector<int>> &arr) {
    for (const auto &row : arr) {
      for (int num : row)
        std::cout << num << ' ';
      std::cout << '\n';
    }
    std::cout << '\n';
  }

  static void RandomTXTFile(const std::string &output_file, int count,
                                int minimal_number, int maximum_number) {
    std::ofstream output(output_file);

    static bool flag = false;
    if (!flag) {
      std::srand(static_cast<unsigned int>(std::time(0)));
      flag = true;
    }

    for (int i = 0; i < count; i++) {
      output << minimal_number +
                    (rand() % (maximum_number - minimal_number + 1))
             << '\n';
    }
    output.close();
  }

  static long long ProductMinMaxTXT(const std::string &input_file) {
    std::ifstream input(input_file);
    int min = INT_MAX;
    int max = INT_MIN;
    int num; 
    while (input >> num) {
    if (num < min) {
        min = num;
    }
    if (num > max) {
        max = num;
    }
}

    input.close();
    return static_cast<long long>(min) * static_cast<long long>(max);
}

  static void RandomTXTLinesFile(const std::string &output_file, int count,
                                     int minimal_number, int maximum_number,
                                     int columns_count) {
    std::ofstream output(output_file);

    static bool flag = false;
    if (!flag) {
      std::srand(static_cast<unsigned int>(std::time(0)));
      flag = true;
    }

    for (int i = 0; i < count; i++)
      for (int j = 0; j < columns_count; j++) {
        output << minimal_number +
                      (rand() % (maximum_number - minimal_number + 1));
        if (j != columns_count - 1)
          output << ' ';
      }
    output << '\n';
    output.close();
  }

  static long long OddNumbersTXT(const std::string &input_file) {
    std::ifstream input(input_file);

    int count = 0;
    std::string line;
    while (std::getline(input, line)) {
        std::stringstream str_stream(line);
        int num;
        while (str_stream >> num) {
            if (num % 2 != 0) {
                count++;
        }
    }
}
input.close();
return count;
}
  static void LettersInLine(const std::string &input_file,
                            const std::string &output_file) {
    std::ifstream input(input_file);
    std::ofstream output(output_file);
    std::string line;
    while (std::getline(input, line)) {
      std::stringstream str_stream(line);
      std::string temp;
      int count = 0;
      while (str_stream >> temp) {
        for (int i = 0; i< temp.size()/2;i++){
            count++;
            
            }
        count++;
        }
        
        output << count - 1 << '\n';
    }
    input.close();
    output.close();
  
}
};

int main() {

  std::cout << "задание 1\n";

  WorkFile::RandBinFile("input.bin", 10, 1, 9);
  WorkFile::CopyFile("input.bin", "output.bin");
  std::cout << "Все элементы созданного файла: ";
  WorkFile::ViewFile("input.bin");
  WorkFile::ViewFile("output.bin");
  std::cout << '\n';

  std::cout << "задание 2\n";

  int k = 4;
  WorkFile::RandBinFile("matrix.bin", k * k, 1, 12);
  std::vector<std::vector<int>> arr = WorkFile::ReadMatrix("matrix.bin", k);
  std::cout << "Сгенерированная матрица: \n";
  WorkFile::ViewMatrix(arr);
  std::cout<<"Строка, сумма которой ближе к нулю: "<< WorkFile::MinRows(arr)+1<<"\n";
  

  std::cout << "задание 4\n";
  WorkFile::RandomTXTFile("output.txt", 20, 1, 20);
  std::cout << "Произведение наибольшего и наимееньшего элементов"
            << WorkFile::ProductMinMaxTXT("output.txt") << '\n';

  std::cout << "задание 5\n";
  k = 3;
  WorkFile::RandomTXTLinesFile("output_line.txt", 20, 1, 10, 3);
  std::cout << "Количеество нечетных элемееентов - " 
            << WorkFile::OddNumbersTXT("output_line.txt") << '\n';

  WorkFile::LettersInLine("textlines.txt", "numofletters.txt");
  return 0;
}
