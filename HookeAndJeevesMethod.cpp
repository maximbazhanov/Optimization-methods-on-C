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

	cout << "Enter number of coordinates: ";
	cin >> n;
	n++;	// One cell for value of function 

	vector< vector< double > > data(3, n);

	int i,j;
	cout << "Enter begin coordinates: ";
	for(j=0; j<n-1; j++) {
		cin >> data[0][j];
		data[1][j]=data[0][j];
	}

	double step;
	cout << "Enter step: ";
	cin >> step;

	double contraction;
	cout << "Enter contraction rate: ";
	cin >> contraction;

	double expansion;
	cout << "Enter expansion rate: ";
	cin >> expansion;

	double precision;
	cout << "Enter precision: ";
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

	cout << "\nSolution\nIterations: " << i << endl;
	for(j=0; j<n-1; j++) {
		cout << "\nCoordinate " << j << ": "  << data[0][j];
	}
	cout << "\nFunction value: " << data[0][n-1] << endl;
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