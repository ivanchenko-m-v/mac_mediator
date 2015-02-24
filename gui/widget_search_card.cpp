/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 17-09-2013
///		Date update	: 01-02-2014
///		Comment		:
/// ============================================================================
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

#include "application.h"
#include "business_logic.h"

#include "widget_search_card.h"
#include "combobox_declarant_type.h"
#include "combobox_ad.h"
#include "combobox_mr.h"
#include "combobox_mediator.h"
#include "combobox_request_category.h"

namespace mac_mediator
{
/// ############################################################################
///			class widget_search_card
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	widget_search_card( )
    /// ------------------------------------------------------------------------
    widget_search_card::widget_search_card(QWidget *parent) :
        QWidget(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~widget_search_card( )
    /// ------------------------------------------------------------------------
    widget_search_card::~widget_search_card( )
    {

    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// id_declarant_type( )
    /// ------------------------------------------------------------------------
    int widget_search_card::id_declarant_type( ) const
    {
        return this->_cbx_declarant_type->id_declarant_type( );
    }

    /// ------------------------------------------------------------------------
    /// id_ad( )
    /// ------------------------------------------------------------------------
    int widget_search_card::id_ad( ) const
    {
        return this->_cbx_ad->id_ad( );
    }
    /// ------------------------------------------------------------------------
    /// id_mr( )
    /// ------------------------------------------------------------------------
    int widget_search_card::id_mr( ) const
    {
        return this->_cbx_mr->id_mr( );
    }
    /// ------------------------------------------------------------------------
    /// id_mediator( )
    /// ------------------------------------------------------------------------
    int widget_search_card::id_mediator( ) const
    {
        return this->_cbx_mediator->id_mediator( );
    }
    /// ------------------------------------------------------------------------
    /// id_request_category( )
    /// ------------------------------------------------------------------------
    int widget_search_card::id_request_category( ) const
    {
        return this->_cbx_request_category->id_request_category( );
    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_search_card::initialize( )
    {
        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_search_card::init_connections( )
    {
        this->connect(
                        this->_cbx_ad, SIGNAL( currentIndexChanged( int ) ),
                        this, SLOT( requery_mr( ) )
                    );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_search_card::init_layout( )
    {
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 5 );
        vl->setSpacing( 5 );

        //declarant type
        vl->addWidget( this->init_declarant_type( ) );
        //administrative division
        vl->addWidget( this->init_ad( ) );
        //municipal district
        vl->addWidget( this->init_mr( ) );
        //mediator
        vl->addWidget( this->init_mediator( ) );
        //request type
        vl->addWidget( this->init_request_type( ) );
        //period
        vl->addWidget( this->init_period( ) );
        //declarant
        vl->addWidget( this->init_declarant( ) );

        vl->addStretch( 1000 );
        this->setLayout( vl );
    }

    /// ------------------------------------------------------------------------
    /// init_declarant_type( )
    /// ------------------------------------------------------------------------
    QWidget *widget_search_card::init_declarant_type( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "declarant type:" ), widget );
        vl->addWidget( lbl );

        this->_cbx_declarant_type = new combobox_declarant_type( widget );
        vl->addWidget( this->_cbx_declarant_type );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_ad( )
    /// ------------------------------------------------------------------------
    QWidget* widget_search_card::init_ad( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "administrative division:" ), widget );
        vl->addWidget( lbl );

        this->_cbx_ad = new combobox_ad( widget );
        vl->addWidget( this->_cbx_ad );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_mr( )
    /// ------------------------------------------------------------------------
    QWidget* widget_search_card::init_mr( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "municipal region:" ), widget );
        vl->addWidget( lbl );

        this->_cbx_mr = new combobox_mr( widget );
        vl->addWidget( this->_cbx_mr );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_mediator( )
    /// ------------------------------------------------------------------------
    QWidget* widget_search_card::init_mediator( )
    {
        const data_mediator &mediator = application::program_instance()->
                                                        authorized_mediator( );

        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "mediator:" ), widget );
        vl->addWidget( lbl );

        this->_cbx_mediator = new combobox_mediator( widget );
        vl->addWidget( this->_cbx_mediator );

        widget->setLayout(vl);

