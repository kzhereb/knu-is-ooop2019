/*
 * create_threads.cpp
 *
 *  Created on: May 22, 2020
 *      Author: KZ
 */

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../unit-testing/catch.hpp"

#include <thread>
#include <mutex>
#include <iostream>
#include <vector>
#include <chrono>

std::mutex g_mutex;

long long sum_sequential(int* arr, std::size_t size) {
	long long result = 0;
	for (std::size_t i = 0; i < size; i++) {
		result += arr[i];
	}
	return result;
}

void single_thread(int* arr, std::size_t start, std::size_t end, long long & result) {
	for (std::size_t i = start; i < end; i++) {
		std::lock_guard<std::mutex> lock(g_mutex);
		result += arr[i];
	}
}

void single_thread_less_locks(int* arr, std::size_t start, std::size_t end, long long & result) {
	long long local_result = 0;
	for (std::size_t i = start; i < end; i++) {

		local_result += arr[i];
	}

	{
		std::lock_guard<std::mutex> lock(g_mutex);
		result+=local_result;
	}


}
template<typename Func>
long long sum_threads(int* arr, std::size_t size, Func thread_func) {
	long long result = 0;
	unsigned num_threads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(num_threads);
	std::size_t thread_size = (size / num_threads)+1;
	std::size_t start = 0;
	for (unsigned i = 0; i < num_threads; i++) {
		threads.at(i)=std::thread(thread_func, arr,
			start, std::min(start + thread_size, size), std::ref(result));
		start += thread_size;
	}
	for (auto& worker : threads) {
		worker.join();
	}

	return result;
}

int* generate_range(std::size_t size) {
	int* result = new int[size];
	for (std::size_t i = 0; i < size; i++) {
		result[i] = i;
	}
	return result;
}

TEST_CASE("sum of array elements", "[threads]") {
	int* test_array = new int[7]{ 1,5,10,20,100,200,4 };
	std::size_t size = 7;
	long long sum;
	SECTION("sequential") {
		sum = sum_sequential(test_array, size);
	}
	SECTION("threads") {
		sum = sum_threads(test_array, size, single_thread);
	}
	SECTION("threads less locks") {
		sum = sum_threads(test_array, size, single_thread_less_locks);
	}

	REQUIRE(sum == 340);

	//std::cout << std::thread::hardware_concurrency() << std::endl;
}

TEST_CASE("sum of sequential numbers", "[threads]") {
	std::size_t size = 1e6;
	int* test_array = generate_range(size);
	long long expected_sum = (long long)size * (size - 1) / 2;

	long long sum;




	SECTION("sequential") {
		auto start = std::chrono::high_resolution_clock::now();
		sum = sum_sequential(test_array, size);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "sequential time: " << diff.count() << " s" << std::endl;

		BENCHMARK("sequential") {
			return sum_sequential(test_array, size);
		};
	}
	SECTION("threads") {
		auto start = std::chrono::high_resolution_clock::now();
		sum = sum_threads(test_array, size, single_thread);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "threads time: " << diff.count() << " s" << std::endl;

//		BENCHMARK("threads") {
//			return sum_threads(test_array, size);
//		};
	}

	SECTION("threads less locks") {
		auto start = std::chrono::high_resolution_clock::now();
		sum = sum_threads(test_array, size, single_thread_less_locks);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> diff = end - start;
		std::cout << "threads time: " << diff.count() << " s" << std::endl;

		BENCHMARK("threads less locks") {
			return sum_threads(test_array, size, single_thread_less_locks);
		};
	}

	REQUIRE(sum == expected_sum);

	//std::cout << std::thread::hardware_concurrency() << std::endl;
}
