/*
 Implementation of the min-heap using an array.

 Max-Heap is a Binary tree where each parent nodes value is greater 
 than that of their child. It is used when you need quick access to 
 the largest number in the array.
*/

#include <iostream>
#include <stdexcept>

class Heap{
	public:
		void insert(const int& data);
		void removemin();
		void print();
		Heap();
		~Heap();

	private:
		// size - number of elements in the array
		// capacity - number of elements the array can store
		int size, capacity;
		int *items_;

		int parent(unsigned index) const;
		int child(unsigned index) const;

		void heapifyUP(unsigned index);
		void heapifyDOWN(unsigned index);
		void growArray();

};

Heap::Heap(): size(0), capacity(2){
	items_ = new int[capacity + 1];
}

Heap::~Heap(){
	delete items_;
	items_ = nullptr;
}

int Heap::parent(unsigned index) const{ return index/2; }

void Heap::growArray(){
	/**
	  * Inorder to accommodate more numbers in the array
	  * Allocate memory in the heap 
	  * Double the size of the old array up to (capacity*2) + 1
	  * Copy the elements of the previous array into the new array
	  */

	// Doubling the size of the array
	int* new_Array = new int[(capacity * 2) + 1];
	// Copying the elements of the old array to the new array
	for(int i=1; i<=size; i++){ new_Array[i] = items_[i]; }
	// Doubling the capacity
	capacity *= 2;
	// delete the items_ inorder to avoid any memory leak
	delete items_;
	// set items_ to point to new_Array
	items_ = new_Array;
}

void Heap::insert(const int& data){
	// if size == capacity it means the array is full and need to grow
	if(size == capacity){ growArray(); }
	items_[++size] = data;
	heapifyUP(size);
}

void Heap::heapifyUP(unsigned index){
	if(index > 1){
		if(items_[index] > items_[parent(index)]){
			std::swap(items_[index], items_[parent(index)]);
			heapifyUP(parent(index));
		}
	}
}

void Heap::removemin(){
	std::swap(items_[1], items_[size--]);
	heapifyDOWN(1);
}

int Heap::child(unsigned index) const{
	unsigned left = index * 2;
	unsigned right = (index * 2) + 1;

	if(right > size){ return left; }
	else if(items_[left] >= items_[right]){ return left; }
	return right;
}

void Heap::heapifyDOWN(unsigned index){
	int childindex = child(index);
	if(index*2 <= size){
		if(items_[index] < items_[childindex]){
			std::swap(items_[index], items_[childindex]);
			heapifyDOWN(childindex);
		}
	}
}

void Heap::print(){
	for(int i=1; i<=size; i++){ std::cout << items_[i] << " "; }
	std::cout << std::endl;
}


int main(){
	Heap heap;

	heap.insert(4);
	heap.insert(10);
	heap.insert(2);
	heap.insert(22);
	heap.insert(45);
	heap.insert(18);
	heap.insert(-8);
	heap.insert(95);
	heap.insert(13);
	heap.insert(42);

	heap.removemin();
	heap.removemin();

	heap.print();
	/*
	Output: 42 22 18 13 10 2 -8 4
	
	Time complexity to build the heap: O(n)
	Time complexity to remove min: O(log(n))
	Time complexity to remove all elements: O(n*log(n))
	*/
	return 0;

}
