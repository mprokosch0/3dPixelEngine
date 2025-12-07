#ifndef VEC2_HPP

# define VEC2_HPP

# include <cmath>

template<typename T>
class Vec2
{
	private:
		T	_x;
		T	_y;


	public:
		Vec2(void);
		Vec2(T x, T y);
		Vec2(Vec2 const &rhs);
		~Vec2();
	
	public:
		Vec2	&operator=(Vec2 const &rhs);
		Vec2	&operator+=(Vec2 const &rhs);
		Vec2	&operator+=(T rhs);
		Vec2	&operator-=(Vec2 const &rhs);
		Vec2	&operator-=(T rhs);
		Vec2	&operator*=(Vec2 const &rhs);
		Vec2	&operator*=(T rhs);
		Vec2	&operator/=(Vec2 const &rhs);
		Vec2	&operator/=(T rhs);

		Vec2	operator+(Vec2 const &rhs) const;
		Vec2	operator+(T rhs) const;
		Vec2	operator-(Vec2 const &rhs) const;
		Vec2	operator-(T rhs) const;
		Vec2	operator*(Vec2 const &rhs) const;
		Vec2	operator*(T rhs) const;
		Vec2	operator/(Vec2 const &rhs) const;
		Vec2	operator/(T rhs) const;

		T		&operator[](int index);
		bool	operator==(Vec2 const &rhs) const;
		bool	operator!=(Vec2 const &rhs) const;
	
	public:
		T		dot(Vec2 const &rhs) const;
		T		cross(Vec2 const &rhs) const;
		void	normalize(void);
		Vec2	normalized(void);
};

# include "Vec2.tpp"

#endif