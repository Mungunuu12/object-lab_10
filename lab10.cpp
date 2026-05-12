#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// =====================================================
// 1-р хүн хийх хэсэг:
// Template LinkedList классын үндсэн бүтэц
// add, insert, get, delete, length функцуудыг бүрэн хэрэгжүүлнэ.
// =====================================================

template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;

        Node(T value) {
            data = value;
            next = nullptr;
        }
    };

    Node* head;
    int size;

public:
    LinkedList() {
        head = nullptr;
        size = 0;
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(T t) {
        Node* newNode = new Node(t);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }

        size++;
    }

    void insert(T t, int index) {
        if (index < 0 || index > size) {
            cout << "Index buruu baina!" << endl;
            return;
        }

        Node* newNode = new Node(t);

        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;

            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
        }

        size++;
    }

    T get(int index) {
        if (index < 0 || index >= size) {
            cout << "Index buruu baina!" << endl;
            return nullptr;
        }

        Node* current = head;

        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->data;
    }

    void deleteAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Index buruu baina!" << endl;
            return;
        }

        Node* temp;

        if (index == 0) {
            temp = head;
            head = head->next;
        } else {
            Node* current = head;

            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }

            temp = current->next;
            current->next = temp->next;
        }

        delete temp;
        size--;
    }

    int length() {
        return size;
    }

    void swapData(int i, int j) {
        T temp = get(i);
        Node* nodeI = head;
        Node* nodeJ = head;

        for (int a = 0; a < i; a++) nodeI = nodeI->next;
        for (int b = 0; b < j; b++) nodeJ = nodeJ->next;

        nodeI->data = nodeJ->data;
        nodeJ->data = temp;
    }
};


// =====================================================
// 2-р хүн хийх хэсэг:
// Lab7 дээрх Shape, Shape2D, Circle, Square, Triangle классуудыг
// шинэ даалгаварт тохируулж цэвэрхэн бичнэ.
// area(), perimeter(), print() функцуудыг override хийж хэрэгжүүлнэ.
// =====================================================

class Shape {
protected:
    string name;

public:
    Shape(string n = "Unknown") {
        name = n;
    }

    virtual double area() = 0;
    virtual double perimeter() = 0;

    string getName() {
        return name;
    }

    virtual void print() {
        cout << "Shape: " << name << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }

    virtual ~Shape() {}
};

class Shape2D : public Shape {
protected:
    double x, y;

public:
    Shape2D(string n, double x0, double y0)
        : Shape(n), x(x0), y(y0) {}
};

class Circle : public Shape2D {
private:
    double radius;

public:
    Circle(double x, double y, double r)
        : Shape2D("Circle", x, y), radius(r) {}

    double area() override {
        return 3.14159 * radius * radius;
    }

    double perimeter() override {
        return 2 * 3.14159 * radius;
    }

    void print() override {
        cout << "Circle" << endl;
        cout << "Radius: " << radius << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
        cout << "------------------------" << endl;
    }
};

class Square : public Shape2D {
private:
    double side;

public:
    Square(double x, double y, double s)
        : Shape2D("Square", x, y), side(s) {}

    double area() override {
        return side * side;
    }

    double perimeter() override {
        return 4 * side;
    }

    void print() override {
        cout << "Square" << endl;
        cout << "Side: " << side << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
        cout << "------------------------" << endl;
    }
};

class Triangle : public Shape2D {
private:
    double side;

public:
    Triangle(double x, double y, double s)
        : Shape2D("Triangle", x, y), side(s) {}

    double area() override {
        return (sqrt(3) / 4) * side * side;
    }

    double perimeter() override {
        return 3 * side;
    }

    void print() override {
        cout << "Triangle" << endl;
        cout << "Side: " << side << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
        cout << "------------------------" << endl;
    }
};


// =====================================================
// 3-р хүн хийх хэсэг:
// main функц дээр 20-30 санамсаргүй дүрс үүсгэнэ.
// LinkedList<Shape*> ашиглан хадгална.
// Дүрсүүдийг төрөл харгалзахгүйгээр area()-аар эрэмбэлж хэвлэнэ.
// =====================================================

void sortByArea(LinkedList<Shape*>& list) {
    int n = list.length();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            Shape* a = list.get(j);
            Shape* b = list.get(j + 1);

            if (a->area() > b->area()) {
                list.swapData(j, j + 1);
            }
        }
    }
}

int main() {
    srand(time(0));

    LinkedList<Shape*> shapes;

    int count = 20 + rand() % 11; 
    // 20-30 ширхэг дүрс санамсаргүй үүсгэнэ

    for (int i = 0; i < count; i++) {
        int type = rand() % 3;
        double x = rand() % 100;
        double y = rand() % 100;
        double side = 1 + rand() % 20;

        if (type == 0) {
            shapes.add(new Circle(x, y, side));
        } 
        else if (type == 1) {
            shapes.add(new Square(x, y, side));
        } 
        else {
            shapes.add(new Triangle(x, y, side));
        }
    }

    cout << "Niit uusgesen dursiin too: " << shapes.length() << endl;
    cout << "\n--- Talbaigaar erembelegdeegui jagsaalt ---\n" << endl;

    for (int i = 0; i < shapes.length(); i++) {
        shapes.get(i)->print();
    }

    sortByArea(shapes);

    cout << "\n--- Talbaigaar eremblegdsen jagsaalt ---\n" << endl;

    for (int i = 0; i < shapes.length(); i++) {
        shapes.get(i)->print();
    }

    // Санах ой чөлөөлөх
    for (int i = 0; i < shapes.length(); i++) {
        delete shapes.get(i);
    }

    return 0;
}