/*
 * composite.cpp
 *
 *  Created on: Mar 20, 2020
 *      Author: KZ
 */

#include "../unit-testing/catch.hpp"

#include <string>
#include <vector>
#include <memory>

class FileSystemObject {
protected:
	std::string name;
public:
	FileSystemObject(std::string name): name{name} {}
	virtual std::size_t get_size() = 0;
	virtual ~FileSystemObject() = default;
};


class File: public FileSystemObject {
private:
	std::size_t size;
public:
	File(std::string name, std::size_t size): FileSystemObject(name), size{size} {}
	std::size_t get_size() override {
		return size;
	}
};

class Directory: public FileSystemObject {
private:
	std::vector<std::shared_ptr<FileSystemObject>> objects;
public:
	Directory(std::string name):FileSystemObject(name) {}
	std::size_t get_size() override {
		std::size_t result = 0;
		for(const auto & fsobject:objects) {
			result += fsobject->get_size();
		}
		return result;
	}

	void add_object(std::shared_ptr<FileSystemObject> object) {
		objects.push_back(object);
	}

};

TEST_CASE("working with filesystem", "[patterns]") {
	std::shared_ptr<File> file = std::make_shared<File>("test.txt",1234);
	std::shared_ptr<File> file2 = std::make_shared<File>("app.exe",1000000);
	std::shared_ptr<Directory> dir = std::make_shared<Directory>("dir");
	dir->add_object(file);
	dir->add_object(file2);
	REQUIRE(file->get_size()==1234);
	REQUIRE(dir->get_size()==1001234);


}

