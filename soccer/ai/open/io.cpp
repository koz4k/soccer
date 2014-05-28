#include "io.h"
#include "../../GameState.h"
#include "MyMove.h"
#include "YourMove.h"
#include <fstream>

namespace soccer { namespace ai { namespace open {
	
const Move* loadMove(std::istream& stream);
void saveMove(const Move* move, std::ostream& stream);

const Move* load(const std::string& fileName)
{
	std::ifstream stream(fileName);
	return loadMove(stream);
}

void save(Move* move, const std::string& fileName)
{
	std::ofstream stream(fileName);
	saveMove(move, stream);
}

const Move* loadMove(std::istream& stream)
{
	Direction dir = DIR_END;
	stream >> dir;
	
	if(dir != DIR_HUBBA_BUBBA)
	{
		if(dir != DIR_END)
			return new MyMove(dir, loadMove(stream));
		else
			return nullptr;
	}
	else
	{
		YourMove* move = new YourMove();
		for(Direction dir = DIR_BEGIN; dir < DIR_END; ++dir)
			move->setMove(dir, loadMove(stream));
		return move;
	}
}

void saveMove(const Move* move, std::ostream& stream)
{
	if(!move)
	{
		stream << DIR_END << " ";
	}
	else if(move->isMyTurn())
	{
		stream << ((MyMove*) move)->getDirection() << " ";
		saveMove(((MyMove*) move)->advance(), stream);
	}
	else
	{
		stream << DIR_HUBBA_BUBBA << " ";
		for(Direction dir = DIR_BEGIN; dir < DIR_END; ++dir)
			saveMove(((YourMove*) move)->advance(dir), stream);
	}
}

} } }