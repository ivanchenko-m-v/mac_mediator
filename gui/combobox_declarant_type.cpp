/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 30-01-2014
///		Date update	: 30-01-2014
///		Comment		:
/// ============================================================================
#include "combobox_declarant_type.h"

#include "application.h"
#include "business_logic.h"

#include "data_model_declarant_type.h"
#include "data_adapter_declarant_type.h"

namespace mac_mediator
{

/// ############################################################################
///			class combobox_declarant_type
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	combobox_declarant_type( )
    /// ------------------------------------------------------------------------
    combobox_declarant_type::combobox_declarant_type(QWidget *parent) :
        QComboBox(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_declarant_type( )
    /// ------------------------------------------------------------------------
    combobox_declarant_type::~combobox_declarant_type( )
    {

    }
    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	id_declarant_type( )
    /// ------------------------------------------------------------------------
    int combobox_declarant_type::id_declarant_type( )
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
    void combobox_declarant_type::initialize( )
    {
        const data_declarant_type_list& list =
                application::the_business_logic().model_declarant_type( )->list( );
        if( !list.size() )
        {
            return;
        }

        this->addItem( "", -1 );
        for( int i=0; i<list.size();++i)
        {
            const data_declarant_type *dt = list.at(i);
            this->addItem( dt->declarant_type_title( ), dt->id_declarant_type( ) );
        }
    }

    /// ------------------------------------------------------------------------
    ///	set_id_declarant_type( )
    /// ------------------------------------------------------------------------
    void combobox_declarant_type::set_id_declarant_type( const int id_declarant_type )
    {
        int index = this->findData( id_declarant_type );
        if( index >= 0 )
        {
            this->setCurrentIndex( index );
        }
    }

}//namespace mac_mediator
