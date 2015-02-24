//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 27-09-2013
//		Date update	: 27-09-2013
//		Comment		:
//=============================================================================

#ifndef __DATA_MODEL_REQUEST_TYPE_H__
#define __DATA_MODEL_REQUEST_TYPE_H__

#include <QAbstractTableModel>
#include <QList>
#include <QVector>

namespace mac_mediator
{

	class data_request_type;
	class data_request_type_collection;
//#############################################################################
//			class data_model_request_type
//#############################################################################
	class data_model_request_type : public QAbstractTableModel
	{

	Q_OBJECT
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		data_model_request_type( QObject* pobj = 0 );
	//-------------------------------------------------------------------------
		virtual ~data_model_request_type( );

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		const data_request_type* request_type( int i_row ) const;

	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		data_model_request_type& operator=( const data_model_request_type &rhs );

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		virtual void initialize( void );
	//-------------------------------------------------------------------------
		virtual void init_columns_header( void )
		{
			this -> _header.append( QObject::tr( "id" ) );
			this -> _header.append( QObject::tr( "request type" ) );
		}

	public:
	//-------------------------------------------------------------------------
		void clear( );
	//-------------------------------------------------------------------------
		void refresh( const QVector<QVector<QVariant> > &data );
	//-------------------------------------------------------------------------
		void refresh( data_request_type_collection *data );
	//-------------------------------------------------------------------------
	//override
		virtual int rowCount(
								const QModelIndex &/*parent = QModelIndex( )*/
							) const
		{
			return this -> _list.size( );
		}
	//-------------------------------------------------------------------------
	//override
		virtual int columnCount(
								const QModelIndex &/*parent = QModelIndex( )*/
							   ) const
		{
			return this -> _header.size( );
		}
	//-------------------------------------------------------------------------
	//override
		virtual QVariant headerData(
									int section,
									Qt::Orientation orientation,
									int role/* = Qt::DisplayRole*/
								   ) const
		{
			if( role != Qt::DisplayRole )
			{
				return QVariant( );
			}
			if(
				( section > this -> _header.size( ) ) ||
				( section < 0 )
			  )
			{
				return QVariant( );
			}

			return ( orientation == Qt::Horizontal )
					? ( this -> _header )[section]
					: " ";
		}
	//-------------------------------------------------------------------------
	//override
		virtual Qt::ItemFlags flags( const QModelIndex &index ) const;
	//-------------------------------------------------------------------------
	//override
		virtual QVariant data(
								const QModelIndex & index,
								int role = Qt::DisplayRole
							 ) const;
	//-------------------------------------------------------------------------
	//override
		virtual bool setData(
								const QModelIndex & index,
								const QVariant & value,
								int role = Qt::EditRole
							 );
	//-------------------------------------------------------------------------
	//override
		virtual bool insertRows(
								int row, int count,
								const QModelIndex &parent = QModelIndex( )
							   );
	//-------------------------------------------------------------------------
	//override
		virtual bool removeRows(
								int row, int count,
								const QModelIndex &parent = QModelIndex( )
							   );

	//=========================================================================
	//		SLOTS
	//=========================================================================
	private:
	//-------------------------------------------------------------------------

	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
		QList<data_request_type*>   _list;
		QVector<QString>            _header;

	};//class data_model_request_type
//#############################################################################

}//namespace mac_mediator

#endif // __DATA_MODEL_REQUEST_TYPE_H__
