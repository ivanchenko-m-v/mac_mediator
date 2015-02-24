//$Header
//==============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 11-06-2013
//		Date update	: 19-06-2013
//		Comment		: Implementation of qt_data_parameter_collection class.
//==============================================================================
#include <QDebug>

#include <stdexcept>

#include "qt_data_parameter.h"

namespace espira
{

namespace db
{

//#############################################################################
//			class qt_data_parameter_collection
//#############################################################################
//=============================================================================
//		OPERATIONS
//=============================================================================
	///------------------------------------------------------------------------
	///	operator[]( int i_row )
    ///------------------------------------------------------------------------
    qt_sqlite_dbvalue* qt_data_parameter_collection::operator[]( int n_param )
	{
		if( !this->_data )
		{
			throw std::runtime_error(
                                "qt_data_parameter_collection not initialized"
									);
		}
        if( n_param < 0 || n_param >= this->_data->size( ) )
		{
			throw std::out_of_range(
                            "index of row qt_data_parameter_collection "
							"out of range"
								   );
		}
        return this->_data->operator[]( n_param );
	}

	///------------------------------------------------------------------------
    ///	operator<<( QDebug q_debug, const qt_data_parameter_collection &rows )
    ///------------------------------------------------------------------------
    QDebug operator<<( QDebug q_debug, const qt_data_parameter_collection &params )
	{
        if( !params._data )
		{
			return q_debug;
		}

        qt_data_parameter_collection::parameter_vector::const_iterator iter =
                                                        params._data->begin( );
        for( ; iter != params._data->end( ); ++iter )
		{
            q_debug << (*iter)->value( );
		}

		return q_debug;
	}

//=============================================================================
//		FUNCTIONS
//=============================================================================
	///------------------------------------------------------------------------
	///	free( )
    ///------------------------------------------------------------------------
    void qt_data_parameter_collection::free( )
	{
		if( !this->_data )
		{
			return;
		}
		while( this->_data->size( ) )
		{
			//get last element
            qt_sqlite_dbvalue *param = this->_data->last( );
			//remove last element from vector
			this->_data->pop_back( );
			//delete last element
            delete param;
		}
		delete _data;

		this->_data = 0;
	}

    ///------------------------------------------------------------------------
    ///	 append(  QVariant *param )
    ///------------------------------------------------------------------------
    void qt_data_parameter_collection::append( qt_sqlite_dbvalue *param )
	{
		if( !this->_data )
		{
            this->_data =  new parameter_vector;
		}
        this->_data->append( param );
	}

//class qt_data_parameter_collection

//#############################################################################
//-----------------------------------------------------------------------------
}//namespace db

}//namespace espira
