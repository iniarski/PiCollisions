#include <iostream>
#include <math.h>
#include <iomanip>

#include <chrono>
#include <sys/time.h>
#include <ctime>

// Two blocks with mass ratio 1 : 100 ^ n (n being natural number),
// the bigger block having initial velocity v,
// collide perfectly elasticaly with eachother, and immovable wall
// on a frictionless surface

// The number of total collision will spell out the begiging n decimal places of the number Pi

// For example, for mass ratio 1 : 10 000 (100^2)
// the total numer of collisions will be 314 as in 3,141592...
// (after that the bigger block will move towards rigth with greater velocity than the smaller one)

//   | 
//   | 
//   | 
// W | 
// A | 
// L |                         |===============|
// L |                         |               |
//   |                    _    |               |
//   |                    V    |  M = 100 ^ n  |
//   |   |=====|      <======= |               |
//   |   |  m  |               |               |
//   |   |=====|               |               |
// ==========================================================================

// Using the perfecty elastic collision formula

//                (m1 - m2) * v1 + 2 * m2 * v2
//          Vf =  ----------------------------
//                          m1 + m2

// We can approximate the number Pi

// At about n = 11 the floating point arithmetics make the result differ from actual number Pi

// Also the algorith is painfully inefficient having O(n) = 10 ^ n complexity
// (only a gimmick, not for real applications)

double pi(int digits){

	// Initial parameters

	double smalMass = 1;
	double biggMass = pow(100, digits);
	double smalVel = 0;
	double biggVel = -16;

	double totlMass = smalMass + biggMass;

	double colCount = 0;

	while(!(smalVel < biggVel && smalVel >= 0)){ // *the end condition
		// the bigger block is moving rigth faster than the smaller one

		if(smalVel < 0){
			// Small block hitting the wall
			// and bouncing back with equal speed
			smalVel = - smalVel;
		}
		else{
			// The two blocks colliding
			double tempVel = ((smalMass - biggMass) * smalVel + 2 * biggMass * biggVel) / totlMass;
			biggVel = ((biggMass - smalMass) * biggVel + 2 * smalMass * smalVel) / totlMass;

			smalVel = tempVel;
		}
		colCount++;
	}
	return colCount / pow(10, digits);
}

int main(){
	// Using fixed decimal points
	std :: cout << std :: fixed;

	for(int i = 0; i <= 10; i ++){
		// Setting the number of decimal places
		std :: cout << std :: setprecision(i);
		// Geting start time
		auto startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		std :: cout << i << " digits of Pi calculated using the colliding blocks method : " << std :: endl;
		std :: cout << pi(i) << std :: endl;

		// Getting end time and calculating time diff in seconds
		auto endTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		float timeDiff = endTime - startTime;
		timeDiff /= 1000;
		std :: cout << std :: setprecision(3) <<  "The calculation took : " << timeDiff << "s\n\n";
	}

	return 0;
}