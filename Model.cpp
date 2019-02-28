#include "Model.h"

void Model::analysis(int const &i) {
	if (i == N) {
		events.push_back(new StopModeling());
	}

	
	for (auto it = animals.begin(); it != animals.end(); ++it)
		(*it)->victimFlag = false;

	
	for (auto it1 = animals.begin(); it1 != animals.end(); ++it1)
	{
		if ((*it1)->deleteFlag)
			continue;

		
		if ((*it1)->predatorFlag)
		{
			auto v = *( (*it1)->victim );
			
			if (v->deleteFlag || v->isOutsideTheSimulation(lowerBorder, upperBorder) || !((*it1)->hasInSight(*v)))
				(*it1)->predatorFlag = false;
			else
				events.push_back(new ChangeDirection(*it1, v));
		}

		
		vector<vector<Animal*>::iterator> victims;
		vector<vector<Animal*>::iterator> predators;

		
		for (auto it2 = animals.begin(); it2 != animals.end(); ++it2)
		{
			if ((*it2)->deleteFlag)
				continue;

			if ((*it1)->canEat(**it2) && (*it1)->isInVoracityZone(**it2)) //it1 eats it2
			{
				events.push_back(new DeleteObject(*it2));
				if ((*it1)->predatorFlag && (*it1)->victim == it2)
					(*it1)->predatorFlag = false;
			}

			if ((*it1)->hasInSight(**it2)) //it1 feels it2
			{
				if ( !((*it1)->predatorFlag) && (*it1)->canEat(**it2) ) //it1 can eat it2
					victims.push_back(it2);

				if ((*it2)->canEat(**it1)) //it2 can eat it1
					predators.push_back(it2);
			}
		}

		
		if (predators.empty()) //it1 is not a victim
		{
			if (!victims.empty())
			{
				auto theNearestIt = (*it1)->whoIsCloser(victims);
				events.push_back(new ChangeDirection(*it1, **theNearestIt));
				(*it1)->predatorFlag = true;
				(*it1)->victim = *theNearestIt;
			}					
		}
		else //it1 is a victim
		{
			auto theNearestIt = (*it1)->whoIsCloser(predators);
			events.push_back(new ChangeDirection(*it1, **theNearestIt));
			(*it1)->victimFlag = true;
		}

		
		if ((*it1)->isOutsideTheSimulation(lowerBorder, upperBorder))
		{
			if ((*it1)->victimFlag || (*it1)->predatorFlag)
				events.push_back(new StopModeling());
			else
				events.push_back(new DeleteObject(*it1));
		}
	}
}



void Model::deleteAnimals() {
	for (auto it = animals.begin(); it != animals.end();) {
		if ((*it)->deleteFlag)
		{
			switch ((*it)->id)
			{
				case DID: { --D; break; }
				case SID: { --S; break; }
				case FID: { --F; break; }
				case HID: { --H; break; }
				default: break;
			}
			it = animals.erase(it);
		}
		else
			++it;
	}
}



bool Model::execution() {
	bool stop = false;
	for (auto it = events.begin(); it != events.end(); ++it)
	{
		if (dynamic_cast<StopModeling*>(*it))
			stop = true;

		(*it)->handle();
		delete (*it);
	}

	events.clear();
	return stop;
}



void Model::run() {
	fillInTheFields();
	int i = 0;

	if (N)
	{
		for (i = 1; ; i++)
		{
			displacement();
			analysis(i);
			if (execution())
				break;
		}

		deleteAnimals();
	}
	
	readWrite.write(D, DS, S, SS, F, FS, H, HS, i, animals);
}
