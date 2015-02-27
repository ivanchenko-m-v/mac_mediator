/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-09-2013
///		Date update	: 27-02-2015
///		Comment		:
/// ============================================================================
#ifndef __WIDGET_CENTRAL_H__
#define __WIDGET_CENTRAL_H__

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QAction>
#include <QMenu>

namespace mac_mediator
{

class widget_search_card;
class widget_card_view;
class listview_request;

/// ############################################################################
///			class widget_central
/// ############################################################################
    class widget_central : public QWidget
    {
    Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        widget_central( const widget_central &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit widget_central(QWidget *parent = 0);
        /// --------------------------------------------------------------------
        virtual ~widget_central( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        QWidget* init_search_card( );
        QWidget* init_view_card( );
        QWidget* init_listview_request( );
        QWidget* init_buttons_search( );
        QWidget* init_buttons_listview( );

        void init_stat_menu( );

        void init_connections( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        widget_central& operator=( const widget_central &rhs );

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
	protected:
        virtual void keyPressEvent ( QKeyEvent * event );

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
        void init_layout();
    public slots:
        /// --------------------------------------------------------------------
        void slot_add_request( );
        void slot_edit_request( );
        void slot_del_request( );
        void slot_id_request_edit( );
        void slot_print_request( );
        void slot_print_preview_paint_requested(QPrinter *p) const;
        void slot_stat_report( );
        void slot_stat_diagram( );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        widget_search_card  *_w_search;
        widget_card_view    *_w_view;
        listview_request    *_lv_request;

        QPushButton         *_btn_find_request;
        QPushButton         *_btn_clear_search_criteria;
        QPushButton         *_btn_add_request;
        QPushButton         *_btn_print_request;
        QPushButton         *_btn_edit_request;
        QPushButton         *_btn_edit_id_request;
        QPushButton         *_btn_del_request;

        QToolButton         *_btn_stat;

        QMenu               *_mnu_stat;
        QAction             *_act_report;
        QAction             *_act_diagram;
        QAction             *_act_list_to_excel;

	};//class widget_central
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __WIDGET_CENTRAL_H__
