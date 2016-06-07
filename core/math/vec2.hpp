#pragma once

namspace math {

class vec2 {
public:
	double x, y;
public:
	vec2();
	vec2(double v);
	vec2(double x_init, double y_init);

	vec2 operator-() const;
	vec2 operator+() const;

	vec2 operator+(vec2 other) const;
	vec2 operator-(vec2 other) const;
	vec2 operator*(vec2 other) const;

	vec2 operator*(double scale) const;
	vec2 operator/(double scale) const;
	friend vec2 operator*(double scale, vec2 vec);
	friend vec2 operator/(double scale, vec2 vec);

	vec2& operator+=(const vec2& other);
	vec2& operator-=(const vec2& other);
	vec2& operator*=(const vec2& other);

	vec2& operator*=(double scale);
	vec2& operator/=(double scale);

	double dist() const;
	double dot(const vec2& other) const;
	vec2 norm() const;
	vec2 abs() const;
};

}
