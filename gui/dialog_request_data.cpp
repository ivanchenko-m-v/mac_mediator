/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 01-10-2013
///		Date update	: 02-02-2014
///		Comment		:
/// ============================================================================
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QKeyEvent>

#include "application.h"
#include "business_logic.h"

#include "dialog_request_data.h"
#include "combobox_declarant_type.h"
#include "combobox_ad.h"
#include "combobox_mr.h"
#include "combobox_mediator.h"
#include "combobox_request_category.h"

#include "dialog_address_list.h"
#include "data_adapter_address.h"
#include "data_adapter_so.h"

namespace mac_mediator
{
/// ############################################################################
///			class dialog_request_data
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	dialog_request_data( )
    /// ------------------------------------------------------------------------
    dialog_request_data::dialog_request_data(
                                            QWidget *parent,
                                            dialog_request_data_mode mode
                                            ) :
        QDialog(parent),
        _mode(mode)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~dialog_request_data( )
    /// ------------------------------------------------------------------------
    dialog_request_data::~dialog_request_data( )
    {
        qDebug() << "dialog_request_data destroyed";
    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// id_request( )
    /// ------------------------------------------------------------------------
    int dialog_request_data::id_request( ) const
    {
        int id_ad = this->id_ad( );
        if( id_ad <= 0 )
        {
            return -1;
        }
        return application::the_business_logic( ).request_new_id( id_ad, this->_dte_date->date( ) );
    }

    /// ------------------------------------------------------------------------
    /// id_declarant_type( )
    /// ------------------------------------------------------------------------
    int dialog_request_data::id_declarant_type( ) const
    {
        return this->_cbx_declarant_type->id_declarant_type( );
    }

    /// ------------------------------------------------------------------------
    /// id_ad( )
    /// ------------------------------------------------------------------------
    int dialog_request_data::id_ad( ) const
    {
        /*
        int index = this->_cbx_ad->currentIndex( );
        if( index == -1 )
        {
            return -1;
        }
        return this->_cbx_ad->itemData( index ).toInt( );
        */
        return this->_cbx_ad->id_ad( );
    }
    /// ------------------------------------------------------------------------
    /// id_mr( )
    /// ------------------------------------------------------------------------
    int dialog_request_data::id_mr( ) const
    {
        /*
        int index = this->_cbx_mr->currentIndex( );
        if( index == -1 )
        {
            return -1;
        }
        return this->_cbx_mr->itemData( index ).toInt( );
        */
        return this->_cbx_mr->id_mr( );
    }
    /// ------------------------------------------------------------------------
    /// id_mediator( )
    /// ------------------------------------------------------------------------
    int dialog_request_data::id_mediator( ) const
    {
        /*
        int index = this->_cbx_mediator->currentIndex( );
        if( index == -1 )
        {
            return -1;
        }
        return this->_cbx_mediator->itemData( index ).toInt( );
        */
        return this->_cbx_mediator->id_mediator( );
    }
    /// ------------------------------------------------------------------------
    /// id_request_category( )
    /// ------------------------------------------------------------------------
    int dialog_request_data::id_request_category( ) const
    {
        /*
        int index = this->_cbx_request_category->currentIndex( );
        if( index == -1 )
        {
            return -1;
        }
        return this->_cbx_request_category->itemData( index ).toInt( );
        */
        return this->_cbx_request_category->id_request_category( );
    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::initialize( )
    {
        this->setModal( true );
        this->setWindowTitle( tr("dialog_request_data") );

        this->init_layout( );

        this->init_connections( );

        if( this->_mode == mode_add_request )
        {
            this->init_app_defaults( );
        }
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::init_connections( )
    {
        //changing ad selection
        this->connect(
                        this->_cbx_ad, SIGNAL(currentIndexChanged(int)),
                        this, SLOT( requery_mr( ) )
                     );
        //find declarant address
        this->connect(
                        this->_btn_address_search, SIGNAL( clicked( ) ),
                        this, SLOT( find_declarant_address( ) )
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
    void dialog_request_data::init_layout( )
    {
        QGridLayout *gl = new QGridLayout;
        gl->setMargin( 5 );
        gl->setSpacing( 5 );

        //line 0
        //------
        //declarant type
        gl->addWidget( this->init_declarant_type( ), 0, 0, 1, 1 );
        //administrative division
        gl->addWidget( this->init_ad( ), 0, 1, 1, 1 );
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
        gl->addWidget( this->init_request_category( ), 1, 3 );

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

        gl->setSizeConstraint(QLayout::SetMinimumSize);

        this->setLayout( gl );
    }

    /// ------------------------------------------------------------------------
    /// init_declarant_type( )
    /// ------------------------------------------------------------------------
    QWidget *dialog_request_data::init_declarant_type( )
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
    QWidget* dialog_request_data::init_ad( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "administrative division:" ), widget );
        vl->addWidget( lbl );

        this->_cbx_ad = new combobox_ad( widget );
        if( this->_mode == mode_edit_request )
        {
            this->_cbx_ad->setEnabled( false );
        }
        vl->addWidget( this->_cbx_ad );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_mr( )
    /// ------------------------------------------------------------------------
    QWidget* dialog_request_data::init_mr( )
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
    QWidget* dialog_request_data::init_mediator( )
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

        if( application::program_instance()->
                authorized_mediator( ).mediator_id( ) )
        {
            widget->setEnabled( false );
        }

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_request_type( )
    /// ------------------------------------------------------------------------
    QWidget* dialog_request_data::init_request_category( )
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
    QWidget* dialog_request_data::init_date( )
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
    QWidget* dialog_request_data::init_time( )
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
    QWidget* dialog_request_data::init_declarant( )
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
    QWidget* dialog_request_data::init_declarant_phone( )
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
    QWidget* dialog_request_data::init_declarant_address( )
    {
        QWidget *widget = new QWidget( this );
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "declarant address:" ), widget );
        vl->addWidget( lbl );

        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 0 );
        hl->setSpacing( 0 );
        this->_txt_declarant_address = new QLineEdit( widget );
        hl->addWidget( this->_txt_declarant_address, 1000 );
        this->_btn_address_search = new QToolButton;
        this->_btn_address_search->setIcon(
                                  *( new QIcon(":/image/images/3_points.png" ) )
                                          );
        int n_size = this->_txt_declarant_address->height( );
        this->_btn_address_search->resize( n_size, n_size );
        hl->addWidget( this->_btn_address_search );
        vl->addLayout( hl );

        widget->setLayout(vl);

        return widget;
    }
    /// ------------------------------------------------------------------------
    /// init_service_organization( )
    /// ------------------------------------------------------------------------
    QWidget* dialog_request_data::init_service_organization( )
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
    QWidget* dialog_request_data::init_other_conflict_party( )
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
    QWidget* dialog_request_data::init_organization( )
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
    QWidget* dialog_request_data::init_request( )
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
    QWidget* dialog_request_data::init_consultation( )
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
    QWidget* dialog_request_data::init_buttons( )
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
    /// init_app_defaults( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::init_app_defaults( )
    {
        int id_ad = application::program_instance( )->id_ad( );
        if( id_ad > 0 )
        {
            this->_cbx_ad->set_id_ad( id_ad );
        }
        int id_mediator = application::program_instance( )->authorized_mediator( ).mediator_id( );
        if( id_mediator > 0 )
        {
            this->_cbx_mediator->set_id_mediator( id_mediator );
        }
    }

    /// ------------------------------------------------------------------------
    /// save_app_defaults( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::save_app_defaults( )
    {
        application::program_instance( )->id_ad( this->id_ad( ) );
        application::program_instance( )->id_mediator( this->id_mediator( ) );
    }

    /// ------------------------------------------------------------------------
    /// set_request_data( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::set_request_data( )
    {
        if( this->_mode == mode_add_request )
        {
            this->_request.clear_data( );
            this->_request.id_request( this->id_request( ) );
        }
        this->_request.id_declarant_type( this->id_declarant_type( ) );
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
    bool dialog_request_data::request_data_valid( )
    {
        if( this->_request.id_request( ) <= 0 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed id request") );
            return false;
        }
        if( this->_request.id_declarant_type( ) <= 0 )
        {
            QMessageBox::warning(0, tr("warning"), tr("failed id declarant type") );
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
    /// ------------------------------------------------------------------------
    /// center_to_screen( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::center_to_screen( )
    {
        QRect rc( QApplication::desktop( )->geometry( ) );
        if( this->parentWidget( ) )
        {
            rc= this->parentWidget( )->frameGeometry( );
        }
        QRect rc_frame( this->frameGeometry( ) );
        this->move(
                   (rc.width()-rc_frame.width())/2,
                   (rc.height()-rc_frame.height())/2
                  );
    }
    /// ------------------------------------------------------------------------
    /// update_controls( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::update_controls( )
    {
        this->_cbx_declarant_type->set_id_declarant_type( this->_request.id_declarant_type( ) );
        this->_cbx_ad->set_id_ad( this->_request.id_ad( ) );
        this->_cbx_mr->set_id_mr( this->_request.id_mr( ) );
        this->_cbx_mediator->set_id_mediator( this->_request.id_mediator( ) );
        this->_cbx_request_category->set_id_request_category( this->_request.id_request_category( ) );
        this->_dte_date->setDate( this->_request.date( ) );
        this->_tme_time->setTime( this->_request.time( ) );
        this->_txt_declarant->setText( this->_request.declarant( ) );
        this->_txt_declarant_phone->setText( this->_request.declarant_phone( ) );
        this->_txt_declarant_address->setText( this->_request.declarant_address( ) );
        this->_txt_service_organization->setText( this->_request.service_organization( ) );
        this->_txt_other_conflict_party->setText( this->_request.other_conflict_party( ) );
        this->_txt_organization->setText( this->_request.organization( ) );
        this->_txt_request->setText( this->_request.request( ) );
        this->_txt_consultation->setText( this->_request.consultation( ) );
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// request_db_insert( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::request_db_insert( )
    {
        bool b_success = application::the_business_logic( )
                                        .request_insert( this->_request );

        if( b_success )
        {
            QMessageBox::information(
                                    0,"info",
                                    tr("successful inserting request card #" )+
                                    this->_request.id_request_string( )
                                    );
            this->save_app_defaults( );
            QDialog::done( QDialog::Accepted );
        }
    }

    /// ------------------------------------------------------------------------
    /// request_db_update( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::request_db_update( )
    {
        bool b_success = application::the_business_logic( )
                                        .request_update( this->_request );
        if( b_success )
        {
            QMessageBox::information(
                                    0,"info",
                                    tr("successful updateing request card #" )+
                                    this->_request.id_request_string( )
                                    );
            this->save_app_defaults( );
            QDialog::done( QDialog::Accepted );
        }
    }

    /// ------------------------------------------------------------------------
    /// save_request_data( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::save_request_data( )
    {
        this->set_request_data( );
        if( !this->request_data_valid( ) )
        {
            return;
        }
        if( this->_mode==mode_add_request )
        {
            this->request_db_insert( );
        }
        if( this->_mode==mode_edit_request )
        {
            this->request_db_update( );
        }

    }

    /// ------------------------------------------------------------------------
    /// find_declarant_address( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::find_declarant_address( )
    {
        dialog_address_list dlg;
        dlg.search_text( this->_txt_declarant_address->text( ) );
        if( dlg.exec( ) == QDialog::Accepted )
        {
            const data_address *addr = dlg.address( );
            if( addr )
            {
                this->_address = *addr;
                this->_txt_declarant_address->setText( addr->address( ) );
            }
            else
            {
                this->_address.clear_data( );
            }
            this->find_service_organization( );
        }
    }

    /// ------------------------------------------------------------------------
    /// find_service_organization( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::find_service_organization( )
    {
        if( !this->_address.address_key( ) )
        {
            return;
        }
        data_so *p_so = application::the_business_logic( ).
                                            so_select( this->_address.address_key( ) );
        if( p_so )
        {
            this->_so = *p_so;
            delete p_so;
            this->_txt_service_organization->setText( this->_so.title( ) );
        }
        else
        {
            this->_so.clear_data( );
        }
    }

    /// ------------------------------------------------------------------------
    /// requery_mr( )
    /// ------------------------------------------------------------------------
    void dialog_request_data::requery_mr( )
    {
        this->_cbx_mr->requery( this->_cbx_ad->id_ad( ) );
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// keyPressEvent( QKeyEvent *event )
    /// ------------------------------------------------------------------------
    void dialog_request_data::keyPressEvent( QKeyEvent *event )
    {
        int key = event->key( );
        if( ( key == Qt::Key_Enter )||( key==Qt::Key_Return ) )
        {
            if( this->_txt_declarant_address == this->focusWidget( ) )
            {
                this->find_declarant_address( );
            }
            else
            {
                QDialog::keyPressEvent( event );
            }
        }
    }

}//namespace mac_mediator
