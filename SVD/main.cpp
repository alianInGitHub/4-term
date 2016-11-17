
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "SVD.h"

using namespace std;


void findSystemSolution(vector<vector<double>> &Array, vector<double> &E, vector<vector<double>> &V, vector<double> &B)
{
	SVD::transpose(V);
	vector<vector<double>> new_E(E.size());
	for (int i = 0; i < E.size(); i++)
	{
		new_E[i].resize(E.size());
		for (int j = 0; j < E.size(); j++)
		{
			if (j == i)
			{
				new_E[i][j] = sqrt(E[j]);
			}
			else
				new_E[i][j] = 0;
		}
	}

	cout << endl << "Result :" << endl;
	// Formula: X = V * new_E * U_trans * B
	// B are our values in the equalcy A * X = B

	// 1) multiply  V * new_E
	vector<vector<double>> temp_array(E.size());
	for (int i = 0; i < E.size(); i++)
	{
		temp_array[i].resize(E.size());
		for (int j = 0; j < E.size(); j++)
		{
			temp_array[i][j] = SVD::multiply(V[i], new_E[j]);
		}

	}
	// 2) multiply temp_array * U_trans
	vector<vector<double>> temp_array_2(E.size());
	for (int i = 0; i < E.size(); i++)
	{
		temp_array_2[i].resize(E.size());
		for (int j = 0; j < E.size(); j++)
		{
			temp_array_2[i][j] = SVD::multiply(temp_array[i], Array[j]);
		}
	}
	// 3) result = temp_array_2 * B
	for (int i = 0; i < E.size(); i++)
	{
		cout << SVD::multiply(temp_array_2[i], B) << endl;
	}
}


int main(void) 
{
	int size;
	cout << "n = ";
	cin >> size;
	vector<vector<double>> Array(size);	//input & right singular valuas
	vector<double> E(size);				// singular values
	vector<vector<double>> V(size);		// left singular vectors

	vector<double> B(size); // AX = B - the system 

	//initialisation
	cout << "Write matrix:" << endl;
    for(int i = 0; i < size; i++)
    {
		Array[i].resize(size);
		V[i].resize(size);
        for(int j = 0; j < size; j++)
        {
            cin >> Array[i][j];
            V[i][j] = 0;
        }
        E[i] = 0;
    }
	
	//finding and printing svd
	SVD::svd(Array, E, V);
		cout << endl << "---------------------------" << endl;
    SVD::writeMatrix(Array);
	SVD::writeVector(E);
	SVD::writeMatrix(V);
    cout << endl;
	cout << endl << "---------------------------" << endl << endl;


	cout << "Write values of matrix B:" << endl;
	for(int i = 0; i < size; i++)
	{
		cin >> B[i];
	}
	
	findSystemSolution(Array, E, V, B);

	system("pause");

    return 0;
}
