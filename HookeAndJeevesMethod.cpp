#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double objectiveFunction(vector < vector<double> > &data, int n, int m);
void research(vector < vector<double> > &data, double step, int n);

void main()
{
	setlocale(LC_ALL,"Russian");

	int n;

	cout << "Введите количество координат: ";
	cin >> n;
	n++;	// One cell for value of function 

	vector< vector< double > > data(3, n);

	int i,j;
	cout << "Введите координаты точки: ";
	for(j=0; j<n-1; j++) {
		cin >> data[0][j];
		data[1][j]=data[0][j];
	}

	double step;
	cout << "Введите шаг: ";
	cin >> step;

	double contraction;
	cout << "Введите коэффициент уменьшение шага: ";
	cin >> contraction;

	double expansion;
	cout << "Введите коэффициент растяжения: ";
	cin >> expansion;

	double precision;
	cout << "Введите точность: ";
	cin >> precision;

	for(i=0; step > precision; i++) {
		research(data, step, n);
		if(data[0][n-1] <= data[1][n-1]) step=step * contraction;
		else {
			while(true) {
				for(j=0; j<n; j++) {
					data[2][j]=data[1][j];
					data[0][j]=data[0][j] + expansion * (data[1][j] - data[0][j]);
				}

				research(data, step, n);
				if(data[2][n-1] <= data[1][n-1]) {
					for(j=0; j<n-1; j++) {
						data[0][j]=data[2][j];
					}
					break;
				}
			}
		}
	}

	cout << "\nРешение\nКоличество итераций: " << i << endl;
	for(j=0; j<n-1; j++) {
		cout << "\nКоордината " << j << ": "  << data[0][j];
	}
	cout << "\nЗначение функции: " << data[0][n-1] << endl;
}

void research(vector < vector<double> > &data, double step, int n)
{
	int j;
	double newValue;

	data[0][n-1]=objectiveFunction(data, n, 0);
	for(j=0; j<n; j++) {
		data[1][j]=data[0][j];
	}

	for(j=0; j<n-1; j++) {
		data[1][j]=data[0][j]+step;
		newValue=objectiveFunction(data, n, 1);

		if(newValue < data[1][n-1]) data[1][n-1]=newValue;
		else {
			data[1][j]=data[0][j]-step;
			newValue=objectiveFunction(data, n, 1);

			if(newValue < data[1][n-1]) data[1][n-1]=newValue;
			else data[1][j]=data[0][j];
		}
	}
}

double objectiveFunction(vector < vector<double> > &data, int n, int m)
{
	double result=0;
	for(int j=0; j<n-1; j++) {
		result=result + cos(data[m][j]);
	}
	return result;
}