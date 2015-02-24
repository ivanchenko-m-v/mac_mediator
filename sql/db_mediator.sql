--1. t_ad - administrative division
CREATE TABLE t_ad
(
	i_ad INTEGER NOT NULL,					--id округа
	x_ad VARCHAR(64) NOT NULL,				--название округа
	x_ad_abbreviation VARCHAR(16) NOT NULL	--аббревиатура округа
);
CREATE UNIQUE INDEX idx_ad ON t_ad (i_ad ASC);
CREATE UNIQUE INDEX idx_xad ON t_ad (x_ad ASC);

--2. t_mr - municipal region 
CREATE TABLE t_mr
(
	i_mr INTEGER NOT NULL,					--id района
	i_ad INTEGER NOT NULL,					--id округа
	x_mr VARCHAR(128) NOT NULL				--название района
);
CREATE UNIQUE INDEX idx_mr ON t_mr (i_mr ASC);
CREATE UNIQUE INDEX idx_admr ON t_mr (i_ad ASC, i_mr ASC);
CREATE UNIQUE INDEX idx_xmr ON t_mr (x_mr ASC);

--3. t_mediator - mediator
CREATE TABLE t_mediator
(
	i_mediator INTEGER NOT NULL,			--id медиатора
	x_mediator VARCHAR(128) NOT NULL,		--ФИО медиатора
	x_mediator_phone VARCHAR(64),			--телефон медиатора
	x_note VARCHAR(128)						--примечание
);
CREATE UNIQUE INDEX idx_mediator ON t_mediator (i_mediator ASC);
CREATE UNIQUE INDEX idx_xmediator ON t_mediator (x_mediator ASC);

--4. t_request_category - request category
CREATE TABLE t_request_category
(
	i_request_category INTEGER NOT NULL,	--id категории обращения
	x_request_category VARCHAR(128)			--категория обращения
);
CREATE UNIQUE INDEX idx_request_category ON t_request_category (i_request_category ASC);
CREATE UNIQUE INDEX idx_xrequest_category ON t_request_category (x_request_category ASC);

--5. t_request - request
CREATE TABLE t_request
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
CREATE UNIQUE INDEX idx_request ON t_request(i_request ASC);
CREATE INDEX idx_request_mediator ON t_request(i_request ASC, i_mediator ASC);
CREATE INDEX idx_request_mr ON t_request(i_request ASC, i_mr ASC);
