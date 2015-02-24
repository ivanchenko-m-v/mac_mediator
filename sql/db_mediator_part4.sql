--8. t_declarant_type - declarant types
CREATE TABLE t_declarant_type
(
	i_declarant_type INTEGER NOT NULL,		--id типа заявителя
	x_declarant_type VARCHAR(48) NOT NULL		--название типа заявителя
);
CREATE UNIQUE INDEX idx_declarant_type ON t_declarant_type (i_declarant_type ASC);

INSERT INTO t_declarant_type (i_declarant_type, x_declarant_type) VALUES(1, 'Физическое лицо');
INSERT INTO t_declarant_type (i_declarant_type, x_declarant_type) VALUES(2, 'Юридическое лицо');