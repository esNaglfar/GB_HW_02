#include <vector>
#include <string>
#include <iostream>



// 1) Ќаписать функцию, добавл€ющую в конец списка вещественных чисел элемент, значение которого равно среднему арифметическому всех его элементов.

void AddAvgToVec(std::vector<int>& _intVector)
{
	int avg = 0;
	for (int value : _intVector)
	{
		avg += value;
	}
	avg = avg / _intVector.size();
	_intVector.push_back(avg);
}

template<typename T>
void PrintVec(const std::vector<T>& vec)
{
	for (T value : vec)
	{
		std::cout << value;
	}
}

// 2. —оздать класс, представл€ющий матрицу. –еализовать в нем метод, вычисл€ющий определитель матрицы.

class Matrix
{
public:
	Matrix(std::vector<std::vector<float>> _matrix) :
		matrix(_matrix),mSize(_matrix.size()), swaps(0u) {
	}

	float GetDenominator()
	{
		Triangulate();
		float denom = 1;
		for (size_t i = 0; i < mSize; i++)
		{
			denom *= triangulated[i][i];
		}

		return (swaps % 2 == 0) ? denom : -denom;
	}

private:
	
	float GetMaxElementInRow(size_t _colIndex)
	{
		float max = std::abs(matrix[_colIndex][_colIndex]);
		size_t maxPos = _colIndex;

		for (size_t i = _colIndex + 1; i < mSize; i++)
		{
			float value = std::abs(matrix[i][_colIndex]);
			if (value > max)
			{
				max = value;
				maxPos = i;
			}
		}

		return maxPos;
	}

	void Triangulate()
	{
		if (triangulated.empty())
		{
			triangulated = matrix;

			for (size_t i = 0; i < mSize; i++)
			{
				size_t max = GetMaxElementInRow(i);
				if (i != max)
				{
					std::swap(triangulated[i], triangulated[max]);
					swaps++;
				}

				for (size_t j = i + 1; j < mSize; j++)
				{
					float multiplier = -triangulated[j][i] / triangulated[i][i];

					for (size_t k = 0; k < mSize; k++)
					{
						triangulated[j][k] += triangulated[i][k] * multiplier;
					}
				}
			}
		}
	}

	std::vector<std::vector<float>> matrix;
	std::vector<std::vector<float>> triangulated;
	size_t swaps;
	size_t mSize;
};


int main()
{
	std::cout << "Task 1\n" << std::endl;
	
	std::vector<int> v = { 1,2,3 };
	AddAvgToVec(v);
	PrintVec(v);

	std::cout << "\nTask 2\n" << std::endl;

	std::vector<float> row1;
	row1.push_back(7);
	row1.push_back(2);
	row1.push_back(5);

	std::vector<float> row2;
	row2.push_back(4);
	row2.push_back(1);
	row2.push_back(9);

	std::vector<float> row3;
	row3.push_back(8);
	row3.push_back(3);
	row3.push_back(7);

	std::vector<std::vector<float>> matrix;
	matrix.push_back(row1);
	matrix.push_back(row2);
	matrix.push_back(row3);

	Matrix mat(matrix);

	std::cout << "Denom " << mat.GetDenominator();

	std::cout << "\nTask 3\n" << std::endl;


	return 0;
}