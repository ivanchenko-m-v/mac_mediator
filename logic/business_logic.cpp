/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 19-09-2013
///		Date update	: 31-01-2014
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QMessageBox>
#include <QStringList>

#include "application.h"
#include "business_logic.h"
#include "data_model_ad.h"
#include "data_model_mr.h"
#include "data_model_mediator.h"
#include "data_model_request.h"
#include "data_model_request_category.h"
#include "data_model_address.h"
#include "data_model_declarant_type.h"

#include "data_adapter_ad.h"
#include "data_adapter_mr.h"
#include "data_adapter_request_category.h"
#include "data_adapter_mediator.h"
#include "data_adapter_request.h"
#include "data_adapter_address.h"
#include "data_adapter_so.h"
#include "data_adapter_declarant_type.h"

namespace mac_mediator
{

/// ############################################################################
///			class business_logic
/// ############################################################################

	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
    /// ------------------------------------------------------------------------
    ///	free_memory( )
    /// ------------------------------------------------------------------------
    void business_logic::free_memory( )
    {
        if( this->_model_ad )
        {
            delete _model_ad;
        }
        if( this->_model_mr )
        {
            delete _model_mr;
        }
        if( this->_model_mediator )
        {
            delete _model_mediator;
        }
        if( this->_model_request )
        {
            delete _model_request;
        }
        if( this->_model_request_category )
        {
            delete _model_request_category;
        }
        if( this->_model_address )
        {
            delete _model_address;
        }
        if( this->_model_declarant_type )
        {
            delete _model_declarant_type;
        }
    }

