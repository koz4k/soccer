#include "io.h"
#include "../../GameState.h"
#include "MyMove.h"
#include "YourMove.h"
#include <fstream>

namespace soccer { namespace ai { namespace open {
	
std::unique_ptr<Move> loadMove(std::istream& stream);
void saveMove(std::unique_ptr<Move> move, std::ostream& stream);

std::unique_ptr<Move> load(const std::string& fileName)
{
	std::ifstream stream(fileName);
	return loadMove(stream);
}

void save(std::unique_ptr<Move> move, const std::string& fileName)
{
	std::ofstream stream(fileName);
	saveMove(std::move(move), stream);
}

std::unique_ptr<Move> loadMove(std::istream& stream)
{
	Direction dir = DIR_END;
	stream >> dir;
	
	if(dir != DIR_HUBBA_BUBBA)
	{
		if(dir != DIR_END)
			return std::make_unique<MyMove>(dir, loadMove(stream));
		else
			return nullptr;
	}
	else
	{
		auto move = std::make_unique<YourMove>();
		for(Direction dir = DIR_BEGIN; dir < DIR_END; ++dir)
			move->setMove(dir, loadMove(stream));
		return move;
	}
}

void saveMove(std::unique_ptr<Move> move, std::ostream& stream)
{
	if(!move)
	{
		stream << DIR_END << " ";
	}
	else if(move->isMyTurn())
	{
        MyMove* myMove = (MyMove*) move.get();
		stream << myMove->getDirection() << " ";
		saveMove(myMove->advance(), stream);
	}
	else
	{
		stream << DIR_HUBBA_BUBBA << " ";
		for(Direction dir = DIR_BEGIN; dir < DIR_END; ++dir)
			saveMove(((YourMove*) move.get())->advance(dir), stream);
	}
}

} } }
