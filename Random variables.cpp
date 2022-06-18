#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

double EPS = 0.0001;

bool equal(double v1, double v2) {
    	return ((v1 - EPS < v2) && (v1 + EPS > v2));
}

class RandomVariable {
    	vector<pair<double, double>> values;

public:
    	RandomVariable(vector<pair<double, double>> inputValues = {})
        {
            double proverka = 0;
            this->values = inputValues;
            for(int i = 0; i < values.size(); i++)
            {
                proverka += values[i].second;
            }
            if(proverka != 1)
            {
                throw (proverka);
            }
        }
    	//double math_ochakvane = 0;
    	//double disperziya = 0;
    	//double standartno_otklonenie = 0;


    double mean() const {

        double math_ochakvane = 0;
        for(int i = 0; i < values.size(); i++) {
                pair<double, double> p = this->values[i]; // dostupvane na elementi ot vector
                math_ochakvane += p.first * p.second;
        }
        return math_ochakvane;
    }

	double variance() const {

		double disperziya = 0;
		double math_ochakvane = mean();
		for(int i = 0; i < values.size(); i++) {
            		pair<double, double> p = this->values[i]; // dostupvane na elementi ot vector
            		disperziya += (p.first - math_ochakvane)*(p.first - math_ochakvane)*p.second;
        }
        return disperziya;
   	}

    double standardDeviation() const {
        double standartno_otklonenie = 0;
        double disperziya = variance();
        standartno_otklonenie += sqrt(disperziya);
        return standartno_otklonenie;
        
    }

    void print() {
        cout<< values.size()<< endl;
        for(int i = 0; i < values.size(); ++i) {
                cout<< "("<< values[i].first<< ", "<< values[i].second<< ") ";
        }
        cout<< endl;
    }
};

double binomialDensity(int n, int k, double p) {
    double w = 1;   //neutral element of multiplication

    // n choose k part
    for (int i = n - k + 1;i <= n; ++i) w = w * i;
    for (int i = 1; i <= k; ++i) w = w / i;

    // p^k * (1-p)^(n-k) part
    w = w * pow(p, k) * pow(1.0 - p, n - k);

    return w;
}

/*RandomVariable binomialRandomVariable(int n, double p) {

	return RandomVariable();
}*/
RandomVariable binomialRandomVariable(int n, double p)
{
    RandomVariable rv(vector<pair<double, double>>({
    						{n * p, pow(p, n)}
    						}));
    return rv;
}

double binomialRandom(int n, double p) {
	return 0;
}

int main() {
    std::srand(std::time(nullptr));
    RandomVariable* rv;
    try
    {

        rv = new RandomVariable(vector<pair<double, double>>({
            {0, 0.5},
            {1, 0.5},
        }));
    }
    catch(double myNum)
    {
        cout<< "Pairut ti trqbva da se symira do 1\n";
        cout << "Tvoqt e = " << myNum;
        return 0;
    }
    rv->print();

    cout<< rv->mean()<< " "<< rv->variance()<< endl;
    cout<< binomialDensity(3, 2, 0.5)<< endl;

	try{
    		RandomVariable b(binomialRandomVariable(3, 0.5));
    		b.print();
    	}catch(double myNum){}

    cout<< binomialRandom(200, 0.5);

    return 0;
}