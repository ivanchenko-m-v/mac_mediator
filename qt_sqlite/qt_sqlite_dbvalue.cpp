/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-06-2013
///		Date update	: 27-06-2013
///		Comment		:
/// ============================================================================

#include "qt_sqlite_dbvalue.h"

namespace espira
{

namespace db
{
/// ############################################################################
///			class qt_sqlite_dbvalue_creator
/// ############################################################################
///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_creator::create
///----------------------------------------------------------------------------
QVariant* qt_sqlite_dbvalue_creator::parse_query_column_value(
                                                         sqlite3_stmt *p_stmt,
                                                         int n_column
                                                       )
{
    QVariant *p_val = 0;
    int n_type = sqlite3_column_type( p_stmt, n_column );
    switch( n_type )
    {
    case SQLITE_INTEGER:
        p_val = new QVariant( sqlite3_column_int64( p_stmt, n_column ) );
        break;
    case SQLITE_FLOAT:
        p_val = new QVariant( sqlite3_column_double( p_stmt, n_column ) );
        break;
    case SQLITE_TEXT:
        p_val = qt_sqlite_dbvalue_creator::parse_query_value_text( p_stmt, n_column );
        break;
    case SQLITE_BLOB:
        p_val = qt_sqlite_dbvalue_creator::parse_query_value_blob( p_stmt, n_column );
        break;
    default:
        break;
    }

    return p_val ? p_val : new QVariant;
}

///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_creator::parse_query_value_text
///----------------------------------------------------------------------------
QVariant* qt_sqlite_dbvalue_creator::parse_query_value_text(
                                                         sqlite3_stmt *p_stmt,
                                                         int n_column
                                                           )
{
    int num_bytes = sqlite3_column_bytes( p_stmt, n_column );
    if( !num_bytes )
    {
        return 0;
    }
    const char *text_bytes =
            reinterpret_cast<const char *>( sqlite3_column_text( p_stmt, n_column ) );

    return new QVariant( QString::fromUtf8( text_bytes, num_bytes ) );
}

///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_creator::parse_query_value_text
///----------------------------------------------------------------------------
QVariant* qt_sqlite_dbvalue_creator::parse_query_value_text(
                                                             sqlite3_value *val
                                                           )
{
    int num_bytes = sqlite3_value_bytes( val );
    if( !num_bytes )
    {
        return 0;
    }
    const char *text_bytes =
            reinterpret_cast<const char *>( sqlite3_value_text( val ) );

    return new QVariant( QString::fromUtf8( text_bytes, num_bytes ) );
}

///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_creator::parse_query_value_blob
///----------------------------------------------------------------------------
QVariant* qt_sqlite_dbvalue_creator::parse_query_value_blob(
                                                        sqlite3_stmt *p_stmt,
                                                        int n_column
                                                            )
{
    int num_bytes = sqlite3_column_bytes( p_stmt, n_column );
    if( !num_bytes )
    {
        return 0;
    }
    const char *text_bytes =
            reinterpret_cast<const char *>( sqlite3_column_blob( p_stmt, n_column ) );

    return new QVariant( QByteArray::fromRawData( text_bytes, num_bytes ) );
}

///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_creator::parse_query_value_blob
///----------------------------------------------------------------------------
QVariant* qt_sqlite_dbvalue_creator::parse_query_value_blob(
                                                            sqlite3_value *val
                                                           )
{
    int num_bytes = sqlite3_value_bytes( val );
    if( !num_bytes )
    {
        return 0;
    }
    const char *text_bytes =
            reinterpret_cast<const char *>( sqlite3_value_blob( val ) );


    return new QVariant( QByteArray::fromRawData( text_bytes, num_bytes ) );
}

///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_creator::create
///----------------------------------------------------------------------------
qt_sqlite_dbvalue* qt_sqlite_dbvalue_creator::create( sqlite3_value *val )
{
    qt_sqlite_dbvalue *p_dbval = 0;
    QVariant *pvv = 0;
    int n_type = sqlite3_value_type( val );
    switch( n_type )
    {
    case SQLITE_INTEGER:
        p_dbval = new qt_sqlite_dbvalue_int64( QVariant( sqlite3_value_int64( val ) ) );
        break;
    case SQLITE_FLOAT:
        p_dbval = new qt_sqlite_dbvalue_double( QVariant( sqlite3_value_double( val ) ) );
        break;
    case SQLITE_TEXT:
        pvv = qt_sqlite_dbvalue_creator::parse_query_value_text( val );
        if(pvv)
        {
            p_dbval = new qt_sqlite_dbvalue_text( *pvv );
        }
        else
        {
            p_dbval = new qt_sqlite_dbvalue_text( QVariant::String );
        }
        delete pvv;
        break;
    case SQLITE_BLOB:
        pvv = qt_sqlite_dbvalue_creator::parse_query_value_blob( val );
        if(pvv)
        {
            p_dbval = new qt_sqlite_dbvalue_blob( *pvv );
        }
        else
        {
            p_dbval = new qt_sqlite_dbvalue_blob( QVariant::ByteArray );
        }
        delete pvv;
        break;
    default:
        break;
    }

    return p_dbval;
}

///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_creator::create_variant
///----------------------------------------------------------------------------
QVariant* qt_sqlite_dbvalue_creator::create_variant( sqlite3_value *val )
{
    QVariant *p_varval = 0;
    int n_type = sqlite3_value_type( val );
    switch( n_type )
    {
    case SQLITE_INTEGER:
        p_varval = new QVariant( sqlite3_value_int64( val ) );
        break;
    case SQLITE_FLOAT:
        p_varval = new QVariant( sqlite3_value_double( val ) );
        break;
    case SQLITE_TEXT:
        p_varval = qt_sqlite_dbvalue_creator::parse_query_value_text( val );
        break;
    case SQLITE_BLOB:
        p_varval = qt_sqlite_dbvalue_creator::parse_query_value_blob( val );
        break;
    default:
        break;
    }

    return p_varval ? p_varval : new QVariant( );
}

/// ############################################################################
///			class qt_sqlite_dbvalue_null
/// ############################################################################
/// ============================================================================
///		FUNCTIONS
/// ============================================================================
///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_null::bind_query_parameter
///----------------------------------------------------------------------------
int qt_sqlite_dbvalue_null::bind_query_parameter(
                                                    sqlite3_stmt *p_stmt,
                                                    int n_param
                                                 )
{
    return sqlite3_bind_null( p_stmt, n_param );
}

/// ############################################################################
///			class qt_sqlite_dbvalue_int
/// ############################################################################
/// ============================================================================
///		FUNCTIONS
/// ============================================================================
///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_int::bind_query_parameter
///----------------------------------------------------------------------------
int qt_sqlite_dbvalue_int::bind_query_parameter(
                                                    sqlite3_stmt *p_stmt,
                                                    int n_param
                                                )
{
    return sqlite3_bind_int( p_stmt, n_param, this->value( ).toInt( ) );
}

/// ############################################################################
///			class qt_sqlite_dbvalue_int64
/// ############################################################################
/// ============================================================================
///		FUNCTIONS
/// ============================================================================
///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_int64::bind_query_parameter
///----------------------------------------------------------------------------
int qt_sqlite_dbvalue_int64::bind_query_parameter(
                                                    sqlite3_stmt *p_stmt,
                                                    int n_param
                                                  )
{
    return sqlite3_bind_int64( p_stmt, n_param, this->value( ).toLongLong( ) );
}

/// ############################################################################
///			class qt_sqlite_dbvalue_double
/// ############################################################################
/// ============================================================================
///		FUNCTIONS
/// ============================================================================
///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_double::bind_query_parameter
///----------------------------------------------------------------------------
int qt_sqlite_dbvalue_double::bind_query_parameter(
                                                    sqlite3_stmt *p_stmt,
                                                    int n_param
                                                   )
{
    return sqlite3_bind_double( p_stmt, n_param, this->value( ).toDouble( ) );
}

/// ############################################################################
///			class qt_sqlite_dbvalue_text
/// ############################################################################
/// ============================================================================
///		FUNCTIONS
/// ============================================================================
///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_text::bind_query_parameter
///----------------------------------------------------------------------------
int qt_sqlite_dbvalue_text::bind_query_parameter(
                                                    sqlite3_stmt *p_stmt,
                                                    int n_param
                                                 )
{
    //очищаем, если присоединяли значение ранее
    this->free( );
    //выделяем память
    this->_param_buf = new QByteArray( this->value( ).toString( ).toUtf8( ) );
    //присоединяем значение
    return sqlite3_bind_text(
                              p_stmt, n_param,
                              this->_param_buf->data( ),
                              this->_param_buf->size( ), SQLITE_STATIC
                            );
}

/// ############################################################################
///			class qt_sqlite_dbvalue_blob
/// ############################################################################
/// ============================================================================
///		FUNCTIONS
/// ============================================================================
///----------------------------------------------------------------------------
///		qt_sqlite_dbvalue_blob::bind_query_parameter
///----------------------------------------------------------------------------
int qt_sqlite_dbvalue_blob::bind_query_parameter(
                                                    sqlite3_stmt *p_stmt,
                                                    int n_param
                                                 )
{
    //очищаем, если присоединяли значение ранее
    this->free( );
    //выделяем память
    this->_param_buf = new QByteArray( this->value( ).toByteArray( ) );
    //присоединяем значение
    return sqlite3_bind_blob(
                              p_stmt, n_param,
                              this->_param_buf->data( ),
                              this->_param_buf->size( ), SQLITE_STATIC
                            );
}

}//namespace db

}//namespace espira
