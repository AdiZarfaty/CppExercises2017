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
	map<string, std::vector<Piece>> _types;

public:
	void addPiece(Piece * piece);

	std::vector<Piece> get(Piece constraints);
};

template <class Piece>
void TypesMap<Piece>::addPiece(Piece * piece) {
	// TODO
}

template <class Piece>
std::vector<Piece> TypesMap<Piece>::get(Piece constraints) {
	cout << "here" << endl;
	return std::vector<Piece>();
}

#endif //EX4_TYPESMAP_H
