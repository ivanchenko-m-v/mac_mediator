--6. t_mediator_login - mediator's logins
CREATE TABLE t_mediator_login
(
	i_mediator INTEGER NOT NULL,			--id медиатора
	x_login VARCHAR(16) NOT NULL,			--login медиатора
	x_hash VARCHAR(64) NOT NULL				--hash пароля медиатора
);
CREATE UNIQUE INDEX idx_mediator_login ON t_mediator_login (i_mediator ASC);

--7. t_mediator_ad - mediator's administrative divisions
CREATE TABLE t_mediator_ad
(
	i_mediator INTEGER NOT NULL,				--id медиатора
	i_administrative_division INTEGER NOT NULL	--id административного округа
);
CREATE UNIQUE INDEX idx_mediator_ad ON t_mediator_ad (i_mediator ASC, i_administrative_division ASC);
