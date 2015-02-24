BEGIN TRANSACTION;
--BACKUP TABLE FOR MR
CREATE TABLE t_mr
(
	i_mr INTEGER NOT NULL,
	x_mr VARCHAR(256)
);
--BACKUPING DATA
INSERT INTO t_mr (i_mr,  x_mr)
	SELECT i_municipal_district, x_municipal_district 
		FROM t_municipal_district;
--UPDATING
UPDATE t_municipal_district 
	SET x_municipal_district=replace(x_municipal_district, 'Муниципальное образование', 'район');

COMMIT TRANSACTION;	
