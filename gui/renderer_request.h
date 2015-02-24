/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 16-10-2013
///		Date update	: 01-02-2014
///		Comment		:
/// ============================================================================
#ifndef __RENDERER_REQUEST_H__
#define __RENDERER_REQUEST_H__

#include <QPainter>

namespace mac_mediator
{
    class data_request;

/// ############################################################################
///			class renderer_request
/// ############################################################################
	class renderer_request : public QPainter
	{
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
		renderer_request( const renderer_request &rhs );

	public:
	/// ------------------------------------------------------------------------
		renderer_request( QPaintDevice *device = 0 ) :
			QPainter( device ),
			_x_pixels_in_cm( 0.0 ),
			_y_pixels_in_cm( 0.0 ),
			_shift_cm_left( 0.0 ),
			_shift_cm_top( 0.0 ),
			_y_current( 0 ),
            _request( 0 ),
            _x_fnt_family( "Times New Roman" )
		{ }
	/// ------------------------------------------------------------------------
		~renderer_request( )
		{ }

	/// ========================================================================
	///		FUNCTIONS
	/// ========================================================================
	private:
	/// ------------------------------------------------------------------------
        void draw_frame_rect( );
	/// ------------------------------------------------------------------------
        void draw_text_header_block(
                                    int y_coord,
                                    const QString &text, const QFont &fnt,
                                    int flags
                                   );
	/// ------------------------------------------------------------------------
        void draw_text_param_block(
                                    int y_coord,
                                    const QString &param, const QString &value,
                                    QFont &fnt, int flags
                                  );
	/// ------------------------------------------------------------------------
        void draw_last_text_param_block(
                                        int y_coord,
                                        const QString &param, const QString &value,
                                        QFont &fnt, int flags
                                       );
	/// ------------------------------------------------------------------------
		void draw_block_header( );
	/// ------------------------------------------------------------------------
		void draw_block_executor( );
	/// ------------------------------------------------------------------------
		void draw_block_declarant( );
	/// ------------------------------------------------------------------------
		void draw_block_request( );

	public:
	/// ------------------------------------------------------------------------
		void draw_request( );

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================
	public:
	/// ------------------------------------------------------------------------
		const data_request* request( ) const
		{ return this->_request; }
	/// ------------------------------------------------------------------------
		void request( const data_request *request )
		{ this->_request = request; }
	/// ------------------------------------------------------------------------
		const double& shift_left( ) const
		{ return this->_shift_cm_left; }
	/// ------------------------------------------------------------------------
		void shift_left( const double &s_left )
		{ this->_shift_cm_left = s_left; }
	/// ------------------------------------------------------------------------
		const double& shift_top( ) const
		{ return this->_shift_cm_top; }
	/// ------------------------------------------------------------------------
		void shift_top( const double &s_top )
		{ this->_shift_cm_top = s_top; }
    /// ------------------------------------------------------------------------
    /// font_family
        void font_family( const QString &x_family )
        { this->_x_fnt_family = x_family; }

        const QString& font_family( ) const
        { return this->_x_fnt_family; }

	/// ========================================================================
	///		OPERATORS
    /// ========================================================================
    private:
	/// ------------------------------------------------------------------------
		renderer_request& operator=( const renderer_request &rhs );

	/// ========================================================================
	///		SLOTS
	/// ========================================================================

	/// ========================================================================
	///			FIELDS
	/// ========================================================================
	private:
		double					_x_pixels_in_cm;
		double					_y_pixels_in_cm;
		double					_shift_cm_left;
		double					_shift_cm_top;
        int                     _y_current;

		QRect                   _rc_frame;

		const data_request		*_request;

        QString                 _x_fnt_family;

	};//class renderer_request

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __RENDERER_REQUEST_H__
