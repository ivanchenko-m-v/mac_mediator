/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 01-10-2013
///		Date update	: 02-02-2014
///		Comment		:
/// ============================================================================
#ifndef __DIALOG_REQUEST_DATA_H__
#define __DIALOG_REQUEST_DATA_H__

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QToolButton>

#include "data_adapter_request.h"
#include "data_adapter_address.h"
#include "data_adapter_so.h"

namespace mac_mediator
{

class combobox_declarant_type;
class combobox_ad;
class combobox_mr;
class combobox_mediator;
class combobox_request_category;
/// ############################################################################
///			class dialog_request_data
/// ############################################################################
    class dialog_request_data : public QDialog
    {
    Q_OBJECT
    public:
        enum dialog_request_data_mode
        {
            mode_add_request = 0,
            mode_edit_request = 1
        };

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        dialog_request_data( const dialog_request_data &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit dialog_request_data(
                                    QWidget *parent = 0,
                                    dialog_request_data_mode mode = mode_add_request
                                    );
        /// --------------------------------------------------------------------
        virtual ~dialog_request_data( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        int id_request( ) const;
        /// --------------------------------------------------------------------
        int id_declarant_type( ) const;
        /// --------------------------------------------------------------------
        int id_ad( ) const;
        /// --------------------------------------------------------------------
        int id_mr( ) const;
        /// --------------------------------------------------------------------
        int id_mediator( ) const;
        /// --------------------------------------------------------------------
        int id_request_category( ) const;

    public:
        /// --------------------------------------------------------------------
        const data_request& request( ) const
        {
            return this->_request;
        }

        /// --------------------------------------------------------------------
        void request( const data_request& r)
        {
            if( this->_mode!=mode_edit_request)
            {
                return;
            }
            this->_request = r;
            this->update_controls( );
        }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        /// --------------------------------------------------------------------
        void init_layout( );
        /// --------------------------------------------------------------------
        void init_connections( );
        /// --------------------------------------------------------------------
        QWidget* init_declarant_type( );
        /// --------------------------------------------------------------------
        QWidget* init_ad( );
        /// --------------------------------------------------------------------
        QWidget* init_mr( );
        /// --------------------------------------------------------------------
        QWidget* init_mediator( );
        /// --------------------------------------------------------------------
        QWidget* init_request_category( );
        /// --------------------------------------------------------------------
        QWidget* init_date( );
        /// --------------------------------------------------------------------
        QWidget* init_time( );
        /// --------------------------------------------------------------------
        QWidget* init_declarant( );
        /// --------------------------------------------------------------------
        QWidget* init_declarant_phone( );
        /// --------------------------------------------------------------------
        QWidget* init_declarant_address( );
        /// --------------------------------------------------------------------
        QWidget* init_service_organization( );
        /// --------------------------------------------------------------------
        QWidget* init_other_conflict_party( );
        /// --------------------------------------------------------------------
        QWidget* init_organization( );
        /// --------------------------------------------------------------------
        QWidget* init_request( );
        /// --------------------------------------------------------------------
        QWidget* init_consultation( );
        /// --------------------------------------------------------------------
        QWidget* init_buttons( );
        /// --------------------------------------------------------------------
        void init_app_defaults( );
        /// --------------------------------------------------------------------
        void save_app_defaults( );
        /// --------------------------------------------------------------------
        void set_request_data( );
        /// --------------------------------------------------------------------
        bool request_data_valid( );
        /// --------------------------------------------------------------------
        void request_db_update( );
        /// --------------------------------------------------------------------
        void request_db_insert( );
        /// --------------------------------------------------------------------
        void update_controls( );

    public:
        /// --------------------------------------------------------------------
        void center_to_screen( );

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
        dialog_request_data& operator=( const dialog_request_data &rhs );

	public:

    /// ========================================================================
    ///			EVENTS
    /// ========================================================================
    protected:
        /// --------------------------------------------------------------------
        void keyPressEvent( QKeyEvent *event );

    /// ========================================================================
    ///			SIGNALS
    /// ========================================================================

    /// ========================================================================
    ///			SLOTS
    /// ========================================================================
    private slots:
        /// --------------------------------------------------------------------
        void find_declarant_address( );
        /// --------------------------------------------------------------------
        void find_service_organization( );
        /// --------------------------------------------------------------------
        void requery_mr( );

    public slots:
        /// --------------------------------------------------------------------
        void save_request_data( );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        combobox_declarant_type     *_cbx_declarant_type;
        combobox_ad                 *_cbx_ad;
        combobox_mr                 *_cbx_mr;
        combobox_mediator           *_cbx_mediator;
        combobox_request_category   *_cbx_request_category;
        QDateEdit                   *_dte_date;
        QTimeEdit                   *_tme_time;
        QLineEdit                   *_txt_declarant;
        QLineEdit                   *_txt_declarant_phone;
        QLineEdit                   *_txt_declarant_address;
        QLineEdit                   *_txt_service_organization;
        QLineEdit                   *_txt_other_conflict_party;
        QLineEdit                   *_txt_organization;
        QTextEdit                   *_txt_request;
        QTextEdit                   *_txt_consultation;

        QToolButton                 *_btn_address_search;

        QPushButton                 *_btn_OK;
        QPushButton                 *_btn_cancel;

        data_request                _request;
        dialog_request_data_mode    _mode;

        //helper objects
        data_address                _address;
        data_so                     _so;

	};//class dialog_request_data
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator
#endif // __DIALOG_REQUEST_DATA_H__
