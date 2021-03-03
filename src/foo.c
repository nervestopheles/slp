double Membership(double x, 
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
        else if (x > min && x <= mid) 
            return 1.0+2.0*((x-max)/(max-min))*((x-min)/(max-min));
        else if (x > mid && x <  max) 
            return 2.0*((x-min)/(max-min))*((x-max)/(max-min));
        else return 0;
    }
    return -1;
}

double Complement(double x) 
{ 
    return 1-x; 
}

double Multiplication(double x, double y) 
{ 
    return x*y; 
}

double LimitedAmount(double x, double y)
{
    if (x+y > 1) return 1;
    else return x+y;
}

double Intersection(double x, double y) 
{
    if (x > y) return y;
    else return x;
}

double Union(double x, double y) 
{
    if (x > y) return x;
    else return y;
}

double Difference(double x, double y) 
{ 
    return Intersection(x, Complement(y)); 
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

