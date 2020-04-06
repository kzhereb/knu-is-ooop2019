/*
 * proxy.cpp
 *
 *  Created on: Apr 6, 2020
 *      Author: KZ
 */

#include "../unit-testing/catch.hpp"

#include <string>
#include <fstream>
#include <memory>

#include <cassert>

class DataStorage {
protected:
	std::size_t size;
	std::string filename;
public:
	DataStorage(std::size_t size, std::string filename) :
			size { size }, filename { filename } {
	}
	virtual ~DataStorage() {
	}
	virtual int get(std::size_t index) = 0;
	virtual void set(std::size_t index, int value) = 0;
};

class FileStorage: public DataStorage {
private:
	int* memory_array;
	void load_from_file() {
		std::ifstream file { filename };
		for (std::size_t i = 0; i < size; i++) {
			file >> memory_array[i];
		}
	}
	void save_to_file() {
		std::ofstream file { filename };
		for (std::size_t i = 0; i < size; i++) {
			file << memory_array[i] << " ";
		}
	}
public:
	FileStorage(std::size_t size, std::string filename) :
			DataStorage(size, filename) {
		memory_array = new int[size];
		load_from_file();
	}
	~FileStorage() {
		save_to_file();
		delete [] memory_array;
	}
	int get(std::size_t index) override {
		assert(index < size);
		return memory_array[index];
	}

	void set(std::size_t index, int value) override {
		assert(index < size);
		memory_array[index] = value;
	}
};

class ProxyStorage: public DataStorage {
private:
	std::shared_ptr<FileStorage> real_storage;
public:
	ProxyStorage(std::size_t size, std::string filename) :
				DataStorage(size, filename) { }
	int get(std::size_t index) override {
		if (!real_storage) {
			real_storage = std::make_shared<FileStorage>(size,filename);
		}
		return real_storage->get(index);
	}

	void set(std::size_t index, int value) override {
		if (!real_storage) {
			real_storage = std::make_shared<FileStorage>(size,filename);
		}
		real_storage->set(index,value);
	}
};

TEST_CASE("working with proxy","[patterns]") {
	{
		ProxyStorage storage{100, "test.txt"};
		storage.set(10,123);
		REQUIRE(storage.get(10)==123);
	}
	{
		ProxyStorage storage2{100, "test.txt"};
		REQUIRE(storage2.get(10)==123);
	}
}

