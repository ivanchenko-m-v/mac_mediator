/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 01-10-2013
///		Date update	: 03-10-2013
///		Comment		:
/// ============================================================================
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

#include "app_mac_mediator.h"
#include "business_logic.h"

#include "widget_request_data.h"
#include "combobox_ad.h"
#include "combobox_mr.h"
#include "combobox_mediator.h"
#include "combobox_request_category.h"

namespace mac_mediator
{
/// ############################################################################
///			class widget_request_data
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	widget_request_data( )
    /// ------------------------------------------------------------------------
    widget_request_data::widget_request_data(QWidget *parent) :
        QWidget(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~widget_request_data( )
    /// ------------------------------------------------------------------------
    widget_request_data::~widget_request_data( )
    {

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_request_data::initialize( )
    {
        this->init_layout( );

        init_connections( );
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_request_data::init_connections( )
    {
        //changing ad selection
        this->connect(
                        this->_cbx_ad, SIGNAL(currentIndexChanged(int)),
                        this->_cbx_mr, SLOT(requery(int))
                     );
        //save request
        this->connect(
                        this->_btn_OK, SIGNAL(clicked()),
                        this, SLOT(save_request_data())
                     );
        //close window
        this->connect(
                        this->_btn_cancel, SIGNAL(clicked()),
                        this, SLOT(close())
                     );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_request_data::init_layout( )
    {
        QGridLayout *gl = new QGridLayout;
        gl->setMargin( 5 );
        gl->setSpacing( 5 );

        //line 0
        //------
        //administrative division
        gl->addWidget( this->init_ad( ), 0, 0, 1, 2 );
        //municipal district
        gl->addWidget( this->init_mr( ), 0, 2, 1, 2 );

        //line 1
        //------
        //date
        gl->addWidget( this->init_date( ), 1, 0 );
        //time
        gl->addWidget( this->init_time( ), 1, 1 );
        //mediator
        gl->addWidget( this->init_mediator( ), 1, 2 );
        //request type
        gl->addWidget( this->init_request_type( ), 1, 3 );

        //line 2
        //------
        //declarant
        gl->addWidget( this->init_declarant( ), 2, 0, 1, 3 );
        //declarant phone
        gl->addWidget( this->init_declarant_phone( ), 2, 3 );

        //line 3
        //------
        //declarant address
        gl->addWidget( this->init_declarant_address( ), 3, 0, 1, 4 );

        //line 4
        //------
        //service organization
        gl->addWidget( this->init_service_organization( ), 4, 0, 1, 4 );

        //line 5
        //------
        //other_conflict_party
        gl->addWidget( this->init_other_conflict_party( ), 5, 0, 1, 4 );

        //line 6
        //------
        //other_conflict_party
        gl->addWidget( this->init_organization( ), 6, 0, 1, 4 );

        //line 7
        //------
        //request
        gl->addWidget( this->init_request( ), 7, 0, 1, 4 );

        //line 8
        //------
        //request
        gl->addWidget( this->init_consultation( ), 8, 0, 1, 4 );

        //line 9
        gl->setRowStretch( 9, 1000 );

        //line 10
        //------
        //buttons
        gl->addWidget( this->init_buttons( ), 10, 0, 1, 4 );

        this->setLayout( gl );
    }

    /// ------------------------------------------------------------------------
    /// init_ad( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_ad( )
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
    QWidget* widget_request_data::init_mr( )
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
    QWidget* widget_request_data::init_mediator( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "mediator:" ), widget );
        vl->addWidget( lbl );

        this->_cbx_mediator = new combobox_mediator( widget );
        vl->addWidget( this->_cbx_mediator );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_request_type( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_request_type( )
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
    /// init_date( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_date( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "date:" ), widget );
        vl->addWidget( lbl );

        this->_dte_date = new QDateEdit( widget );
        this->_dte_date->setCalendarPopup( true );
        this->_dte_date->setDisplayFormat("dd.MM.yyyy");
        this->_dte_date->setDate( QDate::currentDate( ) );
        vl->addWidget( this->_dte_date );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_time( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_time( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "time:" ), widget );
        vl->addWidget( lbl );

        this->_tme_time = new QTimeEdit( widget );
        this->_tme_time->setDisplayFormat("hh:mm");
        this->_tme_time->setTime( QTime::currentTime( ) );
        vl->addWidget( this->_tme_time );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_declarant( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_declarant( )
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
    /// init_declarant_phone( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_declarant_phone( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "declarant phone:" ), widget );
        vl->addWidget( lbl );

        this->_txt_declarant_phone = new QLineEdit( widget );
        this->_txt_declarant_phone->setInputMask( "(999)999-99-99" );
        vl->addWidget( this->_txt_declarant_phone );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_declarant_address( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_declarant_address( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "declarant address:" ), widget );
        vl->addWidget( lbl );

        this->_txt_declarant_address = new QLineEdit( widget );
        vl->addWidget( this->_txt_declarant_address );

        widget->setLayout(vl);

        return widget;
    }
    /// ------------------------------------------------------------------------
    /// init_service_organization( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_service_organization( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "service organization:" ), widget );
        vl->addWidget( lbl );

        this->_txt_service_organization = new QLineEdit( widget );
        vl->addWidget( this->_txt_service_organization );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_other_conflict_party( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_other_conflict_party( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "other conflict party:" ), widget );
        vl->addWidget( lbl );

        this->_txt_other_conflict_party = new QLineEdit( widget );
        vl->addWidget( this->_txt_other_conflict_party );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_organization( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_organization( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "responsible organization:" ), widget );
        vl->addWidget( lbl );

        this->_txt_organization = new QLineEdit( widget );
        vl->addWidget( this->_txt_organization );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_request( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_request( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "request:" ), widget );
        vl->addWidget( lbl );

        this->_txt_request = new QTextEdit( widget );
        vl->addWidget( this->_txt_request );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_consultation( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_consultation( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "consultation:" ), widget );
        vl->addWidget( lbl );

        this->_txt_consultation = new QTextEdit( widget );
        vl->addWidget( this->_txt_consultation );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_buttons( )
    /// ------------------------------------------------------------------------
    QWidget* widget_request_data::init_buttons( )
    {
        QWidget *widget = new QWidget( this );
        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 0 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );

        this->_btn_OK = new QPushButton( QObject::tr("OK") );
        hl->addWidget( this->_btn_OK );

        this->_btn_cancel = new QPushButton( QObject::tr("Cancel") );
        hl->addWidget( this->_btn_cancel );

        widget->setLayout(hl);

        return widget;
    }
    /// ------------------------------------------------------------------------
    /// set_request_data( )
    /// ------------------------------------------------------------------------
    void widget_request_data::set_request_data( )
    {
        this->_request.clear_data( );

        this->_request.id_request( this->id_request( ) );
        this->_request.id_mr( this->id_mr( ) );
        this->_request.id_mediator( this->id_mediator( ) );
        this->_request.id_request_category( this->id_request_category( ) );
        this->_request.date_request( this->_dte_date->date( ) );
        this->_request.time_request( this->_tme_time->time( ) );
        this->_request.declarant( this->_txt_declarant->text( ) );
        this->_request.declarant_phone( this->_txt_declarant_phone->text( ) );
        this->_request.declarant_address( this->_txt_declarant_address->text( ) );
        this->_request.service_organization( this->_txt_service_organization->text( ) );
        this->_request.other_conflict_party( this->_txt_other_conflict_party->text( ) );
        this->_request.organization( this->_txt_organization->text( ) );
        this->_request.request( this->_txt_request->toPlainText( ) );
        this->_request.consultation( this->_txt_consultation->toPlainText( ) );
    }

    /// ------------------------------------------------------------------------
    /// request_data_valid( )
    /// ------------------------------------------------------------------------
    bool widget_request_data::request_data_valid( )
    {
        if( this->_request.id_request( ) <= 0 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed id request") );
            return false;
        }
        if( this->_request.id_mr( ) <= 0 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed id mr") );
            return false;
        }
        if( this->_request.id_mediator( ) <= 0 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed id mediator") );
            return false;
        }
        if( this->_request.id_request_category( ) <= 0 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed request category") );
            return false;
        }
        if( !this->_request.date( ).isValid( ) )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed request date") );
            return false;
        }
        if( !this->_request.time( ).isValid( ) )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed request time") );
            return false;
        }
        if( this->_request.declarant( ).length( ) < 3 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed request declarant") );
            return false;
        }
        if( this->_request.declarant_address( ).length( ) < 3 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed request declarant address") );
            return false;
        }
        if( this->_request.request( ).length( ) < 3 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed request text") );
            return false;
        }
        if( this->_request.consultation( ).length( ) < 3 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed request consultation text") );
            return false;
        }

        return true;
    }
    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// id_request( )
    /// ------------------------------------------------------------------------
    int widget_request_data::id_request( ) const
    {
        int id_ad = this->id_ad( );
        if( id_ad <= 0 )
        {
            return -1;
        }
        return app_mac_mediator::the_business_logic( ).request_new_id( id_ad );
    }
    /// ------------------------------------------------------------------------
    /// id_ad( )
    /// ------------------------------------------------------------------------
    int widget_request_data::id_ad( ) const
    {
        int index = this->_cbx_ad->currentIndex( );
        if( index == -1 )
        {
            return -1;
        }
        return this->_cbx_ad->itemData( index ).toInt( );
    }
    /// ------------------------------------------------------------------------
    /// id_mr( )
    /// ------------------------------------------------------------------------
    int widget_request_data::id_mr( ) const
    {
        int index = this->_cbx_mr->currentIndex( );
        if( index == -1 )
        {
            return -1;
        }
        return this->_cbx_mr->itemData( index ).toInt( );
    }
    /// ------------------------------------------------------------------------
    /// id_mediator( )
    /// ------------------------------------------------------------------------
    int widget_request_data::id_mediator( ) const
    {
        int index = this->_cbx_mediator->currentIndex( );
        if( index == -1 )
        {
            return -1;
        }
        return this->_cbx_mediator->itemData( index ).toInt( );
    }
    /// ------------------------------------------------------------------------
    /// id_request_category( )
    /// ------------------------------------------------------------------------
    int widget_request_data::id_request_category( ) const
    {
        int index = this->_cbx_request_category->currentIndex( );
        if( index == -1 )
        {
            return -1;
        }
        return this->_cbx_request_category->itemData( index ).toInt( );
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// save_request_data( )
    /// ------------------------------------------------------------------------
    void widget_request_data::save_request_data( )
    {
        this->set_request_data( );
        if( !this->request_data_valid( ) )
        {
            return;
        }
        bool b_success = app_mac_mediator::the_business_logic( ).request_insert( this->_request );
        if( b_success )
        {
            QString request_num( QString::number( this->_request.id_request( )>>24 ) );
            request_num +="-" + QString::number( this->_request.id_request( )&0xffffff );

            QMessageBox::information(0,"info", tr("successful inserting request card #" )+request_num );
        }
    }
}//namespace mac_mediator
