// This file is for testing out things

#include <utility>
#include "Position.h"

typedef std::pair<int, Position> p;

p foo(1, Position());
p bar(1, Position());

// This should trigger a comparison of Position which won't work because it has no operator<
//if (foo < bar)