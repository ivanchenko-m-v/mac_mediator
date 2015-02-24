/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 27-09-2013
///		Date update	: 18-10-2013
///		Comment		:
/// ============================================================================
#include <QDebug>

#include "data_model_request.h"
#include "data_adapter_request.h"

namespace mac_mediator
{

/// ############################################################################
///			class data_model_request
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	data_model_request( )
	/// ------------------------------------------------------------------------
	data_model_request::data_model_request( QObject *pobj/* = 0*/ ) :
		QAbstractTableModel( pobj )
	{
		this->initialize( );
	}

	/// ------------------------------------------------------------------------
	///	~data_model_request( )
	/// ------------------------------------------------------------------------
	data_model_request::~data_model_request( )
	{
		this->clear( );

		qDebug( ) << "data_model_request cleared correctly";
	}

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	request( int i_row )
	/// ------------------------------------------------------------------------
	const data_request* data_model_request::request( int i_row ) const
	{
		if( i_row < 0 || i_row >= this->_list.size( ) )
		{
			return 0;
		}
		return this->_list.at( i_row );
	}

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	clear( )
	/// ------------------------------------------------------------------------
	void data_model_request::clear( )
	{
        if( !this->_list.size( ) )
        {
            return;
        }
		this->removeRows( 0, this->_list.size( ) );
		this->_list.clear( );
	}

	/// ------------------------------------------------------------------------
	///	initialize( )
	/// ------------------------------------------------------------------------
	void data_model_request::initialize( )
	{
		this->init_columns_header( );
	}

	/// ------------------------------------------------------------------------
	///	refresh( const QVector<QVector<QVariant> > &data )
	/// ------------------------------------------------------------------------
	void data_model_request::refresh(const QVector<QVector<QVariant> > &data)
	{
		this->clear( );

		if( !data.count( ) )
		{
			//if no data
			return;
		}

		this->beginInsertRows( QModelIndex( ), 0, data.count( ) - 1 );

		QVector<QVector<QVariant> >::const_iterator iter;
		for( iter = data.constBegin( ); iter != data.end( ); ++iter )
		{
			data_request *request = new data_request( *iter );
			this->_list.append( request );
		}
		this->endInsertRows( );
	}

	/// ------------------------------------------------------------------------
	///	refresh( data_request_collection *data )
	/// ------------------------------------------------------------------------
	void data_model_request::refresh( data_request_collection *data )
	{
		this->clear( );

		if( !data || !data->size( ) )
		{
			//if no data
			return;
		}
		this->beginInsertRows( QModelIndex( ), 0, data->size( ) - 1 );

		this->_list.append( *( data->list( ) ) );
		data->free_data_pointer( );

        this->endInsertRows( );
    }

	/// ------------------------------------------------------------------------
	///	insert(const data_request &request)
	/// ------------------------------------------------------------------------
    void data_model_request::insert( const data_request &request )
    {
		this->beginInsertRows( QModelIndex( ), this->_list.size( ), this->_list.size( ) );

        data_request *pr = new data_request( request );
		this->_list.append( pr );

        this->endInsertRows( );
    }

	/// ------------------------------------------------------------------------
	/// virtual
	///	data( )
	/// ------------------------------------------------------------------------
	QVariant data_model_request::data(
										const QModelIndex &index,
										int /*role //= Qt::DisplayRole*/
									   ) const
	{
		if( !index.isValid( ) )
		{
			return QVariant( );
		}
		data_request* request = this->_list.at( index.row( ) );

		switch( index.column( ) )
		{
			case 0:
				return request->id_request_string( );
			//case 1:
				//return request->mediator_name( );
			case 1:
				return request->date_request( );
			//case 3:
				//return request->time_request( );
			case 2:
				return request->mr_title( );
			case 3:
				return request->request_category_title( );
			case 4:
				return request->declarant( );
			default:
				return QVariant( );
		}
		return QVariant( );
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	setData( )
	/// ------------------------------------------------------------------------
	bool data_model_request::setData(
										const QModelIndex &/*index*/,
										const QVariant &/*value*/,
										int /*role //= Qt::EditRole*/
									  )
	{
		return false;
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	flags( )
	/// ------------------------------------------------------------------------
	Qt::ItemFlags data_model_request::flags(const QModelIndex &/*index*/) const
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	/// ------------------------------------------------------------------------
	bool data_model_request::insertRows(
								int row, int count,
								const QModelIndex &parent //= QModelIndex( )
										 )
	{
		if( ( row < 0 ) || ( row > this->_list.size( ) ) )
		{
			return false;
		}

		this->beginInsertRows( parent, row, row + count - 1 );

		for( int i = 0; i < count; i++ )
		{
			data_request* request = new data_request;
			this->_list.insert( row + i, request );
		}

		this->endInsertRows( );

		return true;
	}

	/// ------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	/// ------------------------------------------------------------------------
	bool data_model_request::removeRows(
								int row, int count,
								const QModelIndex &parent //= QModelIndex( )
										 )
	{
		this->beginRemoveRows( parent, row, row + count - 1 );

		for( int i = 0; i < count; ++i )
		{
			data_request *item = this->_list.takeAt( row );
			delete item;
		}

		this->endRemoveRows( );

		return true;
	}

}//namespace mac_mediator
