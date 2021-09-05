#include <memory>
#include <stdexcept>
#include <vector>
#include "p0_starter.cpp"
#include <iostream>
#include <iomanip>
using namespace std;

void testAdd()
{
	cout << "----------test add----------" << endl;
	RowMatrix<int> matrix1(2, 3);
	vector<int> s1(6, 1);
	matrix1.FillFrom(s1);

	cout << "First matrix :" << endl;
	for (int i = 0; i < matrix1.GetRowCount(); i++)
	{
		for (int j = 0; j < matrix1.GetColumnCount(); j++)
		{
			cout << setw(3) << matrix1.GetElement(i, j);
		}
		cout << endl;
	}

	RowMatrix<int> matrix2(2, 3);
	vector<int> s2(6, 2);
	matrix2.FillFrom(s2);

	cout << "Second matrix :" << endl;
	for (int i = 0; i < matrix2.GetRowCount(); i++)
	{
		for (int j = 0; j < matrix2.GetColumnCount(); j++)
		{
			cout << setw(3) << matrix2.GetElement(i, j);
		}
		cout << endl;
	}

	RowMatrixOperations<int> rmop;
	std::unique_ptr<RowMatrix<int>> matrix3 = rmop.Add(&matrix1, &matrix2);

	cout << "the result of Add:" << endl;
	for (int i = 0; i < matrix3->GetRowCount(); i++)
	{
		for (int j = 0; j < matrix3->GetColumnCount(); j++)
		{
			cout << setw(3) << matrix3->GetElement(i, j);
		}
		cout << endl;
	}
}

void testMul()
{
	cout << "----------test multiply----------" << endl;
	RowMatrix<int> matrix1(2, 3);
	vector<int> s1(6, 1);
	matrix1.FillFrom(s1);

	cout << "First matrix :" << endl;
	for (int i = 0; i < matrix1.GetRowCount(); i++)
	{
		for (int j = 0; j < matrix1.GetColumnCount(); j++)
		{
			cout << setw(3) << matrix1.GetElement(i, j);
		}
		cout << endl;
	}

	RowMatrix<int> matrix2(3, 2);
	vector<int> s2(6, 2);
	matrix2.FillFrom(s2);

	cout << "Second matrix :" << endl;
	for (int i = 0; i < matrix2.GetRowCount(); i++)
	{
		for (int j = 0; j < matrix2.GetColumnCount(); j++)
		{
			cout << setw(3) << matrix2.GetElement(i, j);
		}
		cout << endl;
	}

	RowMatrixOperations<int> rmop;
	std::unique_ptr<RowMatrix<int>> matrix3 = rmop.Multiply(&matrix1, &matrix2);

	cout << "the result of multiply :" << endl;
	for (int i = 0; i < matrix3->GetRowCount(); i++)
	{
		for (int j = 0; j < matrix3->GetColumnCount(); j++)
		{
			cout << setw(3) << matrix3->GetElement(i, j);
		}
		cout << endl;
	}
}

void testGEMM()
{
	cout << "----------test GEMM----------" << endl;
	RowMatrix<int> matrix1(2, 2);
	vector<int> s1(6, 1);
	matrix1.FillFrom(s1);

	cout << "First matrix :" << endl;
	for (int i = 0; i < matrix1.GetRowCount(); i++)
	{
		for (int j = 0; j < matrix1.GetColumnCount(); j++)
		{
			cout << setw(3) << matrix1.GetElement(i, j);
		}
		cout << endl;
	}

	RowMatrix<int> matrix2(2, 2);
	vector<int> s2(6, 2);
	matrix2.FillFrom(s2);

	cout << "Second matrix :" << endl;
	for (int i = 0; i < matrix2.GetRowCount(); i++)
	{
		for (int j = 0; j < matrix2.GetColumnCount(); j++)
		{
			cout << setw(3) << matrix2.GetElement(i, j);
		}
		cout << endl;
	}

	RowMatrix<int> matrix4(2, 2);
	vector<int> s3(6, 3);
	matrix4.FillFrom(s3);

	cout << "Third matrix :" << endl;
	for (int i = 0; i < matrix4.GetRowCount(); i++)
	{
		for (int j = 0; j < matrix4.GetColumnCount(); j++)
		{
			cout << setw(3) << matrix4.GetElement(i, j);
		}
		cout << endl;
	}

	RowMatrixOperations<int> rmop;
	std::unique_ptr<RowMatrix<int>> matrix3 = rmop.GEMM(&matrix1, &matrix2, &matrix4);

	cout << "the result of GEMM :" << endl;
	for (int i = 0; i < matrix3->GetRowCount(); i++)
	{
		for (int j = 0; j < matrix3->GetColumnCount(); j++)
		{
			cout << setw(3) << matrix3->GetElement(i, j);
		}
		cout << endl;
	}
}
int main()
{
	testAdd();

	testMul();

	testGEMM();

	return 0;
}