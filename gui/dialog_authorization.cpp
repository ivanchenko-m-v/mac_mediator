/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 12-12-2013
///		Date update	: 18-12-2013
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QCryptographicHash>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

#include "dialog_authorization.h"

namespace espira
{

namespace widgets
{
/// ############################################################################
///			class dialog_authorization
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	dialog_authorization( )
    /// ------------------------------------------------------------------------
    dialog_authorization::dialog_authorization( QWidget *parent, Qt::WindowFlags f ) :
        QDialog( parent, f )
	{
        this->initialize( );
	}

    /// ------------------------------------------------------------------------
    ///	~dialog_authorization( )
    /// ------------------------------------------------------------------------
    dialog_authorization::~dialog_authorization( )
	{
        qDebug() << "dialog_authorization destroyed";
    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// --------------------------------------------------------------------
    /// hash( )
    /// ------------------------------------------------------------------------
    QString dialog_authorization::hash( ) const
    {
        QString s_pwd( this->_txt_pwd->text( ) );
        return QString(
                        QCryptographicHash::hash( s_pwd.toUtf8( ),
                                                  QCryptographicHash::Md5 ).toHex( )
                      );
    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void dialog_authorization::initialize( )
    {
        this->setWindowTitle( tr( "Authorization" ) );

        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
	///	init_layout( )
    /// ------------------------------------------------------------------------
    void dialog_authorization::init_layout( )
    {
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 5 );
        vl->setSpacing( 10 );

        vl->addWidget( this->init_login( ) );
        vl->addWidget( this->init_pwd( ) );
        vl->addWidget( this->init_buttons( ) );

        this->setLayout(vl);
    }

    /// ------------------------------------------------------------------------
    ///	init_connections( )
    /// ------------------------------------------------------------------------
    void dialog_authorization::init_connections( )
    {
        //accept
        this->connect(
                        this->_btn_ok, SIGNAL( clicked( ) ),
                        this, SLOT( accept( ) )
                     );
        //reject
        this->connect(
                        this->_btn_cancel, SIGNAL( clicked( ) ),
                        this, SLOT( reject( ) )
                    );
    }

    /// ------------------------------------------------------------------------
    ///	init_login( )
    /// ------------------------------------------------------------------------
    QWidget *dialog_authorization::init_login( )
    {
        QWidget *widget = new QWidget( this );

        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( tr( "login:" ) );
        lbl->setAlignment( Qt::AlignLeft|Qt::AlignVCenter );
        vl->addWidget( lbl );

        this->_txt_login = new QLineEdit;
        this->_txt_login->setMaxLength( 16 );
        vl->addWidget( this->_txt_login );

        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    ///	init_pwd( )
    /// ------------------------------------------------------------------------
    QWidget *dialog_authorization::init_pwd( )
    {
        QWidget *widget = new QWidget( this );

        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 0 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( tr( "pwd:" ) );
        lbl->setAlignment( Qt::AlignLeft|Qt::AlignVCenter );
        vl->addWidget( lbl );

        this->_txt_pwd = new QLineEdit;
        this->_txt_pwd->setMaxLength( 16 );
        this->_txt_pwd->setEchoMode( QLineEdit::Password );
        vl->addWidget( this->_txt_pwd );
        widget->setLayout(vl);

        return widget;
    }

    /// ------------------------------------------------------------------------
	///	init_buttons( )
    /// ------------------------------------------------------------------------
    QWidget *dialog_authorization::init_buttons( )
    {
        QWidget *widget = new QWidget( this );
        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 0 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );

        this->_btn_ok = new QPushButton( tr("OK") );
        hl->addWidget( this->_btn_ok );

        this->_btn_cancel = new QPushButton( tr("Cancel") );
        hl->addWidget( this->_btn_cancel );

        widget->setLayout(hl);

        return widget;
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================

/// ############################################################################

}//namespace widgets

}//namespace espira
