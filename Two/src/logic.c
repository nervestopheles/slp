void PrintingSquarArray(int count, int array[count][count])
{
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            printf("%6i", array[i][j]);
        }
        printf("\n");
    }
}

void SquarArrayZeroing(int count, int array[count][count])
{
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            array[i][j] = 0;
}

void GetPerformanceDiff(int count, int array[count][count])
{
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            array[i][j] = furnace[j].performance - furnace[i].performance;
}

void GetVolumeDiff(int count, int array[count][count])
{
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            array[i][j] = furnace[j].volume - furnace[i].volume;
}