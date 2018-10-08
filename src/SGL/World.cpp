#include "World.hpp"
#include <cmath>

namespace sgl
{

std::vector<ObjPtr> World::getObjects() const
{
	return Objects;
}

void World::addObject(Object &value)
{
	Objects.push_back(ObjPtr(&value));
}

void World::addObject(Object *value)
{
	Objects.push_back(ObjPtr(value));
}

void World::createObject(const Vector &position, const double mass)
{
	Objects.push_back(ObjPtr(new Object(position, mass)));
}

void World::step(const double time)
{
	for (auto &obj1 : Objects)
	{
		for (auto &obj2 : Objects)
		{
			if (obj1 == obj2) continue; // fordebug

			auto direction = obj2->getPosition() - obj1->getPosition();
			auto R = direction.length();

			direction = direction / R;

			double k = 2 * (1 + 1/R); //magic const

			auto gravityForce = direction * World::getG() *
					((obj1->getMass() * obj2->getMass()) / (std::pow(R, k)));

			obj1->applyForce(gravityForce, time);
		}
		obj1->step(time);
	}
}

}