#include "SVD.h"


using namespace std;

//used to culculate with appropriate accuracy
#define eps 5

//returns the number a with a sign of b
double sign(double a, double b)
{
	return ((b) > 0.0 ? fabs(a) : -fabs(a));
}

template <typename type>

type max(type a, type b)
{
	return (a > b) ? a : b;
}

template <typename type>

type min(type a, type b)
{
	return (a < b) ? a : b;
}


// calculates sqrt( a^2 + b^2 )
double length(double a, double b) 
{
	return sqrtf(a * a + b * b);
}

namespace SVD
{


	//...........................................................................................................
	//...........................................................................................................
	//		INPUT
	//			rightSingularVectors = input matrix which svd we are culculating
	//			singularValues		 = null - vector
	//			leftSingularVectors  = E - identity matrix
	//
	//		OUTPUT
	//			rightSingularVectors
	//			singularValues
	//			leftSingularVectors TRANSPOSED
	//.............................................................................................................
	//...........................................................................................................*/

	void svd(vector<vector<double>> &rightSingularVectors, vector<double> &singularValues, vector<vector<double>> &leftSingularVectors)
	{
		double* temp = new double[singularValues.size()];

		double s;
		unsigned int l;
		double rowSum = 0.0;
		double newRowSum = 0.0;
		double diagonalElement;
		double signedRowSum = 0.0;

		// method of QR iterations
		// on exit we have the right triangular matrix (R) of decomtosition A = QR
		// which is used to find singular values and vectors

		// 1 PARAGRAPH 
		// Householder reduction to bidiagonal form

		for (unsigned i = 0; i < singularValues.size(); i++)
		{
			// for sum from l to n
			l = i + 1;
			// temp[0] = 0;
			temp[i] = rowSum * signedRowSum;
			signedRowSum = newRowSum = rowSum = 0.0;
			// sum all absolute values in the current row
			for (unsigned k = i; k < singularValues.size(); k++)
				rowSum += fabs(rightSingularVectors[k][i]);
			//if it's not null
			if (rowSum)
			{
				for (unsigned k = i; k < singularValues.size(); k++)
				{
					//devide every value by row element's sum
					rightSingularVectors[k][i] /= rowSum;
					//add to new rowSum square of new element
					newRowSum += rightSingularVectors[k][i] * rightSingularVectors[k][i];
				}
				// take the diaganal element in the row
				diagonalElement = rightSingularVectors[i][i];
				// and give the new sum sign of diagonal element
				signedRowSum = -sign(sqrt(newRowSum), diagonalElement);
				// abs(diagonalelement * newsum) - sum
				double h = diagonalElement * signedRowSum - newRowSum;
				//new diagonalelement = diagonalelement - newsum
				rightSingularVectors[i][i] -= signedRowSum;
				//take a minor of rightSingularVectors[i][i]
				for (unsigned j = l; j < singularValues.size(); j++)
				{
					newRowSum = 0.0;
					// culculate newsum for every row below
					for (unsigned k = i; k < singularValues.size(); k++)
						newRowSum += rightSingularVectors[k][i] * rightSingularVectors[k][j];
					diagonalElement = newRowSum / h;
					// reculculate values in current row
					for (unsigned k = i; k < singularValues.size(); k++)
						rightSingularVectors[k][j] += diagonalElement * rightSingularVectors[k][i];
				}

				for (unsigned k = i; k < singularValues.size(); k++)
					rightSingularVectors[k][i] *= rowSum;
			}
			//save composition of sums into array 
			singularValues[i] = rowSum * signedRowSum;

			//repeate steps if i is not the last column number
			signedRowSum = newRowSum = rowSum = 0.0;
			if (i < singularValues.size() && i != singularValues.size() - 1)
			{
				for (unsigned k = l; k < singularValues.size(); k++)
					rowSum += fabs(rightSingularVectors[i][k]);
				if (rowSum)
				{
					for (unsigned k = l; k < singularValues.size(); k++)
					{
						rightSingularVectors[i][k] /= rowSum;
						newRowSum += rightSingularVectors[i][k] * rightSingularVectors[i][k];
					}
					diagonalElement = rightSingularVectors[i][l];
					signedRowSum = -sign(sqrt(newRowSum), diagonalElement);
					double h = diagonalElement * signedRowSum - newRowSum;
					rightSingularVectors[i][l] = diagonalElement - signedRowSum;
					for (unsigned k = l; k < singularValues.size(); k++)
						temp[k] = rightSingularVectors[i][k] / h;
					for (unsigned j = l; j < singularValues.size(); j++)
					{
						newRowSum = 0.0;
						for (unsigned k = l; k < singularValues.size(); k++)
							newRowSum += rightSingularVectors[j][k] * rightSingularVectors[i][k];
						for (unsigned k = l; k < singularValues.size(); k++)
							rightSingularVectors[j][k] += newRowSum * temp[k];
					}
					for (unsigned k = l; k < singularValues.size(); k++)
						rightSingularVectors[i][k] *= rowSum;
				}
			}
		}


		// 2 PARAGRAPH 
		//Accumulation of right-hand transformations
		for (unsigned i = singularValues.size() - 1; i >= 0; i--)
		{
			if (i < singularValues.size() - 1)
			{
				if (signedRowSum != 0)
				{
					for (unsigned j = l; j < singularValues.size(); j++)
						leftSingularVectors[j][i] = (rightSingularVectors[i][j] / rightSingularVectors[i][l]) / signedRowSum;

					for (unsigned j = l; j < singularValues.size(); j++)
					{
						newRowSum = 0.0;
						for (unsigned k = l; k < singularValues.size(); k++)
							newRowSum += rightSingularVectors[i][k] * leftSingularVectors[k][j];

						for (unsigned k = l; k < singularValues.size(); k++)
							leftSingularVectors[k][j] += newRowSum * leftSingularVectors[k][i];
					}
				}
				for (unsigned j = l; j < singularValues.size(); j++)
					leftSingularVectors[i][j] = leftSingularVectors[j][i] = 0.0;
			}
			leftSingularVectors[i][i] = 1.0;
			signedRowSum = temp[i];
			l = i;
		}

		// 3 PARAGRAPH 
		//Accumulation of left-hand transformations

		double tempSumParameter;
		for (unsigned i = min(singularValues.size(), singularValues.size()) - 1; i >= 0; i--)
		{
			l = i + 1;
			// singularVales now is temporaly array which possess the values of 
			// sum compositions ( look in paragraph 1)
			signedRowSum = singularValues[i];
			for (unsigned j = l; j < singularValues.size(); j++)
				rightSingularVectors[i][j] = 0.0;
			// if signedRowSum != 0
			if (signedRowSum)
			{
				signedRowSum = 1.0 / signedRowSum;
				for (unsigned j = l; j < singularValues.size(); j++)
				{
					newRowSum = 0.0;
					for (unsigned k = l; k < singularValues.size(); k++)
						newRowSum += rightSingularVectors[k][i] * rightSingularVectors[k][j];
					tempSumParameter = (newRowSum / rightSingularVectors[i][i]) * signedRowSum;
					for (unsigned k = i; k < singularValues.size(); k++)
						rightSingularVectors[k][j] += tempSumParameter * rightSingularVectors[k][i];
				}
				for (unsigned j = i; j < singularValues.size(); j++)
					rightSingularVectors[j][i] *= signedRowSum;
			}
			else
				for (unsigned j = i; j < singularValues.size(); j++)
					rightSingularVectors[j][i] = 0.0;
			++rightSingularVectors[i][i];
		}

		// 4 PARAGRATH
		//Diagonalization of the bidiagonal form: Loop over
		//singularÌalues, and over allowed iterations
		for (unsigned k = singularValues.size() - 1; k >= 0; k--)
		{
			// limit is 29 itterations - unless the svd is impossible
			for (unsigned its = 0; its < 30; its++)
			{
				bool flag = 1;
				unsigned nm = l - 1;
				for (l = k; l >= 0; l--)
				{							 //Test for splitting
					nm = l - 1;             // temp[1] is always zero
					if (temp[l] == 0.0)
					{
						flag = 0;
						break;
					}
					if (singularValues[nm] == 0.0)
						break;
				}
				double c = 0.0;

				//if all elements exept the first are not zero
				if (flag)
				{
					c = 0.0;
					// cancellation of temp[l], if l > 1.
					s = 1.0;
					// l equals the number of the first zero element in singularValues or int temp array
					for (unsigned i = l; i <= k; i++)
					{
						tempSumParameter = s * temp[i];
						temp[i] = c * temp[i];
						if (tempSumParameter == 0.0)
							break;
						signedRowSum = singularValues[i];
						double converseTempSumParameter = length(tempSumParameter, signedRowSum);

						singularValues[i] = converseTempSumParameter;

						//converse
						converseTempSumParameter = 1.0 / converseTempSumParameter;

						c = signedRowSum * converseTempSumParameter;
						s = -tempSumParameter * converseTempSumParameter;

						//according to formula
						for (unsigned j = 0; j < singularValues.size(); j++)
						{
							double y = rightSingularVectors[j][nm];
							double z = rightSingularVectors[j][i];
							rightSingularVectors[j][nm] = y * c + z * s;
							rightSingularVectors[j][i] = z * c - y * s;
						}
					}
				}

				double z = singularValues[k];
				if (l == k)
				{
					//convergence
					if (z < 0.0)
					{
						singularValues[k] = -z;
						for (unsigned j = 0; j < singularValues.size(); j++)
							leftSingularVectors[j][k] = -leftSingularVectors[j][k];
					}
					break;
				}
				if (its == 29)
					printf("no convergence in 30 svd iterations\n");
				double x = singularValues[l];           //Shift from bottom 2-by-2 minor
				nm = k - 1;
				double y = singularValues[nm];
				signedRowSum = temp[nm];
				double tempValue = temp[k];
				tempSumParameter = ((y - z) * (y + z) + (signedRowSum - tempValue) * (signedRowSum + tempValue)) / (2.0 * tempValue * y);
				signedRowSum = length(tempSumParameter, 1.0);
				tempSumParameter = ((x - z) * (x + z) + tempValue * ((y / (tempSumParameter + sign(signedRowSum, tempSumParameter))) - tempValue)) / x;
				c = s = 1.0;

				//Further QR transformation
				for (unsigned j = l; j <= nm; j++)
				{
					unsigned i = j + 1;
					signedRowSum = temp[i];
					y = singularValues[i];
					tempValue = s * signedRowSum;
					signedRowSum = c * signedRowSum;
					z = length(tempSumParameter, tempValue);
					temp[j] = z;
					c = tempSumParameter / z;
					s = tempValue / z;
					tempSumParameter = x * c + signedRowSum * s;
					signedRowSum = signedRowSum * c - x * s;
					tempValue = y * s;
					y *= c;
					// according to formula
					for (unsigned jj = 0; jj < singularValues.size(); jj++)
					{
						x = leftSingularVectors[jj][j];
						z = leftSingularVectors[jj][i];
						leftSingularVectors[jj][j] = x * c + z * s;
						leftSingularVectors[jj][i] = z * c - x * s;
					}
					z = length(tempSumParameter, tempValue);

					singularValues[j] = z;
					if (z)
					{
						z = 1.0 / z;
						c = tempSumParameter * z;
						s = tempValue * z;
					}
					tempSumParameter = c * signedRowSum + s * y;
					x = c * y - s * signedRowSum;
					//according to formula
					for (unsigned jj = 0; jj < singularValues.size(); jj++)
					{
						y = rightSingularVectors[jj][j];
						z = rightSingularVectors[jj][i];
						rightSingularVectors[jj][j] = y * c + z * s;
						rightSingularVectors[jj][i] = z * c - y * s;
					}
				}
				temp[l] = 0.0;
				temp[k] = tempSumParameter;
				singularValues[k] = x;
			}
		}
		for (unsigned i = 0; i < singularValues.size(); i++)
			if (singularValues[i] < pow(10, -eps)) singularValues[i] = 0;

	}



	// prints an arbitrary size matrix to the standard output
	void writeMatrix(vector<vector<double>> mas)
	{

		for (int i = 0; i < mas.size(); i++)
		{
			for (int j = 0; j < mas[i].size(); j++)
			{
				cout << mas[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	// prints an arbitrary size vector to the standard output
	void writeVector(vector<double> v)
	{

		for (int i = 0; i < v.size(); i++)
		{
			cout << v[i] << " ";
		}
		cout << endl;
	}


	double multiply(vector<double> A, vector<double> B)
	{
		double res = 0.0;
		for (int i = 0; i < A.size(); i++)
		{
			res += A[i] * B[i];
		}
		return res;
	}

	double multiply(double a, vector<double> B)
	{
		double res = 0;
		for (int i = 0; i < B.size(); i++)
		{
			res += a * B[i];
		}
		return res;
	}

	//transpose square matrix
	void transpose(vector<vector<double>> mas)
	{
		for (int i = 0; i < mas.size(); i++)
			for (int j = i; j < mas[i].size(); j++)
			{
				swap(mas[i][j], mas[j][i]);
			}
	}

}