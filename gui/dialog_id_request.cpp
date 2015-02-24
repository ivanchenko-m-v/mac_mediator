/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 17-10-2013
///		Date update	: 19-12-2013
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

#include "application.h"
#include "business_logic.h"

#include "dialog_id_request.h"
#include "data_adapter_request.h"

namespace mac_mediator
{

/// ############################################################################
///			class dialog_id_request
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	dialog_id_request( )
    /// ------------------------------------------------------------------------
	dialog_id_request::dialog_id_request( QWidget *parent, Qt::WindowFlags f ) :
        QDialog( parent, f ),
        _request( 0 )
	{
        this->initialize( );
	}

    /// ------------------------------------------------------------------------
	///	~dialog_id_request( )
    /// ------------------------------------------------------------------------
	dialog_id_request::~dialog_id_request( )
	{
        qDebug() << "dialog_id_request destroyed";
    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	id_new( )
    /// ------------------------------------------------------------------------
    int dialog_id_request::id_new( const QDate &dt ) const
    {
        bool b_ok = false;
        int num = this->_txt_id->text( ).toInt( &b_ok );
        if( !b_ok )
        {
            return 0;
        }
        int nyear = (dt.year( )-2000) << 16;

        return int( ( this->_request->id_request( ) & 0xff000000 )|nyear|num );
    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void dialog_id_request::initialize( )
    {
        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
	///	init_layout( )
    /// ------------------------------------------------------------------------
    void dialog_id_request::init_layout( )
    {
        QGridLayout *gl = new QGridLayout;
        gl->setMargin( 5 );
        gl->setSpacing( 10 );

        gl->addWidget( this->init_id_lineedit( ), 0, 0 );
        gl->addWidget( this->init_buttons( ), 1, 0 );

        this->setLayout(gl);
    }

    /// ------------------------------------------------------------------------
	///	init_connections( )
    /// ------------------------------------------------------------------------
    void dialog_id_request::init_connections( )
    {
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
    }

    /// ------------------------------------------------------------------------
	///	init_id_lineedit( )
    /// ------------------------------------------------------------------------
    QWidget *dialog_id_request::init_id_lineedit( )
    {
        QWidget *widget = new QWidget( this );
        QGridLayout *gl = new QGridLayout;
        gl->setMargin( 0 );
        gl->setSpacing( 0 );

        QLabel *lbl = new QLabel( tr( "id request:" ) );
        lbl->setAlignment( Qt::AlignLeft|Qt::AlignVCenter );
        gl->addWidget( lbl, 0, 0, 1, 2 );

        this->_lbl_ad = new QLabel;
        this->_lbl_ad->setAlignment( Qt::AlignRight|Qt::AlignVCenter );
        gl->addWidget( this->_lbl_ad, 1, 0 );

        this->_txt_id = new QLineEdit;
        this->_txt_id->setInputMask( "0000000" );
        gl->addWidget( this->_txt_id, 1, 1 );

        widget->setLayout(gl);

        return widget;
    }

    /// ------------------------------------------------------------------------
	///	init_buttons( )
    /// ------------------------------------------------------------------------
    QWidget *dialog_id_request::init_buttons( )
    {
        QWidget *widget = new QWidget( this );
        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 0 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );

        this->_btn_ok = new QPushButton( tr("OK") );
        hl->addWidget( this->_btn_ok );

        this->_btn_cancel = new QPushButton( tr("Cancel") );
        hl->addWidget( this->_btn_cancel );

        widget->setLayout(hl);

        return widget;
    }

    /// ------------------------------------------------------------------------
	///	init_buttons( )
    /// ------------------------------------------------------------------------
    void dialog_id_request::update_id_text( )
    {
        if( !this->_request )
        {
            return;
        }
        QString s_id = this->_request->id_request_string( );
        int idx = s_id.indexOf( '-' );
        if( idx < 0 )
        {
            return;
        }
        //text before number, include delimeter
        this->_lbl_ad->setText( s_id.left( idx + 1 ) );
        //text after delimeter
        this->_txt_id->setText( s_id.right( s_id.length( ) - idx - 1 ) );
    }

    /// ------------------------------------------------------------------------
	///	id_valid( int id )
    /// ------------------------------------------------------------------------
    bool dialog_id_request::id_valid( int id )
    {
        return ( id != 0 );
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	save_request_data( )
    /// ------------------------------------------------------------------------
    void dialog_id_request::update_request_id( )
    {
        int id_new = this->id_new( this->_request->date( ) );
        if( !id_valid( id_new ) )
        {
            QMessageBox::warning(
                                    0,"warning",
                                    tr("entered number is invalid" )
                                    );
            return;
        }
        bool b_success = application::the_business_logic( ).
                                         request_update_id(
                                                       this->_request->id_request( ),
                                                       id_new
                                                          );
        if( b_success )
        {
            this->_request->id_request( id_new );
            QMessageBox::information(
                                    0,"info",
                                    tr("successful updateing request card #" )+
                                    this->_request->id_request_string( )
                                    );
            QDialog::done( QDialog::Accepted );
        }
    }

/// ############################################################################

}//namespace mac_mediator
