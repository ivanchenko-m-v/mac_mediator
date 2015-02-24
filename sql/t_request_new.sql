BEGIN TRANSACTION;
--backup table for current request's data
CREATE TABLE t_request_backup
(
	i_request INTEGER NOT NULL,				--id обращения
	i_mr INTEGER NOT NULL,					--id муниципального района
	i_mediator INTEGER NOT NULL,			--id медиатора
	i_request_category INTEGER,				--id категории обращения
	dt_request DATE NOT NULL,				--дата обращения
	tm_request TIME NOT NULL,				--время обращения
	x_declarant VARCHAR(128) NOT NULL,		--заявитель
	x_declarant_phone VARCHAR(48),			--телефон заявителя
	x_declarant_address VARCHAR(256),		--адрес заявителя
	x_service_organization VARCHAR(128),	--управляющая компания
	x_request VARCHAR(1024) NOT NULL,		--суть обращения
	x_other_conflict_party VARCHAR(256),	--вторая сторона конфликта
	x_organization VARCHAR(128),			--ответственная организация
	x_consultation VARCHAR(1024)			--содержание консультации
);
--move current request's data into backup table
INSERT INTO t_request_backup 
	SELECT	i_request, i_mr, i_mediator, i_request_category, dt_request, tm_request,
			x_declarant, x_declarant_phone, x_declarant_address, x_service_organization, 
			x_request, x_other_conflict_party, x_organization, x_consultation
		FROM t_request;
--remove t_request table	
DROP TABLE t_request;
-- create t_request with i_declarant_type
CREATE TABLE t_request
(
	i_request INTEGER NOT NULL,				--id обращения
	i_declarant_type INTEGER NOT NULL,		--id типа заявителя
	i_mr INTEGER NOT NULL,					--id муниципального района
	i_mediator INTEGER NOT NULL,			--id медиатора
	i_request_category INTEGER,				--id категории обращения
	dt_request DATE NOT NULL,				--дата обращения
	tm_request TIME NOT NULL,				--время обращения
	x_declarant VARCHAR(128) NOT NULL,		--заявитель
	x_declarant_phone VARCHAR(48),			--телефон заявителя
	x_declarant_address VARCHAR(256),		--адрес заявителя
	x_service_organization VARCHAR(128),	--управляющая компания
	x_request VARCHAR(1024) NOT NULL,		--суть обращения
	x_other_conflict_party VARCHAR(256),	--вторая сторона конфликта
	x_organization VARCHAR(128),			--ответственная организация
	x_consultation VARCHAR(1024)			--содержание консультации
);
-- move data from backup request's table
INSERT INTO t_request 
	SELECT i_request, 1 as i_declarant_type, i_mr, i_mediator, i_request_category, dt_request, tm_request,
			x_declarant, x_declarant_phone, x_declarant_address, x_service_organization, 
			x_request, x_other_conflict_party, x_organization, x_consultation
		FROM t_request_backup;
-- coomit changes
COMMIT;
