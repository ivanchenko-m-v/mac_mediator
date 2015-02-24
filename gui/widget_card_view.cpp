/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-09-2013
///		Date update	: 01-02-2014
///		Comment		:
/// ============================================================================
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>

#include "widget_card_view.h"

namespace mac_mediator
{
/// ############################################################################
///			class widget_card_view
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	widget_card_view( )
    /// ------------------------------------------------------------------------
    widget_card_view::widget_card_view(QWidget *parent) :
        QWidget(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~widget_card_view( )
    /// ------------------------------------------------------------------------
    widget_card_view::~widget_card_view( )
    {

    }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// request( const data_request &r )
    /// ------------------------------------------------------------------------
    void widget_card_view::request( const data_request &r )
    {
        this->_request = r;
    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_card_view::initialize( )
    {
        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin(0);
        vl->setSpacing(0);

        QString s( tr("widget_card_view") );
        this->_txt_html_request = new QTextBrowser;
        this->_txt_html_request->setText( s );
        vl->addWidget( this->_txt_html_request );

        this->setLayout( vl );
    }
    /// ------------------------------------------------------------------------
    /// update_view( )
    /// ------------------------------------------------------------------------
    void widget_card_view::update_view( )
    {
        QString text = html_mediator_info( );
        text+="<hr>";
        text += "<table><tr><td>"+html_declarant_info( )+"</td><td>&nbsp;</td>";
        text += "<td>"+html_request_info( )+"</td></tr></table>";
        text+="<hr>";

        this->_txt_html_request->setText( text );
    }

    /// ------------------------------------------------------------------------
    /// html_mediator_info( )
    /// ------------------------------------------------------------------------
    QString widget_card_view::html_mediator_info( )
    {
        QString text( "<h1>" + this->_request.id_request_string( ) +"</h1>" );

        text+="<div><h2>" + tr("Executor info") +"</h2>";
        text+="<table><tr><td><strong>" + tr("FIO:") +"</strong></td>";
        text+="<td>" + this->_request.mediator_name( ) + "</td></tr>";
        text+="<tr><td><strong>" + tr("Phone:") +"</strong></td>";
        text+="<td>" + this->_request.mediator_phone( ) + "</td></tr>";
        text+="</table></div>";

        return text;
    }

    /// ------------------------------------------------------------------------
    /// html_declarant_info( )
    /// ------------------------------------------------------------------------
    QString widget_card_view::html_declarant_info( )
    {
        QString text( "<div><h2>" + tr("Declarant info") +"</h2>" );

        text+="<table><tr><td><strong>" + tr("Decl. Type:") +"</strong></td>";
        text+="<td>" + this->_request.declarant_type( ) + "</td></tr>";
        text+="<tr><td><strong>" + tr("FIO:") +"</strong></td>";
        text+="<td>" + this->_request.declarant( ) + "</td></tr>";
        text+="<tr><td><strong>" + tr("Adm. Division:") +"<strong></td>";
        text+="<td>" + this->_request.ad_title( ) + "</td></tr>";
        text+="<tr><td><strong>" + tr("Mun. District:") +"</strong></td>";
        text+="<td>" + this->_request.mr_title( ) + "</td></tr>";
        text+="<tr><td><strong>" + tr("Address:") +"</strong></td>";
        text+="<td>" + this->_request.declarant_address( ) + "</td></tr>";
        text+="<tr><td><strong>" + tr("Phone:") +"</strong></td>";
        text+="<td>" + this->_request.declarant_phone( ) + "</td></tr>";
        text+="<tr><td><strong>" + tr("Service org:") +"</strong></td>";
        text+="<td>" + this->_request.service_organization( ) + "</td></tr>";
        text+="</table></div>";

        return text;
    }

    /// ------------------------------------------------------------------------
    /// html_request_info( )
    /// ------------------------------------------------------------------------
    QString widget_card_view::html_request_info( )
    {
        QString text( "<div><h2>" + tr("Request info") +"</h2>" );

        text+="<table><tr><td><strong>" + tr("Request category:") +"</strong></td>";
        text+="<td>" + this->_request.request_category_title( ) + "</td></tr>";
        text+="<tr><td><strong>" + tr("Request:") +"</strong></td>";
        text+="<td><p>" + this->_request.request( ) + "</p></td></tr>";
        text+="<tr><td><strong>" + tr("Other conflict party:") +"</strong></td>";
        text+="<td>" + this->_request.other_conflict_party( ) + "</td></tr>";
        text+="<tr><td><strong>" + tr("Responsible org:") +"</strong></td>";
        text+="<td>" + this->_request.organization( ) + "</td></tr>";
        text+="<tr><td><strong>" + tr("Consultation:") +"</strong></td>";
        text+="<td><p>" + this->_request.consultation( ) + "</p></td></tr>";
        text+="</table></div>";

        return text;
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// change_view( const data_request &r )
    /// ------------------------------------------------------------------------
    void widget_card_view::change_view( const data_request *r )
    {
        this->request( *r );
        this->update_view( );
    }
}//namespace mac_mediator
