/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 16-10-2013
///		Date update	: 01-02-2014
///		Comment		:
/// ============================================================================
#include "renderer_request.h"
#include "data_adapter_request.h"

namespace mac_mediator
{

/// ############################################################################
///			class renderer_request
/// ############################################################################

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	/// ------------------------------------------------------------------------
	///	draw_frame_rect( )
	/// ------------------------------------------------------------------------
    void renderer_request::draw_frame_rect()
    {
        this->save( );

        this->_x_pixels_in_cm = double( this->device( )->width( ) * 10 ) /
                                double( this->device( )->widthMM( ) );
        this->_y_pixels_in_cm = double( this->device( )->height( ) * 10 ) /
                                double( this->device( )->heightMM( ) );

        int x_shift_left = int( this->_x_pixels_in_cm * this->_shift_cm_left );
        int y_shift_top = int( this->_y_pixels_in_cm * this->_shift_cm_top );
        int width = this->window( ).width( ) - ( x_shift_left*2 );
        int height = this->window( ).height( ) - ( y_shift_top*2 );
        this->_rc_frame = QRect( x_shift_left, y_shift_top, width, height );

        QPen pen( Qt::SolidLine );
        pen.setWidth( 4 );
        this->setPen( pen );
        this->drawRect( this->_rc_frame );

        this->restore( );
    }

	/// ------------------------------------------------------------------------
	///	draw_text_header_block(
    ///                        int y_coord,
    ///                        const QString &text,
    ///                        const QFont &fnt, int flags
    ///                       )
	/// ------------------------------------------------------------------------
    void renderer_request::draw_text_header_block(
                                                    int y_coord,
                                                    const QString &text,
                                                    const QFont &fnt, int flags
                                                 )
    {
        this->save( );

		this->setFont( fnt );

		QFontMetrics fms( fnt );
        QRect rc = fms.boundingRect(
                                QRect(
                                      this->_rc_frame.x( ), this->_rc_frame.y( ),
                                      this->_rc_frame.width( ), 0
                                     ), flags, text );
        QRect rc_draw(
                        this->_rc_frame.x( ), y_coord,
                        this->_rc_frame.width( ), rc.height( )*2
                     );
		this->drawText( rc_draw, flags, text );
		this->drawLine( rc_draw.bottomLeft( ), rc_draw.bottomRight( ) );
        //next block top y
        this->_y_current = y_coord + rc_draw.height( ) + 1;

        //restore
        this->restore( );
    }

	/// ------------------------------------------------------------------------
	/// draw_text_param_block(
    ///                       int y_coord,
    ///                       const QString &param,
    ///                       const QString &value,
    ///                       const QFont &fnt, int flags
    ///                      )
	/// ------------------------------------------------------------------------
    void renderer_request::draw_text_param_block(
                                                    int y_coord,
                                                    const QString &param,
                                                    const QString &value,
                                                    QFont &fnt, int flags
                                                 )
    {
        this->save( );

        fnt.setBold( true );
		QFontMetrics fms_param( fnt );
		int n_width = this->_rc_frame.width( )/2;
        QRect rc_param = fms_param.boundingRect(
                                QRect(
                                      this->_rc_frame.x( ), this->_rc_frame.y( ),
                                      n_width, 0
                                     ), flags, param );
        fnt.setBold( false );
		QFontMetrics fms_value( fnt );
        QRect rc_value = fms_value.boundingRect(
                                QRect(
                                      this->_rc_frame.x( ) + n_width,
                                      this->_rc_frame.y( ),
                                      this->_rc_frame.width( ) - n_width, 0
                                     ), flags, value );
        int n_height =  std::max( rc_param.height( ), rc_value.height( ) ) + 10;
        //param
        QRect rc_draw_param(
                            this->_rc_frame.x( ), y_coord,
                            n_width,
                            n_height
                           );
        fnt.setBold( true );
		this->setFont( fnt );
		this->drawText( rc_draw_param, flags, param );
		this->drawLine( rc_draw_param.topRight( ), rc_draw_param.bottomRight( ) );
        //value
        QRect rc_draw_value(
                        this->_rc_frame.x( ) + n_width, y_coord,
                        this->_rc_frame.width( ) - n_width,
                        n_height
                     );
        fnt.setBold( false );
		this->setFont( fnt );
		this->drawText( rc_draw_value, flags, value );
		this->drawLine( rc_draw_param.bottomLeft( ), rc_draw_value.bottomRight( ) );
        //next block top y
        this->_y_current = y_coord + rc_draw_param.height( ) + 1;

        //restore
        this->restore( );

    }

	/// ------------------------------------------------------------------------
	/// draw_last_text_param_block(
    ///                       int y_coord,
    ///                       const QString &param,
    ///                       const QString &value,
    ///                       const QFont &fnt, int flags
    ///                      )
	/// ------------------------------------------------------------------------
    void renderer_request::draw_last_text_param_block(
                                                        int y_coord,
                                                        const QString &param,
                                                        const QString &value,
                                                        QFont &fnt, int flags
                                                     )
    {
        this->save( );

        fnt.setBold( true );
		QFontMetrics fms_param( fnt );
		int n_width = this->_rc_frame.width( )/2;
        QRect rc_param = fms_param.boundingRect(
                                QRect(
                                      this->_rc_frame.x( ), this->_rc_frame.y( ),
                                      n_width, 0
                                     ), flags, param );
        fnt.setBold( false );
		QFontMetrics fms_value( fnt );
        QRect rc_value = fms_value.boundingRect(
                                QRect(
                                      this->_rc_frame.x( ) + n_width,
                                      this->_rc_frame.y( ),
                                      this->_rc_frame.width( ) - n_width, 0
                                     ), flags, value );
        int n_height =  std::max( rc_param.height( ), rc_value.height( ) );
        n_height =  std::max( n_height, this->_rc_frame.bottom( ) - y_coord );

        //param
        QRect rc_draw_param(
                            this->_rc_frame.x( ), y_coord,
                            n_width,
                            n_height
                           );
        fnt.setBold( true );
		this->setFont( fnt );
		this->drawText( rc_draw_param, flags, param );
		this->drawLine( rc_draw_param.topRight( ), rc_draw_param.bottomRight( ) );
        //value
        QRect rc_draw_value(
                        this->_rc_frame.x( ) + n_width, y_coord,
                        this->_rc_frame.width( ) - n_width,
                        n_height
                     );
        fnt.setBold( false );
		this->setFont( fnt );
		this->drawText( rc_draw_value, flags, value );
        //next block top y
        this->_y_current = y_coord + rc_draw_param.height( ) + 1;

        //restore
        this->restore( );

    }