        if(
            mediator.mediator_id( ) &&
            ( mediator.permissions( ) != "su" )
          )
        {
            widget->setEnabled( true );
        }

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_request_type( )
    /// ------------------------------------------------------------------------
    QWidget* widget_search_card::init_request_type( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "request type:" ), widget );
        vl->addWidget( lbl );

        this->_cbx_request_category = new combobox_request_category( widget );
        vl->addWidget( this->_cbx_request_category );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_declarant( )
    /// ------------------------------------------------------------------------
    QWidget* widget_search_card::init_declarant( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "declarant:" ), widget );
        vl->addWidget( lbl );

        this->_txt_declarant = new QLineEdit( widget );
        vl->addWidget( this->_txt_declarant );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_period( )
    /// ------------------------------------------------------------------------
    QWidget* widget_search_card::init_period( )
    {
        QWidget *widget = new QWidget( this );
        QGridLayout *gl = new QGridLayout;
        gl->setMargin( 0 );
        gl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "from:" ), widget );
        gl->addWidget( lbl, 0, 0 );
        this->_dte_from = new QDateEdit( widget );
        this->_dte_from->setCalendarPopup( true );
        this->_dte_from->setDisplayFormat("dd.MM.yyyy");
        this->_dte_from->setDate( QDate::currentDate( ) );
        gl->addWidget( this->_dte_from, 1, 0 );

        lbl = new QLabel( this->tr( "to:" ), widget );
        gl->addWidget( lbl, 0, 2 );
        this->_dte_to = new QDateEdit( widget );
        this->_dte_to->setCalendarPopup( true );
        this->_dte_to->setDisplayFormat("dd.MM.yyyy");
        this->_dte_to->setDate( QDate::currentDate( ) );
        gl->addWidget( this->_dte_to, 1, 2 );

        widget->setLayout(gl);

        return widget;
    }
    /// ------------------------------------------------------------------------
    /// clear_data( )
    /// ------------------------------------------------------------------------
    void widget_search_card::clear_data( )
    {
        this->_search_criteria.clear_data( );

        this->_cbx_ad->setCurrentIndex( -1 );
        this->_cbx_mediator->setCurrentIndex( -1 );
        this->_cbx_request_category->setCurrentIndex( -1 );
        this->_dte_from->setDate( QDate::currentDate( ) );
        this->_dte_to->setDate( QDate::currentDate( ) );
        this->_txt_declarant->clear( );
    }
    /// ------------------------------------------------------------------------
    /// set_request_data( )
    /// ------------------------------------------------------------------------
    void widget_search_card::set_search_criteria( )
    {
        this->_search_criteria.clear_data( );

        this->_search_criteria.id_declarant_type( this->id_declarant_type( ) );
        this->_search_criteria.id_ad( this->id_ad( ) );
        this->_search_criteria.id_mr( this->id_mr( ) );
        this->_search_criteria.id_mediator( this->id_mediator( ) );
        this->_search_criteria.id_request_category( this->id_request_category( ) );
        this->_search_criteria.declarant( this->_txt_declarant->text( ) );
        //Устанавливаем период в критерий поиска,
        //если даты не совпадают с текущей датой
        if(
           ( this->_dte_from->date( ) != QDate::currentDate( ) ) ||
           ( this->_dte_from->date( ) != this->_dte_to->date( ) )
          )
        {
            this->_search_criteria.date_from( this->_dte_from->date( ) );
            this->_search_criteria.date_to( this->_dte_to->date( ) );
        }
    }
    /// ------------------------------------------------------------------------
    /// request_data_valid( )
    /// ------------------------------------------------------------------------
    bool widget_search_card::search_criteria_valid( )
    {
        if( this->_search_criteria.id_declarant_type( ) > 0 )
        {
            return true;
        }
        if( this->_search_criteria.id_ad( ) > 0 )
        {
            return true;
        }
        if( this->_search_criteria.id_mr( ) > 0 )
        {
            return true;
        }
        if( this->_search_criteria.id_mediator( ) > 0 )
        {
            return true;
        }
        if( this->_search_criteria.id_request_category( ) > 0 )
        {
            return true;
        }
        if( this->_search_criteria.date_from_string( ).length( ) )
        {
            return true;
        }
        if( this->_search_criteria.date_to_string( ).length( ) )
        {
            return true;
        }
        if( this->_search_criteria.declarant( ).length( ) > 3 )
        {
            return true;
        }

        return false;
    }


    /// ========================================================================
    ///			SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// find_requests( )
    /// ------------------------------------------------------------------------
    void widget_search_card::find_requests( )
    {
        this->set_search_criteria( );

        if( !this->search_criteria_valid( ) )
        {
            QMessageBox::warning(0, this->tr("warning"), this->tr("the search criteria not set") );
            return;
        }
        application::the_business_logic( ).request_select( this->search_criteria( ) );
    }

    /// ------------------------------------------------------------------------
    /// clear_search_criteria( )
    /// ------------------------------------------------------------------------
    void widget_search_card::clear_search_criteria( )
    {
        this->clear_data( );
    }

    void widget_search_card::requery_mr( )
    {
        this->_cbx_mr->requery( this->_cbx_ad->id_ad( ) );
    }

}//namespace mac_mediator
