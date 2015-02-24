///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-09-2013
///		Date update	: 01-02-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_REQUEST_H__
#define __DATA_ADAPTER_REQUEST_H__

#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>
#include <QVector>
#include <QVariant>
#include <QSharedPointer>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace mac_mediator
{

/// ############################################################################
///			class data_request
/// ############################################################################
    class data_request
	{
        enum field_data_request
        {
            num_field_request_id = 0,
            num_field_declarant_type = 1,
            num_field_mr = 2,
            num_field_mediator = 3,
            num_field_request_category = 4,
            num_field_date = 5,
            num_field_time = 6,
            num_field_declarant = 7,
            num_field_declarant_phone = 8,
            num_field_declarant_address = 9,
            num_field_service_organization = 10,
            num_field_request = 11,
            num_field_other_conflict_party = 12,
            num_field_organization = 13,
            num_field_consultation = 14,
            num_field_ad = 15,
            num_field_ad_title = 16,
            num_field_mr_title = 17,
            num_field_mediator_name =18,
            num_field_mediator_phone =19,
            num_field_request_category_title = 20,
            num_field_declarant_type_title = 21,
            fields_count = 22
        };
    /// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
        data_request( ) :
            _i_request(0),
            _i_declarant_type(0),
            _i_mr(0),
            _i_mediator(0),
            _i_request_category(0),
            _dt_request(""),
            _tm_request(""),
            _x_declarant(""),
            _x_declarant_phone(""),
            _x_declarant_address(""),
            _x_service_organization(""),
            _x_request(""),
            _x_other_conflict_party(""),
            _x_organization(""),
            _x_consultation(""),
            _i_ad(0),
            _x_ad(""),
            _x_mr(""),
            _x_mediator(""),
            _x_mediator_phone(""),
            _x_request_category(""),
            _x_declarant_type("")
        { }

	/// ------------------------------------------------------------------------
		explicit
        data_request( const data_request &rhs ) :
            _i_request( rhs._i_request ),
            _i_declarant_type( rhs._i_declarant_type ),
            _i_mr( rhs._i_mr ),
            _i_mediator( rhs._i_mediator ),
            _i_request_category( rhs._i_request_category ),
            _dt_request( rhs._dt_request ),
            _tm_request( rhs._tm_request ),
            _x_declarant( rhs._x_declarant ),
            _x_declarant_phone( rhs._x_declarant_phone ),
            _x_declarant_address( rhs._x_declarant_address ),
            _x_service_organization( rhs._x_service_organization ),
            _x_request( rhs._x_request ),
            _x_other_conflict_party( rhs._x_other_conflict_party ),
            _x_organization( rhs._x_organization ),
            _x_consultation( rhs._x_consultation ),
            _i_ad( rhs._i_ad ),
            _x_ad( rhs._x_ad ),
            _x_mr( rhs._x_mr ),
            _x_mediator( rhs._x_mediator ),
            _x_mediator_phone( rhs._x_mediator_phone ),
            _x_request_category( rhs._x_request_category ),
            _x_declarant_type( rhs._x_declarant_type )
        { }

	/// ------------------------------------------------------------------------
		explicit
        data_request( const QVector<QVariant> &row )
        {
            this->clear_data( );

            int i_fields_num = row.size( );

            if( i_fields_num < num_field_request_id ) return;
            _i_request = row[num_field_request_id].toInt( );

            if( i_fields_num < num_field_declarant_type ) return;
            _i_declarant_type = row[num_field_declarant_type].toInt( );

            if( i_fields_num < num_field_mr ) return;
            _i_mr = row[num_field_mr].toInt( );

            if( i_fields_num < num_field_mediator ) return;
            _i_mediator = row[num_field_mediator].toInt( );

            if( i_fields_num < num_field_request_category ) return;
            _i_request_category = row[num_field_request_category].toInt( );

            if( i_fields_num < num_field_date ) return;
            _dt_request = row[num_field_date].toString( );

            if( i_fields_num < num_field_time ) return;
            _tm_request = row[num_field_time].toString( );

            if( i_fields_num < num_field_declarant ) return;
            _x_declarant = row[num_field_declarant].toString( );

            if( i_fields_num < num_field_declarant_phone ) return;
            _x_declarant_phone = row[num_field_declarant_phone].toString( );

            if( i_fields_num < num_field_declarant_address ) return;
            _x_declarant_address = row[num_field_declarant_address].toString( );

            if( i_fields_num < num_field_service_organization ) return;
            _x_service_organization = row[num_field_service_organization].toString( );

            if( i_fields_num < num_field_request ) return;
            _x_request = row[num_field_request].toString( );

            if( i_fields_num < num_field_other_conflict_party ) return;
            _x_other_conflict_party = row[num_field_other_conflict_party].toString( );

            if( i_fields_num < num_field_organization ) return;
            _x_organization = row[num_field_organization].toString( );

            if( i_fields_num < num_field_consultation ) return;
            _x_consultation = row[num_field_consultation].toString( );

            if( i_fields_num < num_field_ad ) return;
            _i_ad = row[num_field_ad].toInt( );

            if( i_fields_num < num_field_ad_title ) return;
            _x_ad = row[num_field_ad_title].toString( );

            if( i_fields_num < num_field_mr_title ) return;
            _x_mr = row[num_field_mr_title].toString( );

            if( i_fields_num < num_field_mediator_name ) return;
            _x_mediator = row[num_field_mediator_name].toString( );

            if( i_fields_num < num_field_mediator_phone ) return;
            _x_mediator_phone = row[num_field_mediator_phone].toString( );

            if( i_fields_num < num_field_declarant_type_title ) return;
            _x_declarant_type = row[num_field_declarant_type_title].toString( );
        }

	/// ------------------------------------------------------------------------
		explicit
        data_request( espira::db::qt_data_row *p_row )
		{
            this->clear_data( );

            int i_fields_num = p_row->columns_count( );

            if( i_fields_num < num_field_request_id ) return;
            _i_request = (*p_row)[num_field_request_id].toInt( );

            if( i_fields_num < num_field_declarant_type ) return;
            _i_declarant_type = (*p_row)[num_field_declarant_type].toInt( );

            if( i_fields_num < num_field_mr ) return;
            _i_mr = (*p_row)[num_field_mr].toInt( );

            if( i_fields_num < num_field_mediator ) return;
            _i_mediator = (*p_row)[num_field_mediator].toInt( );

            if( i_fields_num < num_field_request_category ) return;
            _i_request_category = (*p_row)[num_field_request_category].toInt( );

            if( i_fields_num < num_field_date ) return;
            _dt_request = (*p_row)[num_field_date].toString( );

            if( i_fields_num < num_field_time ) return;
            _tm_request = (*p_row)[num_field_time].toString( );

            if( i_fields_num < num_field_declarant ) return;
            _x_declarant = (*p_row)[num_field_declarant].toString( );

            if( i_fields_num < num_field_declarant_phone ) return;
            _x_declarant_phone = (*p_row)[num_field_declarant_phone].toString( );

            if( i_fields_num < num_field_declarant_address ) return;
            _x_declarant_address = (*p_row)[num_field_declarant_address].toString( );

            if( i_fields_num < num_field_service_organization ) return;
            _x_service_organization = (*p_row)[num_field_service_organization].toString( );

            if( i_fields_num < num_field_request ) return;
            _x_request = (*p_row)[num_field_request].toString( );

            if( i_fields_num < num_field_other_conflict_party ) return;
            _x_other_conflict_party = (*p_row)[num_field_other_conflict_party].toString( );

            if( i_fields_num < num_field_organization ) return;
            _x_organization = (*p_row)[num_field_organization].toString( );

            if( i_fields_num < num_field_consultation ) return;
            _x_consultation = (*p_row)[num_field_consultation].toString( );

            if( i_fields_num < num_field_ad ) return;
            _i_ad = (*p_row)[num_field_ad].toInt( );

            if( i_fields_num < num_field_ad_title ) return;
            _x_ad = (*p_row)[num_field_ad_title].toString( );

            if( i_fields_num < num_field_mr_title ) return;
            _x_mr = (*p_row)[num_field_mr_title].toString( );

            if( i_fields_num < num_field_mediator_name ) return;
            _x_mediator = (*p_row)[num_field_mediator_name].toString( );

            if( i_fields_num < num_field_mediator_phone ) return;
            _x_mediator_phone = (*p_row)[num_field_mediator_phone].toString( );

            if( i_fields_num < num_field_request_category_title ) return;
            _x_request_category = (*p_row)[num_field_request_category_title].toString( );

            if( i_fields_num < num_field_declarant_type_title ) return;
            _x_declarant_type = (*p_row)[num_field_declarant_type_title].toString( );
        }
	/// ------------------------------------------------------------------------
        ~data_request( )
		{
            qDebug( ) << "deleted : " << this->_i_request << " " +
                                         this->_dt_request + " " +
                                         this->_tm_request;
		}

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
		void clear_data( )
		{
            _i_request = 0;
            _i_declarant_type = 0;
            _i_mr = 0;
            _i_mediator = 0;
            _i_request_category = 0;
            _dt_request.clear( );
            _tm_request.clear( );
            _x_declarant.clear( );
            _x_declarant_phone.clear( );
            _x_declarant_address.clear( );
            _x_service_organization.clear( );
            _x_request.clear( );
            _x_other_conflict_party.clear( );
            _x_organization.clear( );
            _x_consultation.clear( );

            _i_ad = 0;
            _x_ad.clear( );
            _x_mr.clear( );
            _x_mediator.clear( );
            _x_mediator_phone.clear( );
            _x_request_category.clear( );
            _x_declarant_type.clear( );
        }

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
    ///	id_request
        int id_request( ) const
        { return this->_i_request; }

        QString id_request_string( ) const
        {
            int i_ad = this->_i_request>>24;
            QString x_ad( QString::number( i_ad ) );
            if( i_ad < 10 )
            {
                x_ad.prepend('0');
            }
            int i_num = this->_i_request&0xffff;
            QString x_num( QString::number( i_num ) );
            while( x_num.size( ) < 4 )
            {
                x_num.prepend('0');
            }

            return QString(x_ad + "-" + x_num);
        }

        void id_request( const int &i_request )
        { this->_i_request = i_request; }

    /// ------------------------------------------------------------------------
    ///	id_declarant_type
        int id_declarant_type( ) const
        { return this->_i_declarant_type; }

        void id_declarant_type( const int &i_declarant_type )
        { this->_i_declarant_type = i_declarant_type; }

    /// ------------------------------------------------------------------------
    ///	id_mr
        int id_mr( ) const
        { return this->_i_mr; }

        void id_mr( const int &i_mr )
        { this->_i_mr = i_mr; }

    /// ------------------------------------------------------------------------
    ///	id_mediator
        int id_mediator( ) const
        { return this->_i_mediator; }

        void id_mediator( const int &i_mediator )
        { this->_i_mediator = i_mediator; }

    /// ------------------------------------------------------------------------
    ///	id_request_category
        int id_request_category( ) const
        { return this->_i_request_category; }

        void id_request_category( const int &i_request_category )
        { this->_i_request_category = i_request_category; }

    /// ------------------------------------------------------------------------
    ///	date_request
        const QString& date_request( ) const
        { return this->_dt_request; }

        QDate date( ) const
        { return QDate::fromString( this->_dt_request, "yyyy-MM-dd" ); }

        void date_request( const QDate &dt_request )
        { this->_dt_request = dt_request.toString("yyyy-MM-dd"); }

	/// ------------------------------------------------------------------------
    ///	time_request
        const QString& time_request( ) const
        { return this->_tm_request; }

        QTime time( ) const
        { return QTime::fromString( this->_tm_request, "hh:mm" ); }

        void time_request( const QTime &tm_request )
        { this->_tm_request = tm_request.toString( "hh:mm" ); }

	/// ------------------------------------------------------------------------
    ///	declarant
        const QString& declarant( ) const
        { return this->_x_declarant; }

        void declarant( const QString &x_declarant )
        { this->_x_declarant = x_declarant; }

	/// ------------------------------------------------------------------------
    //	declarant_address
        const QString& declarant_address( ) const
        { return this->_x_declarant_address; }

        void declarant_address( const QString &x_declarant_address )
        { this->_x_declarant_address = x_declarant_address; }

	/// ------------------------------------------------------------------------
    ///	declarant_phone
        const QString& declarant_phone( ) const
        { return this->_x_declarant_phone; }

        void declarant_phone( const QString &x_declarant_phone )
        { this->_x_declarant_phone = x_declarant_phone; }

	/// ------------------------------------------------------------------------
    ///	service_organization
        const QString& service_organization( ) const
        { return this->_x_service_organization; }

        void service_organization( const QString &x_service_organization )
        { this->_x_service_organization = x_service_organization; }

	/// ------------------------------------------------------------------------
    ///	request
        const QString& request( ) const
        { return this->_x_request; }

        void request( const QString &x_request )
        { this->_x_request = x_request; }

	/// ------------------------------------------------------------------------
    ///	other_conflict_party
        const QString& other_conflict_party( ) const
        { return this->_x_other_conflict_party; }

        void other_conflict_party( const QString &x_other_conflict_party )
        { this->_x_other_conflict_party = x_other_conflict_party; }

    /// ------------------------------------------------------------------------
    ///	organization
        const QString& organization( ) const
        { return this->_x_organization; }

        void organization( const QString &x_organization )
        { this->_x_organization = x_organization; }

    /// ------------------------------------------------------------------------
    ///	consultation
        const QString& consultation( ) const
        { return this->_x_consultation; }

        void consultation( const QString &x_consultation )
        { this->_x_consultation = x_consultation; }

    /// ------------------------------------------------------------------------
    ///	id_ad
        int id_ad( ) const
        { return this->_i_ad; }

    /// ------------------------------------------------------------------------
    ///	ad_title
        const QString& ad_title( ) const
        { return this->_x_ad; }

    /// ------------------------------------------------------------------------
    ///	mr_title
        const QString& mr_title( ) const
        { return this->_x_mr; }

    /// ------------------------------------------------------------------------
    //	mediator_name
        const QString& mediator_name( ) const
        { return this->_x_mediator; }

    /// ------------------------------------------------------------------------
    ///	mediator_phone
        const QString& mediator_phone( ) const
        { return this->_x_mediator_phone; }

    /// ------------------------------------------------------------------------
    ///	request_category_title
        const QString& request_category_title( ) const
        { return this->_x_request_category; }

    /// ------------------------------------------------------------------------
    ///	declarant_type
        const QString& declarant_type( ) const
        { return this->_x_declarant_type; }


    /// ========================================================================
	///		OPERATORS
	/// ========================================================================
	public:
        data_request& operator=( const data_request &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            _i_request = rhs._i_request;
            _i_declarant_type = rhs._i_declarant_type;
            _i_mr = rhs._i_mr;
            _i_mediator = rhs._i_mediator;
            _i_request_category = rhs._i_request_category;
            _dt_request = rhs._dt_request;
            _tm_request = rhs._tm_request;
            _x_declarant = rhs._x_declarant;
            _x_declarant_phone = rhs._x_declarant_phone;
            _x_declarant_address = rhs._x_declarant_address;
            _x_service_organization = rhs._x_service_organization;
            _x_request = rhs._x_request;
            _x_other_conflict_party = rhs._x_other_conflict_party;
            _x_organization = rhs._x_organization;
            _x_consultation = rhs._x_consultation;
            _i_ad = rhs._i_ad;
            _x_ad = rhs._x_ad;
            _x_mr = rhs._x_mr;
            _x_mediator = rhs._x_mediator;
            _x_mediator_phone = rhs._x_mediator_phone;
            _x_request_category = rhs._x_request_category;
            _x_declarant_type = rhs._x_declarant_type;

			return *this;
		}

        QString to_string( ) const
        {
            QString s_result( "" );
            s_result += QString::number( this->_i_request ) + "\n";
            s_result += QString::number( this->_i_declarant_type ) + "\n";
            s_result += QString::number( this->_i_mr ) + "\n";
            s_result += QString::number( this->_i_mediator ) + "\n";
            s_result += QString::number( this->_i_request_category ) + "\n";
            s_result += this->_dt_request + "\n";
            s_result += this->_tm_request + "\n";
            s_result += this->_x_declarant + "\n";
            s_result += this->_x_declarant_phone + "\n";
            s_result += this->_x_declarant_address + "\n";
            s_result += this->_x_service_organization + "\n";
            s_result += this->_x_other_conflict_party + "\n";
            s_result += this->_x_organization + "\n";
            s_result += this->_x_request + "\n";
            s_result += this->_x_consultation + "\n";
            s_result += QString::number( this->_i_ad ) + "\n";
            s_result += this->_x_ad + "\n";
            s_result += this->_x_mr + "\n";
            s_result += this->_x_mediator + "\n";
            s_result += this->_x_mediator_phone + "\n";
            s_result += this->_x_request_category + "\n";
            s_result += this->_x_declarant_type + "\n";

            return s_result;
        }
	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
        int     _i_request;             //--id обращения
        int     _i_declarant_type;      //--id типа заявителя
        int     _i_mr;                  //--id муниципального района
        int     _i_mediator;            //--id медиатора
        int     _i_request_category;    //--id категории обращения
        QString _dt_request;            //--дата обращения
        QString _tm_request;            //--время обращения
        QString _x_declarant;           //--заявитель
        QString _x_declarant_phone;     //--телефон заявителя
        QString _x_declarant_address;	//--адрес заявителя
        QString _x_service_organization;//--управляющая компания
        QString _x_request;             //--суть обращения
        QString _x_other_conflict_party;//--вторая сторона конфликта
        QString _x_organization;        //--ответственная организация
        QString _x_consultation;		//--содержание консультации

        int     _i_ad;                  //--id АО
        QString _x_ad;                  //--АО
        QString _x_mr;                  //--муниципальный район
        QString _x_mediator;            //--медиатор
        QString _x_mediator_phone;      //--телефон медиатора
        QString _x_request_category;    //--категория обращения
        QString _x_declarant_type;      //--тип заявителя

    };//class data_request
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_request_search_criteria
/// ############################################################################
    class data_request_search_criteria
    {
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    public:
    /// ------------------------------------------------------------------------
        data_request_search_criteria( ) :
            _i_declarant_type(0),
            _i_ad(0),
            _i_mr(0),
            _i_mediator(0),
            _i_request_category(0),
            _dt_from(""),
            _dt_to(""),
            _x_declarant("")
        { }

    /// ------------------------------------------------------------------------
        explicit
        data_request_search_criteria( const data_request_search_criteria &rhs ) :
            _i_declarant_type( rhs._i_declarant_type ),
            _i_ad( rhs._i_ad ),
            _i_mr( rhs._i_mr ),
            _i_mediator( rhs._i_mediator ),
            _i_request_category( rhs._i_request_category ),
            _dt_from( rhs._dt_from ),
            _dt_to( rhs._dt_to ),
            _x_declarant( rhs._x_declarant )
        { }

    /// ------------------------------------------------------------------------
        ~data_request_search_criteria( )
        { }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    public:
    /// ------------------------------------------------------------------------
        void clear_data( )
        {
            _i_declarant_type = 0;
            _i_ad = 0;
            _i_mr = 0;
            _i_mediator = 0;
            _i_request_category = 0;
            _dt_from.clear( );
            _dt_to.clear( );
            _x_declarant.clear( );
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    public:
    /// ------------------------------------------------------------------------
    ///	id_declarant_type
        int id_declarant_type( ) const
        { return this->_i_declarant_type; }

        void id_declarant_type( const int &i_declarant_type )
        { this->_i_declarant_type = i_declarant_type; }

    /// ------------------------------------------------------------------------
    ///	id_ad
        int id_ad( ) const
        { return this->_i_ad; }

        void id_ad( const int &i_ad )
        { this->_i_ad = i_ad; }

    /// ------------------------------------------------------------------------
    ///	id_mr
        int id_mr( ) const
        { return this->_i_mr; }

        void id_mr( const int &i_mr )
        { this->_i_mr = i_mr; }

    /// ------------------------------------------------------------------------
    ///	id_mediator
        int id_mediator( ) const
        { return this->_i_mediator; }

        void id_mediator( const int &i_mediator )
        { this->_i_mediator = i_mediator; }

    /// ------------------------------------------------------------------------
    ///	id_request_category
        int id_request_category( ) const
        { return this->_i_request_category; }

        void id_request_category( const int &i_request_category )
        { this->_i_request_category = i_request_category; }

    /// ------------------------------------------------------------------------
    ///	date_from
        const QString& date_from_string( ) const
        { return this->_dt_from; }

        QDate date_from( ) const
        { return QDate::fromString( this->_dt_from, "yyyy-MM-dd" ); }

        void date_from( const QDate &dt_from )
        {
            if( dt_from.isValid( ) )
            {
                this->_dt_from = dt_from.toString("yyyy-MM-dd");
            }
            else
            {
                this->_dt_from.clear( );
            }
        }

    /// ------------------------------------------------------------------------
    ///	date_to
        const QString& date_to_string( ) const
        { return this->_dt_to; }

        QDate date_to( ) const
        { return QDate::fromString( this->_dt_to, "yyyy-MM-dd" ); }

        void date_to( const QDate &dt_to )
        {
            if( dt_to.isValid( ) )
            {
                this->_dt_to = dt_to.toString("yyyy-MM-dd");
            }
            else
            {
                this->_dt_to.clear( );
            }
        }

    /// ------------------------------------------------------------------------
    ///	declarant
        const QString& declarant( ) const
        { return this->_x_declarant; }

        void declarant( const QString &x_declarant )
        { this->_x_declarant = x_declarant; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    public:
        data_request_search_criteria& operator=( const data_request_search_criteria &rhs )
        {
            if( this == &rhs )
            {
                return *this;
            }
            _i_ad = rhs._i_ad;
            _i_mr = rhs._i_mr;
            _i_mediator = rhs._i_mediator;
            _i_request_category = rhs._i_request_category;
            _dt_from = rhs._dt_from;
            _dt_to = rhs._dt_to;
            _x_declarant = rhs._x_declarant;

            return *this;
        }

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        int     _i_declarant_type;      //--id типа заявителя
        int     _i_ad;                  //--id административного округа
        int     _i_mr;                  //--id муниципального района
        int     _i_mediator;            //--id медиатора
        int     _i_request_category;    //--id категории обращения
        QString _dt_from;               //--начало периода обращения
        QString _dt_to;                 //--окончание периода обращения
        QString _x_declarant;           //--заявитель

    };//class data_request_search_criteria
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_request_collection
/// ############################################################################
    class data_request_collection
	{
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	/// ------------------------------------------------------------------------
        data_request_collection( const data_request_collection &rhs );
	public:
	/// ------------------------------------------------------------------------
        data_request_collection( ) :
			_data( 0 )
		{ }
	/// ------------------------------------------------------------------------
        virtual ~data_request_collection( )
		{ this->free( ); }

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
		int size( ) const
		{
			if( !this->_data )
			{
				return 0;
			}
			return this->_data->size( );
		}

	/// ------------------------------------------------------------------------
		void free_data_pointer( )
		{
			if( !this->_data )
			{
				return;
			}
			//free pointer to list
			//but save pointers on list elements
			delete _data;
			this->_data = 0;
		}

	/// ------------------------------------------------------------------------
		void free( )
		{
			if( !this->_data )
			{
				return;
			}
			while( this->_data->size( ) )
			{
				//get last element
                data_request *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

	/// ------------------------------------------------------------------------
        void append( data_request *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_request *>;
			}
			this->_data->append( r );
		}

	/// ------------------------------------------------------------------------
        QList<data_request *>* list( )
		{ return this->_data; }

	/// ========================================================================
	///		OPERATORS
	/// ========================================================================
	private:
        data_request_collection& operator=(
                                        const data_request_collection &rhs
											);
	/// ========================================================================
	//			FIELDS
	/// ========================================================================
	private:
        QList<data_request *>	*_data;

    };//class data_request_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_request
/// ############################################################################
	class data_adapter_request
	{
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		data_adapter_request( const data_adapter_request &rhs );

	public:
	/// ------------------------------------------------------------------------
		explicit data_adapter_request( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
	/// ------------------------------------------------------------------------
		~data_adapter_request( );

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
	/// ------------------------------------------------------------------------
        QString make_filter( const data_request_search_criteria &r_filter ) const;
	/// ------------------------------------------------------------------------
		void cmd_params_insert(
                          espira::db::qt_sqlite_command *pcmd,
                          const data_request &r
                        ) const;
    /// ------------------------------------------------------------------------
        void cmd_params_update(
                          espira::db::qt_sqlite_command *pcmd,
                          const data_request &r
                              ) const;
	/// ------------------------------------------------------------------------
        void execute( const QString &s_sql, const data_request &r ) const;

	public:
	/// ------------------------------------------------------------------------
        int newkey( int i_ad, const QDate &dt ) const;
    /// ------------------------------------------------------------------------
        QVariant select_id_new( int id_from, int id_to ) const;
	/// ------------------------------------------------------------------------
        data_request_collection*
                        select( const data_request &r_filter ) const;
    /// ------------------------------------------------------------------------
        data_request_collection*
                        select( const data_request_search_criteria &r_filter ) const;
	/// ------------------------------------------------------------------------
        void insert( const data_request &request ) const;
	/// ------------------------------------------------------------------------
        void update( const data_request &request ) const;
	/// ------------------------------------------------------------------------
        void update_id( int id_old, int id_new ) const;
	/// ------------------------------------------------------------------------
        void del(const int id_request ) const;

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	private:

	public:

	/// ========================================================================
	///		OPERATORS
    /// ========================================================================
    private:
		data_adapter_request& operator=( const data_adapter_request &rhs );

	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
		static const QString _s_sql_newkey;
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_update_id;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;

	};//class data_adapter_request

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DATA_ADAPTER_REQUEST_H__
