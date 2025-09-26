#include <iostream>
#include <string>

using namespace std;

#include "Map.h"
#include "Set.h"


void testSet()
{
	omen::set<int> s;
	s.insert(4);
	s.insert(1);
	s.insert(2);
	s.insert(12);
	s.insert(22);
	s.insert(2223);
	s.insert(-2);
	s.insert(0);

	omen::set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}

	cout << endl;

	--it;
	while (it != s.begin())
	{
		cout << *it << " ";
		--it;
	}
	cout << endl;
}

void testMap()
{
	omen::map<string, string> dict;
	dict.insert({ "sort", "ÅÅĞò" });
	dict.insert({ "left", "×ó±ß" });
	dict.insert({ "right", "ÓÒ±ß" });

	dict["left"] = "×ó±ß£¬Ê£Óà"; // ĞŞ¸Ä
	dict["insert"] = "²åÈë";  // ²åÈë+ĞŞ¸Ä
	dict["string"];          // ²åÈë

	omen::map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		/*it->first += 'x';*/
		it->second += 'x';
		cout << it->first << ": " << it->second << endl;
		++it;
	}
	cout << endl;
}

int main()
{
	testSet();
	testMap();
    return 0;
}
