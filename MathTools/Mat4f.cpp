#include "Mat4f.h"

// ====== CONSTRUCTORS (MOVE/COPY) / DESTRUCTORS ============================//
Mat4f::Mat4f()
{
	Mat4fHandle tmp ( new ARRAY_16f );
	m_ptr = std::move( tmp );	//take ownership
}

Mat4f::Mat4f( std::initializer_list< float > list )
{
	assert( list.size() == MAT4F_NUM_ELEM );	
	Mat4fHandle tmp ( new ARRAY_16f );
	std::copy_n( 	list.begin(), 		//source
			MAT4F_NUM_ELEM, 	//number of copies
			tmp->begin() );		//destination

	m_ptr = std::move( tmp );		//take ownership
}

Mat4f::Mat4f( std::initializer_list< std::initializer_list< float > > list )
{
    assert( list.size() == MAT4F_DIM ); // 4 rows

    Mat4fHandle tmp ( new ARRAY_16f );

    int rowCounter = 0;
    for( auto const & row : list )
    {
        assert( row.size() == MAT4F_DIM );
        std::copy(  row.begin(),
                    row.end(),
                    tmp->begin() + (MAT4F_DIM * rowCounter) );
        ++rowCounter;
    }

    m_ptr = std::move( tmp );
}

Mat4f::Mat4f( ARRAY_16f const & array )
{
    Mat4fHandle tmp( new ARRAY_16f( array ) );
    m_ptr = std::move( tmp );
}

Mat4f::Mat4f( Mat4f && moved )
{
	m_ptr = std::move( moved.m_ptr );	//take ownership
}

Mat4f::Mat4f( const Mat4f & copied )
{
	Mat4fHandle tmp ( new ARRAY_16f );
	std::copy_n( 	copied.begin(), 	//source
			MAT4F_NUM_ELEM, 	//number of copies
			tmp->begin() );		//destination 

	m_ptr = std::move( tmp ); 		//take ownership
}

Mat4f::~Mat4f()
{
    //unique_ptr m_ptr takes care of clean up :)    
}
// ==========================================================================//

// =========== OPERATORS ====================================================//

Mat4f & Mat4f::operator=( const Mat4f & copied )
{
	if( this != &copied )
	{
		Mat4f tmp( copied );
		*this = std::move( tmp );
	}
	return *this;
}

Mat4f & Mat4f::operator=( Mat4f && moved )
{
	m_ptr = std::move( moved.m_ptr );
	return *this;
}

// With bounds check
float & Mat4f::at( int row, int column )
{
	assert( isValidDimIndex( row ) && isValidDimIndex( column ) );
	return m_ptr->operator[]( row*MAT4F_DIM + column ); 
}
float Mat4f::at( int row, int column ) const
{
	assert( isValidDimIndex( row ) && isValidDimIndex( column ) );
	return m_ptr->operator[]( row*MAT4F_DIM + column ); 
}
float & Mat4f::at( int element )
{
	assert( isValidElementIndex( element ) );
	return m_ptr->operator[]( element );
}
float Mat4f::at( int element ) const
{
	assert( isValidElementIndex( element ) );
	return m_ptr->operator[]( element );
}

// Without bounds check... some speed up
float & Mat4f::operator()( int row, int column )
{
	return m_ptr->operator[]( row*MAT4F_DIM + column ); 
}
float Mat4f::operator()( int row, int column ) const
{
	return m_ptr->operator[]( row*MAT4F_DIM + column );
}
float & Mat4f::operator[]( int element )
{
	return m_ptr->operator[]( element );
}
float Mat4f::operator[]( int element ) const
{
	return m_ptr->operator[]( element );
}


Mat4f Mat4f::operator+( Mat4f other ) const
{
	std::transform(	m_ptr->begin(),
			m_ptr->end(),
			other.m_ptr->begin(),
			other.m_ptr->begin(),
			[]( float left, float right )
			{
				return left + right;
			}
		);
	return other;
}

Mat4f Mat4f::operator*( const Mat4f & other ) const
{
	Mat4f result;

	float element;
	for( int i = 0; i < MAT4F_DIM; ++i )
	{
		for( int j = 0; j < MAT4F_DIM; ++j )
		{
			element = 0;
			for( int k = 0; k < MAT4F_DIM; ++k )
			{
			 	element += (*this)( i, k )*other( k, j );
			}
			result( i, j ) = element;
		}
	}

	return result;
}

Mat4f Mat4f::operator*( float scalar ) const
{
	Mat4f result( *this );	
	std::transform( result.m_ptr->begin(),
			result.m_ptr->end(),
			result.m_ptr->begin(),
			[ &scalar ]( float f )
			{
				return f*scalar;
			}
		);	

	return result;
}

// ==========================================================================//

float const * Mat4f::data() const
{
	return m_ptr->data();
}

Mat4f::ARRAY_16f::iterator Mat4f::begin()
{
	return m_ptr->begin();
}

Mat4f::ARRAY_16f::iterator Mat4f::end()
{
	return m_ptr->end();
}

Mat4f::ARRAY_16f::const_iterator Mat4f::begin() const
{
	return m_ptr->begin();
}

Mat4f::ARRAY_16f::const_iterator Mat4f::end() const
{
	return m_ptr->end();
}

bool Mat4f::isValidDimIndex( int idx ) const
{
	return idx >= 0 && idx < MAT4F_DIM;
}
bool Mat4f::isValidElementIndex( int idx ) const
{
	return idx >= 0 && idx < MAT4F_NUM_ELEM;
}

std::ostream & operator<<( std::ostream & out, const Mat4f & mat )
{
	std::ostream_iterator<int> out_it (out," ");
  	std::copy ( mat.begin(), mat.end(), out_it );
	return out;
}



