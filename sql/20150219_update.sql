BEGIN TRANSACTION;
--27 КОТЕЛЬНИКОВ ПЕТР ФЕДОРОВИЧ, ЗАКРЕПЛЕН ЗА ЗАПАДНЫМ АО, ТЕЛЕФОН: 8-926-209-10-12;
INSERT INTO t_mediator (i_mediator, x_mediator, x_mediator_phone, x_note) values (27,'Котельников Пётр Фёдорович','+7(926)209-10-12','ЗАО');
--связь нового медиатора с округом
insert into t_mediator_ad (i_mediator, i_administrative_division) values (27, 8);
--назначение логина взамен выбывшего медиатора
UPDATE t_mediator_login SET i_mediator=27 WHERE i_mediator=13;
--28   ОСИПОВ ДМИТРИЙ ПАВЛОВИЧ, ЗАКРЕПЛЕН ЗА СЕВЕРО-ЗАПАДНЫМ АО, ТЕЛЕФОН: 8-925-007-01-56.
INSERT INTO t_mediator (i_mediator, x_mediator, x_mediator_phone, x_note) values (28,'Осипов Дмитрий Павлович','+7(926)007-01-56','СЗАО');
--связь нового медиатора с округом
insert into t_mediator_ad (i_mediator, i_administrative_division) values (28, 9);
--назначение логина взамен выбывшего медиатора
UPDATE t_mediator_login SET i_mediator=28 WHERE i_mediator=20;
COMMIT TRANSACTION;