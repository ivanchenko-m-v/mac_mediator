//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 27-09-2013
//		Date update	: 01-10-2013
//		Comment		:
//=============================================================================

#ifndef __DATA_MODEL_MR_H__
#define __DATA_MODEL_MR_H__

#include <QAbstractTableModel>
#include <QList>
#include <QVector>

namespace mac_mediator
{

	class data_mr;
	class data_mr_collection;
    typedef QList<data_mr*> data_mr_list;
//#############################################################################
//			class data_model_mr
//#############################################################################
	class data_model_mr : public QAbstractTableModel
	{

	Q_OBJECT
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		data_model_mr( QObject* pobj = 0 );
	//-------------------------------------------------------------------------
		virtual ~data_model_mr( );

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		const data_mr* municipal_district( int i_row ) const;
	//-------------------------------------------------------------------------
        const data_mr_list& list( ) const
        { return this->_list; }
	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		data_model_mr& operator=( const data_model_mr &rhs );

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
            this -> _header.append( QObject::tr( "class id" ) );
            this -> _header.append( QObject::tr( "ad id" ) );
			this -> _header.append( QObject::tr( "municipal district" ) );
		}

	public:
	//-------------------------------------------------------------------------
		void clear( );
	//-------------------------------------------------------------------------
		void refresh( const QVector<QVector<QVariant> > &data );
	//-------------------------------------------------------------------------
		void refresh( data_mr_collection *data );
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
		data_mr_list        _list;
		QVector<QString>    _header;

	};//class data_model_mr
//#############################################################################

}//namespace mac_mediator

#endif // __DATA_MODEL_MR_H__
