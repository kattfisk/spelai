#ifndef INLUPP_POSITION
#define INLUPP_POSITION

#include <cstdlib>

struct Position
{
	inline Position() : x(0), y(0) {}
	inline Position(int x, int y) { this->x = x; this->y = y; }
	inline int distance_to(const Position &other) const { return std::abs(x - other.x) + std::abs(y - other.y); }
	int x, y;
};

inline bool operator==(const Position &lhs, const Position &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; };
inline bool operator!=(const Position &lhs, const Position &rhs) { return !(lhs == rhs); };

#endif // INLUPP_POSITION
