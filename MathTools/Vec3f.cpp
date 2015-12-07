#include "Vec3f.h"

Vec3f::Vec3f( float x, float y, float z ):
	m_x( x ),
	m_y( y ),
	m_z( z )
{}

// Functions
float Vec3f::length() const
{
	return std::sqrt(	m_x*m_x +
				m_y*m_y +
				m_z*m_z );
}

float Vec3f::lengthSquared() const
{
	return m_x*m_x + m_y*m_y + m_z*m_z;
}

float Vec3f::distance( Vec3f const & other ) const
{
	Vec3f tmp = *this - other; // blah... ha.
	return tmp.length();
}

float Vec3f::dotProduct( Vec3f const & other ) const
{
	return 	m_x*other.x() +
		m_y*other.y() +
		m_z*other.z();
}

Vec3f Vec3f::crossProduct( Vec3f const & other ) const
{
	return Vec3f(	(m_y * other.m_z) - (m_z * other.m_y),
			(m_z * other.m_x) - (m_x * other.m_z),
			(m_x * other.m_y) - (m_y * other.m_x) );
}

Vec3f Vec3f::normalized() const
{
	if(this->x() == 0 && this->y() == 0 && this->z() == 0)
		return *this;
	Vec3f v( *this );
	v.normalize();
	return v;
}

void Vec3f::normalize()
{
	float len = length();
	// Check if zero?
	m_x /= len;
	m_y /= len;
	m_z /= len;
}

Vec3f Vec3f::projectOnto( Vec3f const & other ) const
{
	float scaleRatio = dotProduct( other )/lengthSquared(); 
	return other * scaleRatio;
}

// Operators //

float Vec3f::operator * ( Vec3f const & other ) const
{
    return dotProduct( other );
}

Vec3f Vec3f::operator ^ ( Vec3f const & other ) const
{
    return crossProduct( other );
}

Vec3f & Vec3f::operator = ( Vec3f other ) 
{
	swap( other, *this );
	return *this;
}

Vec3f Vec3f::operator + ( Vec3f const & other ) const 
{
	return Vec3f(
		m_x + other.x(),
		m_y + other.y(),
		m_z + other.z());
}

Vec3f Vec3f::operator - ( Vec3f const & other ) const 
{
	return Vec3f(
		m_x - other.x(),
		m_y - other.y(),
		m_z - other.z());
}

Vec3f Vec3f::operator * ( float factor) const 
{
	return Vec3f(
		m_x * factor,
		m_y * factor,
		m_z * factor);
}

void swap( Vec3f & l, Vec3f & r )
{
	std::swap( l.m_x, r.m_x );
	std::swap( l.m_y, r.m_y );
	std::swap( l.m_z, r.m_z );		
}

std::ostream & operator << ( std::ostream & out, Vec3f const & vec )
{
	return out << vec.x() << " " << vec.y() << " " << vec.z();
}

// Getter/Setter Junk

float & Vec3f::operator[]( size_t idx )
{
    // skip bounds check for speed
    return m_coord[idx];
}

float Vec3f::operator[]( size_t idx ) const
{
    // skip bounds check for speed
    return m_coord[idx];
}

float Vec3f::x() const
{
	return m_x;
}

void Vec3f::x( float x )
{
	m_x = x;
}

float Vec3f::y() const
{
	return m_y;
}

void Vec3f::y( float y )
{
	m_y = y;
}

float Vec3f::z() const
{
	return m_z;
}

void Vec3f::z( float z )
{
	m_z = z;
}
