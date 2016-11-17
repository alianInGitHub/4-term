#include <vector>
#include <iostream>
#include <math.h>

using namespace std;
namespace SVD
{
	void svd(vector<vector<double>> &rightSingularVectors, vector<double> &singularValues, vector<vector<double>> &leftSingularVectors);

	// and other useful functions 

	void writeMatrix(vector<vector<double>> mas);

	void writeVector(vector<double> v);

	double multiply(vector<double> A, vector<double> B);

	double multiply(double a, vector<double> B);

	void transpose(vector<vector<double>> mas);
}

