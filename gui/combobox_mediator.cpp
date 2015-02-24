/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 17-09-2013
///		Date update	: 30-01-2014
///		Comment		:
/// ============================================================================
#include "combobox_mediator.h"

#include "application.h"
#include "business_logic.h"

#include "data_model_mediator.h"
#include "data_adapter_mediator.h"

namespace mac_mediator
{

/// ############################################################################
///			class combobox_mediator
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	combobox_mediator( )
    /// ------------------------------------------------------------------------
    combobox_mediator::combobox_mediator(QWidget *parent) :
        QComboBox(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_mediator( )
    /// ------------------------------------------------------------------------
    combobox_mediator::~combobox_mediator( )
    {

    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	id_mediator( )
    /// ------------------------------------------------------------------------
    int combobox_mediator::id_mediator( ) const
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
    ///	combobox_mediator( )
    /// ------------------------------------------------------------------------
    void combobox_mediator::initialize( )
    {
        const data_mediator_list& list =
                    application::the_business_logic( ).model_mediator( )->list( );
        if( !list.size( ) )
        {
            return;
        }

        if( list.size( ) == 1 )
        {
            const data_mediator *mediator = list.at( 0 );
            this->addItem( mediator->mediator( ), mediator->mediator_id( ) );
            this->setCurrentIndex( 0 );

            return;
        }

        this->addItem( "", -1 );
        for( int i=0; i<list.size();++i)
        {
            const data_mediator *mediator = list.at( i );
            this->addItem( mediator->mediator( ), mediator->mediator_id( ) );
        }
    }

    /// ------------------------------------------------------------------------
    ///	combobox_mediator( )
    /// ------------------------------------------------------------------------
    void combobox_mediator::set_id_mediator( const int id_mediator )
    {
        int index = this->findData( id_mediator );
        if( index >= 0 )
        {
            this->setCurrentIndex( index );
        }
    }

}//namespace mac_mediator
