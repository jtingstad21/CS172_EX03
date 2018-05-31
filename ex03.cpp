#include <iostream>
#include <cmath>
using namespace std;

class Fan {
private:
    int speed; //range 1-3
    bool on;
    int radius; //only positive radius values

public:
    Fan() {
        //the default fan
        speed = 1;
        on = false;
        radius = 5;
    }

    Fan(int s, bool o, int r) {
        //reuse the set functions below
        setSpeed(s);
        on = o;
        setRadius(r);
    }

    //accessor functions
    int getSpeed() { return speed; }
    int getOn() { return on; }
    int getRadius() { return radius; }

    //mutator functions
    void setSpeed(int s) {
        //make sure input is in range, otherwise use the default value
        if (s >= 1 && s <= 3)
            speed = s;
        else
            speed = 1;
    }
    void turnOn() { on = true; }
    void turnOff() { on = false; }
    void setRadius(int r) {
        //make sure input is positive, otherwise use the default value
        if (r > 0)
            radius = r;
        else
            radius = 5;
    }
};

class Quadratic {
private:
    double a, b, c;

public:
    Quadratic(double a, double b, double c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    //accessor functions
    double getA() { return a; }
    double getB() { return b; }
    double getC() { return c; }

    //calculate the discriminant
    double getDiscriminant() {
        return b*b - 4*a*c;
    }

    double getRoot1() {
        double d = getDiscriminant();
        //make sure the discriminant is a legal value
        if (d < 0)
            return 0;
        else
            return (-b + sqrt(d)) / (2*a);
    }

    double getRoot2() {
        //make sure the discriminant is a legal value
        double d = getDiscriminant();
        if (d < 0)
            return 0;
        else
            return (-b - sqrt(d)) / (2*a);
    }
};

class EvenNumber {
private:
    int value;

public:
    //default even number
    EvenNumber() { value = 0; }
    EvenNumber(int value) {
        //If you give me an odd value, I'll make the value bigger.
        if (value % 2 == 1)
            value++;
        this->value = value;
    }

    int getValue() { return value; }
    EvenNumber getNext() { return EvenNumber(value+2); }
    EvenNumber getPrevious() { return EvenNumber(value-2); }
};

string sort(string& s) {
    //simple bubble sort algorithm
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i=0; i<s.size()-1; i++) {
            if (s[i] > s[i+1]) {
                char tmp = s[i];
                s[i] = s[i+1];
                s[i+1] = tmp;
                sorted = false;
            }
        }
    }

    return s;
}

class MyInteger {
private:
    int value;

public:
    MyInteger() { value = 0; }
    MyInteger(int value) { this->value = value; }

    //accessor function
    int getValue() { return value; }
    //Reuse the static isEven function, using this value
    bool isEven() const { return isEven(value); }
    bool isOdd() const { return !isEven(); }
    bool isPrime() const { return isPrime(value); }

    static const bool isEven(int v) { return v % 2 == 0; }
    static const bool isOdd(int v) { return !isEven(v); }
    static const bool isPrime(int v) {
        bool ret = true;
        //count from 2 up to the square root of the value, looking for evenly divisible values
        for (int i=2; i<sqrt(v) && ret; i++) {
            if (v % i == 0)
                ret = false;
        }
        return ret;
    }

    //static functions that take MyInteger objects, but reuse the member functions
    static bool isEven(const MyInteger& i) { return i.isEven(); }
    static bool isOdd(const MyInteger& i) { return i.isOdd(); }
    static bool isPrime(const MyInteger& i) { return i.isPrime(); }

    //Compare for equals
    bool equals(int i) { return i == this->getValue(); }
    bool equals(MyInteger& i) { return i.getValue() == this->getValue(); }

    static int parseInt(const string& s) {
        int ret = 0;
        bool neg = false;
        int start = 0;
        //if the integer is negative, then start at 1
        if (s[0] == '-') {
            start = 1;
            neg = true;
        }
        for (int i=start; i<s.size(); i++) {
            //If we get a non-digit, quit and return 0
            if (s[i] < '0' || s[i] > '9')
                return 0;
            ret = ret*10 + (s[i] - '0');
        }

        //if the string is negative, multiply by -1
        if (neg) ret *= -1;
        return ret;
    }
};

int main() {
    Fan f1, f2(3, true, 10);

    cout << "Fan 1: speed: " << f1.getSpeed() << ", radius: " << f1.getRadius() << ", on? : " << f1.getOn() << endl;
    cout << "Fan 2: speed: " << f2.getSpeed() << ", radius: " << f2.getRadius() << ", on? : " << f2.getOn() << endl;

    Quadratic q1(1,3,2), q2(1,-2,1), q3(1,1,1);

    cout << "q1: " << q1.getRoot1() << ", " << q1.getRoot2() << endl;
    cout << "q2: " << q2.getRoot1() << ", " << q2.getRoot2() << endl;
    cout << "q3: " << q3.getRoot1() << ", " << q3.getRoot2() << endl;

    EvenNumber e(16);
    EvenNumber eP = e.getPrevious();
    EvenNumber eN = e.getNext();

    cout << "Three even numbers: " << eP.getValue() << ", " << e.getValue() << ", " << eN.getValue() << endl;

    cout << "gimme a word: ";
    string word;
    cin >> word;
    sort(word);
    cout << "sorted: " << word << endl;

    MyInteger me(20);
    MyInteger mo(33);
    MyInteger mp(31);

    cout << "Even: " << me.isEven() << ", " << MyInteger::isEven(20) << ", " << MyInteger::isEven(me) << ". ";
    cout << "      " << me.isOdd() << ", " << MyInteger::isOdd(20) << ", " << MyInteger::isOdd(me) << ". ";
    cout << "      " << me.isPrime() << ", " << MyInteger::isPrime(20) << ", " << MyInteger::isPrime(me) << ".\n";
    cout << "Odd: " << mo.isEven() << ", " << MyInteger::isEven(33) << ", " << MyInteger::isEven(mo) << ". ";
    cout << "      " << mo.isOdd() << ", " << MyInteger::isOdd(33) << ", " << MyInteger::isOdd(mo) << ". ";
    cout << "      " << mo.isPrime() << ", " << MyInteger::isPrime(33) << ", " << MyInteger::isPrime(mo) << ".\n";
    cout << "Prime: " << mp.isEven() << ", " << MyInteger::isEven(31) << ", " << MyInteger::isEven(mp) << ". ";
    cout << "      " << mp.isOdd() << ", " << MyInteger::isOdd(31) << ", " << MyInteger::isOdd(mp) << ". ";
    cout << "      " << mp.isPrime() << ", " << MyInteger::isPrime(31) << ", " << MyInteger::isPrime(mp) << ".\n";

    cout << "Equals: " << mp.equals(mp) << ", " << mp.equals(mp.getValue()) << ", " << mp.equals(me) << ", " << mp.equals(me.getValue()) << ".\n";
    cout << "Parse: " << MyInteger::parseInt("1234") << ", " << MyInteger::parseInt("5") << ", " << MyInteger::parseInt("-5") << ", " << MyInteger::parseInt("test") << endl;
}