	/// ------------------------------------------------------------------------
	///	init( )
    /// ------------------------------------------------------------------------
	void business_logic::init( )
	{
		try
		{
            //this->init_db_path( );
            this->init_data_models( );
		}
		catch( std::exception &ex )
		{
			QString s_msg(
							"business_logic::init( )"
							":\n\t" + QString::fromUtf8( ex.what( ) )
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
		catch( ... )
		{
			QString s_msg(
						"business_logic::init( )"
						":\n\t unknown error while initialize business logic"
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
	}
	/// ------------------------------------------------------------------------
	///	exit( )
    /// ------------------------------------------------------------------------
	void business_logic::exit( )
	{
        this->free_memory( );

		qDebug( ) << "correctly exiting business logic";
	}

	///------------------------------------------------------------------------
	///	init_data_models( )
	///
    void business_logic::init_data_models( )
    {
        this->init_model_ad( );

        this->init_model_mr( );

        this->init_model_mediator( );

        this->init_model_request( );

        this->init_model_request_category( );

        this->init_model_address( );

        this->init_model_declarant_type( );
    }

	///------------------------------------------------------------------------
	///	init_model_ad( )
	///
    void business_logic::init_model_ad( )
    {
        this->_model_ad = new data_model_ad;
        //this->ad_select( );
    }
	///------------------------------------------------------------------------
	///	init_model_mr( )
	///
    void business_logic::init_model_mr( )
    {
        this->_model_mr = new data_model_mr;
    }
    /// ------------------------------------------------------------------------
	///	init_model_mediator( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_mediator( )
    {
        this->_model_mediator = new data_model_mediator;
        //this->mediator_select( );
    }
	///------------------------------------------------------------------------
	///	init_model_request( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_request( )
    {
        this->_model_request = new data_model_request;
    }

	///------------------------------------------------------------------------
    ///	init_model_request_category( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_request_category( )
    {
        this->_model_request_category = new data_model_request_category;
        this->request_category_select( );
    }

    ///------------------------------------------------------------------------
    ///	init_model_declarant_type( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_declarant_type( )
    {
        this->_model_declarant_type = new data_model_declarant_type;
        this->declarant_type_select( );
    }

    ///------------------------------------------------------------------------
	///	init_model_address( )
    /// ------------------------------------------------------------------------
    void business_logic::init_model_address( )
    {
        this->_model_address = new data_model_address;
    }

    /// ------------------------------------------------------------------------
	///	ad_select( )
    /// ------------------------------------------------------------------------
    void business_logic::ad_select( )
    {
        data_ad_collection *p_coll = 0;
        int id_authorized_mediator = application::program_instance( )->
                                          authorized_mediator( ).mediator_id( );
        try
		{
            data_adapter_ad ap_ad;
			//select data
            if( !id_authorized_mediator )
            {
                p_coll = ap_ad.select( );
            }
            else
            {
                p_coll = ap_ad.select( id_authorized_mediator );

            }
			//refresh data model
			this->_model_ad->refresh( p_coll );
		}
		catch( std::exception &ex )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
							"business_logic::ad_select( )"
							":\n\t" + QString::fromUtf8( ex.what( ) )
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
		catch( ... )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
						"business_logic::ad_select( )"
						":\n\t unknown error while ADs select"
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
    }

    /// ------------------------------------------------------------------------
	///	mr_select( int i_ad )
    /// ------------------------------------------------------------------------
    void business_logic::mr_select( int i_ad )
    {
        //при перезапросе очищаем модель данных
        //безусловно
        this->_model_mr->clear( );

        data_mr_collection *p_coll = 0;
        try
		{
            if( i_ad <= 0 )
            {
                return;
            }
            data_adapter_mr ap_mr;
			//select data
            data_mr mr;
            mr.ad_id(i_ad);
			p_coll = ap_mr.select( mr );
			//refresh data model
			this->_model_mr->refresh( p_coll );
		}
		catch( std::exception &ex )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
							"business_logic::ad_select( )"
							":\n\t" + QString::fromUtf8( ex.what( ) )
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
		catch( ... )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
						"business_logic::ad_select( )"
						":\n\t unknown error while ADs select"
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
    }

    /// ------------------------------------------------------------------------
	///	request_category_select( )
    /// ------------------------------------------------------------------------
    void business_logic::request_category_select( )
    {
        data_request_category_collection *p_coll = 0;
        try
		{
            data_adapter_request_category ap_rc;
			//select data
			p_coll = ap_rc.select( );
			//refresh data model
			this->_model_request_category->refresh( p_coll );
		}
		catch( std::exception &ex )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
							"business_logic::request_category_select( )"
							":\n\t" + QString::fromUtf8( ex.what( ) )
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
		catch( ... )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
						"business_logic::request_category_select( )"
						":\n\t unknown error while request categories select"
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
    }

    /// ------------------------------------------------------------------------
    ///	declarant_type_select( )
    /// ------------------------------------------------------------------------
    void business_logic::declarant_type_select( )
    {
        data_declarant_type_collection *p_coll = 0;
        try
        {
            data_adapter_declarant_type ap_dt;
            //select data
            p_coll = ap_dt.select( );
            //refresh data model
            this->_model_declarant_type->refresh( p_coll );
        }
        catch( std::exception &ex )
        {
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
            QString s_msg(
                            "business_logic::declarant_type_select( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
            QString s_msg(
                        "business_logic::declarant_type_select( )"
                        ":\n\t unknown error while request categories select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
    }

    /// ------------------------------------------------------------------------
	///	mediator_select( )
    /// ------------------------------------------------------------------------
    void business_logic::mediator_select( )
    {
        data_mediator_collection *p_coll = 0;
        const data_mediator &mediator = application::program_instance( )->
                authorized_mediator( );
         try
		{
            data_adapter_mediator ap_mediator;
			//select data
            if(
                ( !mediator.mediator_id( ) ) ||
                ( mediator.permissions( ) == "su" )
              )
            {
                p_coll = ap_mediator.select( );
            }
            else
            {
                p_coll = ap_mediator.select( mediator.mediator_id( ) );

            }
			//refresh data model
			this->_model_mediator->refresh( p_coll );
		}
		catch( std::exception &ex )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
							"business_logic::mediator_select( )"
							":\n\t" + QString::fromUtf8( ex.what( ) )
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
		catch( ... )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
						"business_logic::mediator_select( )"
						":\n\t unknown error while mediators select"
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
    }

    /// ------------------------------------------------------------------------
    ///	mediator_select_authorized( )
    /// ------------------------------------------------------------------------
    data_mediator* business_logic::mediator_select_authorized(
                                                         const QString &x_login,
                                                         const QString &x_hash
                                                             )
    {
        data_mediator* p_mediator = 0;

        try
        {
            data_adapter_mediator ap_mediator;
            //select data
            p_mediator = ap_mediator.select_authorized( x_login, x_hash );
            //select permissions
            p_mediator->permissions(
                        ap_mediator.select_permissions( p_mediator->mediator_id( ) )
                                   );
        }
        catch( std::exception &ex )
        {
            if( p_mediator )
            {
                delete p_mediator;
                p_mediator = 0;
            }
            QString s_msg(
                            "business_logic::mediator_select_authorized( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
            if( p_mediator )
            {
                delete p_mediator;
                p_mediator = 0;
            }
            QString s_msg(
                        "business_logic::mediator_select_authorized( )"
                        ":\n\t unknown error while mediators select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }

        return p_mediator;
    }

    /// ------------------------------------------------------------------------
    ///	request_new_id( )
    /// ------------------------------------------------------------------------
   int business_logic::request_new_id( int i_ad, const QDate &dt )
   {
       int id_new = 0;
       try
       {
           data_adapter_request ap_request;
           //select data
           id_new = ap_request.newkey( i_ad, dt );
       }
       catch( std::exception &ex )
       {
           id_new = 0;
           QString s_msg(
                           "business_logic::request_new_id( )"
                           ":\n\t" + QString::fromUtf8( ex.what( ) )
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
       }
       catch( ... )
       {
           id_new = 0;
           QString s_msg(
                       "business_logic::request_new_id( )"
                       ":\n\t unknown error while request_ID select"
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
       }

       return id_new;
   }

   /// ------------------------------------------------------------------------
   ///	request_insert( const data_request &request )
   /// ------------------------------------------------------------------------
   bool business_logic::request_insert( const data_request& request )
   {
       try
       {
           data_adapter_request ap_request;
           ap_request.insert( request );
           if( this->_model_request )
           {
               //this->_model_request->insert( request );
           }
       }
       catch( std::exception &ex )
       {
           QString s_msg(
                           "business_logic::request_insert( )"
                           ":\n\t" + QString::fromUtf8( ex.what( ) )
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }
       catch( ... )
       {
           QString s_msg(
                       "business_logic::request_insert( )"
                       ":\n\t unknown error while request inserting"
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }

       return true;
   }
   /// ------------------------------------------------------------------------
   ///	request_update( const data_request &request )
   /// ------------------------------------------------------------------------
   bool business_logic::request_update( const data_request& request )
   {
       try
       {
           data_adapter_request ap_request;
           ap_request.update( request );
       }
       catch( std::exception &ex )
       {
           QString s_msg(
                           "business_logic::request_update( )"
                           ":\n\t" + QString::fromUtf8( ex.what( ) )
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }
       catch( ... )
       {
           QString s_msg(
                       "business_logic::request_update( )"
                       ":\n\t unknown error while request updating"
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }

       return true;
   }

   bool business_logic::request_update_id(int id_old, int id_new)
   {
       try
       {
           data_adapter_request ap_request;
           ap_request.update_id( id_old, id_new );
       }
       catch( std::exception &ex )
       {
           QString s_msg(
                           "business_logic::request_update_id( )"
                           ":\n\t" + QString::fromUtf8( ex.what( ) )
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }
       catch( ... )
       {
           QString s_msg(
                       "business_logic::request_update_id( )"
                       ":\n\t unknown error while request ID updating"
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }

       return true;
   }

   /// ------------------------------------------------------------------------
   ///	request_delete( const int id_request )
   /// ------------------------------------------------------------------------
   bool business_logic::request_delete( const int id_request )
   {
       try
       {
           data_adapter_request ap_request;
           ap_request.del( id_request );
       }
       catch( std::exception &ex )
       {
           QString s_msg(
                           "business_logic::request_delete( )"
                           ":\n\t" + QString::fromUtf8( ex.what( ) )
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }
       catch( ... )
       {
           QString s_msg(
                       "business_logic::request_delete( )"
                       ":\n\t unknown error while request deleting"
                        );
           qDebug( ) << s_msg;
           QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );

           return false;
       }

       return true;
   }

   /// ------------------------------------------------------------------------
   ///	request_select( const data_request_search_criteria &request )
   /// ------------------------------------------------------------------------
   void business_logic::request_select( const data_request_search_criteria &criteria )
   {
        data_request_collection *p_coll = 0;
        try
		{
            data_adapter_request ap_request;
			//select data
			p_coll = ap_request.select( criteria );
			//refresh data model
			this->_model_request->refresh( p_coll );
		}
		catch( std::exception &ex )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
							"business_logic::request_select( )"
							":\n\t" + QString::fromUtf8( ex.what( ) )
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
		catch( ... )
		{
            if( p_coll )
            {
                delete p_coll;
                p_coll = 0;
            }
			QString s_msg(
						"business_logic::request_select( )"
						":\n\t unknown error while requests select"
						 );
			qDebug( ) << s_msg;
			QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
		}
   }

    /// ------------------------------------------------------------------------
    ///	address_select( const QString &criteria )
    /// ------------------------------------------------------------------------
    void business_logic::address_select( const QString &criteria )
    {
         data_address_collection *p_coll = 0;
         try
        {
             data_adapter_address ap_address;
            //select data
            p_coll = ap_address.select( criteria );
            //refresh data model
            this->_model_address->refresh( p_coll );
        }
        catch( std::exception &ex )
        {
             if( p_coll )
             {
                 delete p_coll;
                 p_coll = 0;
             }
            QString s_msg(
                            "business_logic::address_select( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
             if( p_coll )
             {
                 delete p_coll;
                 p_coll = 0;
             }
            QString s_msg(
                        "business_logic::address_select( )"
                        ":\n\t unknown error while addresss select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
         }
    }

    /// ------------------------------------------------------------------------
    ///	so_select( const long long &id_TIB )
    /// ------------------------------------------------------------------------
    data_so* business_logic::so_select( const long long &id_TIB )
    {
         data_so *p_so = 0;
         try
        {
             data_adapter_so ap_so;
            //select data
            p_so = ap_so.select( id_TIB );
        }
        catch( std::exception &ex )
        {
             if( p_so )
             {
                 delete p_so;
                 p_so = 0;
             }
            QString s_msg(
                            "business_logic::so_select( )"
                            ":\n\t" + QString::fromUtf8( ex.what( ) )
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
        }
        catch( ... )
        {
             if( p_so )
             {
                 delete p_so;
                 p_so = 0;
             }
            QString s_msg(
                        "business_logic::so_select( )"
                        ":\n\t unknown error while addresss select"
                         );
            qDebug( ) << s_msg;
            QMessageBox::critical( 0, QObject::tr( "critical" ), s_msg );
         }

         return p_so;
    }
	/// ========================================================================
	///		SLOTS
	/// ========================================================================

/// ############################################################################

}//namespace mac_mediator
