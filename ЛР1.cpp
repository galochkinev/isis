#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>


class CustomArray {
public:
    using Iterator = double*;

    CustomArray(size_t allocSize = minSize) : mElements(0), mAllocSize(0), mSize(0) {
        allocate(allocSize);
    }

    CustomArray(const CustomArray& other) : CustomArray() {
        *this = other;
    }

    CustomArray(double* array, int size) : CustomArray() {
        CustomArray created = CustomArray(size);

        for (int index = 0; index < size; ++index) {
            created.pushBack(array[index]);
        }

        *this = created;
    }

    CustomArray(Iterator first, Iterator last) : CustomArray() {
        if (first > last)
            throw std::logic_error("invalid iterators order");
        CustomArray created;
        for (Iterator it = first; it != last; ++it)
            created.pushBack(*it);
        *this = created;
    }

    ~CustomArray() { free(); }

    double& operator[](size_t index) {
        if (0 <= index && index < size())
            return mElements[index];
        else
            throw std::out_of_range("out of range");
    }

    friend std::ostream& operator<<(std::ostream& out, const CustomArray& array) {
        out << std::setprecision(3) << std::fixed;
        for (int i = 0; i < array.size(); i++) {
            out << array.mElements[i] << " ";
        }
        return out << std::endl;
    }

    CustomArray& operator=(const CustomArray& other) {
        if (this != &other) {
            free();
            mAllocSize = other.mAllocSize;
            mSize = other.mSize;
            mElements = new double[mAllocSize];
            for (unsigned i = 0; i < mSize; ++i) {
                mElements[i] = other.mElements[i];
            }
        }
        return *this;
    }

    double* begin() const { return mElements; }
    double* end() const { return (mElements + mSize); }

    void clear() {
        resize(10);
        mSize = 0;
    }

    void resize(size_t reallocSize) {
        if (reallocSize > maxSize)
            throw std::invalid_argument("array too long");
        if (reallocSize == mAllocSize)
            return;
        if (reallocSize == 0) {
            free();
            mElements = 0;
        }
        else {
            double* newElements = new double[reallocSize];
            mAllocSize = reallocSize;
            if (mSize > reallocSize)
                mSize = reallocSize;
            for (unsigned i = 0; i < mSize; ++i)
                newElements[i] = mElements[i];
            free();
            mElements = newElements;
        }
    }

    size_t size() const { return mSize; }
    size_t capacity() const { return mAllocSize; }

    void popBack() {
        if (mSize)
            --mSize;
        else
            throw std::logic_error("empty array deleting");
    }

    void pushBack(double newElement) {
        if (size() >= capacity())
            resize(std::min(capacity() + 10, maxSize));
        ++mSize;
        mElements[size() - 1] = newElement;
    }

    void print(bool writeNewLine = true) const {
        if (size() == 0) {
            std::cout << "array is empty";
            if (writeNewLine)
                std::cout << "\n";
            return;
        }
        for (auto element : *this)
            std::cout << element << " ";
        if (writeNewLine)
            std::cout << "\n";
    }

private:
    static size_t minSize;
    double* mElements;
    size_t mAllocSize;
    size_t mSize
static size_t maxSize;

    void allocate(size_t allocSize) {
        if (allocSize > maxSize)
            throw std::invalid_argument("array too long");
        if (allocSize < minSize)
            allocSize = minSize;
        mAllocSize = allocSize;
        mElements = new double[mAllocSize];
    }

    void free() {
        if (mElements) {
            delete[] mElements;
            mElements = 0;
        }
    }
};

size_t CustomArray::minSize = 10;
size_t CustomArray::maxSize = 10000;

CustomArray createCustomArray(double* array, int size) {
    return CustomArray(array, size);
}

double randDouble(int min, int max) {
    int range = max - min + 1;
    return std::rand() % range + min;
}

struct MainTaskModel {
    double sum;
    double avg;
};

MainTaskModel mainTask(CustomArray& array) {
    double sum = 0;
    double avg = 0;

    std::cout << array;

    for (int i = 0; i < array.size(); i++) {
        sum += array[i];
    }

    avg = sum / array.size();

    array.pushBack(sum);
    array.pushBack(avg);

    std::cout << array;

    MainTaskModel result = { sum, avg };

    return result;
}

void task7(CustomArray& array) {
    mainTask(array);

    CustomArray negativeNumbers = CustomArray();

    for (int i = 0; i < array.size(); i++) {
        auto target = array[i];
        if (target < 0) {
            negativeNumbers.pushBack(target);
        }
    }

    auto taskDelimiter = (negativeNumbers[0] + negativeNumbers[negativeNumbers.size() - 1]) * 2;
    auto delimiter = taskDelimiter ? taskDelimiter : 1;

    for (int i = 0; i < array.size(); i++) {
        if ((i + 1) % 3 == 0) {
            array[i] *= delimiter;
        }
    }

    std::cout << array;
}

int main() {
    int size;
    std::cin >> size;
    double* input = new double[size];

    for (int i = 0; i < size; i++) {
        std::cin >> input[i];
    }

    CustomArray arr = createCustomArray(input, size);

    int code;
    double argument;

    std::cout << arr.size() << std::endl;
    task7(arr);

    while (std::cin >> code) {
        if (code == 0)
            break;

        switch (code) {
        case 1:
            std::cin >> argument;
            arr.pushBack(argument);
            std::cout << "+: " << arr.size() << std::endl;
            task7(arr);
            break;
        case 2:
            arr.popBack();
            std::cout << "-: " << arr.size() << std::endl;
            task7(arr);
            break;
        }
    }
    delete[] input;
    return 0;
}
