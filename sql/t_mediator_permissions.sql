-- t_mediator_permissions - mediator permissions(права медиатора использовать функционал программы)
CREATE TABLE t_mediator_permissions
(
	i_mediator INTEGER NOT NULL,				--id медиатора
	x_permissions VARCHAR(16) NOT NULL			--права
);
CREATE UNIQUE INDEX idx_mediator_permissions ON t_mediator_permissions (i_mediator ASC, x_permissions ASC);

INSERT INTO t_mediator_permissions (i_mediator, x_permissions)
	VALUES (14, 'su');