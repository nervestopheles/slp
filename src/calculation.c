void CalcOfSets()
{
    system("clear");

    /* Данные по которым будут считаться множества */
    printf("\n-------------------- Source Data --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        printf("%10s: (x%i) | V = %6.3f | M = %4.0f \n", 
                data[i].name, i+1, data[i].V, data[i].M);
    }

    /* Функции Принадлежности */
    printf("\n-------------------- Membership Functions --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        memberArrV[i] = Membership(data[i].V, minV, midV, maxV, 1);
        memberArrM[i] = Membership(data[i].M, minM, midM, maxM, 0);
        printf("%10s: (x%i) | %5.3f | %5.3f \n", 
                data[i].name, i+1, memberArrV[i], memberArrM[i]);
    }

    /* Дополнение | Инверсия */
    printf("\n-------------------- Supplement --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        supplementArrV[i] = Supplement(memberArrV[i]);
        supplementArrM[i] = Supplement(memberArrM[i]);
        printf("%10s: (x%i) | %5.3f | %5.3f \n", 
                data[i].name, i+1, supplementArrV[i], supplementArrM[i]);
    }

    /* Нахождение ближайшего четкого множества */
    printf("\n-------------------- Near --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        nearArrV[i] = Near(memberArrV[i]);
        nearArrM[i] = Near(memberArrM[i]);
        printf("%10s: (x%i) | %1.0f | %1.0f \n", 
            data[i].name, i+1, nearArrV[i], nearArrM[i]);
    }

    /* Расстояние Хэмминга */
    printf("\n-------------------- Hamming Distance --------------------\n\n"); 
    HammingDistance(memberArrV, nearArrV, hammingDistV);
    HammingDistance(memberArrM, nearArrM, hammingDistM);
    for (int i = 0; i < arrLength; i++) {
        printf("%10s: (x%i) | %5.3f | %5.3f \n", 
            data[i].name, i+1, hammingDistV[i], hammingDistM[i]);
    }

    /* Линейный индекс нечеткости */
    printf("\n-------------------- Linear Fuzzy Index --------------------\n\n"); 
    linearFuzzyIndexV = LinearFuzzyIndex(hammingDistV);
    linearFuzzyIndexM = LinearFuzzyIndex(hammingDistM);
    printf("  Capacity: %5.3f\n", linearFuzzyIndexV); 
    printf("  Mass: %5.3f\n", linearFuzzyIndexM);

    /* Пересечение | MIN */
    printf("\n-------------------- Intersection --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        intersectionArr[i] = Intersection(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, intersectionArr[i]);
    }

    /* Объединение | MAX */
    printf("\n-------------------- Union --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        unionArr[i] = Union(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, unionArr[i]);
    }

    /* Разность V от M */
    printf("\n-------------------- Difference V - M --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        differenceArr_VM[i] = Difference(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, differenceArr_VM[i]);
    }

    /* Разность M от V */
    printf("\n-------------------- Difference M - V --------------------\n\n"); 
    for (int i = 0; i < arrLength; i++) {
        differenceArr_MV[i] = Difference(memberArrM[i], memberArrV[i]);
        printf("  (x%i) | %5.3f \n", i+1, differenceArr_MV[i]);
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
        multiplicationArr[i] = Multiplication(memberArrV[i], memberArrM[i]);
        printf("  (x%i) | %5.3f \n", i+1, multiplicationArr[i]);
    }

    /* Декартово | Прямое произведение */
    printf("\n-------------------- Cartesian Product --------------------\n\n"); 
    CartesianProduct(memberArrV, memberArrM, cartesianProductArr);
    for (int i = 0; i < sizeof(cartesianProductArr)/sizeof(double); i++) {
        printf("  (x%2i) | %5.3f \n", i+1, *(cartesianProductArr + i));
    }
}