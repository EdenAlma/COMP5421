#include<iterator>
#include<iostream>
#include<iomanip>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
#include<set>
#include<fstream>
#include<sstream>

using namespace std;

bool is_palindrome(const string&);
string & remove_leading_trailing_non_alpha(string &);
void test_is_palindrome();
void test_second_max();
void print_word_frequency_1(const string&);
void print_word_frequency_2(const string&);
void print_word_index(const string&);


template <typename I>
pair<I, bool> second_max(I start, I finish)
{
	bool same = true;

	if (start == finish)
	{
		return make_pair(finish, false);
	}

	I tempMax = start;
	I startCopy = start;
	I tempSec = start;

	for (startCopy; startCopy != finish; ++startCopy)
	{
		if (*tempMax != *startCopy) { same = false; }
		
		if (*tempMax < *startCopy)
		{
			tempSec = tempMax;
			tempMax = startCopy;
		}
	}

	if (same) { return make_pair(start, false); }
	else { return make_pair(tempSec, true); }

}



int main()
{

	test_is_palindrome();
	cout << "------------------------------------------------------\n";

	test_second_max();
	cout << "------------------------------------------------------\n";

	string filename = "input.txt";

	print_word_frequency_1(filename);
	cout << "------------------------------------------------------\n";

	print_word_frequency_2(filename);
	cout << "------------------------------------------------------\n";

	print_word_index(filename);

	return 0;

}







class MyCompare
{

public:

	bool operator()(string l, string r) const
	{
		transform(l.begin(), l.end(), l.begin(), toupper);
		transform(r.begin(), r.end(), r.begin(), toupper);

		if (l < r) return true;
		else return false;

	}

};


bool is_palindrome(const string& phrase)
{
	auto lamb = [&](char c)
	{
		if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
			return false;
		else
			return true; };

	string temp;
	auto it = remove_copy_if(phrase.begin(), phrase.end(), inserter(temp, temp.begin()), lamb);
	transform(temp.begin(), temp.end(), temp.begin(), toupper);

	auto mid = temp.begin();

	if (temp.size() % 2 == 0)
		advance(mid, (temp.size() / 2 - 1));
	else
		advance(mid, (temp.size() / 2));

	return equal(temp.begin(), mid, temp.rbegin());
}


string & remove_leading_trailing_non_alpha(string & word)
{
	auto lamb = [&](char c)
	{
		if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
			return false;
		else
			return true; };


	do
	{

		auto f = word.begin();
		auto b = word.rbegin();

		if (lamb(*f))
		{
			word.erase(f);
		}

		if (lamb(*b))
		{
			word.pop_back();
		}


	} while (false);


	return word;
}


void test_is_palindrome()
{
	string str_i = "Was it a car or a cat I saw?";
	string str_u = "Was it a car or a cat U saw?";

	cout << "the phrase \"" + str_i + "\" is " +
		(is_palindrome(str_i) ? "" : "not ") + "a palindrome\n";

	cout << "the phrase \"" + str_u + "\" is " +
		(is_palindrome(str_u) ? "" : "not ") + "a palindrome\n";
}


void test_second_max()
{
	vector<int> int_vec{1,1,5,5,7,7};

	auto retval = second_max(int_vec.begin(), int_vec.end());

	if (retval.second)
	{
		cout << "The second largest element in int_vec is " << *retval.first << endl;
	}
	else
	{
		if (retval.first == int_vec.end())
			cout << "List empty, no elements \n";
		else
			cout << "Container's element are all equal to " << *retval.first << endl;
	}

}


void print_word_frequency_1(const string& filename) 
{
	ifstream ifs = ifstream(filename);

	if (!ifs) throw invalid_argument(string("could not open file") + filename);

	map<string, int> word_frequency_map;

	string line;
	while (getline(ifs, line))
	{
		istringstream iss(line);

		string word;

		while (iss >> word)
		{
			++word_frequency_map[ remove_leading_trailing_non_alpha(word) ];
		}
	}

	for (const auto &word : word_frequency_map)
	{
		cout << setw(10) << word.first << " " << word.second << endl;
	}
}


void print_word_frequency_2(const string& filename)
{
	ifstream ifs = ifstream(filename);

	if (!ifs) throw invalid_argument(string("could not open file") + filename);

	
	map<string, int, MyCompare> word_frequency_map;

	string line;
	while (getline(ifs, line))
	{
		istringstream iss(line);

		string word;

		while (iss >> word)
		{
			++word_frequency_map[remove_leading_trailing_non_alpha(word)];
		}
	}

	for (const auto &word : word_frequency_map)
	{
		cout << setw(10) << word.first << " " << word.second << endl;
	}
}


void print_word_index(const string& filename)
{
	ifstream ifs = ifstream(filename);

	if (!ifs) throw invalid_argument(string("could not open file") + filename);


	map<string, set<int>, MyCompare> word_frequency_map;

	string line;
	int lineNum = 1;

	while (getline(ifs, line))
	{

		istringstream iss(line);

		string word;

		while (iss >> word)
		{
			word_frequency_map[remove_leading_trailing_non_alpha(word)].insert(lineNum);
		}

		++lineNum;
	}

	for (const auto &word : word_frequency_map)
	{
		cout << setw(10) << word.first << " "; 
		auto temp = word.second;
		for (auto it = temp.begin(); it != temp.end(); ++it)
		{
			cout << *it << " ";
		}

		cout << endl;
	}
}


