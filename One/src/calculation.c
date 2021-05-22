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
    double dataV[arrLength], dataM[arrLength];
    for (int i = 0; i < arrLength; i++) {
       dataV[i] = data[i].V;
       dataM[i] = data[i].M;
    }
    MembershipHigh(dataV, memberArrV, minV, midV, maxV);
    MembershipLow(dataM, memberArrM, minM, midM, maxM);
    for (int i = 0; i < arrLength; i++) {
        printf("%10s: (x%i) | %5.3f | %5.3f \n", 
            data[i].name, i+1, memberArrV[i], memberArrM[i]);
    }

    /* Дополнение | Инверсия */
    printf("\n-------------------- Supplement --------------------\n\n"); 
    Supplement(memberArrV, supplementArrV);
    Supplement(memberArrM, supplementArrM);
    for (int i = 0; i < arrLength; i++) {
        printf("%10s: (x%i) | %5.3f | %5.3f \n", 
            data[i].name, i+1, supplementArrV[i], supplementArrM[i]);
    }

    /* Нахождение ближайшего четкого множества */
    printf("\n-------------------- Near --------------------\n\n"); 
    Near(memberArrV, nearArrV);
    Near(memberArrM, nearArrM);
    for (int i = 0; i < arrLength; i++) {
        printf("%10s: (x%i) | %1.0f | %1.0f \n", 
            data[i].name, i+1, nearArrV[i], nearArrM[i]);
    }

    /* Линейный индекс нечеткости */
    printf("\n-------------------- Linear Fuzzy Index --------------------\n\n"); 
    linearFuzzyIndexV = LinearFuzzyIndex(memberArrV, nearArrV);
    linearFuzzyIndexM = LinearFuzzyIndex(memberArrM, nearArrM);
    printf("  Capacity: %5.3f\n", linearFuzzyIndexV); 
    printf("  Mass: %5.3f\n", linearFuzzyIndexM);

    /* Квадратичный индекс нечеткости */
    printf("\n-------------------- Quadro Fuzzy Index --------------------\n\n"); 
    quadroFuzzyIndexV = QuadroFuzzyIndex(memberArrV, nearArrV);
    quadroFuzzyIndexM = QuadroFuzzyIndex(memberArrM, nearArrM);
    printf("  Capacity: %5.3f\n", quadroFuzzyIndexV); 
    printf("  Mass: %5.3f\n", quadroFuzzyIndexM);

    /* Мера нечеткости Егера */
    printf("\n-------------------- Eger Fuzzy Measure --------------------\n\n"); 
    fuzOneV = FUZone(memberArrV), fuzTwoV = FUZtwo(memberArrV);
    fuzOneM = FUZone(memberArrM), fuzTwoM = FUZtwo(memberArrM);
    printf("  p = 1:\n");
    printf("  Capacity: %5.3f\n", fuzOneV);
    printf("  Mass: %5.3f\n\n", fuzOneM);
    printf("  p = 2:\n");
    printf("  Capacity: %5.3f\n", fuzTwoV);
    printf("  Mass: %5.3f\n", fuzTwoM);

    /* Мера нечеткости Коско */
    printf("\n-------------------- Kosko Fuzzy Measure --------------------\n\n"); 
    koskoV = Kosko(memberArrV);
    koskoM = Kosko(memberArrM);
    printf("  Capacity: %5.3f\n", koskoV);
    printf("  Mass: %5.3f\n", koskoM);

    /* Пересечение | MIN */
    printf("\n-------------------- Intersection --------------------\n\n"); 
    Intersection(memberArrV, memberArrM, intersectionArr);
    for (int i = 0; i < arrLength; i++) {
        printf("  (x%i) | %5.3f \n", i+1, intersectionArr[i]);
    }

    /* Объединение | MAX */
    printf("\n-------------------- Union --------------------\n\n"); 
    Union(memberArrV, memberArrM, unionArr);
    for (int i = 0; i < arrLength; i++) {
        printf("  (x%i) | %5.3f \n", i+1, unionArr[i]);
    }

    /* Разность V от M */
    printf("\n-------------------- Difference V - M --------------------\n\n"); 
    Difference(memberArrV, memberArrM, differenceArr_VM);
    for (int i = 0; i < arrLength; i++) {
        printf("  (x%i) | %5.3f \n", i+1, differenceArr_VM[i]);
    }

    /* Разность M от V */
    printf("\n-------------------- Difference M - V --------------------\n\n"); 
    Difference(memberArrM, memberArrV, differenceArr_MV);
    for (int i = 0; i < arrLength; i++) {
        printf("  (x%i) | %5.3f \n", i+1, differenceArr_MV[i]);
    }

    /* Ограниченная Сумма */
    printf("\n-------------------- Limited Amount --------------------\n\n"); 
    LimitedAmount(memberArrV, memberArrM, limitedAmountArr);
    for (int i = 0; i < arrLength; i++) {
        printf("  (x%i) | %5.3f \n", i+1, limitedAmountArr[i]);
    }

    /* Алгебраическое произведение */
    printf("\n-------------------- Multiplication --------------------\n\n"); 
    Multiplication(memberArrV, memberArrM, multiplicationArr);
    for (int i = 0; i < arrLength; i++) {
        printf("  (x%i) | %5.3f \n", i+1, multiplicationArr[i]);
    }

    /* Сравнение нечетких множеств */
    printf("\n-------------------- Comparison of sets --------------------\n\n"); 
    compFlag = Comparison(memberArrV, memberArrM);
    if (compFlag == _compXinY) compStr = "Set V(capacity) is contained in set M(mass).";
    else if (compFlag == _compYinX) compStr = "Set M(mass) is contained in set V(capacity).";
    else if (compFlag == _compEqual) compStr = "Sets are equal.";
    else compStr = "Nothing.";
    printf("  %s\n", compStr);
}