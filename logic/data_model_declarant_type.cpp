///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 31-01-2014
///		Date update	: 31-01-2014
///		Comment		:
/// ============================================================================
#include <QDebug>

#include "data_model_declarant_type.h"
#include "data_adapter_declarant_type.h"

namespace mac_mediator
{

///#############################################################################
///			class data_model_declarant_type
///#############################################################################

    ///=========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    ///=========================================================================
	///------------------------------------------------------------------------
    ///	data_model_declarant_type( )
	///
    data_model_declarant_type::data_model_declarant_type( QObject *pobj/* = 0*/ ) :
		QAbstractTableModel( pobj )
	{
		this->initialize( );
	}

	///------------------------------------------------------------------------
    ///	~data_model_declarant_type( )
	///
    data_model_declarant_type::~data_model_declarant_type( )
	{
		this->clear( );

        qDebug( ) << "data_model_declarant_type cleared correctly";
	}

    ///=========================================================================
    ///		PROPERTIES
    ///=========================================================================
	///------------------------------------------------------------------------
    ///	declarant_type( int i_row )
	///
    const data_declarant_type* data_model_declarant_type::declarant_type( int i_row ) const
	{
		if( i_row < 0 || i_row >= this->_list.size( ) )
		{
			return 0;
		}
		return this->_list.at( i_row );
	}

    ///=========================================================================
	//		FUNCTIONS
    ///=========================================================================
	///------------------------------------------------------------------------
	///	clear( )
	///
    void data_model_declarant_type::clear( )
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
    void data_model_declarant_type::initialize( )
	{
		this->init_columns_header( );
	}

	///------------------------------------------------------------------------
	///	refresh( const QVector<QVector<QVariant> > &data )
	///
    void data_model_declarant_type::refresh(const QVector<QVector<QVariant> > &data)
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
            data_declarant_type *declarant_type = new data_declarant_type( *iter );
            this->_list.append( declarant_type );
		}
		this->endInsertRows( );
	}

	//-------------------------------------------------------------------------
    void data_model_declarant_type::refresh( data_declarant_type_collection *data )
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
    QVariant data_model_declarant_type::data(
										const QModelIndex &index,
										int /*role //= Qt::DisplayRole*/
									   ) const
	{
		if( !index.isValid( ) )
		{
			return QVariant( );
		}
        data_declarant_type* declarant_type = this->_list.at( index.row( ) );

		switch( index.column( ) )
		{
            case data_declarant_type::num_field_id:
                return declarant_type->id_declarant_type( );
            case data_declarant_type::num_field_title:
                return declarant_type->declarant_type_title( );
			default:
				return QVariant( );
		}
		return QVariant( );
	}

	///------------------------------------------------------------------------
	/// virtual
	///	setData( )
	///
    bool data_model_declarant_type::setData(
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
    Qt::ItemFlags data_model_declarant_type::flags(const QModelIndex &/*index*/) const
	{
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}

	///------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	///
    bool data_model_declarant_type::insertRows(
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
            data_declarant_type* declarant_type = new data_declarant_type;
            this->_list.insert( row + i, declarant_type );
		}

		this->endInsertRows( );

		return true;
	}

	///------------------------------------------------------------------------
	/// virtual
	///	insertRows( )
	///
    bool data_model_declarant_type::removeRows(
								int row, int count,
								const QModelIndex &parent //= QModelIndex( )
										 )
	{
		this->beginRemoveRows( parent, row, row + count - 1 );

		for( int i = 0; i < count; ++i )
		{
            data_declarant_type *item = this->_list.takeAt( row );
			delete item;
		}

		this->endRemoveRows( );

		return true;
	}

}//namespace mac_mediator
