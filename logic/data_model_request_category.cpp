//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 27-09-2013
//		Date update	: 01-10-2013
//		Comment		:
//=============================================================================
#include <QDebug>

#include "data_model_request_category.h"
#include "data_adapter_request_category.h"

namespace mac_mediator
{

//#############################################################################
//			class data_model_request_category
//#############################################################################

	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	///------------------------------------------------------------------------
	///	data_model_request_category( )
	///
	data_model_request_category::data_model_request_category( QObject *pobj/* = 0*/ ) :
		QAbstractTableModel( pobj )
	{
		this->initialize( );
	}

	///------------------------------------------------------------------------
	///	~data_model_request_category( )
	///
	data_model_request_category::~data_model_request_category( )
	{
		this->clear( );

		qDebug( ) << "data_model_request_category cleared correctly";
	}

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	///------------------------------------------------------------------------
	///	request_category( int i_row )
	///
	const data_request_category* data_model_request_category::request_category( int i_row ) const
	{
		if( i_row < 0 || i_row >= this->_list.size( ) )
		{
			return 0;
		}
		return this->_list.at( i_row );
	}

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	///------------------------------------------------------------------------
	///	clear( )
	///
	void data_model_request_category::clear( )
	{
        if( !this->_list.size( ) )
        {
            return;
        }
		this->removeRows( 0, this->_list.size( ) );
		this->_list.clear( );
	}

	///------------------------------------------------------------------------
	///	initialize( )
	///
	void data_model_request_category::initialize( )
	{
		this->init_columns_header( );
	}

	///------------------------------------------------------------------------
	///	refresh( const QVector<QVector<QVariant> > &data )
	///
	void data_model_request_category::refresh(const QVector<QVector<QVariant> > &data)
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
			data_request_category *request_category = new data_request_category( *iter );
			this->_list.append( request_category );
		}
		this->endInsertRows( );
	}

	//-------------------------------------------------------------------------
	void data_model_request_category::refresh( data_request_category_collection *data )
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

	///------------------------------------------------------------------------
	/// virtual
	///	data( )
	///
	QVariant data_model_request_category::data(
										const QModelIndex &index,
										int /*role //= Qt::DisplayRole*/
									   ) const
	{
		if( !index.isValid( ) )
		{
			return QVariant( );
		}
		data_request_category* request_category = this->_list.at( index.row( ) );

		switch( index.column( ) )
		{
			case 0:
				return request_category->request_category_id( );
			case 1:
				return request_category->request_category( );
			default:
				return QVariant( );
		}
		return QVariant( );
	}

	///------------------------------------------------------------------------
	/// virtual
	///	setData( )
	///
	bool data_model_request_category::setData(
										const QModelIndex &/*index*/,
										const QVariant &/*value*/,
										int /*role //= Qt::EditRole*/
									  )
	{
		return false;
	}

	///------------------------------------------------------------------------
	/// virtual
	///	flags( )
	///
	Qt::ItemFlags data_model_request_category::flags(const QModelIndex &/*index*/) const
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

	///------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	///
	bool data_model_request_category::insertRows(
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
			data_request_category* request_category = new data_request_category;
			this->_list.insert( row + i, request_category );
		}

		this->endInsertRows( );

		return true;
	}

	///------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	///
	bool data_model_request_category::removeRows(
								int row, int count,
								const QModelIndex &parent //= QModelIndex( )
										 )
	{
		this->beginRemoveRows( parent, row, row + count - 1 );

		for( int i = 0; i < count; ++i )
		{
			data_request_category *item = this->_list.takeAt( row );
			delete item;
		}

		this->endRemoveRows( );

		return true;
	}

}//namespace mac_mediator
