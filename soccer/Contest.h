#ifndef _Soccer_Contest_h_
#define _Soccer_Contest_h_

#include "Judge.h"
#include "Ai.h"
#include <vector>
#include <ostream>

namespace soccer {

class Contest
{
  public:
  	Contest();
  	~Contest();
  	void addAi(const char* name, Ai* ai);
  	void run(int repetitions);
  	
	friend std::ostream& operator<<(std::ostream& out, const Contest& contest);
 
  private:
  	int& getWins_(int i, int j);
  	int getWins_(int i, int j) const;
  
  	std::vector<Ai*> ais_;
  	std::vector<int> wins_;
  	int repetitions_;
  	std::vector<const char*> names_;
};
  	
std::ostream& operator<<(std::ostream& out, const Contest& contest);

}

#endif