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
	virtual void add_object(std::shared_ptr<FileSystemObject> object) {
		throw std::logic_error("Not implemented");
	}
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

	void add_object(std::shared_ptr<FileSystemObject> object) override {
		objects.push_back(object);
	}

};

class Link: public FileSystemObject {
private:
	std::shared_ptr<FileSystemObject> object;
public:
	Link(std::string name, std::shared_ptr<FileSystemObject> object) : FileSystemObject(name), object{object} {}
	std::size_t get_size() override {
		return object->get_size();
	}
	void add_object(std::shared_ptr<FileSystemObject> child_object) override {
		object->add_object(child_object);
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

	SECTION("add subdirectory") {
		std::shared_ptr<Directory> parent_dir = std::make_shared<Directory>("parent");
		parent_dir->add_object(dir);
		REQUIRE(parent_dir->get_size()==1001234);
		std::shared_ptr<File> file3 = std::make_shared<File>("test.txt",4);
		parent_dir->add_object(file3);
		REQUIRE(parent_dir->get_size()==1001238);

	}

	SECTION("working with links") {
		std::shared_ptr<Link> dir_link = std::make_shared<Link>("dir2",dir);
		REQUIRE(dir_link->get_size()==1001234);
		std::shared_ptr<File> file3 = std::make_shared<File>("test.txt",4);
		dir->add_object(file3);
		REQUIRE(dir->get_size()==1001238);
		REQUIRE(dir_link->get_size()==1001238);
		std::shared_ptr<File> file4 = std::make_shared<File>("some.txt",1000);
		dir_link->add_object(file4);
		REQUIRE(dir->get_size()==1002238);
		REQUIRE(dir_link->get_size()==1002238);
	}

	SECTION("add itself") {
		//ERROR - infinite recursion
		//dir->add_object(dir);
		//REQUIRE(dir->get_size()==1001234);
	}
}

