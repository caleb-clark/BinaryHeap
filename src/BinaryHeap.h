#include <vector>
#include <iostream>

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

typedef unsigned int UInt32;

template <class T>
class BinaryHeap 
{
private:
	friend class BinaryHeap;
	std::vector<T> * heap_;
	bool max_;
	UInt32 size_;
public:
	// constructor
	BinaryHeap(bool max = true);
	// destructor
	~BinaryHeap();
	// copy constructor
	BinaryHeap(const BinaryHeap<T>& b);
	// copy assignment operator overload
	BinaryHeap<T>& operator=(const BinaryHeap<T>& b);
	// insert element into heap
	void insert(T t);
	// get element with first priority
	T retrieve_first();
	// remove element with first priority
	// and return that element
	T remove_first();
	// get the size of the heap
	size_t size() const;
	// get the children of an element
	std::pair<T,T> get_children(T t);
	// given a vector of elements
	// insert all of them into the heap
	void heapify(const std::vector<T>& v);
	// get whether the heap is 
	// a min or max
	bool is_max();

	T operator[](UInt32 pos) const;

	void print();

	template <typename Y>
	friend std::ostream& operator<<(std::ostream& os, const BinaryHeap<T>& b);

};


// constructor
template <class T>
BinaryHeap<T>::BinaryHeap(bool max)
{
	heap_ = new std::vector<T>();
	this->max_ = max;
	this->size_ = 0;
}

// destructor
template <class T>
BinaryHeap<T>::~BinaryHeap()
{
	delete heap_;
}

// copy constructor
template <class T>
BinaryHeap<T>::BinaryHeap(const BinaryHeap<T>& b)
{
	this->max_ = b.is_max();
	this->heap_ = new std::vector<T>();
	this->size_ = b.size_;
	for (UInt32 i = 0; i < b.heap_; i++) {
		this->heap_->push_back(b.heap_->at(i));
	}

}

// copy assignment operator overload
template <class T>
BinaryHeap<T>& BinaryHeap<T>::operator=(const BinaryHeap<T>& b)
{
	delete this->heap_;
	this->max_ = b.max_;
	this->heap_ = new std::vector<T>();
	this->size_ = b.size_;
	for (UInt32 i = 0; i < b.heap_; i++) {
		this->heap_->push_back(b.heap_->at(i));
	}

}

// insert element into heap
template <class T>
void BinaryHeap<T>::insert(T t)
{
	heap_->push_back(t);
	UInt32 pos = heap_->size() - 1;
	while (heap_->at(pos/2) > t) {
		
		heap_->at(pos) = heap_->at(pos/2);
		if (pos == 0) break;
		pos /= 2;
		
	}
	heap_->at(pos) = t;
	size_++;
}

// get element with first priority
template <class T>
T BinaryHeap<T>::retrieve_first()
{
	return heap_->at(0);
}

// remove element with first priority
// and return that element
template <class T>
T BinaryHeap<T>::remove_first()
{
	T to_return;
	if (size_ > 0) {
		to_return = heap_->at(0);
	} else {
		std::cout << "No elements in heap, exiting." << std::endl;
		exit(-1);
	}
	
	if (size_ == 2) {
		heap_->at(0) = heap_->at(1);
	} else if (size_ > 2) {
		heap_->at(0) = heap_->at(heap_->size()-1);
		UInt32 index = 0;
		bool stop = false;

		while (!stop) {

			if (2*index + 1 == (heap_->size() - 1) || heap_->at(2*index + 1) < heap_->at(2*index + 2)) {
				// left child is smaller
				if (heap_->at(index) > heap_->at(2*index + 1)) {
					T tmp = heap_->at(2*index + 1);
					heap_->at(2*index + 1) = heap_->at(index);
					heap_->at(index) = tmp;
					index = 2*index + 1;
					if (2*index + 1 >= heap_->size()) {
						stop = true;
					}
				} else {
					stop = true;
				}


			} else {
				// right child is smaller
				if (heap_->at(index) > heap_->at(2*index + 2)) {
					T tmp = heap_->at(2*index + 2);
					heap_->at(2*index + 2) = heap_->at(index);
					heap_->at(index) = tmp;
					index = 2*index + 2;
					if (2*index + 1 >= heap_->size()) {
						stop = true;
					}
				} else {
					stop = true;
				}
			}
		}
	}
	size_--;
	heap_->erase(heap_->begin()+(heap_->size()-1));
	return to_return;
}

// get the children of an element
template <class T>
std::pair<T,T> BinaryHeap<T>::get_children(T t)
{
	UInt32 i = 0;
	for (; i < heap_->size(); i++) {
		if (heap_->at(i) == t) {
			break;
		}
	}
	if (heap_->at(i) != t) {
		std::cout << "Element not in heap" << std::endl;
		T tmp = T();
		return std::make_pair(tmp,tmp);
	}
	return std::make_pair(heap_->at(2*i + 1),heap_->at(2*i + 2));
}

// get the size of the heap
template <class T>
size_t BinaryHeap<T>::size() const
{
	return heap_->size();
}

// given a vector of elements
// insert all of them into the heap
template <class T>
void BinaryHeap<T>::heapify(const std::vector<T>& v)
{
	for (UInt32 i = 0; i < v.size(); i++) {
		this->insert(v[i]);
	}
}

template<class T>
bool BinaryHeap<T>::is_max()
{
	return this->max_;
}

template<class T>
T BinaryHeap<T>::operator[](UInt32 pos) const
{
	if (pos < heap_->size()) {
		return heap_->at(pos);
	} else {
		std::cout << "Out of Range" << std::endl;
		T tmp = T();
		return tmp;
	}
}

template <class T>
void BinaryHeap<T>::print()
{
	int layer_cnt = 1;
	int curr_cnt = 0;
	for (int i = 0; i < heap_->size(); i++) {
	
		std::cout << heap_->at(i) << " ";
		curr_cnt++;
		if (curr_cnt == layer_cnt) {
			curr_cnt = 0;
			layer_cnt *= 2;
			std::cout << std::endl;
		}
		
	}
	std::cout << std::endl;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const BinaryHeap<T>& b)
{
	int layer_cnt = 1;
	int curr_cnt = 0;
	for (int i = 0; i < b.size(); i++) {
	
		os << b[i];
		curr_cnt++;
		if (curr_cnt == layer_cnt) {
			curr_cnt = 0;
			layer_cnt *= 2;
			os << std::endl;
		}
		
	}

}
#endif