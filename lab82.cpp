#include <iostream>
#include <utility>  
#include <atomic>

template<class T>
class MyShared
{
    T* p = nullptr;
    std::atomic<int>* count = nullptr;

public:
    explicit MyShared(T* p = nullptr) : p(p), count(new std::atomic<int>(1)) {}
    MyShared(const MyShared& other) : p(other.p), count(other.count) {
        if (count) {
            ++(*count);
        }
    }
    MyShared& operator=(const MyShared& other) {
        if (this != &other) {
            cleanup();
            p = other.p;
            count = other.count;
            if (count) {
                ++(*count);
            }
        }
        return *this;
    }
    MyShared(MyShared&& other) noexcept : p(other.p), count(other.count) {
        other.p = nullptr;
        other.count = nullptr;
    }
    MyShared& operator=(MyShared&& other) noexcept {
        if (this != &other) {
            cleanup();
            p = other.p;
            count = other.count;
            other.p = nullptr;
            other.count = nullptr;
        }
        return *this;
    }
    ~MyShared() {
        cleanup();
    }
    T* get() const {
        return p;
    }
    T& operator*() const {
        return *p;
    }
    T* operator->() const {
        return p;
    }

private:
    void cleanup() {
        if (count && --(*count) == 0) {
            delete p;
            delete count;
        }
    }
};

template<class T, class... Args>
MyShared<T> Make_MyShared(Args&&... args) {
    return MyShared<T>(new T(std::forward<Args>(args)...));
}

class MyPoint {
    int x, y;

public:
    MyPoint(int x, int y) : x(x), y(y) {
        std::cout << "MyPoint(" << x << ", " << y << ")\n";
    }

    void print() const {
        std::cout << "MyPoint(" << x << ", " << y << ")\n";
    }
};

int main() {
    MyShared<MyPoint> point1 = Make_MyShared<MyPoint>(3, 4);
    point1->print();
    MyShared<MyPoint> point2 = point1;
    point2->print();
    MyShared<MyPoint> point3 = Make_MyShared<MyPoint>(5, 6);
    point3->print();
    point3 = point1;
    point3->print();
    MyShared<MyPoint> point4 = std::move(point1);
    point4->print();


    return 0;
}
