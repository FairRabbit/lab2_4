#include<iostream>	
#include<vector>
#include<list>
#include<set>
#include<map> //multiset
#include<ctime>
#include<algorithm>
#include<thread>
using namespace std;

//filling coletion
template<typename T>
void full(T& col,int& size) {
	for (int i = 0;i < size; ++ i) {
		col.emplace_back(rand() % 10);
	}
}
template<> void full(map<int, int>& col, int& size) {
	for (int i = 0; i < size; ++i) {
		col.emplace(rand() % 10, rand() % 10);
	}
}
template<> void full(multiset<int>& col, int& size) {
	for (int i = 0;i < size;++i) {
		col.insert(rand() % 10);
	}
}

//collection console output
template<typename T>
void print(T& col) {
	for (auto i = col.begin();i != col.end();++i) {
		cout << *i << endl;
	}
}
template<> void print(map<int, int>& col) {
	for (auto i = col.begin(); i != col.end(); ++i) {
		cout << i->first << ' ' << i->second << endl;
	}
}

//task completion
template<typename T>
void exercise(T& col,int& value) {
	print(col);
	cout << "=========================" << endl;
	for_each(col.begin(), col.end(), [&value](int& a)
		{
			if (a == value) {
				a *= 2;
			}
		});
	print(col);
	cout << endl;
}
template<> void exercise(multiset<int>& col, int& value) {
	print(col);
	cout << "=========================" << endl;
	int v = count_if(col.begin(), col.end(), [&value](const int& a) {return a == value;});
	if (v != false) {
		col.erase(find_if(col.begin(), col.end(), [&value](const int& a) {return a == value;}));
	}
	while (v == true) {
		col.insert(value * 2);
		--v;
	}
	print(col);
	cout << endl;
}
template<> void exercise(map<int, int>& col, int& value) {
	print(col);
	cout << "=========================" << endl;
	auto t = find_if(col.begin(), col.end(), [](auto& a) {return a.second == 4;});
	if (t != col.end()) {
		t->second = value * 2;
	}
	print(col);
	cout << endl;
}

//collection timeout
template<typename T>
void t(T col,int size) {
	auto start = chrono::high_resolution_clock::now();
	full(col, size);
	auto end = chrono::high_resolution_clock::now();
	auto time_gen = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "time_gen: " << time_gen.count() << " microseconds" << endl;
}


int main() {

	srand(time(NULL));
	
	int value,size;
	cout << "collection size: ";
	cin >> size;
	cout << "value to double in collection: ";
	cin >> value;

	vector<int> vec;
	list<int> lis;
	map<int, int> m;
	multiset<int> s;

	//parallel populationn of collections
	thread th1([=]() {t(vec, size);});
	thread th2([=]() {t(lis, size);});
	thread th3([=]() {t(s, size);});
	thread th4([=]() {t(m, size);});

	cout << "collection size 2: ";
	cin >> size;

	//populating collections for a job
	full(vec, size);
	full(lis, size);
	full(s, size);
	full(m, size);
	//task completion
	exercise(vec, value);
	exercise(lis, value);
	exercise(s, value);
	exercise(m, value);
	//waiting for streams
	th1.join();
	th2.join();
	th3.join();
	th4.join();

	return 0;
}