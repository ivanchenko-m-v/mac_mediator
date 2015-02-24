/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 21-10-2013
///		Date update	: 23-10-2013
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>

#include "application.h"
#include "business_logic.h"

#include "dialog_address_list.h"
#include "listview_address.h"

#include "data_adapter_address.h"

namespace mac_mediator
{

/// ############################################################################
///			class dialog_address_list
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	dialog_address_list( )
    /// ------------------------------------------------------------------------
	dialog_address_list::dialog_address_list( QWidget *parent, Qt::WindowFlags f ) :
        QDialog( parent, f ),
        _address( 0 )
	{
        this->initialize( );
	}

    /// ------------------------------------------------------------------------
	///	~dialog_address_list( )
    /// ------------------------------------------------------------------------
	dialog_address_list::~dialog_address_list( )
	{
        qDebug() << "dialog_address_list destroyed";
    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void dialog_address_list::initialize( )
    {
        this->setWindowTitle( tr( "find declarant address" ) );

        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
	///	init_layout( )
    /// ------------------------------------------------------------------------
    void dialog_address_list::init_layout( )
    {
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        vl->addWidget( this->init_search_lineedit( ) );
        vl->addWidget( this->init_list_widget( ) );

        this->setLayout(vl);
    }

    /// ------------------------------------------------------------------------
	///	init_connections( )
    /// ------------------------------------------------------------------------
    void dialog_address_list::init_connections( )
    {
        this->connect(
                        this->_lv_street_buildings,
                        SIGNAL( address_selected( const data_address* ) ),
                        this,
                        SLOT( address_selected( const data_address* ) )
                     );
    /*
        //save request
        this->connect(
                        this->_btn_ok, SIGNAL(clicked()),
                        this, SLOT(update_request_id())
                     );
        //close window
        this->connect(
                        this->_btn_cancel, SIGNAL(clicked()),
                        this, SLOT(close())
                     );
                     */
    }

    /// ------------------------------------------------------------------------
	///	init_search_lineedit( )
    /// ------------------------------------------------------------------------
    QWidget *dialog_address_list::init_search_lineedit( )
    {
        this->_txt_search_text = new QLineEdit;
        return this->_txt_search_text;
    }

    /// ------------------------------------------------------------------------
	///	init_list_widget( )
    /// ------------------------------------------------------------------------
    QWidget *dialog_address_list::init_list_widget( )
    {
        this->_lv_street_buildings = new listview_address;
        return this->_lv_street_buildings;
    }

    /// ------------------------------------------------------------------------
	///	refresh_list( )
    /// ------------------------------------------------------------------------
    void dialog_address_list::refresh_list( )
    {
        QApplication::setOverrideCursor( QCursor( Qt::WaitCursor ) );

        application::the_business_logic( ).
                                      address_select( this->_txt_search_text->text( ) );

        QApplication::restoreOverrideCursor();
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// keyPressEvent( QKeyEvent *event )
    /// ------------------------------------------------------------------------
    void dialog_address_list::keyPressEvent( QKeyEvent *event )
    {
        int key = event->key( );
        if( ( key == Qt::Key_Enter )||( key==Qt::Key_Return ) )
        {
            if( this->_txt_search_text == this->focusWidget( ) )
            {
                this->refresh_list( );
            }
            else
            {
                QDialog::keyPressEvent( event );
            }
        }
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// address_selected(const data_address *address)
    /// ------------------------------------------------------------------------
    void dialog_address_list::address_selected(const data_address *address)
    {
        this->_address = address;
        this->accept( );
    }


/// ############################################################################

}//namespace mac_mediator
