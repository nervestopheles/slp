#include <stdlib.h>
#include <stdio.h>

#include "settings.h"
#include "foo.c"

int main(void) 
{
    double memberArrV[arrLength];
    double memberArrM[arrLength];

    double complementArrV[arrLength];
    double complementArrM[arrLength];

    double intersectionArr[arrLength];
    double unionArr[arrLength];

    double limitedAmountArr[arrLength];
    double differenceArr[arrLength];

    double multiplicationArr[arrLength];
    double *cartesianProductArr;

    double minV = 1, maxV = 12;
    double midV = (minV + maxV) / 2;

    double minM = 300, maxM = 1200;
    double midM = (minM + maxM) / 2;

    printf("\n-------------------- Source Data --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        printf("%10s:  (x%i) | V = %6.3f | M = %.0f \n", Data[i].name, i+1, Data[i].V, Data[i].M);
    } 
    
    /* Функции Принадлежности */
    printf("\n-------------------- Membership Functions --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        memberArrV[i] = membership(Data[i].V, minV, midV, maxV, 1);
        memberArrM[i] = membership(Data[i].M, minM, midM, maxM, 0);
        printf("%10s:  (x%i) | %5.3f | %5.3f \n", Data[i].name, i+1, memberArrV[i], memberArrM[i]);
    }

    /* Дополнение | Инверсия */
    printf("\n-------------------- Complemet --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        complementArrV[i] = complement(memberArrV[i]);
        complementArrM[i] = complement(memberArrM[i]);
        printf("%10s:  (x%i) | %5.3f | %5.3f \n", Data[i].name, i+1, complementArrV[i], complementArrM[i]);
    }

    /* Пересечение | MIN */
    printf("\n-------------------- Intersection --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        intersectionArr[i] = intersection(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, intersectionArr[i]);
    }

    /* Объединение | MAX */
    printf("\n-------------------- Union --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        unionArr[i] = Union(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, unionArr[i]);
    }

    /* Разность */
    printf("\n-------------------- Difference --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        differenceArr[i] = difference(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, differenceArr[i]);
    }

    /* Ограниченная Сумма */
    printf("\n-------------------- Limited Amount --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        limitedAmountArr[i] = LimitedAmount(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, limitedAmountArr[i]);
    }

    /* Алгебраическое произведение */
    printf("\n-------------------- Multiplication --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        multiplicationArr[i] = multiplication(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, multiplicationArr[i]);
    }

    /* Декартово | Прямое произведение */
    printf("\n-------------------- Cartesian Product --------------------\n\n"); 
    cartesianProductArr = CartesianProduct(memberArrV, memberArrM);
    for (int i = 0; i < arrLength*arrLength; i++) {
        printf("  (x%2i) | %5.3f \n", i+1, *(cartesianProductArr + i));
    }

    printf("\n-------------------------------------------------------------\n");
    return 0;
}

