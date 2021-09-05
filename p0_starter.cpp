#include <iostream>
#include "p0_starter.h"

template <typename T>
class Matrix
{
protected:
	int rows_;
	int cols_;
	T* linear_;
	Matrix(int rows, int cols)
	{
		rows_ = rows;
		cols_ = cols;
		linear_ = new T[rows * cols];
	}

public:
	virtual int GetRowCount() const = 0;
	virtual int GetColumnCount() const = 0;
	virtual T GetElement(int i, int j) const = 0;
	virtual void SetElement(int i, int j, T val) = 0;
	virtual void FillFrom(const std::vector<T>& source) = 0;
	virtual ~Matrix()
	{
		delete[] linear_;
	}
};

template <typename T>
class RowMatrix : public Matrix<T>
{
public:
	RowMatrix(int rows, int cols) : Matrix<T>(rows, cols)
	{
		data_ = new T * [rows];
		for (int i = 0; i < rows; i++)
		{
			data_[i] = &this->linear_[i * cols];
		}
	}

	int GetRowCount() const override
	{
		return this->rows_;
	}

	int GetColumnCount() const override
	{
		return this->cols_;
	}

	T GetElement(int i, int j) const override
	{
		return data_[i][j];
	}

	void SetElement(int i, int j, T val)
	{
		data_[i][j] = val;
	}

	void FillFrom(const std::vector<T>& source) override
	{
		for (int r = 0; r < this->rows_; r++)
		{
			for (int c = 0; c < this->cols_; c++)
			{
				data_[r][c] = source[this->cols_ * r + c];
			}
		}
	}

	~RowMatrix()
	{
		delete[] data_;
	}
private:
	T** data_;
};

template <typename T>
class RowMatrixOperations {
public:
	static std::unique_ptr<RowMatrix<T>> Add(const RowMatrix<T>* matrixA, const RowMatrix<T>* matrixB)
	{
		if (matrixA->GetColumnCount() != matrixB->GetColumnCount() 
			|| matrixA->GetRowCount() != matrixB->GetRowCount())
		{
			return std::unique_ptr<RowMatrix<T>>(nullptr);
		}
		else
		{
			int matrixA_row = matrixA->GetRowCount();
			int matrixB_col = matrixB->GetColumnCount();
			std::unique_ptr<RowMatrix<T>> matrixAdd(new RowMatrix<T>(matrixA_row, matrixB_col));
			for (int i = 0; i < matrixA_row; i++)
			{
				for (int j = 0; j < matrixB_col; j++)
				{
					matrixAdd->SetElement(i, j, matrixA->GetElement(i, j) + matrixB->GetElement(i, j));
				}
			}
			return matrixAdd;
		}
	}

	static std::unique_ptr<RowMatrix<T>> Multiply(const RowMatrix<T>* matrixA, const RowMatrix<T>* matrixB)
	{
		if (matrixA->GetColumnCount() !=  matrixB->GetRowCount())
		{
			return std::unique_ptr<RowMatrix<T>>(nullptr);
		}
		else
		{
			int matrixA_row = matrixA->GetRowCount();
			int matrixB_col = matrixB->GetColumnCount();
			int matrixA_col = matrixA->GetColumnCount();
			std::unique_ptr<RowMatrix<T>> matrixMul(new RowMatrix<T>(matrixA_row, matrixB_col));
			for (int i = 0; i < matrixA_row; i++)
			{
				for (int j = 0; j < matrixB_col; j++)
				{
					T temp = 0;
					for (int k = 0; k < matrixA_col; k++)
					{
						temp += matrixA->GetElement(i, k) * matrixB->GetElement(k, j);
					}
					matrixMul->SetElement(i, j, temp);
				}
			}
			return matrixMul;
		}
	}

	static std::unique_ptr<RowMatrix<T>> GEMM(const RowMatrix<T>* matrixA, const RowMatrix<T>* matrixB,
		const RowMatrix<T>* matrixC)
	{
		if (matrixA->GetColumnCount() != matrixB->GetColumnCount() 
			|| matrixA->GetRowCount() != matrixB->GetRowCount())
		{
			return std::unique_ptr<RowMatrix<T>>(nullptr);
		}
		else
		{
			return Add(Multiply(matrixA, matrixB).get(), matrixC);
		}
	}

};
