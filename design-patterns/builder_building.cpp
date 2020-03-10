/*
 * builder_building.cpp
 *
 *  Created on: Mar 10, 2020
 *      Author: KZ
 */
#include <vector>

#include "../unit-testing/catch.hpp"

enum class RoofType { Triangle, Flat, Ornamental };

enum class RoomType { LivingAppartment, Office, Store, Service};

struct Room {
	RoomType type;
	double area; // in m^2
};

class Building {
private:
	std::size_t floor_number;
	RoofType roof_type;
	int constructed_year;
	std::string architect_name;
	std::vector<Room> rooms;
	friend class BuildingBuilder;
public:
	Building() = default;

	double get_total_area() {
		double result = 0.0;
		for(const auto& room:rooms) {
			result+= room.area;
		}
		return result;
	}

};

class BuildingBuilder {
private:
	Building under_construction;
public:
	BuildingBuilder& set_floor_number(std::size_t floor_number) {
		under_construction.floor_number = floor_number;
		return *this;
	}
	BuildingBuilder& set_architect_name(std::string name) {
		under_construction.architect_name = name;
		return *this;
	}
	BuildingBuilder& add_room(Room room) {
		under_construction.rooms.push_back(room);
		return *this;
	}

	Building construct_building() {
		return under_construction;
	}

};

TEST_CASE("build simple building", "[patterns]") {
	BuildingBuilder builder;
	builder.set_floor_number(10).set_architect_name("Vasyl")
			.add_room({RoomType::Store,200})
			.add_room({RoomType::LivingAppartment,100})
			.add_room({RoomType::LivingAppartment,20})
			.add_room({RoomType::Service,3});
	Building house = builder.construct_building();
	double error = 1e-8;
	REQUIRE(std::abs(house.get_total_area() - 323.0) < error);
}

TEST_CASE("comparing doubles","[cpp]") {
	double one_third = 1/3.0;
	double two_thirds = 1 - one_third;
	REQUIRE((1-two_thirds)*3 != 1);
	double error = 1e-8;
	REQUIRE(std::abs((1-two_thirds)*3 - 1.0)<error);
}