	/// ------------------------------------------------------------------------
	///	draw_block_header( )
	/// ------------------------------------------------------------------------
    void renderer_request::draw_block_header( )
    {
        QFont fnt_block_header( this->_x_fnt_family, 16, QFont::Bold );
        this->setFont( fnt_block_header );

		QString s_text(
                        QObject::tr( "Request card # " ) +
                        this->_request->id_request_string( )
                      );

        this->draw_text_header_block(
                                     this->_y_current, s_text,
                                     fnt_block_header, Qt::AlignCenter
                                    );
    }

	/// ------------------------------------------------------------------------
	///	draw_block_executor( )
	/// ------------------------------------------------------------------------
    void renderer_request::draw_block_executor( )
    {
        QFont fnt_block( this->_x_fnt_family, 14, QFont::Bold );
        this->setFont( fnt_block );

		QString s_text( QObject::tr( "Executor info" ) );

        this->draw_text_header_block(
                                     this->_y_current, s_text,
                                     fnt_block, Qt::AlignCenter
                                    );
        fnt_block.setBold( false );
        fnt_block.setPointSize( 12 );
        //mediator
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Mediator" ),
                                    this->_request->mediator_name( ),
                                    fnt_block, Qt::AlignCenter
        );
        //mediator phone
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Mediator phone" ),
                                    this->_request->mediator_phone( ),
                                    fnt_block, Qt::AlignCenter
        );
    }

	/// ------------------------------------------------------------------------
	///	draw_block_declarant( )
	/// ------------------------------------------------------------------------
    void renderer_request::draw_block_declarant( )
    {
        QFont fnt_block( this->_x_fnt_family, 14, QFont::Bold );
        this->setFont( fnt_block );

		QString s_text( QObject::tr( "Declarant info" ) );

        this->draw_text_header_block(
                                     this->_y_current, s_text,
                                     fnt_block, Qt::AlignCenter
                                    );
        fnt_block.setBold( false );
        fnt_block.setPointSize( 12 );
        //declarant type
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Declarant type" ),
                                    this->_request->declarant_type( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
        );
        //declarant
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Declarant" ),
                                    this->_request->declarant( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
        );
        //ad_title
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Administrative division" ),
                                    this->_request->ad_title( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
                                   );
        //mr_title
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Municipal district" ),
                                    this->_request->mr_title( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
                                   );
        //declarant_address
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Address" ),
                                    this->_request->declarant_address( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
                                   );
        //declarant_phone
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Declarant phone" ),
                                    this->_request->declarant_phone( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
                                   );
        //service_organization
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Service organization" ),
                                    this->_request->service_organization( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
                                   );
    }

	/// ------------------------------------------------------------------------
	///	draw_block_request( )
	/// ------------------------------------------------------------------------
    void renderer_request::draw_block_request( )
    {
        QFont fnt_block( this->_x_fnt_family, 14, QFont::Bold );
        this->setFont( fnt_block );

		QString s_text( QObject::tr( "Request info" ) );

        this->draw_text_header_block(
                                     this->_y_current, s_text,
                                     fnt_block, Qt::AlignCenter
                                    );
        fnt_block.setBold( false );
        fnt_block.setPointSize( 12 );
        //date
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Date" ),
                                    this->_request->date( ).toString( "dd.MM.yyyy" ),
                                    fnt_block, Qt::AlignCenter
                                   );
        //time
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Time" ),
                                    this->_request->time( ).toString( "hh:mm" ),
                                    fnt_block, Qt::AlignCenter
                                   );
        //request category
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Request category" ),
                                    this->_request->request_category_title( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
                                   );
        //request
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Request contents" ),
                                    this->_request->request( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
                                   );
        //other_conflict_party
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Other conflict party" ),
                                    this->_request->other_conflict_party( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
                                   );
        //responsible organization
        this->draw_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Responsible organization" ),
                                    this->_request->organization( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
                                   );
        //consultation
        this->draw_last_text_param_block(
                                    this->_y_current,
                                    QObject::tr( "Consultation" ),
                                    this->_request->consultation( ),
                                    fnt_block, Qt::AlignCenter|Qt::TextWordWrap
                                        );

    }

	/// ------------------------------------------------------------------------
	///	draw_request( )
	/// ------------------------------------------------------------------------
    void renderer_request::draw_request( )
    {
        if( !this->device( ) )
        {
            return;
        }
        if( !this->_request )
        {
            return;
        }
        this->draw_frame_rect( );

        this->draw_block_header( );

        this->draw_block_executor( );

        this->draw_block_declarant( );

        this->draw_block_request( );
    }

/// ############################################################################

}//namespace envelope_printing
