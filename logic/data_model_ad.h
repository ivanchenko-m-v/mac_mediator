//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 27-09-2013
//		Date update	: 01-10-2013
//		Comment		:
//=============================================================================

#ifndef __DATA_MODEL_AD_H__
#define __DATA_MODEL_AD_H__

#include <QAbstractTableModel>
#include <QList>
#include <QVector>

namespace mac_mediator
{

	class data_ad;
	class data_ad_collection;
    typedef QList<data_ad*> data_ad_list;
//#############################################################################
//			class data_model_ad
//#############################################################################
	class data_model_ad : public QAbstractTableModel
	{

	Q_OBJECT
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		data_model_ad( QObject* pobj = 0 );
	//-------------------------------------------------------------------------
		virtual ~data_model_ad( );

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		const data_ad* administrative_division( int i_row ) const;
	//-------------------------------------------------------------------------
		const data_ad_list& list( ) const
		{
            return this->_list;
		}

	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		data_model_ad& operator=( const data_model_ad &rhs );

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
			this -> _header.append( QObject::tr( "administrative division" ) );
			this -> _header.append( QObject::tr( "ad abbreviation" ) );
		}

	public:
	//-------------------------------------------------------------------------
		void clear( );
	//-------------------------------------------------------------------------
		void refresh( const QVector<QVector<QVariant> > &data );
	//-------------------------------------------------------------------------
		void refresh( data_ad_collection *data );
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
		data_ad_list        _list;
		QVector<QString>	_header;

	};//class data_model_ad
//#############################################################################

}//namespace mac_mediator

#endif // __DATA_MODEL_AD_H__
