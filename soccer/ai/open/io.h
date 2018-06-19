#ifndef _soccer_io_h_
#define _soccer_io_h_

#include "Move.h"
#include <string>

namespace soccer { namespace ai { namespace open {

const Move* load(const std::string& fileName);
void save(Move* move, const std::string& fileName);

} } }

#endif