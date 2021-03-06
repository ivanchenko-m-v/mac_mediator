/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 30-01-2014
///		Date update	: 30-01-2014
///		Comment		:
/// ============================================================================
#ifndef __COMBOBOX_DECLARANT_TYPE_H__
#define __COMBOBOX_DECLARANT_TYPE_H__

#include <QComboBox>

namespace mac_mediator
{

/// ############################################################################
///			class combobox_declarant_type
/// ############################################################################
    class combobox_declarant_type : public QComboBox
	{
        Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        combobox_declarant_type( const combobox_declarant_type &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit combobox_declarant_type(QWidget *parent = 0);
        /// --------------------------------------------------------------------
        virtual ~combobox_declarant_type( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
        /// --------------------------------------------------------------------
        int id_declarant_type( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
	public:
        /// --------------------------------------------------------------------
        void set_id_declarant_type( const int id );

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
        combobox_declarant_type& operator=( const combobox_declarant_type &rhs );

	public:

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:

    };//class combobox_declarant_type
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator
#endif // __COMBOBOX_DECLARANT_TYPE_H__
