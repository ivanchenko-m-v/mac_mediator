BEGIN TRANSACTION;
--Гришина Елена Борисовна	Ведущий специалист	ЦАО	8 925 007 01 22
UPDATE t_mediator SET x_mediator='Гришина Елена Борисовна', x_mediator_phone='+7(925)007-01-22' WHERE i_mediator=21;
--Кренева Ирина Анатольевна	Ведущий специалист	САО	8 925 007 90 55
UPDATE t_mediator SET x_mediator='Кренева Ирина Анатольевна', x_mediator_phone='+7(925)007-90-55' WHERE i_mediator=20;
--Федоткина Анастасия Юрьевна	Специалист	СВАО	8 925 007 01 61
UPDATE t_mediator SET x_mediator='Федоткина Анастасия Юрьевна', x_mediator_phone='+7(925)007-01-61' WHERE i_mediator=19;
--Кротикова Анастасия Руслановна	Специалист	ВАО	8 925 007 90 26
UPDATE t_mediator SET x_mediator='Кротикова Анастасия Руслановна', x_mediator_phone='+7(925)007-90-26' WHERE i_mediator=18;
--Самарская Елизавета Викторовна	Ведущий специалист	ЮВАО	8 925 007 90 14
UPDATE t_mediator SET x_mediator='Самарская Елизавета Викторовна', x_mediator_phone='+7(925)007-90-14' WHERE i_mediator=17;
--Алексеева Светлана Леонидовна	Специалист	ЮАО	8 925 800 35 15
UPDATE t_mediator SET x_mediator='Алексеева Светлана Леонидовна', x_mediator_phone='+7(925)800-35-15' WHERE i_mediator=16;
--Марченков Сергей Игоревич	Главный специалист	ЮЗАО	8 926 245 35 51
UPDATE t_mediator SET x_mediator='Марченков Сергей Игоревич', x_mediator_phone='+7(926)245-35-51' WHERE i_mediator=15;
--Бушева Алла Викторовна	Ведущий специалист	ЗАО	8 926 209 10 12
--UPDATE t_mediator SET x_mediator='Бушева Алла Викторовна', x_mediator_phone='+7(926)209-10-12' WHERE i_mediator=13;
COMMIT TRANSACTION;
