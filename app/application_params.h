/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-10-2013
///		Date update	: 11-10-2013
///		Comment		:
/// ============================================================================
#ifndef __APPLICATION_PARAMS_H__
#define __APPLICATION_PARAMS_H__

#include <QObject>
#include <QHash>

namespace espira
{

namespace utils
{
    typedef QHash<QString, QString> ss_hash;
/// ############################################################################
///			class application_params
/// ############################################################################
    class application_params : public QObject
    {
    Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        application_params( const application_params &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit application_params(
                                const QString &f_path=QString( ),
                                QObject *parent=0
                                ) :
                                QObject( parent ),
                                _f_path( f_path )
        { }
        /// --------------------------------------------------------------------
        virtual ~application_params( )
        { }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
        /// --------------------------------------------------------------------
        /// cfg_file_path
        const QString& cfg_file_path( ) const
        { return this->_f_path; }

        void cfg_file_path( const QString &f_path )
        { this->_f_path = f_path; }

        /// --------------------------------------------------------------------
        /// parameter
        QString parameter( const QString &param ) const
        {
            if( this->_hash_params.contains( param ) )
            {
                return this->_hash_params[param];
            }
            return QString( );
        }

        void parameter( const QString &param, const QString &value )
        {
            this->_hash_params[param] = value;
        }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------

    public:
        /// --------------------------------------------------------------------
        void parse_cfg_file( const QString &f_path=QString( ) );
        /// --------------------------------------------------------------------
        void save_cfg_file( const QString &f_path=QString( ) );

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        application_params& operator=( const application_params &rhs );

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    public slots:
        /// --------------------------------------------------------------------

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        QString _f_path;

        ss_hash  _hash_params;

	};//class ini_file_parser
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace utils

}//namespace espira
#endif // __APPLICATION_PARAMS_H__
