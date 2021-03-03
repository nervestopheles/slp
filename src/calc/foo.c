const int arrLength = 7;

struct obj 
{
    char *name;
    double V;
    double M;
};

struct obj Data[] = {
    { "K/SQ 2"   , 0.3  , 110   }, 
    { "K/SQ 3"   , 0.9  , 200   }, 
    { "K/SQ 5"   , 4.5  , 380   }, 
    { "CM-243 V" , 4    , 550   }, 
    { "CM-489 B" , 8    , 1220  }, 
    { "K/SQ 7"   , 13.5 , 1230  }, 
    { "K/SQ 10"  , 38   , 2700  }
};

double membership(double x,
    double min, double mid, double max, char choice)
{
    if (choice) {
        if (x <= min) return 0;
        else if (x > min && x <= mid) 
            return 2.0*((x-min)/(max-min))*((x-min)/(max-min));
        else if (x > mid && x <  max) 
            return 1.0-2.0*((x-max)/(max-min))*((x-max)/(max-min));
        else return 1.0;
    } else {
        if (x <= min) return 1.0;
        else if (x > min && x <= mid) return 1.0+2.0*((x-max)/(max-min))*((x-min)/(max-min));
        else if (x > mid && x <  max) return 2.0*((x-min)/(max-min))*((x-max)/(max-min));
        else return 0;
    }
    return -1;
}

double complement(double x) 
{ 
    return 1-x; 
}

double multiplication(double x, double y) 
{ 
    return x*y; 
}

double LimitedAmount(double x, double y)
{
    if (x+y > 1) return 1;
    else return x+y;
    return -1; /* Error? */
}

double intersection(double x, double y) {
    if (x > y) return y;
    else return x;
    return -1; /* Error? */ 
}

double Union(double x, double y) {
    if (x > y) return x;
    else return y;
    return -1; /* Error? */ 
}

double difference(double x, double y) 
{ 
    return intersection(x, complement(y)); 
}

double* CartesianProduct(double arrX[], double arrY[])
{
    double *cartesianProductArr = malloc(sizeof(double)*arrLength*arrLength);
    int step = 0;
    for (int i = 0; i < arrLength; i++) {
        for (int j = 0; j < arrLength; j++) {
            *(cartesianProductArr+step) = arrX[i] * arrY[j];
            step++;
        }
    }
    return cartesianProductArr;
}

