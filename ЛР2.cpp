#include <iostream>
#include <vector>
#include <stdexcept>

class Array {
private:
    std::vector<int> data;
    int lowerBound;
    int upperBound;

public:
    Array(int lower, int upper) : lowerBound(lower), upperBound(upper) {
        data.resize(upper - lower + 1, 0);
    }

    ~Array() {}

    void set(int index, int value) {
        if (index < lowerBound || index > upperBound) {
            throw std::out_of_range("wrong index");
        }
        data[index - lowerBound] = value;
    }

    int get(int index) const {
        if (index < lowerBound || index > upperBound) {
            throw std::out_of_range("wrong index");
        }
        return data[index - lowerBound];
    }

    Array operator+(int constant) const {
        Array result(lowerBound, upperBound);
        for (int i = 0; i < data.size(); ++i) {
            result.set(lowerBound + i, data[i] + constant);
        }
        return result;
    }

    Array operator*(int constant) const {
        Array result(lowerBound, upperBound);
        for (int i = 0; i < data.size(); ++i) {
            result.set(lowerBound + i, data[i] * constant);
        }
        return result;
    }

    Array operator+(const Array& other) const {
        if (lowerBound != other.lowerBound || upperBound != other.upperBound) {
            throw std::invalid_argument("Arrays have different bounds");
        }

        Array result(lowerBound, upperBound);
        for (int i = 0; i < data.size(); ++i) {
            result.set(lowerBound + i, data[i] + other.data[i]);
        }
        return result;
    }

    Array operator*(const Array& other) const {
        if (lowerBound != other.lowerBound || upperBound != other.upperBound) {
            throw std::invalid_argument("Arrays have different bounds");
        }

        Array result(lowerBound, upperBound);
        for (int i = 0; i < data.size(); ++i) {
            result.set(lowerBound + i, data[i] * other.data[i]);
        }
        return result;
    }

    Array operator-(const Array& other) const {
        if (lowerBound != other.lowerBound || upperBound != other.upperBound) {
            throw std::invalid_argument("Arrays have different bounds");
        }

        Array result(lowerBound, upperBound);
        for (int i = 0; i < data.size(); ++i) {
            result.set(lowerBound + i, data[i] - other.data[i]);
        }
        return result;
    }

    Array operator/(const Array& other) const {
        if (lowerBound != other.lowerBound || upperBound != other.upperBound) {
            throw std::invalid_argument("Arrays have different bounds");
        }

        Array result(lowerBound, upperBound);
        for (int i = 0; i < data.size(); ++i) {
            if (other.data[i] != 0) {
                result.set(lowerBound + i, data[i] / other.data[i]);
            }
            else {
                throw std::invalid_argument("delenie na 0");
            }
        }
        return result;
    }

    void print() const {
        for (int i = 0; i < data.size(); ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    int lowerBound, upperBound;
    std::cin >> lowerBound >> upperBound;

    Array array1(lowerBound, upperBound);
    Array array2(lowerBound, upperBound);

    for (int i = lowerBound; i <= upperBound; ++i) {
        int value;
        std::cin >> value;
        array1.set(i, value);
    }

    for (int i = lowerBound; i <= upperBound; ++i) {
        int value;
        std::cin >> value;
        array2.set(i, value);
    }

    int constant;
    std::cin >> constant;

    std::cout << "Array1= ";
    array1.print();

    std::cout << "Array1+const= ";
    (array1 + constant).print();

    std::cout << "Array1*const= ";
    (array1 * constant).print();

    std::cout << "Array2= ";
    array2.print();

    std::cout << "Array2+const= ";
    (array2 + constant).print();

    std::cout << "Array2*const= ";
    (array2 * constant).print();

    std::cout << "summa= ";
    (array1 + array2).print();

    std::cout << "raznost= ";
    (array1 - array2).print();

    std::cout << "proizv= ";
    (array1 * array2).print();

    try {
        Array divide = array1 / array2;
        std::cout << "delenie= ";
        divide.print();
    }
    catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    while (true) {
        int action, index;
        std::cin >> action >> index;
        if (action == 0) {
            break;
        }
        else if (action == 1) {
            try {
                int value = array1.get(index);
                std::cout << "Array1[" << index << "]= " << value << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cout << "Array1 " << e.what() << " " << index << std::endl;
            }
        }
        else if (action == 2) {
            try {
                int value = array2.get(index);
                std::cout << "Array2[" << index << "]= " << value << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cout << "Array2 " << e.what() << " " << index << std::endl;
            }
        }
        else {
            std::cout << "Invalid action" << std::endl;
        }
    }

    return 0;
}