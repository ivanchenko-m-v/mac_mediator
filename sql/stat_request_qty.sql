SELECT i_ad, x_ad, sum(cnt_request) as qty FROM
(SELECT t_municipal_district.i_administrative_division AS i_ad, t_administrative_division.x_abbr AS x_ad, count(t_request.i_request) AS cnt_request FROM t_municipal_district,t_administrative_division, t_REQUEST WHERE ((t_REQUEST.i_mr=t_municipal_district.i_municipal_district)AND(t_municipal_district.i_administrative_division=t_administrative_division.i_administrative_division)AND(t_request.dt_request>='2013-01-01')AND(t_request.dt_request<='2013-12-31') )
GROUP BY t_municipal_district.i_administrative_division, t_administrative_division.x_abbr, t_REQUEST.i_mr, t_municipal_district.i_municipal_district, t_municipal_district.i_administrative_division, t_administrative_division.i_administrative_division,t_request.dt_request)
GROUP BY i_ad, x_ad;