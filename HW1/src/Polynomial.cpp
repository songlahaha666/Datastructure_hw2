#include <iostream>
#include <cmath> // 用於 pow 函數
using namespace std;

class Polynomial; // Forward declaration

class Term {
    friend Polynomial;
public:
    float coef; // 係數
    int exp;    // 指數
};

class Polynomial {
public:
    Polynomial(); // 建構多項式 p(x) = 0
    ~Polynomial(); // 解構子釋放動態記憶體
    Polynomial Add(const Polynomial& poly) const; // 多項式相加
    Polynomial Mult(const Polynomial& poly) const; // 多項式相乘
    float Eval(float f) const; // 計算多項式在 f 的值
    friend istream& operator>>(istream& is, Polynomial& p); // 多項式輸入
    friend ostream& operator<<(ostream& os, const Polynomial& p); // 多項式輸出

private:
    Term* termArray; // 非零項的陣列
    int capacity;    // termArray 的大小
    int terms;       // 非零項的數量
};

Polynomial::Polynomial() : capacity(1), terms(0) {
    termArray = new Term[capacity];
}

Polynomial::~Polynomial() {
    delete[] termArray;
}

Polynomial Polynomial::Add(const Polynomial& poly) const {
    Polynomial result;
    result.capacity = terms + poly.terms;
    result.termArray = new Term[result.capacity];

    int thisPos = 0, polyPos = 0, resultPos = 0;

    while (thisPos < terms && polyPos < poly.terms) {
        if (termArray[thisPos].exp == poly.termArray[polyPos].exp) {
            float sumCoef = termArray[thisPos].coef + poly.termArray[polyPos].coef;
            if (sumCoef != 0) {
                result.termArray[resultPos].coef = sumCoef;
                result.termArray[resultPos].exp = termArray[thisPos].exp;
                resultPos++;
            }
            thisPos++;
            polyPos++;
        }
        else if (termArray[thisPos].exp > poly.termArray[polyPos].exp) {
            result.termArray[resultPos] = termArray[thisPos];
            thisPos++;
            resultPos++;
        }
        else {
            result.termArray[resultPos] = poly.termArray[polyPos];
            polyPos++;
            resultPos++;
        }
    }

    while (thisPos < terms) {
        result.termArray[resultPos] = termArray[thisPos];
        thisPos++;
        resultPos++;
    }

    while (polyPos < poly.terms) {
        result.termArray[resultPos] = poly.termArray[polyPos];
        polyPos++;
        resultPos++;
    }

    result.terms = resultPos;
    return result;
}

Polynomial Polynomial::Mult(const Polynomial& poly) const {
    Polynomial result;
    result.capacity = terms * poly.terms;
    result.termArray = new Term[result.capacity];

    for (int i = 0; i < terms; ++i) {
        for (int j = 0; j < poly.terms; ++j) {
            float newCoef = termArray[i].coef * poly.termArray[j].coef;
            int newExp = termArray[i].exp + poly.termArray[j].exp;
            bool found = false;

            for (int k = 0; k < result.terms; ++k) {
                if (result.termArray[k].exp == newExp) {
                    result.termArray[k].coef += newCoef;
                    found = true;
                    break;
                }
            }

            if (!found) {
                result.termArray[result.terms].coef = newCoef;
                result.termArray[result.terms].exp = newExp;
                result.terms++;
            }
        }
    }

    // 移除係數為0的項次
    int validTerms = 0;
    for (int i = 0; i < result.terms; ++i) {
        if (result.termArray[i].coef != 0) {
            result.termArray[validTerms++] = result.termArray[i];
        }
    }
    result.terms = validTerms;

    return result;
}

float Polynomial::Eval(float f) const {
    float result = 0.0;
    for (int i = 0; i < terms; ++i) {
        result += termArray[i].coef * pow(f, termArray[i].exp);
    }
    return result;
}

istream& operator>>(istream& is, Polynomial& p) {
    cout << "輸入非零項的數量: ";
    is >> p.terms;
    p.capacity = p.terms;
    delete[] p.termArray; // 釋放先前的動態記憶體
    p.termArray = new Term[p.capacity];

    for (int i = 0; i < p.terms; ++i) {
        cout << "輸入第" << i + 1 << "項的係數和指數: ";
        is >> p.termArray[i].coef >> p.termArray[i].exp;
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& p) {
    for (int i = 0; i < p.terms; ++i) {
        if (i > 0 && p.termArray[i].coef > 0) os << "+";
        os << p.termArray[i].coef << "x^" << p.termArray[i].exp;
    }
    return os;
}

int main() {
    Polynomial p1, p2;
    cout << "輸入第一個多項式:\n";
    cin >> p1;
    cout << "輸入第二個多項式:\n";
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "第一個多項式: " << p1 << endl;
    cout << "第二個多項式: " << p2 << endl;
    cout << "多項式的和: " << sum << endl;
    cout << "多項式的積: " << product << endl;

    return 0;
}
