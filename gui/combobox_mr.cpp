/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 17-09-2013
///		Date update	: 01-10-2013
///		Comment		:
/// ============================================================================
#include "combobox_mr.h"

#include "application.h"
#include "business_logic.h"
#include "data_model_mr.h"
#include "data_adapter_mr.h"

namespace mac_mediator
{

/// ############################################################################
///			class combobox_mr
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	combobox_mr( )
    /// ------------------------------------------------------------------------
    combobox_mr::combobox_mr(QWidget *parent) :
        QComboBox(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_mr( )
    /// ------------------------------------------------------------------------
    combobox_mr::~combobox_mr( )
    {

    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	id_mr( )
    /// ------------------------------------------------------------------------
    int combobox_mr::id_mr( ) const
    {
        if( this->currentIndex( ) == -1 )
        {
            return -1;
        }
        return this->itemData( this->currentIndex( ) ).toInt( );
    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void combobox_mr::initialize( )
    {
    }
    /// ------------------------------------------------------------------------
	///	refresh_data( )
    /// ------------------------------------------------------------------------
    void combobox_mr::refresh_data( )
    {
        this->clear( );

        const data_mr_list& list =
                    application::the_business_logic().model_mr( )->list( );
        if( !list.size() )
        {
            return;
        }

        this->addItem( "", -1 );
        for( int i=0; i<list.size();++i)
        {
            const data_mr *mr = list.at(i);
            this->addItem( mr->mr_title( ), mr->mr_id( ) );
        }
    }

    /// ------------------------------------------------------------------------
	///	set_id_mr( const int id_mr )
    /// ------------------------------------------------------------------------
    void combobox_mr::set_id_mr( const int id_mr )
    {
        int index = this->findData( id_mr );
        if( index >= 0 )
        {
            this->setCurrentIndex( index );
        }
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	requery( )
    /// ------------------------------------------------------------------------
    void combobox_mr::requery( int i_ad )
    {
        application::the_business_logic( ).mr_select(i_ad);
        this->refresh_data( );
    }
}//namespace mac_mediator
