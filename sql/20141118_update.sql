BEGIN TRANSACTION;
--ПЕРЕИМЕНОВАТЬ ХАЛИЛОВА ВМ->НОВИКОВА  ВМ
UPDATE t_mediator SET x_mediator='Новикова Вусало Мазахировна' WHERE i_mediator=12;
--Убрать у Новиковой МВ ответственность за ЮВАО
DELETE FROM t_mediator_ad WHERE ((i_mediator=11)AND(i_administrative_division=5));
--+ Соломенко Владимир Юрьевич
INSERT INTO t_mediator (i_mediator, x_mediator, x_note)
	SELECT max(i_mediator)+1, 'Соломенко Владимир Юрьевич', 'все округа' FROM t_mediator;
--
INSERT INTO t_mediator_permissions (i_mediator, x_permissions)
	SELECT i_mediator, 'su'  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
--+  Голюсова Марина Михайловна
INSERT INTO t_mediator (i_mediator, x_mediator, x_note)
	SELECT max(i_mediator)+1, 'Голюсова Марина Михайловна', 'все округа' FROM t_mediator;
--
INSERT INTO t_mediator_permissions (i_mediator, x_permissions)
	SELECT i_mediator, 'su'  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';

COMMIT TRANSACTION;
--t_mediator_ad
BEGIN TRANSACTION;
--
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 1  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 2  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 3  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 4  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 5  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 6  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 7  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 8  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 9  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 10  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 11  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 12  FROM t_mediator WHERE x_mediator='Соломенко Владимир Юрьевич';
--
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 1  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 2  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 3  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 4  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 5  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 6  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 7  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 8  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 9  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 10  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 11  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
INSERT INTO t_mediator_ad (i_mediator, i_administrative_division) 
	SELECT i_mediator, 12  FROM t_mediator WHERE x_mediator='Голюсова Марина Михайловна';
--
COMMIT TRANSACTION;
