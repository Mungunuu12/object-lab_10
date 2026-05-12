#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

template <class T>
class LinkedList{
private:
    class Node{
    public:
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
    LinkedList(){
        head = nullptr;
        size = 0;
    }
    void add(T t){
        Node* newNode = new Node(t);
        if (head == nullptr){
            head = newNode;
        } 
        else{
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        size++;
    }
    void insert(T t, int index) {
        Node* newNode = new Node(t);
        if (index == 0){
            newNode->next = head;
            head = newNode;
        } 
        else{
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
        if (index == 0){
            temp = head;
            head = head->next;
        } 
        else{
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

class Shape {
protected:
    string name;

public:
    Shape(string n) : name(n) {}
    string ner() const { return name; }
};

class TwoDShape : public Shape {
protected:
    double urt;
    double x;
    double y;

public:
    TwoDShape(string n, double x, double y, double r) : Shape(n), x(x), y(y), urt(r) {}
    virtual double talbai() = 0;
    virtual double perimeter() = 0;
    virtual string turul() = 0;
};

class Circle : public TwoDShape {
public:
    Circle(string n, double tuvX, double tuvY, double r) : TwoDShape(n, tuvX, tuvY, r) {}
    double talbai() override {
        return urt * urt * M_PI;
    }
    double perimeter() override {
        return urt * M_PI * 2;
    }
    string turul() override {
        return "Toirog";
    }
};

class Square : public TwoDShape {
private:
    double sx[4];
    double sy[4];

public:
    Square(string n, double zahX, double zahY, double side) : TwoDShape(n,zahX, zahY, side){
        sx[0] = zahX;
        sy[0] = zahY;
        sx[1] = zahX + side;
        sy[1] = zahY;
        sx[2] = zahX;
        sy[2] = zahY - side;
        sx[3] = zahX + side;
        sy[3] = zahY - side;
    }
    double talbai() override {
        return urt * urt;
    }
    double perimeter() override {
        return 4 * urt;
    }
    string turul() override {
        return "Kvadrat";
    }
};

class Triangle : public TwoDShape {
private:
    double tx[3];
    double ty[3];
    double undur;
    
public:
    Triangle(string n, double deedX, double deedY, double side) : TwoDShape(n, deedX, deedY, side) {
        undur = side * (sqrt(3.0) / 2.0);
        tx[0] = deedX;
        ty[0] = deedY;
        tx[1] = deedX - (side / 2.0);
        ty[1] = deedY - undur;
        tx[2] = deedX + (side / 2.0);
        ty[2] = deedY - undur;
    }
    double talbai() override {
        return urt * undur / 2.0;
    }
    double perimeter() override {
        return 3 * urt;
    }
    string turul() override {
        return "Gurvaljin";
    }
};

void sort(LinkedList<TwoDShape*>& list) {
    int n = list.length();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            TwoDShape* a = list.get(j);
            TwoDShape* b = list.get(j + 1);
            if (a->talbai() > b->talbai()) {
                list.swapData(j, j + 1);
            }
        }
    }
}

int main() {
    LinkedList<TwoDShape*> shapes;
    int count = 20 + rand() % 11; 
    int countCircle = 0, countSquare = 0, countTriangle = 0;
    for (int i = 0; i < count; i++) {
        int type = rand() % 3;
        double x = rand() % 100;
        double y = rand() % 100;
        double side = 1 + rand() % 20;
        if (type == 0){
            countCircle++;
            shapes.add(new Circle("Circle" + to_string(countCircle), x, y, side));
        } 
        else if (type == 1){
            countSquare++;
            shapes.add(new Square("Square" + to_string(countSquare), x, y, side));
        }
        else{
            countTriangle++;
            shapes.add(new Triangle("Triangle" + to_string(countTriangle), x, y, side));
        }
    }
    cout << "Niit uusgesen dursiin too: " << shapes.length() << endl;
    sort(shapes);
    cout << "\n--- Talbaigaar eremblegdsen jagsaalt ---\n" << endl;
    for (int i = 0; i < shapes.length(); i++){
        TwoDShape* s = shapes.get(i);
        cout << s->ner() << "\t" << s->turul()
             << "\n ~ Talbai: "    << s->talbai()
             << "\n ~ Perimeter: " << s->perimeter() << "\n";
    }
    for (int i = 0; i < shapes.length(); i++){
        delete shapes.get(i);
    }
    return 0;
}