//
// Created by Tomer Amir on 10/01/2018.
//

#ifndef EX4_TYPESMAP_H
#define EX4_TYPESMAP_H


#include <map>
#include <string>
#include <vector>
#include <list>
#include <iostream>

using std::map;
using std::list;
using std::string;
using std::cout;
using std::endl;

template <class Piece>
class TypesMap {
private:
	map<string, std::vector<Piece*>> _types;

public:
	void addPiece(Piece * piece);

	std::vector<Piece*> get(Piece constraints);
};

template <class Piece>
void TypesMap<Piece>::addPiece(Piece * piece) {
	auto type = piece->getType();

	if (_types.find(type) == _types.end()) {
		_types[type] = std::vector<Piece*>();
	}

	_types[type].push_back(piece);
}

template <class Piece>
std::vector<Piece*> TypesMap<Piece>::get(Piece constraints) {
	// TODO
	if (_types.empty()) {
		return std::vector<Piece*>();
	}

	return _types.begin()->second;
}

#endif //EX4_TYPESMAP_H
