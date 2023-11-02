#pragma once
#include <string>
using namespace std;

class Mob;
class Breed
{
private:
	string name;

public:
	Breed(string name) : name(name) {};
	virtual string GetName() { return this->name; }
	Mob* CreateMob(float maxHp);
};

