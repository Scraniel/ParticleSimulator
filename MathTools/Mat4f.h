#ifndef MAT4F_H
#define MAT4F_H

#define MAT4F_DIM 4
#define MAT4F_NUM_ELEM 16

#include <cassert>
#include <memory>
#include <initializer_list>
#include <array>
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "../MathTools/Vec3f.h"

// Stores a 4 by 4 Matrix in Row Major order.
// When passing to glUniform4x4fv, turn on transpose.

class Mat4f
{

public:
    typedef std::array< float, MAT4F_NUM_ELEM > ARRAY_16f;
    typedef std::unique_ptr< ARRAY_16f > Mat4fHandle;

public:
	explicit Mat4f();
	
	// not explicit, so Mat4f m = {1,...,16};
	Mat4f( std::initializer_list< float > list );
    // if passing in already existing array
    Mat4f( ARRAY_16f const & array );
    // Mat4f m = { {1,2,3,4}, {5,6,7,8},...,{13,14,15,16} };
    Mat4f( std::initializer_list< std::initializer_list< float > > list );

	// Move constructor
	Mat4f( Mat4f&& moved );
	// Copy Constructor
	Mat4f( const Mat4f & copied );
	~Mat4f();


    float & at( int row, int column );
	float & operator()( int row, int column );
    float & at( int element );
	float & operator[]( int element );

    float at( int row, int column ) const;
    float at( int element ) const;
	float operator()( int row, int column ) const;
	float operator[]( int element ) const;

	Mat4f operator+( Mat4f other ) const;
	Mat4f operator*( const Mat4f & other ) const;
	Mat4f operator*( float scalar ) const;

    // assigment operator
	Mat4f & operator=( const Mat4f & copied );
    // move-assignment operator
	Mat4f & operator=( Mat4f && moved );

	bool isValidDimIndex( int idx ) const;
	bool isValidElementIndex( int idx ) const;

	ARRAY_16f::iterator begin();
	ARRAY_16f::iterator end();
	ARRAY_16f::const_iterator begin() const;
	ARRAY_16f::const_iterator end() const;

	float const * data() const;
		
private:
	Mat4fHandle m_ptr;

};

std::ostream & operator<<( std::ostream &, const Mat4f & mat );


#endif // MAT4F_H
