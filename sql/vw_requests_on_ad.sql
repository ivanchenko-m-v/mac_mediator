CREATE VIEW vw_requests_on_ad  AS
SELECT t_request.i_request, t_municipal_district.i_administrative_division, t_request.i_declarant_type, t_request.i_request_category, dt_request  
	FROM t_municipal_district, t_request 
	WHERE (t_request.i_mr=t_municipal_district.i_municipal_district);
	
SELECT i_administrative_division, i_request_category, i_declarant_type, count(i_request) as num_requests
FROM (SELECT * FROM vw_requests_on_ad WHERE (dt_request>='2014-01-01')AND(dt_request<='2014-01-31'))
GROUP BY i_administrative_division, i_request_category, i_declarant_type
ORDER BY i_administrative_division, i_request_category, i_declarant_type;
