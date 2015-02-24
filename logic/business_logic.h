/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 19-09-2013
///		Date update	: 31-01-2014
///		Comment		:
/// ============================================================================
#ifndef __BUSINESS_LOGIC_H__
#define __BUSINESS_LOGIC_H__

#include "application.h"
#include <QDate>

namespace mac_mediator
{

class data_model_ad;
class data_model_mr;
class data_model_mediator;
class data_model_request_category;
class data_model_request;
class data_model_address;
class data_model_declarant_type;
class data_mediator;
class data_request;
class data_request_search_criteria;
class data_so;
/// ############################################################################
///			class business_logic
/// ############################################################################
	class business_logic
	{
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		business_logic( const business_logic &rhs );

	public:
	/// ------------------------------------------------------------------------
		business_logic( ) :
            _db_path(""),
            _model_ad(0),
            _model_mr(0),
            _model_mediator(0),
            _model_request(0),
            _model_request_category(0),
            _model_address(0),
            _model_declarant_type(0)
		{ }

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        const QString& db_path( ) const
        { return this->_db_path; }

        void db_path( const QString& db_path)
        { this->_db_path = db_path; }
    /// ------------------------------------------------------------------------
        data_model_ad* model_ad( ) const
        { return this->_model_ad; }
    /// ------------------------------------------------------------------------
        data_model_mr* model_mr( ) const
        { return this->_model_mr; }
    /// ------------------------------------------------------------------------
        data_model_mediator* model_mediator( ) const
        { return this->_model_mediator; }
    /// ------------------------------------------------------------------------
        data_model_request* model_request( ) const
        { return this->_model_request; }
    /// ------------------------------------------------------------------------
        data_model_request_category* model_request_type( ) const
        { return this->_model_request_category; }
    /// ------------------------------------------------------------------------
        data_model_address* model_address( ) const
        { return this->_model_address; }
    /// ------------------------------------------------------------------------
        data_model_declarant_type* model_declarant_type( ) const
        { return this->_model_declarant_type; }

    /// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
        void init_data_models( );
	/// ------------------------------------------------------------------------
        void init_model_ad( );
	/// ------------------------------------------------------------------------
        void init_model_mr( );
    /// ------------------------------------------------------------------------
        void init_model_mediator( );
	/// ------------------------------------------------------------------------
        void init_model_request( );
	/// ------------------------------------------------------------------------
        void init_model_request_category( );
	/// ------------------------------------------------------------------------
        void init_model_address( );
    /// ------------------------------------------------------------------------
        void init_model_declarant_type( );
    /// ------------------------------------------------------------------------
        void free_memory( );

	public:
	/// ------------------------------------------------------------------------
		void init( );
	/// ------------------------------------------------------------------------
		void exit( );

	/// ------------------------------------------------------------------------
        void ad_select( );
    /// ------------------------------------------------------------------------
        void mr_select( int i_ad );
    /// ------------------------------------------------------------------------
        void request_category_select( );
    /// ------------------------------------------------------------------------
        void declarant_type_select( );
    /// ------------------------------------------------------------------------
        void mediator_select( );
    /// ------------------------------------------------------------------------
        data_mediator* mediator_select_authorized(
                                        const QString &x_login,
                                        const QString &x_hash
                                       );
    /// ------------------------------------------------------------------------
        int request_new_id( int i_ad, const QDate &dt );
    /// ------------------------------------------------------------------------
        bool request_insert( const data_request &request );
    /// ------------------------------------------------------------------------
        bool request_update( const data_request &request );
    /// ------------------------------------------------------------------------
        bool request_update_id( int id_old, int id_new );
    /// ------------------------------------------------------------------------
        bool request_delete(const int id_request);
    /// ------------------------------------------------------------------------
        void request_select( const data_request_search_criteria &criteria );
    /// ------------------------------------------------------------------------
        void address_select(const QString &criteria);
    /// ------------------------------------------------------------------------
        data_so* so_select(const long long &id_TIB );

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
		business_logic& operator=( const business_logic &rhs );

	public:

	/// ========================================================================
	///		FIELDS
    /// ========================================================================
    private:
        QString _db_path;

        data_model_ad               *_model_ad;
        data_model_mr               *_model_mr;
        data_model_mediator         *_model_mediator;
        data_model_request          *_model_request;
        data_model_request_category *_model_request_category;
        data_model_address          *_model_address;
        data_model_declarant_type   *_model_declarant_type;

	};//class business_logic

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __BUSINESS_LOGIC_H__
