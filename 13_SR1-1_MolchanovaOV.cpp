#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Matrix
{
public:
	Matrix()
	{
		_rows = 0;
		_columns = 0;
		_data = nullptr;
	}

	Matrix(size_t rows, size_t columns)
	{
		_rows = rows;
		_columns = columns;
		_data = nullptr;

		size_t total_size = rows * columns * sizeof(double);
		_data = (double*)malloc(total_size);
		if (!_data)
		{
			_rows = 0;
			_columns = 0;
		}
		else
		{
			memset(_data, 0, total_size);
		}
	}

	double element(size_t row, size_t column)
	{
		size_t index = row * _columns + column;
		return _data[index];
	}

	void set_element(size_t row, size_t column, double value)
	{
		size_t index = row * _columns + column ;
		_data[index] = value;
	}

	size_t rows() { return _rows; }

	size_t columns() { return _columns; }

	bool is_valid() { return _data != nullptr; }

	void print()
	{
		if (is_valid())
		{
			for (size_t row = 0; row < _rows; row++)
			{
				for (size_t column = 0; column < _columns; column++)
				{
					cout << element(row, column) << "   ";
				}
				cout << endl;
			}
		}
		else
		{
			cout << "Not valid" << endl;
		}
	}

	vector<double> slice1()
	{
		vector<double> result;
		// 2->1
		for (size_t i = rows(); i > 1; i--)
		{
			result.push_back(element(i, columns() - 1));
		}
		//1->0
		for (size_t i = columns(); i > 1; i--)
		{
			result.push_back(element(0, i));
		}
		//0->3
		for (size_t i = 0; i < rows(); i++)
		{
			result.push_back(element(i, 0));
		}
		
		return result;
	}

	vector<double> slice2()
	{
		vector<double> result;
		// 2->1
		for (size_t i = rows(); i > 1; i--)
		{
			result.push_back(element(i, columns() - 1));
		}
		//1->3
		size_t a = columns();
		size_t b = 0;
		while( a > 0 && b < rows())
		{
				result.push_back(element(b, a));
				a--;
				b++;
		}
		//3->0
		for (size_t i = rows(); i > 1; i--)
		{
			result.push_back(element(i, 0));
		}

		return result;
	}

	vector<double> slice3()
	{
		vector<double> result;
		// 3->1
		for (size_t i = 0; i < rows(); i++)
		{
			result.push_back(element(rows() - i - 1, i));
		}
		//1->2
		for (size_t i = 1; i < rows(); i++)
		{
			result.push_back(element(i, columns() - 1));
		}
		//2->0
		size_t a = rows();
		size_t b = columns();
		while (a > 0 && b > 0)
		{
			result.push_back(element(a, b));
			a--;
			b--;
		}

		return result;
	}

	Matrix add(Matrix &other)
	{
		if (rows() == other.rows() && columns() == other.columns())
		{
			Matrix result((rows() + other.rows()), (columns() + other.columns()));

			for (size_t i = 0; i < rows(); i++)
			{
				for (size_t j = 0; j < columns(); j++)
				{
					result.set_element(i, j, int(element(i, j) + other.element(i, j)));
				}
			}
			return result;
		}
		else
		{
			return Matrix();
		}
	}

	~Matrix()
	{
		if (_data) free(_data);
	}

private:
	size_t _rows, _columns;
	double* _data;
};


int main() 
{
	Matrix m(6, 6);
	/*for (size_t i = 0; i < m.rows(); ++i)
	{
		for (size_t j = 0; i < m.columns(); ++j)
		{
			m.set_element(i, j, i * 10 + j);
		}
	}*/								//эта вещь выдает ошибку индекса
	m.print();

	Matrix a(6, 6);
	/*for (size_t i = 0; i < m.rows(); ++i)
		{
			for (size_t j = 0; i < m.columns(); ++j)
			{
				m.set_element(i, j, 1);
			}
		}*/								//эта вещь выдает ошибку индекса
	a.print();

	//Matrix c = a.add(m);				//эта вещь выдает ошибку типов
	//c.print();

	vector<double> s1 = m.slice1(); //не работает
	vector<double> s2 = m.slice2(); //не работает
	vector<double> s3 = m.slice3(); //не работает

	return 0;

	//Простите, я не знаю как это исправлять...
};