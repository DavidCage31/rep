#include <iostream>
#include <ctime>
#include <random>

#define chap size
#define sarqi_chap make_size

template<typename norVec_Ty>
class NorVector 
{
private:
	int N;
	norVec_Ty* norVec;
	norVec_Ty* arr;

public:
	NorVector()
	{
		N = 0;
		norVec = new norVec_Ty[N];
	}
	NorVector(const int size)
	{
		N = size;
		norVec = new norVec_Ty[N];
	}

	~NorVector()
	{
		delete[] norVec;
	}

	/**
	NorVector(const norVec_Ty& other)
	{
		this->N = other.size();

		delete this->norVec;
		this->norVec = new norVec_Ty[N];

		for (int i = 0; i < N; i++)
		{
			this->norVec[i] = other[i];
		}
	}
	/**/

	norVec_Ty& operator[] (const int index)
	{
		return norVec[index];
	}

	norVec_Ty& operator= (const norVec_Ty& other)
	{
		if (this != &other)
		{
			delete[] this->norVec;
			this->norVec = new norVec_Ty[other.size()];

			for (int i = 0; i < other.size(); i++)
				this->norVec[i] = other[i];

			this->N = other.N;
		}

		return *this;
	}

	std::ostream& operator<<(const norVec_Ty& norV)
	{
		std::ostream out;

		for (int i = 0; i < norV.size(); i++)
			out << norV[i] << " ";

		out << "\n";

		return out;
	}

	void push_back(const norVec_Ty& value);

	void make_size(const int size);

	void show()
	{
		for (int i = 0; i < N; i++)
			std::cout << norVec[i] << " ";

		std::cout << "\n";
	}

	void fill_vec()
	{
		for (int i = 0; i < N; i++)
			norVec[i] = rand();
	}

	void del_vec()
	{
		delete[] norVec;
		norVec = nullptr;
	}

	void reverse()
	{
		for (int i = 0; i < N / 2; i++)
			std::swap(norVec[i], norVec[N - i - 1]);
	}

	int size()
	{
		return N;
	}
};

template<typename norVec_Ty>
void NorVector<norVec_Ty>::push_back(const norVec_Ty& value)
{
	arr = new norVec_Ty[N + 1];

	for (int i = 0; i < N; i++)
	{
		arr[i] = norVec[i];
	}

	delete[] norVec;

	norVec = new norVec_Ty[N + 1];

	for (int i = 0; i < N; i++)
	{
		norVec[i] = arr[i];
	}

	delete[] arr;
	arr = NULL;

	norVec[N] = value;
	N++;
}

template<typename norVec_Ty>
void NorVector<norVec_Ty>::make_size(const int size) 
{
	arr = new norVec_Ty[size];

	for (int i = 0; i < N && i < size; i++) 
	{
		arr[i] = norVec[i];
	}

	delete[] norVec;

	norVec = new norVec_Ty[size];

	for (int i = 0; i < size && i < N; i++)
	{
		norVec[i] = arr[i];
	}

	N = size;

	delete[] arr;
	arr = NULL;
}

int main() 
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	NorVector<int> a, b;
	int lenutsun;

	lenutsun = 10;

	a.make_size(lenutsun);
	a.fill_vec();

	b.make_size(5);
	b.fill_vec();

	a.show();
	b.show();
	
	std::cout << "----------------------------------\n";

	a = b;

	a.show();
	b.show();

	return 0;
}