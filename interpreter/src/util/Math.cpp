
double PI = 3.141592653589793;

double modulus (double x, double y){
    double r = x < 0 ? -x : x;
    while (r >= y) r = r - y;
    if(x < 0) return -r;
    return r;
}