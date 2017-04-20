#include "rec_fun.h"
#include <iostream>

using namespace mry2270; 
int main() {
	//check triangle
	triangle(std::cout, 3, 5);
	//check numbers
	numbers(std::cout, "THERBLIG", 2);
	//check bears
	int tests[] = {250, 208, 42, 84, 53, 41};
	for (auto i : tests)
		std::cout << i << " " << mry2270::bears(i) << std::endl;
	//check pattern
	pattern(std::cout, 16, 2);
	//check path
	std::multimap<int,int> mymultimap;

	mymultimap.insert (std::pair<int,int>(1,1));
	mymultimap.insert (std::pair<int,int>(1,2));
	mymultimap.insert (std::pair<int,int>(1,7));
  	mymultimap.insert (std::pair<int,int>(2,3));
  	mymultimap.insert (std::pair<int,int>(3,2));
  	mymultimap.insert (std::pair<int,int>(3,3));
  	mymultimap.insert (std::pair<int,int>(3,4));
  	mymultimap.insert (std::pair<int,int>(3,5)); 
  	std::set<int> already_tried; 
  	
  	std::cout << path(mymultimap, 1, 5, already_tried) << std::endl; //should be true
  	std::cout << path(mymultimap, 1, 42, already_tried) << std::endl; //should be false

}