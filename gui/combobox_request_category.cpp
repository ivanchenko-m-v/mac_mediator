/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 17-09-2013
///		Date update	: 30-01-2014
///		Comment		:
/// ============================================================================
#include "application.h"
#include "business_logic.h"

#include "combobox_request_category.h"

#include "data_model_request_category.h"
#include "data_adapter_request_category.h"

namespace mac_mediator
{

/// ############################################################################
///			class combobox_request_category
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	combobox_request_category( )
    /// ------------------------------------------------------------------------
    combobox_request_category::combobox_request_category(QWidget *parent) :
        QComboBox(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_request_category( )
    /// ------------------------------------------------------------------------
    combobox_request_category::~combobox_request_category( )
    {

    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// id_request_category( )
    /// ------------------------------------------------------------------------
    int combobox_request_category::id_request_category( ) const
    {
        int index = this->currentIndex( );
        if( index == -1 )
        {
            return -1;
        }
        return this->itemData( index ).toInt( );
    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void combobox_request_category::initialize( )
    {
        const data_request_category_list &list =
                    application::the_business_logic( )
                        .model_request_type( )->list( );
        if( !list.size() )
        {
            return;
        }

        this->addItem( "", -1 );
        for( int i=0; i<list.size();++i)
        {
            const data_request_category *rc = list.at(i);
            this->addItem( rc->request_category( ), rc->request_category_id( ) );
        }

    }

    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void combobox_request_category::set_id_request_category( const int id_request_category )
    {
        int index = this->findData( id_request_category );
        if( index >= 0 )
        {
            this->setCurrentIndex( index );
        }
    }

}//namespace mac_mediator
