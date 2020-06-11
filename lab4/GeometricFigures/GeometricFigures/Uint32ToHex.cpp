#include <iomanip>
#include <sstream>

std::string Uint32ToHexString(uint32_t value)
{
	std::stringstream stream;
	stream << std::hex << value;
	return stream.str();
}
