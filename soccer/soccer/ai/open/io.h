#ifndef _soccer_io_h_
#define _soccer_io_h_

#include "Move.h"
#include <string>
#include <memory>

namespace soccer { namespace ai { namespace open {

std::unique_ptr<Move> load(const std::string& fileName);
void save(std::unique_ptr<Move> move, const std::string& fileName);

} } }

#endif
