/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-09-2013
///		Date update	: 27-02-2015
///		Comment		:
/// ============================================================================
#include <QAction>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <QPrinter>
#include <QPrintPreviewDialog>

#include "application.h"
#include "business_logic.h"

#include "widget_central.h"
#include "widget_card_view.h"
#include "widget_search_card.h"
#include "listview_request.h"
#include "dialog_request_data.h"
#include "dialog_id_request.h"
#include "renderer_request.h"
#include "dialog_period.h"

namespace mac_mediator
{
/// ############################################################################
///			class widget_central
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	widget_central( )
    /// ------------------------------------------------------------------------
    widget_central::widget_central(QWidget *parent) :
        QWidget(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~widget_central( )
    /// ------------------------------------------------------------------------
    widget_central::~widget_central( )
    {

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_central::initialize( )
    {
        this->init_layout( );

        this->init_connections( );

        this->_w_search->setFocus( );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_central::init_layout( )
    {
        QGridLayout *gl = new QGridLayout;

        //column 0
        gl->addWidget( this->init_search_card( ), 0, 0 );
        gl->addWidget( this->init_buttons_search( ), 1, 0 );
        //column 1
        gl->addWidget( this->init_listview_request( ), 0, 1 );
        gl->addWidget( this->init_buttons_listview( ), 1, 1 );
        gl->addWidget( this->init_view_card( ), 2, 0, 2, 2 );

        gl->setColumnStretch( 0, 20 );
        gl->setColumnStretch( 1, 800 );

        gl->setRowStretch( 0, 500 );
        gl->setRowStretch( 2, 500 );

        this->setLayout( gl );
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_central::init_connections( )
    {
        //_btn_find_request
        this->connect(
                    this->_btn_find_request, SIGNAL( clicked( ) ),
                    this->_w_search, SLOT( find_requests( ) )
                    );
        //_btn_clear_search_criteria
        this->connect(
                    this->_btn_clear_search_criteria, SIGNAL( clicked( ) ),
                    this->_w_search, SLOT( clear_search_criteria( ) )
                    );
        //_btn_add_request
        this->connect(
                    this->_btn_add_request, SIGNAL( clicked( ) ),
                    this, SLOT( slot_add_request( ) )
                    );
        //_btn_print_request
        this->connect(
                    this->_btn_print_request, SIGNAL( clicked( ) ),
                    this, SLOT( slot_print_request( ) )
                    );
        //_btn_edit_request
        this->connect(
                    this->_btn_edit_request, SIGNAL( clicked( ) ),
                    this, SLOT( slot_edit_request( ) )
                    );
        //_btn_edit_id_request
        this->connect(
                    this->_btn_edit_id_request, SIGNAL( clicked( ) ),
                    this, SLOT( slot_id_request_edit( ) )
                    );
        //_btn_del_request
        this->connect(
                    this->_btn_del_request, SIGNAL( clicked( ) ),
                    this, SLOT( slot_del_request( ) )
                    );
        //_lv_request
        this->connect(
                     this->_lv_request, SIGNAL(current_request_changed(const data_request*)),
                     this->_w_view, SLOT(change_view(const data_request*))
                     );
        //_act_report
        this->connect(
                     this->_act_report, SIGNAL( triggered( ) ),
                     this, SLOT( slot_stat_report( ) )
                     );
        //_act_diagram
        this->connect(
                     this->_act_diagram, SIGNAL( triggered( ) ),
                     this, SLOT( slot_stat_diagram( ) )
                     );
    }

    /// ------------------------------------------------------------------------
    /// init_search_card( )
    /// ------------------------------------------------------------------------
    QWidget* widget_central::init_search_card( )
    {
        this->_w_search = new widget_search_card( this );

        return this->_w_search;
    }

    /// ------------------------------------------------------------------------
    /// init_view_card( )
    /// ------------------------------------------------------------------------
    QWidget* widget_central::init_view_card( )
    {
        this->_w_view = new widget_card_view( this );

        return this->_w_view;
    }

    /// ------------------------------------------------------------------------
    /// init_listview_request( )
    /// ------------------------------------------------------------------------
    QWidget* widget_central::init_listview_request( )
    {
        QWidget *widget = new QWidget( this );

        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 5 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "request list:" ), this );

        vl->addWidget( lbl );

        this->_lv_request = new listview_request( this );
        vl->addWidget( this->_lv_request );

       // vl->addStretch( 1000 );

        widget->setLayout( vl );

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_buttons_search( )
    /// ------------------------------------------------------------------------
    QWidget* widget_central::init_buttons_search( )
    {
        QWidget *widget = new QWidget( this );

        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 5 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );

        //_btn_find_request
        this->_btn_find_request = new QPushButton;
        this->_btn_find_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/edit-find.png" ) )
                                 );
        this->_btn_find_request->setToolTip( QObject::tr( "find requests" ) );
        hl->addWidget( this->_btn_find_request );

        //_btn_clear_search_criteria
        this->_btn_clear_search_criteria = new QPushButton;
        this->_btn_clear_search_criteria->setIcon(
                        *( new QIcon( ":/image/images/32x32/edit-clear.png" ) )
                                 );
        this->_btn_clear_search_criteria->setToolTip( QObject::tr( "clear search criteria" ) );
        hl->addWidget( this->_btn_clear_search_criteria );

        //_btn_add_request
        this->_btn_add_request = new QPushButton;
        this->_btn_add_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-new.png" ) )
                                 );
        this->_btn_add_request->setToolTip( QObject::tr( "add declarant\'s request" ) );
        hl->addWidget( this->_btn_add_request );

        widget->setLayout( hl );

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_buttons_listview( )
    /// ------------------------------------------------------------------------
    QWidget* widget_central::init_buttons_listview( )
    {
        QWidget *widget = new QWidget( this );

        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 5 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );

        //_btn_print_request
        this->_btn_print_request = new QPushButton;
        this->_btn_print_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-print.png" ) )
                                 );
        this->_btn_print_request->setToolTip( QObject::tr( "print request" ) );
        hl->addWidget( this->_btn_print_request );

