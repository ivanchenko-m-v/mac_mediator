BEGIN TRANSACTION;
--ДОБАВЛЕНИЕ НОВОГО МЕДИАТОРА 'Лаврентьевой Виктории Павловне'
INSERT INTO t_mediator (i_mediator, x_mediator, x_note) values (24,'Лаврентьева Виктория Павловна','ЗелАО');
--связь нового медиатора с округом
insert into t_mediator_ad (i_mediator, i_administrative_division) values (24, 10);
--удаление связей с округо для Курцева (10)
delete from t_mediator_ad where i_mediator=10;
--вставка новой связи для Курцева(10,8)
insert into t_mediator_ad (i_mediator, i_administrative_division) values (10,8);
--ЗелАО - Лутфуллин (9,10)
insert into t_mediator_ad (i_mediator, i_administrative_division) values (9,10);
COMMIT TRANSACTION;