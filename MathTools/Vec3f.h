#ifndef VEC3F_H
#define VEC3F_H

#include <iostream> 	// std::{cout, endl, etc.}
#include <cmath> 	// std::{sqrt, abs, etc.}
#include <algorithm>    // std::swap

class Vec3f
{
public:
	explicit Vec3f( float x = 0, float y = 0, float z = 0 );
	//Vec3f( Vec3f const & other ); // copy constructor maybe?

	// Getter/Setter
	float x() const;
	float y() const;
	float z() const;
	void x( float x );
	void y( float y );
	void z( float z );
    float & operator[]( size_t idx );
    float operator[]( size_t idx ) const;

	// Usefull Member Functions
	Vec3f normalized() const;
	void normalize();
	float length() const;
	float lengthSquared() const;
	float distance( Vec3f const & other ) const;
	float dotProduct( Vec3f const & other ) const;
	Vec3f crossProduct( Vec3f const & other ) const;
	Vec3f projectOnto( Vec3f const & other ) const;

	// Usefull Member Operators
	Vec3f operator * ( float factor ) const;
	Vec3f operator + ( const Vec3f & other ) const;	
	Vec3f operator - ( const Vec3f & other ) const;
	Vec3f & operator = ( Vec3f other ); // assignment operator
    void operator += ( const Vec3f & other );
	void operator -= ( const Vec3f & other );
	void operator *= ( float factor );

    // Dot Product //
    float operator * ( Vec3f const & other ) const;
    // Cross Product // 
    Vec3f operator ^ ( Vec3f const & other ) const;


	friend void swap( Vec3f & l, Vec3f & r );

private:
    // anonymous union/struct hackery
    // so that m_x has same mem space as m_coord[0] and
    // vise-versa, and same for other coords
    union
    {
        struct{ float m_x, m_y, m_z; };
        float m_coord[3];
    };
        
};


std::ostream & operator<<( std::ostream & out, Vec3f const & vec );

#endif // Vec3f
