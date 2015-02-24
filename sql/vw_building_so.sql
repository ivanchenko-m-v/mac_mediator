CREATE VIEW vw_building_so AS             
SELECT t_building_address.i_code_TIB,  t_building_address.x_building_address, t_service_organization.x_so_title 
	FROM (t_building_address LEFT OUTER JOIN t_building_so ON t_building_address.i_code_TIB=t_building_so.i_code_TIB) 
		LEFT OUTER JOIN  t_service_organization ON t_building_so.i_so=t_service_organization.i_so;