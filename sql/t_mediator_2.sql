insert into t_mediator (i_mediator,x_mediator,x_mediator_phone,x_note)
	select max(i_mediator)+1, 'Дурманова Валерия Михайловна', '+7(925)007-01-52', 'ЮВАО' from t_mediator;
insert into t_mediator (i_mediator,x_mediator,x_mediator_phone,x_note)
	select max(i_mediator)+1, 'Чучин Иван Валерьевич', '+7(925)007-01-63', 'ЗелАО' from t_mediator;