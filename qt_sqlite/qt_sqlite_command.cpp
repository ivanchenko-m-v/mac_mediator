//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 10-06-2013
//		Date update	: 25-06-2013
//		Comment		:
//=============================================================================

#include <stdexcept>
#include <sqlite3.h>

#include "qt_sqlite_connection.h"
#include "qt_sqlite_command.h"

namespace espira
{

namespace db
{

//#############################################################################
//			class qt_sqlite_command
//#############################################################################
//=============================================================================
//		CONSTRUCTORS/DESTRUCTOR
//=============================================================================
///----------------------------------------------------------------------------
///		qt_sqlite_command::~qt_sqlite_command( )
///----------------------------------------------------------------------------
qt_sqlite_command::~qt_sqlite_command( )
{
	try
	{
		//если забыли закрыть команду
        qt_sqlite_command::close( );
	}
	catch( std::runtime_error &ex )
	{
		//записать событие в log-файл
		//в случае сбоя закрытия
	}
}

//=============================================================================
//		FUNCTIONS
//=============================================================================
///----------------------------------------------------------------------------
///		qt_sqlite_command::open( )
///----------------------------------------------------------------------------
void qt_sqlite_command::open( )
{
    if( this->_cmd_text.isEmpty( ) )
    {
        throw std::runtime_error( "Prepared command hasn't command text." );
    }
	if( this->_p_stmt )
	{
		throw std::runtime_error( "Prepared command was already opened." );
	}
    QByteArray ba_cmd_text( this->_cmd_text.toUtf8( ) );
	//получить указатель на объект запроса sqlite3 API
	sqlite3_stmt *p_stmt = 0;
	int retcode = sqlite3_prepare_v2(
										this->_pdb,
                                        ba_cmd_text.data( ),
                                        ba_cmd_text.size( ),
										&p_stmt,
										0
									);
	if( retcode != SQLITE_OK || !p_stmt )
	{
        this->command_error(
                            std::string( "SQL error preparing query : " )
                           );
	}
	//команда готова к присоединению параметров
	//или к исполнению при их отсутствии
	this->_p_stmt = p_stmt;
}

///----------------------------------------------------------------------------
///		qt_sqlite_command::reset( )
///----------------------------------------------------------------------------
void qt_sqlite_command::reset( )
{
    if( !this->_p_stmt )
    {
        std::string s_msg( "qt_sqlite_command::reset( ) : " );
        s_msg += std::string("trying to reset not opened query" );
        this->command_error( s_msg );
    }
    int rc = sqlite3_reset( this->_p_stmt );
    if( rc != SQLITE_OK )
    {
        std::string s_msg( "qt_sqlite_command::reset( ) : " );
        s_msg += std::string("sqlite3_reset not successful\n" );
        this->command_error( s_msg );
    }
    rc = sqlite3_clear_bindings( this->_p_stmt );
    if( rc != SQLITE_OK )
    {
        std::string s_msg( "qt_sqlite_command::reset( ) : " );
        s_msg += std::string("sqlite3_clear_bindings not successful\n" );
        this->command_error( s_msg );
    }
    this->_params.free( );
}

///----------------------------------------------------------------------------
///		qt_sqlite_command::bind_parameters( )
///----------------------------------------------------------------------------
void qt_sqlite_command::bind_parameters( )
{
    qt_data_parameter_collection::iterator iter = this->_params.begin( );
    int num_param = 0;
    for( ; iter < this->_params.end( ); ++iter )
    {
        //sqlite params counting starting from 1
        int rc = (*iter)->bind_query_parameter( this->_p_stmt, ++num_param );
        if( rc != SQLITE_OK )
        {
            std::string s_msg( "SQL error binding query parameter #" );
            s_msg += QString::number( num_param ).toStdString( );
            s_msg += std::string( " to query:\n" );
            s_msg += this->_cmd_text.toStdString( );
            this->command_error( s_msg );
        }
    }
}

///----------------------------------------------------------------------------
///		qt_sqlite_command::execute( )
///----------------------------------------------------------------------------
void qt_sqlite_command::execute( )
{
    if( !this->_p_stmt )
    {
        this->command_error( std::string( "Trying to execute command without opening" ) );
    }
    //присоединяем параметры
    this->bind_parameters( );
    //выполняем запрос
    int rc = sqlite3_step( this->_p_stmt );
    if( rc == SQLITE_ERROR )
    {
        this->command_error( std::string( this->_cmd_text.toStdString( ) ) );
    }
    //если выборка
    if( rc == SQLITE_ROW )
    {
        //заполнить результат
        this->fill_query_result( );
    }
}

///----------------------------------------------------------------------------
///		qt_sqlite_command::execute_2( )
/// NOTE: difference between execute and execute_2 is a method of parsing column
/// values by 'fill_query_result' and 'fill_query_result_2'
///----------------------------------------------------------------------------
void qt_sqlite_command::execute_2( )
{
    if( !this->_p_stmt )
    {
        this->command_error( std::string( "Trying to execute command without opening" ) );
    }
    //присоединяем параметры
    this->bind_parameters( );
    //выполняем запрос
    int rc = sqlite3_step( this->_p_stmt );
    if( rc == SQLITE_ERROR )
    {
        this->command_error( std::string( this->_cmd_text.toStdString( ) ) );
    }
    //если выборка
    if( rc == SQLITE_ROW )
    {
        //заполнить результат
        this->fill_query_result_2( );
    }
}

///----------------------------------------------------------------------------
///		qt_sqlite_command::fill_query_result( )
///----------------------------------------------------------------------------
void qt_sqlite_command::fill_query_result( )
{
    //clear previously executed result
    this->_last_result.free( );

    int rc = SQLITE_ROW;
    //получить количество столбцов
    int n_columns = sqlite3_column_count( this->_p_stmt );
    while( rc == SQLITE_ROW )
    {
        qt_data_row *row = new qt_data_row;
        //заполнить запись
        for( int i = 0; i < n_columns; ++i )
        {
            //получить значение поля
            QVariant *column_val =
                    qt_sqlite_dbvalue_creator::parse_query_column_value( this->_p_stmt, i );
            row->append( *column_val );
        }
        //добавить запись к результату запроса
        this->_last_result.append( row );
        //перейти к следующей записи
        rc = sqlite3_step( this->_p_stmt );
    }
    if( rc == SQLITE_ERROR )
    {
        this->command_error(
                            std::string( this->_cmd_text.toStdString( ) ) +
                            std::string( "\nfill query result error" )
                           );
    }
}

///----------------------------------------------------------------------------
///		qt_sqlite_command::fill_query_result_2( )
///----------------------------------------------------------------------------
void qt_sqlite_command::fill_query_result_2( )
{
    //clear previously executed result
    this->_last_result.free( );

    int rc = SQLITE_ROW;
    //получить количество столбцов
    int n_columns = sqlite3_column_count( this->_p_stmt );
    while( rc == SQLITE_ROW )
    {
        qt_data_row *row = new qt_data_row;
        //заполнить запись
        for( int i = 0; i < n_columns; ++i )
        {
            //получить значение поля
            sqlite3_value *pval = sqlite3_column_value( this->_p_stmt, i );
            //преобразовать в QVariant
            QVariant *column_val =
                    qt_sqlite_dbvalue_creator::create_variant( pval );
            row->append( *column_val );
        }
        //добавить запись к результату запроса
        this->_last_result.append( row );
        //перейти к следующей записи
        rc = sqlite3_step( this->_p_stmt );
    }
    if( rc == SQLITE_ERROR )
    {
        this->command_error(
                            std::string( this->_cmd_text.toStdString( ) ) +
                            std::string( "\nfill query result error" )
                           );
    }
}

///----------------------------------------------------------------------------
///		qt_sqlite_command::execute_scalar( )
///----------------------------------------------------------------------------
const QVariant& qt_sqlite_command::execute_scalar( )
{
    this->_last_scalar = QVariant( QVariant::Invalid );
    //выполняем запрос
    this->execute( );
    //извлекаем результат
    if( this->_last_result.size( ) )
    {
        this->_last_scalar = this->_last_result[0]->operator []( 0 );
    }
    return this->_last_scalar;
}

///----------------------------------------------------------------------------
///		qt_sqlite_command::close( )
///----------------------------------------------------------------------------
void qt_sqlite_command::close( )
{
	//финализировать объект sqlite3 API, если этого не было сделано
	if( !this->_p_stmt )
	{
		return;
	}
    int retcode = sqlite3_finalize( this->_p_stmt );
    this->_p_stmt = 0;

    if( retcode != SQLITE_OK )
	{
        this->command_error(
                    std::string( "Can't finalize sqlite3 prepared command : " )
                           );
    }
}

///----------------------------------------------------------------------------
///		qt_sqlite_command::command_error( )
///----------------------------------------------------------------------------
void qt_sqlite_command::command_error( const std::string &err )
{
    std::string s_msg = err;
    if( this->_conn )
    {
        s_msg += this->_conn->last_error_msg( ).toStdString( );
        if( this->_p_stmt )
        {
            sqlite3_finalize( this->_p_stmt );
            this->_p_stmt = 0;
        }
    }
    throw std::runtime_error( s_msg );
}

//#############################################################################

}//namespace db

}//namespace espira
