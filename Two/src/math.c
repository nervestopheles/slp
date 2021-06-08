/*
    Просчет значений принадлежащих к нечеткому
    множеству "производительность печей Y которая
    существенно больше чем производительность печей X"
*/
void GetPerformanceMembership(float min, float max, int length,
    float src[length][length], float res[length][length])
{
    float mid = (min+max) / 2;

    for (int i = 0; i < length; i++) {
        for(int j = 0; j < length; j++) {
            if (src[i][j] <= min) res[i][j] = 0;
            else if (src[i][j] > min && src[i][j] <= mid)
                res[i][j] = 2.0*((src[i][j]-min)/\
                    (max-min))*((src[i][j]-min)/(max-min));
            else if (src[i][j] > mid && src[i][j] < max)
                res[i][j] = 1.0-2.0*((src[i][j]-max)/\
                    (max-min))*((src[i][j]-max)/(max-min));
            else res[i][j] = 1.0;
        }
    }
}

/*
    Просчет значений принадлежащих к нечеткому
    множеству "примерно одинаковые объемы печных каналов X и Y"
*/
void GetVolumeMembership(float min, float max, int length,
    float src[length][length], float res[length][length])
{
    float mid = (min+max) / 2;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (fabs(src[i][j]) <= min) res[i][j] = 1.0;
            else if (fabs(src[i][j]) > min && fabs(src[i][j]) <= mid)
                res[i][j] = 1.0+2.0*((fabs(src[i][j])-max)/\
                    (max-min))*((fabs(src[i][j])-min)/(max-min));
            else if (fabs(src[i][j]) > mid && fabs(src[i][j]) < max)
                res[i][j] = fabs(2.0*((fabs(src[i][j])-min)/\
                    (max-min))*((fabs(src[i][j])-max)/(max-min)));
            else res[i][j] = 0;
        }
    }
}

char * GetReflectiveStatus(int count, float array[count][count])
{
    char check;

    check = 0;
    for (int i = 0; i < count && array[i][i] == 1; i++)
        check++;
    if (check == count) return REFLECTIVE;

    check = 0;
    for (int i = 0; i < count && array[i][i] == 0; i++)
        check++;
    if (check == count) return ANTIREFLECTIVE;

    return NON_REFLECTIVE;
}

char * GetSymmetricStatus(int count, float array[count][count])
{
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            if (array[i][j] == array[j][i]) {}
            else return NON_SYMMETRIC;
    return SYMMETRIC;
}

float Min(float x, float y) { return (x < y) ? x : y; }

char * GetTransitiveStatus(int count, float array[count][count])
{
    float buf;
    float tmp[count];

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            for (int k = 0; k < count; k++) {
                tmp[k] = Min(array[i][k], array[k][j]);
            }
            buf = tmp[0];
            for (int i = 1; i < count; i++) {
                if (buf < tmp[i]) buf = tmp[i];
            }
            if (array[i][j] < buf) return NON_TRANSITIVE;
        }
    }
    return TRANSITIVE;
}

void UpdateProperties(int count,
    float src[count][count], struct Properties *res)
{
    res->ref_status = GetReflectiveStatus(count, src);
    res->sym_status = GetSymmetricStatus(count, src);
    res->trs_status = GetTransitiveStatus(count, src);
}

void GetPerforanceFurnaceStat(float array[furnace_count])
{
    for (int i = 0; i < furnace_count; i++) {
        array[i] = furnace[i].performance;
    }
}

void GetVolumeFurnaceStat(float array[furnace_count])
{
    for (int i = 0; i < furnace_count; i++) {
        array[i] = furnace[i].volume;
    }
}

void GetPerformanceFurnaceDiff(int count, float array[count][count])
{
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            array[i][j] = furnace[j].performance - furnace[i].performance;
}

void GetVolumeFurnaceDiff(int count, float array[count][count])
{
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            array[i][j] = furnace[j].volume - furnace[i].volume;
}

void SquarArrayZeroing(int count, float array[count][count])
{
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count; j++)
            array[i][j] = 0;
}

void PrintingSquarArray(int count, float array[count][count])
{
    printf("%9c", ' ');
    for (int i = 0; i < count; i++)
        printf("x%i%9c", i, ' ');
    printf("\n");

    for (int i = 0; i < count; i++) {
        printf("x%i: ", i);
        for (int j = 0; j < count; j++) {
            printf("%10.5f ", array[i][j]);
        }
        printf("\n");
    }
}
