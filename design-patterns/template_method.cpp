/*
 * template_method.cpp
 *
 *  Created on: Apr 16, 2020
 *      Author: KZ
 */
#include "../unit-testing/catch.hpp"

#include <utility>
#include <iostream>
#include <cstddef>

class Sorter {
public:
	virtual void sort(int* arr, std::size_t begin, std::size_t end) =0;
};

class QuickSort: public Sorter {
public:
	void sort(int* arr, std::size_t begin, std::size_t end) override {
		if (end-begin<2) {return;}
		int pivot = get_pivot_value(arr,begin,end);
		auto limits = partition(arr,begin,end,pivot);
		sort(arr,begin,limits.first);
		sort(arr,limits.second,end);
	}
protected:
	virtual int get_pivot_value(int* arr, std::size_t begin, std::size_t end) = 0;
	virtual std::pair<std::size_t, std::size_t> partition(int* arr, std::size_t begin, std::size_t end, int pivot) = 0;
};

class LomutoQuickSort: public QuickSort {
protected:
	int get_pivot_value(int* arr, std::size_t begin, std::size_t end) override {
		return arr[end-1];
	}
	std::pair<std::size_t, std::size_t> partition(int* arr, std::size_t begin, std::size_t end, int pivot) override {
		std::size_t i = begin;
		for(std::size_t j=begin; j<end-1; j++) {
			if (arr[j]<pivot) {
				std::swap(arr[i],arr[j]);
				i++;
			}
		}
		std::swap(arr[i], arr[end-1]);
		return {i,i+1};
	}

};

class StdPartitionQuickSort: public QuickSort {
protected:
	int get_pivot_value(int* arr, std::size_t begin, std::size_t end) override {
		return arr[(begin+end)/2];
	}
	std::pair<std::size_t, std::size_t> partition(int* arr, std::size_t begin, std::size_t end, int pivot) override {
		auto left = std::partition(arr+begin, arr+end,
				[pivot](const auto& item) {return item < pivot;});
		auto right = std::partition(arr+begin, arr+end,
				[pivot](const auto& item) {return !(pivot < item);});
		return {std::distance(arr,left),std::distance(arr,right)};
	}
};

class PivotStrategy {
public:
	virtual int get_pivot_value(int* arr, std::size_t begin, std::size_t end) = 0;
};

class PartitionStrategy {
public:
	virtual std::pair<std::size_t, std::size_t> partition(int* arr, std::size_t begin, std::size_t end, int pivot) = 0;

};

class StrategyBasedQuickSort: public QuickSort {

};

TEST_CASE("sorting with quicksort","[patterns]") {
	int test_array[] = {10, -1, 17, 123, 5, 7, 10, 123};
	Sorter* sorter = nullptr;
	SECTION ("Lomuto") {
		sorter = new LomutoQuickSort;
	}
	SECTION ("std::partition") {
		sorter = new StdPartitionQuickSort;
	}

	sorter->sort(test_array,0,8);


	for (std::size_t i=0;i<8;i++) {
		std::cout<<test_array[i]<<" ";
	}
	std::cout<<std::endl;

	REQUIRE(std::is_sorted(std::begin(test_array),std::end(test_array)));

//	REQUIRE(test_array[0]==-1);
//	REQUIRE(test_array[1]==-1);
//	REQUIRE(test_array[0]==-1);
//	REQUIRE(test_array[0]==-1);
//	REQUIRE(test_array[0]==-1);
//	REQUIRE(test_array[0]==-1);
//	REQUIRE(test_array[0]==-1);
//	REQUIRE(test_array[0]==-1);
}
