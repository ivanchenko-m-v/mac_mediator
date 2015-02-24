/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 12-11-2013
///		Date update	: 12-11-2013
///		Comment		:
/// ============================================================================
#include <QDialog>
#include <QWidget>
#include <QDateTimeEdit>
#include <QPushButton>

#ifndef __DIALOG_PERIOD_H__
#define __DIALOG_PERIOD_H__

namespace mac_mediator
{
/// ############################################################################
///			class dialog_period
/// ############################################################################
    class dialog_period : public QDialog
	{
	Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        dialog_period( const dialog_period &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit dialog_period( QWidget *parent = 0, Qt::WindowFlags f = 0 );
        /// --------------------------------------------------------------------
        virtual ~dialog_period( );

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
        QWidget* init_period( );
        /// --------------------------------------------------------------------
        QWidget* init_date_from( );
        /// --------------------------------------------------------------------
        QWidget* init_date_to( );
        /// --------------------------------------------------------------------
        QWidget* init_buttons( );

	public:

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
        /// --------------------------------------------------------------------
        QDate date_from( ) const
        {
            return this->_dte_from->date( );
        }
        /// --------------------------------------------------------------------
        QDate date_to( ) const
        {
            return this->_dte_to->date( );
        }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        dialog_period& operator=( const dialog_period &rhs );

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    private slots:

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        QDateTimeEdit   *_dte_from;
        QDateTimeEdit   *_dte_to;

        QPushButton *_btn_ok;
        QPushButton *_btn_cancel;

	};//class dialog_period
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DIALOG_PERIOD_H__