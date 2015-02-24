SELECT t_request.i_request, t_request.i_declarant_type, t_request.i_mr, t_request.i_mediator, t_request.i_request_category, 
       t_request.dt_request, t_request.tm_request, t_request.x_declarant, t_request.x_declarant_phone,
       t_request.x_declarant_address, t_request.x_service_organization, t_request.x_request, 
       t_request.x_other_conflict_party, t_request.x_organization, t_request.x_consultation,
       t_administrative_division.i_administrative_division, t_administrative_division.x_administrative_division, t_municipal_district.x_municipal_district,
       t_mediator.x_mediator, t_mediator.x_mediator_phone, t_request_category.x_request_category, t_declarant_type.x_declarant_type
       FROM t_request, t_administrative_division, t_municipal_district, t_mediator, t_request_category, t_declarant_type
       WHERE (
              (t_request.i_mr=t_municipal_district.i_municipal_district)AND
              (t_municipal_district.i_administrative_division=t_administrative_division.i_administrative_division)AND
              (t_request.i_mediator=t_mediator.i_mediator)AND
              (t_request.i_request_category=t_request_category.i_request_category)AND
              (t_request.i_declarant_type=t_declarant_type.i_declarant_type)
             );
             
CREATE VIEW vw_request AS             
SELECT t_request.i_request, t_request.i_declarant_type, t_request.i_mr, t_request.i_mediator, t_request.i_request_category, 
       t_request.dt_request, t_request.tm_request, t_request.x_declarant, t_request.x_declarant_phone,
       t_request.x_declarant_address, t_request.x_service_organization, t_request.x_request, 
       t_request.x_other_conflict_party, t_request.x_organization, t_request.x_consultation,
       t_administrative_division.i_administrative_division, t_administrative_division.x_administrative_division, t_municipal_district.x_municipal_district,
       t_mediator.x_mediator, t_mediator.x_mediator_phone, t_request_category.x_request_category, t_declarant_type.x_declarant_type
       FROM t_request, t_administrative_division, t_municipal_district, t_mediator, t_request_category, t_declarant_type
       WHERE (
              (t_request.i_mr=t_municipal_district.i_municipal_district)AND
              (t_municipal_district.i_administrative_division=t_administrative_division.i_administrative_division)AND
              (t_request.i_mediator=t_mediator.i_mediator)AND
              (t_request.i_request_category=t_request_category.i_request_category)AND
              (t_request.i_declarant_type=t_declarant_type.i_declarant_type)
             );

SELECT i_request, i_declarant_type, i_mr, i_mediator, i_request_category, 
       dt_request, tm_request, x_declarant, x_declarant_phone,
       x_declarant_address, x_service_organization, x_request, 
       x_other_conflict_party, x_organization, x_consultation,
       i_administrative_division, 
       x_administrative_division, x_municipal_district,
       x_mediator, x_mediator_phone, x_request_category, x_declarant_type
       FROM vw_request;