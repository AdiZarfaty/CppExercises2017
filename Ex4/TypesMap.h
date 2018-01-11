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
	std::vector<Piece*> res;

	if (_types.empty()) {
		return res;
	}

	for (auto it = constraints.begin(); it != constraints.end(); ++it) {
		if (*it == std::numeric_limits<int>::min()) {
			for (int k = -constraints.getRange(); k <= constraints.getRange(); k++) {
				*it = k;

				auto tmp = get(constraints);

				if (!tmp.empty()) {
					res.insert(res.end(), tmp.begin(), tmp.end());
				}
			}

			return res;
		}
	}

	auto type = constraints.getType();

	if (_types.find(type) != _types.end()) {
		return _types[type];
	}

	return res;
}

#endif //EX4_TYPESMAP_H
