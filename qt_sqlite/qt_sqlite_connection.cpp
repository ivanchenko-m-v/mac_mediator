//$Header
//=============================================================================
//		Author		: M. Ivanchenko
//		Date create	: 10-06-2013
//		Date update	: 10-06-2013
//		Comment		:
//=============================================================================
#include <sqlite3.h>
#include <stdexcept>

#include <QFile>

#include "qt_sqlite_connection.h"
#include "qt_sqlite_command.h"

namespace espira
{

namespace db
{

//#############################################################################
//			class qt_sqlite_connection
//#############################################################################
//=============================================================================
//			CONSTRUCTORS/DESTRUCTOR
//=============================================================================
/// ----------------------------------------------------------------------------
///		qt_sqlite_connection::open
/// ----------------------------------------------------------------------------
qt_sqlite_connection::~qt_sqlite_connection( )
{
	try
	{
		//очистка контейнера команд
		//очистка контейнера транзакций

		//если забыли закрыть соединение
        this->close( );
	}
	catch( std::runtime_error &ex )
	{
		//записать событие в log-файл
	}
}

//=============================================================================
//			FUNCTIONS
//=============================================================================
/// ----------------------------------------------------------------------------
///		qt_sqlite_connection::check_connection_properties
/// ----------------------------------------------------------------------------
void qt_sqlite_connection::check_connection_properties( )
{
	//проверить установки пути к БД
    if( this->_db_path.isEmpty( ) )
	{
		throw std::runtime_error(
									"Can't open database : "
									"database file name was not set."
								);
	}
	//проверить существование файла БД
    if( !QFile::exists( this->_db_path ) )
	{
		throw std::runtime_error(
									"Can't open database : "
									"database file name is not exists."
								);
	}
}
///----------------------------------------------------------------------------
///		qt_sqlite_connection::open
///----------------------------------------------------------------------------
void qt_sqlite_connection::open( )
{
	//проверить свойства соединения с БД
	this->check_connection_properties( );

    QByteArray ba_db_name( this->_db_path.toUtf8( ) );
	//попытка открыть БД
    int retcode = sqlite3_open( ba_db_name.data( ), &( this->_pdb ) );
	//проверка успешности открытия
	if( retcode != SQLITE_OK )
	{
		std::string msg_err( "Can't open database : " );
		msg_err += sqlite3_errmsg( this->_pdb );
		sqlite3_close( this->_pdb );
        this->_pdb = 0;

		throw std::runtime_error( msg_err );
	}
}

///----------------------------------------------------------------------------
///		qt_sqlite_connection::close
///----------------------------------------------------------------------------
void qt_sqlite_connection::close( )
{
	//проверка указателя на открытую БД
	if( !this->_pdb )
	{
		return;
	}
    //закрыть соединение
    int retcode = sqlite3_close( this->_pdb );
    //проверить успешность закрытия
    if( retcode != SQLITE_OK )
    {
        throw std::runtime_error(
                                std::string( "Can't close database : " ) +
                                sqlite3_errmsg( this->_pdb )
                                );
    }

    this->_pdb = 0;
}

///----------------------------------------------------------------------------
///		qt_sqlite_connection::create_command
///----------------------------------------------------------------------------
qt_sqlite_command*
        qt_sqlite_connection::create_command( const QString &s_cmd_text )
{
	//проверка существования указателя БД sqlite3 API
	//соединение должно быть открыто!
	if( !this->_pdb )
	{
		throw std::runtime_error(
									"Can't create command : "
									"database connection wasn't opened."
								);
	}
	//создать в динамической памяти объект sqlite_command
    qt_sqlite_command *p_cmd = new qt_sqlite_command( );
	//инициализация объекта sqlite_command
    p_cmd->command_text( s_cmd_text );
	//необходимо для last_error_msg( )
	p_cmd->_conn = this;
	//необходимо для реализации db_command::open( )
	p_cmd->_pdb = this->_pdb;

	return p_cmd;
}

///----------------------------------------------------------------------------
///		qt_sqlite_connection::last_error_msg( )
///----------------------------------------------------------------------------
QString qt_sqlite_connection::last_error_msg( ) const
{
    if( !this->_pdb )
	{
        return QString( "" );
	}

    return QString( sqlite3_errmsg( this->_pdb ) );
}

//#############################################################################

}//namespace db

}//namespace espira
