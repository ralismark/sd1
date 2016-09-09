#pragma once

#include "gvec.hpp"

#include <ostream>

template <typename T>
class rect
{
public: // Statics
#pragma clang diagnostic push

#pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#pragma clang diagnostic ignored "-Wnested-anon-types"
	struct access {
		union {
			struct {
				T x1, y1;
			};
			gvec<T, 2> min;
		};
		union {
			struct {
				T x2, y2;
			};
			gvec<T, 2> max;
		};

		// Warning: following values will be reset after use

		union {
			struct {
				T w, h;
			};
			gvec<T, 2> size;
		};

		gvec<T, 2> center;

		access(const T& v1, const T& v2, const T& v3, const T& v4,
			const T& v5, const T& v6, const T& v7, const T& v8)
			: x1(v1), y1(v2), x2(v3), y2(v4)
			, w(v5), h(v6), center(make_vec<T>(v7, v8))
		{ ; }
	};
#pragma clang diagnostic pop

private: // Variables
	access ac; // From [x1, y2] to [x2, y2]
	bool dirty; // Set after access, reset on fix
public:
	bool retain_size; // fix other values based on size. evaluate this first
	bool retain_center; // fix based on center
public:
	rect();
	rect(const T& w, const T& h); // w*h from origin
	rect(const gvec<T, 2>& sz); // Same as above

	rect(const T& ox, const T& oy, const T& w, const T& h); // [ox,oy] to [ox+w,oy+h]. I agree that it is kinda inconsistent
	rect(const gvec<T, 2>& o, const gvec<T, 2>& sz); // As above

	rect(const rect<T>& other);
	rect<T>& operator=(const rect<T>& other);

	rect<T>& fix(); // Make sure values are legit

	access* operator->();
	const access* operator->() const;

	// implementation
	bool operator==(const rect<T>& other) const;
	bool operator!=(const rect<T>& other) const;

	bool contains(const gvec<T, 2>& p, bool permit_eq = false) const; // permit_eq means that true is still returned if edges overlap
	bool overlaps(const rect<T>& r, bool permit_eq = false) const; // permit_eq as with contains

	template <typename T>
	friend std::ostream& operator<<(std::ostream& os, const rect<T>& r);
};

#include "rect.tpp"
