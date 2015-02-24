//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 08-11-2010
//		Date update	: 08-11-2010
//		Comment		:
//=============================================================================
#ifndef __DELEGATE_LINE_EDIT_H__
#define __DELEGATE_LINE_EDIT_H__

#include <QItemDelegate>

namespace mac_mediator
{

//#############################################################################
//			class delegate_line_edit
//#############################################################################
	class delegate_line_edit : public QItemDelegate
	{
	Q_OBJECT
	//=========================================================================
	//		CONSTRUCTORS/DESTRUCTOR
	//=========================================================================
	private:
	//-------------------------------------------------------------------------
		delegate_line_edit( const delegate_line_edit &rhs );

	public:
	//-------------------------------------------------------------------------
		explicit delegate_line_edit( QObject *parent = 0 );
	//-------------------------------------------------------------------------
		~delegate_line_edit( );

	//=========================================================================
	//		FUNCTIONS
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		//override
		QWidget *createEditor(
							QWidget *parent, const QStyleOptionViewItem &option,
							const QModelIndex &index
							 ) const;
	//-------------------------------------------------------------------------
		//override
		void setEditorData( QWidget *editor, const QModelIndex &index ) const;
	//-------------------------------------------------------------------------
		//override
		void setModelData(
							QWidget *editor, QAbstractItemModel *model,
							const QModelIndex &index
						 ) const;
	//-------------------------------------------------------------------------
		//override
		void updateEditorGeometry(
							QWidget *editor,
							const QStyleOptionViewItem &option,
							const QModelIndex &index
								 ) const;
	//-------------------------------------------------------------------------
		//override
		void paint(
					QPainter * painter,
					const QStyleOptionViewItem& option,
					const QModelIndex& index
				  ) const;

	//=========================================================================
	//		PROPERTIES
	//=========================================================================
	public:
	//-------------------------------------------------------------------------
		Qt::Alignment alignment( )
		{ return this -> _alignment; }
	//-------------------------------------------------------------------------
		void alignment( Qt::Alignment alignment )
		{ this -> _alignment = alignment; }


	//=========================================================================
	//		OPERATORS
	//=========================================================================
	private:
		delegate_line_edit& operator=( const delegate_line_edit &rhs );

	public:

	//=========================================================================
	//			FIELDS
	//=========================================================================
	private:
		Qt::Alignment	_alignment;

	};//class delegate_line_edit
//#############################################################################
//-----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DELEGATE_LINE_EDIT_H__
