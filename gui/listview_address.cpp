/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 23-10-2013
///		Date update	: 23-10-2013
///		Comment		:
/// ============================================================================
#include <QAbstractItemView>
#include <QHeaderView>
#include <QItemDelegate>
#include <QScrollBar>

#include "application.h"
#include "business_logic.h"

#include "data_model_address.h"

#include "listview_address.h"
#include "delegate_line_edit.h"

namespace mac_mediator
{

/// ############################################################################
///			class listview_address
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ------------------------------------------------------------------------
	///	listview_address( )
	/// ------------------------------------------------------------------------
	listview_address::listview_address( QWidget *parent ) :
		QTableView( parent )
	{
		this->initialize( );
	}

	/// ------------------------------------------------------------------------
	///	~listview_address( )
	/// ------------------------------------------------------------------------
	listview_address::~listview_address( )
	{
		this->setModel( 0 );
	}

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	/// -----------------------------------------------------------------------
	///	current_address( )
	/// -----------------------------------------------------------------------
    const data_address* listview_address::current_address( )
	{
		QModelIndex idx = this->selectionModel( )->currentIndex( );
		if( !idx.isValid( ) )
		{
			return 0;
		}

		return application::the_business_logic( ).
							model_address( )->address( idx.row( ) );
	}

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	initialize( )
	/// ------------------------------------------------------------------------
    void listview_address::initialize( )
	{
		this->init_view( );

		this->init_connections( );
	}

	/// ------------------------------------------------------------------------
	///	init_view( )
	/// ------------------------------------------------------------------------
    void listview_address::init_view( )
    {
        this->setShowGrid( false );
		//this->setGridStyle( Qt::DotLine );
		this->horizontalHeader( )->setVisible( false );
		this->horizontalHeader( )->setClickable( false );
		this->verticalHeader( )->setVisible( false );
		this->verticalHeader( )->setClickable( false );
		this->setModel(
				application::the_business_logic( ).model_address( )
					  );

		this->setSelectionMode( QAbstractItemView::SingleSelection );
		this->setSelectionBehavior( QAbstractItemView::SelectRows );

		this->setItemDelegate( new delegate_line_edit );
    }

	/// ------------------------------------------------------------------------
	///	init_connections( )
	/// ------------------------------------------------------------------------
    void listview_address::init_connections( )
    {
        this->connect(
                     this, SIGNAL( doubleClicked( QModelIndex ) ),
                     this, SLOT( address_selected( ) )
                     );
    }

	/// ========================================================================
	///		SLOTS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	address_selected( )
	/// ------------------------------------------------------------------------
    void listview_address::address_selected( )
    {
        const data_address *address = this->current_address( );
        if( address )
        {
            emit address_selected( address );
        }
    }

	/// ========================================================================
	///		EVENTS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	resizeEvent( QResizeEvent *event )
	/// ------------------------------------------------------------------------
    void listview_address::resizeEvent( QResizeEvent *event )
    {
        QTableView::resizeEvent( event );

        if( !this->model( ) )
        {
            return;
        }
        this->setColumnWidth( 0, this->viewport( )->width( ) );
    }

/// ############################################################################

}//namespace mac_mediator
