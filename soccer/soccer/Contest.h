#ifndef _soccer_Contest_h_
#define _soccer_Contest_h_

#include "Judge.h"
#include "Ai.h"
#include <functional>
#include <vector>
#include <ostream>
#include <memory>

namespace soccer {

class Contest
{
  public:
  	typedef std::function<bool(int, int)> Matches;
  
  	Contest(Matches matches, int matchTime, bool verbose = false);
  	void addAi(std::string name, std::unique_ptr<Ai> ai1, std::unique_ptr<Ai> ai2);
  	void run(int repetitions);
  	
	friend std::ostream& operator<<(std::ostream& out, const Contest& contest);
 
  private:
  	std::pair<int, int>& getData_(int i, int j);
  	std::pair<int, int> getData_(int i, int j) const;
  
  	std::vector<std::unique_ptr<Ai>> ais1_;
  	std::vector<std::unique_ptr<Ai>> ais2_;
  	Matches matches_;
	int time_;
	bool verbose_;
  	std::vector<std::pair<int, int>> data_;
  	int repetitions_;
  	std::vector<std::string> names_;
};
  	
std::ostream& operator<<(std::ostream& out, const Contest& contest);

}

#endif
