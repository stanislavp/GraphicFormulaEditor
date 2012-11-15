//! STDEXCEPT
#include <stdexcept>

namespace Exception
{
	class IsPlainGlyph : public std::logic_error
	{
	public:
		explicit IsPlainGlyph(const std::string& what);
	};

}
