//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 27-09-2013
//		Date update	: 29-09-2013
//		Comment		:
//=============================================================================
#include <QDebug>

#include "data_model_ad.h"
#include "data_adapter_ad.h"

namespace mac_mediator
{

//#############################################################################
//			class data_model_ad
//#############################################################################

	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	///------------------------------------------------------------------------
	///	data_model_ad( )
	///
	data_model_ad::data_model_ad( QObject *pobj/* = 0*/ ) :
		QAbstractTableModel( pobj )
	{
		this->initialize( );
	}

	///------------------------------------------------------------------------
	///	~data_model_ad( )
	///
	data_model_ad::~data_model_ad( )
	{
		this->clear( );

		qDebug( ) << "data_model_ad cleared correctly";
	}

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	///------------------------------------------------------------------------
	///	administrative_division( int i_row )
	///
	const data_ad* data_model_ad::administrative_division( int i_row ) const
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
	void data_model_ad::clear( )
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
	void data_model_ad::initialize( )
	{
		this->init_columns_header( );
	}

	///------------------------------------------------------------------------
	///	refresh( const QVector<QVector<QVariant> > &data )
	///
	void data_model_ad::refresh(const QVector<QVector<QVariant> > &data)
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
			data_ad *ad = new data_ad( *iter );
			this->_list.append( ad );
		}
		this->endInsertRows( );
	}

	//-------------------------------------------------------------------------
	void data_model_ad::refresh( data_ad_collection *data )
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
	QVariant data_model_ad::data(
										const QModelIndex &index,
										int /*role //= Qt::DisplayRole*/
									   ) const
	{
		if( !index.isValid( ) )
		{
			return QVariant( );
		}
		data_ad* ad = this->_list.at( index.row( ) );

		switch( index.column( ) )
		{
			case 0:
				return ad->ad_id( );
			case 1:
				return ad->ad_title( );
			default:
				return QVariant( );
		}
		return QVariant( );
	}

	///------------------------------------------------------------------------
	/// virtual
	///	setData( )
	///
	bool data_model_ad::setData(
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
	Qt::ItemFlags data_model_ad::flags(const QModelIndex &/*index*/) const
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

	///------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	///
	bool data_model_ad::insertRows(
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
			data_ad* ad = new data_ad;
			this->_list.insert( row + i, ad );
		}

		this->endInsertRows( );

		return true;
	}

	///------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	///
	bool data_model_ad::removeRows(
								int row, int count,
								const QModelIndex &parent //= QModelIndex( )
										 )
	{
		this->beginRemoveRows( parent, row, row + count - 1 );

		for( int i = 0; i < count; ++i )
		{
			data_ad *item = this->_list.takeAt( row );
			delete item;
		}

		this->endRemoveRows( );

		return true;
	}

}//namespace mac_mediator
