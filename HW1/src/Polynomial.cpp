#include <iostream>
#include <cmath> // �Ω� pow ���
using namespace std;

class Polynomial; // Forward declaration

class Term {
    friend Polynomial;
public:
    float coef; // �Y��
    int exp;    // ����
};

class Polynomial {
public:
    Polynomial(); // �غc�h���� p(x) = 0
    ~Polynomial(); // �Ѻc�l����ʺA�O����
    Polynomial Add(const Polynomial& poly) const; // �h�����ۥ[
    Polynomial Mult(const Polynomial& poly) const; // �h�����ۭ�
    float Eval(float f) const; // �p��h�����b f ����
    friend istream& operator>>(istream& is, Polynomial& p); // �h������J
    friend ostream& operator<<(ostream& os, const Polynomial& p); // �h������X

private:
    Term* termArray; // �D�s�����}�C
    int capacity;    // termArray ���j�p
    int terms;       // �D�s�����ƶq
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

    // �����Y�Ƭ�0������
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
    cout << "��J�D�s�����ƶq: ";
    is >> p.terms;
    p.capacity = p.terms;
    delete[] p.termArray; // ������e���ʺA�O����
    p.termArray = new Term[p.capacity];

    for (int i = 0; i < p.terms; ++i) {
        cout << "��J��" << i + 1 << "�����Y�ƩM����: ";
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
    cout << "��J�Ĥ@�Ӧh����:\n";
    cin >> p1;
    cout << "��J�ĤG�Ӧh����:\n";
    cin >> p2;

    Polynomial sum = p1.Add(p2);
    Polynomial product = p1.Mult(p2);

    cout << "�Ĥ@�Ӧh����: " << p1 << endl;
    cout << "�ĤG�Ӧh����: " << p2 << endl;
    cout << "�h�������M: " << sum << endl;
    cout << "�h�������n: " << product << endl;

    return 0;
}
