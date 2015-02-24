/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 12-11-2013
///		Date update	: 12-11-2013
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

#include "application.h"
#include "business_logic.h"

#include "dialog_period.h"

namespace mac_mediator
{

/// ############################################################################
///			class dialog_period
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	dialog_period( )
    /// ------------------------------------------------------------------------
	dialog_period::dialog_period( QWidget *parent, Qt::WindowFlags f ) :
        QDialog( parent, f )
	{
        this->initialize( );
	}

    /// ------------------------------------------------------------------------
	///	~dialog_period( )
    /// ------------------------------------------------------------------------
	dialog_period::~dialog_period( )
	{
        qDebug() << "dialog_period destroyed";
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
    void dialog_period::initialize( )
    {
        this->setWindowTitle( tr( "stats for period" ) );

        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
	///	init_layout( )
    /// ------------------------------------------------------------------------
    void dialog_period::init_layout( )
    {
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 5 );
        vl->setSpacing( 10 );

        vl->addWidget( this->init_period( ) );
        vl->addWidget( this->init_buttons( ) );

        this->setLayout(vl);
    }

    /// ------------------------------------------------------------------------
	///	init_connections( )
    /// ------------------------------------------------------------------------
    void dialog_period::init_connections( )
    {
        //accept
        this->connect(
                        this->_btn_ok, SIGNAL( clicked( ) ),
                        this, SLOT( accept( ) )
                     );
        //reject
        this->connect(
                        this->_btn_cancel, SIGNAL( clicked( ) ),
                        this, SLOT( reject( ) )
                    );
    }

    /// ------------------------------------------------------------------------
	///	init_period( )
    /// ------------------------------------------------------------------------
    QWidget* dialog_period::init_period( )
    {
        QWidget *widget = new QWidget( this );

        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 0 );
        hl->setSpacing( 10 );

        hl->addWidget( this->init_date_from( ) );
        hl->addWidget( this->init_date_to( ) );

        widget->setLayout(hl);

        return widget;
    }

    /// ------------------------------------------------------------------------
	///	init_date_from( )
    /// ------------------------------------------------------------------------
    QWidget* dialog_period::init_date_from( )
    {
        QWidget *widget = new QWidget( this );

        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( tr( "period from:" ) );
        lbl->setAlignment( Qt::AlignLeft|Qt::AlignVCenter );
        vl->addWidget( lbl );

        this->_dte_from = new QDateTimeEdit;
        this->_dte_from->setCalendarPopup( true );
        this->_dte_from->setDisplayFormat("dd.MM.yyyy");
        this->_dte_from->setDate( QDate::currentDate( ) );
        vl->addWidget( this->_dte_from );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
	///	init_date_to( )
    /// ------------------------------------------------------------------------
    QWidget* dialog_period::init_date_to( )
    {
        QWidget *widget = new QWidget( this );

        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( tr( "to:" ) );
        lbl->setAlignment( Qt::AlignLeft|Qt::AlignVCenter );
        vl->addWidget( lbl );

        this->_dte_to = new QDateTimeEdit;
        this->_dte_to->setCalendarPopup( true );
        this->_dte_to->setDisplayFormat("dd.MM.yyyy");
        this->_dte_to->setDate( QDate::currentDate( ) );
        vl->addWidget( this->_dte_to );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
	///	init_buttons( )
    /// ------------------------------------------------------------------------
    QWidget *dialog_period::init_buttons( )
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

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================

/// ############################################################################

}//namespace mac_mediator
