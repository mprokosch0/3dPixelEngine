#ifndef VEC3_HPP

# define VEC3_HPP

# include <cmath>

template<typename T>
class Vec3
{
	private:
		T	_x;
		T	_y;
		T	_z;

	public:
		Vec3(void);
		Vec3(T x, T y, T z);
		Vec3(Vec3 const &rhs);
		~Vec3();
	
	public:
		Vec3	&operator=(Vec3 const &rhs);
		Vec3	&operator+=(Vec3 const &rhs);
		Vec3	&operator+=(T rhs);
		Vec3	&operator-=(Vec3 const &rhs);
		Vec3	&operator-=(T rhs);
		Vec3	&operator*=(Vec3 const &rhs);
		Vec3	&operator*=(T rhs);
		Vec3	&operator/=(Vec3 const &rhs);
		Vec3	&operator/=(T rhs);

		Vec3	operator+(Vec3 const &rhs) const;
		Vec3	operator+(T rhs) const;
		Vec3	operator-(Vec3 const &rhs) const;
		Vec3	operator-(T rhs) const;
		Vec3	operator*(Vec3 const &rhs) const;
		Vec3	operator*(T rhs) const;
		Vec3	operator/(Vec3 const &rhs) const;
		Vec3	operator/(T rhs) const;

		T		&operator[](int index);
		bool	operator==(Vec3 const &rhs) const;
		bool	operator!=(Vec3 const &rhs) const;
	
	public:
		T		dot(Vec3 const &rhs) const;
		Vec3	cross(Vec3 const &rhs) const;
		void	normalize(void);
		Vec3	normalized(void);
};

# include "Vec3.tpp"

#endif