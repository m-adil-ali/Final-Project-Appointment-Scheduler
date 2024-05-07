#include <iostream>

using namespace std;

class Rectangle
{
private:
    int length;
    int width;
public:
   /* Rectangle() {
        length = 0;
        width = 0;
        area = 0;
    }*/
    void SetLength(int l) {
        length = l;
        //SetArea();
    }
    void SetWidth(int w) {
        width = w;
        //SetArea();
    }
    int getlength()
    {
        return length;
    }
    int getwidth()
    {
        return width;
    }

    
    int area()
    {
        return length * width;
    }
    int perimeter()
    {
        return 2*(length+width)
    }
    void TakeInput() {
        cout << "Enter Width: ";
        cin >> width;
        cout << "Enter Length: ";
        cin >> length;
        //SetArea();
    }

    
    

    /*void SetArea() {
        area = length * width;
    }*/

    void PrintData() {
        cout << "Length is: " << length << endl;
        cout << "Width is: " << width << endl;
        cout << "Area is: " << area << endl;
        cout << "Perimeter is: " << perimeter << endl;
    }
};

int main() {
    Rectangle R1;
    //cout << R1.area() << endl;
   R1.TakeInput();
    /*cout << R1.getlength() << endl;
    cout << R1.getwidth() << endl;
    R1.PrintData();*/
    // R1.SetLength(3);
    // R1.SetWidth(2);
    // R1.PrintData();
    //return 0;
}