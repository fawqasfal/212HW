#include "sequence1.h"
#include <assert.h> 
/* INVARIANT : 
	used, and size(), will always be less than CAPACITY.
	data[] will contain all of the objects of the sequence, and will be of size CAPACITY. 
	if size == 0 or current_index > size(), there is no current variable that can be accessed
*/ 	

namespace main_savitch_3
{ 
	const sequence::size_type sequence::CAPACITY; //needed to give CAPACITY an address for const refs 
	sequence::sequence() {
		used = 0;
		current_index = 0;
	}
	void sequence::start() {
		current_index = 0;
	}
	void sequence::advance() {
		assert(is_item()); 
		current_index++;
	}
	void sequence::insert(const value_type& entry) {
		assert(size() < CAPACITY);
		for (int i = size(); i > current_index; i--)
			data[i] = data[i-1];
		data[current_index] = entry;
		used++;
	}
	void sequence::attach(const value_type& entry) {
		assert(size() < CAPACITY);
		if (size() > 0) current_index++;
		insert(entry);
	}
	void sequence::remove_current() {
		assert(is_item());
		used--;
		for(int i = current_index; i < used; i++)
			data[i] = data[i+1];
		data[used+1] = 0; //resets the last element
	}
	sequence::size_type sequence::size() const { 
		return used;
	}
	sequence::value_type sequence::current() const { 
	 	assert(is_item());
 		return data[current_index];
 	}
	bool sequence::is_item() const {
		return current_index < size(); 
		//if size() == 0, then current_index == 0. if size() > 0 and current index >= size(), were past last element.
 	}
}