        //_btn_edit_request
        this->_btn_edit_request = new QPushButton;
        this->_btn_edit_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-edit.png" ) )
                                 );
        this->_btn_edit_request->setToolTip( QObject::tr( "edit request" ) );
        hl->addWidget( this->_btn_edit_request );

        //_btn_edit_id_request
        this->_btn_edit_id_request = new QPushButton;
        this->_btn_edit_id_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/id-request-edit.png" ) )
                                 );
        this->_btn_edit_id_request->setToolTip( QObject::tr( "edit id of the request" ) );
        hl->addWidget( this->_btn_edit_id_request );

        //_btn_del_request
        this->_btn_del_request = new QPushButton;
        this->_btn_del_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-close.png" ) )
                                 );
        this->_btn_del_request->setToolTip( QObject::tr( "delete request" ) );
        hl->addWidget( this->_btn_del_request );

        hl->addStretch( 50 );

        //_btn_stat
        this->_btn_stat = new QToolButton;
        this->_btn_stat->setIcon(
                            QIcon( ":/image/images/32x32/office-chart-pie.png" )
                                 );
        this->_btn_stat->setToolTip( QObject::tr( "statistics" ) );
        this->_btn_stat->setPopupMode( QToolButton::MenuButtonPopup );
        this->init_stat_menu( );
        this->_btn_stat->setMenu( this->_mnu_stat );
        hl->addWidget( this->_btn_stat );

        widget->setLayout( hl );

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_stat_menu( )
    /// ------------------------------------------------------------------------
    void widget_central::init_stat_menu( )
    {
        this->_mnu_stat = new QMenu( );
        //_act_report
        this->_act_report = this->_mnu_stat->addAction( tr("Report") );
        //_act_diagram
        this->_act_diagram = this->_mnu_stat->addAction( tr("Diagaram") );
        //_act_list_to_excel
        this->_act_list_to_excel = this->_mnu_stat->addAction(
                            QIcon( ":/image/images/16x16/libreoffice-calc.png" ),
                            tr("List to Excel")
                                                             );
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// keyPressEvent ( QKeyEvent * event )
    /// ------------------------------------------------------------------------
    void widget_central::keyPressEvent( QKeyEvent * event )
    {
        if( event->key( ) == Qt::Key_N )
        {
            if( event->modifiers( ) & Qt::ControlModifier )
            {
                this->slot_add_request( );
            }
        }
        QWidget::keyPressEvent( event );
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// slot_add_request( )
    /// ------------------------------------------------------------------------
    void widget_central::slot_add_request( )
    {
        dialog_request_data w_data_add;
        w_data_add.exec( );
    }

    /// ------------------------------------------------------------------------
    /// slot_edit_request( )
    /// ------------------------------------------------------------------------
    void widget_central::slot_edit_request( )
    {
        data_request *request =
            const_cast<data_request*>( this->_lv_request->current_request( ) );
        if( !request )
        {
            return;
        }
        dialog_request_data w_data_edit( 0, dialog_request_data::mode_edit_request );
        w_data_edit.request( *request );
        int res = w_data_edit.exec( );
        //update data model item
        if( res == QDialog::Accepted )
        {
            *request = w_data_edit.request( );
        }
    }

    /// ------------------------------------------------------------------------
    /// slot_del_request( )
    /// ------------------------------------------------------------------------
    void widget_central::slot_del_request( )
    {
        const data_request *r = this->_lv_request->current_request( );
        if( !r )
        {
            return;
        }
        int i_reply = QMessageBox::question(
                                    0, tr("apply action"),
                                    tr( "Press Yes if you're want delete request" ),
                                    QMessageBox::No|QMessageBox::Yes
                                           );
        if( i_reply == QMessageBox::Yes)
        {
            business_logic &logic = application::the_business_logic( );
            if( logic.request_delete( r->id_request( ) ) )
            {
                QMessageBox::information(
                                         0, tr("info"),
                                         r->id_request_string( ) +
                                         tr(" request successful deleted from db")
                                        );
            }
        }
    }

    /// ------------------------------------------------------------------------
    /// slot_id_request_edit( )
    /// ------------------------------------------------------------------------
    void widget_central::slot_id_request_edit( )
    {
        const data_request *request = this->_lv_request->current_request( );
        if( !request )
        {
            return;
        }
        dialog_id_request dlg;
        dlg.request( const_cast<data_request *>( request ) );
        dlg.exec( );
    }

    /// ------------------------------------------------------------------------
    /// slot_print_request( )
    /// ------------------------------------------------------------------------
    void widget_central::slot_print_request( )
    {
		const data_request *r = this->_lv_request->current_request( );
		if( !r )
		{
            return;
		}
		QPrinter printer;
		printer.setPageMargins( 15, 15, 15, 15, QPrinter::Millimeter );
		printer.setOrientation( QPrinter::Portrait );
		printer.setPaperSize( QPrinter::A4 );
		printer.setPaperSource( QPrinter::Auto );

		QPrintPreviewDialog ppvw_dlg( &printer );
		ppvw_dlg.setWindowTitle( tr( "Request card info" ) );
		ppvw_dlg.setWindowFlags( Qt::WindowMaximizeButtonHint|Qt::WindowCloseButtonHint );
		this->connect(
				&ppvw_dlg, SIGNAL( paintRequested( QPrinter* ) ),
				this, SLOT( slot_print_preview_paint_requested( QPrinter* ) )
					 );
		ppvw_dlg.exec( );
    }

    /// ------------------------------------------------------------------------
	///	slot_print_preview_paint_requested( QPrinter *p ) const
    /// ------------------------------------------------------------------------
    void widget_central::slot_print_preview_paint_requested( QPrinter *p ) const
	{
		//get request
		const data_request *r = this->_lv_request->current_request( );
		if( !r )
		{
            return;
		}
		renderer_request rdr( p );
		rdr.request( r );
		//
		rdr.begin( p );
        rdr.draw_request( );
        rdr.end( );
    }

    /// ------------------------------------------------------------------------
    /// slot_stat_report( )
    /// ------------------------------------------------------------------------
    void widget_central::slot_stat_report( )
    {
        dialog_period dlg;
        if( dlg.exec( ) != QDialog::Accepted )
        {
            return;
        }
        QMessageBox::information(0, "slot_stat_report", "report" );
    }

    /// ------------------------------------------------------------------------
    /// slot_stat_diagram( )
    /// ------------------------------------------------------------------------
    void widget_central::slot_stat_diagram( )
    {
        dialog_period dlg;
        if( dlg.exec( ) != QDialog::Accepted )
        {
            return;
        }
        QMessageBox::information(0, "slot_stat_diagram", "diagram" );
    }

}//namespace mac_mediator
