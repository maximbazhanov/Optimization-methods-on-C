#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

template <class type1> void vectorInput(vector< type1 > &a)
{
	int i;

	for(i = 0; i < (int) a.size(); i++) {
		cin >> a[i];
	}
}

template <class type1> void vectorOutput(vector< vector< type1 >> &a)
{
	int i, j;

	for(i = 0; i < (int) a.size(); i++) {
		for(j = 0; j < (int) a.size(); j++) {
			cout << setw(8) << a[i][j] << "  ";
		}
		cout << endl;
	}
}

template <class type1> void nelderAndMeadMethod(vector< type1 > &a, type1 length)
{
	unsigned int i, j, n;
	n = a.size();
	vector< vector< type1 >> data(n + 1, n + 1);

	// В первой строке нового массива — координаты начальной точки
	for(j = 0; j < n; j++) {
		data[0][j] = a[j];
	}

	// Расчет координат симплекса
	for(i = 1; i < (int) data.size(); i++) {
		for(j = 0; j < n; j++) {
			if(i - 1 == j) {
				data[i][j] = data[0][j] + (length * sqrt(n - 1.0) + n - 1.0) / n * sqrt(2.0);
			}
			else {
				data[i][j] = data[0][j] + (length * sqrt(n - 1.0) - 1.0) / n * sqrt(2.0);
			}
		}
	}
	
	for(i = 0; i < (int) data.size(); i++) {
		objFunction(data, i);
	}

	vectorOutput(data);
	cout << endl;
	Sort(data);
	vectorOutput(data);	
}

template <class type1> void objFunction(vector< vector< type1 >> &a, int i)
{
	int j;
	int n = a.size() - 1;
	a[i][n] = 0;
	for(j = 0; j < n; j++) {
		a[i][n] = a[i][n] + cos(a[i][j]);
	}
}

template <class type1> void Sort(vector< vector< type1 >> &a)
{
	int i, j;
	int n = a.size() - 1;
	for(i = 0; i < (int) a.size(); i++) {
		for(j = i + 1; j < (int) a.size(); j++) {
			if(a[i][n] < a[j][n]) {
				swap(a[i], a[j]);
			}
		}
	}
}

void main()
{
	vector< double > a(4);
	cout << "Enter the begin point: ";
	vectorInput(a);
	double length;

	cout << "Edge length: ";
	cin >> length;
	cout << endl;

	nelderAndMeadMethod(a, length);
}