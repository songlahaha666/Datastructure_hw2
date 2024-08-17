# HW2 Polynomial

## 1.解題說明

設計重載操作符，用於輸入輸出。

設計多項式的加法、乘法功能函式。

驗算函數功能是否正確。

### 舉例說明
```cpp 
istream& operator>>(istream& is, Polynomial& p)
ostream& operator<<(ostream& os, const Polynomial& p)
```
宣告重載函式來實現輸入與輸出
## 2.演算法設計與實作

### 加法

```cpp
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
```

### 乘法

```cpp
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
```

## 3.效能分析

### 空間複雜度

terms: O( $n$ )

Add: O( $n1+n2$ ) 其中 n1 和 n2 分別是兩個多項式的非零項數量。

Mult: O( $n1 \times n2$ )

Eval: O( $1$ )

### 時間複雜度

terms: O( $1$ )

Add: O( $n1+n2$ )

Mult: O( $n1 \times n2$ )

Eval: O( $n$ )
## 4.測試

```
輸入第一個多項式:
輸入非零項的數量: 3
輸入第1項的係數和指數: 4 2
輸入第2項的係數和指數: 3 1
輸入第3項的係數和指數: 2 0
輸入第二個多項式:
輸入非零項的數量: 3
輸入第1項的係數和指數: 4 2
輸入第2項的係數和指數: 3 1
輸入第3項的係數和指數: 2 0
第一個多項式: 4x^2+3x^1+2x^0
第二個多項式: 4x^2+3x^1+2x^0
多項式的和: 8x^2+6x^1+4x^0
多項式的積: 16x^4+24x^3+25x^2+12x^1+4x^0
輸入一個值給p1代入:3
p1(3) = 47
```

## 5.心得討論

這次的作業我學到了好多東西，而且也更精進了自己編寫程式碼的邏輯與思維，老師說學一個東西都是要從基礎開始打，
不然後面更難的實作要怎麼辦，我覺得說得很對，所以透過這次打好基礎之後，我感覺我可以更進一步挑戰更難的問題了。
